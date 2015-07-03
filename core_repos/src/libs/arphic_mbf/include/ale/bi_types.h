/*EncryptOn*/
/************************************************************************
;
;   (C) Copyright Arphic Technology Corp. 1993-2005
;
;    Title:     Arphic Mobile Font Rasterizer
;
;    Module:    bi-types (include file)
;
;    Version:   1.00
;
;    Author:    Koffman Huang
;
;***********************************************************************/

#ifndef bi_typesH
#define bi_typesH

/*******************************************************************************
    All types define
*******************************************************************************/
 
#define  BI_VOID                void
#define  BI_BYTE                signed char
#define  BI_UBYTE               unsigned char
#define  BI_INT16               short
#define  BI_UINT16              unsigned short
#define  BI_INT32               long
#define  BI_UINT32              unsigned long
#if ((defined(_MSC_VER)) && (_MSC_VER < 1400))
	#define  BI_INT64           __int64
#elif (defined(_ICC))
	#define  BI_INT64           double
#else
	#define  BI_INT64           long long
#endif

   /* type definition used in layout engine
      -------------------------------------------------------- */
   #ifndef ALE_DATATYPE
   #define ALE_DATATYPE
   #define ALE_CHAR    BI_BYTE
   #define ALE_UBYTE   BI_UBYTE
   #define ALE_INT16   BI_INT16
   #define ALE_UINT16  BI_UINT16
   #define ALE_INT32   BI_INT32
   #define ALE_UINT32  BI_UINT32
   #endif


/*********
 * stdio.h replacement
 *********/
#define Ar_NULL 0
#define Ar_ABS(x) (((x)<0) ? (-(x)) : (x))


#endif   /* #ifndef bi_typesH */
