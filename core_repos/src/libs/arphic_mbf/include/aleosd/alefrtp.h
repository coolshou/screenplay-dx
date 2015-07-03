/*

       Arphic Layout Engine    ver $Name$
           Copyright (C) 2001-2009 Arphic Technology Co., Ltd. All rights reserved.

        Interface for FreeType: Include file

 */



#ifndef  __ARPHIC_ALEFRTP_H__
#define  __ARPHIC_ALEFRTP_H__

#include <ft2build.h>
#include FT_FREETYPE_H

#include <freetype/tttables.h>

#include "aleuser.h"



#ifdef __cplusplus
extern "C"
 {
#endif

AleFontDriverInterface *GetFreeTypeFontAleInterface (void);


    /* New Interface
       -------------------------------- */

      ALE_INT32 ALEFreeType_CalculateWorkBufferSize (FT_Library ALibrary, FT_Face AFace);
                         /*
                              Calculate necessary working buffer for font AFace.
                          */

    ALE_INT32 ALEFreeType_Initialize
         (FT_Library ALibrary, FT_Face AFace, char *AWorkBuffer, ALE_INT32 AWorkBufferSize);

        #define ALEFreeType_Insufficient_WorkBuffer  -2000
        #define ALEFreeType_Initialize_Error -2001
                     /*
                           Perform necessary initialization, including start
                             Layout Engine and other necessary operations.

                          You should start FreeType and load font yourself by
                          FreeType's API, call ALEFreeType_CalculateWorkBufferSize ()
                          to get necessary buffer size, allocate buffer and then call this
                          function to initialize LE.

                          return value: positive integer: success
                             and the return value is the size of working buffer used.

                          negative:
                             ALEFreeType_Insufficient_WorkBuffer:
                                AWorkBuffer is insufficient
                             ALEFreeType_Initialize_Error:
                                Other errors.

                             ALE_ERROR_WORKBUFFER, ALE_ERROR_DATATYPE,
                             ALE_ERROR_WORKBUFFER_32BITALIGN...
                                Layout Engine initialize error. See Layout Engine's document.
                      */


    ALE_INT32 ALEFreeType_GetMaxCharWidth (char *WorkBuf);
    ALE_INT32 ALEFreeType_GetMaxCharHeight (char *WorkBuf);
                   /* Get Maximum character height.
                       WorkBuf: working buffer of LAYOUT ENGINE
                    */

    ALE_UINT32 ALEFreeType_SetGrayscale (ALE_INT32 grayscale, char *WorkBuf);
    ALE_UINT32 ALEFreeType_GetGrayscale (char *WorkBuf);

    ALE_UINT32 ALEFreeType_SetHinting (ALE_INT32 hint, char *WorkBuf);

    ALE_UINT32 ALEFreeType_SetTypeface (ALE_INT32 flag, char *WorkBuf);

                 #define ALEFreeType_Flag_GrayScale   0x01
                 #define ALEFreeType_Flag_Hinting   0x02

                 #define ALEFreeType_Flag_Bold   0x04
                 #define ALEFreeType_Flag_Italic  0x08
                 #define ALEFreeType_Flag_AllTypeface   0x0C


    ALE_INT32 ALEFreeType_SetHoriAdvanceBias (ALE_INT16 bias, char *WorkBuf);
                     /*
                         Increase or decrease the horizontal advance of
                          all characters (except it is zero)
                          bias > 0: increase, < 0: decrease
                      */


#ifdef __cplusplus
 };
#endif

#endif
