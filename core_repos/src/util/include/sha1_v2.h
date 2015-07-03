#ifndef SHA1_V2_H
#define SHA1_V2_H

#define SHA1_HASH_BIT_LENGTH 160                       //160bit
#define SHA1_HASH_BYTE_LENGTH (SHA1_HASH_BIT_LENGTH/8) //20 byte 

typedef unsigned int u32;
typedef unsigned char byte;

typedef struct {
    u32  h0,h1,h2,h3,h4;
    u32  nblocks;
    byte buf[64];
    int  count;
} SHA1_CONTEXT;

void sha1_init (void *context);
void sha1_write( void *context, byte *inbuf, size_t inlen);
void sha1_final(void *context);

#endif

