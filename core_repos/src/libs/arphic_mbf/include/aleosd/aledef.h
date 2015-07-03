/*

       Arphic Layout Engine    ver $Name$
           Copyright (C) 2001-2010 Arphic Technology Co., Ltd. All rights reserved.

        definition (internal data)

 */


#ifndef  __ARPHIC_ALEDEF_H__
#define  __ARPHIC_ALEDEF_H__

#include "aleuser.h"

#ifdef __cplusplus
extern "C"
 {
#endif


/*----------------------------------- Constant   ------------------------------------------ */


          #ifndef NULL
          #define NULL 0
          #endif

          #ifndef ZWNJ
          #define  ZWNJ  0x200C
          #endif

          #ifndef ZWJ
          #define  ZWJ   0x200D
          #endif

/*----------------------------------- Data Structure   ------------------------------------------ */





                                 struct AleMultiPhaseCharInfoType
                                      {
                                         ALE_UINT16 OriginChar;

                                         ALE_UINT16 AboveChar, MidAboveChar, MidChar, MidBelowChar, BelowChar;
                                         ALE_UINT16 PreChar, PostChar;  /* add on July 2006 for Tamil and future language */
                                              /* OriginChar = AboveChar + MiddleChar + BelowChar (0 if none) */

                                         ALE_CHAR MidPhase;  /* Phase of Mid part of char */

                                         ALE_CHAR Padding; /* make structure is 32-bit alignment */
                                         ALE_UINT16 Padding2;
                                      };

                                 #define  AleSubStringForExceptionType_MAXLEN 12

                                 struct AleSubStringForExceptionType
                                  {
                                    /* original Unicode string */
                                    ALE_UINT16  SubString [AleSubStringForExceptionType_MAXLEN];

                                    /* display this Unicode string instead;
                                        (cannot be longer than above; end by zero) */
                                    ALE_UINT16 DisplayString [AleSubStringForExceptionType_MAXLEN];

                                    /* info for display */
                                    ALE_CHAR DisplayPhase [AleSubStringForExceptionType_MAXLEN];
                                    ALE_CHAR DisplayFlag [AleSubStringForExceptionType_MAXLEN];
                                  };


                                /* used in CharGroupFlag [] */
                                #define CharGroupFlag_HalfForm 1

                                #define CharGroupFlag_ExceptionBreak 2

                                #define CharGroupFlag_IsBelowMark 4
                                                         /*
                                                            if you set some character's phase to HCGP_Mid,
                                                            but still hope its horizontal position
                                                               affected by other character's metrics extend1,
                                                            set this flag.
                                                          */






/*----------------------------------- Working Buffer   ------------------------------------------ */

           #define  AleSubStringForComposeType_MAXLEN 5
           #define  AleSubStringForComposeType_NewGlyphMin 100


           struct AleSubStringForComposeType
            {
               ALE_UINT16 GlyphIndex;
                        /*
                            if GlyphIndex < AleSubStringForComposeType_NewGlyphMin,
                            it is a composing method:
                               2: compose 2 characters parallely
                               3: compose 3 characters, put middle one at bottom
                               4: exchange this char with next char

                            otherwise, it is a
                            glyph index to a new composed character  (if index < glyphtotal)
                               or
                            Unicode character (if index >= glyphtotal)
                         */

               ALE_UINT16  SubString [AleSubStringForComposeType_MAXLEN];

            };


                               /* Render Phase (render will be taken in reversed order)
                                   remember to change phase & mask together
                                  ---------------------------------------------------------------- */
                               #define HCGP_Max HCGP_PrePost
                               #define HCGP_PrePost 9
                                                                 /* PrePost is a special phase for some "double-side" vowels.
                                                                    NOTE: AleMultiPhaseCharScanSub () and
                                                                    AleCombineCharBeforePhaseSub () must be executed, and
                                                                    MultiPhaseChar [] array must be established.
                                                                */
                               #define HCGP_Pre  8
                               #define HCGP_Mid  7
                               #define HCGP_MidBelow  6    /* below symbol only for consonant */
                               #define HCGP_MidAbove  5    /* above symbol only for consonant */
                               #define HCGP_Post  4     /* post are generally for vowels */
                               #define HCGP_Below  3
                               #define HCGP_Above  2
                               #define HCGP_End    1

                               /* Mask */
                               #define HCGP_PrePost_Mask 0x200
                               #define HCGP_Pre_Mask 0x100
                               #define HCGP_Mid_Mask 0x80
                               #define HCGP_MidBelow_Mask 0x40
                               #define HCGP_MidAbove_Mask 0x20
                               #define HCGP_Post_Mask 0x10
                               #define HCGP_Below_Mask 0x08
                               #define HCGP_Above_Mask 0x04
                               #define HCGP_End_Mask 0x02

                               /* Special Mask: if set, multiphase char exists */
                               #define HCGP_MultiPhaseChar_Mask 0x01

                               #define SCG_RECORDPHASE(x)  WInfo-> CharGroupPhaseMask |= (ALE_UINT16) (1<< (x));
                               #define SCG_SETPHASE(x)  WInfo-> CharGroupPhaseMask = (ALE_UINT16) (1<< (x));
                               #define SCG_HASPHASE(x)  (WInfo-> CharGroupPhaseMask & (ALE_UINT16) (1<< (x)))
                               #define HCGP_IsMajorPhase(x) ((x)!=HCGP_MidBelow && (x)!=HCGP_MidAbove && (x)!=HCGP_Below && (x)!=HCGP_Above)


                                struct AleCombineMarkInfoType
                                   {
                                      ALE_UINT32 Mask;
                                      ALE_UINT16 GlyphIndex;

                                      ALE_INT16 Padding; /* make structure is 32-bit alignment */
                                   };

          /*EncryptOn*/

         struct AleWorkInfoType
           {

              /* CheckCode
                 ------------------------ */
              ALE_UINT16 CheckCode;  /* must be following code */
              #define ALE_WORKBUFFER_CHECKCODE 0x2351

              /* Setting
                 ------------------------ */
              ALE_UBYTE TextDirection;
              ALE_UBYTE RightClippingMode;

              /* Font Driver
                 ---------------------------------------- */
              AleFontDriverInterface FD;
              char *FontDriverWorkBuffer;

              /* Char Group Operations
                 -------------------------------- */
               #define CHARGROUPMAXLEN 12

               ALE_CHAR CharGroupPhase [CHARGROUPMAXLEN];
                         /* 5-move back char to front, 4-half form & base cons,
                              3-above  2-below  1-tail */

               ALE_CHAR CharGroupFlag [CHARGROUPMAXLEN];
                         /*
                             see above #define
                          */

               ALE_UINT16 CharGroupGlyphIndex [CHARGROUPMAXLEN];
                          /* 0: use current char;
                             FFFF: skip this char;
                             others: replaced unicode/glyph index

                             NOTE: CharGroupGlyphIndex [] may be changed during rendering
                                if  a multi-phase char is encounterred
                           */

               struct AleMultiPhaseCharInfoType *CharGroupMultiPhaseInfo [CHARGROUPMAXLEN];
                           /*
                                 non-NULL if this is a multi-phase char
                            */

               ALE_UINT32  CharGroupTempData [CHARGROUPMAXLEN];
                          /* used as temp var */

               ALE_UINT16 CharGroupPhaseMask;
                          /* (~ & (1<<n)) != 0 means there are chars of phase n */

               ALE_UINT16 PrevCharGroupMask; /* previous neighboring chargroup mask */
               ALE_UINT16 CharGroupFirstChar;  /* first character in char group */

               ALE_INT16 PrevCharGroupAboveExtend, PrevCharGroupBelowExtend;
               ALE_INT16 CurrCharGroupAboveExtend, CurrCharGroupBelowExtend;
                            /*
                               data recording the above/below graphic extend of char group,
                                 so next char group may be able to dodge some glyph
                                 to avoid collision.
                             */

               ALE_UINT16 FontID;  /* Used by Mobile font, -1: undefine */

               ALE_UINT16 CharPositionFirstWordLen;
                   /* skip first # characters and treat them as
                       one word when revising charater positions.
                       NOTE: this will only works for some language,
                       and will not work properly for bi-directional text.
                     */

               ALE_UINT16 Padding;

               struct AleSubStringForExceptionType *CharGroupLastException;
               ALE_UINT16 *CharGroupLastExceptionStart, *CharGroupLastExceptionEnd;


               /* Render Result
                  ------------------------ */
               ALE_INT32 LastOutputStringClipped;
               ALE_INT32 LastRenderedStringLength;
                  /* how many characters renderred last time AleGetStringFont () processed */

               /* Bi-Direction Text Operation
                  ---------------------------------------- */
               ALE_UINT16 *LastBiDiReOrderBuffer;
               ALE_INT32 GivenBiDiReOrderBufferSize;
               ALE_UINT16 *GivenBiDiReOrderBuffer;

               ALE_UINT16 BiDiReOrdefFlag;

                          #define ALE_BIDIREORDER_BEGINBORDERJOIN 1
                          #define ALE_BIDIREORDER_ENDBORDERJOIN 2


               /* Others
                  ------------------------ */
               ALE_INT16 TabWidth;  /* non-zero means Tab enabled and its width in pixels */
               ALE_UINT16 DefaultChar;

               ALE_UINT16 RenderOption;
               AleKerningHeaderType *CurrKerningData;

               AleExtension *Extension;
               AleExtendRenderInfo *ExtendRenderInfo;

               ALE_UINT16 (*UserLigatureFunction) (ALE_UINT16 *ASubString,
                              ALE_INT32 xstart,  ALE_INT32 *ALigatureLength,
                              ALE_INT32 *ALigatureWidth, ALE_INT32 *ALigatureHeight,
                              char *WorkBuf);


               /* Buffers
                  ------------------------ */
               /* Right-to-Left text reordering */
               #ifdef __ARPHIC_BIDI_SUPPORT__
               ALE_UINT16 InnerBiDiReOrderBuffer [(ALE_INNER_BIDI_BUFFER_MAXLEN+1)*3];
               #endif

               /* Bengali, Old version */
               #ifdef __ARPHIC_LAYOUTENGINE_OLD_BENGALI__
               ALE_UINT16 InnerBengaliBuffer_OrgStr [256];
               ALE_UINT16 InnerBengaliBuffer_ReOrder [256];
               ALE_INT32 UseOldBengali;
               #endif

                /*
                    NOTE: to add new members, you may consider changing some
                       parameters from 32bit to 16bit first to save working buffer space.
                 */

                /* For Mobile Font (FontID is declared before)
                   ---------------------------------------------- */
                ALE_INT32 ExtTableOffset;    /* -1:undefine 0:no table*/

           };


           #define ALE_PREPARE_WORKBUFFER  struct AleWorkInfoType *WInfo = (struct AleWorkInfoType*) WorkBuf;
           #define ALE_PREPARE_WORKBUFFER_ALE  struct AleWorkInfoType *AleWInfo = (struct AleWorkInfoType*) WorkBuf;

              /*
                  macro for check validity of working buffer to avoid user send the wrong working buffer
               */
           #define ALE_CHECK_WORKBUFFER_CODE  if ( WInfo-> CheckCode != ALE_WORKBUFFER_CHECKCODE ) return ALE_ERROR_WORKBUFFER;
           #define ALE_CHECK_WORKBUFFER_END  if ( WInfo-> CheckCode != ALE_WORKBUFFER_CHECKCODE ) return;
           #define ALE_CHECK_WORKBUFFER_RET(x)  if ( WInfo-> CheckCode != ALE_WORKBUFFER_CHECKCODE ) return (x);


              /*
                  macro for accessing font driver interface
               */
           #define PAleGetGlyphIndex     (*WInfo-> FD. AleGetGlyphIndex)
           #define PAleGetFont             (*WInfo-> FD. AleGetFont)
           #define PAleCalculateBufferSizeInPixel (*WInfo-> FD. AleCalculateBufferSizeInPixel)
           #define PAleResetFontBuffer  (*WInfo-> FD. AleResetFontBuffer)
           #define PAleAccessFontDriver  (*WInfo-> FD. AleAccessFontDriver)
           #define PAleGetCharFontCache (*WInfo-> FD. AleGetCharFontCache)
           #define PAleDrawCharOnBuffer (*WInfo-> FD. AleDrawCharOnBuffer)
           #define PAleGetFontMetricsExt1 (*WInfo-> FD. AleGetFontMetricsExt1)
           #define PAleGetDefaultKerningData (*WInfo-> FD. AleGetDefaultKerningData)
           #define PAleKerningToRealOffset (*WInfo-> FD. AleKerningToRealOffset)
           #define PAleQueryDriverInfo (*WInfo-> FD. AleQueryDriverInfo)



          /*EncryptOff*/







/*----------------------------------- Language-Specific Data  ------------------------------------------ */

                extern struct AleSubStringForComposeType  AleSubStringForCompose [];




               #ifdef __ARPHIC_LAYOUTENGINE_HINDI__

                               #ifndef  __ALE_HINDI_ECCB    /* Hindi External Char Code Bias */
                               #define  __ALE_HINDI_ECCB  0
                               #endif

                               #define Hindi_Halant  0x094D
                               #define Hindi_Ra  0x0930
                               #define Hindi_Nukta 0x093C
                               #define __HINDI__RA_HALANT_ABOVE  (0xE015+__ALE_HINDI_ECCB)
                               #define __HINDI__RA_HALANT_BELOW  (0xE016+__ALE_HINDI_ECCB)
                               #define __HINDI__DUMMYCIRCLE        (0xE080+__ALE_HINDI_ECCB)

                               #define __ALE_COMPACT_HINDI_ENABLECHAR  (0xE0C0+__ALE_HINDI_ECCB)
               #endif

               #ifdef __ARPHIC_LAYOUTENGINE_BENGALI__

                               #ifndef  __ALE_BENGALI_ECCB    /* Bengali External Char Code Bias */
                               #define  __ALE_BENGALI_ECCB  0
                               #endif

                               #define Bengali_Halant  0x09CD
                               #define Bengali_Ra  0x09B0
                               #define Bengali_Nukta 0x09BC
                               #define __BENGALI__RA_HALANT_ABOVE  (0xE302+__ALE_BENGALI_ECCB)
                               #define __BENGALI__RA_HALANT_BELOW  (0xE301+__ALE_BENGALI_ECCB)
                               #define __BENGALI__DUMMYCIRCLE        (0xE480+__ALE_BENGALI_ECCB)

                               #define Bengali_Ya  0x09AF
                               #define __BENGALI__YA_HALANT_POST  (0xE300+__ALE_BENGALI_ECCB)


                                /* (following macros are also used by alemobi.c) */

                                #define Bengali_ExtendStart  0xE300+__ALE_BENGALI_ECCB
                                #define Bengali_ExtendEnd   0xE4FF+__ALE_BENGALI_ECCB

               #endif



               #ifdef __ARPHIC_LAYOUTENGINE_TAMIL__

                               #ifndef  __ALE_TAMIL_ECCB    /* Tamil External Char Code Bias */
                               #define  __ALE_TAMIL_ECCB  0
                               #endif

                               #define __TAMIL__DUMMYCIRCLE       (0xE500+__ALE_TAMIL_ECCB)
               #endif

               #ifdef __ARPHIC_LAYOUTENGINE_SINHALA__

                               #ifndef  __ALE_SINHALA_ECCB    /* Sinhala External Char Code Bias */
                               #define  __ALE_SINHALA_ECCB  0
                               #endif

                               #define Sinhala_Halant  0x0DCA
                               #define Sinhala_Ya  0x0DBA
                               #define Sinhala_Ra  0x0DBB
                               #define __SINHALA__YA_HALANT_POST  (0xE602+__ALE_SINHALA_ECCB)

                               #define __SINHALA__RA_HALANT_ABOVE  (0xE608+__ALE_SINHALA_ECCB)
                               #define __SINHALA__DUMMYCIRCLE       (0xE600+__ALE_SINHALA_ECCB)
               #endif

               #ifdef __ARPHIC_LAYOUTENGINE_GURMUKHI__

                               #ifndef  __ALE_GURMUKHI_ECCB    /* GURMUKHI External Char Code Bias */
                               #define  __ALE_GURMUKHI_ECCB  0
                               #endif

                               #define Gurmukhi_Halant  0x0A4D
                               #define Gurmukhi_Ya  0x0A2F
                               #define Gurmukhi_Ra  0x0A30
                               #define Gurmukhi_Va  0x0A35
                               #define Gurmukhi_Ha  0x0A39
                               #define Gurmukhi_Nukta 0x0A3C

                               #define __GURMUKHI__RA_HALANT_ABOVE  (0xE888+__ALE_GURMUKHI_ECCB)
                               #define __GURMUKHI__RA_HALANT_BELOW  (0xE881+__ALE_GURMUKHI_ECCB)
                               #define __GURMUKHI__DUMMYCIRCLE       (0xE880+__ALE_GURMUKHI_ECCB)
               #endif


               #ifdef __ARPHIC_LAYOUTENGINE_GUJARATI__

                               #ifndef  __ALE_GUJARATI_ECCB    /* Gujarati External Char Code Bias */
                               #define  __ALE_GUJARATI_ECCB  0
                               #endif

                               #define Gujarati_Halant  0x0ACD
                               #define Gujarati_Ya  0x0AAF
                               #define Gujarati_Ra  0x0AB0
                               #define Gujarati_Va  0x0AB5
                               #define Gujarati_Ha  0x0AB9
                               #define Gujarati_Nukta 0x0ABC

                               #define __GUJARATI__RA_HALANT_ABOVE  (0xE901+__ALE_GUJARATI_ECCB)
                               #define __GUJARATI__RA_HALANT_BELOW  (0xE902+__ALE_GUJARATI_ECCB)
                               #define __GUJARATI__DUMMYCIRCLE       (0xE900+__ALE_GUJARATI_ECCB)
               #endif


               #ifdef __ARPHIC_LAYOUTENGINE_MALAYALAM__

                               #ifndef  __ALE_MALAYALAM_ECCB    /* Malayalam External Char Code Bias */
                               #define  __ALE_MALAYALAM_ECCB  0
                               #endif

                               #define Malayalam_Halant  0x0D4D
                               #define Malayalam_Ya  0x0D2F
                               #define Malayalam_Ra  0x0D30
                               #define Malayalam_Va  0x0D35
                               #define Malayalam_La  0x0D32
                               /* Malayalam has NO nukta */

                               #define __MALAYALAM__YA_HALANT_POST  (0xEA03+__ALE_MALAYALAM_ECCB)

                               /* Malayalam only have Ra-pre form: C-halant-Ra */
                               #define __MALAYALAM__RA_HALANT_PRE  (0xEA01+__ALE_MALAYALAM_ECCB)
                               #define __MALAYALAM__DUMMYCIRCLE       (0xEA00+__ALE_MALAYALAM_ECCB)
               #endif

               #ifdef __ARPHIC_LAYOUTENGINE_TELUGU__

                               #ifndef  __ALE_TELUGU_ECCB    /* Telugu External Char Code Bias */
                               #define  __ALE_TELUGU_ECCB  0
                               #endif

                               #define Telugu_Halant  0x0C4D

                               #define Telugu_Ra  0x0C30


                               #define __TELUGU__DUMMYCIRCLE        (0xED00+__ALE_TELUGU_ECCB)




                               /* Not exist in TeluguMynamar */
                               /*  #define Telugu_Nukta 0x093C  */
                               /* #define __TELUGU__RA_HALANT_ABOVE  (0xE015+__ALE_TELUGU_ECCB) */


               #endif


               #ifdef __ARPHIC_LAYOUTENGINE_KANNADA__

                               #ifndef  __ALE_KANNADA_ECCB    /* Kannada External Char Code Bias */
                               #define  __ALE_KANNADA_ECCB  0
                               #endif

                               #define Kannada_Halant  0x0CCD

                               #define Kannada_Ra  0x0CB0

                               #define __KANNADA__DUMMYCIRCLE        (0xEE80+__ALE_KANNADA_ECCB)

                               #define Kannada_Nukta 0x0CBC
                               /* #define __KANNADA__RA_HALANT_ABOVE  (0xE015+__ALE_KANNADA_ECCB) */


               #endif

               #ifdef __ARPHIC_LAYOUTENGINE_ORIYA__

                               #ifndef  __ALE_ORIYA_ECCB    /* Oriya External Char Code Bias */
                               #define  __ALE_ORIYA_ECCB  0
                               #endif

                               #define Oriya_Halant  0x0B4D
                               #define Oriya_Nukta 0x0B3C
                               #define Oriya_Ra  0x0B30

                               #define __ORIYA__DUMMYCIRCLE        (0xF000+__ALE_ORIYA_ECCB)


                               #define __ORIYA__RA_HALANT_ABOVE  (0xF001+__ALE_ORIYA_ECCB)


               #endif

               #ifdef __ARPHIC_LAYOUTENGINE_TIBETAN__

                               #ifndef  __ALE_TIBETAN_ECCB    /* Tibetan External Char Code Bias */
                               #define  __ALE_TIBETAN_ECCB  0
                               #endif

                               #define Tibetan_Halant  0x0F84
                               #define Tibetan_Ra  0x0F62
                               #define Tibetan_SubNYa  0x0F99
                               #define __TIBETAN__RA_HALANT_ABOVE  (0xEB15+__ALE_HINDI_ECCB)
                               #define __TIBETAN__RA_HALANT_BELOW  (0xEB16+__ALE_HINDI_ECCB)

                               /* Tibetan only have Ra-pre form: C-halant-Ra */
                               #define __TIBETAN__DUMMYCIRCLE       (0xEB00+__ALE_TIBETAN_ECCB)
               #endif


               #ifdef __ARPHIC_LAYOUTENGINE_THAI__
                               #ifndef  __ALE_THAI_ECCB    /* Thai External Char Code Bias */
                               #define  __ALE_THAI_ECCB  0
                               #endif

                               /*
                                  NOTE: You may need to use AleIsThaiAboveMarkExtend ()
                                               / AleIsThaiBelowMarkExtend ()
                                */
                               #define AleIsThaiAboveMark(c)  (((c) >= 0x0E34 && (c) <= 0x0E37) || ((c)>= 0x0E47 && (c)<=0x0E4E) || (c)==0x0E31)
                               #define AleIsThaiBelowMark(c)  ((c) >= 0x0E38 && (c) <= 0x0E3A)
                               #define AleIsThaiMark(c)  (((c) >= 0x0E34 && (c) <= 0x0E3A) || ((c)>= 0x0E47 && (c)<=0x0E4E) || (c)==0x0E31)


                               /* WARNING: substract __ALE_THAI_ECCB before using it */
                               /* used by alemain.c:
                                    WARNING: ONLY MARKS AFFECTED By Metrics Extend1/2 IS ADDED;
                                      Marks specially designed for long head/foot consonants
                                        should NOT be included
                                 */
                               #define AleIsThaiAboveGenMarkExtend(c)  (  ((c)>=0xE201 && (c)<=0xE205) ||  ((c)>=0xE220 && (c)<=0xE242)  )
                               /* NOT USED NOW  #define AleIsThaiBelowGenMarkExtend(c)  0   */
                               /* WARNING: substract  __ALE_THAI_ECCB before using it */

               #endif

               #if  (defined(__ARPHIC_LAYOUTENGINE_THAI__) ||  defined (__ARPHIC_LAYOUTENGINE_LAO__))
                               #define AleThaiReplaceInfo_REPLACEMAX 3
                               typedef struct _AleThaiReplaceInfo
                                {
                                   ALE_UINT16 ReplaceIndex;
                                                       /* > 0 means replacing;
                                                          use ReplaceStr [ReplaceIndex] for next character */
                                   ALE_UINT16 ReplaceStr [AleThaiReplaceInfo_REPLACEMAX];
                                   /* keep this structure 32-bit aligned */
                                } AleThaiReplaceInfo;
               #endif

               #ifdef __ARPHIC_LAYOUTENGINE_MYANMAR__

                               #ifndef  __ALE_MYANMAR_ECCB    /* Myanmar External Char Code Bias */
                               #define  __ALE_MYANMAR_ECCB  0
                               #endif

                               #define Myanmar_Halant  0x1039
                               #define Myanmar_Ra  0x101B
                               #define Myanmar_Ya 0x101A
                               #define Myanmar_Wa 0x101D
                               #define Myanmar_Ha 0x101F

                               #define Myanmar_Nga 0x1004
                               #define Myanmar_Jha 0x1008

                               #define Myanmar_Na 0x1014

                               /* Unicode 5.1 */
                               #define Myanmar_YaMedial2  0x103B
                               #define Myanmar_RaMedial2  0x103C
                               #define Myanmar_WaMedial2  0x103D
                               #define Myanmar_HaMedial2  0x103E
                               #define Myanmar_Halant2    0x103A

                               #define __MYANMAR__DUMMYCIRCLE        (0xEC00+__ALE_MYANMAR_ECCB)

                               #define __MYANMAR__RA_HALANT_BELOW  (0xEC03+__ALE_MYANMAR_ECCB)
                               #define __MYANMAR__YWA_HALANT_POST  (0xEC06+__ALE_MYANMAR_ECCB)
                               #define __MYANMAR__YHA_HALANT_POST  (0xEC07+__ALE_MYANMAR_ECCB)
                               #define __MYANMAR__WHA_HALANT_BELOW  (0xEC08+__ALE_MYANMAR_ECCB)
                               #define __MYANMAR__WHYA_HALANT_BELOW  (0xEC0A+__ALE_MYANMAR_ECCB)

                               #define __MYANMAR__NGA_HALANT_ABOVE  (0xEC09+__ALE_MYANMAR_ECCB)

                               #define __MYANMAR_HA_HALANT_BELOW (0xEC86 + __ALE_MYANMAR_ECCB)


                               /* Not exist in Mynamar */
                               /*  #define Myanmar_Nukta 0x093C  */
                               /* #define __MYANMAR__RA_HALANT_ABOVE  (0xE015+__ALE_MYANMAR_ECCB) */


               #endif



               #ifdef __ARPHIC_LAYOUTENGINE_KHMER__

                               #ifndef  __ALE_KHMER_ECCB    /* Myanmar External Char Code Bias */
                               #define  __ALE_KHMER_ECCB  0
                               #endif

                               #define Khmer_Halant     0x17D1
                               #define Khmer_Halant2   0x17D2

                               #define Khmer_Ro         0x179A

                               #define Khmer_Robat    0x17CC
                               #define Khmer_ConsShifter1  0x017C9
                               #define Khmer_ConsShifter2  0x017CA

                               #define __KHMER__DUMMYCIRCLE        (0xF100+__ALE_KHMER_ECCB)


                               /* Not exist in Mynamar */
                               /*  #define Khmer_Nukta 0x093C  */
                               /* #define __KHMER__RA_HALANT_BELOW  (0xEC03+__ALE_KHMER_ECCB) */
                               /* #define __KHMER__RA_HALANT_ABOVE  (0xE015+__ALE_KHMER_ECCB) */


               #endif


               #ifdef __ARPHIC_LAYOUTENGINE_LAO__
                               #ifndef  __ALE_LAO_ECCB    /* Lao External Char Code Bias */
                               #define  __ALE_LAO_ECCB  0
                               #endif

                               /*
                                  NOTE: You may need to use AleIsLaoAboveMarkExtend ()
                                               / AleIsLaoBelowMarkExtend ()
                                */
                               #define AleIsLaoAboveMark(c)  (((c) >= 0x0EB4 && (c) <= 0x0EB7) || (c) == 0x0EBB ||  ((c)>= 0x0EC7 && (c)<=0x0ECE) || (c)==0x0EB1)
                               #define AleIsLaoBelowMark(c)  (((c) >= 0x0EB8 && (c) <= 0x0EBA) || (c) == 0x0EBC )
                               #define AleIsLaoMark(c)  (((c) >= 0x0EB4 && (c) <= 0x0EBC) || ((c)>= 0x0EC7 && (c)<=0x0ECE) || (c)==0x0EB1)


                               /* WARNING: substract __ALE_LAO_ECCB before using it */
                               /* used by alemain.c:
                                    WARNING: ONLY MARKS AFFECTED By Metrics Extend1/2 IS ADDED;
                                      Marks specially designed for long head/foot consonants
                                        should NOT be included
                                 */
                               #define AleIsLaoAboveGenMarkExtend(c)  (  ((c)>=0xF201 && (c)<=0xF205) ||  ((c)>=0xF220 && (c)<=0xF242)  )
                               /* NOT USED NOW  #define AleIsLaoBelowGenMarkExtend(c)  0   */
                               /* WARNING: substract  __ALE_LAO_ECCB before using it */


               #endif

               #ifdef __ARPHIC_LAYOUTENGINE_ARABIC__
                               #ifndef  __ALE_ARABIC_ECCB    /* Arabic External Char Code Bias */
                               #define  __ALE_ARABIC_ECCB  0
                               #endif
               #endif


/*----------------------------------- Bengali   ------------------------------------------ */

/* by Henry 20051102 for 12 shift one dot left for special hindi char */
/* #define FOR_12_NEW_MET */
/* #define FOR_BENGALI_001 */
/* #define FOR_BENGALI_002_E300 */
/* #define FOR_NOKIA_THAI_12 */

#ifdef FOR_BENGALI_002_E300
#define BENGALI_EXTERNAL_SHIFT  0x300
#else
#define BENGALI_EXTERNAL_SHIFT  0
#endif

#ifdef __ARPHIC_LAYOUTENGINE_BENGALI__
   #define BG_SPECIAL_MARK_CODE    0x9ff
   #define BG_SPECIAL_ORGX         9999
#endif



/*----------------------------------- subfunctions ------------------------------------------ */

  #ifdef  __ALE_C_MEM_FUNC__
         #define AleMemset memset
         #define AleMemcpy memcpy

         #include <string.h>
         /* #include <mem.h> */

  #else
     #ifndef __ALE_USER_MEM_FUNC__
         #define AleMemset AleMemsetSub
         #define AleMemcpy AleMemcpySub
     #else
         #define AleMemset AleUserMemset
         #define AleMemcpy AleUserMemcpy

         /* implemented by user */
         ALE_UBYTE *AleUserMemset(void *ss, ALE_UBYTE cc ,ALE_INT32 len);
         ALE_UBYTE *AleUserMemcpy(void *dest ,void *src ,ALE_INT32 len);
     #endif
  #endif

  ALE_UBYTE *AleMemsetSub (void *ss, ALE_UBYTE cc ,ALE_INT32 len);
  ALE_UBYTE *AleMemcpySub (void *dest ,void *src ,ALE_INT32 len);
  void AleSetUShort (ALE_UINT16 *p, ALE_UINT16 value, ALE_INT32 count);

  struct AleSubStringForComposeType *AleSeekSubStringForCompose (ALE_UINT16 *AString, char *WorkBuf);

  ALE_INT32 AleSeekFromSortedChar (ALE_UINT16 code, ALE_UINT16 *table,
                                                      ALE_INT32 entrysize, ALE_INT32 entryoffset);
                                                     /* entrysize: # of UINT16 each entry (NOT IN BYTES)*/

/*-------------------------- language-specific subfunctions ------------------------------------------ */

 #ifdef __ARPHIC_LAYOUTENGINE_INDIC__

                ALE_INT32 AleGetSubStringLength (ALE_UINT16 *s1, ALE_INT32 maxlen1);
                ALE_INT32 AleCompareSubString (ALE_UINT16 *s1, ALE_INT32 maxlen1,
                                                                    ALE_UINT16 *s2, ALE_INT32 maxlen2, ALE_INT32 s2isPrefix);
                ALE_INT32 AleInitializeSubStringTable (struct AleSubStringForComposeType *table);
                struct AleSubStringForComposeType *AleSeekSubStringFromTable
                         (struct AleSubStringForComposeType *table,  ALE_UINT16 *AString, ALE_INT32 ALenLimit, char *WorkBuf);

                ALE_UINT16 SeekGlyphForSubStringFromTable
                   (struct AleSubStringForComposeType *table,
                     ALE_UINT16 *AString, ALE_INT32 ALenLimit, ALE_INT32 *ASubStringLen, char *WorkBuf);



                struct AleSubStringForExceptionType *AleSeekSubStringFromExceptionTable
                     (struct AleSubStringForExceptionType *table,  ALE_UINT16 *AString,
                       ALE_INT32 ALenLimit, ALE_INT32 *ASubStringLen);




      void AleMultiPhaseCharScanSub (ALE_UINT16 *start, ALE_UINT16 *next,
                 struct AleMultiPhaseCharInfoType *AMultiPhaseCharTable, char *WorkBuf);

      void AleCombineCharBeforePhaseSub (ALE_INT32 phase, ALE_UINT16 *start, ALE_UINT16 *next,
                                     ALE_UINT16 *abovemask, struct AleCombineMarkInfoType *abovecombine,
                                     ALE_UINT16 *midabovemask, struct AleCombineMarkInfoType *midabovecombine,
                                     ALE_UINT16 *midbelowmask, struct AleCombineMarkInfoType *midbelowcombine,
                                     ALE_UINT16 *belowmask, struct AleCombineMarkInfoType *belowcombine,
                                     char *WorkBuf);
                           /*
                               NOTE: if no HCGP_Post character exists, and
                                  midbelowmask == belowmask & midbelowcombine == belowcombine,
                                  characters of both below phase & midbelow phase will be combined together,
                                  so is midabove & above phase.
                            */

      void AleLocateCharGroupGlyphIndex ( ALE_UINT16 *start, ALE_UINT16 *next,
                                                 ALE_INT32 currphase, ALE_INT32 nextphase,
                                                 ALE_UINT16 *lastchar, ALE_UINT16 *nextchar,
                                                 ALE_UINT16 **plastglyph, ALE_UINT16 **pnextglyph, char *WorkBuf);

      void AleLocateCharGroup_VisibleGlyphIndex ( ALE_UINT16 *start, ALE_UINT16 *next,
                                                 ALE_INT32 currphase, ALE_INT32 nextphase,
                                                 ALE_UINT16 *lastchar, ALE_UINT16 *nextchar,
                                                 ALE_UINT16 **plastglyph, ALE_UINT16 **pnextglyph, char *WorkBuf);

 #endif  /* sub functions for some languages */



#ifdef __cplusplus
 };
#endif



#endif





