/************************************************************************
;
;   (C) Copyright Arphic Technology Corp. 1993-2005
;
;    Title:     Arphic Mobile Font Rasterizer
;
;    Module:    type define
;
;    Version:   1.00
;
;    Author:    Henry Huang
;
;***********************************************************************/
/*EncryptOn*/

/*#include    "alldef.h"*/
#include "platform.h"

#ifndef typedefH
#define typedefH

#define HITACHI
#define codeMARK           0x80000000L
#define codeMARK1          0x80000001L
#define maxFONT            20
#define EGT_LOAD_NO_BITMAP 0x0001
#define EGT_BITMAP_GRAY    0x0002
#define NEWCRVGENSIZE      201
#define MAXINTERSECT       14

#define      AR_CHAR        char
#define      AR_BYTE        unsigned char
#define      AR_INT16       short int
#define      AR_F2Dot14     short int
#define      AR_UINT16      unsigned short int
#define      AR_INT32       long
#define      AR_DWORD       long
#define      AR_UINT32      unsigned long
#define      AR_INT64       long long
#define      AR_VOID        void

typedef void (* PROCPTR)();

typedef struct {
    AR_UINT16  MinHeight;
	AR_F2Dot14 HorizonStroke;
    AR_F2Dot14 VerticalStroke;
    AR_F2Dot14 SlopeStroke;
}   ADJENTRY;

typedef struct {
    AR_UINT16   EntryCount;
    ADJENTRY Entrys[7];
}   ADJTABLE;

typedef struct {
	AR_INT16   MinX;
	AR_INT16   MinY;
	AR_INT16   MaxX;
	AR_INT16   MaxY;
	AR_INT16   EscX;
    AR_INT16   EscY;
}   BBOXMET;

#undef M1
typedef struct {
	AR_F2Dot14 M11;
	AR_F2Dot14 M12;
	AR_F2Dot14 M21;
	AR_F2Dot14 M22;
	AR_INT16   TX;
    AR_INT16   TY;
}   TRANSMAT;

typedef struct {
	AR_UINT16  LineMode;
	AR_INT16   y;
	AR_INT16   xl;
    AR_INT16   xr;
}   RASTERLINE;

typedef struct {
	AR_INT16   y;
	AR_INT16   xl;
	AR_INT16   xr;
}   RASTERLINEout;

typedef struct {
	AR_INT16   x1;
	AR_INT16   y1;
	AR_INT16   x2;
    AR_INT16   y2;
}   BEZIERpoint;

typedef struct {
    AR_UINT32  ptr;
    union {
        AR_UINT32  IDset[2];
        struct {
			AR_UINT16  ID;
            AR_UINT16  set;
            AR_UINT32  typeface;
        }   s;
    }   u;
#ifdef  HITACHI
	AR_INT32    off2ptr;
	AR_INT16    glyphid;
	AR_INT16    Reserved1;
#endif
}   FONT_ID;



/*---For GetEgtFont()---*/
typedef struct {
    BI_INT16   GlyphOriginX;
    BI_INT16   GlyphOriginY;
    BI_INT16   BlackBoxX;
    BI_INT16   BlackBoxY;
    BI_INT16   ReferOriginX;
    BI_INT16   ReferOriginY;
    BI_INT16   CellIncX;
    BI_INT16   CellIncY;
} CHARMET;

/*---For GetEgtFont()---*/
typedef struct  {
    BI_INT16   Height;
    BI_INT16   Ascent;
    BI_INT16   Descent;
    BI_INT16   InternalLeading;
    BI_INT16   ExternalLeading;
    BI_INT16   AveCharWidth;
    BI_INT16   MaxCharWidth;
    BI_INT16   Weight;
    BI_INT16   FirstChar;
    BI_INT16   LastChar;
    BI_INT16   DefaultChar;
	BI_INT16   BreakChar;
    BI_INT16   Italic;
    BI_INT16   Underlined;
    BI_INT16   StruckOut;
    BI_INT16   PitchAndFamily;
    BI_INT16   CharSet;
    BI_INT16   Reserved1;
    BI_INT16   MaxBoundingBox[4];
} FONTMET;

/*---For GetEgtFont()---*/
typedef struct  EGT_BITMAP_
{
    BI_INT16           Rows;
    BI_INT16           Width;
    BI_INT16           Pitch;
    BI_INT16           NumGrays;
    unsigned char*  Buffer;
    unsigned long   BufferLength;
} EGT_BITMAP;

/*---For GetEgtFont()---*/
typedef struct  EGT_FONT_
{
    BI_INT16           Code;
    BI_INT16           Height;
    BI_INT16           Width;
    BI_INT16           Reserved1;
    EGT_BITMAP      Bitmap;
    FONTMET         FontMetrics;
    CHARMET         CharMetrics;
    long            Flag;
} EGT_FONT;


/*
#define ArFunEgtSetAll       0
#define ArFunEgtRst          1
#define ArFunEgtSetWrk       2
#define ArFunEgtSetIdt       3
#define ArFunEgtSetFmt       4
#define ArFunEgtSetGray      5
#define ArFunEgtSetRotate    6
#define ArFunEgtSetSiz       7
*/
#define ArGetFntBmp 0

/*  this is original code for large size
typedef struct  SORTER_S_ {
    AR_INT32   lastHIDX;
    AR_INT32   *orderPTR;
    AR_INT32   *topHidxPTR;
    AR_INT32   *topVPTR;
    AR_INT32   *H;
}   SORTER_S;
*/

typedef struct  SORTER_S_ {
    BI_INT32   lastHIDX;
    BI_INT16   *orderPTR;
    BI_INT16   *topHidxPTR;
    BI_INT16   *topVPTR;
    BI_INT16   *H;
}   SORTER_S;


typedef AR_VOID (*ENTRY_FUNC)();
typedef AR_VOID (*CVGEN_FUNC)();

typedef struct  ArVarGlobalAll_
  {
    AR_INT32   numRASTERs ;

AR_INT16           GLRemainFntDatBit ;
AR_BYTE         GLOldIconFlag ;
AR_BYTE         GLCurrSign ;
AR_INT16           GLGr2Count ;
AR_INT16           GLGr3Count ;
AR_INT16           GLPrevPx ;
AR_INT16           GLPrevPy ;
AR_UINT32          STstrokePtr ;
AR_UINT32          STfontDataPtr ;
AR_UINT32          tmpfontDataPtr ;
AR_UINT32          tmpstrokePtr ;
AR_UINT16          GLCustomID ;
AR_UINT16          GLPreCustomID ;
AR_INT16           STfontNo ;
AR_UINT16          STstartcode ;
AR_UINT16          STfinalcode ;
AR_INT16           SToutformat ;
AR_UINT32       STout_cnt ;
AR_UINT32       STout_cnt2 ;
AR_BYTE         STerrflag ;
AR_BYTE         STsetclp ;
AR_INT16           GLadjustflag ;
AR_INT16           STclp_vmin ;
AR_INT16           STclp_hmin ;
AR_INT16           STclp_vmax ;
AR_INT16           STclp_hmax ;

AR_INT32*          GradeVal;
AR_BYTE*           GradePtr;
AR_BYTE*           GradeFlg;
AR_INT32*          SplitStk;
AR_UINT16          GLGr2Value[16];
AR_CHAR            GLGr3Value[16][2];
AR_BYTE            GLVvalary[16];
FONT_ID         STfontPtr[maxFONT];
AR_BYTE            *STworkend;
/************************* global variable *********************/
AR_INT32           GLfontsmallsize ;
AR_INT16           sRemainBit ;
AR_INT16           sRemainVal ;
AR_INT16           fWidth ;
AR_INT16           fHeight ;
AR_INT32           GLPtrCache ;
AR_INT32           GLCurrGlyphPtr ;
AR_INT32           GLCurrGlyphLen ;
AR_INT16           GLCacheFlag ;
AR_INT16           GLInBuffPtr ;
AR_INT16           GLpCount ;
AR_INT16           GLvCount ;
AR_INT32           GLBackDI ;
AR_INT32           GLGdlDataPtr ;
AR_UINT16          GLFont_Version ;
AR_UINT16          GLstkIDData ;
AR_INT32           GLLargeSizeFlag ;
AR_INT32           GLBackSI ;
AR_INT32           GLProcCallFlag ;
AR_INT32           GLFontDataPtr ;
AR_INT32           GLPathOrientation ;
AR_INT32           GLDoubleGrid ;
AR_INT32           GLGdlSPtr ;
AR_INT32           GLQuardScale ;
AR_INT32           GLQuardMask ;
AR_INT32           GLHalfScale ;
AR_INT32           GLScaleMask ;
AR_INT32           GLUnitScale ;
AR_INT32           GLV_Stem ;
AR_INT32           GLH_Stem ;
AR_INT32           GLS_Stem ;
AR_INT32           GLChn_Width ;
AR_INT32           GLChn_Height ;
AR_INT32           GLChn_Square ;
AR_INT32           GLFont_Max_Height ;
AR_INT32           GLFont_Max_Width ;
AR_INT32           l_path_incr ;
AR_INT32           l_path_ptr ;
AR_INT32           r_path_incr ;
AR_INT32           r_path_ptr ;
AR_INT32           GLResizeFactor ;
AR_INT32           GLResizeDirect;
AR_INT32           GLClosureType ;
AR_UINT16          GLstkID ;
AR_BYTE            GLFontData ;
AR_BYTE            Reserved1 ;
AR_BYTE            *STout_buf;
RASTERLINEout   *STout_r;
RASTERLINEout   *STout_r2;
BEZIERpoint     *STout_p;
AR_UINT16          GLCurrWeightTable[128];
TRANSMAT        GLCurrTransMatrix;
BBOXMET         GLCurrBoundingBox;
PROCPTR         GLPseudo_Fill_Line;
/************************* global variable *********************/
AR_BYTE            *GLGdlDataBuff;
AR_UINT16          GLPVBuff[30];
AR_UINT16          GLPBuff[30];
AR_UINT16          GLVBuff[30];
AR_UINT16          GLWeightTable[128];
AR_UINT16          GLChn_Scal[2];
AR_UINT16          GLChn_Trans[6];
AR_INT32           *pathbuff;
AR_BYTE            *GLInFileBuff;
/*--------------------------------------------- Dcrva7.c global */
AR_INT32   *Spec_r1;
AR_INT32   grid ;
AR_INT32   grid_scal ;
AR_INT32   CurrentY ;
AR_INT32   ExtendY ;
AR_INT32   FirstY ;
AR_INT32   *str_ptr;
AR_INT32   *x_grid;        /*AR_INT32  x_grid[25];*/
AR_INT32   *BoundaryY;
AR_INT32   *BoundAddress;
AR_INT16   IsQ4 ;
AR_INT16   state ;
AR_INT32   GridOffset ;
AR_INT32   p ;
AR_INT32   *x_wrk_buf;     /*AR_INT32   x_wrk_buf[61*2];*/
AR_INT32   *y_wrk_buf;     /*AR_INT32   y_wrk_buf[60*2];*/
/*--------------------------------------------- dsplat.c */
AR_INT32   *top_d_pt[2];
AR_INT32   *splt_sav[2];
AR_INT32   *spl;           /*AR_INT32   spl[146*2]; */
AR_INT32   *seg_ptr;
AR_INT16   pnt_flag , pathflag ;
AR_INT32   prevopty , linediff , startlin ;
AR_INT32   GridSave;
AR_INT16   l_p_link ;
AR_INT16   Directflag;
AR_INT32   Aa0, AAa1;
AR_INT16   numXPT ;
AR_INT16   cntOUT ;


SORTER_S frame;
AR_INT32   LrasterSEGs[16], RrasterSEGs[16];
AR_INT32   LHsegs[16], RHsegs[16];
AR_INT32   y , xl , xr ;
AR_BYTE    *ip;
AR_BYTE    xr1[2], xl1[2];
char *GLbmapbuf;
AR_INT16 GLwidthB;
AR_INT16 GLstartx;
AR_INT16 GLstarty;
AR_INT16 GLCode1;
AR_INT16		GLBoundingMinX;
AR_INT16		GLBoundingMinY;
AR_INT16		GLBoundingMaxX;
AR_INT16		GLBoundingMaxY;

AR_BYTE    patternL[8];
AR_BYTE    patternR[8];
AR_BYTE    patternL1[8][2];
AR_BYTE    patternR1[8][2];
AR_BYTE    patternL2[8][2];
AR_BYTE    patternR2[8][2];
AR_BYTE    patternL3[8][2];
AR_BYTE    patternR3[8][2];
AR_BYTE    patternL4[8][2];
AR_BYTE    patternR4[8][2];

AR_INT32   STerronVal, STerronVali2, GLPrevIconCnt, CurrHigh;
BEZIERpoint *STout_new;
AR_INT16   InNewCrvgenFlag, GLAntiAlias;
AR_INT16           GLSetRotate;
AR_BYTE    GradeCnt, ActiveCnt;
AR_BYTE    ActivePtr0[MAXINTERSECT + 5], ActivePtr1[MAXINTERSECT + 5];
AR_INT16   reserved14;
AR_BYTE    SplitStkPtr[MAXINTERSECT], SplitStkTyp[MAXINTERSECT];

AR_INT32   GLReg_r0 ;
AR_INT32   GLReg_a1 ;
AR_INT32   GLReg_a0 ;
AR_INT32   GLTrn_Inc ;
AR_INT32   GLPlineFlag ;
AR_INT32   GLLoopFlag1 ;
AR_INT32   GLPathBuffPtr ;
AR_INT32   GLPVBuffPtr ;

AR_INT32   ny , nxl , nxr ;

AR_UINT32  metricsPTR[6];
AR_UINT16  WeightTable[128];

AR_INT32   *splt_wrk[2];
AR_INT32   *lPtr;
AR_INT32   GLRegBuff[16][2];
AR_INT32   GLGdlStack[40][2];

AR_UINT16          STcode;
AR_BYTE B2Rflag1;
AR_BYTE Reserved11;
BI_INT16 BMPgrayflag, bmpflag, bmpflag1,GrayNum;

AR_VOID (*OutputEntry)();
AR_VOID (*CvGenOut)();
AR_VOID (*Xfill)();

#if BI_SMALL_WORK_BUFFER_FOR_MONO_CURVE_GEN
char curve_gen_buffer[10*1024];  /*16384*/
#else
char curve_gen_buffer[12*1024];
#endif

AR_INT32 BuffHeight;
AR_INT32 BuffWidth;
AR_INT32 ClearRasterFlag;
AR_INT16 BBoxMinX;
AR_INT16 BBoxMinY;
AR_INT16 BBoxMaxX;
AR_INT16 BBoxMaxY;
AR_INT32 bbox_flag;
} TArVarGlobalAll_forCurvGen, *PTArVarGlobalAll_forCurvGen;


typedef struct  ArVarCRV_
  {
AR_INT32   *Spec_r1;
AR_INT32   grid ;
AR_INT32   grid_scal ;
AR_INT32   CurrentY ;
AR_INT32   ExtendY ;
AR_INT32   FirstY ;
AR_INT32   *str_ptr;
AR_INT32   *x_grid;
AR_INT32   *BoundaryY;
AR_INT32   *BoundAddress;
AR_VOID    (*CvGenOut)();
AR_INT16   IsQ4 ;
AR_INT16   state ;
AR_INT32   GridOffset ;
AR_INT32   p ;
AR_INT32   *x_wrk_buf;
AR_INT32   *y_wrk_buf;
AR_INT16   l_p_link ;
AR_INT16   Reserved1 ;
AR_INT32   *top_d_pt[2];
AR_INT32   *splt_sav[2];
AR_INT32   *spl;
  } TArVarCRV, *PTArVarCRV;

  typedef struct {
    AR_INT32   x1, y1;
    AR_INT32   x2, y2;
    AR_INT32   x3, y3;
    AR_INT32   x4, y4;
} POSptr;


#endif
