/************************************************************************
;
;   (C) Copyright Arphic Technology Corp. 1993-2008
;
;    Title:     Arphic Mobile Font Rasterizer
;
;    Module:    GDL for Mfont (include file)
;
;    Version:   1.00
;
;    Author:    Koffman Huang
;
;***********************************************************************/

#ifndef bi_gdlH
#define bi_gdlH

/* user define options */
#define GDL_SUPPORT_SGDL 0     /* developing */
#define GDL_SUPPORT_AUTOHINT 1   /* developing */

/* BI external routing */
#ifdef __cplusplus
extern "C"
 {
#endif

#if 1
typedef long           GDL_INT32  ;
typedef unsigned long  GDL_UINT32 ;
typedef short          GDL_INT16  ;
typedef unsigned short GDL_UINT16 ;
typedef void           GDL_VOID   ;
typedef unsigned char  GDL_BYTE   ;
typedef unsigned char  GDL_UBYTE  ;
typedef GDL_INT16      GDL_F2Dot14;

/* GreenHills compiler */
#ifdef __ghs__                          
typedef double         GDL_DOUBLE ;   /* 64bit, 64bit double in Hifont */
typedef double         GDL_DDLONG ;   /* 128bit double long in Hifont  */
#elif ((defined(_MSC_VER)) && (_MSC_VER < 1400))
typedef __int64        GDL_DOUBLE ;   /* 64bit, 64bit double in Hifont */
typedef __int64        GDL_DDLONG ;   /* 128bit double long in Hifont  */
#else
typedef long long      GDL_DOUBLE ;   /* 64bit, 64bit double in Hifont */
typedef long long      GDL_DDLONG ;   /* 128bit double long in Hifont  */
#endif

#else
#define  GDL_INT32     long
#define  GDL_UINT32    unsigne long
#define  GDL_INT16     short
#define  GDL_UINT16    unsigned short
#define  GDL_VOID      void
#define  GDL_BYTE      char
#define  GDL_UBYTE     unsigned char
#define  GDL_F2Dot14   GDL_INT16
/* GreenHills compiler */
#ifdef __ghs__
#define  GDL_DOUBLE    double   /* 64bit, 64bit double in Hifont */
#define  GDL_DDLONG    double   /* 128bit double long in Hifont  */
#else
#define  GDL_DOUBLE    long long   /* 64bit, 64bit double in Hifont */
#define  GDL_DDLONG    long long   /* 128bit double long in Hifont  */
#endif
#endif

/* GDL function prototype */
typedef GDL_VOID (*ParaFun)(GDL_VOID*);
typedef GDL_VOID (*GDLProFun)(GDL_INT32,GDL_VOID*);

enum
{
    GDL_codeMARK        = 0x80000000L,
    GDL_PATHBUFFSIZE    = 232 + 8,  /* INT32 */
    GDL_BUFFER_SIZE     = 2048      /* bytes */
};

#ifndef ___ControlPointType16___
#define ___ControlPointType16___
typedef struct {
    GDL_UINT16 firstx;
    GDL_UINT16 firsty;
    GDL_UINT16 secondx;
    GDL_UINT16 secondy;
    GDL_UINT16 thirdx;
    GDL_UINT16 thirdy;
}   BI_ControlPointType16;
#endif

typedef struct {
    GDL_INT32   y1;
    GDL_INT32   x1;
    GDL_INT32   y2;
    GDL_INT32   x2;
}   GDL_BEZIERpoint;

typedef struct {
    GDL_F2Dot14 M11;    /* =0x4000 */
    GDL_F2Dot14 M12;    /* =0      */
    GDL_F2Dot14 M21;    /* =0      */
    GDL_F2Dot14 M22;    /* =0x4000 */
    GDL_INT16   TX;
    GDL_INT16   TY;
}   GDL_TRANSMAT;

#if BI_KANJI_HINTING
typedef struct {
    GDL_INT32   y;
    GDL_INT32   x;
}   GDL_pnt;

enum
{
    MAX_GDL_ALIGN_PTS       =256,
    /* KHG_ initial stands for Kanji Half-Gray */
    KHG_INCREASE            =1<<0,
    KHG_DECREASE            =1<<1,
    KHG_GIVEN_SUBSTROKE     =1<<2,
    KHG_RECORDING           =1<<3
};

typedef struct GDL_align
{
    GDL_INT32   (*get_key)(const GDL_pnt*);
    GDL_INT32   (*get_val)(const GDL_pnt*);
    GDL_INT32   pntcnt;
    GDL_pnt     pnt[MAX_GDL_ALIGN_PTS];
    GDL_INT32   pnt_halfgray[MAX_GDL_ALIGN_PTS/32]; /* bit masks of pnt[] */
    GDL_INT16   halfgray_type;      /* Or-combination of KHG_* constants */
    GDL_UBYTE   shift_key;          /* Relavant only when KHG_GIVEN_SUBSTROKE is set */
    GDL_UBYTE   cur_key;            /* Init as 0 for each parse */
    GDL_pnt     cur_pnt;            /* Init as (-1,-1) for each parse */
}   GDL_align;
#endif

typedef struct
{
    GDL_INT32   GLRegBuff[16][2];
    GDL_INT32   GLReg_r0;      /* = 0L; */
    GDL_INT32   GLReg_a0;      /* = 0L; */
    GDL_INT32   GLReg_a1;      /* = 0L; */
    GDL_INT32   GLGdlDataPtr;  /* = 0L; */
    GDL_INT32   GLPVBuffPtr;   /* = 0L; */
	GDL_INT32   *lPtr;
	GDL_INT32   GLTrn_Inc;     /* = 0L; */
    GDL_INT32   PlineFlag;     /* = 0L; */
	GDL_INT32   LoopFlag;
	GDL_INT32   GLGdlStack[40][2];
    GDL_INT32   GLPathBuffPtr; /* = 0L; */
    ParaFun     parafun[8];
    GDLProFun   gdlprofun[172];

    /* outside */
    GDL_INT16   fWidth;
    GDL_INT16   fHeight;
    GDL_INT32   GLUnitScale;   /* 0x0010 << 4 */
    GDL_INT32   GLGdlSPtr;     /* 0 */
    GDL_BYTE*   GLGdlDataBuff;
    GDL_UINT16  GLPBuff[30];
    GDL_UINT16  GLVBuff[30];
    GDL_UINT16  GLPVBuff[30];
    GDL_INT32   GLFont_Max_Height; /* = 0L; */
    GDL_INT32   GLFont_Max_Width;  /* = 0L; */
    GDL_INT32   GLQuardScale;      /* = 0L; */
    GDL_INT32   GLQuardMask;   /* = 0L; */
    GDL_INT32   GLDoubleGrid;
    GDL_INT32   GLHalfScale;   /*= 0L; */
    GDL_INT32   GLScaleMask;
    GDL_INT32   GLV_Stem; /* = 0L; */
    GDL_INT32   GLH_Stem; /* = 0L; */
    GDL_INT32   GLS_Stem; /* = 0L; */
    GDL_INT32   GLChn_Width; /* = 0L; */
    GDL_INT32   GLChn_Height;/* = 0L; */
    GDL_INT32   GLChn_Square;/* = 0L; */
    GDL_INT32   l_path_ptr;  /* = 0L; */
    GDL_INT32   l_path_incr;
    GDL_INT32   r_path_ptr;
    GDL_INT32   r_path_incr;
    GDL_INT32   *pathbuff;
    GDL_INT32   GLPathOrientation; /* =0 */
    GDL_INT32   GLResizeDirect;
    GDL_INT32   GLResizeFactor;
    GDL_INT32   GLfontsmallsize;
    GDL_INT32   GLLargeSizeFlag;
    GDL_INT16   GLadjustflag;
    GDL_INT16   padding2;  /* for 4-byte alignment */
    GDL_TRANSMAT GLCurrTransMatrix;
    GDL_INT32   GLClosureType; /* output */
    GDL_INT32   GLBackDI; /* -1 */
    GDL_INT32   Bit_Shift; /* add for smllsize control */
#if GDL_SUPPORT_SGDL
    GDL_INT32   stick_type_flag; /* 1--> stick type */
    GDL_INT32   output_grayscale256_path;
    GDL_INT16   width;
    GDL_INT16   height;
#endif
#if BI_COMBINE_GDL_NONOVERLAP
	GDL_INT16 GDLoverlap[16];
	GDL_INT16 GDLovercnt;
	GDL_INT16 GDLoverlap2;
#endif
#if GDL_SUPPORT_AUTOHINT    /* test K-Render for GDL */
	GDL_INT32 GDLAutoHintFlag; /* bit0:horizontal, bit1:vertical */
	GDL_INT32 GDLAuoHintLevel; /* 0~255 */
#endif
#if BI_GDL_CLOSURE_TYPE
    GDL_INT32   substrokecnt;
    GDL_INT32   closure_type[16];
#endif
#if BI_KANJI_HINTING
    GDL_align   gdlalign;
    GDL_align   gdlaligny;
#endif
} TGData;

GDL_VOID  Ar_GDL_SetParaFun(TGData* GD);
GDL_VOID  Ar_GDL_SetGDLProFun(TGData* GD);
GDL_INT16 AR_GDL_Process(TGData*);
GDL_INT32 Ar_GDL_Init(TGData* GD, GDL_INT32* path_buff, GDL_BYTE* data_buff);
GDL_INT32 Ar_GDL_SetSize(TGData* GD, GDL_INT16 sh,GDL_INT16 sw, GDL_INT32 AccurateFlag);
GDL_INT32 Ar_GDL_Set_Weight(TGData* GD, GDL_INT32 vstem, GDL_INT32 hstem, GDL_INT32 sstem );
GDL_INT32 Ar_GDL_Parse(TGData* GD, GDL_BYTE* outGlyphData);
#if GDL_SUPPORT_AUTOHINT    /* test K-Render for GDL */
GDL_INT32 Ar_GDL_SetAutoHint(TGData* GD, GDL_INT32 flag, GDL_INT32 level);
GDL_INT32 Ar_GDL_GetAutoHint(TGData* GD, GDL_INT32* flag, GDL_INT32* level);
#endif
#if GDL_SUPPORT_SGDL
GDL_INT32 Ar_GDL_Parse2(TGData* GD, GDL_BYTE* outGlyphData, GDL_INT32* GlyphType);
GDL_INT32 Ar_GDL_Convert_GDL_To_Stick_Path(GDL_VOID* in_str, GDL_INT16 count,
                                           GDL_VOID* out_str, GDL_INT16* out_count,
                                           GDL_INT16 bit_shift);
GDL_INT32 Ar_GDL_Convert_GDL_To_Stick256_Path(GDL_VOID* in_str, GDL_INT16 count,
                                              GDL_VOID* out_str, GDL_INT16* out_count,
                                              GDL_INT16 bit_shift,GDL_INT16 sw, GDL_INT16 sh);
#endif
#ifdef __cplusplus
 }
#endif

#endif /* bi_gdlH */

/* END */
