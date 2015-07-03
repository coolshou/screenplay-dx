/***************************************************************************
 * Copyright (C) 2006, Alphanetworks, inc. All Rights Reserved
 * @file:    test_main.c
 * @brief:   sample code for software and hardware aes(ecb, ctr, cbc, omac1)
 * @author:  wills_yin@alphanetworks.com
 * @date:    08/Aug/2006
 * @history:
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>

#include "aes_cbc.h"

#ifdef __HW_AES__
#include "common.h"
#include "dcc/include/dcc.h"
#endif

#define AES_BLOCK_SIZE	                  16
#define BUFFER_SIZE                       (65280)
#define AES_CONTEXT_T                     aes_context

#define TIME_DIFF2(tv2, tv1) ((tv2.tv_sec - tv1.tv_sec) * 1000 *1000 + (tv2.tv_usec - tv1.tv_usec))

static char KEY[]= { 
			0x8b, 0x5c, 0x50, 0xae, 0x60, 0x8f, 0x30, 0x4c, 
			0xe7, 0x83, 0x6f, 0xe3, 0xa5, 0x90, 0xb5, 0x2a
                   };


typedef enum aes_mode_e aes_mode_t;

enum aes_mode_e {
	aes_ecb = 0,
	aes_ctr,
	aes_cbc,
	aes_omac1
};

struct aes_wrapper_t {
	/* user options */
	int            type;
	int            mode;
	int            encrypt;
	int            dump;
        /* common resource */
	char           key[AES_BLOCK_SIZE];
	int            key_size;
	int            fdr;
	int            fdw;
	char           *in;
	char           *out;
	char           IV[AES_BLOCK_SIZE];
	int            length;
	/* private data */
	void          *data;
};

struct crypt_func_t {
	int			type;
	aes_mode_t              mode;
	int                     (* init) (struct aes_wrapper_t    *aes);    
	void                    (* encrypt) (struct aes_wrapper_t *aes);    
	void                    (* decrypt) (struct aes_wrapper_t *aes);    
	int                     (* destroy) (struct aes_wrapper_t *aes);    
};

unsigned long clear_pointer = 0;
unsigned long cipher_pointer = 0;

static int   soft_cbc_init(struct aes_wrapper_t * aes);
static void  soft_cbc_encrypt(struct aes_wrapper_t * aes);
static void  soft_cbc_decrypt(struct aes_wrapper_t * aes);
static int   soft_cbc_destroy(struct aes_wrapper_t * aes);

static int   hw_cbc_init(struct aes_wrapper_t * aes);
static void  hw_cbc_encrypt(struct aes_wrapper_t * aes);
static void  hw_cbc_decrypt(struct aes_wrapper_t * aes);
static int   hw_cbc_destroy(struct aes_wrapper_t * aes);

static struct crypt_func_t aes_func_list[] =
{
	{ 0, aes_cbc, soft_cbc_init, soft_cbc_encrypt, soft_cbc_decrypt, soft_cbc_destroy},
	{ 1, aes_cbc, hw_cbc_init,   hw_cbc_encrypt,   hw_cbc_decrypt,   hw_cbc_destroy}
};

#ifdef __HW_AES__

#define MBUS_LINEAR_MAX                   0x1e00
#define MBUS_DOUBLE_MAX                   0x3c00
#define AES_MAX_BLOCKS                    255
#define AES_BYTES_PER_BLOCK               16
#define MAX_AES_LENGTH                    ((MBUS_LINEAR_MAX < (AES_MAX_BLOCKS * AES_BYTES_PER_BLOCK)) ? MBUS_LINEAR_MAX : (AES_MAX_BLOCKS * AES_BYTES_PER_BLOCK))

struct aes_hw_context {
	struct RUA *pRUA;
	struct DCC *pDCC;
};

static int Hardware_AES_128_KeySetup_Ex(struct aes_wrapper_t *aes)
{
	RMstatus status ;
	struct aes_hw_context *hw;

	if (aes->data == NULL) {
		if ( (aes->data = malloc(sizeof(struct aes_hw_context))) == NULL) {
			printf("Failed to malloc:%s:%d\n", __FILE__, __LINE__);
			exit(-1);
		}
		memset(aes->data, 0, sizeof(struct aes_hw_context));
	}
	
	hw = (struct aes_hw_context *) aes->data;

	if ( hw->pRUA == NULL) {
		status = RUACreateInstance(&hw->pRUA, 0);

		if (RMFAILED(status)) {
			printf("Error creating RUA instance! : %d\n", status);
			return -1;
		}
	}

	if ( hw->pDCC== NULL ) {
		status = DCCOpen(hw->pRUA, &hw->pDCC);

		if (RMFAILED(status)) {
			printf("Error Opening DCC! : %d\n", status);
			return -1;
		}

		status = DCCInitMicroCode(hw->pDCC);
		if (RMFAILED(status)) {
			printf("Cannot initialize microcode : %s\n", RMstatusToString(status));
			return -1;
		}
	}

	RUASetProperty(hw->pRUA, EMHWLIB_MODULE(Cipher, 0), 
			RMCipherPropertyID_AES_128_KeySetup, aes->key, sizeof(RMAESKey), 0);

	return 0;

}

#define cbc_decrypt(plain, cipher, count) \
{                                                      \
	while(count--){                                \
		*plain ^= *cipher;                     \
		*(plain+1) ^= *(cipher+1);             \
		*(plain+2) ^= *(cipher+2);             \
		*(plain+3) ^= *(cipher+3);             \
		plain+=4;                              \
		cipher+=4;                             \
	}                                              \
}

static inline int Hardware_AES_128_CBC_Decrypt(struct aes_wrapper_t *aes)
{
	struct RMcipherBuffer ciBuf;
	int total = aes->length;
	unsigned char *istart, *ostart;
	struct aes_hw_context *hw = (struct aes_hw_context *) aes->data;
	int psize, index;
	int count;
	unsigned int *cipher, *plain;

	istart = (unsigned char *)aes->in;
	ostart = (unsigned char *)aes->out;
	psize = index = 0;
	cipher = plain = NULL;

	do {
		RMuint32 completion = 1;
		ciBuf.FromAddress = (RMuint32)istart;
		ciBuf.ToAddress = (RMuint32)ostart;
	
		if (total > MAX_AES_LENGTH)
			ciBuf.Size = MAX_AES_LENGTH;
		else 
			ciBuf.Size = total;
		total -=  ciBuf.Size;

		RUASetProperty(hw->pRUA, EMHWLIB_MODULE(Cipher, 0), 
				RMCipherPropertyID_AES_128_ECB_Decrypt, &ciBuf, sizeof(ciBuf), 0);

		if (index == 1) {
			cipher = (unsigned int*)aes->IV;
			plain  = (unsigned int*)aes->out;

			count = AES_BLOCK_SIZE/ sizeof(unsigned int);
			while(count--)
				*plain++ ^= *cipher++;

			cipher = (unsigned int*)aes->in;
			count = (psize - AES_BLOCK_SIZE)/(sizeof(unsigned int) * 4);

			cbc_decrypt(plain, cipher, count);
		} else if (index > 1) {
			count = psize / (sizeof(unsigned int) * 4);

			cbc_decrypt(plain, cipher, count);
		} 

		psize = ciBuf.Size;

		istart += ciBuf.Size;
		ostart += ciBuf.Size;

		index++;

		while (completion) 
			RUAGetProperty(hw->pRUA,
					EMHWLIB_MODULE(Cipher, 0),
					RMCipherPropertyID_Hardware_Cipher_Completion,
					&completion,
					sizeof(completion));

	} while(total > 0);

	if (index == 1) {
		cipher = (unsigned int*)aes->IV;
		plain  = (unsigned int*)aes->out;

		count = AES_BLOCK_SIZE/ sizeof(unsigned int);
		while(count--)
			*plain++ ^= *cipher++;

		cipher = (unsigned int*)aes->in;
		count = (psize - AES_BLOCK_SIZE)/(sizeof(unsigned int) * 4);

		cbc_decrypt(plain, cipher, count);
	} else if (index > 1) {
		count = psize / (sizeof(unsigned int) * 4);

		cbc_decrypt(plain, cipher, count);
	} 

	memcpy(aes->IV, aes->in + aes->length - AES_BLOCK_SIZE, AES_BLOCK_SIZE); 

	return 0;
}
#endif

static int soft_cbc_init(struct aes_wrapper_t* aes)
{
	if (aes->data == NULL) {
		if ( (aes->data = malloc(sizeof(aes_context))) == NULL) {
			printf("Failed to malloc:%s:%d\n", __FILE__, __LINE__);
			return -1;
		}
		memset(aes->data, 0, sizeof(aes_context));
	}

	AES_set_key((aes_context *) aes->data, aes->key, aes->key_size);

	return 0;
}

static void  soft_cbc_encrypt(struct aes_wrapper_t * aes)
{
	aes_context *ac = (aes_context *) aes->data;	

	AES_cbc_encrypt(ac, aes->in, aes->out, aes->length, aes->IV, 1);
	memcpy(aes->IV, aes->out + aes->length - AES_BLOCK_SIZE, AES_BLOCK_SIZE); 
}

static void  soft_cbc_decrypt(struct aes_wrapper_t * aes)
{
	aes_context *ac = (aes_context *) aes->data;	

	AES_cbc_encrypt(ac, aes->in, aes->out, aes->length, aes->IV, 0);
	memcpy(aes->IV, aes->in + aes->length - AES_BLOCK_SIZE, AES_BLOCK_SIZE); 
}

static int   soft_cbc_destroy(struct aes_wrapper_t * aes)
{
	if (aes && aes->data)
		free(aes->data);

	return 0;
}

static int hw_cbc_init(struct aes_wrapper_t *aes)
{
#ifdef __HW_AES__
	Hardware_AES_128_KeySetup_Ex(aes);
#endif
	return 0;
}

static void  hw_cbc_encrypt(struct aes_wrapper_t * aes)
{
}

//#define __CBC_STATISTICS__

static void  hw_cbc_decrypt(struct aes_wrapper_t * aes)
{
#ifdef __HW_AES__
	Hardware_AES_128_CBC_Decrypt(aes);
#endif
}

static int hw_cbc_destroy(struct aes_wrapper_t* aes)
{
#ifdef __HW_AES__
	RMstatus status;
	struct aes_hw_context * hw = (struct aes_hw_context*) aes->data;

	if (!aes || !aes->data)
		return -1;

	status = DCCClose(hw->pDCC);
	if (RMFAILED(status)) {
		printf("Cannot close DCC. : %s\n", RMstatusToString(status));
	}

	status = RUADestroyInstance(hw->pRUA);
	if (RMFAILED(status)) {
		printf("Cannot destroy RUA instance : %d\n", status);
	}

	free(aes->data);
#endif
	return 0;
}

static  int aes_init_data(struct aes_wrapper_t * aes, char* argv[])
{

	int i = 1;

	memset(aes, 0, sizeof(struct aes_wrapper_t));

	if (argv[i][0] == '-' && !strcmp(argv[i], "-w")) {
		aes->dump = 1;
		i++;
	}
		
	aes->type    = atoi(argv[i]);
	aes->encrypt = atoi(argv[i+1]);

	aes->key_size = AES_BLOCK_SIZE;
	memcpy(aes->key, KEY, aes->key_size);
	
	if ( (aes->fdr = open(argv[i+2], O_RDONLY)) < 0 ) {
		fprintf(stderr, "Open %s failed:%s\n", argv[i+2], strerror(errno));
		return -1;
	}

	if ( (aes->fdw = open(argv[i+3], O_WRONLY | O_CREAT | O_TRUNC)) < 0) {
		fprintf(stderr, "Open %s failed:%s\n", argv[i+3], strerror(errno));
		return -1;
	}
	chmod(argv[i+3], S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH);

	if ( (aes->in = malloc(BUFFER_SIZE)) == NULL ){
		fprintf(stderr, "Out of memory, %s:%d\n", __FILE__, __LINE__);
		return -1;
	}

	if ( (aes->out = malloc(BUFFER_SIZE)) == NULL ){
		fprintf(stderr, "Out of memory, %s:%d\n", __FILE__, __LINE__);
		return -1;
	}

#if 1
	cipher_pointer = (unsigned long)aes->in;
	clear_pointer  = (unsigned long)aes->out;

	clear_pointer  &= 0x7fffffff;
	cipher_pointer &= 0x7fffffff;
	aes->in = cipher_pointer;
	aes->out = clear_pointer;
#endif

	return aes_func_list[aes->type].init(aes);
}

static  int aes_release_data(struct aes_wrapper_t * aes)
{
	if (!aes)
		return 0;

	if (aes->in)  free(aes->in);
	if (aes->out) free(aes->out);
	if (aes->fdr) close(aes->fdr);
	if (aes->fdw) close(aes->fdw);
	
	if (aes_func_list[aes->type].destroy)
		aes_func_list[aes->type].destroy(aes);
	return 0;
}

static void show_usage()
{
	fprintf(stderr, "Usage: <prog> [-w] <hw/soft>  <enctypt/decrypt> <read file> <write file> \n");
	fprintf(stderr, "\tOptions enctypt: 1 decrypt: \n");
	fprintf(stderr, "\t       hw: 1 soft: 0 \n");
}

int main(int argc, char* argv[]) 
{
	size_t nread;
	int total, remain;
	int            file_size;
	float          elapsed_time;
	struct timeval tv_start;
	struct timeval tv_end;
	struct aes_wrapper_t  aes;
	void  (* pfn) (struct aes_wrapper_t *aes);    

	if (argc != 5 && argc != 6 )  {
		show_usage();
		return -1;
	}

	if ( aes_init_data(&aes, argv) < 0 ) 
		goto cleanup;

	gettimeofday(&tv_start, NULL);

	file_size = 0;
	remain = 0;
	if (aes.encrypt)
		pfn = aes_func_list[aes.type].encrypt;
	else 
		pfn = aes_func_list[aes.type].decrypt;

	while ( (nread = read(aes.fdr, aes.in + remain,  BUFFER_SIZE - remain)) ) {
		total = nread + remain;
		remain = total % 16;
		aes.length = total - remain; 


		pfn(&aes);

		if (remain) {
			fprintf(stderr, "Need to memmove. remain = %d\n", remain);
			memmove(aes.in, aes.in + aes.length, remain);
		}
		if (aes.dump)
			write(aes.fdw, aes.out, aes.length);
		file_size += aes.length;
	}

	if (remain) {
		fprintf(stderr, "++++++%s:%d, remain=%d\n", __FILE__, __LINE__, remain);
		memset(aes.in + remain, 0, AES_BLOCK_SIZE - remain);
		aes.length = AES_BLOCK_SIZE;

		pfn(&aes);

		if (aes.dump)
			write(aes.fdw, aes.out, AES_BLOCK_SIZE);
		file_size += AES_BLOCK_SIZE; 

	}

	gettimeofday(&tv_end, NULL);
	elapsed_time = TIME_DIFF2(tv_end, tv_start)/1000.0/1000.0; 
	fprintf(stderr, "+++++++++++++++%s:%d,total elapsed time=%4.2f, throughput=%4.2fMbps \n", 
			__FILE__, __LINE__, elapsed_time, 
			8.0 * file_size/(1024.0 * 1024.0 *elapsed_time));
cleanup:
	aes_release_data(&aes);

	return 0;
}

