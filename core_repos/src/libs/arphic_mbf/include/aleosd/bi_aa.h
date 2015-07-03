/************************************************************************
;
;   (C) Copyright Arphic Technology Corp. 1993-2007
;
;    Title:     Arphic Mobile Font Rasterizer
;
;    Module:    grayscale filler
;
;    Version:   1.00
;
;    Author:    Koffman Huang
;
;***********************************************************************/

#ifndef _BI_AA_INCLUDED_
#define _BI_AA_INCLUDED_

#include "platform.h"
#include "bi_types.h"

/* switch */
#define AA_DRAW_WITH_EVEN_OLD_RULE          0
#define AA_LARGE_SIZE                       0 /* above 256x256 */
#define AA_ACCURATE_BBOX                    1 /* disable for more speed */

/* some value define */
#define AA_MAX_SIZE                         256
#define AA_LEVEL_STACK_SIZE                 32
#define AA_BEZIER_STACK_SIZE                (AA_LEVEL_STACK_SIZE * 3 + 1) * 2
#define AA_CONIC_LEVEL                      256        /* for speed */

/* AA errors */
#define AA_ERROR_INSUFFICIENT_WORK_BUFFER  -1
#define AA_ERROR_BEZIER_STACK_OVERFLOW     -2


typedef struct TCell_*  PCell;

#if AA_LARGE_SIZE
typedef struct  TCell_
{
    BI_INT32    x;
    BI_INT32    cover;
    BI_INT32    area;
    PCell       next;
} TCell;
#else
typedef struct  TCell_
{
    BI_UBYTE   x;
    BI_UBYTE   padding; /* for 4-byte alignment */
    BI_INT16   cover;
    BI_INT32   area;
    PCell      next;
} TCell;
#endif

typedef struct TRasData_   /* raster intenal use */
{
    /* current status */
    BI_INT32     area;
    BI_INT32     cover;
    BI_INT32     valid;
    BI_INT32     x;
    BI_INT32     y;
    BI_INT32     ex;
    BI_INT32     ey;

    /* for cells */
    BI_INT32     max_cells; /* num of cells can be used, we record n-1 */
    BI_INT32     num_cells;
    PCell        cells;
    PCell*       ycells;

    /* bbox */
    BI_INT32     bbox_min_ex, bbox_min_ey;
    BI_INT32     bbox_max_ex, bbox_max_ey;

    /* boundary */
    BI_INT32     min_ex, max_ex;
    BI_INT32     min_ey, max_ey;

    /* for bezier */
    BI_INT32     conic_level; /* for speed control */
    BI_INT32     bez_stack[AA_BEZIER_STACK_SIZE];
    BI_INT32     lev_stack[AA_LEVEL_STACK_SIZE];

#if BI_SUPPORT_GAMMA_CORRECTION
    /* for Gamma correction */
    BI_INT32     gamma_correction_flag;
    BI_UBYTE*    gamma;  /* gamma table */
#endif
#if BI_GDL_CLOSURE_TYPE
    BI_INT32     closure_type;
#endif

} TRasData, *PRasData;


typedef struct TRas_
{
    BI_INT32*  contour;
    BI_INT32   num_nodes;
    BI_BYTE*   target;
    BI_INT32   buffer_width;
    BI_INT32   buffer_height;
#if BI_SUPPORT_4_16_GRAY_LEVELS
	BI_INT32   grayshift;
	BI_INT32   graymask;
#endif
    PRasData   rd;
} TRas;


/* AA external routing */
#ifdef __cplusplus
extern "C" {
#endif

    BI_INT32 aa_init_ras( TRas* ras, BI_BYTE* work_buffer,BI_INT32 work_buffer_size );
    BI_INT32 aa_set_dynamic_work_buff( TRas* ras, BI_BYTE* work_buffer, BI_INT32 byte_size );
    BI_INT32 aa_get_work_buff_usage( TRas* ras );
    BI_INT32 aa_reset_ras( TRas* ras );
    BI_INT32 aa_outline_decompose( TRas* ras, BI_INT32* contour, BI_BYTE* node_type, BI_INT32 num_nodes);
    BI_INT32 aa_render( TRas* ras , BI_BYTE* bitmap, BI_INT32 buf_width, BI_INT32 buf_height, BI_INT32 ox,
                        BI_INT32 oy, BI_INT32 bold_width,BI_INT32 gamma_correct, BI_UBYTE* gamma_tbl);

#ifdef __cplusplus
}
#endif

#endif /* _BI_AA_INCLUDED_ */

