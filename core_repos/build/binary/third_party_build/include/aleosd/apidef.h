/*
//-------------------------------------------------------------------------
// Arphic Bitmap Font API  ver $Name$
//
//  essential data definition
//
// Copyright (C) 2001-2010 Arphic Technology Co., Ltd.
// All rights reserved.
//-------------------------------------------------------------------------
// API Version 2.02  (for 16/32 bits compiling)
//-------------------------------------------------------------------------
*/
#ifndef __APIDEF1__
#define __APIDEF1__


/* ------------- PLATFORM DEPENDENT SETTING --------------------------- */

/* .............................Below code is controlled by source controller, do not modify */
/* @@_ALE_AUTO_SOURCE ENDIAN */



/* Little Endian/Big Endian CPU ? */
/* DISABLE these 3 lines while compiling for Big-Endian CPU */
#if (!defined (RBMP_LITTLE_ENDIAN) && !defined (RBMP_BOTH_ENDIAN))
#define  RBMP_LITTLE_ENDIAN
#endif

/* @@_ALE_AUTO_SOURCE - */
/* .............................Above code is controlled by source controller, do not modify */

/* FOR Mobile Font: unmark this line if layout engine not bundled */
/* #define __RBMP_NO_LAYOUTENGINE__ */


/*-------------------------------------------------------------------------*/

   /* Type. NOTE: modify with aleuser.h, layout engine
      ---------------------------------------------------------------- */
   #ifndef ALE_DATATYPE

    #define ALE_DATATYPE
    #define ALE_CHAR    signed char
    #define ALE_UBYTE   unsigned char
    #define ALE_INT16   signed short
    #define ALE_UINT16  unsigned short
    #define ALE_INT32   signed long
    #define ALE_UINT32  unsigned long
   #endif

   /* Font data pointer modifier
      ---------------------------------------- */
   #if defined(RBMP_FONTPTR_PRE) || defined (RBMP_FONTPTR_POST)
        /*
           NOTE: if you #define one of above macro, you must also
             write a function the same as memcpy ():
             ALE_UBYTE *RbmpFontDatacpy
                 (void *dest, RBMP_FONTDATA  *src, ALE_INT32 len);
         */
      #ifndef RBMP_FONTDATA_USERDEFINED
      #define RBMP_FONTDATA_USERDEFINED
      #endif
   #endif

   #ifndef RBMP_FONTPTR_PRE
   #define RBMP_FONTPTR_PRE
   #endif
   #ifndef RBMP_FONTPTR_POST
   #define RBMP_FONTPTR_POST
   #endif
   #ifndef RBMP_FONTDATA
   #define RBMP_FONTDATA   RBMP_FONTPTR_PRE void RBMP_FONTPTR_POST
   #endif
   #ifndef RBMP_FONTACCESS
   #define RBMP_FONTACCESS  RBMP_FONTPTR_PRE ALE_UBYTE RBMP_FONTPTR_POST
   #endif

/* ==================================================================== */
/* Error Codes */
        /*
            NOTE: to make layout engine compatible with old customers,
             change constant with Arphic Layout Engine (aleuser.h)
         */
#define RBMP_SUCCESS_GETFONT    111

#define RBMP_ERROR_NOFONT       -201
#define RBMP_ERROR_CODETYPE     -202
#define RBMP_ERROR_CODE         -203
#define RBMP_ERROR_FONTSIZE     -204
#define RBMP_ERROR_WORKBUFFER   -205
#define RBMP_ERROR_MAPTABLE     -206

#define RBMP_ERROR_WRONGHEADER   -207
#define RBMP_ERROR_ENDIANMISMATCH -208

#define RBMP_ERROR_BIDI_INSUFFICIENT_BUFFER -209
#define RBMP_ERROR_BIDI_TYPE_NUMBER  -210
#define RBMP_ERROR_BIDI_UNSUPPORTED -211

#define RBMP_ERROR_DATATYPE  -212
#define RBMP_ERROR_MEMORY_FONT_ONLY  -213
#define RBMP_ERROR_MEMORY_FONT_NULL  -214

#define RBMP_ERROR_WORKBUFFER_32BITALIGN -215

#define RBMP_ERROR_CACHE_BUFFER -216
#define RBMP_ERROR_CACHE_NOT_SUPPORTED -217

#define RBMP_ERROR_FONT_ADDRESS_ALIGN -218
#define RBMP_ERROR_FONT_DATA_ALIGN -219

  /* 2006/05/15 NOTE: -230~-999 is left for layout engine) */

/*==================================*/



#ifdef   RBMP_LITTLE_ENDIAN  /*for program coding base on little-Endian*/
   #define RBMP_aUSHORT(x) (ALE_UINT16)((((ALE_UINT16)(x))<<8) | (((ALE_UINT16)(x))>>8))
   #define RBMP_aULONG(x)  (ALE_UINT32)(((ALE_UINT32)(x)>>24) | ((((ALE_UINT32)(x)<<8)>>24)<<8) | ((((ALE_UINT32)(x)<<16)>>24)<<16)| ((ALE_UINT32)(x)<<24))
#else   /*for program coding base on Big_endian*/
   #ifdef RBMP_BOTH_ENDIAN
     #define RBMP_aUSHORT(x) (ALE_UINT16)((((ALE_UINT16)(*((ALE_UBYTE*)(&(x)))))<<8) | ((ALE_UINT16)( ((ALE_UBYTE*)(&(x)))[1]  )))
     #define RBMP_aULONG(x) (ALE_UINT32)(((ALE_UINT32)(((ALE_UBYTE*)(&(x)))[3])) | (((ALE_UINT32)(((ALE_UBYTE*)(&(x)))[2]))<<8) | (((ALE_UINT32)(((ALE_UBYTE*)(&(x)))[1]))<<16)| ((ALE_UINT32)(*((ALE_UBYTE*)(&(x))))<<24))
   #else
     #define RBMP_aUSHORT(x)   (x)
     #define RBMP_aULONG(x)    (x)
   #endif
#endif

#define  RBMP_cvUSHORT(x) ((x)=RBMP_aUSHORT(x))
#define  RBMP_cvULONG(x) ((x)=RBMP_aULONG(x))


/* -------------------------------------------------------------------- */
/* Old Macro Names */

#ifndef RBMP_DISABLE_OLD_DEFINE

     #define SUCCESS_GETFONT    RBMP_SUCCESS_GETFONT

     #define ERROR_NOFONT       RBMP_ERROR_NOFONT
     #define ERROR_CODETYPE     RBMP_ERROR_CODETYPE
     #define ERROR_CODE         RBMP_ERROR_CODE
     #define ERROR_FONTSIZE     RBMP_ERROR_FONTSIZE
     #define ERROR_WORKBUFFER   RBMP_ERROR_WORKBUFFER
     #define ERROR_MAPTABLE     RBMP_ERROR_MAPTABLE

     #define ERROR_WRONGHEADER          RBMP_ERROR_WRONGHEADER
     #define ERROR_ENDIANMISMATCH       RBMP_ERROR_ENDIANMISMATCH

     #define ERROR_BIDI_INSUFFICIENT_BUFFER   RBMP_ERROR_BIDI_INSUFFICIENT_BUFFER
     #define ERROR_BIDI_TYPE_NUMBER           RBMP_ERROR_BIDI_TYPE_NUMBER
     #define ERROR_BIDI_UNSUPPORTED           RBMP_ERROR_BIDI_UNSUPPORTED

     #define ERROR_DATATYPE                 RBMP_ERROR_DATATYPE
     #define ERROR_MEMORY_FONT_ONLY         RBMP_ERROR_MEMORY_FONT_ONLY
     #define ERROR_MEMORY_FONT_NULL         RBMP_ERROR_MEMORY_FONT_NULL

     #define ERROR_WORKBUFFER_32BITALIGN    RBMP_ERROR_WORKBUFFER_32BITALIGN

     #define ERROR_CACHE_BUFFER             RBMP_ERROR_CACHE_BUFFER
     #define ERROR_CACHE_NOT_SUPPORTED      RBMP_ERROR_CACHE_NOT_SUPPORTED

     #define ERROR_FONT_ADDRESS_ALIGN       RBMP_ERROR_FONT_ADDRESS_ALIGN
     #define ERROR_FONT_DATA_ALIGN          RBMP_ERROR_FONT_DATA_ALIGN


     /*==================================*/


     #define aUSHORT   RBMP_aUSHORT
     #define aULONG    RBMP_aULONG
     #define cvUSHORT  RBMP_cvUSHORT
     #define cvULONG   RBMP_cvULONG


#endif  /* RBMP_DISABLE_OLD_DEFINE */


/* ==================================================================== */

/*==================================*/
/*#define  MaxFnum  15*/
/*
//---for working buffer------
   ///ALE_INT32              FontInfoSize=28;
   ///ALE_UINT32     FListOffs;
   ///ALE_UINT16    FontNumbers ;
   ///ALE_INT32              FontListIdx;
*/

/*---------------------------*/

         #define RBMP_FontAttr_Italic 0x1
         #define RBMP_FontAttr_Bold 0x2
         #define RBMP_FontAttr_UnderLine 0x4

         #define RBMP_Codepage_All  -32768


         /* for internal use */
         #define RBMP_FontAttr_WithKern 0x10
         #define RBMP_FontAttr_SelfMap 0x20
         #define RBMP_FontAttr_UnpackBit  0x10

         #define RBMP_FontAttr_AllGeneral 0x07
         #define RBMP_FontAttr_SearchMask 0xFFCF

struct FONTTYPEFACE
{
    ALE_INT16 CodePage;
    ALE_INT16 FontWidth;
    ALE_INT16 FontHeight;
    ALE_INT16 FontAttr;
    ALE_INT16 FontAttrValue;
    ALE_INT16 reserved;
};

struct FONTMETRICS
{
    ALE_INT16   outBufWidth;
    ALE_INT16   outBufHeight;
    ALE_INT16   Ascender;

      /* exchange following 2 fields for 32-bit padding,
         suggested by Koffman */
    ALE_INT16   horiAdvance;
    ALE_CHAR    OriginX;

    /* for Hindi or other languages */
    ALE_CHAR Extend1;
    ALE_CHAR Extend2;
    ALE_CHAR Reserved1;
};



           /*
              NOTE: modify following macros with font conterting tools
                in directory genFd2.100 & genFile2.100
                For Speed, the most commonly used font type 10 & type 8  is written at beginning
            */
#define ArphicRBMP_IsProportionalFormat(f) ( (f)==10 || (f) == 8 || (f)==3 || ((f) >=7 && (f) <=13))
#define ArphicRBMP_IsRowScanFormat(f) ( (f)==10 || (f)==8 || (f)==5 || (f)==6  || (f) ==9  || (f) == 12)
#define ArphicRBMP_IsColumnScanFormat(f) ( (f)== 11 || ((f)>=1 && (f)<=3) || (f) ==7 || (f) == 13 )
#define ArphicRBMP_IsByteAlignedFormat(f) ((f)==10 || (f)==8 || (f)==1 || (f)==5 || (f) ==7  || (f) == 11)
#define ArphicRBMP_IsBitAlignedFormat(f) ((f)==2 || (f)==3 || (f) ==6 || (f)==9 || (f) == 12 || (f) == 13 )
#define ArphicRBMP_FormatHasExtendMetrics(f) ((f)==10 || ((f) >= 11 && (f) <= 13) )

/*  2005/03/18 increase working buffer to 2048
 */
#define ArphicRBMP_MinWorkBufferSize 2048



   /* Char Info Cache
      -------------------------------- */
                    typedef struct _RBMPCharPartialInfo
                     {
                        ALE_UINT16 GlyphIndex;
                        ALE_CHAR Padding1, Padding2;
                        ALE_CHAR OriginX, horiAdvance, Extend1, Extend2;
                     } RBMPCharPartialInfo;


                    typedef struct _RBMPCharInfoCache
                     {
                        ALE_INT16 SegmentTotal;
                        ALE_INT16 Padding1;

                        ALE_UINT16 *Segments;
                               /* each segment contains a start code and a length code
                                   so it have SegmentTotal*2 entries.

                                   NOTE: half-font not supported.
                                   Do not send segment <0x7F unless you put char in full font.
                                */
                        ALE_UINT16 *Padding2;

                        ALE_INT32 CacheSize; /* # of entries in Cache */
                        RBMPCharPartialInfo *Cache;

                     } RBMPCharInfoCache;


#endif




