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
#define _GRAYSCALE_QUALITY_SPEED_ GRAYSCALE_HI_QUALITY_HI_SPEED

#define BI_FILE_ACCESS_SUPPORT 1
#define FOR_ROM_POINTER_ACCESS 0
#define BI_LINE_PATTERN_SUPPORT 0
#define BI_BITMAP_EMBOLDEN_SUPPORT 1
#define BI_USE_C_LIB_MEMCPY 1
#define BI_USE_C_LIB_MEMSET 1
#define BI_SYMBIAN_SUPPORT 0
#define BI_TRANSFORM_SUPPORT 1
#define BI_FOR_MULTI_TASKING_OPTION 1
#define BI_BITMAP_FONT_CACHE 1
#define BI_SUPPORT_GAMMA_CORRECTION 1
#define BI_SAVE_WORKING_MEMORY 0
#define BI_NEW_AA_SUPPORT 1
#define BI_VERTICAL_WRITING 0
#define BI_SUPPORT_GDL_GLYPH_FORMAT 1
#define BI_SUPPORT_GDL_LEVEL1_CACHE 1
#define BI_SUPPORT_ECONOMIC_PLATFORM 0
#define BI_HQHS_SUPPORT_BOLD 1
#define BI_SET_WEIGHT 0
#define BI_DEBUG_MODE                  0   /* speed down when open, need bi_internal_use.h */
#define BI_SUPPORT_RADICAL_BASE_FONT 0
/************************Variable compile option[End]**************************/

/***********************Special for economic[Start]****************************/
#define BI_IMPROVE_SPEED_MET2             BI_SUPPORT_ECONOMIC_PLATFORM
#define BI_IMPROVE_SPEED_GLYPH_INDEX      BI_SUPPORT_ECONOMIC_PLATFORM
#define BI_FOR_GRAYSCALE_WIDTH_CONTROL222 BI_SUPPORT_ECONOMIC_PLATFORM || BI_HQHS_SUPPORT_BOLD
#define BI_EMBEDDED_GRAY_BITMAP           BI_SUPPORT_ECONOMIC_PLATFORM
#define BI_SUPPORT_ECONOMIC_PLATFORM2     BI_HQHS_SUPPORT_BOLD && _GRAYSCALE_QUALITY_SPEED_
/************************Special for economic[End]*****************************/


/******************************************************************************/
/******************************************************************************/
/**************************Do not modify below code****************************/
/******************************************************************************/
/******************************************************************************/

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
#define  FOR_SPECIAL_EMBEDDED_BITMAP_FOR_GRAY       0
#define  BI_SUPPORT_SUBPIXEL                        0  /* developing */
#define  BI_GRAYSCALE_OUTLINE                       1
#define  BI_FILL_GRAYSCALE_BY_STROKE                0
#define  BI_SUPPORT_GRAYSCALE_HINTING               0  /* developing */
#define  CACHE_NEW_API                              0
#endif   /* #ifndef _PLATFORM_INCLUDED_ */




