/********************************************************************************************
 *     LEGAL DISCLAIMER 
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES 
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED 
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS 
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED, 
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR 
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY 
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, 
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK 
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION 
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *     
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH 
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, 
 *     TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE 
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
 *     
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS 
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.  
 ************************************************************************************************/
/*
*
* \par Description
*   The definition of mt85 system
*
*/

#ifndef __MT85__MT85_H__
#define __MT85__MT85_H__

#include <linux/fb.h>

#include <fusion/shm/pool.h>

#include <core/layers.h>
#include <core/screens.h>
#include <core/surface_pool.h>

#include "mt85xx_fb.h"

//#include "mtk_dfb_cfg.h"

//#include <gfx_cmdque.h>
//#include <gfx_if.h>
#include "x_typedef.h"

#if CONFIG_DIRECTFB_MULTI_MEM_POOL
#if CONFIG_DIRECTFB_LARGE_MEM
#define FB_MEM_SLICE_NUM  5
#else
#define FB_MEM_SLICE_NUM  3
#endif
#endif

#include "mt85_surfacemanager.h"
#include "mt85_vt.h"

#if DFB_SUPPORT_GFX_ADAPTER
#define DFB_CMDBUF_FLUSH_FLAG               0xFEDCBA98
#endif

/// Bitblt option
typedef enum 
{
    E_GFXBLT_TRANSPARENT = 0,
    E_GFXBLT_KEYNOT,
    E_GFXBLT_COLORCHANGE,
    E_GFXBLT_CLIP,
    E_GFXBLT_CFMT_ENA,
    E_GFXBLT_KEYSDSEL
} GFX_BLT_OPT_T;

/// Bitblt option flag : color format translation
#define D_GFXFLAG_CFMT_ENA      (1 << (INT32)E_GFXBLT_CFMT_ENA)

/// Bitblt option flag : transparent
#define D_GFXFLAG_TRANSPARENT   (1 << (INT32)E_GFXBLT_TRANSPARENT)

#ifndef FB_ACCEL_MEDIATEK_85XX
#define FB_ACCEL_MEDIATEK_85XX 8530
#endif

#define MT85_PRIMARY_SUPPORTED_OPTIONS (DLOP_ALPHACHANNEL | DLOP_OPACITY | DLOP_SRC_COLORKEY)

#define MT85_PRIMARY_DEFAULT_WIDTH 1280
#define MT85_PRIMARY_DEFAULT_HEIGHT 720

#if CONFIG_DIRECTFB_MULTI_MEM_POOL
typedef enum _FB_MEM_TYPE
{
    FBMT_CH1 = 0,
    FBMT_CH2,
    FBMT_LIN
}FB_MEM_TYPE;

typedef struct _MULTI_POOL
{
    unsigned int    num;

    unsigned char * phys[FB_MEM_SLICE_NUM];
    unsigned char * addr[FB_MEM_SLICE_NUM];    
    unsigned long   size[FB_MEM_SLICE_NUM];
    FB_MEM_TYPE     type[FB_MEM_SLICE_NUM];
}MULTI_POOL;

extern MULTI_POOL mt85_multi_pool;
#endif

#define MT85_MAX_OSD_PLANE 2

typedef struct {
     CoreSurfacePool           *pool;

     FusionSHMPoolShared       *shmpool;

     SurfaceManager            *manager;
} MT85Shared;

typedef struct {
     MT85Shared                *shared;

     CoreDFB                   *core;

     int                        fd;
     struct fb_fix_screeninfo   fix;
     void                      *mem;

     struct mt85fb_imagebuffer  imagebuf;
     
     VirtualTerminal           *vt;
} MT85;
typedef enum 
{
    CM_Reserved0 = 0,
    CM_Reserved1 = 1,
    CM_YCbCr_CLUT8 = 2,
    CM_Reserved2 = 3,
    CM_CbYCrY422_DIRECT16 = 4,
    CM_YCbYCr422_DIRECT16 = 5,
    CM_AYCbCr8888_DIRECT32 = 6,
    CM_Reserved3 = 7,
    CM_Reserved4 = 8,
    CM_Reserved5 = 9,
    CM_RGB_CLUT8 = 10,
    CM_RGB565_DIRECT16 = 11,
    CM_ARGB1555_DIRECT16 = 12,
    CM_ARGB4444_DIRECT16 = 13,
    CM_ARGB8888_DIRECT32 = 14,
    CM_Reserved6 = 15
} GFX_COLOR_MODE_T;



typedef enum _GFX_COLORMODE_T
{
    GFX_COLORMODE_AYCbCr_CLUT2  = 0,
    GFX_COLORMODE_AYCbCr_CLUT4  = 1,
    GFX_COLORMODE_AYCbCr_CLUT8  = 2,
    GFX_COLORMODE_CbYCrY_16     = 3,
    GFX_COLORMODE_YCbYCr_16     = 4,
    GFX_COLORMODE_AYCbCr_D8888  = 5,
    GFX_COLORMODE_ARGB_CLUT2    = 6,
    GFX_COLORMODE_ARGB_CLUT4    = 7,
    GFX_COLORMODE_ARGB_CLUT8    = 8,
    GFX_COLORMODE_RGB_D565      = 9,
    GFX_COLORMODE_ARGB_D1555    = 10,
    GFX_COLORMODE_ARGB_D4444    = 11,
    GFX_COLORMODE_ARGB_D8888    = 12,
    GFX_COLORMDOE_YUV_420_BLK   = 13,
    GFX_COLORMODE_YUV_420_RS    = 14,
    GFX_COLORMDOE_YUV_422_BLK   = 15,
    GFX_COLORMODE_YUV_422_RS    = 16,
    GFX_COLORMDOE_YUV_444_BLK   = 17,
    GFX_COLORMODE_YUV_444_RS    = 18,
    GFX_COLORMODE_RESERVED = 19
    
} GFX_COLORMODE_T;

typedef struct _GFX_CMDQUE_T
{
    int i4ShortQue;
    int i4QueConfig;
    int i4QueCapacity;
    int i4QueSize;
    int i4PrevIndex;
    int i4ReadIndex;
    int i4WriteIndex;
    int i4QueFlushCount;
    int i4QueIntCount;
    unsigned char *pu1PrevAddr;
    unsigned char *pu1ReadAddr;
    unsigned char *pu1WriteAddr;
    volatile unsigned long long  *pu8QueTop;
    struct _GFX_CMDQUE_T *prNext;
} GFX_CMDQUE_T;

typedef struct {
     /* file descriptor from /dev/fb0 */
     int                    fd;

#if 0 /*yjg*/
     /* mapping of shared command queue control structure and DMA region */
     volatile GFX_CMDQUE_T *shm_cmd_que;
     volatile unsigned long long       *cmd_que_buf;
#endif

     int num_plane;
     
     CoreScreen              *screen;     

     CoreLayer *layer1;
     CoreLayer *layer2;
     
} MT85DriverData;

typedef enum {
     MT85_LAYER_OSD1,
     MT85_LAYER_OSD2,
     MT85_LAYER_VDP1,
     MT85_LAYER_VDP2
} MT85LayerID;


typedef struct {
     MT85LayerID            layer;
} MT85LayerData;

extern MT85 *dfb_mt85;

extern const SurfacePoolFuncs   mt85SurfacePoolFuncs;
extern /*const*/ DisplayLayerFuncs  mt85PrimaryLayerFuncs;
extern /*const*/ ScreenFuncs        mt85PrimaryScreenFuncs;

#if DFB_SUPPORT_GFX_ADAPTER

#include "u_common.h"
#include "x_memtype.h"
//#include "x_os.h"
#include "x_typedef.h"

// max allowed number of commands in buffer
#if !(GFX_DRV_CMDBUF_DYNAMIC_SIZE)
#define MAX_BUFF_SIZE  256
#endif

#define ASSERT(x)		//((x) ? (void)0 : Assert(#x, __FILE__, (INT32)__LINE__))

/* enumerations */
typedef enum
{
    GFX_CLEAR = 0,
    GFX_DST_IN,
    GFX_DST_OUT,
    GFX_DST_OVER,
    GFX_SRC,
    GFX_SRC_IN,
    GFX_SRC_OUT,
    GFX_SRC_OVER
} GFX_PD_RULE_T;

/// GFX Cmd Buf State Machine
typedef enum
{
   GFX_CMDBUF_STATE_IDLE,               ///< Cmd buffer init state
   GFX_CMDBUF_STATE_ACTIVE,             ///< Cmd buffer active
   GFX_CMDBUF_STATE_WAITFLUSH,          ///< Cmd buffer wait flush
   GFX_CMDBUF_STATE_INFLUSH,            ///< Cmd buffer in flush
   GFX_CMDBUF_STATE_MAX                 ///< The max
} GFX_CMDBUF_STATE;

typedef enum _GFX_BUFF_CMD_TYPE_T
{
    GFX_BUFF_TYPE_FILL_RECT = 0,
    GFX_BUFF_TYPE_BITBLT,
    GFX_BUFF_TYPE_ALPHA_COMPOSITION,
    GFX_BUFF_TYPE_STRETCH_BITBLT,
    
    GFX_BUFF_TYPE_DRAW_LINE_H,
    GFX_BUFF_TYPE_DRAW_LINE_V,
    GFX_BUFF_TYPE_TRANSPARENT_BITBLT,
    GFX_BUFF_TYPE_TRANSPARENT_FILL,
    GFX_BUFF_TYPE_REPLACE_COLOR,
    GFX_BUFF_TYPE_ALPHA_BLENDING,
    GFX_BUFF_TYPE_EXT_ALPHA_MUL,
    GFX_BUFF_TYPE_ALPHA_BITBLT,  
    GFX_BUFF_TYPE_ALPHAMAP_BITBLT,
    GFX_BUFF_TYPE_COLOR_BITBLT,
    GFX_BUFF_TYPE_YCBCR_TO_RGB,     
    GFX_BUFF_TYPE_ADV_STRETCH_BITBLT,
    GFX_BUFF_TYPE_ROP_BITBLT,
    GFX_BUFF_TYPE_PALETTE_BITBLT,       
    GFX_BUFF_TYPE_ROTATE_90 ,
    GFX_BUFF_TYPE_IGPG_DECODE,
    GFX_BUFF_TYPE_FLUSH,
    GFX_BUFF_TYPE_STOP, // 21
    
    GFX_BUFF_TYPE_FILL_RECT_COMPOSE,
    GFX_BUFF_TYPE_FILL_COMPOSITION,
    //#ifdef GL_XOR
    GFX_BUFF_TYPE_STRETCH_COMPOSITION,
    GFX_BUFF_TYPE_ADV_STRETCH_COMPOSITION,
    GFX_BUFF_TYPE_ROTATE_STRETCH ,
    GFX_BUFF_TYPE_ROTATE_ADV_STRETCH,
    GFX_BUFF_TYPE_ROTATE_STRETCH_COMPOSITION,
    GFX_BUFF_TYPE_ROTATE_ADV_STRETCH_COMPOSITION,
    GFX_BUFF_TYPE_ROTATE_COMPOSITION,
    GFX_BUFF_TYPE_MIRROR_FLIP,
    GFX_BUFF_TYPE_Y2R_BITBLT,
    GFX_BUFF_TYPE_Y2R_COMPOSE,
    GFX_BUFF_TYPE_Y2R_XOR,
    GFX_BUFF_TYPE_Y2R_STRETCH,
    GFX_BUFF_TYPE_ROTATE_ONLY,
    GFX_BUFF_TYPE_YUV_STRETCH_COMPOSITION,
    GFX_BUFF_TYPE_YUV_ADV_STRETCH_COMPOSITION,
    GFX_BUFF_TYPE_YUV_ROTATE_STRETCH ,
    GFX_BUFF_TYPE_YUV_ROTATE_ADV_STRETCH,
    GFX_BUFF_TYPE_YUV_ROTATE_STRETCH_COMPOSITION,
    GFX_BUFF_TYPE_YUV_ROTATE_ADV_STRETCH_COMPOSITION,
    GFX_BUFF_TYPE_YUV_ROTATE_COMPOSITION,
    GFX_BUFF_TYPE_YUV_ROTATE,
    GFX_BUFF_TYPE_CLUT8_STRETCH_COMPOSITION,
    GFX_BUFF_TYPE_CLUT8_ADV_STRETCH_COMPOSITION,
    GFX_BUFF_TYPE_CLUT8_ROTATE_STRETCH ,
    GFX_BUFF_TYPE_CLUT8_ROTATE_ADV_STRETCH,
    GFX_BUFF_TYPE_CLUT8_ROTATE_STRETCH_COMPOSITION,
    GFX_BUFF_TYPE_CLUT8_ROTATE_ADV_STRETCH_COMPOSITION,
    GFX_BUFF_TYPE_CLUT8_ROTATE_COMPOSITION,
    GFX_BUFF_TYPE_CLUT8_ROTATE,
    GFX_BUFF_TYPE_FLIPGRADEFILL,

    // used for DirectFB
    GFX_BUFF_TYPE_COLORKEYBITBLT,
    GFX_BUFF_TYPE_COLORKEY_STRETCH_BITBLT,
    GFX_BUFF_TYPE_FILL_RECT_BLEND,
    GFX_BUFF_TYPE_STRETCH_BITBLT_BLEND,
#if ((CONFIG_CHIP_VER_CURR == CONFIG_CHIP_VER_MT8550) || (CONFIG_CHIP_VER_CURR == CONFIG_CHIP_VER_MT8555))
    // used for DirectFB Pre-multiply
    GFX_BUFF_TYPE_PM_FILL_RECT,
    GFX_BUFF_TYPE_PM_FILL_RECT_BLEND,
    GFX_BUFF_TYPE_PM_BITBLT,
    GFX_BUFF_TYPE_PM_ALPHA_COMPOSITION,
    GFX_BUFF_TYPE_PM_STRETCH_BITBLT,
    GFX_BUFF_TYPE_PM_STRETCH_BITBLT_BLEND,
#endif
    //#endif

    #ifdef GFX_SUPPORT_DOUBLE_BUFFER
    GFX_BUFF_TYPE_FLIP,
    #endif

    #ifdef GFX_SUPPORT_3D_DOUBLE_BUFFER
    GFX_BUFF_TYPE_3D_FLIP,
    #endif

    #if GFX_3D_HOR_ROTATE
    GFX_BUFF_TYPE_3DHORROTATE,
    #endif

    GFX_BUFF_TYPE_MAX
} GFX_BUFF_CMD_TYPE_T;

/// GFX  Flush Type
typedef enum
{
   GFX_DRV_FLUSH_NONE = 0,      ///< Not available.
   GFX_DRV_FORCE_FLUSH,         ///< force flush
    GFX_DRV_AUTO_FLUSH        ///< auto flush
}GFX_DRV_FLUSH_TYPE;

typedef enum _GFX_YCBCR_FORMAT_T
{
    GFX_YCBCR_420_MB  = 0,
    GFX_YCBCR_420_LNR = 1,
    GFX_YCBCR_422_LNR = 2       /* MT538x only */
} GFX_YCBCR_FORMAT_T;

typedef enum
{
    GFX_PALETTE_MSB = 0,
    GFX_PALETTE_LSB = 1,
} GFX_BYTE_ALIGNED_T;

//GFX Priority
typedef enum
{
    GFX_DRV_CMDBUF_PRIORITY_LOW = 1,       ///< Low priority, for normal image decoder driver
    GFX_DRV_CMDBUF_PRIORITY_MID = 3,       ///< Medium priority, for video decoder driver SD source using
    GFX_DRV_CMDBUF_PRIORITY_HIGH = 10,     ///< High priority, for video decoder driver HD source using
    GFX_DRV_CMDBUF_PRIORITY_HIGHEST = 15,     ///< Highest priority, for video decoder driver HD source using
    GFX_DRV_CMDBUF_PRIORITY_MAX            ///< The max
} GFX_DRV_CMDBUF_PRIORITY;

typedef struct
{
    UINT32 ui4_unused;
} *GFX_HPALETTE_T;

typedef struct _GFX_FILL_T
{
   #if 1 //def USE_RESOURCE_MANAGER 
    INT32           u4TicketId;
    UINT32            u4Flag;   
   #endif
    VOID*     __cross_space__ pv_dst;
    VOID*     __cross_space__ pv_dst2;
    INT32           i4_dst_x;
    INT32           i4_dst_y;
    UINT32          ui4_dst_pitch;
    UINT32          ui4_dst_pitch2;
    GFX_COLORMODE_T e_dst_cm;
    BOOL           b_compressed;       

    UINT32          ui4_width;
    UINT32          ui4_height;
    UINT32          ui4_color;
    UINT32          ui4ModuleID;
} GFX_FILL_T;

typedef struct _GFX_FILL_BLEND_T
{
   #if 1 //def USE_RESOURCE_MANAGER 
    INT32           u4TicketId;
    UINT32          u4Flag;   
   #endif
    VOID*     __cross_space__ pv_dst;
    VOID*     __cross_space__ pv_dst2;
    INT32           i4_dst_x;
    INT32           i4_dst_y;
    UINT32          ui4_dst_pitch;
    UINT32          ui4_dst_pitch2;
    GFX_COLORMODE_T e_dst_cm;
    BOOL            b_compressed;       

    UINT32          ui4_width;
    UINT32          ui4_height;
    UINT32          ui4_color;
    UINT32          ui4ModuleID;

    UINT8           ui1_alpha;
} GFX_FILL_BLEND_T;

typedef struct _GFX_FILL_COMPOSE_T
{
   #if 1 //def USE_RESOURCE_MANAGER 
    INT32           u4TicketId;
    UINT32          u4Flag;   
   #endif
    VOID*     __cross_space__ pv_dst;
    VOID*     __cross_space__ pv_dst2;
    INT32           i4_dst_x;
    INT32           i4_dst_y;
    UINT32          ui4_dst_pitch;
    UINT32          ui4_dst_pitch2;
    GFX_COLORMODE_T e_dst_cm;
    BOOL            b_compressed;       

    UINT32          ui4_width;
    UINT32          ui4_height;
    UINT32          ui4_color;
    UINT32          ui4ModuleID;

    UINT8           ui1_alpha;
    GFX_PD_RULE_T   e_rule;
#if ((CONFIG_CHIP_VER_CURR == CONFIG_CHIP_VER_MT8550) || (CONFIG_CHIP_VER_CURR == CONFIG_CHIP_VER_MT8555))
    UINT32          ui4_src_pm_rd;
    UINT32          ui4_dst_pm_rd;
    UINT32          ui4_dst_pm_wr;
#endif
} GFX_FILL_COMPOSE_T;

 #if 1//def USE_RESOURCE_MANAGER   

 #define COMMON_BITBLT_FIELDS        \
    INT32           u4TicketId;     \
    UINT32         u4Flag;       \
    VOID*       __cross_space__   pv_src;         \
    INT32           i4_src_x;       \
    INT32           i4_src_y;       \
    UINT32          ui4_src_pitch;  \
    GFX_COLORMODE_T e_src_cm;       \
    BOOL           b_src_compressed;       \
                                    \
    VOID*       __cross_space__    pv_dst;         \
    INT32           i4_dst_x;       \
    INT32           i4_dst_y;       \
    UINT32          ui4_dst_pitch;  \
    GFX_COLORMODE_T e_dst_cm;       \
    BOOL           b_dst_compressed;       \
                                    \
    UINT32          ui4_width;      \
    UINT32          ui4_height;     \
    GFX_YCBCR_FORMAT_T  e_ycbcr_format;     \
    VOID*           __cross_space__  pv_cbcr_or_palette;             \
    UINT32              ui4_cbcr_pitch;     \
    UINT8              ui1_ycbcr_alpha;  \
    GFX_BYTE_ALIGNED_T  e_byte_aligned;  \
    GFX_HPALETTE_T      h_palette;       \
    UINT32          ui4ModuleID;         \
    UINT32          u4_alCom_normal;       \
    UINT32          u4_src_picth_en;   
#else

#define COMMON_BITBLT_FIELDS        \
    BOOL            bSyncEn;       \
    VOID*       __cross_space__   pv_src;         \
    INT32           i4_src_x;       \
    INT32           i4_src_y;       \
    UINT32          ui4_src_pitch;  \
    GFX_COLORMODE_T e_src_cm;       \
    BOOL           b_src_compressed;       \
                                    \
    VOID*       __cross_space__    pv_dst;         \
    INT32           i4_dst_x;       \
    INT32           i4_dst_y;       \
    UINT32          ui4_dst_pitch;  \
    GFX_COLORMODE_T e_dst_cm;       \
    BOOL           b_dst_compressed;       \
                                    \
    UINT32          ui4_width;      \
    UINT32          ui4_height;

#endif  

typedef struct _GFX_BITBLT_T
{
    COMMON_BITBLT_FIELDS

    UINT8       ui1_alpha;
    
#if (CONFIG_CHIP_VER_CURR >= CONFIG_CHIP_VER_MT8550)
    UINT32 u4RollBackEn;
    UINT32 u4QulityMode; 
    UINT32 u4LineSeparate;
#endif
} GFX_BITBLT_T;

#if ((CONFIG_CHIP_VER_CURR == CONFIG_CHIP_VER_MT8550) || (CONFIG_CHIP_VER_CURR == CONFIG_CHIP_VER_MT8555))
typedef struct _GFX_PREMULT_BITBLT_T
{
    COMMON_BITBLT_FIELDS

    UINT8  ui1_alpha;

    UINT32 ui4_src_premult;
    UINT32 ui4_dst_premult;

    UINT32 u4RollBackEn;
    UINT32 u4QulityMode; 
    UINT32 u4LineSeparate;
} GFX_PREMULT_BITBLT_T;
#endif

typedef struct _GFX_ALPHA_COMPOSITION_T
{
    COMMON_BITBLT_FIELDS

    UINT8           ui1_alpha;

    GFX_PD_RULE_T   e_rule;

    BOOL            b_rect_src_option;
    UINT32          ui4_color;
} GFX_ALPHA_COMPOSITION_T;

#if ((CONFIG_CHIP_VER_CURR == CONFIG_CHIP_VER_MT8550) || (CONFIG_CHIP_VER_CURR == CONFIG_CHIP_VER_MT8555))
typedef struct _GFX_PREMULT_ALPHA_COMPOSITION_T
{
    COMMON_BITBLT_FIELDS

    UINT8           ui1_alpha;

    GFX_PD_RULE_T   e_rule;

    BOOL            b_rect_src_option;
    UINT32          ui4_color;

    UINT32          ui4_src_premult;
    UINT32          ui4_dst_premult;
} GFX_PREMULT_ALPHA_COMPOSITION_T;
#endif

typedef struct _GFX_STRETCH_BITBLT_T
{
    COMMON_BITBLT_FIELDS

    UINT32      ui4_dst_width;
    UINT32      ui4_dst_height;
    //UINT32*    pv_palette;
} GFX_STRETCH_BITBLT_T;

#if ((CONFIG_CHIP_VER_CURR == CONFIG_CHIP_VER_MT8550) || (CONFIG_CHIP_VER_CURR == CONFIG_CHIP_VER_MT8555))
typedef struct _GFX_PREMULT_STRETCH_BITBLT_T
{
    COMMON_BITBLT_FIELDS

    UINT32          ui4_dst_width;
    UINT32          ui4_dst_height;
    //UINT32*        pv_palette;

    UINT32          ui4_src_premult;
    UINT32          ui4_dst_premult;
    UINT8           ui1_alpha;
    GFX_PD_RULE_T   e_rule;
} GFX_PREMULT_STRETCH_BITBLT_T;
#endif

#if ((CONFIG_CHIP_VER_CURR == CONFIG_CHIP_VER_MT8550) || (CONFIG_CHIP_VER_CURR == CONFIG_CHIP_VER_MT8555))
typedef struct _GFX_PREMULT_STRETCH_BITBLT_BLEND_T
{
    COMMON_BITBLT_FIELDS

    UINT32      ui4_dst_width;
    UINT32      ui4_dst_height;

    UINT32      ui4_src_premult;
    UINT32      ui4_dst_premult;
    UINT8       ui1_alpha;
    GFX_PD_RULE_T   e_rule;
} GFX_PREMULT_STRETCH_BITBLT_BLEND_T;
#endif

typedef struct _GFX_CMD_BUFF_T
{
#if CONFIG_SYS_MEM_PHASE3
    UINT32          ui4_gfx_ticket_offset;
    HANDLE_T        h_MemHandle;
#endif
    UINT32          u4CmdbufOwner;
    UINT32          ui4_gfx_ticketid;
    GFX_DRV_CMDBUF_PRIORITY e_cmdbuff_priority; 
} GFX_CMD_BUFF_T;

typedef struct
{
    UINT32 ui4_unused;
} *GFX_HRGNLIST_T;

typedef struct _GFX_FLIP_T 
{
    UINT32            ui4_plane_id;
    GFX_HRGNLIST_T    rgnlist;
    UINT32            ui4_flip_id;
    BOOL              b_force;
} GFX_FLIP_T;

#ifdef GFX_SUPPORT_3D_DOUBLE_BUFFER
typedef struct _GFX_FLIP_3D_T 
{
    UINT32            ui4_plane_id;
    GFX_HRGNLIST_T    rgnlist_left;
    GFX_HRGNLIST_T    rgnlist_right;
    UINT32            ui4_flip_id;
    BOOL              b_force;
} GFX_FLIP_3D_T;
#endif

typedef struct _GFX_COLORKEY_BITBLT_T
{
    COMMON_BITBLT_FIELDS

    UINT32      b_key_sd_sel;
    UINT32      ui4_color_space_min;
    UINT32      ui4_color_space_max;
} GFX_COLORKEY_BITBLT_T;

typedef struct _GFX_COLORKEY_STRETCH_BITBLT_T
{
    COMMON_BITBLT_FIELDS

    UINT32      ui4_dst_width;
    UINT32      ui4_dst_height;

    UINT32      b_key_sd_sel;
    UINT32      ui4_color_space_min;
    UINT32      ui4_color_space_max;
} GFX_COLORKEY_STRETCH_BITBLT_T;

typedef struct _GFX_TRANSPARENT_BITBLT_T
{
    COMMON_BITBLT_FIELDS

#if 0
    UINT8       ui1_alpha;
#endif

    BOOL        b_inverse_masking;
    UINT32      ui4_color_space_min;
    UINT32      ui4_color_space_max;
} GFX_TRANSPARENT_BITBLT_T;

typedef struct _GFX_TRANSPARENT_FILL_T
{
    COMMON_BITBLT_FIELDS

#if 0
    UINT8       ui1_alpha;
#endif

    BOOL        b_inverse_masking;
    UINT32      ui4_color_space_min;
    UINT32      ui4_color_space_max;

    UINT32      ui4_fill_color;
} GFX_TRANSPARENT_FILL_T;

typedef struct _GFX_REPLACE_COLOR_T
{
    COMMON_BITBLT_FIELDS

    UINT8           ui1_alpha;

    UINT32    __local_space__ *pui4_original_color;
    UINT32    __local_space__ *pui4_new_color;
    UINT8           ui1_color_num;
} GFX_REPLACE_COLOR_T;

typedef GFX_BITBLT_T GFX_ALPHA_BLEND_T;

typedef GFX_BITBLT_T GFX_ALPHA_MUL_T;

typedef struct _GFX_BITBLT_BASE_T
{
    COMMON_BITBLT_FIELDS
} GFX_BITBLT_BASE_T;

typedef GFX_BITBLT_BASE_T GFX_ALPHAMAP_BITBLT_T;

typedef struct _GFX_YCBCR_TO_RGB
{
    COMMON_BITBLT_FIELDS

    VOID      *pv_cbcr;
    //UINT32              ui4_cbcr_pitch;
    UINT8               ui1_alpha;
    //GFX_YCBCR_FORMAT_T  e_ycbcr_format;
} GFX_YCBCR_TO_RGB_T;

typedef enum
{
    GFX_ROP_NOT_SRC = 0,
    GFX_ROP_NOT_DST,
    GFX_ROP_SRC_XOR_DST,
    GFX_ROP_SRC_XNOR_DST,
    GFX_ROP_SRC_AND_DST,
    GFX_ROP_NOT_SRC_AND_DST,
    GFX_ROP_SRC_AND_NOT_DST,
    GFX_ROP_NOT_SRC_AND_NOT_DST,
    GFX_ROP_SRC_OR_DST,
    GFX_ROP_NOT_SRC_OR_DST,
    GFX_ROP_SRC_OR_NOT_DST,
    GFX_ROP_NOT_SRC_OR_NOT_DST
} GFX_ROP_TYPE_T;

typedef struct _GFX_ROP_BITBLT_T
{
    COMMON_BITBLT_FIELDS

    GFX_ROP_TYPE_T      e_rop_type;
} GFX_ROP_BITBLT_T;

typedef struct _GFX_PLTBLT_T
{
    COMMON_BITBLT_FIELDS

    //GFX_BYTE_ALIGNED_T  e_byte_aligned;
    //GFX_HPALETTE_T      h_palette;
    //UINT32*                  pv_palette;
} GFX_PLTBLT_T;

typedef enum
{
    GFX_CLOCKWISE   = 0,
    GFX_C_CLOCKWISE,
    GFX_ROTATE_NULL
} GFX_ROTATE_FLAG_T;

typedef struct _GFX_ROTATE_T
{
    COMMON_BITBLT_FIELDS

    GFX_ROTATE_FLAG_T e_direction;
} GFX_ROTATE_T;

typedef enum _GFX_OPTION_T
{
    GFX_OPTION_COMP     = 0,
    GFX_OPTION_XOR     = 1,
} GFX_OPTION_T;

typedef struct _GFX_ROTATE_STRETCH_ALPHACOMP_T
{
    COMMON_BITBLT_FIELDS
    UINT8           ui1_alpha_assigned;
    UINT8           ui1_ac_ar;
    GFX_PD_RULE_T   e_rule;
    BOOL             b_rect_src_option;
    UINT32          ui4_color;
    UINT32          ui4_dst_width;
    UINT32          ui4_dst_height;
    GFX_OPTION_T  e_option;
    UINT32          ui4_rot_op;
} GFX_ROTATE_STRETCH_ALPHACOMP_T;  

typedef enum 
{
    E_BITBLT_SRC_MIRROR = 0,
    E_BITBLT_SRC_FLIP,
    E_BITBLT_DST_MIRROR,
    E_BITBLT_DST_FLIP,
    E_BITBLT_SRC_FLIPMIRROR,
    E_BITBLT_DST_FLIPMIRROR,
    E_BITBLT_NORMAL,
    E_BITBLT_MF_MAX
}EGFX_BITBLT_OPT_T;

typedef struct _GFX_BITBLT_MIRROR_FLIP_T
{
    COMMON_BITBLT_FIELDS

    UINT8       ui1_alpha;
    EGFX_BITBLT_OPT_T u4Opt;
    
} GFX_BITBLT_MIRROR_FLIP_T;

typedef struct _GFX_REFLECT_T
{
    COMMON_BITBLT_FIELDS
    //UINT8       ui1_alpha;
    //EGFX_BITBLT_OPT_T u4Opt;
    INT32       i4StartAlpha;
    INT32       i4EndAlpha;
    //INT32       i4AlphaHeight;
    //UINT32      u4GradeFliiMode;
    //UINT32      ui4_color;
}GFX_REFLECT_T;

typedef enum _RLE_COLORMODE_T
{
    RLE_COLORMODE_AYCbCr_CLUT2  = 0,
    RLE_COLORMODE_AYCbCr_CLUT4  = 1,
    RLE_COLORMODE_AYCbCr_CLUT8  = 2,
    RLE_COLORMODE_CbYCrY_16     = 3,
    RLE_COLORMODE_YCbYCr_16     = 4,
    RLE_COLORMODE_AYCbCr_D8888  = 5,
    RLE_COLORMODE_ARGB_CLUT2    = 6,
    RLE_COLORMODE_ARGB_CLUT4    = 7,
    RLE_COLORMODE_ARGB_CLUT8    = 8,
    RLE_COLORMODE_RGB_D565      = 9,
    RLE_COLORMODE_ARGB_D1555    = 10,
    RLE_COLORMODE_ARGB_D4444    = 11,
    RLE_COLORMODE_ARGB_D8888    = 12,
    RLE_COLORMDOE_YUV_420_BLK   = 13,
    RLE_COLORMODE_YUV_420_RS    = 14,
    RLE_COLORMDOE_YUV_422_BLK   = 15,
    RLE_COLORMODE_YUV_422_RS    = 16,
    RLE_COLORMDOE_YUV_444_BLK   = 17,
    RLE_COLORMODE_YUV_444_RS    = 18
}RLE_COLORMODE_T;

typedef struct _RLE_IMG_DIRECT_DECODE_T
{	  
    INT32           u4TicketId;   
    BOOL            bSyncEn;       
    VOID        __cross_space__    *pv_img_buf;        /* image data */
    VOID        __cross_space__    *pv_img_buf2;       /* image data2 */
    UINT32          ui4_img_size;       /* image size */
    VOID        __cross_space__    *pv_type_data;      /* type data */
		
    VOID        __cross_space__    *pv_dst;            /* destination starting address */

    UINT32          ui4_src_x;          /* x offset in the source image in pixels */
    UINT32          ui4_src_y;          /* y offset in the source image in pixels */
    UINT32          ui4_src_width;      /* width to be decoded in pixels */
    UINT32          ui4_src_height;     /* height to be decoded in pixels */

    UINT32          ui4_dst_x;          /* x offset in the destination in pixels */
    UINT32          ui4_dst_y;          /* y offset in the destination in pixels */
    UINT32          ui4_dst_width;      /* expected output width in pixels */
    UINT32          ui4_dst_height;     /* expected output height in pixels */
    UINT32          ui4_dst_pitch;      /* pitch of the destination image */
    UINT32          ui4_dst2_pitch;     /* pitch of the additional destination image */
    RLE_COLORMODE_T e_dst_cm;           /* destination color mode */    
    UINT32          ui4ModuleID;
#ifdef SUPPORT_FRAME_ACCURATE
    UINT64          ui8Tickets;
#endif
} RLE_IMG_DIRECT_DECODE_T;

typedef union _GFX_CMD_BUF_U
{   
#ifdef GFX_SUPPORT_DOUBLE_BUFFER
    GFX_FLIP_T                          rFlipCmd;
#endif
#ifdef GFX_SUPPORT_3D_DOUBLE_BUFFER
    GFX_FLIP_3D_T                       r3DFlipCmd;
#endif

    GFX_ALPHA_COMPOSITION_T             rAlphaCompositionCmd;
    GFX_FILL_T                          rFillCmd;
    GFX_BITBLT_T                        rBitbltCmd;
    GFX_TRANSPARENT_BITBLT_T            rTransparentBitbltCmd;
    GFX_TRANSPARENT_FILL_T              rTransparentFillCmd;
    GFX_REPLACE_COLOR_T                 rRplCmd;
    GFX_ALPHA_BLEND_T                   rAlphaBlendCmd;
    GFX_ALPHA_MUL_T                     rAlphaMulCmd;
    GFX_BITBLT_BASE_T                   rBitbltBaseCmd;
    GFX_STRETCH_BITBLT_T                rStretchBitbltCmd;
    GFX_ALPHAMAP_BITBLT_T               rAlphaMapBitbltCmd;
    GFX_YCBCR_TO_RGB_T                  rYc2RgbCmd;
    GFX_ROP_BITBLT_T                    rRopBitbltCmd;
    GFX_PLTBLT_T                        rPBitbltCmd;
    GFX_ROTATE_T                        rRotateCmd;
    
#if (CONFIG_CHIP_VER_CURR == CONFIG_CHIP_VER_MT8520)
    RLE_IMG_DIRECT_DECODE_T             rRleImgDirectDecodeCmd;
#endif

#ifdef GL_XOR
    GFX_ROTATE_STRETCH_ALPHACOMP_T      rRotateStretchAlphaCompCmd;
    GFX_BITBLT_MIRROR_FLIP_T            rBitbltMirrorFlipCmd;
    GFX_REFLECT_T                       rReflectCmd;
#endif

    GFX_FILL_BLEND_T                    rFillRectBlendCmd;
    GFX_COLORKEY_BITBLT_T               rColorKeyBitbltCmd;
    GFX_COLORKEY_STRETCH_BITBLT_T       rColorKeyStretchBitbltCmd;
#if ((CONFIG_CHIP_VER_CURR == CONFIG_CHIP_VER_MT8550) || (CONFIG_CHIP_VER_CURR == CONFIG_CHIP_VER_MT8555))
    GFX_FILL_T                          rPremultFillCmd;
    GFX_PREMULT_BITBLT_T                rPremultBitbltCmd;
    GFX_PREMULT_ALPHA_COMPOSITION_T     rPremultAlphaComposeCmd;
    GFX_PREMULT_STRETCH_BITBLT_T        rPremultStretchBitbltCmd;
    GFX_PREMULT_STRETCH_BITBLT_BLEND_T  rPremultStretchBitbltBlendCmd;
#endif
} GFX_CMD_BUF_U;

typedef struct _GFX_BUFF_CMD_ITEM_T
{
    //GFX_BUFF_CMD_TYPE_T e_Type; // command type
    UINT32              u4CmdType;
    //GFX_DRV_FLUSH_TYPE  eFlushType; // command type 
    UINT32              u4FlushType;
    //UINT32 u4TimeStamp; // (reserved) time stamp of the command issued
    //UINT32 u4EstDuration; // (reserved) estimated duration of this command

    //GFX_APP_INSTANCEID_T e_app_id; // (reserved) module identifier which issues this command
    //GFX_HW_INSTANCEID_T  e_hw_id; // (reserved)
    //BOOL fg_OnScreen; // (reserved) if the drawing is on on-screen surface

#if 0
    UINT32 u4CmdBuff[35]; // command data
#else
    UINT32 u4CmdBuff[(sizeof(GFX_CMD_BUF_U) + 3)/4];
#endif
    UINT32                  u4Reserved[5];
} GFX_BUFF_CMD_ITEM_T;

typedef struct _GFX_LINUX_CMDBUF_T
{
    UINT32                  u4CmdbufOwner;
    UINT32                  u4GfxCmdMaxCount;
    UINT32                  u4GfxCmdBufId;           ///< the GFXCmd Buf Id
    UINT32                  u4GfxPriority;           ///< priority
    UINT32                  u4GfxHwInstId;           ///< GFX hardware instance id.
    UINT32                  u4Reserved1[3];            // add for cache line
    UINT32                  u4GfxCurrPriority;       ///< current priority (priority will increase if not serviced)
    UINT32                  u4GfxCmdBufEvent;         ///< GFX Cmd Buf Event Handle
    UINT32                  u4RdPoint;
    UINT32                  u4GfxCmdBufState;         ///< Vg Cmd Buf state
    UINT32                  u4Reserved2[4];            // add for cache line
    UINT32                  u4WrPoint;
    UINT32                  u4Reserved3[7];            // add for cache line
#if DFB_SUPPORT_GFX_ADAPTER
    UINT32                  u4FlushFlag;
    UINT32                  u4Reserved4[7];
#endif
    UINT32                  u4GfxCmdBufCompress;
    UINT32                  u4WaitDoneState;
#if (defined(GFX_SUPPORT_DOUBLE_BUFFER) || defined(GFX_SUPPORT_3D_DOUBLE_BUFFER))
    BOOL                    fgWaitFlipDone;
    BOOL                    u4Reserved5[3];
    VOID*                   pvFlipEndBuf;
    VOID*                   pvFlipStartBuf;
    VOID*                   pvLastFlipBuf;
    UINT32                  u4Reserved6[2];
#endif
#ifdef GFX_SUPPORT_3D_DOUBLE_BUFFER
    VOID*                   pvFlipEndBufR;
    VOID*                   pvFlipStartBufR;
    VOID*                   pvLastFlipBufR;
    UINT32                  u4Reserved7[5];
#endif
} GFX_LINUX_CMDBUF_T;

// used for mmap
typedef struct _GFX_DRV_CMDBUF_T
{
    GFX_LINUX_CMDBUF_T      *prGfxDrvCmdBuf;
    VOID                    *prPrevCmdBuf;          ///< previous Cmd Buf
    VOID                    *prNextCmdBuf;          ///< Next Cmd Buffer
    UINT32                  u4Private;
    UINT32                  ui4GfxCmdBufSema;          // /< GFX Cmd Buf Same
    UINT32                  u4Reserved[3];
} GFX_DRV_CMDBUF_T;

typedef struct _MT85_ADAPTER_CMDBUF_T
{
    UINT32                  hGfxCmdBufSema;          // /< GFX Cmd Buf Same
    BOOL                    fg_compress;             //  for WT
    UINT32                  u4Private;              ///< private data, used to verify if cmd buf is valid
    UINT32                  u4GfxPriority;           ///< priority
    GFX_LINUX_CMDBUF_T      *prGfxMwCmdBuf;
} MT85_ADAPTER_CMDBUF_T;
#endif


#endif

