/*

       Arphic Layout Engine    ver $Name$
           Copyright (C) 2001-2010 Arphic Technology Co., Ltd. All rights reserved.

         include file for user

 */

#ifndef  __ARPHIC_ALEUSER_H__
#define  __ARPHIC_ALEUSER_H__

/***********
 * Added by builder kit
 ***********/
 #define __ALE_C_MEM_FUNC__ 1
/*** end ***/

#define LeVersion "$Name: le_v03030000_20100929 $"


/* .............................Below code is controlled by source controller, do not modify */


#define __ARPHIC_LAYOUTENGINE_PARTIALLANGUAGE__

#ifndef __ARPHIC_LAYOUTENGINE_ARABIC__
#define __ARPHIC_LAYOUTENGINE_ARABIC__
#endif

#ifndef __ARPHIC_LAYOUTENGINE_HEBREW__
#define __ARPHIC_LAYOUTENGINE_HEBREW__
#endif



































































/* .............................Above code is controlled by source controller, do not modify */


   /* Language Control
      -------------------------------------------------------- */

                /* To make layout engine compatible with old customers,
                    we support original macros
                    ---------------------------------------------------------------- */
                  #ifdef __ARPHIC_BITMAPAPI_ALLLANGUAGE__
                    #ifndef __ARPHIC_LAYOUTENGINE_ALLLANGUAGE__
                    #define __ARPHIC_LAYOUTENGINE_ALLLANGUAGE__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_PARTIALLANGUAGE__
                    #ifndef __ARPHIC_LAYOUTENGINE_PARTIALLANGUAGE__
                    #define __ARPHIC_LAYOUTENGINE_PARTIALLANGUAGE__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_HINDI__
                    #ifndef __ARPHIC_LAYOUTENGINE_HINDI__
                    #define __ARPHIC_LAYOUTENGINE_HINDI__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_BENGALI__
                    #ifndef __ARPHIC_LAYOUTENGINE_BENGALI__
                    #define __ARPHIC_LAYOUTENGINE_BENGALI__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_TAMIL__
                    #ifndef __ARPHIC_LAYOUTENGINE_TAMIL__
                    #define __ARPHIC_LAYOUTENGINE_TAMIL__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_SINHALA__
                    #ifndef __ARPHIC_LAYOUTENGINE_SINHALA__
                    #define __ARPHIC_LAYOUTENGINE_SINHALA__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_GURMUKHI__
                    #ifndef __ARPHIC_LAYOUTENGINE_GURMUKHI__
                    #define __ARPHIC_LAYOUTENGINE_GURMUKHI__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_GUJARATI__
                    #ifndef __ARPHIC_LAYOUTENGINE_GUJARATI__
                    #define __ARPHIC_LAYOUTENGINE_GUJARATI__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_MALAYALAM__
                    #ifndef __ARPHIC_LAYOUTENGINE_MALAYALAM__
                    #define __ARPHIC_LAYOUTENGINE_MALAYALAM__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_TELUGU__
                    #ifndef __ARPHIC_LAYOUTENGINE_TELUGU__
                    #define __ARPHIC_LAYOUTENGINE_TELUGU__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_KANNADA__
                    #ifndef __ARPHIC_LAYOUTENGINE_KANNADA__
                    #define __ARPHIC_LAYOUTENGINE_KANNADA__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_ORIYA__
                    #ifndef __ARPHIC_LAYOUTENGINE_ORIYA__
                    #define __ARPHIC_LAYOUTENGINE_ORIYA__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_TIBETAN__
                    #ifndef __ARPHIC_LAYOUTENGINE_TIBETAN__
                    #define __ARPHIC_LAYOUTENGINE_TIBETAN__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_THAI__
                    #ifndef __ARPHIC_LAYOUTENGINE_THAI__
                    #define __ARPHIC_LAYOUTENGINE_THAI__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_MYANMAR__
                    #ifndef __ARPHIC_LAYOUTENGINE_MYANMAR__
                    #define __ARPHIC_LAYOUTENGINE_MYANMAR__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_KHMER__
                    #ifndef __ARPHIC_LAYOUTENGINE_KHMER__
                    #define __ARPHIC_LAYOUTENGINE_KHMER__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_LAO__
                    #ifndef __ARPHIC_LAYOUTENGINE_LAO__
                    #define __ARPHIC_LAYOUTENGINE_LAO__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_ARABIC__
                    #ifndef __ARPHIC_LAYOUTENGINE_ARABIC__
                    #define __ARPHIC_LAYOUTENGINE_ARABIC__
                    #endif
                  #endif

                  #ifdef __ARPHIC_BITMAPAPI_ARABIC_EXTEND__
                    #ifndef __ARPHIC_LAYOUTENGINE_ARABIC_EXTEND__
                    #define __ARPHIC_LAYOUTENGINE_ARABIC_EXTEND__
                    #endif
                  #endif

       /* Support Henry's Macro
          ---------------------------------------- */
       #ifdef __ARPHIC_LAYOUTENGINE_BENGALI__
           #if ( !defined (FOR_BENGALI_001) && !defined (FOR_BENGALI_002_E300))
              #define  FOR_BENGALI_001
              #define  FOR_BENGALI_002_E300
           #endif
       #else
           #if ( defined (FOR_BENGALI_001) || defined (FOR_BENGALI_002_E300))
             #ifndef   __ARPHIC_LAYOUTENGINE_BENGALI__
             #define   __ARPHIC_LAYOUTENGINE_BENGALI__
             #endif
           #endif
       #endif

       /* For convenience, if "All language" not defined, and any
           language is defined, automatically define "partial language"
          ------------------------------------------------------------------------ */
      #if  (!defined ( __ARPHIC_LAYOUTENGINE_ALLLANGUAGE__) &&  !defined ( __ARPHIC_LAYOUTENGINE_PARTIALLANGUAGE__) )
         #if   (  defined (__ARPHIC_LAYOUTENGINE_HINDI__) || defined (__ARPHIC_LAYOUTENGINE_THAI__) || defined (__ARPHIC_LAYOUTENGINE_ARABIC__) ||  defined (__ARPHIC_LAYOUTENGINE_BENGALI__)  )
            #define __ARPHIC_LAYOUTENGINE_PARTIALLANGUAGE__
         #else
            #if   (   defined (__ARPHIC_LAYOUTENGINE_TAMIL__) || defined (__ARPHIC_LAYOUTENGINE_HEBREW__) || defined (__ARPHIC_LAYOUTENGINE_SINHALA__) || defined (__ARPHIC_LAYOUTENGINE_MYANMAR__) )
              #define __ARPHIC_LAYOUTENGINE_PARTIALLANGUAGE__
            #else
              #if (   defined (__ARPHIC_LAYOUTENGINE_GURMUKHI__) || defined (__ARPHIC_LAYOUTENGINE_GUJARATI__)  ||  defined (__ARPHIC_LAYOUTENGINE_MALAYALAM__) ||  defined (__ARPHIC_LAYOUTENGINE_TIBETAN__)  )
              #define __ARPHIC_LAYOUTENGINE_PARTIALLANGUAGE__
              #else
                #if (defined (__ARPHIC_LAYOUTENGINE_TELUGU__) ||  defined (__ARPHIC_LAYOUTENGINE_KANNADA__) ||  defined (__ARPHIC_LAYOUTENGINE_ORIYA__) || defined (__ARPHIC_LAYOUTENGINE_KHMER__) )
                #define __ARPHIC_LAYOUTENGINE_PARTIALLANGUAGE__
                #else
                   #if (defined (__ARPHIC_LAYOUTENGINE_LAO__) )
                   #define __ARPHIC_LAYOUTENGINE_PARTIALLANGUAGE__
                   #endif
                #endif
              #endif
            #endif
         #endif
      #endif

      /* if no langauge is defined at all,
          enable all languages
         -------------------------------------------------------------- */
      #ifndef __ARPHIC_LAYOUTENGINE_PARTIALLANGUAGE__
      #ifndef __ARPHIC_LAYOUTENGINE_ALLLANGUAGE__
      #define __ARPHIC_LAYOUTENGINE_ALLLANGUAGE__
      #endif
      #endif

      #ifdef  __ARPHIC_LAYOUTENGINE_ALLLANGUAGE__
        #ifndef  __ARPHIC_LAYOUTENGINE_HINDI__
        #define  __ARPHIC_LAYOUTENGINE_HINDI__
        #endif
        #ifndef  __ARPHIC_LAYOUTENGINE_THAI__
        #define  __ARPHIC_LAYOUTENGINE_THAI__
        #endif
        #ifndef  __ARPHIC_LAYOUTENGINE_MYANMAR__
        #define  __ARPHIC_LAYOUTENGINE_MYANMAR__
        #endif
        #ifndef  __ARPHIC_LAYOUTENGINE_KHMER__
        #define  __ARPHIC_LAYOUTENGINE_KHMER__
        #endif
        #ifndef  __ARPHIC_LAYOUTENGINE_LAO__
        #define  __ARPHIC_LAYOUTENGINE_LAO__
        #endif
        #ifndef  __ARPHIC_LAYOUTENGINE_ARABIC__
        #define  __ARPHIC_LAYOUTENGINE_ARABIC__
        #endif
        #ifndef  __ARPHIC_LAYOUTENGINE_ARABIC_EXTEND__
        #define  __ARPHIC_LAYOUTENGINE_ARABIC_EXTEND__
        #endif
        #ifndef  __ARPHIC_LAYOUTENGINE_BENGALI__
        #define  __ARPHIC_LAYOUTENGINE_BENGALI__
            /* enable Henry's macro to avoid external font collision */
            #ifndef FOR_BENGALI_002_E300
            #define FOR_BENGALI_002_E300
            #endif
        #endif

        #ifndef  __ARPHIC_LAYOUTENGINE_TAMIL__
        #define  __ARPHIC_LAYOUTENGINE_TAMIL__
        #endif

        #ifndef  __ARPHIC_LAYOUTENGINE_SINHALA__
        #define  __ARPHIC_LAYOUTENGINE_SINHALA__
        #endif

        #ifndef  __ARPHIC_LAYOUTENGINE_GURMUKHI__
        #define  __ARPHIC_LAYOUTENGINE_GURMUKHI__
        #endif

        #ifndef  __ARPHIC_LAYOUTENGINE_GUJARATI__
        #define  __ARPHIC_LAYOUTENGINE_GUJARATI__
        #endif

        #ifndef  __ARPHIC_LAYOUTENGINE_MALAYALAM__
        #define  __ARPHIC_LAYOUTENGINE_MALAYALAM__
        #endif

        #ifndef  __ARPHIC_LAYOUTENGINE_TELUGU__
        #define  __ARPHIC_LAYOUTENGINE_TELUGU__
        #endif

        #ifndef  __ARPHIC_LAYOUTENGINE_KANNADA__
        #define  __ARPHIC_LAYOUTENGINE_KANNADA__
        #endif

        #ifndef  __ARPHIC_LAYOUTENGINE_ORIYA__
        #define  __ARPHIC_LAYOUTENGINE_ORIYA__
        #endif

        #ifndef  __ARPHIC_LAYOUTENGINE_TIBETAN__
        #define  __ARPHIC_LAYOUTENGINE_TIBETAN__
        #endif

        #ifndef  __ARPHIC_LAYOUTENGINE_HEBREW__
        #define  __ARPHIC_LAYOUTENGINE_HEBREW__
        #endif

        /* For Old Customers */
        #ifndef  __ARPHIC_BITMAPAPI_HINDI__
        #define  __ARPHIC_BITMAPAPI_HINDI__
        #endif
        #ifndef  __ARPHIC_BITMAPAPI_THAI__
        #define  __ARPHIC_BITMAPAPI_THAI__
        #endif
        #ifndef  __ARPHIC_BITMAPAPI_ARABIC__
        #define  __ARPHIC_BITMAPAPI_ARABIC__
        #endif

      #endif

      #ifdef __ARPHIC_NOARABIC__
        #ifdef  __ARPHIC_LAYOUTENGINE_ARABIC__
        #undef __ARPHIC_LAYOUTENGINE_ARABIC__
        #endif
      #endif

      #ifdef __ARPHIC_NOHINDI__
        #ifdef  __ARPHIC_LAYOUTENGINE_HINDI__
        #undef __ARPHIC_LAYOUTENGINE_HINDI__
        #endif
      #endif

      #ifdef __ARPHIC_NOTAMIL__
        #ifdef  __ARPHIC_LAYOUTENGINE_TAMIL__
        #undef __ARPHIC_LAYOUTENGINE_TAMIL__
        #endif
      #endif

      #ifdef __ARPHIC_NOSINHALA__
        #ifdef  __ARPHIC_LAYOUTENGINE_SINHALA__
        #undef __ARPHIC_LAYOUTENGINE_SINHALA__
        #endif
      #endif

      #ifdef __ARPHIC_NOGURMUKHI__
        #ifdef  __ARPHIC_LAYOUTENGINE_GURMUKHI__
        #undef __ARPHIC_LAYOUTENGINE_GURMUKHI__
        #endif
      #endif

      #ifdef __ARPHIC_NOGUJARATI__
        #ifdef  __ARPHIC_LAYOUTENGINE_GUJARATI__
        #undef __ARPHIC_LAYOUTENGINE_GUJARATI__
        #endif
      #endif

      #ifdef __ARPHIC_NOMALAYALAM__
        #ifdef  __ARPHIC_LAYOUTENGINE_MALAYALAM__
        #undef __ARPHIC_LAYOUTENGINE_MALAYALAM__
        #endif
      #endif

      #ifdef __ARPHIC_NOTELUGU__
        #ifdef  __ARPHIC_LAYOUTENGINE_TELUGU__
        #undef __ARPHIC_LAYOUTENGINE_TELUGU__
        #endif
      #endif

      #ifdef __ARPHIC_NOKANNADA__
        #ifdef  __ARPHIC_LAYOUTENGINE_KANNADA__
        #undef __ARPHIC_LAYOUTENGINE_KANNADA__
        #endif
      #endif

      #ifdef __ARPHIC_NOORIYA__
        #ifdef  __ARPHIC_LAYOUTENGINE_ORIYA__
        #undef __ARPHIC_LAYOUTENGINE_ORIYA__
        #endif
      #endif

      #ifdef __ARPHIC_NOTIBETAN__
        #ifdef  __ARPHIC_LAYOUTENGINE_TIBETAN__
        #undef __ARPHIC_LAYOUTENGINE_TIBETAN__
        #endif
      #endif

      /* derived macros
         -------------------------------- */
      #if  (  defined ( __ARPHIC_LAYOUTENGINE_ARABIC__) || defined (__ARPHIC_LAYOUTENGINE_HEBREW__) )
      #ifndef  __ARPHIC_BIDI_SUPPORT__
      #define  __ARPHIC_BIDI_SUPPORT__
      #endif
      #endif


      #if   (  defined (__ARPHIC_LAYOUTENGINE_HINDI__)   || defined (__ARPHIC_LAYOUTENGINE_GURMUKHI__)   || defined (__ARPHIC_LAYOUTENGINE_GUJARATI__)  )
        #ifndef  __ARPHIC_LAYOUTENGINE_INDIC__
        #define  __ARPHIC_LAYOUTENGINE_INDIC__
        #endif
                 /* If Independent Vowel & Consonant lays in xx04-xx39, and no near indep. vowel & cons
                    combined together, handle them as general character.
                    Never use if cross-char group operations exists (ex: CompactHindi)
                  */
        #ifndef  __ALE_INDIC_QUICK1CH__
        #define  __ALE_INDIC_QUICK1CH__
        #endif
                 /*
                     Reduce initialize operations for chargroups
                     with only mid-phase
                  */
        #ifndef  __ALE_INDIC_QUICKMID__
        #define  __ALE_INDIC_QUICKMID__
        #endif
      #endif

      /* so are following languages */
      #if  ( defined (__ARPHIC_LAYOUTENGINE_MALAYALAM__)  || defined (__ARPHIC_LAYOUTENGINE_TAMIL__) || defined (__ARPHIC_LAYOUTENGINE_TELUGU__) )
        #ifndef  __ARPHIC_LAYOUTENGINE_INDIC__
        #define  __ARPHIC_LAYOUTENGINE_INDIC__
        #endif
        #ifndef  __ALE_INDIC_QUICK1CH__
        #define  __ALE_INDIC_QUICK1CH__
        #endif
        #ifndef  __ALE_INDIC_QUICKMID__
        #define  __ALE_INDIC_QUICKMID__
        #endif
      #endif
      #if   (  defined (__ARPHIC_LAYOUTENGINE_KANNADA__) || defined (__ARPHIC_LAYOUTENGINE_ORIYA__)   )
        #ifndef  __ARPHIC_LAYOUTENGINE_INDIC__
        #define  __ARPHIC_LAYOUTENGINE_INDIC__
        #endif
        #ifndef  __ALE_INDIC_QUICK1CH__
        #define  __ALE_INDIC_QUICK1CH__
        #endif
        #ifndef  __ALE_INDIC_QUICKMID__
        #define  __ALE_INDIC_QUICKMID__
        #endif
      #endif

      #if   (defined (__ARPHIC_LAYOUTENGINE_BENGALI__))
        #ifndef  __ARPHIC_LAYOUTENGINE_INDIC__
        #define  __ARPHIC_LAYOUTENGINE_INDIC__
        #endif
      #endif



      #if   (  defined (__ARPHIC_LAYOUTENGINE_MYANMAR__) || defined (__ARPHIC_LAYOUTENGINE_SINHALA__) || defined (__ARPHIC_LAYOUTENGINE_TIBETAN__)   )
        #ifndef  __ARPHIC_LAYOUTENGINE_INDIC__
        #define  __ARPHIC_LAYOUTENGINE_INDIC__
        #endif
      #endif

      #if   (  defined (__ARPHIC_LAYOUTENGINE_KHMER__) )
        #ifndef  __ARPHIC_LAYOUTENGINE_INDIC__
        #define  __ARPHIC_LAYOUTENGINE_INDIC__
        #endif
      #endif




   /* Type. NOTE: modify with apidef.h, bitmap font system
      -------------------------------------------------------- */
   #ifndef ALE_DATATYPE
    #define ALE_DATATYPE
    #define ALE_CHAR    signed char
    #define ALE_UBYTE   unsigned char
    #define ALE_INT16   signed short
    #define ALE_UINT16  unsigned short
    #define ALE_INT32   signed long
    #define ALE_UINT32  unsigned long
   #endif



   /* Constants and Message Codes
      -------------------------------------------------------- */
    #define ALE_INNER_BIDI_BUFFER_MAXLEN 84

        /*
            NOTE: to make layout engine compatible with old customers,
             change constant with RBMP API (apidef.h)
         */
    #ifndef  ALE_SUCCESS_GETFONT
    #define ALE_SUCCESS_GETFONT    111
    #endif

    #define ALE_ERROR_NOFONT       -201
    #define ALE_ERROR_CODETYPE     -202
    #define ALE_ERROR_CODE         -203
    #define ALE_ERROR_FONTSIZE     -204
    #define ALE_ERROR_WORKBUFFER   -205
    #define ALE_ERROR_MAPTABLE     -206

    #define ALE_ERROR_BIDI_INSUFFICIENT_BUFFER -209
    #define ALE_ERROR_BIDI_TYPE_NUMBER  -210
    #define ALE_ERROR_BIDI_UNSUPPORTED -211
    #define ALE_ERROR_DATATYPE  -212
    #define ALE_ERROR_WORKBUFFER_32BITALIGN -215


    /* keep old error message code available*/
    #ifndef  SUCCESS_GETFONT
    #define SUCCESS_GETFONT    ALE_SUCCESS_GETFONT
    #endif
    #ifndef ERROR_BIDI_INSUFFICIENT_BUFFER
    #define ERROR_BIDI_INSUFFICIENT_BUFFER ALE_ERROR_BIDI_INSUFFICIENT_BUFFER
    #endif


      /* new error code start from -230 */
    #define ALE_ERROR_GETFONT  -230
    #define ALE_NOT_SUPPORTED   -231
    #define ALE_ILLEGAL_START   -232
    #define ALE_ILLEGAL_BUFFERSIZE   -233
    #define ALE_MISSING_CHAR  -234



   /* Data Structure
      -------------------------------------------------------- */
     typedef struct _AleFontMetrics
     {
         ALE_INT16   outBufWidth;
         ALE_INT16   outBufHeight;
         ALE_INT16   Ascender;
         ALE_INT16   OriginX;
         ALE_INT16   horiAdvance;

         /* for Hindi or other languages */
         ALE_INT16 Extend1;
         ALE_INT16 Extend2;

         ALE_INT16 Padding; /* make structure is 32-bit alignment */

     } AleFontMetrics;



                typedef struct _AleKernPairIndexType
                 {
                    ALE_UINT16  PrevChar, CurrChar;
                         /* WARNING: you may need to reverse byte order  */
                 } AleKernPairIndexType;

                typedef struct _AleKerningHeaderType
                 {
                   /* CAUTION:
                       1.Kerning Data may be burned in ROM,
                         so do not try to modify its contents.

                       2.Remember to check byte order yourself,
                         You may need to reverse byte order!
                    */

                   ALE_UINT32 CheckCode;
                   ALE_UINT32 TotalSize; /* total size of kerning data, including this header */
                   ALE_UINT32 Flag;
                   ALE_INT32 KernTotal;

                    /* Followed by IndexTable & XTable.

                        AleKernPairIndexType IndexTable [KernTotal];
                        ALE_CHAR XTable [KernTotal];

                     */

                 } AleKerningHeaderType;




#ifdef __cplusplus
extern "C"
 {
#endif

         /* Font Driver Interface
            -------------------------------------------------------- */
         typedef struct _AleFontDriverInterface
          {
             ALE_INT32 (*AleGetGlyphIndex) (ALE_UINT16 ucode, char *WorkBuf);
                                   /*
                                       Given an Unicode ucode, get its glyph index;
                                       return -1 if glyph not available
                                    */

             ALE_INT16 (*AleGetFont) (ALE_INT16 tcodetype, ALE_UINT16 charCod,
                                         char *tFontBuf, AleFontMetrics *fm0, char *WorkBuf);
                                    /*
                                        tcodetype = 1 means unicode
                                        charCode: Unicode of Char
                                        tFontBuf: font buffer, may be NULL if only metrics needed
                                        fm0: structure to receive metrics of this font
                                     */


             void (*AleCalculateBufferSizeInPixel) (ALE_INT16 ABufferRowByteTotal, ALE_INT16 ABufferColumnByteTotal,
                                           ALE_INT32 *x, ALE_INT32 *y, char *WorkBuf);
                                    /*
                                         given buffer of ABufferRowByteTotal * ABufferColumnByteTotal (bytes)
                                         get its size in pixels and put in *x & *y
                                     */

             void (*AleResetFontBuffer) (char *tFontBuf,  ALE_INT16 ABufferRowByteTotal,
                                ALE_INT16 ABufferColumnByteTotal,  ALE_INT32 AAct, char *WorkBuf);


             #define ALE_ACCESSFONTDRV_WIDTHBBOX 1
             #define ALE_ACCESSFONTDRV_HEIGHTBBOX 2
             #define ALE_ACCESSFONTDRV_SETFONT 3

             #define ALE_ACCESSFONTDRV_NEGATIVE_START_OK  4
                           /* return 1 if negative start x/y is accepted */

             ALE_INT32 (*AleAccessFontDriver) (ALE_INT32 AAccessType, void *AData, char *WorkBuf);
                                    /*
                                        Get Information about font.
                                        For any AAccessType not supported, 0 should be returned.
                                     */


             ALE_UBYTE* (*AleGetCharFontCache) (char *WorkBuf);
                                   /*
                                        return a cache for character font access. You can provide NULL if none.
                                        If you provide, it must be able to contain any characters of current size and
                                        grayscale.

                                        When layout engine is rendering, it will send this cache to (*AleGetFont) ()
                                           (parameter tFontBuf) when retrieve char's metrics, and then, it will send
                                           this cache later to following (*AleDrawCharOnBuffer) () (parameter tCharFontBuf)

                                         In general, font driver prepare character's font and metrics together.

                                         Since Llayout engine needs font driver to calculate character's metrics first, and
                                         then layout engine request font driver to draw this character on some place
                                         in the buffer, if you provide this cache, the font driver may reduce some
                                         effort.
                                     */


             ALE_INT32 (*AleDrawCharOnBuffer) (char *tFontBuf, ALE_INT16 ABufferRowByteTotal, ALE_INT16 ABufferColumnByteTotal,
                                          ALE_INT16 tcodetype, ALE_UINT16 charCod,
                                          char *tCharFontBuf, AleFontMetrics *charfm,
                                          ALE_INT32 xstart, ALE_INT32 ystart, ALE_INT32 xlimit, ALE_INT32 ylimit,
                                          ALE_INT32 need_or, ALE_INT32 rightcut, char *WorkBuf);
                                     /*
                                         Draw a character on a give buffer.

                                         tFontBuf: buffer to be drawn
                                         ABufferRowByteTotal, ABufferColumnByteTotal: row/column size of buffer in bytes

                                         tcodeType, charCod: code of character, if tcodetype = 1, charCod is char's unicode,
                                                         see AleGetFont ()
                                         tCharFontBuf: if not NULL, it contains the font data of this character obtained
                                                      via AleGetFont ().
                                              tCharFontBuf may be 3 values:
                                                 1. NULL: you have to prepare this character's font yourself
                                                 2. the return value of (*AleGetCharFontCache)()
                                                 3. if user call AleGetStringFont () with tCharFontBuf != NULL,
                                                     tCharFontBuf here  will be user's tCharFontBuf
                                              In case 2 & 3, tCharFonBuf will contain the returned font by
                                                 (*AleGetFont)(), so you may use this for rendering directly instead
                                                 of retrieving font again.

                                          charfm: metrics of this char
                                          xstart, ystart:  up-left corner of this character
                                          xlimit, ylimit: size of tFontBuf in pixels
                                          need_or: always use "OR" for drawning this font, because some character
                                                   may overlap other characters.

                                          rightcut: the char may not be totally displayed; right part may be clipped

                                         return: 1-success, 0-failed, -1:right part clipped
                                      */


             ALE_INT32 (*AleGetFontMetricsExt1) (ALE_UINT16 ucode, char *WorkBuf);
                                   /*
                                      Get metrcs Ext1 for char with Unicode = ucode
                                      (for alebenga.c)
                                    */

             AleKerningHeaderType * (*AleGetDefaultKerningData) (char *ABuffer, ALE_INT32 *ASize, char *WorkBuf);
                                   /*
                                       Return the default kerning data of current font.

                                       If no such kerning data, or if it is not in memory, NULL is returned.

                                       When return, *ASize will be the size of kerning data,
                                         whether it is returned or not.

                                       If ABuffer is given, it is used to load the kerning data.
                                       *ASize will be set to the entire data size of this data. If ABuffer
                                         is not NULL, you should set *ASize to the size of ABuffer []
                                         when calling this function.
                                    */

             ALE_INT32 (*AleKerningToRealOffset) (ALE_INT32 x, char *WorkBuf);
                                  /*
                                     Convert offset in XTable [] of kerning data (in parameter x) to
                                     real offset on screen (in pixels) and return the real offset.
                                  */

             #define ALE_DRVINFO_SUPPORT_HORIADV_CLIP  1
             #define ALE_DRVINFO_SUPPORT_PARTIAL_CHAR  2
             #define ALE_DRVINFO_DEFAULT_RIGHTCLIP_MODE  3
             #define ALE_DRVINFO_ZEROADV_LOOSECLIP   4
             #define ALE_DRVINFO_DEFAULT_COMPACT_HINDI   5

             ALE_INT32 (*AleQueryDriverInfo) (ALE_INT32 AType, ALE_INT32 APara, char *WorkBuf);
                       /*
                          AType
                            ALE_DRIVERINFO_SUPPORT_HORIADV_CLIP
                               return 1-support display character in a buffer of width == char's horizontal advance
                                 0-do not support
                            ALE_DRIVERINFO_SUPPORT_PARTIAL_CHAR
                                 return 1-support display character in a buffer of width < char's horizontal advance
                                 0-do not support
                            ALE_DRVINFO_DEFAULT_RIGHTCLIP_MODE
                                return default right-clipping mode
                            ALE_DRVINFO_ZEROADV_LOOSECLIP
                                return 1 to display characters with zero advance and
                                            is just out of boundary (the next column after right-most column)
                                   0-otherwise
                            ALE_DRVINFO_DEFAULT_COMPACT_HINDI
                                return 1 if ALE_RNDO_CompactHindi should be started by default
                        */


              /* NOTE: if you want to add more functions, add
                 default function at AleSetFontDriver () to
                 avoid old-version users do not provide
                 new interfaces.
               */



             /* Data used for user-designed version of font driver */
             void *ExtendData;


          } AleFontDriverInterface;



   /* Initialization
      -------------------------------------------------------- */
   ALE_INT32 AleGetWorkBufferSize (void);  /* return work buffer size*/

   ALE_INT16 AleReset (char *AWorkBuf, ALE_UINT16 bufSize,
                                  AleFontDriverInterface *AFontDriver,
                                  char *AFontDriverWorkBuf);

   ALE_INT16 AleSetFontDriver (AleFontDriverInterface *AFontDriver,
                                  char *AFontDriverWorkBuf, char *WorkBuf);
   ALE_INT16 AleSetFontDriverWorkBuffer (char *AFontDriverWorkBuf, char *WorkBuf);
                /*
                    NOTE: if you start layout engine NOT via RBMP API RbmpReset (),
                     and you want to use old RBMP's layout engine API
                        (such as RbmpGetStringFont ())
                     Call RbmpSetAleWorkBuffer  (curent layout engine's working buffer)
                        so they (old API) can access correct working buffer.
                 */

   ALE_INT16 AleGetFontDriver (AleFontDriverInterface **AFontDriver,
                                  char **AFontDriverWorkBuf, char *WorkBuf);

   char *AleGetFontDriverWorkBuffer (char *WorkBuf);


   ALE_INT16 AleSetFontDriverExtendData (void *AData, char *WorkBuf);
   void *AleGetFontDriverExtendData (char *WorkBuf);



   /* Font Operations
      -------------------------------------------------------- */



       /*
         Provide layout engine info to retrieve font of an entire string
         via this structure.

         To make your code compatible with future versions, we suggest
         you to reset the entire structure to zero by

           memset (&YourStructure, 0, sizeof (YourStructure));

         before setting any member.
        */
       typedef struct _AleGetStringFontInfo
        {
           /* Input
              ------------------------ */
           ALE_INT16 CodeType;
                       /* code type, 0-current language, 1-Unicode, 2-GlyphIndex
                           NOTE: for some languages, only Unicode is supported
                        */

           ALE_INT16 CharSpace;
                          /*
                            space (# of pixels) between each character.
                            Only support English and CJK;
                            do not support Indic/Arabic script or other complex ligature.
                            generally, set it to zero.

                             (Move this field after CodeType for 32-bit padding problem)
                           */

           ALE_UINT16 *String;
                       /* string to display, must add one element of zero at end */

           char *FontBuffer;
                         /* bitmap buffer to receive font. if you send NULL, font will
                            not be returned, only metrics is returned.
                          */

           ALE_INT16 BufferRowByteTotal;
                          /* # of bytes of a line(row) in above tFontBuf */

           ALE_INT16 BufferColumnByteTotal;
                          /* # of bytes of a column in above tFontBuf */

           AleFontMetrics *FontMetrics;
                          /* point to a AleFontMetrics structure to receive metrics
                             of this string */

           char *CharFontBuffer;
                          /*
                             buffer for retreiving font of a single character
                             when rendering by layout engine.
                             generally this is not needed, set this to NULL
                           */

           ALE_UINT16 *CharPosition;
                           /*
                             if you need to know the position of each character
                              when renderred, send an array here.
                             otherwise, just give NULL.
                            */

           ALE_INT16 DoNotClearBuffer;
                            /*
                               set to zero if you want layout engine to clear
                               buffer (tFontBuf) before rendering;
                               set to 1 if you do not want this.
                             */

           ALE_INT16 StartX, StartY;
                           /*
                              Position of upper-left corner of the rectangle area where
                              the string is renderred in tFontBuf.
                              generally, set both to zero.
                              NOTE: you can not give negative values.
                            */

           /* Output
              ------------------------ */
            ALE_INT16 HorizontalClipped;
                            /*
                                If not zero, renderred string is horizontally clipped because
                                   of insufficient buffer width. Zero if no such clipping occurred.
                                The returned value is # of character first clipped.
                                Ex: return 5 means the 5th character (and the remaining string)
                                  is clipped. So only 4 characters are rendered (i.e. AString[0]...AString [3])
                                This value is the same as the returned value of
                                  AleLasOutputStringClipped ().
                             */

            ALE_INT16 VerticalClipped;
                            /*
                                If not zero, renderred string is vertically clipped because
                                   of insufficient buffer height.  Zero if no such clipping occurred.
                             */

            ALE_INT16 Padding; /* make structure is 32-bit alignment */

        } AleGetStringFontInfo;

   ALE_INT16 AleGetStringFont (AleGetStringFontInfo *AInfo, char *WorkBuf);
                              /*
                                 AInfo: all information of retrieving font of an entire string.

                                 return:
                                   ALE_SUCCESS_GETFONT: ok
                                         (note: check clipping yourself)
                                   ERROR_BIDI_INSUFFICIENT_BUFFER
                                         bi-directional buffer insufficient
                                   ALE_ILLEGAL_START
                                         positon of startx/y is out of buffer area


                                 NOTE: to support Arabic:
                                   1. remember to active BiDirecition Text algorithm
                                       by AleSetTextDirection ()

                                   2. if your Unicode string will be longer than
                                      ALE_INNER_BIDI_BUFFER_MAXLEN
                                      please given re-order buffer by
                                      SetBiDiReorderBuffer (),
                                      otherwise ERROR_BIDI_INSUFFICIENT_BUFFER
                                      will be returned.

                                   3. you can use AleLasOutputStringClipped ()
                                      to see if your string is too ALE_INT32 for the buffer.
                               */

         /* convenient version for above function (with DoNotClearBuffer = StartX = StartY = 0) */
         ALE_INT16 AleGetStringFont0 (ALE_INT16 tcodetype, ALE_UINT16 *AString,
                                      char *tFontBuf,
                                      ALE_INT16 ABufferRowByteTotal, ALE_INT16 ABufferColumnByteTotal,
                                      AleFontMetrics *fm0,
                                      char *tCharFontBuf,  ALE_INT32 ACharSpace,
                                      ALE_UINT16 *ACharPosition,
                                      char *WorkBuf);



     ALE_INT32 AleLastOutputStringClipped (char *WorkBuf);
                              /*
                                   if last string sent to AleGetStringFont () is too long for
                                    buffer, it returns the order of character clipped
                                     (1 means displayed 0 chars, cut at 1st char
                                      2 means displayed 1 characters, cut at 2nd char...etc)
                                    otherwise it returns 0
                               */

     ALE_INT16 AleGetFont (ALE_INT16 tcodetype, ALE_UINT16 charCod,
                                         char *tFontBuf, AleFontMetrics *fm0, char *WorkBuf);

   /* Bi-Direction Support
      -------------------------------- */
   #define ALE_TEXTDIR_DEFAULT  0
   #define ALE_TEXTDIR_ENGLISH_MAJOR 1
   #define ALE_TEXTDIR_ARABIC_MAJOR 2
   #define ALE_TEXTDIR_ARABIC_SMART 3
   #define ALE_TEXTDIR_ARABIC_FIRSTCHAR 4

   ALE_INT16 AleSetTextDirection (ALE_INT16 type, char *WorkBuf);
                              /*
                                  type:
                                     ALE_TEXTDIR_DEFAULT (0, default): Always Left-to-right, no right-to-left
                                     ALE_TEXTDIR_ENGLISH_MAJOR (1): default left-to-right; right-to-left for Arabic
                                     ALE_TEXTDIR_ARABIC_MAJOR (2): default right-to-left, left-to-right for English
                                     ALE_TEXTDIR_ARABIC_SMART (3): default right-to-left, left-to-right for English;
                                         If no right-to-left language in text, all line is left-to-right.

                                  set type to 1-3 if you use right-to-left text
                               */
   ALE_INT16 AleGetTextDirection (char *WorkBuf); /* return current setting of text direction */
   ALE_INT16 AleIsUsingArabicTextDirection (char *WorkBuf);
                /*  return 1 if text direction is ALE_TEXTDIR_ARABIC_MAJOR or
                    ALE_TEXTDIR_ARABIC_SMART; 0 otherwise
                  */

   ALE_UINT16 *AleGetLastBiDiReorderBuffer (char *WorkBuf);
                              /*
                                 Get last AleGetStringFont ()'s display string
                                   NULL: no re-order occurred or insufficient reorder buffer
                                   non-NULL: the returned buffer contains rendered
                                      string (ended by zero) and then the original
                                      order (1 means originally the first char)
                               */

   void AleSetBiDiReorderBuffer (ALE_UINT16 *ABuffer, ALE_INT32 ABufferSize, char *WorkBuf);
                        /*
                            buffer size should be >=
                              (max string length + 1) * 3 * sizeof (ALE_UINT16)
                            give ABuffer = NULL means using internal buffer
                         */

   /* Cursor Operation Support

       Please use these functions immediately after
       AleGetStringFont ()
      ------------------------------------------------ */
   ALE_INT32 AleGetCharIndex (ALE_INT32 x, ALE_UINT16 *ALastCharPosition, char *WorkBuf);
             /*
                  Get the index of character at horizontal position x for last time you call
                   AleGetStringFont ().

                  return value: the order of character where x is on.
                   1 means x is on the first character (i.e. AString [0])
                   2 means x is on the second (i.e. AString [1])
                   ....etc.
                   0 means not on any character.

                  ALastCharacterPosition: returned ACharPos []
                        last time you call AleGetStringFont () (cannot be NULL)

                  NOTE: please use this function immediately after calling
                    AleGetStringFont ()
              */

   ALE_INT32 AleGetDisplayOrder (ALE_INT32 index, char *WorkBuf);
             /*
                 Get the display order of the (index)th character last time
                   AleGetStringFont () is called.

                 return: order: 1 means the first, 2 means the second...etc.
                 NOTE: if index is out of bound, 0 is returned.

                 in general, the returned value is index. However,
                 when Arabic or BiDirection text renderred,
                 the returned value may be different.

              */

   ALE_INT32 AleGetDisplayDirection (ALE_INT32 index, char *WorkBuf);
              /*
                 Get the display direction of the (index)th character last time
                   AleGetStringFont () is called.

                 return:  "Even number" (including 0) means this character
                   is displayed in left-to-right order;
                   "Odd number" means this character is displayed in
                   "right-to-left" order.
                 Note: if index is out of range, current base text direction
                 is used for judge.
               */

   ALE_INT32 AleGetDisplayLeft  (ALE_INT32 index, ALE_UINT16 *ALastCharPosition, char *WorkBuf);
   ALE_INT32 AleGetDisplayRight  (ALE_INT32 index, ALE_UINT16 *ALastCharPosition, char *WorkBuf);
             /*
                 Get the horizontal display boundary (left/right)
                   of the (index)th character in last time
                   AleGetStringFont () is called.
                   i.e. AString [index-1] when calling AleGetStringFont ()

                 NOTE
                        "left" boundary is at the first pixel column of this character,
                    while "right" boundary is at the first pixel column of next character.

                 return -1 if out of range.
              */

   ALE_INT32 AleGetCursorPrevIndex (ALE_INT32 index, ALE_UINT16 *ALastCharPosition, char *WorkBuf);
   ALE_INT32 AleGetCursorNextIndex (ALE_INT32 index, ALE_UINT16 *ALastCharPosition, char *WorkBuf);
             /*
                 when cursor is on the index(th) character,
                  (i.e. AString [index-1] when last time ecalling
                    AleGetStringFont ())
                  which character should be skipped to when
                  moving cursor previously or next.

                 return: 1 means the first character,
                   2 means the second...etc

                 you can send returned value to AleGetDisplayLeft ()
                 to get new cursor position.
              */

    ALE_INT32 AleSetLastRenderedStringLength (ALE_INT32 ANewLength, char *WorkBuf);
            /*
                Set LastRenderedStringLength record in working buffer.

                In general, you send the char position array generated by AleGetStringFont ()
                directly to above API functions (parameter ACharPosition []). However, if you
                want to use ALastCharPosition [] array calculated by yourself
                 on above API functions, set related string length by this function before calling them.

                For example, you may display a string of 20 characters in different sizes
                by calling AleGetStringFont () several times for different segments,
                and then you calculated a char position array of 20 characters
                yourself. To use this array for above API functions, you have to
                use AleSetLastRenderedStringLength () in advance like this:

                AleSetLastRenderedStringLength (20, <working buffer>);
                index = AleGetCharIndex (x, <char position array calculated by yourself>, <working buffer>);

                return: 0 on success; non-zero if failed.

                NOTE: if you use bi-directional text such as Arabic, be sure the
                Bi-direcitonal text reordering buffer matchs the char position
                array generated by yourself.
            */

    ALE_INT32 AleGetLastRenderedStringLength (char *WorkBuf);
            /* return string length of last renderred string */

    /* Other Display Control
       -------------------------------- */
    ALE_INT16 AleSetTab (ALE_UINT16 tabval, char *WorkBuf);
              /*
                   Set TAB width = tabval,
                   0 means do not support TAB (this is the default setting)
               */


    #define ALE_DEFAULTCHAR_NONE 0
    #define ALE_DEFAULTCHAR_SPACE  0xFFFF
    #define ALE_DEFAULTCHAR_STOP   0xFFFE

    ALE_INT32 AleSetDefaultChar (ALE_UINT16 charcode, char *WorkBuf);
                  /*
                       Set default character code
                          (character displayed by AleGetStringFont () when request character
                            is not available, i.e. missing character)

                       The code may be in Unicode or glyph index, depends on code type given to
                          AleGetStringFont ().

                       Three special codes can be given:
                         ALE_DEFAULTCHAR_NONE   ignore the missing char, do not display anything
                                                            (this is the default setting)
                         ALE_DEFAULTCHAR_SPACE  left a proper space for missing char
                         ALE_DEFAULTCHAR_STOP   just stop to display and return, ignore all
                                                          remaining characters.
                                                          AleGetStringFont () will return
                                                          ALE_MISSING_CHAR in this condition.

                         return 0 on success.
                   */


      #define ALE_RIGHTCLIP_SAFE   0
      #define ALE_RIGHTCLIP_HORIADV    1
      #define ALE_RIGHTCLIP_DISPLAYALL  2
            /* NOTE: keep above value in serial; otherwise, modify AleSetRightClippingMode () */

      ALE_INT16 AleSetRightClippingMode (ALE_INT16 AMode, char *WorkBuf);
                       /*
                           Set Right-Clipping Mode: How Layout Engine stop rendering
                           when bitmap buffer's width is insufficient for the whole string.

                           ALE_RIGHTCLIP_SAFE
                             Stop rendering when remaining width < maximum possible
                             character width (ex: 16 for 16x16 bitmap font). This mode
                             guarantees all displayed characters are not clipped at all, but
                             some extra space will be left at buffer's right side.

                           ALE_RIGHTCLIP_HORIADV
                             Stop rendering when remaining width < character's
                             horizontal advance. This mode is better in buffer usage.
                             However, some special characters in some languages
                             may have glyph beyond its horizontal advance, and
                             these parts may be clipped at buffer's right side.
                             NOTE: some font engine may not support this mode.

                           ALE_RIGHTCLIP_DISPLAYALL
                             Stop rendering when remaining width is zero, i.e.
                             try to display characters as many as possible, even
                             if they can only be partially displayed.
                             NOTE: some font engine may not support this mode.

                           If you want to display Arabic right-aligned, you
                           should try ALE_RIGHTCLIP_HORIADV or
                           ALE_RIGHTCLIP_DISPLAYALL.

                           Return:
                             1-success
                             0-illegal mode, or mode not supported by font engine
                        */
      ALE_INT16 AleGetRightClippingMode (char *WorkBuf);


      /* Bi-Directional Text Control
         ------------------------------------------------ */
      ALE_UINT16 *AleBiDiReOrder
             (ALE_UINT16 *AString, ALE_UINT16 *ABuffer,
              ALE_INT32 ABaseLevel,  /*  -1 means decide by program */
              ALE_INT32 AReOrderOption,
              ALE_INT32 AMaxStringLength,
              char *WorkBuf);

      ALE_UINT16 *AleBiDiReOrder2
                  (ALE_UINT16 *AString, ALE_UINT16 *ABuffer,
                   ALE_INT32 ABaseLevel,  /* -1 means decide by program */
                   ALE_INT32 AMaxStringLength, char *WorkBuf);

       #define ALE_REORDER_ONLY_NECESSARY 1
       #define ALE_REORDER_MARK_BEFORE_CHAR  2
          /*
               Input:
                 *AString: the original Unicode string
                 ABaseLevel:  0:default text direction is left-to-right (majorly English)
                   1:default is right-to-left (majorly Arabic)
                   -1: decide by first English or Arabic character (if none, left-to-right is selected)
                   (NOTE: this is different from AleSetTextDirection ()'s parameter "type")

                 AReOrderOption: bitmask combination of following flags.
                       (For AleBiDiReOrder2, there is no such parameter, so 0 is assumed,
                       i.e. the following flags are not given)
                    ALE_REORDER_ONLY_NECESSARY
                       if set and no right-to-left text exists, re-order will not be performed
                       even if baselevel is right-to-left. (For AleBiDiReOrder2, there is no
                       such parameter, so reordering is always performed)
                    ALE_REORDER_MARK_BEFORE_CHAR
                       Put Arabic's combination marks (ex: U+0651) BEFORE the character
                       it modified. (Otherwise, this function will put marks AFTER the
                       character it modified.) Only use this flag if you want to display
                       reordered string yourself instead of calling AleGetStringFont (),
                       and you do know the difference.

                 AMaxStringLength: max possible length of *AString.
                 ABuffer []: a buffer to contain the result
                   NOTE: size of ABuffer[] must >= (AMaxStringLength+1) * 3

               Output:
                 *ABuffer: the reorderred string with Arabic characters replaced by
                  proper characters in Arabic presentation form A or B.
                  (NOTE: If no Arabic in AString, do not use data inside *ABuffer)

               Return value:
                 *AString itself: no re-ordering is necessary (and *ABuffer will be set to null-string!)
                 *ABuffer: the reordered string
                  NULL: error: the string needs to be reordered,
                            but the reorder buffer (*ABuffer) is insufficient: a larger buffer is necessary.


           */


      void AleSetBiDiBorderJoinInArabic (ALE_UINT16 CharBeforeBegin, ALE_UINT16 CharAfterEnd, char *WorkBuf);
                    /*
                       NOTE: AleLineClippingCheck () and AleGetStringFontInBlock ()
                         will use it to change setting.
                     */

      void AleSetRTLLigatureToPostCharPos (ALE_UINT16 *ACharPosition, char *WorkBuf);
      ALE_INT32 AleGetLigatureHeadDisplayPos (ALE_INT32 displaystart, ALE_UINT16 *ACharPosition, char *WorkBuf);

      ALE_INT16 AleGetTextDirectionByFirstChar (ALE_UINT16 *AString,  char *WorkBuf);
                     /*
                         Decide text direction by first "strong type character",
                            i.e. character with obvious direction, such as English or Arabic.
                         Return:  1-Left to Right, 2-Right to Left.
                         If no strong type character is found, current TextDirection
                          will be used to make decision:
                            If TextDirection <= 1: return 1.
                            otherwise: return 2.
                      */

   /* Language-Specific Support
      ------------------------------------------------ */
   ALE_INT16 AleEnableThaiCharGroup (ALE_INT32 enabled, char *WorkBuf);
                         /*
                             Enable/Disable Thai's Character Group in AleGetStringFont ().
                               (default is disabled).

                             If this is enabled, AleGetStringFont () will make revise for
                             Thai in CharPosition [] array so that consonants and vowels
                             consisting multiple Unicode characters will be treated
                             as one ligature.
                             This setting has no effect on renderred string, but
                             will make cursor operation function more correct
                             for Thai.

                             enabled:1 means enabled, 0 means disabled

                             return: 0-set success
                             ALE_NOT_SUPPORTED: Thai not supported
                          */

   ALE_UINT16 *TryToFindNextThaiCharGroup (ALE_UINT16 *start, char *WordBuf);
                          /*
                             Try to find the first character group from string
                              pointed by *start.

                             return:
                                non-NULL: address of the character immediately
                                  follow the first character group of start
                                  i.e. where next character group starts.
                                NULL: start is not pointed to a Thai character,
                                   or Thai not supported.
                           */



                         /* Rendering Flags for following function
                            ------------------------------------------------ */
                         #define ALE_RNDO_AdvanceCharGroupEnabled         1
                         #define ALE_RNDO_SinhalaAutoCombine           2
                         #define ALE_RNDO_FirstCharNoZeroWidth         4
                         #define ALE_RNDO_CompactHindi                 8
                         #define ALE_RNDO_CharSpaceBiasEnabled       0x10
                         #define ALE_RNDO_DisableKerningFromFont     0x20
                         #define ALE_RNDO_DisableCommonCaseOptimize         0x40
                         #define ALE_RNDO_DisableCharGroupDictionary         0x80
                         #define ALE_RNDO_EnableArabicLigature  0x100
                         #define ALE_RNDO_CharGroupDictionaryFirst   0x200
                         #define ALE_RNDO_LimitRightBoundary  0x400

                         /* for compatibility of old code */
                         #define ALE_RNDO_ThaiCharGroupEnabled         ALE_RNDO_AdvanceCharGroupEnabled

   ALE_INT16 AleSetRenderOption (ALE_UINT32 option, ALE_INT32 enabled, char *WorkBuf);
                          /*
                             Set Rendering Options.

                             option:
                               ALE_RNDO_AdvancedCharGroupEnabled
                                  enable Thai & Myanmar character group detection.
                                  (setting this option is the same as calling
                                   AleEnableThaiCharGroup ())
                                  default: disabled

                               ALE_RNDO_SinhalaAutoCombine
                                  Generally, you need to add ZWJ to Unicode string to
                                  make characters combined into ligatures or change
                                  forms (such as Ra or Ya).  If this is enabled,
                                  ZWJ will not be necessary. However, you can still
                                  disable the combination by inserting ZWNJ.
                                  default: disabled

                               ALE_RNDO_FirstCharNoZeroWidth
                                  If this is enabled, layout engine will always check if the
                                   level of adjacent vowels/tonemarks are conflict, the
                                   last one of the conflict vowel/tonemark would be
                                   rendered independently with maximum character width.
                                   NOTE: the option is only available when displaying some
                                   scripts such as Thai, and the returned character
                                   position information will be incorrect. You should
                                   not use returned character position information and
                                   cursor-related APIs such as AleGetCharIndex () for
                                   rendering result.

                               ALE_RNDO_CompactHindi
                                  If this is enabled, layout engine will try to overlap
                                  Hindi characters by metrics Extend2 to make words
                                  more compact.
                                  default: bitmapfont-disabled, MobileFont-enabled

                               ALE_RNDO_CharSpaceBiasEnabled
                                  This option is for internal use.

                               ALE_RNDO_DisableKerningFromFont
                                  If this is enabled, kerning setting inside font data
                                  will not be enabled automatically. This is used
                                  when you want to provide kerning data yourself.

                               ALE_RNDO_EnableArabicLigature
                                  enable Arabic Form-A ligatures

                               ALE_RNDO_LimitRightBoundary
                                  This option is for internal use

                             enabled:1 means enabled, 0 means disabled
                                (all options' default settings are disabled)

                             return: 0-set success
                             ALE_NOT_SUPPORTED: option not supported

                           */

   ALE_UINT32 AleGetRenderOption (ALE_UINT32 mask, char *WorkBuf);
                          /*
                             Get current render option.
                               mask:0- get OR combination of all options
                                  non-zero: get only option indicated by mask
                           */


      /* Extension
         ------------------------------------------------------------- */

                                typedef struct _AleExtension
                                 {
                                    /* Information from AleGetStringFont ()
                                         (will be set by AleGetStringFont())
                                        ------------------------------------------------ */
                                    char *WorkBuf;

                                    AleGetStringFontInfo *StringInfo;
                                    ALE_UINT16 *DisplayString;  /* the string displayed */
                                    ALE_INT32 xstart;
                                    ALE_INT32 lineheight;


                                    /* Information from AleGetStringFontInBlock ()
                                       (will be set by AleGetStringFontInBlock())
                                        ------------------------------------------------------- */
                                    AleGetStringFontInfo *BlockStringInfo;
                                    void *BlockBlockInfo;  /* AleGetStringFontInBlockInfo */
                                          /* If these fields are non-NULL, AleGetStringFontInBlock ()
                                               is in process.
                                           */
                                    ALE_INT32 BlockLineCount;
                                        /* this line is the ?th of lines (0~) on screen  */

                                    ALE_INT32 BlockLineHeight;
                                        /* current height of this line */

                                    ALE_INT32 BlockHeightSum;
                                        /* sum of heights of lines already displayed */

                                    ALE_INT32 BlockYLimit;
                                        /* all pixels output should < BlockYLimit. */

                                    /* Following are pointers to call back functions.
                                        Please set them yourself before using this structure.
                                        set to NULL if not available.
                                     */

                                    /* Callback Functions
                                          (invoked by AleGetStringFont())
                                        ------------------------------------------------ */
                                    ALE_INT32 (*CalculateLineHeight) (struct _AleExtension *AExtension);
                                            /* invoked at beginning of line (in order to union char height) */

                                    ALE_UINT16 (*CheckBeforeChar)
                                               (ALE_UINT16 *p,  ALE_INT32 *ybias,
                                                           ALE_INT32 *wordlen, ALE_INT32 *horiadvance,
                                                           struct _AleExtension *AExtension);
                                            /* check if string at *p (& p[1], p [2]...) should be replaced.
                                                Return:
                                                 0: *p and following characters do not need to be replaced
                                                 0xFFFF: need to be replaced, total *wordlen characters (p[0]..p[wordlen-1])
                                                   do not display it. just move *horiadvance pixels right.
                                                   (the function can display as image or others directly here)
                                                 other value: need to be replaced, total *wordlen characters;
                                                   return value is the Unicode to be displayed

                                                 *ybias: set this value to the y position move of this character if
                                                   return value is not 0xFFFF
                                             */
                                    void *CheckBeforeCharInfo;

                                    /* Callback Functions
                                          (invoked by AleGetStringFontInBlock ())

                                           For each line, (*BlockModifyLineWidth)() will first be called for a
                                           new line. This function may be called several times with different
                                           line height with (*BlockModifyLineHeight) ().

                                           After that, (*BlockModifyLinePosition) () will be called to modify
                                           the line position.

                                          CAUTION!
                                          you must be sure the modification
                                          made by following callback functions will not
                                          make the result display out of screen or
                                          even out of buffer!
                                          -------------------------------------------------------- */
                                    ALE_INT32 (*BlockModifyLineWidth)  (ALE_INT32 ANewLine,
                                                           ALE_INT32 *ALineWidth, struct _AleExtension *AExtension);
                                                    /*

                                                         modify *ALineWidth for current line
                                                         return 1:modified, 0:not,
                                                               -1 if display should be aborted.

                                                          ANewLine: if non-zero, this is a new line;
                                                          if zero, we just re-calculate current line (possibly with
                                                            line height changed)

                                                        NOTE: if line position is modified, always
                                                           return 1 even if line width is not modified.
                                                           otherwise position modification will not be taken.
                                                    */

                                    ALE_INT32 (*BlockModifyLineHeight) (ALE_UINT16 *ALine,
                                                ALE_INT32 *ALineHeight, struct _AleExtension *AExtension);
                                                    /*
                                                          Modify current line's height in *ALineHeight (CANNOT SHRINK)
                                                          return 1: modified. 0:not.

                                                          Flag ALE_BLOCKFLAG_DYNAMIC_LINE_HEIGHT must be set
                                                          when calling AleGetStringFontInBlock () (ABlockInfo-> Flag).
                                                          Otherwise, this function is ignored.

                                                          NOTE: this function may be called repeatly for diffrent length of *ALine.

                                                     */

                                    ALE_INT32 (*BlockModifyLinePosition)
                                        (ALE_INT16 *xbias, ALE_INT16 *ybias, struct _AleExtension *AExtension);
                                           /* modify rendering info for current line before calling AleGetStringFont ()
                                                return 1: modified, 0:not modified
                                            */
                                    void *ModifyLineInfo;

                                    /* Set this pointer to more data if needed. */
                                    void *MoreExtensionInfo;


                                    /* There may be more extensions
                                       ---------------------------------------- */
                                    struct _AleExtension *NextExtension;


                                 } AleExtension;



   AleExtension *AleSetExtension (AleExtension *ext, char *WorkBuf);
                          /*
                              Set Layout Engine extension functions.
                              Return: previous extension.

                              Set extension to NULL to close extension function
                                (this is the default setting)

                              NOTE:  __ARPHIC_LAYOUTENGINE_EXTENSION__
                              must be defined. Otherwise the setting will be
                              ignored.
                           */






             typedef struct _AleExtendRenderInfo
              {
                  ALE_UINT32 RequestFlag;
                  ALE_UINT32 ResultFlag;
                             /*
                                  RequestFlag contains the features requested.
                                  Parameters are given in following corresponding fields.

                                  ResultFlag contains the features supported by layout engine and
                                  font engine. If it is set, the request is handled and the results
                                  are put in following corresponding fields.
                               */

                      #define ALE_EXTRENDERINFO_BOUNDING_BOX  0x01
                            /*
                                 Set this flag in RequestFlag if you want to get bounding box
                                 info of all following rendering.

                                 If font engine supports bounding box, this flag will
                                 be set in ResultFlag and BBoxLeft, BBoxTop,
                                 BBoxWidth, BBoxHeight will contain the
                                 bounding box information.

                                 NOTE: the bounding box will keep growing after
                                 every following API calls. To get the bounding box
                                 of a particular API call, clear this flag from
                                 ResultFlag in advance.
                             */

                  ALE_INT16 BBoxLeft, BBoxTop;
                  ALE_UINT16 BBoxWidth, BBoxHeight;
                            /*  Parameters for flag ALE_EXTRENDERINFO_BOUNDING_BOX  */


                  /* Reserved for future use */
                  ALE_INT32 Padding [8];

              } AleExtendRenderInfo;


    AleExtendRenderInfo *AleSetExtendRenderInfo (AleExtendRenderInfo  *AInfo, char *WorkBuf);
                         /*
                              Set ExtendRenderInfo so you can give special request to LE & font engine,
                              or retrieve more information about rendering.

                              return: previous setting

                              NOTE: set info to NULL yourself if you do not need to use it anymore.
                         */


   ALE_INT32 AleSetUserLigatureFunction
              (ALE_UINT16 (*AUserLigatureFunction) (ALE_UINT16 *ASubString,
                              ALE_INT32 xstart,  ALE_INT32 *ALigatureLength,
                              ALE_INT32 *ALigatureWidth, ALE_INT32 *ALigatureHeight,
                              char *WorkBuf), char *WorkBuf);
                       /*
                            Set User's Ligature Check function:
                            Check if ASubString (display from xstart) starts a ligature.
                            If not, return zero directly.

                            If yes, return the ligature's Unicode and set *ALigatureLength to
                              the length of ligature (number of characters.).
                              (ALigatureWidth/Height will be ignored by this function)

                            If you want to display the ligature yourself, return 0xFFFF and
                               set *ALigatureWidth and *ALigatureHeigh to the
                               width and height of this ligature.

                            NOTE: for performance issue, substrings of complex script
                             (Indic, Myanmar...etc) will not be sent to this function.
                             This user ligature function is mainly used for motion symbols
                             such as :)  :(  :P
                        */




   /* Kerning
      ------------------------------------------------ */
   ALE_INT32 AleEnableKerningData (char *ABuffer, ALE_INT32 *ALoadBufferSize, char *WorkBuf);
                      /*
                          Enable kerning data in following cases:

                            case I: You have your own kerning data,
                              set ABuffer = the address of your kerning data &
                              set ALoadBufferSize = NULL.
                              NOTE: it is suggested to set render option
                                ALE_RNDO_DisableKerningFromFont to keep
                                your kerning data from being overriden by the setting
                                of font data.

                            case II: You want to enable the kerning data inside
                              font data, and you already load whole font data
                              into memory:
                              set ABuffer = NULL & ALoadBufferSize = NULL.

                              If kerning data is not available or if it is not in
                              memory, ALE_NOT_SUPPORTED will be returned,
                              (and kerning will be disabled).

                            case III: You want to query the size of kerning data
                              inside font data, so you can allocate memory to load it.
                              set ABuffer = NULL,
                              set ALoadBufferSize = address of an integer to
                                   receive kerning data size.
                              when return, *ALoadBufferSize will be set
                               to the size of kerning data in bytes.
                               return ALE_SUCCESS_GETFONT if kern data available,
                                ALE_NOT_SUPPORTED if not

                            case IV: You provide a buffer to load kerning data
                                   into memory and enable it. If your font data
                                   is not inside memory, you should use this function
                                   in this way.
                                   (If you do not know the size of kering data,
                                    you can query for it. see case III.)

                                 set ABuffer [] = your buffer,
                                 set *ALoadBufferSize = size of your buffer in bytes.

                                When return, *ALoadBufferSize will be set to the
                                size of kerning data, and ABuffer [] will contain
                                the kerning data.
                                If size of ABuffer[] is insufficient,
                                  ALE_ILLEGAL_BUFFERSIZE will be returned;
                                If no kerning data is available,
                                  ALE_NOT_SUPPORTED will be returned (and kerning will be disabled).

                          return:
                            ALE_SUCCESS_GETFONT  ok
                            ALE_ILLEGAL_START  data in ABuffer [] is error (and kerning will be disabled).
                            ALE_ILLEGAL_BUFFERSIZE size of ABuffer [] is insufficient

                            ALE_NOT_SUPPORTED  no kerning data available.
                                NOTE: in case II/IV kerning will be disabled in
                                 following rendering.

                         WARNING: If there are more than one font in your font data,
                          the setting in case I, II, IV may be void if you select another
                          font. Unless your font is in memory and you let the kerning
                          data be started automatically, you will need to set kerning
                          every time when you select a new font.

                       */
   void AleDisableKerningData (char *WorkBuf);
                     /*  Stop using current kerning data */

   ALE_INT32 AleGetKerningX (ALE_UINT16 APrevChar, ALE_UINT16 ACurrChar, char *WorkBuf);
                      /*
                          Get X Offset (in pixels) of character pair [APrevChar, ANextChar]
                             positive: enlarge char space; negative: shrink char space
                       */

   /* Font Access
      ------------------------------------------------ */


             typedef struct _AleSetFontInfo
              {
                  ALE_UINT16 Width, Height;  /* Width and Height of Font */
                  ALE_UINT32 Flag;            /* combination of following flags: */

                      #define ALE_SETFONT_ITALIC     0x01
                      #define ALE_SETFONT_BOLD     0x02
                      #define ALE_SETFONT_UNDERLINE     0x04
                      #define ALE_SETFONT_OUTLINE     0x08

                      #define ALE_SETFONT_HINTING  0x40

                      #define ALE_SETFONT_GRAYSCALE  0x100

                      #define ALE_SETFONT_RGBA  0x200
                                        /* Font color is requested in following field:
                                              Red, Green, Blue, Alpha
                                         */

                      #define ALE_SETFONT_FONTID 0x400
                                       /* Font ID is requested as in field FontID
                                           (Only available on some font system) */
                      #define ALE_SETFONT_CODEPAGE 0x800
                                       /* Font CodePage is requested as in field CodePage
                                          (Only available on some font system) */

                 /* Optiona Fields. Only used when
                       corresponding Flag is set.
                    ---------------------------------------- */
                 ALE_UBYTE Red, Green, Blue, Alpha;
                           /* Font color, only used if ALE_SETFONT_RGBA is set
                               range is 0 (darkest)- 0xFF (brightest)
                               For Alpha, range is 0 (transparent) - 0xFF (opaque)
                             */

                 ALE_INT32 FontID;
                             /* Request font of particular FontID.
                                 (Only available on some font system) */

                 #define ALE_SETFONT_CODEPAGE_ALL -32768
                 ALE_INT32 CodePage;
                             /* Request font of particular CodePage.
                                 (Only available on some font system)
                                If you set CodePage to ALE_SETFONT_CODEPAGE_ALL,
                                all codepage is accepted.
                              */

              } AleSetFontInfo;


    ALE_INT32 AleSetFont (AleSetFontInfo  *AInfo, char *WorkBuf);

             /*  Request Set font. Setting info is in *AInfo.

                   CAUTION: this is just a convenient function for you to "change"
                    font. Some font engine may need special setting for the
                    "first" font setting after font engine is initialized, and this
                    API may not work properly for this. So you should use font
                    engine's API for the first font setting instead of this function.

                    Some features you requested may not be supported at every
                    font engine.

                  Return value:
                     ALE_SETFONT_SUCCESS  font set successfully
                     ALE_SETFONT_PARTIAL_SUPPORTED
                          Font setting is partially supported: font is set but
                          some features you requested are not satisfied.
                          NOTE:
                            for font engine not supporting ALE_SETFONT_FONTID
                             or ALE_SETFONT_CODEPAGE, they will still return
                             ALE_SETFONT_SUCCESS even if you set those 2
                             flags. These flags are reserved for particular
                             font system.

                     ALE_SETFONT_NOT_SUPPORTED
                          Font setting is not supported on current font engine


              */

             #define ALE_SETFONT_SUCCESS 2
             #define ALE_SETFONT_PARTIAL_SUPPORTED 1
             #define ALE_SETFONT_NOT_SUPPORTED 0






#ifdef __cplusplus
 };
#endif



#endif

