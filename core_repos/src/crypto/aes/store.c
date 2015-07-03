/***************************************************************************
 * Copyright (C) 2007, Alphanetworks, inc. All Rights Reserved
 * @file:    store.c
 * @brief:   Convert the mcx bin files to sfio files with AES CTR mode
 * @author:  wills_yin@alphanetworks.com
 * @date:    Dec/26/2007
 * @history:
 ***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include "aes_cbc.h"
#include "aes.h"

/* alpha AES key. */
static unsigned char aeskey[16] = {
	0xad, 0x18, 0xc3, 0x04,
	0x80, 0x91, 0x2e, 0x65,
	0x27, 0xbc, 0xf9, 0x5b,
	0x4c, 0xee, 0x36, 0xda
};

/* Random device to generate IV */
#define RANDOMDEV             "/dev/urandom"

#define SECURITY_AES_BLOCKLEN 16

#define MAX_NAME_LEN	(256)

#define CERT_SFIO	"cert.SigmaDesignsEM862xLDeviceCertificate.sfio"
#define PKEY_SFIO	"rsapKey.SigmaDesignsEM862xLDevicePrivateKey.sfio"
#define CRTPKEY_SFIO	"rsacrtpKey.SigmaDesignsEM862xLDevicePrivateKey.sfio"
#define CPKEY_SFIO	"cardea_key.sfio"
#define CCRTPKEY_SFIO	"cardea_crtkey.sfio"

#define CERT_BIN        "cert.bin"
#define PKEY_BIN        "pkey.bin"
#define CRTPKEY_BIN     "crtpkey.bin"
#define CPKEY_BIN       "cpkey.bin"
#define CCRTPKEY_BIN    "ccrtpkey.bin"

#define BUF_SIZE	(4096)

#define SUCCESS     0
#define FAILURE     -1

struct file_map {
	char           cmd; 
	char           user_bin[MAX_NAME_LEN];
	const char *   def_bin;
	const char *   sfio;
};

static struct file_map file_array[] = {
	{ 'c',  "\0",   CERT_BIN,      CERT_SFIO,      },
	{ 'k',  "\0",   PKEY_BIN,      PKEY_SFIO,      },
	{ 't',  "\0",   CRTPKEY_BIN,   CRTPKEY_SFIO,   },
	{ 'r',  "\0",   CPKEY_BIN,     CPKEY_SFIO,     },
	{ 's',  "\0",   CCRTPKEY_BIN,  CCRTPKEY_SFIO   },
	{ '?',  "\0",   NULL,          NULL,           }
};

static void usage(const char *name)
{
	assert(NULL != name);

	fprintf(stderr,
		"\n"
		"Usage: %s [-c CERT.BIN] [-k PKEY.BIN] [-r CPKEY.BIN] [-t CRTPKEY.BIN] [-s CCRTPKEY.BIN]\n"
		"  Creates device cert and private key files as suitable for\n"
		"  later usage by the security PAL. The created file(s) must\n"
		"  be later installed at the correct place on the target file\n"
		"  system.\n"
		"  \n"
		"  Options are not mandatory. If none is specified, the \n"
		"  utility will attempt to process the device cert,\n"
		"  the device private key, \n"
		"  as well as the Cardea private key\n"
		"  from 'cert.bin', 'pkey.bin'/'crtpkey.bin' and 'cpkey.bin/ccrtpkey.bin' in\n"
		"  the current directory, respectively. If either option is\n"
		"  present, only the corresponding element will be processed.\n"
		"  If all options are present, all elements will be\n"
		"  processed, from the passed file arguments.\n"
		"  \n"
		"  Note: because it uses the software AES CTR, \n"
		"  So, this utility needn't be run on the target system.\n"
		"  \n", name);
}

static void save_user_bin(char cmd, char *optarg)
{
	int i = 0;

	while (file_array[i].sfio) {
		if (file_array[i].cmd == cmd) {
			snprintf(file_array[i].user_bin, MAX_NAME_LEN - 1, "%s", optarg);
			return;
		}
		i++;
	}
}

static void iv_add_(unsigned char * iv_base, unsigned int incr)
{
	unsigned long int tmp;

	if (incr){
		tmp = *iv_base + (incr & 0xFF);
		if (tmp > 0xFF){
			iv_add_(iv_base-1, tmp >> 8);
		}
		*iv_base = tmp & 0xFF;
		iv_add_(iv_base-1, incr >> 8);
	}
}

static void iv_add(unsigned char *iv_base, unsigned int incr) 
{
	iv_add_(iv_base + SECURITY_AES_BLOCKLEN - 1, incr);
}

static int cert_get_iv(unsigned char *iv) 
{
	FILE * iv_source;
	int n_read = 0 ;

	
	if ( (iv_source = fopen(RANDOMDEV, "r")) == NULL)
		return -1;

	n_read = fread((void *)iv, 1, SECURITY_AES_BLOCKLEN, iv_source);

	fclose(iv_source);

	return ( n_read == SECURITY_AES_BLOCKLEN ? 0 : -1);
}

static int do_store(const aes_context *ac, const char *bin_name, const char *sfio_name)
{
	size_t nread;
	FILE *fin, *fout;
	int i, r = SUCCESS;

	unsigned char buf[SECURITY_AES_BLOCKLEN];
	unsigned char aesiv[SECURITY_AES_BLOCKLEN];
	unsigned char buf1[SECURITY_AES_BLOCKLEN];

	assert(ac);
	assert(NULL != bin_name && bin_name[0] != '\0');
	assert(NULL != sfio_name && sfio_name[0] != '\0');

	fin = fout = NULL;

	fin = fopen(bin_name, "rb");
	if (NULL == fin) {
		perror(bin_name);
		r = FAILURE;
		goto release;
	} 

	fout = fopen(sfio_name, "w");
	if (NULL == fout) {
		perror(sfio_name);
		r = FAILURE;
		goto release;
	} 

	cert_get_iv(aesiv);
	fwrite(aesiv, 1, SECURITY_AES_BLOCKLEN, fout);

	do {
		memset(buf, 0, SECURITY_AES_BLOCKLEN);

		nread = fread(buf, sizeof *buf, SECURITY_AES_BLOCKLEN, fin);
		if (nread == 0) {
			fprintf(stderr, "%s:%d, nread=%d\n", __FUNCTION__, __LINE__, nread);
			break;
		} else if (nread < 0) {
			perror("nread < 0\n");
			break;
		}

		aes_encrypt(ac, aesiv, buf1);
		for (i = 0; i < SECURITY_AES_BLOCKLEN; i++)
			buf1[i] ^= buf[i];
		fwrite(buf1, 1, nread, fout);

		iv_add(aesiv, 1);
	} while (1);

release:
	if (fin) 
		fclose(fin);
	if (fout)
		fclose(fout);
	return r;
}

int main(int argc, char **argv)
{
	int i, opt;
	int usercmd = 0, r = SUCCESS;

	aes_context ac;	

	while (-1 != (opt = getopt(argc, argv, "c:k:t:r:s:"))) {
		switch (opt) {
		case 'c':
			fprintf(stderr, "input cert bin: %s.\n", optarg);
			save_user_bin(opt, optarg);
			usercmd = 1;
			break;
		case 'k':
			fprintf(stderr, "input pkey bin: %s.\n", optarg);
			save_user_bin(opt, optarg);
			usercmd = 1;
			break;
		case 't':
			fprintf(stderr, "input crtpkey bin: %s.\n", optarg);
			save_user_bin(opt, optarg);
			usercmd = 1;
			break;
		case 'r':
			fprintf(stderr, "input cpkey bin: %s.\n", optarg);
			save_user_bin(opt, optarg);
			usercmd = 1;
			break;
		case 's':
			fprintf(stderr, "input ccrtpkey bin: %s.\n", optarg);
			save_user_bin(opt, optarg);
			usercmd = 1;
			break;
		case '?':
		case ':':
		default:
			r = FAILURE;
			usage(argv[0]);
			break;
		}
		if (SUCCESS != r) {
			break;
		}
	}

	if (SUCCESS != r || optind < argc) {
		fprintf(stderr, "Unrecognized non-option command line argument(s).\n");
		r = FAILURE;
		goto exit;
	} 
		
	AES_set_key(&ac, aeskey, SECURITY_AES_BLOCKLEN);

	i = 0;
	while (file_array[i].sfio) {
		if (usercmd) {
			if (file_array[i].user_bin[0] != '\0') 
				r = do_store(&ac, file_array[i].user_bin, file_array[i].sfio);
		} else {
			r = do_store(&ac, file_array[i].def_bin, file_array[i].sfio);
		}
		if (r == FAILURE) 
			fprintf(stderr, "%s created failed\n\n", file_array[i].sfio);
		i++;
	}
exit:

	return r;
}

