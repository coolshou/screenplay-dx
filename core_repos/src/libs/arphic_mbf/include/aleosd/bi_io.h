/*EncryptOn*/
#ifndef _BI_IO_INCLUDED_
#define _BI_IO_INCLUDED_

#include "platform.h"
#include "bi_types.h"

/* For file access define */
#if BI_FILE_ACCESS_SUPPORT
#include <stdio.h>
typedef struct
{
   FILE* fp;
   BI_BYTE* buffer;
} FileAccessInstance;
#endif

/* I/O callback function */
typedef BI_INT32 (*BIGetDataFunc) (BI_VOID* Instance,BI_INT32 offset,BI_INT32 fonlen, BI_VOID *Buff);

#ifdef  __cplusplus
extern "C" {
#endif

BI_INT32    AR_GetDataBufferFuncROM(BI_VOID* Instance,BI_INT32 offset,BI_INT32 fonlen, BI_VOID *Buff);
BI_INT32    AR_GetDataBufferFuncFILE(BI_VOID* Instance,BI_INT32 offset,BI_INT32 fonlen, BI_VOID *Buff);
#if  FOR_ROM_POINTER_ACCESS
BI_INT32    AR_GetDataDirectFuncROM(BI_VOID* Instance,BI_INT32 offset,BI_INT32 fonlen, BI_VOID **Buff);
#endif
BI_INT32 	FreetypeToBuffer(BI_VOID *data, BI_INT32 offset, BI_INT32 fonlen, BI_VOID *Buff);
#if BI_FILE_PART_SUPPORT
BI_INT32 	GetPartDataToBuffer(BI_VOID *data, BI_INT32 offset, BI_INT32 fonlen, BI_VOID *Buff);
BI_INT32 	binarysearch(BI_UINT16* data, BI_INT32 search, BI_INT32 n);
#endif
#ifdef	__cplusplus
}
#endif



#endif
