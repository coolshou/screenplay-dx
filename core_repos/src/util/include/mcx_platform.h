#ifndef __MCX_PLATFORM_H__
#define __MCX_PLATFORM_H__

#ifdef __x86__
#define pkAPI 
typedef int bool_t;
typedef unsigned int uint32_t;
typedef int32_t   pkRESULT;
typedef char TCHAR;
#else 
#include "rmpaltypes.h"			/* mcx/PAK-B7/Source/Platform/SigmaDesignsEM8622L-PAL-B21/PALimpl/include/rmpaltypes.h */
#endif

#include "pkPlatform.h"			/* mcx/PAK-B7/Source/PAL/pkPlatform.h */
#include "DisconnectReasons.h" 		/* mcx/PAK-B7/Source/PDK/XSP/Shared/DisconnectReasons.h */
#endif
