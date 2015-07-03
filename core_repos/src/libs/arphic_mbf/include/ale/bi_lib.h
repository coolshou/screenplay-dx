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
#include "bi_io.h"
#include "bi_render.h"
#if BI_SUPPORT_GDL_GLYPH_FORMAT
#include "bi_gdl.h"
#endif
#if BI_DEBUG_MODE
#include "bi_internal_use.h"
#endif

/* MFONT_UNUSED is a macro used to indicate that a given parameter is not  */
/* used -- this is only used to get rid of unpleasant compiler warnings    */
#ifndef MFONT_UNUSED
#define MFONT_UNUSED( arg )  ( (arg) = (arg) )
#endif

/*******************************************************************************
    Mobile font version
*******************************************************************************/
#if BI_SUPPORT_GDL_GLYPH_FORMAT
    #define BI_MBF_VERSION_MAJOR    1
    #define BI_MBF_VERSION_MINOR    7
    #define BI_MBF_VERSION_RELEASE  0
    #define BI_MBF_VERSION_BUILD    0
#else
    #define BI_MBF_VERSION_MAJOR    1
    #define BI_MBF_VERSION_MINOR    6
    #define BI_MBF_VERSION_RELEASE  1
    #define BI_MBF_VERSION_BUILD    0
#endif

#define BI_ENGINE_VERSION_MAJOR     2
#define BI_ENGINE_VERSION_MINOR     14
#define BI_ENGINE_VERSION_RELEASE   23
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
#define BI_ERROR_INSUFFICIENT_WORKING_BUFFER	      -1
#define BI_ERROR_UNICODE_MAPPING_TABLE_NOT_FOUND      -2
#define BI_ERROR_GET_GLYPH_INDEX_ERROR                -3
#define BI_ERROR_ID_NOT_FOUND                         -4
#define BI_ERROR_INVALID_SIZE_HEIGHT                  -5
#define BI_ERROR_INVALID_SIZE_WIDTH                   -6
#define BI_ERROR_GET_DATA_FUNCTION_NOT_FOUND          -7
#define BI_ERROR_GLYPH_TRUNCATION                     -8
#define BI_ERROR_GET_FONT_DATA_ERROR                  -9
#define BI_ERROR_GET_CHAR_WIDTH_ERROR                 -10
#define BI_ERROR_INSUFFICIENT_GLYPH_BUFFER_SIZE       -11
#define BI_ERROR_GET_FONT_METRICS_TABLE_FAULT         -12
#define BI_ERROR_CHARSET_NOT_SUPPORT                  -13
#define BI_ERROR_INSUFFICIENT_HINTING_BUFFER          -14
#define BI_ERROR_MISSING_CHARACTER                    -15
#define BI_ERROR_GET_STROKE_WIDTH                     -16
#define BI_ERROR_GET_GRAY_ADJ_TABLE                   -17
#define BI_ERROR_GET_GLOBEL_TABLE                     -18
#define BI_ERROR_CODE_NOT_FOUND_IN_TABLE              -19
#define BI_ERROR_RBM_ENDIANMISMATCH                   -20
#define BI_ERROR_RBM_INSUFFICIENT_WORKING_BUFFER      -21
#define BI_ERROR_MBF_VERSION_INCOMPATABLE             -22
#define BI_ERROR_GRAY_ADJ_STROKE_BUFFER_OVERFLOW      -23
#define BI_ERROR_GET_BBOX_TABLE                       -24
#define BI_ERROR_GET_FMET_TABLE                       -25
#define BI_ERROR_GAMMA_VALUE_INCORRECT                -26
#define BI_ERROR_GET_MHNT_TABLE                       -27
#define BI_ERROR_GET_BBOX_ERROR_TABLE                 -28
#define BI_ERROR_GET_BBOX_ERROR_TABLE_DATA_ERROR      -29
#define BI_ERROR_TOO_MANY_CONTROL_POINT_OF_ONE_STROKE -30
#define BI_ERROR_SET_VERTICAL_WRITING_SET_PARA        -31
#define BI_ERROR_SET_VERTICAL_WRITING_NO_DATA         -32
#define BI_ERROR_GET_TFST_TABLE                       -33
#define BI_ERROR_READ_TFST_TABLE                      -34
#define BI_ERROR_GET_GDLT_TABLE                       -35
#define BI_ERROR_INSUFFICIENT_GDL_BUFFER_SIZE         -36
#define BI_ERROR_GLYPH_TABLE_NOT_FOUND                -37
#define BI_ERROR_GDL_TABLE_NOT_FOUND                  -38
#define BI_ERROR_GDL_INIT_ERROR                       -39
#define BI_ERROR_THE_GRAY_LEVEL_NOT_SUPPORT           -40
#if BI_SET_WEIGHT
#define BI_ERROR_SETWEIGHT_INIT_ERROR                 -41
#endif
#define BI_ERROR_GET_RCDT_TABLE                       -42
#define BI_ERROR_RCD_TABLE_NOT_FOUND                  -43

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
#define BI_STYLE_OUTLINE_FRAME                      ( 1L << 3 )

/* BI_OUTPUT_FORMAT_XXX */
#define BI_OUTPUT_FORMAT_NORMAL_BITMAP              0

/* BI_SET_GRAY_XXX */
#define BI_SET_GRAY_MONOCHROME                      0
#define BI_SET_GRAY_GRAYSCALE_4                     1
#define BI_SET_GRAY_GRAYSCALE_256                   2
#define BI_SET_GRAY_SUBPIXEL_RGB                    3
#define BI_SET_GRAY_SUBPIXEL_BGR                    4
#define BI_SET_GRAY_SUBPIXEL_VRGB                   5
#define BI_SET_GRAY_SUBPIXEL_VBGR                   6

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

#define BI_MAX_SIZE                            255      /* monochrome Max size */
#define BI_GRAYSCALE_MAX_SIZE                  128      /* for grayscale Max size */ 
#define BI_MAX_LEN                             256
#define BI_MAX_FONT                              9      /* 2005.11.21 */
#define BI_MAX_SUB_ICON                         16      /* 2005.11.21 */
#define MAX_CONTROL_POINT                      256      /* 2006.01.25 */
#define BI_MAX_STATUS                           28      /* last status(BI_MAX_STATUS-1) is reserved, 2005.11.21 */
#define BI_MAX_ADD_POINT                       128      /* value 128 = 64 point */
#define BI_MAX_DEL_POINT                       128      /* value 128 = 64 point */
#define BI_GLYPH_BUFFER_SIZE                  2048      /* for compress glyph data */

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
#define BI_GET_DATA_USER_DEFINE                 0xffffffff


#define BI_MEM_ITEM_MAX_COUNT 11
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
} ArGetDataFunctions;
#endif

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
#if FOR_MONO_QUALITY_001
    BI_INT32            MonoHintTblPtr;
#endif
#if BI_SUPPORT_TYPEFACE_SCALING
    BI_INT32            TypefaceScaleTblPtr;
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
    BI_UBYTE            BoldV;
    BI_UBYTE            BoldH;
    BI_UBYTE            BoldS;
    BI_UBYTE            PaddingByte;        /* unused,just for four byte alignment padding */
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
    BI_UBYTE            NoEmboldenFlag;
    BI_UBYTE            RegularBoldV;
    BI_UBYTE            RegularBoldH;
    BI_UBYTE            RegularBoldS;
    BI_INT32            fix_pitch_move_glyph_when_bold_flags;
    BI_INT32            BitmapEmboldenFlag;
#endif
#if BI_SUPPORT_RADICAL_BASE_FONT
    BI_INT32            RCDTablePtr;
    BI_INT32            RCD_Min_ID;
    BI_INT32            RCD_Max_ID;
    BI_INT32            RCD_Format;
    BI_INT16            OffsetX256;
    BI_INT16            OffsetY256;
#endif
} BI_InternalFormat,*PBI_InternalFormat;

typedef struct {
    BI_UINT32           StrokeNo;
    BI_UBYTE            px;
    BI_UBYTE            py;
#if BI_SUPPORT_HINTING
    BI_UBYTE            StatusIndex;        /* 0xff-->no status */
    BI_BYTE             padding;            /* unused,just for four byte alignment padding */
#else
    BI_BYTE             padding[2];         /* unused,just for four byte alignment padding */ 
#endif
#if BI_SUPPORT_GDL_GLYPH_FORMAT
    /* for GDL */
    BI_BYTE             padding_gdl[2];     /* unused,just for four byte alignment padding */
    BI_UBYTE            key_count;
    BI_UBYTE            width_count;
    BI_UBYTE            px1[8];
    BI_UBYTE            py1[8];
    BI_UBYTE            w[8];
    BI_INT32            StrokeOffset;
#endif
} BI_StrokeFormat;

#if BI_SUPPORT_HINTING
typedef struct {                            /* must four byte alignment */
    BI_UINT32           ExStrokeNo; 
    BI_INT32            SubstrokeAdjFlag;
    BI_UBYTE            StrokeAdj[BI_MAX_SUB_ICON]; /* 0 --> the stroke ,1~ --> substroke 1*/
    BI_UBYTE            BoldValueV[BI_MAX_SUB_ICON];
    BI_UBYTE            BoldValueH[BI_MAX_SUB_ICON];
    BI_UBYTE            BoldValueS[BI_MAX_SUB_ICON];
    BI_INT16            KeyPointAdjX;       /* offset +/- */
    BI_INT16            KeyPointAdjY;
    BI_BYTE             ControlPointAdjX[MAX_CONTROL_POINT];
	BI_BYTE             ControlPointAdjY[MAX_CONTROL_POINT];
    /* for grayscale width control */
    BI_BYTE             Gray_Stroke_Width_Buffer[BI_GRAY_ADJ_MAX_STROKE_BUFFER];
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
#endif

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
    BI_INT32            user_default_char;
#if BI_SUPPORT_GAMMA_CORRECTION
    BI_INT32            GammaValue;
#endif
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
#if BI_VERTICAL_WRITING
    BI_INT32  vtwg_off;
    BI_INT32  seqcode2;
    BI_UINT16           VerticalEnable;     /* BI_SET_vertical_writing_XXX          */
    BI_UINT16           VerticalMode;       /* BI_SET_vertical_writing_XXX          */
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
#if BI_SET_WEIGHT
        BI_INT32            adjmode;
        BI_INT32            adjoff;
        TArFontWeight       adjtable;
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
BI_INT16  Ar_BI_GetMet(PTArVarGlobalAll pp,BI_INT32 code,BI_INT32 size,BI_INT32 sizeH,BI_INT32 *OrgX,BI_INT32 *BaseLine,BI_INT32 *AdvX);
BI_INT16  Ar_BI_GetMet2(PTArVarGlobalAll pp,BI_INT32 code,BI_INT32 size,BI_INT32 sizeH,BI_INT32 *OrgX,BI_INT32 *OrgY,BI_INT32 *AdvX,BI_INT32 *OrgY256,BI_INT32 *AdvX256);
BI_INT16  Ar_BI_GetFMET22(PTArVarGlobalAll pp,BI_INT32 sizeW,BI_INT16* lsb,BI_INT16* rsb);
BI_INT16  Ar_BI_GetFMET(PTArVarGlobalAll pp,BI_INT32 sizeW,BI_INT16* lsb,BI_INT16* rsb);
#endif
BI_INT16 Ar_BI_GetBBox(PTArVarGlobalAll pp,BI_INT32 code,BI_INT32 sizeW,BI_INT32 sizeH,BI_UINT32 *MinX,BI_UINT32 *MinY,BI_UINT32 *MaxX,BI_UINT32 *MaxY);
BI_INT16 Ar_BI_GetBBoxError(PTArVarGlobalAll pp,BI_INT32 code,BI_INT32 size,BI_INT32 *eMinX,BI_INT32 *eMinY,BI_INT32 *eMaxX,BI_INT32 *eMaxY);
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
BI_INT32 getGlyIdxU(BI_UINT16 ucode ,BI_UINT32 mapoffset, BI_BYTE *WorkBuf);
#endif
BI_UINT16 ICode_seq2(BI_UINT16 Bcode ,BI_INT16 tcodePage);

#ifdef __cplusplus
}
#endif

#endif   /*#ifndef _BI_LIB_INCLUDED_*/
