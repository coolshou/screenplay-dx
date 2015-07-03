/*
//-------------------------------------------------------------------------
// Arphic Bitmap Font API  ver $Name: le_v02170300_20090402 $
//
//  essential data definition
//
// Copyright (C) 2001-2009 Arphic Technology Co., Ltd.
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
#ifndef  RBMP_LITTLE_ENDIAN
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

        /*
            NOTE: to make layout engine compatible with old customers,
             change constant with Arphic Layout Engine (aleuser.h)
         */
#define SUCCESS_GETFONT    111

#define ERROR_NOFONT       -201
#define ERROR_CODETYPE     -202
#define ERROR_CODE         -203
#define ERROR_FONTSIZE     -204
#define ERROR_WORKBUFFER   -205
#define ERROR_MAPTABLE     -206

/*200409*/
#define ERROR_WRONGHEADER   -207
#define ERROR_ENDIANMISMATCH -208


  #define ERROR_BIDI_INSUFFICIENT_BUFFER -209
  #define ERROR_BIDI_TYPE_NUMBER  -210
  #define ERROR_BIDI_UNSUPPORTED -211


#define ERROR_DATATYPE  -212
#define ERROR_MEMORY_FONT_ONLY  -213
#define ERROR_MEMORY_FONT_NULL  -214

#define ERROR_WORKBUFFER_32BITALIGN -215

#define ERROR_CACHE_BUFFER -216
#define ERROR_CACHE_NOT_SUPPORTED -217

  /* 2006/05/15 NOTE: -230~-999 is left for layout engine) */

/*==================================*/



#ifdef   RBMP_LITTLE_ENDIAN  /*for program coding base on little-Endian*/
   #define aUSHORT(x) (ALE_UINT16)((((ALE_UINT16)(x))<<8) | (((ALE_UINT16)(x))>>8))
   #define aULONG(x)  (ALE_UINT32)(((ALE_UINT32)(x)>>24) | ((((ALE_UINT32)(x)<<8)>>24)<<8) | ((((ALE_UINT32)(x)<<16)>>24)<<16)| ((ALE_UINT32)(x)<<24))
#else   /*for program coding base on Big_endian*/
   #define aUSHORT(x)   (x)
   #define aULONG(x)    (x)
#endif

#define  cvUSHORT(x) ((x)=aUSHORT(x))
#define  cvULONG(x) ((x)=aULONG(x))

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
                        ALE_UINT16 *Segments;
                               /* each segment contains a start code and a length code
                                   so it have SegmentTotal*2 entries.

                                   NOTE: half-font not supported.
                                   Do not send segment <0x7F unless you put char in full font.
                                */

                        ALE_INT32 CacheSize; /* # of entries in Cache */
                        RBMPCharPartialInfo *Cache;

                     } RBMPCharInfoCache;


#endif




