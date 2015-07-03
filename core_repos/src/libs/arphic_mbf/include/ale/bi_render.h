/*EncryptOn*/
/************************************************************************
;
;   (C) Copyright Arphic Technology Corp. 1993-2005
;
;    Title:     Arphic Mobile Font Rasterizer
;
;    Module:    render (include file)
;
;    Version:   1.00
;
;    Author:    Koffman Huang
;
;***********************************************************************/
#ifndef _bi_renderH_
#define _bi_renderH_

#include "platform.h"
#include "bi_types.h"

/* option define */
/*#define BI_TRANSFORM_SUPPORT           0 */
/*#ifdef MOMO_QUALTY_TOOL*/
#define FOR_MONO_QUALITY_001            1
/*
#else
#define FOR_MONO_QUALITY_001            0
#endif
*/

/*#define FOR_DEVELOP_TOOL               0*/

/* for raster define */
#define MAX_STACK_SIZE          128*6*2     /* min = 53  when size=128 ,
					       memory size=128*6*2  = 1.5KB */
#define MAX_POINT_ARRAY_SIZE    1024*2      /* min = 513 when size=128 ,
                                               memory size=1024*2*2 = 2KB   */

/* display format */
#define BI_DISPLAY_MONOCHROME          0  /* default */
#define BI_DISPLAY_GRAYSCALE           1
#define BI_DISPLAY_SUBPIXEL            2


/* This is used for development tools, */
/* now we define it in "vcft.h"        */
#ifdef FOR_DEVELOP_TOOL
/*
    0x1 left Over Boundary
    0x2 right
    0x4 top
    0x8 button
    0x10 vertail line
    0x20 horizontal line
*/
/*BI_INT16 OverBoundaryFlag;*/
#endif

/*---------------------for grayscale module[Start]----------------------------*/
#define SPECIAL_NOKIA_GRAY_QUALITY 0
#define FOR_BUG_20061004_001    /* over stack in nonsquare*/
#define FOR_BUG_20061004_002    /* round and truncate*/
#define FOR_QUALITY_PERFORMANCE_NO_FORWARD_DIFFERENCE
#define FOR_SINGLE_DOT_PROBLEM
#define FOR_OVER_SQUARE_PROBLEM
#define FOR_GRAY_BBOX
#define FOR_ITALIC
#define FOR_ITALIC2

#define FOR_LARGE_GRAY_SLANT_WIDTH
#define FOR_LARGE_GRAY_SLANT_WIDTH2

#define FOR_ADD_STARTXY
#define FOR_PROBLEM_QUALITY_001
#define FOR_PROBLEM_HANGUP_001
/* #define FOR_PROBLEM_QUALITY_003_CONNECT */
#define FOR_PROBLEM_QUALITY_004_SPLIT
#define FOR_PROBLEM_QUALITY_005_DIFF_LEN
/*#define FOR_PROBLEM_QUALITY_006_ROUNDGOTHIC*/
/*#define FOR_TEST_002*/
#define FOR_LETTER_SIZE_TEST
/*#define FOR_SPEED_CONST_CACHE*/
/*#define FOR_SPEED_CONST_CACHE4*/ /* define in platform.h */
#define FOR_NORMAL_SPEED
#define FOR_NORMAL_SPEED2
/*#define FOR_WIDTH_CONTROL*/

#define FIND_MAX_FOR_TEST       0           /* for test */

#define HD_MAX_DISTANCE         65535
#define HD_EXPAND_BOLD          3
#ifdef FOR_ITALIC2
#define BASE_ARRAY_COUNT        400
#else
#define BASE_ARRAY_COUNT        300
#endif
#define TEMP_ARRAY_SIZE         160*4
#define GRAY_SMALL_SIZE         1
#define GRAY_DENSITY_BASE       6

#define HD_FOR_GRAY_DISPLAY

#define MAX_STACK_COUNT         128         /* min = 53  when size=128 , memory size=128*6*2  = 1.5KB */
#define MAX_POINT_ARRAY_COUNT   1024        /* min = 513 when size=128 , memory size=1024*2*2 = 2KB   */

/* grayscale module memory alloc */
#define MEM_ADDR_GRAY_BASE_ARYA    0
#define MEM_ADDR_GRAY_BASE_ARYA2   (3*BASE_ARRAY_COUNT*2)
#define MEM_ADDR_GRAY_BASE_ARYA3   (6*BASE_ARRAY_COUNT*2)
#define MEM_ADDR_GRAY_BASE_ARYB1   (9*BASE_ARRAY_COUNT*2)
#define MEM_ADDR_GRAY_BASE_ARYB2   (9*BASE_ARRAY_COUNT*2+BASE_ARRAY_COUNT*2)
#define MEM_ADDR_GRAY_BASE_ARYB3   (9*BASE_ARRAY_COUNT*2+2*BASE_ARRAY_COUNT*2)
#define MEM_ADDR_GRAY_TEMP_ARY1    (9*BASE_ARRAY_COUNT*2+3*BASE_ARRAY_COUNT*2)
#define MEM_ADDR_GRAY_TEMP_ARY2    (9*BASE_ARRAY_COUNT*2+3*BASE_ARRAY_COUNT*2+TEMP_ARRAY_SIZE)
#define MEM_ADDR_GRAY_TEMP_ARY3    (9*BASE_ARRAY_COUNT*2+3*BASE_ARRAY_COUNT*2+2*TEMP_ARRAY_SIZE)
#define MEM_ADDR_GRAY_STACK        (9*BASE_ARRAY_COUNT*2+3*BASE_ARRAY_COUNT*2+3*TEMP_ARRAY_SIZE)
#define MEM_ADDR_GRAY_POINT_ARRAY  (9*BASE_ARRAY_COUNT*2+3*BASE_ARRAY_COUNT*2+3*TEMP_ARRAY_SIZE+MAX_STACK_SIZE)
#define MEM_ADDR_GRAY_POINT_ARRAY_SIZE 3072
#define MEM_GRAY_FIX_REQUIRED      (MEM_ADDR_GRAY_POINT_ARRAY + MEM_ADDR_GRAY_POINT_ARRAY_SIZE)
/*-----------------------for grayscale module[END]----------------------------*/

/* glyph format */
typedef enum  BI_Glyph_Format_
{
    BI_GLYPH_MONOCHROME_RASTERLINE =0,
    BI_GLYPH_GRAYSCALE_RASTERLINE  =1,
    BI_GLYPH_BEZIER_CURVE          =2,
    BI_GLYPH_BITMAP                =3
} BI_Glyph_Format;

typedef struct {
    BI_INT16   y;
    BI_INT16   xl;
    BI_INT16   xr;
}   BI_RASTERLINEout;

typedef struct {
    BI_INT16   x;
    BI_INT16   yt;
    BI_INT16   yd;
}   BI_RASTERLINEoutY;

typedef struct {
    BI_UBYTE   y;
    BI_UBYTE   x;
    BI_UBYTE   cover;
    BI_UBYTE   len;
} BI_GRASTERLINEout;

typedef struct {
    BI_UBYTE x;
    BI_UBYTE y;
} BI_PointXY;

typedef struct {
    BI_UBYTE firstx;
    BI_UBYTE firsty;
    BI_UBYTE secondx;
    BI_UBYTE secondy;
    BI_UBYTE thirdx;
    BI_UBYTE thirdy;
} BI_ControlPointType;

#ifndef ___ControlPointType16___
#define ___ControlPointType16___
typedef struct {
    BI_UINT16 firstx;
    BI_UINT16 firsty;
    BI_UINT16 secondx;
    BI_UINT16 secondy;
    BI_UINT16 thirdx;
    BI_UINT16 thirdy;
} BI_ControlPointType16;
#endif

#ifndef ___BI_BEZIERpoint___
#define ___BI_BEZIERpoint___
/* this is 24.8 fix point format for outout format */
typedef struct {
	BI_INT32   y1;
	BI_INT32   x1;
	BI_INT32   y2;
	BI_INT32   x2;
} BI_BEZIERpoint;
#endif

typedef struct BI_RasterRec_*  BI_Raster;

typedef struct BI_BBox_
{
    BI_UINT16 maxx;
    BI_UINT16 maxy;
    BI_UINT16 minx;
    BI_UINT16 miny;
} BI_BBox;

#if BI_TRANSFORM_SUPPORT
typedef struct BI_Matrix_
{
    BI_INT16 xx;
    BI_INT16 xy;
    BI_INT16 yx;
    BI_INT16 yy;
} BI_Matrix;

typedef struct BI_Matrix32_
{
	BI_INT32 xx;
	BI_INT32 xy;
	BI_INT32 yx;
	BI_INT32 yy;
} BI_Matrix32;
#endif
#if BI_VERTICAL_WRITING
typedef struct BI_Matrix2_
{
    BI_INT32 xx;
    BI_INT32 xy;
    BI_INT32 yx;
    BI_INT32 yy;
    BI_INT32 dx;
    BI_INT32 dy;
    BI_INT32 dx2;
    BI_INT32 dy2;
} BI_Matrix2;
typedef struct BI_1POINT_
{
    BI_INT32 px;
    BI_INT32 py;
    BI_INT32 val;
    BI_INT32 val2;
} BI_1POINT;
typedef struct BI_4POINTS_
{
    BI_1POINT pnt1;
    BI_1POINT pnt2;
    BI_1POINT pnt3;
    BI_1POINT pnt4;
} BI_4POINTS;
#endif

#if FOR_MONO_QUALITY_001
#define MQ_MAX_EXTREME          10
#define MQ_MAX_STROKE_PARA      7
#define MQ_MAX_ALIGN_PARA       8
#define MQ_MAX_MODE_COUNT       8
#define MQ_MAX_PATTERN_COUNT    64 /*8*/
#define MQ_MAX_CODE_PARA        8
#define MQ_MAX_STROKE_COUNT     8
#define MQ_MAX_SAVE_POINT       512

#define CM_NONE_                50
#define CM_REFLECT_OTHER_CODE   51
#define CM_ALIGN_X_ODD          52
#define CM_ALIGN_X_Y_ODD        53
#define CM_ALIGN_Y_ODD          54
#define CM_ALIGN_Y_SAME         55
#define CM_ALIGN_X_SAME         56
#define CM_ALIGN_X_Y_SAME       57
#define CM_NOAUTO_ALIGN         58

#define  SS_NONE                0
#define  SS_REFLECT_X_ODD       1
#define  SS_REFLECT_X_SAME      2
#define  SS_REFLECT_X_SLANT     3
#define  SS_REFLECT_Y_ODD       4
#define  SS_REFLECT_Y_SAME      5
#define  SS_REFLECT_XY_SAME     6
#define  SS_CANCEL_STROKE       7
#define  SS_ALIGN_X_ODD         88
#define  SS_ALIGN_PRE_STROKE    99
#define  SS_ALIGN_POINT         10
#define  SS_REFLECT_XY_SLANT    11
#define  SS_SAVE_POINT_LIST     12
#define  SS_RESTORE_POINT_LIST  13
#define  SS_KEEP_PARTIAL_STROKE 14
#define  SS_SAVE_LAST_X         15
#define  SS_SAVE_LAST_Y         16
#define  SS_RESTORE_LAST_X      17
#define  SS_RESTORE_LAST_Y      18
#define  SS_REFLECT_XY_SMALL    19
#define  SS_TEMPDEF_BBOX_XY_SAME 8
#define  SS_TEMPDEF_BBOX_X_ODD   9
#define  SS_TEMPDEF_BBOX2_XY_SAME 31
#define  SS_TEMPDEF_BBOX2_X_ODD   32

#define  PT_COUNTERCLOCKWISE    22
#define  PT_CLOCKWISE           21
#define  PT_DELTA_1_PATTERN    	23
#define  PT_DELTA_2_PATTERN     24
#define  PT_DELTA_3_PATTERN     25
#define  PT_DELTA_4_PATTERN     26
#define  PT_DELTA_5_PATTERN     27
#define  PT_DELTA_6_PATTERN     28
#define  PT_DELTA_7_PATTERN     29
#define  PT_DELTA_8_PATTERN     30

#if 1 /* 1111111111 */
#define  PT_NS_DELTA_1_PATTERN     41
#define  PT_NS_DELTA_2_PATTERN     42
#define  PT_NS_DELTA_3_PATTERN     43
#define  PT_NS_DELTA_4_PATTERN     44
#define  PT_NS_DELTA_5_PATTERN     45
#define  PT_NS_DELTA_6_PATTERN     46
#define  PT_NS_DELTA_7_PATTERN     47
#define  PT_NS_DELTA_8_PATTERN     48
#endif

typedef struct Mono_Hinting_Pattern_
{
    BI_UBYTE         pattern_type;
    BI_UBYTE         extreme_count;
    BI_UBYTE         extreme[MQ_MAX_EXTREME];
} TMono_Hinting_Pattern;

typedef struct Mono_Hinting_Mode_
{
    BI_UBYTE         stroke_mode;
    BI_UBYTE         para[MQ_MAX_STROKE_PARA];
} TMono_Hinting_Mode;

typedef struct Mono_Hinting_Stroke_
{
    BI_UBYTE         stroke_no;
    BI_UBYTE         size1;
    BI_UBYTE         align_mode;
    BI_UBYTE         mode_count;
    BI_UBYTE         align_mode_para[MQ_MAX_ALIGN_PARA];
    TMono_Hinting_Mode    mode[MQ_MAX_MODE_COUNT];
    BI_UBYTE         size2;
    BI_UBYTE         pattern_count;
    BI_UBYTE         padding[2];
    TMono_Hinting_Pattern pattern[MQ_MAX_PATTERN_COUNT];
} TMono_Hinting_Stroke;

typedef struct Mono_Hinting_Save_
{
    BI_INT16         pointList[MQ_MAX_SAVE_POINT];
    BI_INT32         pointListCnt;
    BI_UBYTE         px;
    BI_UBYTE         py;
    BI_UBYTE         lastpx;
    BI_UBYTE         lastpy;
} TMono_Hinting_Save;

typedef struct Mono_Hinting_
{
    BI_UINT16        code;
    BI_UBYTE         code_mode;
    BI_UBYTE         stroke_count;
    BI_UBYTE         code_mode_para[MQ_MAX_CODE_PARA];
    TMono_Hinting_Stroke  stroke[MQ_MAX_STROKE_COUNT];
    BI_UBYTE         enable_stroke;
    BI_UBYTE         enable_curve;
    BI_UBYTE         enable_stroke_no;
    BI_UBYTE         padding;
    TMono_Hinting_Save save;
    BI_UINT16        code2;
    BI_UINT16        padding2;
} TMono_Hinting,*PTMono_Hinting;
#endif /* FOR_MONO_QUALITY_001 */


typedef struct  BI_Raster_Params_
{
    BI_VOID*                   target;
    BI_VOID*                   source;
    BI_INT16                   ras_count;
    BI_INT16                   height;
    BI_INT16                   width;
    BI_INT16                   base_size; /* base = 2^n , base_size=n */
    BI_INT16                   pitch;
    BI_INT16                   BufferWidth;
    BI_INT16                   BufferHeight;
    BI_INT16                   x;
    BI_INT16                   y; 
    BI_INT16                   dx;
    BI_INT16                   dy;
    BI_INT16                   BoldV;
    BI_INT16                   BoldH;
    BI_INT16                   BoldS;
    BI_BYTE**                  cdx;       /* control point move x */
    BI_BYTE**                  cdy;       /* control point move x */
    BI_INT16                   AdvX;
    BI_INT16                   OrgY;
    BI_INT16                   AdvX256;
    BI_INT16                   OrgY256;
    BI_INT16                   OffsetX;
    BI_INT16                   OffsetY;
    BI_INT32                   flags;     /* bit 1 : closure render,
                                             bit 2 : round-gothic,
                                             bit 3 : Italic,
                                             bit 4 : Transform
                                             bit 5 : GDL control point (4bytes)
                                             bit 6 : GDL non-accurate
                                             bit 7 : clipping
                                             bit 8 : end of substroke
                                             bit 9 : no scale path (for Stick GDL )
                                           */
    BI_BBox                    bbox;
#if BI_TRANSFORM_SUPPORT
    BI_Matrix                  matrix;
#endif
#if BI_VERTICAL_WRITING
    BI_Matrix2                 matrix2;
#endif
	BI_INT32                   ClearFlag;
    BI_INT32                   StrokeWidth;
    BI_INT32                   GammaValue;
    BI_INT32                   bbox_flag;
#if FOR_MONO_QUALITY_001
    PTMono_Hinting             pmonohint;
#endif /* FOR_MONO_QUALITY_001 */
#if BI_SUPPORT_GRAYSCALE_HINTING
	BI_BYTE*                   hinting_data;
	BI_INT32                   hinting_data_length; 
#endif
    BI_INT16                   StrokeNo;
	BI_INT16                   SubStrokeNo;
    BI_INT16                   padding;     /* not used , just for 4byte alignment padding */
    BI_INT16                   GridFitFlag; /* for grid fit */
    BI_INT16                   hx;          /* for grid fit */
	BI_INT16                   hy;          /* for grid fit */
	BI_INT16                   clip_x;      /* for clipping */
	BI_INT16                   clip_y;      /* for clipping */
	BI_INT16                   clip_width;  /* for clipping */
	BI_INT16                   clip_height; /* for clipping */
    BI_VOID*                   user;
} BI_Raster_Params;

typedef BI_INT32
  (*BI_Raster_New_Func)( BI_VOID*        memory,
                         BI_Raster*      raster );

typedef BI_INT32
  (*BI_Raster_Reset_Func)( BI_Raster     raster,
                           BI_UBYTE*     pool_base,
                           BI_UINT32     pool_size );

typedef BI_INT32
  (*BI_Raster_Set_Mode_Func)( BI_Raster  raster,
                              BI_UINT32  mode,
                              BI_VOID*   args );

typedef BI_INT32
  (*BI_Raster_Render_Func)( BI_Raster          raster,
                            BI_Raster_Params*  params );

typedef BI_INT32
  (*BI_Raster_Done_Func)( BI_Raster  raster );

typedef struct  BI_Raster_Funcs_
{
    BI_Glyph_Format          glyph_format;
    BI_BYTE padding[3]; /* unused,just for four byte alignment padding */
    BI_Raster_New_Func       raster_new;
    BI_Raster_Reset_Func     raster_reset;
    BI_Raster_Set_Mode_Func  raster_set_mode;
    BI_Raster_Render_Func    raster_render;
    BI_Raster_Done_Func      raster_done;
} BI_Raster_Funcs;


#endif  /* #ifndef _bi_renderH_ */

