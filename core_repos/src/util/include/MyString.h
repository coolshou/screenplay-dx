/*
 * INTEL CONFIDENTIAL
 * Copyright (c) 2002, 2003 Intel Corporation.  All rights reserved.
 * 
 * The source code contained or described herein and all documents
 * related to the source code ("Material") are owned by Intel
 * Corporation or its suppliers or licensors.  Title to the
 * Material remains with Intel Corporation or its suppliers and
 * licensors.  The Material contains trade secrets and proprietary
 * and confidential information of Intel or its suppliers and
 * licensors. The Material is protected by worldwide copyright and
 * trade secret laws and treaty provisions.  No part of the Material
 * may be used, copied, reproduced, modified, published, uploaded,
 * posted, transmitted, distributed, or disclosed in any way without
 * Intel's prior express written permission. 
 *
 * No license under any patent, copyright, trade secret or other
 * intellectual property right is granted to or conferred upon you
 * by disclosure or delivery of the Materials, either expressly, by
 * implication, inducement, estoppel or otherwise. Any license
 * under such intellectual property rights must be express and
 * approved by Intel in writing.
 *  
 * $Workfile: MyString.h
 * $Revision:
 * $Author: Intel, DPA, Solution Architecture
 * $Date: 10/05/02
 * $Archive:
 */

/*
 * Implements additional string functionality.
 */

#ifndef MY_STRING_H

#include <ctype.h>
#include <stdlib.h>


/* The reverse of the above: convert a HEX digit in the [0, 15] range
 *    to an ASCII character representing it.  The A-F characters are
 *       always in upper case.  */
#define XDIGIT_TO_XCHAR(x) (((x) < 10) ? ((x) + '0') : ((x) - 10 + 'A'))

/*
 *  EndsWith()
 *      str                 : the string to analyze
 *      endsWith            : the token to find at the end of str
 *      ignoreCase          : nonzero indicates case insensitive search
 *
 *  If "str" ends with "endsWith", then we return nonzero.
 */
int EndsWith(const char* str, const char* endsWith, int ignoreCase);

/*
 *  IndexOf()
 *      str                 : the string to analyze
 *      findThis            : the token to find 
 *      ignoreCase          : nonzero indicates case insensitive search
 *
 *  Returns the first index where findThis can be found in str.
 *  Returns -1 if not found.
 */
int IndexOf(const char* str, const char* findThis);

/*
 *  IndexOf()
 *      str                 : the string to analyze
 *      findThis            : the token to find 
 *      ignoreCase          : nonzero indicates case insensitive search
 *
 *  Returns the last index where findThis can be found in str.
 *  Returns -1 if not found.
 */
int LastIndexOf(const char* str, const char* findThis);

/*
 *  IndexOf()
 *      str                 : the string to analyze
 *      startsWith          : the token to find 
 *      ignoreCase          : nonzero indicates case insensitive search
 *
 *  Returns nonzero value if the string starts with 'startsWith'.
 */
int StartsWith(const char* str, const char* startsWith, int ignoreCase);

int intUtf8ToAnsi(char *dest, const char *src, int destLen);

const wchar_t * strUtf8ToUtf16(wchar_t *dest, const unsigned char *src, int destsize, int *converted);

// int strToUtf8(char *dest, const char *src, int destSize, int isWide, int *charactersConverted);
// int strUtf8Len(char *src, int isWide, int asEscapedUri);

const unsigned char *strUtf16ToUtf8(unsigned char *dest, const wchar_t *src, int destsize, int *converted);

/*
 *  Stores UTF8-compliant escaped URI in 'dest'.
 *  Returns number of bytes used in dest.
 */
int strToEscapedUri(char *dest, const char *src, int destSize, int isWide, int *charactersConverted);

/* makes a copy of the string by mallocing a new buffer and copying
 * the string into it 
 */
char *MakeStrcpy(const char *string);


/* Chomps off the trailing newline on a string much like Perl's chomp function
 */
void StrChomp(char *s);

/* reversed the src string 's' and store the reversed string in 'rs' */
void StrReverse(char *s, char *rs);

char* encode_string_maybe(const char* s);

char MungeHexDigit(const char* one_hexdigit);
                                                                                                                            
char GetCharFromHex(const char* two_hexdigits);

extern int strHTTPUnEscape(char* data);
int strXmlUnEscape(char* data);

//if its not a colon or a forwardslash or alphanumerical then the character is url encoded
char* encodeNonAlphanumericsInUrl(const char* s);

extern int GetLastIndexOfParentPath(char* pathName, char* dirDelimiter, int includeDelimiter);
extern char *GetParentPath(char *pathName, char *dirDelimiter, int includeDelimiter);
extern char *GetFileExtension(char *pathName, int returnCopy);
#endif
