/************************************************************************
;
;   (C) Copyright Arphic Technology Corp. 1993-2005
;
;    Title:     Arphic Mobile Font Rasterizer
;
;    Module:    bi-lib (include file)
;
;    Version:   1.10
;
;    Author:    Koffman Huang
;
;***********************************************************************/
/*EncryptOn*/

#ifndef _BI_LIB_INCLUDED_
#define _BI_LIB_INCLUDED_

#include "platform.h"
#include "bi_types.h"
#include "bi_mono_render.h"
#include "bi_gray_render.h"
/*webber*/
#include "bi_outline.h"
#include "bi_io.h"
#include "bi_render.h"
#if BI_SUPPORT_GDL_GLYPH_FORMAT
#include "bi_gdl.h"
#endif
#if BI_DEBUG_MODE
#include "bi_internal_use.h"
#endif

#if BI_SUPPORT_K_RENDER
/* Some definition for FIX point convert */
#define BI_ROUND8( x )   ( (BI_INT32)(((x)+128) >> 8) )
#define BI_FLOOR8( x )   ( (BI_INT32)(((x)+255) >> 8) )
#define BI_TRUNC8( x )   ( (BI_INT32)((x) >> 8) )
#define BI_SHIFT8( x )   ( (BI_INT32)((x) << 8) )
#endif

/* MFONT_UNUSED is a macro used to indicate that a given parameter is not  */
/* used -- this is only used to get rid of unpleasant compiler warnings    */
#ifndef MFONT_UNUSED
#define MFONT_UNUSED( arg )  ( (arg) = (arg) )
#endif

#if ASCII_Hinting_QUALITY
#define Ar_abs(x) (((x)<0) ? (-(x)) : (x))
#endif

/*******************************************************************************
    Mobile font version
*******************************************************************************/
#if BI_KANJI_HINTING
    #define BI_MBF_VERSION_MAJOR    1
    #define BI_MBF_VERSION_MINOR    10
    #define BI_MBF_VERSION_RELEASE  0
    #define BI_MBF_VERSION_BUILD    0
#elif BI_GDL_HINTING
    #define BI_MBF_VERSION_MAJOR    1
    #define BI_MBF_VERSION_MINOR    9
    #define BI_MBF_VERSION_RELEASE  0
    #define BI_MBF_VERSION_BUILD    0
#elif BI_COPY_INFORMATION
    #define BI_MBF_VERSION_MAJOR    1
    #define BI_MBF_VERSION_MINOR    8
    #define BI_MBF_VERSION_RELEASE  0
    #define BI_MBF_VERSION_BUILD    0
#elif BI_SUPPORT_GDL_GLYPH_FORMAT
    #define BI_MBF_VERSION_MAJOR    1
    #define BI_MBF_VERSION_MINOR    7
    #define BI_MBF_VERSION_RELEASE  0
    #define BI_MBF_VERSION_BUILD    0
#else
    #define BI_MBF_VERSION_MAJOR    1
    #define BI_MBF_VERSION_MINOR    6
    #define BI_MBF_VERSION_RELEASE  1
    #define BI_MBF_VERSION_BUILD    0
#endif /* BI_SUPPORT_GDL_GLYPH_FORMAT */

#define BI_ENGINE_VERSION_MAJOR     4
#define BI_ENGINE_VERSION_MINOR     2
#define BI_ENGINE_VERSION_RELEASE   0
#define BI_ENGINE_VERSION_BUILD     0

#define VERSION_VALUE( M,I,R,B )    (M*1000000+I*10000+R*100+B)
/*******************************************************************************
    Option define
*******************************************************************************/
#define BI_STROKE_NO_COMPRESS       0
#define BI_STROKE_UNCOMPRESS_MODULE 1
#define BI_RELOCATE_MODULE          1
#define BI_RESIZE_MODULE            1
#define BI_DOUBLE_BUFFER_MODE       0
#define BI_FOR_SUBPIXEL             0
#define BI_FOR_MONOCHROME           1
#define BI_PROPORTIONAL_SUPPORT     1
#define BI_FONT_LINK_SUPPORT        1
#define BI_CODE_SYSTEM_SUPPORT      1
#define BI_MAPPING_TABLE_SUPPORT    1
#define BI_METRICS_SUPPORT          0

/*******************************************************************************
    Option define for developer
*******************************************************************************/
#define BI_CALLBACK_ROUTINE         1

/* other option define
BI_TRANSFORM_SUPPORT        define in file "bi_render.h"
*/

/*******************************************************************************
    Error code
*******************************************************************************/
/* BI_ERROR_XXX */
enum
{
    BI_ERROR_INSUFFICIENT_WORKING_BUFFER	      =-1,
    BI_ERROR_UNICODE_MAPPING_TABLE_NOT_FOUND      =-2,
    BI_ERROR_GET_GLYPH_INDEX_ERROR                =-3,
    BI_ERROR_ID_NOT_FOUND                         =-4,
    BI_ERROR_INVALID_SIZE_HEIGHT                  =-5,
    BI_ERROR_INVALID_SIZE_WIDTH                   =-6,
    BI_ERROR_GET_DATA_FUNCTION_NOT_FOUND          =-7,
    BI_ERROR_GLYPH_TRUNCATION                     =-8,
    BI_ERROR_GET_FONT_DATA_ERROR                  =-9,
    BI_ERROR_GET_CHAR_WIDTH_ERROR                 =-10,
    BI_ERROR_INSUFFICIENT_GLYPH_BUFFER_SIZE       =-11,
    BI_ERROR_GET_FONT_METRICS_TABLE_FAULT         =-12,
    BI_ERROR_CHARSET_NOT_SUPPORT                  =-13,
    BI_ERROR_INSUFFICIENT_HINTING_BUFFER          =-14,
    BI_ERROR_MISSING_CHARACTER                    =-15,
    BI_ERROR_GET_STROKE_WIDTH                     =-16,
    BI_ERROR_GET_GRAY_ADJ_TABLE                   =-17,
    BI_ERROR_GET_GLOBEL_TABLE                     =-18,
    BI_ERROR_CODE_NOT_FOUND_IN_TABLE              =-19,
    BI_ERROR_RBM_ENDIANMISMATCH                   =-20,
    BI_ERROR_RBM_INSUFFICIENT_WORKING_BUFFER      =-21,
    BI_ERROR_MBF_VERSION_INCOMPATABLE             =-22,
    BI_ERROR_GRAY_ADJ_STROKE_BUFFER_OVERFLOW      =-23,
    BI_ERROR_GET_BBOX_TABLE                       =-24,
    BI_ERROR_GET_FMET_TABLE                       =-25,
    BI_ERROR_GAMMA_VALUE_INCORRECT                =-26,
    BI_ERROR_GET_MHNT_TABLE                       =-27,
    BI_ERROR_GET_BBOX_ERROR_TABLE                 =-28,
    BI_ERROR_GET_BBOX_ERROR_TABLE_DATA_ERROR      =-29,
    BI_ERROR_TOO_MANY_CONTROL_POINT_OF_ONE_STROKE =-30,
    BI_ERROR_SET_VERTICAL_WRITING_SET_PARA        =-31,
    BI_ERROR_SET_VERTICAL_WRITING_NO_DATA         =-32,
    BI_ERROR_GET_TFST_TABLE                       =-33,
    BI_ERROR_READ_TFST_TABLE                      =-34,
    BI_ERROR_GET_GDLT_TABLE                       =-35,
    BI_ERROR_INSUFFICIENT_GDL_BUFFER_SIZE         =-36,
    BI_ERROR_GLYPH_TABLE_NOT_FOUND                =-37,
    BI_ERROR_GDL_TABLE_NOT_FOUND                  =-38,
    BI_ERROR_GDL_INIT_ERROR                       =-39,
    BI_ERROR_THE_GRAY_LEVEL_NOT_SUPPORT           =-40,
    BI_ERROR_SETWEIGHT_INIT_ERROR                 =-41,
    BI_ERROR_GET_RCDT_TABLE                       =-42,
    BI_ERROR_RCD_TABLE_NOT_FOUND                  =-43,
    BI_ERROR_GET_LCHT_TABLE                       =-44,
    BI_ERROR_LCH_TABLE_NOT_FOUND                  =-45,
    BI_ERROR_GET_GPMT_TABLE                       =-46,
    BI_ERROR_NOT_SUPPORT_GPMT_TABLE_FORMAT        =-47,
    BI_ERROR_GET_GPMT_TABLE_DATA_ERROR            =-48,
    /*webber 2009.9 -start */
    BI_ERROR_TOO_MANY_CONTROL_POINT_OF_ONE_GLYPH  =-49,
    BI_ERROR_TOO_MANY_CONTOURS_OF_ONE_GLYPH       =-50,
    BI_ERROR_PARTIALCACHE_SETTING		          =-51,
    BI_ERROR_PARTIALCACHE_FILE		              =-52,
    /*webber 2009.9 -end */
    BI_ERROR_GET_AHNT_TABLE                       =-53,   /* for ASCII Hinting */
    BI_ERROR_GET_MTGY_TABLE                       =-54,
    BI_ERROR_GET_GRAY_BBOX_ERROR_TABLE            =-55,
    BI_ERROR_GET_GRAY_BBOX_ERROR_TABLE_DATA_ERROR =-56,
    BI_ERROR_PARSE_GDL_HINT_DATA_ERROR            =-57,
    BI_ERROR_PARSE_GDL_HINT_INSUFFICIENT_WORKING_BUFFER =-58,
    BI_ERROR_PARSE_GDL_HINT_UNKNOW_INSTRUCTION    =-59,
    BI_ERROR_GET_GDMT_TABLE                       =-60,
    BI_ERROR_NOT_SUPPORT_GDMT_TABLE_FORMAT        =-61,
    BI_ERROR_GET_GDMT_TABLE_DATA_ERROR            =-62,
    BI_ERROR_WRONG_GDL_GLYPH_DATA                 =-63,
    BI_ERROR_PARSE_GDL_SET_WEIGHT_ERROR           =-64,
    BI_ERROR_PARSE_GDL_SET_AUTO_HINT_ERROR        =-65,
    BI_ERROR_GET_HINT_TABLE                       =-66,
    BI_ERROR_NOT_SUPPORT_GDHT_TABLE_FORMAT        =-67,
    BI_ERROR_GET_GDHT_TABLE_DATA                  =-68,
    BI_ERROR_GET_GDL_HINT_DATA                    =-69,
    BI_ERROR_INSUFFICIENT_GDL_HINT_BUFFER         =-70,
    BI_ERROR_GET_KANJI_TABLE_ID                   =-71,
    BI_ERROR_GET_KANJI_TABLE_VERSION              =-72,
    BI_ERROR_GET_FLAT_TABLE                       =-73,
    BI_ERROR_INCORRECT_FLAT_TABLE_VERSION         =-74,
    BI_ERROR_TOO_MANY_SECTION_IN_FLAT_TABLE       =-75,
    BI_ERROR_FLAT_TABLE_DATA_ERROR                =-76
};

#if BI_SET_WEIGHT
/* BI_SET_WEIGHT_XXX */
#define BI_SET_WEIGHT_DISABLE                        0
#define BI_SET_WEIGHT_NORMAL                         1
#endif

/* BI_SET_CHARSET_XXX */
#define BI_SET_CHARSET_LATIN_1                      0
#define BI_SET_CHARSET_BIG5                         1
#define BI_SET_CHARSET_SJIS	                        2
#define BI_SET_CHARSET_GB2312                       3
#define BI_SET_CHARSET_KSC                          4
#define BI_SET_CHARSET_SEQ                          0xfffe
#define BI_SET_CHARSET_UNICODE                      0xffff

/* BI_STYLE_XXX (same as FontMetrics style define) */
#define BI_STYLE_REGULAR                            0
#define BI_STYLE_ITALIC                             ( 1L << 0 )
#define BI_STYLE_BOLD                               ( 1L << 1 )
#define BI_STYLE_OUTLINE                            ( 1L << 2 )
#if BI_ATTRIBUTE_3D
#define BI_STYLE_3D_1                               ( 1L << 3 )
#define BI_STYLE_3D_2                               ( 1L << 4 )
#define BI_STYLE_3D                                 ( 1L << 4 )
#define BI_STYLE_SHADOW                             ( 1L << 5 )
#define BI_STYLE_OUTLINE_FRAME                      ( 1L << 30)
#else
#define BI_STYLE_OUTLINE_FRAME                      ( 1L << 3 )
#endif

/* BI_OUTPUT_FORMAT_XXX */
#define BI_OUTPUT_FORMAT_NORMAL_BITMAP              0
/*webber*/
#define BI_OUTPUT_FORMAT_OUTLINE                    1
#define BI_OUTPUT_FORMAT_FT_OUTLINE                 2

/* BI_SET_GRAY_XXX */
#define BI_SET_GRAY_MONOCHROME                      0
#define BI_SET_GRAY_GRAYSCALE_4                     1
#define BI_SET_GRAY_GRAYSCALE_256                   2
#if BI_SUPPORT_4_16_GRAY_LEVELS
#define BI_SET_GRAY_GRAYSCALE_16                    3
#define BI_SET_GRAY_SUBPIXEL_RGB                    4
#define BI_SET_GRAY_SUBPIXEL_BGR                    5
#define BI_SET_GRAY_SUBPIXEL_VRGB                   6
#define BI_SET_GRAY_SUBPIXEL_VBGR                   7
#else
#define BI_SET_GRAY_SUBPIXEL_RGB                    3
#define BI_SET_GRAY_SUBPIXEL_BGR                    4
#define BI_SET_GRAY_SUBPIXEL_VRGB                   5
#define BI_SET_GRAY_SUBPIXEL_VBGR                   6
#endif
/* BI_SET_ROTATE_XXX */
#define BI_SET_ROTATE_NORMAL                        0
#define BI_SET_ROTATE_CLOCKWISE_90                  1
#define BI_SET_ROTATE_CLOCKWISE_180                 2
#define BI_SET_ROTATE_CLOCKWISE_270                 3

/* BI_SET_VERTICAL_WRITING_XXX */
#define BI_SET_VERTICAL_WRITING_DISABLE             0
#define BI_SET_VERTICAL_WRITING_ENABLE              1

/* BI_SET_VERTICAL_WRITING_MODE_XXX */
#define BI_SET_VERTICAL_WRITING_MODE_DISPLAY        0
#define BI_SET_VERTICAL_WRITING_MODE_PRINT          1

/*******************************************************************************
    Define stroke status value as below:
       0     --> position not adjuest
       1~8   --> position offset
                     1 2 3
                     4 0 5
                     6 7 8
       9     --> not available stroke
       10    --> exchange stroke
       11~14 --> reserve
       15    --> no any adjuestment
*******************************************************************************/
#define BI_STROKE_STATUS_NO_OFFSET              0
#define BI_STROKE_STATUS_OFFSET_TOP_LEFT        1
#define BI_STROKE_STATUS_OFFSET_TOP_MIDDLE      2
#define BI_STROKE_STATUS_OFFSET_TOP_RIGHT       3
#define BI_STROKE_STATUS_OFFSET_MIDDLE_LEFT     4
#define BI_STROKE_STATUS_OFFSET_MIDDLE_RIGHT    5
#define BI_STROKE_STATUS_OFFSET_BOTTOM_LEFT     6
#define BI_STROKE_STATUS_OFFSET_BOTTOM_MIDDLE   7
#define BI_STROKE_STATUS_OFFSET_BOTTOM_RIGHT    8
#define BI_STROKE_STATUS_NOT_AVAILABLE          9
#define BI_STROKE_STATUS_EXCHANGE_STROKE       10
#define BI_STROKE_STATUS_SUBSTROKE_ADJUESTMENT 11
#define BI_STROKE_STATUS_ADD_POINT             12
#define BI_STROKE_STATUS_MINUS_POINT           13
#define BI_STROKE_STATUS_CUSTOM_WIDTH          14
#define BI_STROKE_STATUS_NO_ADJUESTMENT        15
/* globel operation for develop tool */
#define BI_STROKE_GLOBEL_MOVE                  16       /* a , (b,c)->(d,e) */
#define BI_STROKE_GLOBEL_EXCHANGE_STROKE       17       /* a , b -> c */
#define BI_STROKE_GLOBEL_SUBSTROKE_MOVE        18       /* a , b , (c,d)->(e,f) */
/* control point operation */
#define BI_STROKE_CONTROL_STROKE_MOVE          19       /* n , dx, dy */
#define BI_STROKE_CONTROL_POINT_MOVE           20       /* n , cn , dx , dy */
/* proportional information */
#define BI_PROPORTIONAL_GLOBEL                 21       /* OrgX,OrgY,AdvX ,after v1.4.0.0 */
#define BI_PROPORTIONAL_LOCAL                  22       /* OrgX,AdvX */
#define BI_PROPORTIONAL_LOCAL_EX               23       /* OrgX,OrgY,AdvX ,after v1.4.0.0 */
#define BI_GLYPH_OFFSET_GLOBEL                 24       /* OffX,OffY ,after v1.4.0.0 */
#define BI_STROKE_STATUS_EXCHANGE_STROKE_EX    25       /* 4-bytes for stroke ID */
/* copy information */
#define BI_STROKE_STATUS_FOR_COPY              26

/* for BI file */
#define BI_SEGMENT_NUM                        1024      /* 4byte*1024 = 1kbyte */
#define BI_SEGMENT_FACTOR                        6      /* BI_MAX_SEQ_CODE/BI_SEGMENT_NUM , 2^6 = 64 */
#define BI_MAX_SEQ_CODE                      65536
#define BI_MAX_STROKE_NUM_OF_ONE_CHAR           64      /* 2005.11.21 */
#define BI_MAX_ADJUEST_COUNT                 256*2
#define BI_HEADER_SIZE                         610
#define BI_FONT_DATA_HEADER_SIZE      (2*4)+1024*4      /* (2*4) + (MAX_ADJUEST_SIZE*4) + (SEGMENT_NUM*4) */
#define BI_STROKE_FORMAT_SIZE                    4      /* 201~14280 */
#define BI_FREQ_STROKE_FORMAT_SIZE               3      /* 0~201 */
#define BI_STROKE_FORMAT_SIZE_EX                 3      /* 201~14280 for Exchange stroke */
#define BI_FREQ_STROKE_FORMAT_SIZE_EX            2      /* 0~201 for Exchange stroke */

#ifdef _FREETYPE_WORKAROUNDS_
    #define BI_MAX_SIZE                      65535    /* monochrome Max size (Outline fonts do not care sizes) */
#else
#define BI_MAX_SIZE                            255      /* monochrome Max size */
#endif

#if BI_SUPPORT_K_RENDER
#define BI_GRAYSCALE_MAX_SIZE                  255      /* for grayscale Max size */
#else
#define BI_GRAYSCALE_MAX_SIZE                  128      /* for grayscale Max size */
#endif

#define BI_MAX_LEN                             256
#define BI_MAX_FONT                              9      /* 2005.11.21 */
#define BI_MAX_SUB_ICON                         16      /* 2005.11.21 */
#define MAX_CONTROL_POINT                      256      /* 2006.01.25 */
#define BI_MAX_STATUS                           28      /* last status(BI_MAX_STATUS-1) is reserved, 2005.11.21 */
#define BI_MAX_ADD_POINT                       128      /* value 128 = 64 point */
#define BI_MAX_DEL_POINT                       128      /* value 128 = 64 point */
#if BI_GDL_CLOSURE_TYPE
#define BI_GLYPH_BUFFER_SIZE                  4096      /* for compress glyph data */
#else
#define BI_GLYPH_BUFFER_SIZE                  3072      /* for compress glyph data */
#endif
#define BI_MAX_KEY_POINT                         8

/* for MET table */
#ifndef BI_MET_HORIZONTAL_TABLE
#define BI_MET_HORIZONTAL_TABLE
#define BI_MET_HORIZONTAL_LABEL_1               'M'
#define BI_MET_HORIZONTAL_LABEL_2               'E'
#define BI_MET_HORIZONTAL_LABEL_3               'T'
#define BI_MET_HORIZONTAL_LABEL_4               'H'
#define BI_MET_HORIZONTAL_VERSION_MAJOR         1
#define BI_MET_HORIZONTAL_VERSION_MINOR         0
#define BI_MET_HORIZONTAL_VERSION_RELEASE       0
#define BI_MET_HORIZONTAL_VERSION_BUILD         1
#define BI_MET_HORIZONTAL_BLOCK_NUM             256
#define BI_BI_MET_HORIZONTAL_MAX_SEQ_CODE       65536
#define BI_MET_HORIZONTAL_ENTRY_COUNT           256     /* BI_BI_MET_HORIZONTAL_MAX_SEQ_CODE/BI_MET_HORIZONTAL_BLOCK_NUM */
#define BI_MET_HORIZONTAL_FIELD_SIZE            2
#define BI_MET_HORIZONTAL_FIELD_COUNT           4
#define BI_MET_HORIZONTAL_ENTRY_SIZE            8       /* BI_MET_HORIZONTAL_FIELD_SIZE*BI_MET_HORIZONTAL_FIELD_COUNT */
#define BI_MET_HORIZONTAL_FLAG_MODE_DEFAULT     0
#define BI_MET_HORIZONTAL_FLAG_MODE_FMET        1
#define BI_MET_HORIZONTAL_FLAG_MODE_FIXED       2
#define BI_MET_CARRY_MODE_DEFAULT               0
#define BI_MET_CARRY_MODE_ROUND                 1
#define BI_MET_CARRY_MODE_FLOOR                 2
#define BI_MET_CARRY_MODE_CEIL                  3
#endif

/* for Formula MET table */
#ifndef BI_FMET_TABLE
#define BI_FMET_TABLE
#define BI_FMET_TABLE_LABEL_1                   'F'
#define BI_FMET_TABLE_LABEL_2                   'M'
#define BI_FMET_TABLE_LABEL_3                   'E'
#define BI_FMET_TABLE_LABEL_4                   'T'
#define BI_FMET_TABLE_ID                        'F'+('M'<<8)+('E'<<16)+('T'<<24)
#define BI_FMET_TABLE_VERSION_MAJOR             1
#define BI_FMET_TABLE_VERSION_MINOR             0
#define BI_FMET_TABLE_VERSION_RELEASE           0
#define BI_FMET_TABLE_VERSION_BUILD             0
#define BI_FMET_TABLE_RECORD_SIZE               8
#endif

/* for Mono Hinting table */
#ifndef BI_MHNT_TABLE
#define BI_MHNT_TABLE
#define BI_MHNT_TABLE_LABEL_1                   'M'
#define BI_MHNT_TABLE_LABEL_2                   'H'
#define BI_MHNT_TABLE_LABEL_3                   'N'
#define BI_MHNT_TABLE_LABEL_4                   'T'
#define BI_MHNT_TABLE_ID                        'M'+('H'<<8)+('N'<<16)+('T'<<24)
#define BI_MHNT_TABLE_VERSION_MAJOR             1
#define BI_MHNT_TABLE_VERSION_MINOR             0
#define BI_MHNT_TABLE_VERSION_RELEASE           0
#define BI_MHNT_TABLE_VERSION_BUILD             0
#define BI_MHNT_TABLE_BLOCK_NUM                 256
#define BI_MHNT_TABLE_MAX_SEQ_CODE              65536
#define BI_MHNT_TABLE_MAX_BLOCK_SIZE            65536  /* bytes */
#define BI_MHNT_TABLE_ENTRY_COUNT               256
#define BI_MHNT_TABLE_BLOCK_INDEX_SIZE          2
#endif

/* for strokes GDL table */
#ifndef BI_GDLT_TABLE
#define BI_GDLT_TABLE
#define BI_GDLT_TABLE_LABEL_1                'G'
#define BI_GDLT_TABLE_LABEL_2                'D'
#define BI_GDLT_TABLE_LABEL_3                'L'
#define BI_GDLT_TABLE_LABEL_4                'T'
#define BI_GDLT_TABLE_ID                     'G'+('D'<<8)+('L'<<16)+('T'<<24)
#define BI_GDLT_TABLE_VERSION_MAJOR          1
#define BI_GDLT_TABLE_VERSION_MINOR          0
#define BI_GDLT_TABLE_VERSION_RELEASE        0
#define BI_GDLT_TABLE_VERSION_BUILD          0
#define BI_GDLT_TABLE_BLOCK_NUM              512
#define BI_GDLT_TABLE_MAX_SEQ_CODE           16384
#define BI_GDLT_TABLE_MAX_BLOCK_SIZE         65536  /* bytes */
#define BI_GDLT_TABLE_ENTRY_COUNT            32
#define BI_GDLT_TABLE_BLOCK_INDEX_SIZE       2
#endif

/* for strokes RCDT table */
#ifndef BI_RCDT_TABLE
#define BI_RCDT_TABLE
#define BI_RCDT_TABLE_LABEL_1                'R'
#define BI_RCDT_TABLE_LABEL_2                'C'
#define BI_RCDT_TABLE_LABEL_3                'D'
#define BI_RCDT_TABLE_LABEL_4                'T'
#define BI_RCDT_TABLE_ID                     'R'+('C'<<8)+('D'<<16)+('T'<<24)
#define BI_RCDT_TABLE_VERSION_MAJOR          1
#define BI_RCDT_TABLE_VERSION_MINOR          0
#define BI_RCDT_TABLE_VERSION_RELEASE        0
#define BI_RCDT_TABLE_VERSION_BUILD          0
#define BI_RCDT_TABLE_BLOCK_NUM              512
#define BI_RCDT_TABLE_MAX_SEQ_CODE           65536
#define BI_RCDT_TABLE_MAX_BLOCK_SIZE         65536  /* bytes */
#define BI_RCDT_TABLE_ENTRY_COUNT            128
#define BI_RCDT_TABLE_BLOCK_INDEX_SIZE       2
#endif

/* for strokes LCHT table */
#ifndef BI_LCHT_TABLE
#define BI_LCHT_TABLE
#define BI_LCHT_TABLE_LABEL_1                'L'
#define BI_LCHT_TABLE_LABEL_2                'C'
#define BI_LCHT_TABLE_LABEL_3                'H'
#define BI_LCHT_TABLE_LABEL_4                'T'
#define BI_LCHT_TABLE_ID                     'L'+('C'<<8)+('H'<<16)+('T'<<24)
#define BI_LCHT_TABLE_VERSION_MAJOR          1
#define BI_LCHT_TABLE_VERSION_MINOR          0
#define BI_LCHT_TABLE_VERSION_RELEASE        0
#define BI_LCHT_TABLE_VERSION_BUILD          0
#define BI_LCHT_TABLE_BLOCK_NUM              256
#define BI_LCHT_TABLE_MAX_SEQ_CODE           65536
#define BI_LCHT_TABLE_MAX_BLOCK_SIZE         65536  /* bytes */
#define BI_LCHT_TABLE_ENTRY_COUNT            256
#define BI_LCHT_TABLE_BLOCK_INDEX_SIZE       2
#endif

/* for BBox error table */
#ifndef BI_BBOX_ERROR_TABLE
#define BI_BBOX_ERROR_TABLE
#define BI_BBOX_ERROR_TABLE_LABEL_1          'B'
#define BI_BBOX_ERROR_TABLE_LABEL_2          'O'
#define BI_BBOX_ERROR_TABLE_LABEL_3          'X'
#define BI_BBOX_ERROR_TABLE_LABEL_4          'E'
#define BI_BBOX_ERROR_TABLE_ID               'B'+('O'<<8)+('X'<<16)+('E'<<24)
#define BI_BBOX_ERROR_TABLE_VERSION_MAJOR    1
#define BI_BBOX_ERROR_TABLE_VERSION_MINOR    0
#define BI_BBOX_ERROR_TABLE_VERSION_RELEASE  0
#define BI_BBOX_ERROR_TABLE_VERSION_BUILD    0
#define BI_BBOX_ERROR_TABLE_BLOCK_NUM        256
#define BI_BBOX_ERROR_TABLE_MAX_SEQ_CODE     65536
#define BI_BBOX_ERROR_TABLE_MAX_BLOCK_SIZE   65536  /* bytes */
#define BI_BBOX_ERROR_TABLE_ENTRY_COUNT      256
#define BI_BBOX_ERROR_TABLE_BLOCK_INDEX_SIZE 2
#endif

/* for GRAY BBox error table */
#ifndef BI_GRAY_BBOX_ERROR_TABLE
#define BI_GRAY_BBOX_ERROR_TABLE
#define BI_GRAY_BBOX_ERROR_TABLE_LABEL_1          'B'
#define BI_GRAY_BBOX_ERROR_TABLE_LABEL_2          'O'
#define BI_GRAY_BBOX_ERROR_TABLE_LABEL_3          'G'
#define BI_GRAY_BBOX_ERROR_TABLE_LABEL_4          'E'
#define BI_GRAY_BBOX_ERROR_TABLE_ID               'B'+('O'<<8)+('G'<<16)+('E'<<24)
#define BI_GRAY_BBOX_ERROR_TABLE_VERSION_MAJOR    1
#define BI_GRAY_BBOX_ERROR_TABLE_VERSION_MINOR    0
#define BI_GRAY_BBOX_ERROR_TABLE_VERSION_RELEASE  0
#define BI_GRAY_BBOX_ERROR_TABLE_VERSION_BUILD    0
#define BI_GRAY_BBOX_ERROR_TABLE_BLOCK_NUM        256
#define BI_GRAY_BBOX_ERROR_TABLE_MAX_SEQ_CODE     65536
#define BI_GRAY_BBOX_ERROR_TABLE_MAX_BLOCK_SIZE   65536  /* bytes */
#define BI_GRAY_BBOX_ERROR_TABLE_ENTRY_COUNT      256
#define BI_GRAY_BBOX_ERROR_TABLE_BLOCK_INDEX_SIZE 2
#endif

/* for BBOX table */
#ifndef BI_BBOX_TABLE
#define BI_BBOX_TABLE
#define BI_BBOX_TABLE_LABEL_1                   'B'
#define BI_BBOX_TABLE_LABEL_2                   'B'
#define BI_BBOX_TABLE_LABEL_3                   'O'
#define BI_BBOX_TABLE_LABEL_4                   'X'
#define BI_BBOX_TABLE_ID                        'B'+('B'<<8)+('O'<<16)+('X'<<24)
#define BI_BBOX_TABLE_VERSION_MAJOR             1
#define BI_BBOX_TABLE_VERSION_MINOR             0
#define BI_BBOX_TABLE_VERSION_RELEASE           0
#define BI_BBOX_TABLE_VERSION_BUILD             0
#define BI_BBOX_TABLE_BLOCK_NUM                 256
#define BI_BBOX_TABLE_MAX_SEQ_CODE              65536
#define BI_BBOX_TABLE_ENTRY_COUNT               256     /* BI_BBOX_TABLE_MAX_SEQ_CODE/BI_BBOX_TABLE_BLOCK_NUM */
#define BI_BBOX_TABLE_FIELD_SIZE                1
#define BI_BBOX_TABLE_FIELD_COUNT               4
#define BI_BBOX_TABLE_ENTRY_SIZE                4       /* BI_BBOX_TABLE_FIELD_SIZE*BI_BBOX_TABLE_FIELD_COUNT */
#endif

/* for globel table */
#ifndef BI_GLOBEL_TABLE
#define BI_GLOBEL_TABLE
#define BI_GLOBEL_ATTR_TYPE_MONO_STROKE_WIDTH   1
#define BI_GLOBEL_ATTR_TYPE_CHAR_ATTR           2
#define BI_GLOBEL_TABLE_LABEL_1                 'G'
#define BI_GLOBEL_TABLE_LABEL_2                 'B'
#define BI_GLOBEL_TABLE_LABEL_3                 'L'
#define BI_GLOBEL_TABLE_LABEL_4                 'T'
#define BI_GLOBEL_TABLE_ID                      'G'+('B'<<8)+('L'<<16)+('T'<<24)
#define BI_GLOBEL_TABLE_VERSION_MAJOR           1
#define BI_GLOBEL_TABLE_VERSION_MINOR           0
#define BI_GLOBEL_TABLE_VERSION_RELEASE         0
#define BI_GLOBEL_TABLE_VERSION_BUILD           0
#define BI_GLOBEL_TABLE_BLOCK_NUM               256
#define BI_BI_GLOBEL_TABLE_MAX_SEQ_CODE         65536
#define BI_GLOBEL_TABLE_ENTRY_COUNT             256     /* BI_BI_MET_HORIZONTAL_MAX_SEQ_CODE/BI_MET_HORIZONTAL_BLOCK_NUM */
#define BI_GLOBEL_TABLE_BLOCK_INDEX_SIZE        2
#define BI_GLOBEL_TABLE_MAX_ATTRIBUTE_COUNT     64
#define BI_GLOBEL_TABLE_ATTRIBUTE_UNIT_SIZE     2
#endif

/* for tables index table */
#ifndef BI_TABLE_INDEX_TABLE
#define BI_TABLE_INDEX_TABLE
#define BI_TABLE_INDEX_LABEL_1                  'T'
#define BI_TABLE_INDEX_LABEL_2                  'I'
#define BI_TABLE_INDEX_LABEL_3                  'D'
#define BI_TABLE_INDEX_LABEL_4                  'X'
#define BI_TABLE_INDEX_ID                       'T'+('I'<<8)+('D'<<16)+('X'<<24)
#define BI_TABLE_INDEX_VERSION_MAJOR            1
#define BI_TABLE_INDEX_VERSION_MINOR            0
#define BI_TABLE_INDEX_VERSION_RELEASE          0
#define BI_TABLE_INDEX_VERSION_BUILD            0
#endif

/* for gray adj table */
#ifndef BI_GRAY_ADJ_TABLE
#define BI_GRAY_ADJ_TABLE
#define BI_GRAY_ADJ_LABEL_1                     'G'
#define BI_GRAY_ADJ_LABEL_2                     'A'
#define BI_GRAY_ADJ_LABEL_3                     'D'
#define BI_GRAY_ADJ_LABEL_4                     'J'
#define BI_GRAY_ADJ_ID                          'G'+('A'<<8)+('D'<<16)+('J'<<24)
#define BI_GRAY_ADJ_VERSION_MAJOR               2
#define BI_GRAY_ADJ_VERSION_MINOR               0
#define BI_GRAY_ADJ_VERSION_RELEASE             0
#define BI_GRAY_ADJ_VERSION_BUILD               0
#define BI_GRAY_ADJ_DENSITY_DEFAULT             64
#define BI_GRAY_ADJ_BOLD_WIDTH_DEFAULT          64
#define BI_GRAY_ADJ_FONT_TYPE_DEFAULT           0       /* 0 --> Round , 1--> Round_Gothic */
#define BI_GRAY_ADJ_LETTER_SIZE_DEFAULT         256
#define BI_GRAY_ADJ_WIDTH_DEFAULT               15
#define BI_GRAY_ADJ_MAX_STROKE_BUFFER           64      /* bytes */
#endif

/* for width table */
#ifndef BI_MONO_WIDTH_TABLE
#define BI_MONO_WIDTH_TABLE
#define BI_MONO_WIDTH_TABLE_LABEL_1             'M'
#define BI_MONO_WIDTH_TABLE_LABEL_2             'W'
#define BI_MONO_WIDTH_TABLE_LABEL_3             'D'
#define BI_MONO_WIDTH_TABLE_LABEL_4             'T'
#define BI_MONO_WIDTH_TABLE_ID                  'M'+('W'<<8)+('D'<<16)+('T'<<24)
#define BI_MONO_WIDTH_TABLE_VERSION_MAJOR       1
#define BI_MONO_WIDTH_TABLE_VERSION_MINOR       0
#define BI_MONO_WIDTH_TABLE_VERSION_RELEASE     0
#define BI_MONO_WIDTH_TABLE_VERSION_BUILD       0
#endif

/* for typeface scaling */
#ifndef BI_TYPEFACE_SCALING_TABLE
#define BI_TYPEFACE_SCALING_TABLE
#define BI_TYPEFACE_SCALING_TABLE_LABEL_1       'T'
#define BI_TYPEFACE_SCALING_TABLE_LABEL_2       'F'
#define BI_TYPEFACE_SCALING_TABLE_LABEL_3       'S'
#define BI_TYPEFACE_SCALING_TABLE_LABEL_4       'T'
#define BI_TYPEFACE_SCALING_TABLE_ID            'T'+('F'<<8)+('S'<<16)+('T'<<24)
#define BI_TYPEFACE_SCALING_TABLE_VERSION_MAJOR   1
#define BI_TYPEFACE_SCALING_TABLE_VERSION_MINOR   0
#define BI_TYPEFACE_SCALING_TABLE_VERSION_RELEASE 0
#define BI_TYPEFACE_SCALING_TABLE_VERSION_BUILD   0
#endif

/* for flat mode */
#ifndef BI_FLAT_MODE_TABLE
#define BI_FLAT_MODE_TABLE
#define BI_FLAT_MODE_TABLE_LABEL_1       'F'
#define BI_FLAT_MODE_TABLE_LABEL_2       'L'
#define BI_FLAT_MODE_TABLE_LABEL_3       'A'
#define BI_FLAT_MODE_TABLE_LABEL_4       'T'
#define BI_FLAT_MODE_TABLE_ID            'F'+('L'<<8)+('A'<<16)+('T'<<24)
#define BI_FLAT_MODE_TABLE_VERSION_MAJOR   1
#define BI_FLAT_MODE_TABLE_VERSION_MINOR   0
#define BI_FLAT_MODE_TABLE_VERSION_RELEASE 0
#define BI_FLAT_MODE_TABLE_VERSION_BUILD   0
#endif

/* for grayscale parameter */
#ifndef BI_GRAY_PARAM_TABLE
#define BI_GRAY_PARAM_TABLE
#define BI_GRAY_PARAM_TABLE_LABEL_1       'G'
#define BI_GRAY_PARAM_TABLE_LABEL_2       'P'
#define BI_GRAY_PARAM_TABLE_LABEL_3       'M'
#define BI_GRAY_PARAM_TABLE_LABEL_4       'T'
#define BI_GRAY_PARAM_TABLE_ID            'G'+('P'<<8)+('M'<<16)+('T'<<24)
#define BI_GRAY_PARAM_TABLE_VERSION_MAJOR   1
#define BI_GRAY_PARAM_TABLE_VERSION_MINOR   0
#define BI_GRAY_PARAM_TABLE_VERSION_RELEASE 0
#define BI_GRAY_PARAM_TABLE_VERSION_BUILD   0
#endif

/* GDL parameter */
#ifndef BI_GDL_PARAM_TABLE
#define BI_GDL_PARAM_TABLE
#define BI_GDL_PARAM_TABLE_LABEL_1       'G'
#define BI_GDL_PARAM_TABLE_LABEL_2       'D'
#define BI_GDL_PARAM_TABLE_LABEL_3       'M'
#define BI_GDL_PARAM_TABLE_LABEL_4       'T'
#define BI_GDL_PARAM_TABLE_ID            'G'+('D'<<8)+('M'<<16)+('T'<<24)
#define BI_GDL_PARAM_TABLE_VERSION_MAJOR   1
#define BI_GDL_PARAM_TABLE_VERSION_MINOR   0
#define BI_GDL_PARAM_TABLE_VERSION_RELEASE 0
#define BI_GDL_PARAM_TABLE_VERSION_BUILD   0
#endif

/* GDL Hinting */
#ifndef BI_GDL_HINT_TABLE
#define BI_GDL_HINT_TABLE
#define BI_GDL_HINT_TABLE_LABEL_1       'G'
#define BI_GDL_HINT_TABLE_LABEL_2       'D'
#define BI_GDL_HINT_TABLE_LABEL_3       'H'
#define BI_GDL_HINT_TABLE_LABEL_4       'T'
#define BI_GDL_HINT_TABLE_ID            'G'+('D'<<8)+('H'<<16)+('T'<<24)
#define BI_GDL_HINT_TABLE_VERSION_MAJOR   1
#define BI_GDL_HINT_TABLE_VERSION_MINOR   0
#define BI_GDL_HINT_TABLE_VERSION_RELEASE 0
#define BI_GDL_HINT_TABLE_VERSION_BUILD   0
#endif

/* Kanji Hinting */
#ifndef BI_KANJI_HINT_TABLE
#define BI_KANJI_HINT_TABLE
#define BI_KANJI_HINT_TABLE_LABEL_1         'K'
#define BI_KANJI_HINT_TABLE_LABEL_2         'J'
#define BI_KANJI_HINT_TABLE_LABEL_3         'H'
#define BI_KANJI_HINT_TABLE_LABEL_4         'T'
#define BI_KANJI_HINT_TABLE_ID              (BI_KANJI_HINT_TABLE_LABEL_1+((BI_KANJI_HINT_TABLE_LABEL_2+((BI_KANJI_HINT_TABLE_LABEL_3+(BI_KANJI_HINT_TABLE_LABEL_4<<8))<<8))<<8))
#define BI_KANJI_HINT_TABLE_VERSION_MAJOR   1
#define BI_KANJI_HINT_TABLE_VERSION_MINOR   3
#define BI_KANJI_HINT_TABLE_VERSION_RELEASE 0
#define BI_KANJI_HINT_TABLE_VERSION_BUILD   0
#define BI_KANJI_HINT_TABLE_VERSION         (BI_KANJI_HINT_TABLE_VERSION_MAJOR+256*(BI_KANJI_HINT_TABLE_VERSION_MINOR+256*(BI_KANJI_HINT_TABLE_VERSION_RELEASE+256*BI_KANJI_HINT_TABLE_VERSION_BUILD)))
#endif

#ifndef BI_MULTI_GRAY_TABLE
#define BI_MULTI_GRAY_TABLE
#define BI_MULTI_GRAY_TABLE_LABEL_1       'M'
#define BI_MULTI_GRAY_TABLE_LABEL_2       'T'
#define BI_MULTI_GRAY_TABLE_LABEL_3       'G'
#define BI_MULTI_GRAY_TABLE_LABEL_4       'Y'
#define BI_MULTI_GRAY_TABLE_ID            'M'+('T'<<8)+('G'<<16)+('Y'<<24)
#define BI_MULTI_GRAY_TABLE_VERSION_MAJOR   1
#define BI_MULTI_GRAY_TABLE_VERSION_MINOR   0
#define BI_MULTI_GRAY_TABLE_VERSION_RELEASE 0
#define BI_MULTI_GRAY_TABLE_VERSION_BUILD   0
#endif

#ifndef BI_BITMAP_ICON_TABLE
#define BI_BITMAP_ICON_TABLE
#define BI_BITMAP_ICON_TABLE_LABEL_1       'B'
#define BI_BITMAP_ICON_TABLE_LABEL_2       'M'
#define BI_BITMAP_ICON_TABLE_LABEL_3       'I'
#define BI_BITMAP_ICON_TABLE_LABEL_4       'C'
#define BI_BITMAP_ICON_TABLE_ID            'B'+('M'<<8)+('I'<<16)+('C'<<24)
#define BI_BITMAP_ICON_TABLE_VERSION_MAJOR   1
#define BI_BITMAP_ICON_TABLE_VERSION_MINOR   0
#define BI_BITMAP_ICON_TABLE_VERSION_RELEASE 0
#define BI_BITMAP_ICON_TABLE_VERSION_BUILD   0
#endif

/* for ASCII Hinting table */
#ifndef BI_AHNT_TABLE
#define BI_AHNT_TABLE
#define BI_AHNT_TABLE_LABEL_1                   'A'
#define BI_AHNT_TABLE_LABEL_2                   'H'
#define BI_AHNT_TABLE_LABEL_3                   'N'
#define BI_AHNT_TABLE_LABEL_4                   'T'
#define BI_AHNT_TABLE_ID                        'A'+('H'<<8)+('N'<<16)+('T'<<24)
#define BI_AHNT_TABLE_VERSION_MAJOR             1
#define BI_AHNT_TABLE_VERSION_MINOR             0
#define BI_AHNT_TABLE_VERSION_RELEASE           0
#define BI_AHNT_TABLE_VERSION_BUILD             0
#define BI_AHNT_TABLE_BLOCK_NUM                 256
#define BI_AHNT_TABLE_MAX_SEQ_CODE              65536
#define BI_AHNT_TABLE_ENTRY_COUNT               256      /* BI_AHNT_TABLE_MAX_SEQ_CODE/BI_AHNT_TABLE_BLOCK_NUM */
#define BI_AHNT_TABLE_FIELD_SIZE                1
#define BI_AHNT_TABLE_FIELD_COUNT               12
#define BI_AHNT_TABLE_ENTRY_SIZE                12       /* BI_AHNT_TABLE_FIELD_SIZE*BI_AHNT_TABLE_FIELD_COUNT */
#endif

#define BI_FLAG_GET_FONT_NO_EMBEDDED_BITMAP     ( 1L<<0 )
#define BI_FLAG_GET_FONT_NO_RENDER              ( 1L<<1 )


/* FONT_FLAG */
#define BI_FONT_FLAG_BITMAP_1BIT_TO_8BIT        ( 1L<<0 )

/* BI_OPTION_FLAG_XXX */
#define BI_OPTION_FLAG_MONO_ODD_USE_EVEN_SIZE            ( 1L<<0 )
#define BI_OPTION_FLAG_HIGHT_SPEED_GRAYSCALE_MODE        ( 1L<<2 )
#define BI_OPTION_FLAG_USE_DEFAULT_CHAR                  ( 1L<<3 )
#define BI_OPTION_FLAG_EXTEND_FIX_PITCH_ADVX_WHEN_BOLD   ( 1L<<4 )
#define BI_OPTION_FLAG_GRID_FITTING                      ( 1L<<5 )
#define BI_OPTION_FLAG_AUTO_FLAT_MODE2                   ( 1L<<6 )
#define BI_OPTION_FLAG_KEEP_STROKE_WIDTH_WHEN_FLAT       ( 1L<<7 )
#define BI_OPTION_FLAG_NO_HINTTING                       ( 1L<<8 )
#define BI_OPTION_FLAG_KEEP_ADVX_WHEN_OUTLINE            ( 1L<<9 )
#define BI_OPTION_FLAG_RBMP_POST_PROCESS_ITALIC          ( 1L<<10) 

/* BI_FLAG_XXX (for font metrics flags)*/
#define BI_FLAG_SCALABLE			   ( 1L << 0 )
#define BI_FLAG_FIXED_SIZES			   ( 1L << 1 )
#define BI_FLAG_PROPORTIONAL			   ( 1L << 2 )
#define BI_FLAG_HORIZONTAL			   ( 1L << 3 )
#define BI_FLAG_VERTICAL			   ( 1L << 4 )
#define BI_FLAG_KERNING				   ( 1L << 5 )
#define BI_FLAG_COMPLEX_SCRIPT			   ( 1L << 6 )
#define BI_FLAG_HAVE_DEFAULT_CHAR		   ( 1L << 7 )
#define BI_FLAG_CLIP_BY_SIZE                       ( 1L << 8 )
#define BI_FLAG_SIZE_SHARE                         ( 1L << 9 )

/*******************************************************************************
    Define Header (as same as VCFT)
*******************************************************************************/
#define HEAD_55AA                                0
#define HEAD_VER                                 2
#define HEAD_TOTALSIZE                           4
#define HEAD_EGTMARK                             8
#define HEAD_MARK                               24
#define HEAD_CUSTOM_ID                          56
#define HEAD_CHARSET                            58
#define HEAD_TYPEFACE                           60
#define HEAD_USED                               64     /* set 0xff */
#define HEAD_RESERVED1                         140     /* set 0xff */
#define HEAD_BI_TABLE_IDX_PTR                  148     /* for BI */
#define HEAD_FONT_METRICS_PTR                  152     /* for BI */
#define HEAD_BI_FONT_LINK_ID                   156     /* for BI */
#define HEAD_BI_DATA_PTR                       160     /* for BI */
#define HEAD_BI_GLYPH_PTR                      164     /* for BI */
#define HEAD_BI_ADJ_PTR                        168     /* for BI */
#define HEAD_BI_MET_PTR                        172     /* for BI */
#define HEAD_BI_BMP_PTR                        176     /* for BI */
#define HEAD_BI_MAP_PTR                        180     /* for BI */
#define HEAD_GRID_STR                          184     /* set 0x00 */
#define HEAD_OTHERS                            188
/* total 610 */

#if BI_BITMAP_FONT_CACHE
#define BI_CACHE_MODE_32BIT                    0
#define BI_CACHE_MODE_64BIT                    1
#endif

#if BI_IMPROVE_SPEED_GLYPH_INDEX
#define BI_SPEED_MARK_GLY                       -9999
#endif
/*******************************************************************************
                                  Type define
*******************************************************************************/
#if BI_CALLBACK_ROUTINE

#define BI_GET_DATA_ROM_MODE                    0x00000000
#define BI_GET_DATA_FILE_MODE                   0x00000001
#define BI_GET_DATA_ROM_PART_MODE               0x00000010
#define BI_GET_DATA_FILE_PART_MODE              0x00000011
#define BI_GET_DATA_USER_DEFINE                 0xffffffff


#define BI_MEM_ITEM_MAX_COUNT 12
/*******************************************************************************
    BI_MEM_ITEM_ID_xxx
*******************************************************************************/
#define BI_MEM_ITEM_ALL                                            1
#define BI_MEM_ITEM_FONT_ID_LIST_ARRAY                             2
#define BI_MEM_ITEM_BITMAP_ENGINE_WORK_BUFFER                      3
#define BI_MEM_ITEM_FILE_ACCESS_BUFFER                             4
#define BI_MEM_ITEM_FONT_ID_STRUCTURE                              5
#define BI_MEM_ITEM_FACE_DATA_STRUCTURE                            6
#define BI_MEM_ITEM_STROKE_DATA_STRUCTURE                          7
#define BI_MEM_ITEM_HINT_DATA                                      8
#define BI_MEM_ITEM_GLYPH_BUFFER                                   9
#define BI_MEM_ITEM_GRAYSCALE_RASTER_BUFFER                        10
#define BI_MEM_ITEM_GRAYSCALE_RASTER_DATA                          11
#define BI_MEM_ITEM_GDL_DATA                                       12
#define BI_MEM_ITEM_GDL_CACHE1_DATA                                13
#define BI_MEM_ITEM_GDL_HINT_BUFFER                                14

typedef struct {
    BI_VOID*  start_addr;
    BI_UINT32 length;
    BI_UINT16 item_id;
    BI_UINT16 padding;
} TMemItem;

typedef struct {
    BI_VOID*  memory;
    BI_UINT32 memory_size;
    BI_VOID*  free_mem_ptr;
	BI_UINT32 free_mem_size;
	BI_VOID*  render_mem_ptr;  /* we can free the memory when switch render mode */
	BI_UINT32 render_mem_size; /* the size is render fix size not include bitmap render buffer */
    BI_UINT32 item_count;
    TMemItem  items[BI_MEM_ITEM_MAX_COUNT];
} TArMem;

#if BI_SUPPORT_GDL_LEVEL1_CACHE
typedef struct {
	BI_UBYTE            cached;
	BI_UBYTE            key_count;
	BI_UBYTE            width_count;
	BI_UBYTE            padding;
	BI_INT32            StrokeOffset;
} BI_GDL_DATA_CACHE1;
#endif

#if BI_GDL_HINTING
/* Instruction ID */
#define HINT_GDL_PARAM  1
#define HINT_MOVE_KEY   2
#define HINT_MOVE_XY    3
#define HINT_MOVE_X     4
#define HINT_MOVE_Y     5
#define HINT_MOVE_CXY   6
#define HINT_MOVE_CN    7
#define HINT_STEM_WIDTH 8
#define HINT_ADDP_16    9
#define HINT_ADDP_256   10
#define HINT_DEL_SUB_STK 13


#define BI_MAX_HINT_STROKE 64
#define BI_MAX_GDL_HINT_SIZE 256
#define BI_MAX_HINT_ADD_POINT 256

/* one stroke hinting data */
typedef struct {
	BI_UBYTE StrokeNum;
	BI_UBYTE ControlPointNum;
	BI_BYTE  OffsetX; /* fix 4.4 , -8.0~7.9375 */
	BI_BYTE  OffsetY;
} TMoveCXY;

typedef struct {
	BI_UBYTE StrokeNum;
	BI_UBYTE KeyNum;
	BI_BYTE  OffsetX; /* -127~128 */
	BI_BYTE  OffsetY;
} TMoveKey;

typedef struct {
	BI_UBYTE StrokeNum;
	BI_UBYTE SubStrokeNum;
    BI_BYTE  OffsetX; /* fix 4.4 , -8.0~7.9375 */
	BI_BYTE  OffsetY;
} TMoveSubstroke;

typedef struct {
	BI_UBYTE StrokeNum;
	BI_BYTE  StemWidth; /* -128~127 */
	BI_INT16 padding;
} TStemWidth;

typedef struct {
	BI_UBYTE Level; /* 0~16     */
	BI_BYTE  X;     /* -128~127 */
	BI_BYTE  Y;
	BI_BYTE  padding;
} TAddPoint;

typedef struct {
	BI_UBYTE           BoldV;              /* fix 2.6 , default=0x40 */
	BI_UBYTE           BoldH;              /* fix 2.6 , default=0x40 */
	BI_UBYTE           BoldS;              /* fix 2.6 , default=0x40 */
	BI_UBYTE           Level;              /* 0~255 auto align , default=255 */
	BI_UBYTE           Gamma;              /* 0~20 (0~2.0) , default=10      */
	BI_UBYTE           padding;            /* unused  */
	BI_UINT16          Flags;              /* bit0:horizontal, bit1:vertical, 2~15bit reserved */
} TGDL_Param;

typedef struct {
	BI_UBYTE StrokeNum;
	BI_UBYTE SubStrokeNum;
	BI_INT16 padding;
} TDelSubstroke;

typedef struct {
	BI_INT16  Move_CP_Count;
	BI_INT16  Move_Sub_Count;
	BI_INT16  Stem_Width_Count;
	BI_INT16  Add_Point_Count;
	BI_INT16  Del_Sub_Stk_Count;
	BI_INT16  padding;
	TMoveCXY  Move_CP_Array[MAX_CONTROL_POINT];
	TMoveSubstroke Move_Sub_Stroke_Array[BI_MAX_HINT_STROKE];
	TStemWidth Stem_Width_Array[BI_MAX_HINT_STROKE];
	TAddPoint Add_Point_Array[BI_MAX_HINT_ADD_POINT];
	TDelSubstroke Del_Sub_Stroke_Array[BI_MAX_HINT_STROKE];
	TGDL_Param GDL_Param_Setting;
} TGDL_Hint_Data;

typedef struct {
	BI_UINT16 MinCode;
	BI_UINT16 MaxCode;
	BI_UINT16 MaxBlockRecordNum;
	BI_UINT16 Flag;  /* bit 1-->no hint */
	BI_UINT32 BlockOffset;
} TGDL_Hint_Size_Index;

#endif

#if BI_BITMAP_FONT_CACHE
typedef struct {
    BI_BYTE        *cachebuff;      /* cache buff size=cachenodecount*(2^cachenodesize+2)+2^entrycount*48*/
    BI_INT32       cachebufflen;
    BI_INT32       entrycount;      /* 8=256,9=512,10=1024,11=2048,12=4096*/
    BI_INT32       cachenodesize;   /* must be 4=16,5=32,...,10=1024*/
}   ArsCacheBuff;

typedef struct {
    BI_UINT16      startcode;
    BI_UINT16      finalcode;
    BI_UINT16	   max_cachesize;
    BI_BYTE        enable;          /* 0=disable,1=enable and reset*/
    BI_BYTE        cache_mode;
}   ArsCacheStatus;


/* for internl use */
typedef struct { 
    BI_INT32       HashKey1;
    BI_INT32       HashKey2;
    BI_BYTE*       In_bmp_buf;       /* In line buffer mode this would a output when check not hit */
    BI_INT16       In_Buff_Height;
    BI_INT16       In_Buff_Width;
    BI_INT16       In_Left_Offset;  /* We just cache bbox of char so must record offset */
    BI_INT16       In_Top_Offset;
    BI_INT32       mode_flag;
    /* Output */
    BI_BYTE*       Out_bmp_buf;      /* output when cache hit */
    BI_INT16       Out_Buff_Height;
    BI_INT16       Out_Buff_Width;
    BI_INT16       Out_Left_Offset;
    BI_INT16       Out_Top_Offset;
    /* Internal use */
    BI_INT32 MAX_HASH_GROUP;
    BI_INT32 MAX_CACHE_NODESIZE;
    BI_INT32 CACHE_NODESHIFT;
    BI_INT32 MAX_CACHE_NODE;
    BI_BYTE   *ArvCacheTmpBmpBuff;
    BI_UINT32 *ArvHTable_check;
    BI_UINT32 *ArvHTable_check2;
    BI_UINT16 *ArvHTable_save8;
    BI_INT16  *ArvHTable_ptr;
    BI_BYTE   *ArvHTable_lru_ptr;
    BI_BYTE   *ArvCacheBuff;
    BI_INT16  *ArvCacheNode;
	ArsCacheStatus ArvCacheStatus3;
    BI_UINT32 *ArvCacheNodeCnt;
    BI_INT16  *ArvFreeHead;
    /* for BI_PROCESS_GRAYSCALE_WITH_16_LEVEL use */
#if BI_PROCESS_GRAYSCALE_WITH_16_LEVEL
    BI_UINT16 depth;
    BI_UINT16 fWidth;
    BI_UINT32 oddflag;
#endif /* BI_PROCESS_GRAYSCALE_WITH_16_LEVEL */   
} TCacheDataStructure,*PTCacheDataStructure;

#endif

typedef struct ArGetDataFunctions_
{
    BI_INT32            Mode;
    BI_VOID*            Instance;
    BIGetDataFunc       GetDataToBuffer;    /* get data to buffer */
#if FOR_ROM_POINTER_ACCESS
    BIGetDataFunc       GetDataDirect;      /* Access data direct on RAM(ROM) */
#endif
#if BI_FILE_PART_SUPPORT					/* webber 2009.04.23*/
	BI_INT32			FontBufferSize;		/* user defined font buffer size(kb)*/
	BI_BYTE				*MemAddress;		/* user defined start address*/
#endif
} ArGetDataFunctions;
#endif

#if BI_FILE_PART_SUPPORT
typedef struct UserDefinedCallbackData_ {
	BI_UINT16			   tableCount;
	BI_UINT16				 stackNum;
	BI_UINT16				 stackSize;
	BI_UINT16				 unusedStack;
	BI_BYTE					 *wrkBuffer;
	BI_UINT16				 *address;
	BI_VOID					 *fileBuffer;
	BI_UINT16				 mode;
	BI_UINT16        padding;
} UserDefinedCallbackData;
#endif
/*webber*/
#define MaxOutlinePoints 512
#define MaxOutlineContours 128
typedef struct AOutlineRecTag {
	BI_INT32	x;
	BI_INT32	y;
}AOutlineRec;
typedef struct AOutlineSlotRecTag {
	BI_INT16      n_contours;
	BI_INT16      n_points;
	AOutlineRec   points[MaxOutlinePoints];
	BI_BYTE       pointType[MaxOutlinePoints];/*0:conic, 1:on*/
	BI_INT16      contours[MaxOutlineContours];
	BI_INT32      flag;
}AOutlineSlotRec;
#if BI_EMBEDED_BMP_SUPPORT
typedef struct RbmInstanceForMfont_
{
    ArGetDataFunctions* MfontGetDataFuncs;
    BI_INT32            RbmDataOffset;
    BI_INT32            EmBmpFlag;          /* embedded bitmap size flag */
    BI_INT32            CodeType;           /* 1-->Unicode, 2-->Native */
	BI_BYTE*            RbmpInfo;           /* Rbm engine working buffer*/
} RbmInstanceForMfont;
#endif

typedef struct {
    BI_UINT32           ptr;
    union {
        BI_UINT32       IDset[2];
        struct {
            BI_UINT16   ID;
            BI_UINT16   charset;
            BI_UINT32   typeface;
        }   s;
    }   u;
}   Font_ID;

typedef  struct  TArFontMetrics_
{
    BI_UINT16           FontID;             /* Unique font ID             */
    BI_BYTE             padding1[2];        /* unused,just for four byte alignment padding */
    BI_BYTE             FontName[128];
    BI_BYTE             FamilyName[64];
    BI_BYTE             SubFamilyName[64];
    BI_UINT32           Flag;               /* BI_FLAG_XXX ,bit set       */
    BI_UINT16           UnitsPerEM;         /* EM square size             */
    BI_UINT16           FontHeight;         /* Ascender-Descender */
    BI_INT16            Ascender;           /* usually positive           */
    BI_INT16            Descender;          /* usually native             */
    BI_UINT16           InternalLeading;
    BI_UINT16           LineGap;            /* ExternalLeading            */
    BI_UINT16           Spacing;            /* Char spacing */
    BI_INT16            MaxAdvanceWidth;
    BI_INT16            MaxAdvanceHeight;
    BI_INT16            UnderlinePosition;                                              
    BI_UINT16           UnderlineThickness;
    BI_INT16            StruckOutPosition;
    BI_INT16            MaxBoundingBox [4]; /* MinX,MinY,MaxX,MaxY        */
    BI_UINT32           Weight;             /* BI_WEIGHT_XXX              */
    BI_UINT32           Style;              /* BI_STYLE_XXX , bit set     */
    BI_UINT32           UnicodeRange[4];    /* 0:Bits 0-31,1: Bits 32-63,2:
                                               Bits 64-95,3: Bits 96-127 ,
                                               bit set, truetype compatible */
    BI_UINT32           CodePageRange[2];   /* 0:Bits 0-31,1:Bits 32-63 ,
                                               bit set, truetype compatible */
    BI_UINT16           NumGlyphs;          /*include spaces              */
    BI_UINT16           FirstChar;          /* coding by font charset     */
    BI_UINT16           LastChar;           /* coding by font charset     */
    BI_UINT16           DefaultChar;        /* missing char               */
    BI_UINT16           BreakChar;          /* next line char             */
    BI_UINT16           NumFixedSizes;      /* number of embedded bitmap sizes */
    BI_UINT16*          FixedSizes;         /* n*2=height,(n*2)+1=width   */
} TArFontMetrics,*PTArFontMetrics;

#if BI_SUPPORT_K_RENDER
enum
{
    BI_STICK_GRID_FIT_MODE_AUTO             = 1,
    BI_STICK_GRID_FIT_MODE_CENTER           = 2,
    BI_STICK_GRID_FIT_MODE_GRID             = 4,
    BI_STICK_NO_GROW_HEAD                   = 0x10
};

typedef struct {
    BI_UINT16           BoldV;              /* fix 8.8 */
    BI_UINT16           BoldH;              /* fix 8.8 */
    BI_UINT16           BoldS;              /* fix 8.8 */
    BI_UINT16           Phase;              /* 0~256   */
    BI_UINT16           padding;            /* unused  */
    BI_UINT16           Gamma;
    BI_UINT32           Stick_Gray_Flag;    /* for K Rener parameter */
                                            /* bit 1~2 align mode */
                                            /*
                                            bit 1~4: stick grayscale grid fit mode
                                                        off            : bit1~4 = 0
                                                        auto mode      : bit1 = 1
                                                        center mode    : bit2 = 1
                                                        grid mode      : bit3 = 1
                                                        Reserved       : bit4
                                             bit 5: no grow head

                                             BI_STICK_GRID_FIT_MODE_AUTO                1
                                             BI_STICK_GRID_FIT_MODE_CENTER              2
                                             BI_STICK_GRID_FIT_MODE_GRID                4
                                             BI_STICK_NO_GROW_HEAD                   0x10
                                             */

} BI_WIDTH_STRUCT;
#endif /* BI_SUPPORT_K_RENDER */

#if BI_SUPPORT_FLAT_MODE
#define BI_FLAT_MODE_MAX_SECTION 16
typedef struct {
	BI_UINT16 SectionCount;
	BI_UINT16 CurrentFlag; /* bit1:Mono bit2:Gray bit3:offset% bit4:H% bit5:W% bit6:Scale Adv */
	BI_UINT16 OrgHeight;
	BI_UINT16 OrgWidth;
	BI_UINT16 StartCode[BI_FLAT_MODE_MAX_SECTION];
	BI_UINT16 EndCode[BI_FLAT_MODE_MAX_SECTION];
	BI_UINT16 Height[BI_FLAT_MODE_MAX_SECTION];
	BI_UINT16 Width[BI_FLAT_MODE_MAX_SECTION];
	BI_INT16  OffsetX[BI_FLAT_MODE_MAX_SECTION];
	BI_INT16  OffsetY[BI_FLAT_MODE_MAX_SECTION];
	BI_UINT16 Flag[BI_FLAT_MODE_MAX_SECTION];
} BI_FLAT_STRUCT;
#endif /* BI_SUPPORT_FLAT_MODE */

typedef struct {
	/* fixed internal data */
	BI_INT32            MinSeqCode;
	BI_INT32            MaxSeqCode;
    BI_INT32            SegmentOffset;
    BI_INT32            FontMetricsPtr;
    BI_INT32            FontDataPtr;
#if BI_SUPPORT_GDL_GLYPH_FORMAT
    BI_INT32            GDLTablePtr;
    BI_INT32            GDL_Min_ID;         
    BI_INT32            GDL_Max_ID;
    BI_INT32            GDL_Format;         /* format no. */
#if BI_SUPPORT_GDL_LEVEL1_CACHE
    BI_GDL_DATA_CACHE1* gld_cache1; 
#endif /* BI_SUPPORT_GDL_LEVEL1_CACHE */
#endif /* BI_SUPPORT_GDL_GLYPH_FORMAT */
#if BI_SUPPORT_HINTING
    BI_INT32            AdjDataPtr;
    BI_INT32            AdjMinSeqCode;
    BI_INT32            AdjMaxSeqCode;
    BI_INT32            AdjSegmentOffset;
    BI_INT32            AdjustSizesCount;
    BI_INT32            AdjustSizes[BI_MAX_ADJUEST_COUNT];
    BI_INT32            AdjustFlag;
    BI_INT16            AddPointCount;
    BI_INT16            DeletePointCount;
    BI_UBYTE            AddPoints[BI_MAX_ADD_POINT];    /*128*/
    BI_UBYTE            DeletePoints[BI_MAX_DEL_POINT]; /*128*/
    BI_INT16            GlyphOffestX;
    BI_INT16            GlyphOffestY;
    BI_INT32            GWidthPtr;
    BI_INT16            Gray_Stroke_Width00_Mapping_Value;
    BI_INT16            Gray_Stroke_Width01_Mapping_Value;
    BI_INT16            Gray_Stroke_Width10_Mapping_Value;
    BI_INT16            Gray_Stroke_Width11_Mapping_Value;
    BI_INT32            GWidthFlag;
#endif /* hinting */
    BI_INT32            GAdjPtr;
    BI_INT32            MonoWidthPtr;
    BI_INT32            GlobelPtr;
    BI_INT32            BBoxTblPtr;
    BI_INT32            FMetTblPtr;
    BI_INT32            BBoxErrorTblPtr;
#if ASCII_Hinting_QUALITY
    BI_INT32            GrayBBoxErrorTblPtr;
#endif
#if FOR_MONO_QUALITY_001
    BI_INT32            MonoHintTblPtr;
#endif
#if ASCII_Hinting_QUALITY
    BI_INT32            ASCIIHintTblPtr;
#endif
#if BI_SUPPORT_TYPEFACE_SCALING
	BI_INT32            TypefaceScaleTblPtr;
#endif
#if BI_SUPPORT_FLAT_MODE
	BI_INT32            FlatModeTblPtr;
	BI_FLAT_STRUCT      FlatModeData;
	BI_INT16            Flat_Offset_X;
	BI_INT16            Flat_Offset_Y;
#endif
#if BI_PROPORTIONAL_SUPPORT
    BI_INT32            MetDataPtr;
    BI_INT32            orgx;
    BI_INT32            orgy;
    BI_INT32            advx;
    BI_INT32            CoordMode;                     /* 0 --> Mode1, 1 --> Mode2 */
    BI_INT32            MetDeltaHintingFlag;
    BI_INT32            glyph_orgx_offset;
    BI_INT32            glyph_orgy_offset;
#endif
    BI_INT32            advx256;                       /* for Italic */
    BI_INT32            orgy256;                       /* for Italic */ 
#if BI_EMBEDED_BMP_SUPPORT
	RbmInstanceForMfont RbmInstance;
#else    
    BI_INT32            RbmDataOffset;
#endif
#if BI_FONT_LINK_SUPPORT
    BI_INT32            FontLinkID;
#endif
    BI_INT32            Org_Height;
    BI_INT32            Org_Width;
    BI_INT32            GlyphDataPtr;
    /* variable internal data */
    BI_INT32            Height;
    BI_INT32            Width;
    BI_INT32            GlyphHeight;
    BI_INT32            GlyphWidth;
    /* tempary ---glyph buffer */
    BI_BYTE*            glyph;
    BI_Raster           raster;
    BI_Raster_Funcs     raster_func;
   
    /* for header */
    BI_UBYTE            MBF_Version_Major;
    BI_UBYTE            MBF_Version_Minor;
    BI_UBYTE            MBF_Version_Release;
    BI_UBYTE            MBF_Version_Build;
    BI_UINT32           DisplayType;
    BI_UINT32           GlyphType;
    BI_UINT32           Most_Freq_Stroke;
#if BI_CODE_SYSTEM_SUPPORT
    BI_UINT32           Codepage;
#endif    
    BI_BYTE             FaceName[16];
#if BI_SUPPORT_K_RENDER
    BI_INT32            GrayParamTblPtr;
    BI_UINT16           BoldV;              /* fix 8.8 */
    BI_UINT16           BoldH;              /* fix 8.8 */
    BI_UINT16           BoldS;              /* fix 8.8 */
    BI_UINT16           Stick_Gray_Flag;    /* for K Rener parameter */
    BI_UINT16           Phase;
    BI_UINT16           padding_after_Pahse;
    BI_WIDTH_STRUCT     Stroke_Width[BI_GRAYSCALE_MAX_SIZE+1];
#else
    BI_UBYTE            BoldV;
    BI_UBYTE            BoldH;
    BI_UBYTE            BoldS;
    BI_UBYTE            PaddingByte;        /* unused,just for four byte alignment padding */
#endif
    BI_INT32            GrayLevel;     
#if BI_MAPPING_TABLE_SUPPORT
    BI_INT32            MapTableOffset;
    /* Cached info for BIgetGlyIdxU () */
    BI_UINT32           LastMapOffs;
    BI_UINT16           LastMapType;
    BI_UINT16           LastMapSegCount;
#define BI_LASTMAPSEG_CACHESIZE 36
    BI_UINT16           LastMapSegInfo [BI_LASTMAPSEG_CACHESIZE *3];
#endif
    /* Transform */
#if BI_TRANSFORM_SUPPORT
    BI_Matrix           matrix;
#endif
#if BI_VERTICAL_WRITING
    BI_Matrix2          matrix2;
#endif
#if BI_SET_WEIGHT
    BI_INT32            adjoff;
#endif
#if BI_CALLBACK_ROUTINE
    ArGetDataFunctions* GetDataFuncs;
#endif
    BI_INT16            OffsetX;
    BI_INT16            OffsetY;
    TArFontMetrics      FontMetrics;
    BI_UINT16           BaseSize;
    BI_UBYTE            Padding2[2];        /* unused,just for four byte alignment padding */
    BI_UINT32           option_flags;
    BI_INT32            flags;
#if BI_BITMAP_EMBOLDEN_SUPPORT
#if BI_SUPPORT_K_RENDER
    BI_UINT16           NoEmboldenFlag;
    BI_UINT16           RegularBoldV;       /* fix 8.8 */
    BI_UINT16           RegularBoldH;       /* fix 8.8 */
    BI_UINT16           RegularBoldS;       /* fix 8.8 */
#else
    BI_UBYTE            NoEmboldenFlag;
    BI_UBYTE            RegularBoldV;
    BI_UBYTE            RegularBoldH;
    BI_UBYTE            RegularBoldS;
#endif /* BI_SUPPORT_K_RENDER */
    BI_INT32            fix_pitch_move_glyph_when_bold_flags;
    BI_INT32            BitmapEmboldenFlag;
#endif /* BI_BITMAP_EMBOLDEN_SUPPORT */

#if BI_SUPPORT_RADICAL_BASE_FONT
    BI_INT32            RCDTablePtr;
    BI_INT32            RCD_Min_ID;
    BI_INT32            RCD_Max_ID;
    BI_INT32            RCD_Format;
    BI_INT16            RadicalOffsetX;
    BI_INT16            RadicalOffsetY;

    BI_INT32            LCHTablePtr;               /* 2009/04/21 johnny_chen*/
    BI_INT32            LCH_Min_ID;
    BI_INT32            LCH_Max_ID;
    BI_INT32            LCH_Format;

    BI_INT32            RadicalNo;                 /* Number of radical in this font */
#endif
    BI_INT32            GLEmboldenWidth; 
#if BI_GDL_HINTING
    BI_INT32            GDLParamTblPtr;
    BI_INT32            GDLHintTblPtr;
    BI_INT32            GDLHintMaxLength;          /* reference MaxHintDataLength in GDHT */
    BI_BYTE*            GDLHintBufferPtr;          /* reference MaxHintDataLength in GDHT */
    TGDL_Param          GDL_Param;
    TGDL_Hint_Size_Index GDL_Size_Index;
    TGDL_Hint_Data      GDL_Hint_Data;
#endif
#if BI_KANJI_HINTING
    BI_UBYTE            NoConnectLineH[256/8];
    BI_UBYTE            NoConnectLineW[256/8];
    BI_INT32            KanjiHintTableBase;
    BI_INT32            KanjiHintMinCode;
    BI_INT32            KanjiHintMaxCode;
    BI_INT32            KanjiHintMaxSizeBase;
#endif
} BI_InternalFormat,*PBI_InternalFormat;

typedef struct {
    BI_UINT32           StrokeNo;
    BI_INT16            px;
    BI_INT16            py;
#if BI_SUPPORT_HINTING
	BI_UBYTE            StatusIndex;        /* 0xff-->no status */
    BI_BYTE             padding[3];         /* unused,just for four byte alignment padding */
#endif
#if BI_KANJI_HINTING
    BI_BYTE             canceled;           /* boolean: stroke canceled */
    BI_UBYTE            AlignSubstroke;     /* relavant when ForcedAlignType != 0 */
    BI_INT16            ForcedAlignType;    /* KHG_INCREASE, KHG_DECREASE, KHG_INCREASE<<2, KHG_DECREASE<<2 */
#endif
#if BI_SUPPORT_GDL_GLYPH_FORMAT
    /* for GDL */
    BI_BYTE             padding_gdl[2];     /* unused,just for four byte alignment padding */
    BI_UBYTE            key_count;
    BI_UBYTE            width_count;
    BI_INT16            px1[8];
    BI_INT16            py1[8];
    BI_UBYTE            w[8];
    BI_INT32            StrokeOffset;
#endif
} BI_StrokeFormat;

#if BI_SUPPORT_HINTING
typedef struct {                            /* must four byte alignment */
    BI_UINT32           ExStrokeNo; 
    BI_INT32            SubstrokeAdjFlag;
    BI_UBYTE            StrokeAdj[BI_MAX_SUB_ICON]; /* 0 --> the stroke ,1~ --> substroke 1*/
#if BI_SUPPORT_K_RENDER
    BI_UINT16           BoldValueV[BI_MAX_SUB_ICON];
    BI_UINT16           BoldValueH[BI_MAX_SUB_ICON];
    BI_UINT16           BoldValueS[BI_MAX_SUB_ICON];
#else
    BI_UBYTE            BoldValueV[BI_MAX_SUB_ICON];
    BI_UBYTE            BoldValueH[BI_MAX_SUB_ICON];
    BI_UBYTE            BoldValueS[BI_MAX_SUB_ICON];
#endif
    BI_INT16            KeyPointAdjX;       /* offset +/- */
    BI_INT16            KeyPointAdjY;
	BI_BYTE             ControlPointAdjX[MAX_CONTROL_POINT];
    BI_BYTE             ControlPointAdjY[MAX_CONTROL_POINT];
    /* for grayscale width control */
    BI_BYTE             Gray_Stroke_Width_Buffer[BI_GRAY_ADJ_MAX_STROKE_BUFFER];
#if BI_COPY_INFORMATION
    BI_UINT32           CopyStrokeNo;
    BI_UBYTE            Copypx;
    BI_UBYTE            Copypy;
    BI_UBYTE            Padding[2];    /* for four byte alignment */
#endif /* BI_COPY_INFORMATION */
}
BI_StatusFormat;
#endif /* Hinting */



typedef struct  TArCharMetrics_
{
    BI_INT16            OriginX;	    /* origin X postion of font in buffer */
    BI_INT16            OriginY;            /* origin Y postion of font in buffer */
    BI_INT16            Advance;            /* next character origin distance */
    BI_INT16            BBoxUpperLeftX;     /* bbox upper left X position */
    BI_INT16            BBoxUpperLeftY;     /* bbox upper left Y position */
    BI_UINT16           BBoxWidth;          /* bbox horizontal width */
    BI_UINT16           BBoxHeight;         /* bbox vertical height */
#if BI_VERTICAL_WRITING
    BI_INT16            orgx;            /* next character origin distance */
    BI_INT16            orgy;            /* next character origin distance */
    BI_INT16            advx;            /* next character origin distance */
    BI_INT16            advy;            /* next character origin distance */
#endif
/* unused ,just for four byte alignment padding */
    BI_BYTE 	        padding[2];
} TArCharMetrics,*PTArCharMetrics;

#if BI_SET_WEIGHT
typedef struct  ArWeightEntry_
{
    BI_INT16            size;
    BI_INT16            hstem;
    BI_INT16            vstem;
    BI_INT16            sstem;
} TArWeightEntry, *PTArWeightEntry;

typedef struct  ArFontWeight_
{
    BI_INT32            entrycnt;
    TArWeightEntry      entry[16];
} TArFontWeight, *PTArFontWeight;
#endif /* BI_SET_WEIGHT */

typedef struct {
    /* memory manage */
    TArMem              memory;
    /* stroke data */
    BI_INT16            StrokeCount;
    BI_INT16            pitch;
    BI_INT16            BuffWidth;          /* buffer width  */
    BI_INT16            BuffHeight;         /* buffer height */
    BI_BYTE*            bitmap;
    /* internal use */
    BI_INT32            AvailabileFonts;
    BI_StrokeFormat     *Strokes;
#if BI_SUPPORT_HINTING
    BI_StatusFormat     *Status;
    BI_UINT32            StatusCount;
#endif
    Font_ID             *ID[BI_MAX_FONT];
    BI_InternalFormat   *BI_Internal;
    BI_InternalFormat   *BI_Internals[BI_MAX_FONT];
#if !BI_STROKE_NO_COMPRESS
    BI_BYTE             *GlyphDataBuffer;
#endif
#if BI_CALLBACK_ROUTINE
    ArGetDataFunctions  *GetDataFuncs;
#endif
#if BI_FILE_ACCESS_SUPPORT
    FileAccessInstance  FileAccessInst;
#endif
    BI_INT32            ClearRasterFlag;
    BI_INT32            style_flag;
    BI_INT32            style_outline_width;
#if BI_ATTRIBUTE_3D
    BI_UINT32           attribute_type;     /* For 3D style, internal variable*/
    BI_INT32            style_depth_3D;
    BI_INT32            style_direction_3D;
#endif    
    BI_INT32            user_default_char;
#if BI_SUPPORT_GAMMA_CORRECTION
	BI_INT32            GammaValue;
	BI_INT32            Custom_GammaValue;
#if BI_SUPPORT_MULTI_GRAY_TABLE
    BI_INT32            GammaValue2;
#endif /* BI_SUPPORT_MULTI_GRAY_TABLE */
#endif /* BI_SUPPORT_GAMMA_CORRECTION */
#if BI_FOR_MULTI_TASKING_OPTION
    /* used for record ArSetFont multi tasking */
    BI_UINT16           multi_ID;	        /* switch font by ID          */
    BI_UINT16           multi_CharSet;          /* BI_SET_CHARSET_XXX         */
    BI_UINT32           multi_Style;            /* BI_STYLE_XXX , bit set     */
    BI_UINT32           multi_OutlineWidth;     /* For Outline style          */
    BI_UINT32           multi_OutputFormat;     /* BI_OUTPUT_FORMAT_XXX       */
    BI_UINT16           multi_GrayLevel;        /* BI_SET_GRAY_XXX            */
    BI_UINT16           multi_Rotate;           /* BI_SET_ROTATE_XXX          */
    BI_UINT16           multi_Width;            /* set char width             */
    BI_UINT16           multi_Height;           /* set char height            */
    BI_UINT32           multi_flag;             /* set option flag            */
#endif

#if BI_FOR_PROBLEM_FILE_ACCESS
    /* file access buffer */
    BI_UBYTE            FileAccessBuffer[512];
#endif

#if BI_BITMAP_FONT_CACHE
    TCacheDataStructure cds;
    BI_UINT16  GLIDidx;
    BI_INT16   CacheHitFlag; /* 0--> not hit, 1-->hit */
#if CACHE_NEW_API
    ArsCacheBuff* ArvCacheBuff2;
    ArsCacheStatus* ArvCacheStatus2;
#else
    BI_INT16   CacheEnable;
#endif  /* CACHE_NEW_API */

#endif
    BI_INT16  BBoxMinX;
    BI_INT16  BBoxMinY;
    BI_INT16  BBoxMaxX;
    BI_INT16  BBoxMaxY;
    BI_INT32  bbox_flag;
    BI_UINT16 MinBuffHeight;
    BI_UINT16 MinBuffWidth;
#if BI_KERNING_PAIR
    BI_INT32  krn2_off;
    BI_INT32  krn2_flag;
    BI_INT32  krn2_base;
    BI_INT32  krn2_minisize;
    BI_INT32  krn2_startcode;
    BI_INT32  krn2_endcode;
    BI_UINT16 krn2_count;
    BI_UINT16 krn2_prevcode;
#endif
#if BI_VERTICAL_WRITING
#if BI_ROTATE_USE_VERTICAL
    BI_INT32  RotateFlag;
#endif
    BI_INT32  vtwg_off;
    BI_INT32  seqcode2;
    BI_UINT16           VerticalEnable;     /* BI_SET_vertical_writing_XXX          */
    BI_UINT16           VerticalMode;       /* BI_SET_vertical_writing_XXX          */
#endif
#if BI_SHARE_SIZE
    BI_INT32  sharesize_off;
    BI_INT32  sharesize_cnt;
#endif
#if FOR_MONO_QUALITY_001
    TMono_Hinting       monohint;
    BI_UBYTE            hint_bin[sizeof(TMono_Hinting)];
    BI_UINT32           hint_bin_length;
#endif /* FOR_MONO_QUALITY_001 */
#if BI_IMPROVE_SPEED_MET2
    BI_INT32  speedarg[256][10]; /* 0:w 1:h 2:style 3:orgx 4:orgy 5:advx */
                                 /* 6:BBoxUpperLeftX 7:BBoxUpperLeftY    */
                                 /* 8:BBoxWidth 9:BBoxHeight             */
#endif
#if BI_IMPROVE_SPEED_GLYPH_INDEX
    BI_INT32  speedgly[256];
#endif
#if BI_EMBEDDED_GRAY_BITMAP
    BI_INT32  ebgm_off;
    BI_INT32  ebmm_off;
    BI_INT32  seqcode;
#endif
#if BI_SUPPORT_GDL_GLYPH_FORMAT
	BI_VOID*            gdl_var;
	BI_INT32*           path_buff_ptr;
	BI_BYTE*            gdl_data_buff_ptr;
#endif  /* BI_SUPPORT_GDL_GLYPH_FORMAT */
    BI_INT32            clip_flag;
	BI_INT16            clip_x;
	BI_INT16            clip_y;
	BI_INT16            clip_width;
	BI_INT16            clip_height;
	BI_INT32            sequence_code;
#if !BI_GDL_HINTING /* for WGTB table */
        BI_INT32            adjmode;
        BI_INT32            adjoff;
#endif
#if BI_SET_WEIGHT
        TArFontWeight       adjtable;
#endif
#if ASCII_Hinting_QUALITY
    TASCII_Hinting ASCIIHint;
#endif /* ASCII_Hinting_QUALITY */
#if BI_SUPPORT_TRANSFORM_MATRIX
    BI_Matrix           matrix;
#endif
#if BI_SUPPORT_MULTI_GRAY_TABLE
	BI_INT32 FontColor;
	BI_INT32 BackColor;
	BI_INT32 MTGY_Table_Offset;
        BI_INT16 MultiGrayIndex;            /* record use multi gray table index */
        BI_INT16 padding;                   /* unused,just for four byte alignment padding */
#endif /* BI_SUPPORT_MULTI_GRAY_TABLE */
#if BI_SUPPORT_BITMAP_ICON
	BI_INT32 BMIC_Table_Offset;
#endif /* BI_SUPPORT_BITMAP_ICON */
    /* Johnny */
    BI_INT16    OffsetX256;
    BI_INT16    OffsetY256;
#if BI_DECODING_GRAY_BITMAP
  BI_BYTE       ebgm_reftbl[256*16];
  BI_BYTE       ebgm_cprs[32*32*2];
#endif
  BI_BYTE       ebgm_outbmp[32*32];
#if BI_SUPPORT_4_16_GRAY_LEVELS
  BI_INT32      grayshift;
  BI_INT32      graymask;
#endif
#if BI_GDL_CLOSURE_TYPE
    GDL_INT32   substrokecnt;
    GDL_INT32   closure_type[16];
#endif
} BI_FontFormat,TArVarGlobalAll,*PTArVarGlobalAll;


/*Unicode encoding must need code table,
  the font size bigger than native encoding*/
typedef struct  ArFontInfo_
{
    /* used for ArInitFont*/
    BI_UINT16           RomCount;           /* rom count                  */
    BI_UINT16           FontCount;          /* available fonts count      */
    BI_BYTE*            RomAddr;            /* rom starting address array */
    BI_BYTE*            WorkBuff;           /* working buffer             */
    BI_UINT32           WorkBuffSize;       /* working buffer size        */
    /* get data callback functions */
    ArGetDataFunctions GetDataFunc;
    /* Output ,feedback from ArInitFont */
    BI_UINT16*          FontIDList;         /* all ID list array that
                                                   available fonts            */

    /* used for ArSetFont*/
    BI_UINT16           ID;	            /* switch font by ID          */
    BI_UINT16           CharSet;            /* BI_SET_CHARSET_XXX         */
    BI_UINT32           Style;              /* BI_STYLE_XXX , bit set     */
    BI_UINT32           OutlineWidth;       /* For Outline style */
#if BI_ATTRIBUTE_3D
    BI_UINT32           Depth_3D;           /* For 3D style */
    BI_UINT32           Direction_3D;       /* For 3D style */
#endif
    BI_UINT32           OutputFormat;       /* BI_OUTPUT_FORMAT_XXX       */
    BI_UINT16           GrayLevel;          /* BI_SET_GRAY_XXX            */
    BI_UINT16           Rotate;             /* BI_SET_ROTATE_XXX          */
    BI_UINT16           Width;              /* set char width             */
    BI_UINT16           Height;             /* set char height            */
    BI_UINT32           flag;               /* set option flag            */

#if BI_VERTICAL_WRITING
    BI_UINT16           VerticalEnable;     /* BI_SET_vertical_writing_XXX          */
    BI_UINT16           VerticalMode;       /* BI_SET_vertical_writing_XXX          */
#endif
    /* Only for internal use */
    TArVarGlobalAll Internal;               /*buffer for global variable,
                                              refer to struct TArVarGlobalAll*/
} TArFontInfo, *PTArFontInfo;

typedef struct  ArCharInfo_
{
    /* Input ,used for ArGetFont */
    BI_UINT16           Code;               /* char code                  */
    BI_UINT16           BuffWidthB;         /* width of output bitmap buffer
                                                   in bytes                   */
    BI_BYTE*            BmpBuff;            /* output bitmap buffer       */
    BI_UINT32           BuffHeight;         /* height of output bitmap buffer */
    BI_INT16            StartX;             /* set origin X */
    BI_INT16            StartY;             /* set origin Y */
    BI_UINT32           flag;               /* BI_ FLAG_GET_FONT_ XXX ,bit set */

    /* Output , freedback from ArGetFont */
    TArCharMetrics      CharMetrics;
} TArCharInfo, *PTArCharInfo;

/*********************
 *  I/O callback function
 **********************/
#ifdef	__cplusplus
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


/*********************
 *  Embedded Bitmap API
 **********************/
#if BI_MAPPING_TABLE_SUPPORT
BI_INT32 BIgetGlyIdxU (BI_UINT16 ucode ,BI_UINT32 mapoffset,PBI_InternalFormat pint);
#endif

#if BI_EMBEDED_BMP_SUPPORT
BI_VOID  RbmpGetDataProc(BI_VOID *RbmpInstance, BI_UINT32 RbmpOffs ,BI_VOID *dataBuf ,BI_UINT16 dataLen);
#endif

/*********************
 *  BI_LIB API
 **********************/


/* BI_VOID   RelocateStroke(BI_INT16 H,BI_INT16 W,BI_INT16 OKeyX,BI_INT16 OKeyY,BI_INT16 KeyX,BI_INT16 KeyY,BI_INT16 adj,BI_INT16 *ox,BI_INT16 *oy,BI_INT16 *dx,BI_INT16 *dy);*/
BI_INT16  DrawCharB(PTArVarGlobalAll pp);
BI_INT16  Ar_BI_Init(PBI_InternalFormat pint,BI_INT32 addr);
BI_VOID   Ar_BI_InitStatusAll(PTArVarGlobalAll pp);
BI_INT16  Ar_BI_SetSize(PTArVarGlobalAll pp,BI_INT16 h,BI_INT16 w);
BI_INT32  Ar_BI_GetFont(PTArVarGlobalAll pp,BI_INT32 code);
BI_INT16  Ar_BI_GetStatus(PTArVarGlobalAll pp,BI_INT32 code,BI_INT32 DisplayFlag);
BI_INT32  Ar_BI_GetFontMetrics(PTArVarGlobalAll pp,TArFontMetrics** FontMetrics,BI_UINT16 FontID);
BI_INT32  Ar_BI_GetFontMetricsInternal(PBI_InternalFormat pint,TArFontMetrics* FontMetrics);
BI_INT16  Ar_BI_CheckGlyph(PTArVarGlobalAll pp,BI_INT32 code);
#if BI_PROPORTIONAL_SUPPORT
BI_INT16  Ar_BI_ProcessMet( PTArVarGlobalAll pp,BI_INT32 code,BI_INT32 sizeW,BI_INT32 sizeH,BI_INT32 style,BI_INT32 graylevel );
BI_INT16  Ar_BI_GetMet(PTArVarGlobalAll pp,BI_INT32 code,BI_INT32 size,BI_INT32 sizeH,BI_INT32 *OrgX,BI_INT32 *BaseLine,BI_INT32 *AdvX);
BI_INT16  Ar_BI_GetMet2(PTArVarGlobalAll pp,BI_INT32 code,BI_INT32 size,BI_INT32 sizeH,BI_INT32 *OrgX,BI_INT32 *OrgY,BI_INT32 *AdvX,BI_INT32 *OrgY256,BI_INT32 *AdvX256);
BI_INT16  Ar_BI_GetFMET22(PTArVarGlobalAll pp,BI_INT32 sizeW,BI_INT16* lsb,BI_INT16* rsb);
BI_INT16  Ar_BI_GetFMET(PTArVarGlobalAll pp,BI_INT32 sizeW,BI_INT16* lsb,BI_INT16* rsb);
#endif
BI_INT16 Ar_BI_GetBBox(PTArVarGlobalAll pp,BI_INT32 code,BI_INT32 sizeW,BI_INT32 sizeH,BI_UINT32 *MinX,BI_UINT32 *MinY,BI_UINT32 *MaxX,BI_UINT32 *MaxY);
BI_INT16 Ar_BI_GetBBoxError(PTArVarGlobalAll pp,BI_INT32 code,BI_INT32 size,BI_INT32 *eMinX,BI_INT32 *eMinY,BI_INT32 *eMaxX,BI_INT32 *eMaxY,BI_INT32 GrayLevel);
BI_INT16  DrawCharB(PTArVarGlobalAll pp);
BI_VOID   Ar_BI_Done(PTArVarGlobalAll pp);
BI_INT16  Ar_BI_GetGrayAdj(PTArVarGlobalAll pp,BI_INT32 size,BI_INT16 *Density,BI_INT16 *boldw,BI_INT16 *FontType,
                           BI_INT16 *LetterSize,BI_INT16 *GrayToMonoFlag,BI_INT16 *Width00,
                           BI_INT16 *Width01,BI_INT16 *Width10,BI_INT16 *Width11);
BI_INT16  Ar_BI_GetGrayWidth(PTArVarGlobalAll pp,BI_UINT16 code,BI_BYTE* StrokeBuffer);
BI_INT16  Ar_BI_GetGlobel(PTArVarGlobalAll pp,BI_INT32 code,BI_INT32 DisplayFlag);
BI_INT16  Ar_BI_GetGlobel_NoEmboldenFlag(PTArVarGlobalAll pp,BI_INT32 code);
BI_INT16  Ar_BI_GetStrokeWidth(PTArVarGlobalAll pp,BI_INT32 size,BI_UINT32 TableNo,BI_UINT32* V,BI_UINT32* H,BI_UINT32* S);
BI_INT32  Ar_BI_GetExtTableOffset(PBI_InternalFormat pint,BI_INT32 offset,BI_BYTE* Tag);
BI_INT16  Ar_BI_GetMinBufferSize(PTArVarGlobalAll pp,BI_UINT16 Width,BI_UINT16 Height,BI_UINT16* BuffWidthB,BI_UINT16* BuffHeight);
#if FOR_MONO_QUALITY_001
BI_INT16  Ar_BI_GetMonoHintData(PTArVarGlobalAll pp,BI_INT32 code);
#endif
#if BI_GRAYSCALE_OUTLINE
BI_INT32  Ar_BI_Grayscale_Outline(PTArVarGlobalAll pp);    
#endif
#if BI_SUPPORT_RADICAL_BASE_FONT
BI_INT32  Ar_BI_GetRCD_Offset(PTArVarGlobalAll pp,BI_INT32 composit_id, BI_INT32* Radical_Data_Offset);
BI_INT32  Ar_BI_GetRCD_Radical_Data(PTArVarGlobalAll pp, BI_INT32 Radical_Data_Offset, BI_INT32* Count, BI_UINT16* flag);
BI_INT32  Ar_BI_GetRCD_Radical(PTArVarGlobalAll pp, BI_INT32 Radical_Data_Offset, BI_INT32 No,
                               BI_INT16 flag, BI_INT32* Radical_ID, BI_INT32* OffsetX, BI_INT32* OffsetY);
/* 2009/04/21 johnny_chen */
BI_INT32  Ar_BI_GetLCH_Offset(PTArVarGlobalAll pp,BI_INT32 composit_id, BI_INT32* LocalHinting_Data_Offset, BI_INT32* MinLCHID, BI_INT32* MaxLCHID, BI_INT32* MinLCHSizeH, BI_INT32* MaxLCHSizeH, BI_INT32* MinLCHSizeW, BI_INT32* MaxLCHSizeW);
BI_INT32  Ar_BI_GetLCH_Hinting_Data(PTArVarGlobalAll pp, BI_INT32 LocalHinting_Data_Offset, BI_INT32 Radical_Count, BI_INT32 No, BI_INT32 Radical_ID, BI_INT32* LCH_OffsetX, BI_INT32* LCH_OffsetY, BI_INT32* change_radical);
#endif
#if BI_SUPPORT_K_RENDER
BI_INT16 Ar_BI_GetGrayParam(PTArVarGlobalAll pp,BI_UINT16 size,
                            BI_UINT16* V,BI_UINT16* H,BI_UINT16* S,
                            BI_UINT16* Gamma,BI_UINT32* flag,BI_UINT16* Phase);
BI_INT16 Ar_BI_GetDefaultGrayParam(BI_UINT16 size,
                                   BI_UINT16* V,BI_UINT16* H,BI_UINT16* S,
                                   BI_UINT16* Gamma,BI_UINT32* flag,BI_UINT16* Phase);                             
#endif

#if BI_TRANSFORM_SUPPORT
BI_VOID BI_Vector_Transform( BI_INT16 *x ,BI_INT16 *y,BI_Matrix*  matrix );
#endif

#if BI_GDL_HINTING
BI_INT16 Ar_BI_GetGDLParam( PTArVarGlobalAll pp,BI_UINT16 size,
							BI_UBYTE* Level,BI_UBYTE* V,BI_UBYTE* H,BI_UBYTE* S,
							BI_UBYTE* tGamma,BI_UINT16* flag );
#endif

/* BI external routing */
#ifdef __cplusplus
extern "C"
 {
#endif
BI_INT16 Ar_BI_SetGlyphSize(PTArVarGlobalAll pp,BI_INT16 sh,BI_INT16 sw);
BI_INT32 ArInitFont(PTArFontInfo ArFontInfo);
BI_INT32 ArSetFont(PTArFontInfo ArFontInfo);
BI_INT32 ArGetFont(PTArFontInfo ArFontInfo,PTArCharInfo ArCharInfo,BI_INT32 GetMode);
BI_INT32 ArGetWrk(BI_INT32 height,BI_INT32 width,BI_INT32 grayscale,BI_INT32 font_num);
BI_INT32 ArGetFontMetrics(PTArFontInfo ArFontInfo,BI_UINT16 FontID,PTArFontMetrics* FontMetrics);
BI_INT32 ArGetCharWidth(PTArFontInfo ArFontInfo,BI_UINT16 Code);
#if BI_SUPPORT_TRANSFORM_MATRIX
BI_INT32 ArGetCharWidth2(PTArFontInfo ArFontInfo,BI_UINT16 Code,BI_INT16 *advx,BI_INT16 *advy);
#endif
BI_INT32 ArGetGlyphIndex(PTArFontInfo ArFontInfo,BI_UINT16 Code);
BI_INT32 ArCheckGlyph(PTArFontInfo ArFontInfo,BI_UINT16 code);
BI_INT32 ArCheckGlyph2(PTArFontInfo ArFontInfo,PTArCharInfo ArCharInfo,BI_UINT16 code);
BI_INT32 ArGetMinBmpBufferSize(PTArFontInfo ArFontInfo,BI_UINT16* BuffWidth,BI_UINT16* BuffHeight);
BI_INT32 ArGetMinBufferSize(PTArFontInfo ArFontInfo,BI_UINT16* BuffWidthB,BI_UINT16* BuffHeight);
BI_INT32 ArGetFontHeight(PTArFontInfo ArFontInfo);
BI_INT32 ArGetBaselinePos(PTArFontInfo ArFontInfo);
BI_INT32 ArGetCharIndex(PTArFontInfo ArFontInfo,BI_UINT16 Code);
BI_VOID  ArGetEngineVer(BI_BYTE* Major,BI_BYTE* Minor,BI_BYTE* Release,BI_BYTE* Build);
BI_VOID  ArGetSupportFontVer(BI_BYTE* Major,BI_BYTE* Minor,BI_BYTE* Release,BI_BYTE* Build);
BI_VOID  ArGetFontVer(PTArFontInfo ArFontInfo,BI_BYTE* Major,BI_BYTE* Minor,BI_BYTE* Release,BI_BYTE* Build);
BI_INT32 ArSetDefaultChar(PTArFontInfo ArFontInfo,BI_UINT16 code);
BI_INT32 ArSetGamma( PTArFontInfo ArFontInfo, BI_INT32 GammaValue );
#if BI_VERTICAL_WRITING
BI_INT32   ArSetVerticalWriting(PTArFontInfo ArFontInfo,BI_INT32 enable,BI_INT32 mode);
#endif
#if FOR_MONO_QUALITY_001
BI_INT32 RcParseHint(BI_UBYTE *bptr,PTMono_Hinting monohintp);
#endif
#if BI_SUPPORT_GDL_GLYPH_FORMAT
BI_INT16 Ar_BI_GetGDLData(PTArVarGlobalAll pp,BI_INT32 stk_id, BI_INT32 stk_offset);
BI_INT16 Ar_BI_GetGDLValue(PTArVarGlobalAll pp,BI_INT32 stk_id,BI_INT16* Key_Count,BI_INT16* Width_Count,BI_INT32* Stk_Offset);
BI_INT16 Ar_BI_ParseGDL(PTArVarGlobalAll pp,BI_INT16 stk_no);
#endif
#if BI_BITMAP_EMBOLDEN_SUPPORT
BI_INT16 Ar_BI_Draw_Bold(PTArVarGlobalAll pp);
#endif

#if BI_BITMAP_FONT_CACHE
BI_INT32 ArSetFontCache(PTArFontInfo ArFontInfo,ArsCacheBuff *vCacheBuff,ArsCacheStatus *vCacheStatus);
BI_INT32 ArFontCacheInit(PTArFontInfo ArFontInfo,BI_BYTE* CacheBuffer,BI_INT32 CacheBufferLength);
BI_INT32 ArFontCacheSetNodeSize(PTArFontInfo ArFontInfo,BI_INT32 nodesize);
BI_INT32 ArFontCacheSetEntryCount(PTArFontInfo ArFontInfo,BI_INT32 entrycount);
BI_INT32 ArFontCacheStart(PTArFontInfo ArFontInfo);
BI_INT32 ArFontCacheEnable(PTArFontInfo ArFontInfo,BI_INT16 enable);
#endif
BI_INT32 ArGetExtTableOffset(PTArFontInfo ArFontInfo,BI_BYTE* Tag);

#if BI_EMBEDED_BMP_SUPPORT
BI_INT32 getGlyIdxU(BI_UINT16 ucode ,BI_UINT32 mapoffset, char *WorkBuf);
#endif
BI_UINT16 ICode_seq2(BI_UINT16 Bcode ,BI_INT16 tcodePage);

#if BI_SET_WEIGHT
BI_INT32   ArSetWeight(PTArFontInfo ArFontInfo,PTArFontWeight ArFontWeight,BI_INT32 mode);
#endif
#if BI_KERNING_PAIR
BI_INT32   ArGetKerning(PTArFontInfo ArFontInfo,BI_UINT16 LeftCode,BI_UINT16 RightCode,BI_INT16 *KernValue,BI_INT16 KernMode);
#endif

#if BI_SUPPORT_K_RENDER
BI_INT32   ArGetStrokeWidth(PTArFontInfo ArFontInfo, BI_INT32 size, BI_INT32 flag, BI_UINT16* V, BI_UINT16* H, BI_UINT16* S);
BI_INT32   ArSetStrokeWidth(PTArFontInfo ArFontInfo, BI_INT32 size, BI_INT32 flag, BI_UINT16 V, BI_UINT16 H, BI_UINT16 S);
BI_INT32   ArGetGrayRenderFlag(PTArFontInfo ArFontInfo, BI_INT32 size, BI_INT32* flag);
BI_INT32   ArSetGrayRenderFlag(PTArFontInfo ArFontInfo, BI_INT32 size, BI_INT32 flag);
BI_INT32   ArGetGammaBySize(PTArFontInfo ArFontInfo, BI_INT32 size, BI_UINT16* gamma);
BI_INT32   ArSetGammaBySize(PTArFontInfo ArFontInfo, BI_INT32 size, BI_UINT16 gamma);
BI_INT32   ArGetPhase(PTArFontInfo ArFontInfo, BI_INT32 size, BI_UINT16* Phase);
BI_INT32   ArSetPhase(PTArFontInfo ArFontInfo, BI_INT32 size, BI_UINT16 Phase);
#endif

#if ASCII_Hinting_QUALITY
BI_INT32 Ar_BI_GetAsc(PTArVarGlobalAll pp,BI_INT32 code);
BI_INT16 Ar_BI_GetASCFromBBox(PTArVarGlobalAll pp,BI_INT32 code,BI_INT32 sizeW,BI_INT32 sizeH);
#endif

#if BI_SUPPORT_MULTI_GRAY_TABLE
BI_INT32   ArSetGrayLevel(PTArFontInfo ArFontInfo, BI_INT32 FontColor, BI_INT32 BackColor);
#endif
#if BI_SUPPORT_BITMAP_ICON
BI_INT16 Ar_BI_GetBmicParam(PTArVarGlobalAll pp, BI_UINT16 charSize, PTArCharInfo ArCharInfo, BI_BYTE* tempbuf);
#endif

#if BI_GDL_HINTING
BI_INT16 Ar_BI_GDL_Hint_Init(TGDL_Hint_Data* ghd);
BI_INT16 Ar_BI_GDLSetting(PTArVarGlobalAll pp, BI_UINT16 scode);
BI_INT16 Ar_BI_GDL_Hint_Parser(BI_BYTE* hint_data,BI_INT32 gdl_hint_data_length,TGDL_Hint_Data* ghd);
BI_INT16 Ar_BI_GDL_Hint_Process_CP_MOVE( BI_INT32 stroke_no , BI_INT32 SubCount ,BI_BYTE** outGlyph ,
										 const TGDL_Hint_Data *GDL_Hint_Data );
BI_INT16 Ar_BI_GDL_Hint_Process_Substroke_MOVE( BI_INT32 stroke_no , BI_INT32 SubCount ,BI_BYTE** outGlyph ,
												const TGDL_Hint_Data *GDL_Hint_Data );
BI_INT16 Ar_BI_GDL_Hint_Process_Stroke_Width( BI_INT32 stroke_no ,
											  BI_INT32 *vstem , BI_INT32 *hstem , BI_INT32 *sstem ,
											  const TGDL_Hint_Data *GDL_Hint_Data  );
BI_INT16 Ar_BI_GDL_Hint_Process_Add_Point( BI_UBYTE* bmpbuf, BI_INT32 BufferHeight,
										   BI_INT32 pitch,BI_INT32 offsetx,BI_INT32 offsety ,
										   BI_INT32 GammaValue,
										   const TGDL_Hint_Data *GDL_Hint_Data );
BI_INT16 Ar_BI_Check_GDL_Hint_Del_SubStroke( BI_INT32 stroke_no, BI_INT32 sub_stroke_no,
                                           const TGDL_Hint_Data *GDL_Hint_Data );
#endif
#if BI_SUPPORT_TRANSFORM_MATRIX
BI_INT32   ArSetTransformMatrix(PTArFontInfo ArFontInfo,BI_TrnMatrix *ArTrmMtx, BI_INT32 mode);
#endif

#if BI_SUPPORT_FLAT_MODE
BI_INT32 Ar_BI_CheckAndSetFlatMode( PTArVarGlobalAll pp, BI_UINT16 scode );
#endif

#ifdef __cplusplus
}
#endif

#endif   /*#ifndef _BI_LIB_INCLUDED_*/
