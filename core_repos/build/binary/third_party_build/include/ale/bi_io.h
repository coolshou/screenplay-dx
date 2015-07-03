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

#ifdef	__cplusplus
}
#endif



#endif
