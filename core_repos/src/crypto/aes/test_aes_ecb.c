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

char Key[]={
	0x8b, 0x5c, 0x50, 0xae, 0x60, 0x8f, 0x30, 0x4c, 0xe7, 0x83, 
	0x6f, 0xe3, 0xa5, 0x90, 0xb5, 0x2a
};

char Input[]={
	0x55, 0x50, 0xd9, 0x11, 0xd2, 0x30, 0x6c, 0x79, 0x97, 0xa2, 
	0x93, 0x25, 0x33, 0x32, 0xc4, 0x86
};

char Output[]={
	0x00, 0x3d, 0x32, 0x2b, 0x05, 0x89, 0x69, 0xd5, 0x28, 0x29, 
	0xe8, 0xf2, 0xc7, 0xbd, 0x2a, 0x86
};

int main() {
	int i;
	char buf1[AES_BLOCK_SIZE];
	aes_context ac;	
	AES_set_key(&ac, Key, KEY_SIZE);
	aes_encrypt(&ac, Input,buf1);

	if(!memcmp(buf1,Output,AES_BLOCK_SIZE))
		printf("Encrypt Success! We have validated the AES-ECB mode\n");
	else
		printf("Encrypt Faied! We didn't validated the AES-ECB mode\n");
	memset(buf1,0,AES_BLOCK_SIZE);
	aes_decrypt(&ac, Output,buf1);
	if(!memcmp(buf1,Input,AES_BLOCK_SIZE))
		printf("Decrpt Success! We have validated the AES-ECB mode\n");
	else
		printf("Decrypt Faied! We didn't validated the AES-ECB mode\n");

	for(i=0;i<AES_BLOCK_SIZE;i++)
		printf("%c", buf1[i]);
	return 0;
}
