/*****************************************
 Copyright  2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   dfbdefs.h
  @brief  A/V control definitions needed by DirectFB and shared with middleware clients, which may not be aware of Sigma implementation

  @author Sorin Otescu
  @date   2007-07-06

  $Header
  
*/

#ifndef _DFBDEFS_H_
#define _DFBDEFS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/// \defgroup dfblayers DirectFB Layer IDs
/// These values identify the video and graphic layers in DirectFB calls (example: SetMixerConfiguration)
///\ingroup hiconf
///@{
#define EM86LAYER_OSD       0	///< OSD layer (graphic)

#define EM86LAYER_BKGND     1	///< Background layer (graphic)

#define EM86LAYER_MAINVIDEO 2	///< Main video layer

#define EM86LAYER_SECVIDEO  3	///< Secondary video layer (video or graphic)

#define EM86LAYER_SECOSD 	4	///< Secondary OSD layer (graphic)

#define EM86LAYER_COUNT		5	///< Total number of layers

///@}

#ifdef __cplusplus
}
#endif


#endif // _DFBDEFS_H_

