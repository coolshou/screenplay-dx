/*******************************************************************************
;
;   (C) Copyright Arphic Technology Corp. 1993-2005
;
;    Title:     Platform Setting
;
;    Version:   2.00
*******************************************************************************/


#ifndef _PLATFORM_INCLUDED_
#define _PLATFORM_INCLUDED_

/* the following are the preset features for specific behavior. */
/* Each modification needs careful testing to prevent things go wrong */

/*EncryptOn*/

/****************Do not modify definitions of this section[Start]**************/
/* balance of quality and speed */
#define GRAYSCALE_HI_QUALITY_NORMAL_SPEED        0
#define GRAYSCALE_NORMAL_QUALITY_HI_SPEED        1
#define GRAYSCALE_HI_QUALITY_HI_SPEED            2
/****************Do not modify definitions of this section[End]****************/


/************************Variable compile option[Start]************************/
/* modify this line only if you would like to do the balance evaluation of    */
/* quality and speed under gray (antialiased) mode                            */
#define _GRAYSCALE_QUALITY_SPEED_      GRAYSCALE_HI_QUALITY_HI_SPEED

#define BI_FILE_ACCESS_SUPPORT         1   /* 1--> support file access, 0--> speed up */
#define FOR_ROM_POINTER_ACCESS         0
#define BI_LINE_PATTERN_SUPPORT        0
#define BI_BITMAP_EMBOLDEN_SUPPORT     1
#define BI_USE_C_LIB_MEMCPY            1   /* 1--> Use C libray memcpy, 0--> Use our function(slow) */
#define BI_USE_C_LIB_MEMSET            1   /* 1--> Use C libray memset, 0--> Use our function(slow) */
#define BI_SYMBIAN_SUPPORT             0
#define BI_TRANSFORM_SUPPORT           1
#define BI_FOR_MULTI_TASKING_OPTION    1
#define BI_BITMAP_FONT_CACHE           1
#define BI_SUPPORT_GAMMA_CORRECTION    1
#define BI_SAVE_WORKING_MEMORY         0   /* 1--> working buffer 22KB */
#define BI_NEW_AA_SUPPORT              1   /* need bi_aa.c, bi_aa.h    */
#define BI_VERTICAL_WRITING            0
#define BI_SUPPORT_ECONOMIC_PLATFORM   1
#define BI_SHARE_SIZE                  1   /* support share size in extend table*/
#define BI_SET_WEIGHT                  1   /* for adj table */
#define BI_DEBUG_MODE                  0   /* speed down when open, need bi_internal_use.h */
#define BI_SUPPORT_RADICAL_BASE_FONT   1
#define BI_HQHS_SUPPORT_BOLD           1   /* should set HQHS mode */
#define BI_SMALL_CODESIZE_MONO         0   /* reduce code size */
#define BI_ROTATE_USE_VERTICAL         0   /* reduce code size */
#define BI_KERNING_PAIR                0   /* KERNING PAIR */
#define BI_ATTRIBUTE_3D                0   /* ATTRIBUTE_3D */
#define BI_SUPPORT_GDL_GLYPH_FORMAT    1   /* need bi_gdl.c, bi_gdl.h  */
#define BI_SUPPORT_GDL_LEVEL1_CACHE    1   /* record GDL Index, speedup GDL font , need about 4kb buffer */
#define BI_GDL_HINTING                 0   /* support GDL hinting, must open BI_SUPPORT_GDL_GLYPH_FORMAT */
#define BI_KANJI_HINTING               0   /* support kanji hinting and avoid connected line problem across adjacent chars */
#define BI_SUPPORT_FLAT_MODE           1   /* 1: enable */
/************************Variable compile option[End]**************************/


/******************************************************************************/
/******************************************************************************/
/**************************Do not modify below code****************************/
/******************************************************************************/
/******************************************************************************/

/***********************Special for economic[Start]****************************/
#define BI_IMPROVE_SPEED_MET2             1
#define BI_IMPROVE_SPEED_GLYPH_INDEX      1
#define BI_FOR_GRAYSCALE_WIDTH_CONTROL222   (BI_SUPPORT_ECONOMIC_PLATFORM || BI_HQHS_SUPPORT_BOLD)
#define BI_EMBEDDED_GRAY_BITMAP           BI_SUPPORT_ECONOMIC_PLATFORM
#define BI_SUPPORT_ECONOMIC_PLATFORM2       (BI_HQHS_SUPPORT_BOLD && _GRAYSCALE_QUALITY_SPEED_)
/************************Special for economic[End]*****************************/

#if BI_SYMBIAN_SUPPORT
    #include "MobileFontUtility.h"
#else
    #include "bi_conv.h"
#endif

#if BI_USE_C_LIB_MEMSET
    #include <string.h>
    #if BI_SYMBIAN_SUPPORT
        #define BI_Memset(aTrg, aChar, aLength) (BI_BYTE*)PLATFORM_S_Fill((void*)(aTrg), (aLength), (aChar))
    #else
        #define BI_Memset(Trg, aChar, aLength) (BI_BYTE*)memset(Trg, aChar, aLength)
    #endif
    #define FILLZ(aControlVar, aTrg, aLength)  BI_Memset(aTrg, 0, aLength)
#else
	/*#define FILLZ(aControlVar, aTrg, aLength) for (aControlVar=0; aControlVar<((BI_INT16)(aLength)); aControlVar++) ((char *)aTrg)[aControlVar]=0;*/
	#define FILLZ(aControlVar, aTrg, aLength) for (aControlVar=0; aControlVar<((BI_INT16)(aLength)); aControlVar++) (aTrg)[aControlVar]=0;
#endif

#define FILL(aTrg, aChar, aLength)  BI_Memset(Trg, aChar, aLength)
#define aUSHORT_LIB(x) (BI_UINT16)((((BI_UINT16)(x))<<8) | (((BI_UINT16)(x))>>8))
#define ConvertWORD(a)   BI_ConvertWORD(a)
#define ConvertDWORD(a)   BI_ConvertDWORD(a)


#if   (_GRAYSCALE_QUALITY_SPEED_ == GRAYSCALE_HI_QUALITY_HI_SPEED)
    #define QUALITY_FLAG                  2
    #define FOR_SPEED_CONST_CACHE4
#elif (_GRAYSCALE_QUALITY_SPEED_ == GRAYSCALE_HI_QUALITY_NORMAL_SPEED)
    #define QUALITY_FLAG                  0
#elif (_GRAYSCALE_QUALITY_SPEED_ == GRAYSCALE_NORMAL_QUALITY_HI_SPEED)
    #define QUALITY_FLAG                  1
#endif

#define BI_FOR_PROBLEM_FILE_ACCESS        1

/*-----BI_PROCESS_GRAYSCALE_WITH_16_LEVEL-----*/
/* Form 256 --> 16, effect:                   */
/*     1.reduce helf cache buffer             */
/*     2.down a bit of quality                */
#define BI_PROCESS_GRAYSCALE_WITH_16_LEVEL 0

/*-----------------for memory-----------------*/
/* HINTING + GRAYSCALE_WIDTH_CONTROL  17KB    */
/* EMBBED BMP                          2KB    */
/* MONO_CURVE_GEN                     17KB    */
#if BI_SAVE_WORKING_MEMORY
    #define BI_SUPPORT_HINTING                      0
    #define BI_EMBEDED_BMP_SUPPORT                  0
    #define BI_SUPPORT_MONO_CURVE_GEN               1
    #define BI_SMALL_WORK_BUFFER_FOR_MONO_CURVE_GEN 0
#else
    #define BI_SUPPORT_HINTING                      1
    #define BI_EMBEDED_BMP_SUPPORT                  1
    #define BI_SUPPORT_MONO_CURVE_GEN               1
    #define BI_SMALL_WORK_BUFFER_FOR_MONO_CURVE_GEN 0
#endif

#define  BI_MONOCHROME_WIDTH_CONTROL                0
#define  BI_SUPPORT_TYPEFACE_SCALING                1
#define  FOR_SPECIAL_EMBEDDED_BITMAP                0
#define  FOR_SPECIAL_EMBEDDED_BITMAP_FOR_GRAY       1  /* convert bit mono bitmap to byte bitmap */
#define  BI_SUPPORT_SUBPIXEL                        0  /* developing */
#define  BI_GRAYSCALE_OUTLINE                       1
#define  BI_FILL_GRAYSCALE_BY_STROKE                1
#define  CACHE_NEW_API                              0  /* developing */
#define  BI_FILE_PART_SUPPORT                       1  /* default=1, partial cache */
#define  BI_SUPPORT_K_RENDER                        1  /* clear grayscale stick render */
#define  BI_K_RENDER_MORE_CLEAR                     1  /* align gray to one side for more contrast */
#define  BI_SUPPORT_MULTI_GRAY_TABLE                0  /* developing */
#define  BI_KERNING_UNICODE                         1  /* default=1, use Unicode if 1, use seq if 0 */
#define  BI_SUPPORT_BITMAP_ICON                     0  /* default=0, for supporting 7-seg (bitmap icon) */
#define  BI_COMBINE_GDL_NONOVERLAP                  0  /* 1:support special GDL push/pop hinting for quality of overlapped stroke*/
#define  BI_DECODING_GRAY_BITMAP                    1  /* 1:support compressed 4-bits gray bitmap,0:not support*/
#define  BI_SET_NEW_GDL_BOLD                        0  /* 0: normal for 'A','M'(v3.3.6),1:GDL bold=1.5,1.33,1.33 for Android*/
#define  BI_SUPPORT_TRANSFORM_MATRIX                0  /*0: disable transform matrix ,1:enable */
#define  BI_SUPPORT_4_16_GRAY_LEVELS                0  /* 1: support output bitmap for 4 and 16 gray levels */
#define  BI_GDL_CLOSURE_TYPE                        0  /* 1: enable for white stroke*/

/* ASCII_Hinting */
#define  ASCII_Hinting_QUALITY                      0
/* Copy_Stroke Information */
#define  BI_COPY_INFORMATION                        0
/* Cache BBox for speed */
#define  BI_SPEED_CACHE_BBOX                        0
#endif   /* #ifndef _PLATFORM_INCLUDED_ */
