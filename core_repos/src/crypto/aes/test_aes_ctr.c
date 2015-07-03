#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include "aes_cbc.h"
#include "aes.h"
#define AES_BLOCK_SIZE	16
#define KEY_SIZE 	128	/* bits */

#define EMT_AESCBC_BLKLEN AES_BLOCK_SIZE
#define AES_CONTEXT_T  aes_context
#define EMT_ESPAES_KEY_SZ 16
int pretty_print(const unsigned char *buf, int count) {
	int i=0;
	for (;i<count;i++) {
		if (i%8==0) putchar(' ');
		if (i%16==0) putchar('\n');
		printf ("%02hhx ", buf[i]);
	}
	putchar('\n');
	return i;
}

/*
 *	The AES in Counter mode Arrays
 */
char Key[]={
	0x60, 0x09, 0x5e, 0xcd, 0xf6, 0x1e, 0xa4, 0x6b, 0xac, 0x69, 
	0xc4, 0xab, 0x32, 0x5d, 0x72, 0x08
};

char DataId[]={
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

char Input[]={
	0x95, 0xdd, 0xad, 0xbf, 0x43, 0x03, 0xa6, 0x05, 0xe7, 0x95, 
	0xbf, 0x06, 0x18, 0x46, 0xeb, 0xaf
};

char Output[]={
	0xaa, 0x9b, 0x36, 0x83, 0xeb, 0x9d, 0xee, 0xab, 0x06, 0xbe, 
	0xb3, 0x63, 0xa3, 0x90, 0x84, 0xee
};

int main() {
	int i;
	char buf1[AES_BLOCK_SIZE];
	aes_context ac;	
	AES_set_key(&ac, Key, KEY_SIZE);
	aes_encrypt(&ac, DataId,buf1);
	
	for(i=0;i<AES_BLOCK_SIZE;i++)
		buf1[i]^=Input[i];
	if(!memcmp(buf1,Output,AES_BLOCK_SIZE))
		printf("Encrypt Success! We have validated the AES-CTR mode\n");
	else
		printf("Encrypt Faied! We didn't validated the AES-CTR mode\n");
	memset(buf1,0,AES_BLOCK_SIZE);

	aes_encrypt(&ac, DataId,buf1);
	for(i=0;i<AES_BLOCK_SIZE;i++)
		buf1[i]^=Output[i];
	if(!memcmp(buf1,Input,AES_BLOCK_SIZE))
		printf("Decrypt Success! We have validated the AES-CTR mode\n");
	else
		printf("Decrypt Faied! We didn't validated the AES-CTR mode\n");

	return 0;
}
