/*EncryptOn*/
/************************************************************************
;
;   (C) Copyright Arphic Technology Corp. 1993-2005
;
;    Title:     Arphic Mobile Font Rasterizer
;
;    Module:    Curve generator (include file)
;
;    Version:   1.03
;
;    Author:    Henry Huang
;
;***********************************************************************/

#ifndef _NEWGENTASKING_INCLUDED_
#define _NEWGENTASKING_INCLUDED_

#include "bi_types.h"
#include "typedef2.h"
#include "platform.h"

BI_INT32   Atopdown_newgen_init_multitasking(PTArVarGlobalAll_forCurvGen pp);
BI_INT32   Atopdown_newgen_multitasking(PTArVarGlobalAll_forCurvGen pp,BI_UBYTE *bmapbuf,BI_INT32 widthB,BI_INT32 *pathbuff2,BI_INT32 pathbuff9ptr);

#endif

