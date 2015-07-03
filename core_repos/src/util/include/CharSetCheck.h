#ifndef _CHAR_SET_CHECK_H_

#define _CHAR_SET_CHECK_H_

#define CSC_REMOVE_SPACE	(0x10)
#define CSC_UTF16_BE		(0x1)	// Big endian
#define CSC_UTF16_LE		(0x2)	// Little endian

#include <endian.h>

#if __BYTE_ORDER == __LITTLE_ENDIAN
	#define CSC_UTF16_CUR_ENDIAN CSC_UTF16_LE
#elif __BYTE_ORDER == __BIG_ENDIAN
	#define CSC_UTF16_CUR_ENDIAN CSC_UTF16_BE
#else
	#error "We don't have endian ?"
#endif


int CSC_UTF16_To_UTF8(char* string, char* utf8buf, int *len, int flag);

#endif // _MY_CHAR_SET_H_
