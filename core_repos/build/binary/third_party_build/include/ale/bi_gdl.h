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
#define GDL_SUPPORT_SGDL 0 /* developing */

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
#elif (defined(_ICC))
typedef double         GDL_DOUBLE ;   /* 64bit, 64bit double in Hifont */
typedef double         GDL_DDLONG ;   /* 128bit double long in Hifont  */
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


#define GDL_codeMARK        0x80000000L
#define GDL_PATHBUFFSIZE    (232 + 8) /* INT32 */
#define GDL_BUFFER_SIZE     1024      /* bytes */
#define GDL_R_P_MARK        0         /* for pathbuff */
#define GDL_R_P_LINK        1
#define GDL_L_X_HEAD        2
#define GDL_L_Y_HEAD        3
#define GDL_R_X_HEAD        GDL_PATHBUFFSIZE - 4
#define GDL_R_Y_HEAD        GDL_PATHBUFFSIZE - 3
#define GDL_L_P_MARK        GDL_PATHBUFFSIZE - 2 /* for pathbuff */
#define GDL_L_P_LINK        GDL_PATHBUFFSIZE - 1


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
#if BI_SET_WEIGHT
    GDL_INT16   hstem;
    GDL_INT16   vstem;
    GDL_INT16   sstem;
    GDL_INT16   padding3;  /* for 4-byte alignment */
#endif
#if GDL_SUPPORT_SGDL
    GDL_INT32   stick_type_flag; /* 1--> stick type */
    GDL_INT32   output_grayscale256_path;
    GDL_INT16   width;
    GDL_INT16   height;
#endif
} TGData;

/* BI external routing */
#ifdef __cplusplus
extern "C"
 {
#endif
GDL_VOID  Ar_GDL_SetParaFun(TGData* GD);
GDL_VOID  Ar_GDL_SetGDLProFun(TGData* GD);
GDL_INT16 AR_GDL_Process(TGData*);
GDL_INT32 Ar_GDL_Init(TGData* GD, GDL_INT32* path_buff, GDL_BYTE* data_buff);
GDL_INT32 Ar_GDL_SetSize(TGData* GD, GDL_INT16 sh,GDL_INT16 sw, GDL_INT32 AccurateFlag);
GDL_INT32 Ar_GDL_Set_Weight(TGData* GD, GDL_INT32 vstem, GDL_INT32 hstem, GDL_INT32 sstem );
GDL_INT32 Ar_GDL_Parse(TGData* GD, GDL_BYTE* outGlyphData);
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
