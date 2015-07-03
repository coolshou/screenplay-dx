/*****************************************
 Copyright  2005  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   mdefs_vr.h
  @brief  DVD-VR definitions shared with middleware clients
  
  @author Sorin Papuc
  @date   2005-06-01
  
  $Log: mdefs_vr.h,v $
  Revision 1.6  2006-04-06 14:39:24  isarkany
  Fixed Audio Coding mode

  Revision 1.5  2006/01/30 02:46:22  sorinp
  Clarified media sapce - media type correspondence

  Revision 1.4  2006/01/13 00:24:16  sorinp
  First draft of the complete spec

  Revision 1.3  2005/11/02 10:52:07  isarkany
  Integrated sorin's changes

  Revision 1.2  2005/10/05 18:44:05  sorinp
  Mostly doc upgrades

  Revision 1.1  2005/09/29 06:27:03  sorinp
  updated the file structure and started the definitions for the DVD-VR media space

  Revision 1.7  2005/07/25 16:05:07  isarkany
  *** empty log message ***

  Revision 1.6  2005/07/07 14:00:03  rdemeter
  hmmm, too more syntax errors

  Revision 1.5  2005/06/20 21:19:48  sorinp
  doc-related fix

  Revision 1.4  2005/06/20 20:19:10  sorinp
  Made CPresEng implementation details private
  added documentation module support

  Revision 1.3  2005/06/09 21:28:27  sorinp
  Added CPresEng::WaitOnVSync; changed soem names to more used ones; updated docuemntation; removed format ID from some names, the namespace should be enough

  Revision 1.2  2005/06/05 17:20:40  sorinp
  Updated file headers

*/

#ifndef _MDEFS_VR_H_
#define _MDEFS_VR_H_

#include "mdefs.h"

///\defgroup VRMEDDEFS DVD-VR Media Space Media Definitions
/// Definitions for media with #TMediaType of #MTYPE_APP_DVDVR
///\ingroup VRMSDEFS

/// Video coding mode values
enum EVRVideoCodingType
{
    VR_MPEG1 = 0,
    VR_MPEG2
};

/// TV System values
enum EVRTVSystem
{
    VR_525_60 = 0,
    VR_625_50,
};

/// Aspect ratio values
enum EVRAspectRatio
{
    VR_4_3 = 0,
    VR_16_9
};

/// Application flag for video values
enum EVRVideoApplicationFlag
{
    VR_StaticAspectRatio = 0,   ///< the aspect ratio value in the data structure is correct
    VR_DynamicAspectRatio,      ///< the aspect ratio value in the data structure may be incorrect, use the one in RDI_PCK
};

/// NTSC video resoultion values
enum EVRNTSCVideoResolution
{
    VR_720_480 = 0,
    VR_704_480,
    VR_352_480,
    VR_352_240,
    VR_544_480,
    VR_480_480
};

/// PAL video resoultion values
enum EVRPALVideoResolution
{
    VR_720_576 = 0,
    VR_704_576,
    VR_352_576,
    VR_352_288,
    VR_544_576,
    VR_576_576
};

/// Video stream attributes
///\ingroup VRMEDDEFS
struct SVR_V_ATR
{
    unsigned int VidCompMode:2;             ///< Video compression mode - uses #EVRVideoCodingType values
    unsigned int TVSystem:2;                ///< TV system - uses #EVRTVSystem values
    unsigned int AspectRatio:2;             ///< Aspect ratio - uses #EVRAspectRatio values
    unsigned int AppFlag:2;                 ///< Application Flag - uses #EVRVideoApplicationFlag values. Ignored for Still Picture video stream
    unsigned int ln21sw1:1;                 ///< line21_switch_1 - 1 if GOP header has line 21 info for the top field, 0 if not. Ignored for Still Picture video stream
    unsigned int ln21sw2:1;                 ///< line21_switch_2 - 1 if GOP header has line 21 info for the bottom field, 0 if not. Ignored for Still Picture video stream
    unsigned int Vidres:3;                  ///< Video resolution - uses #EVRNTSCVideoResolution or #EVRPALVideoResolution values
    unsigned int reserved:3;                ///< reserved
};

/// Audio coding mode values
enum EVRAudioCodingType
{
    VR_AC3 = 0,
    VR_MPEG = 2,
    VR_MP2MC,
    VR_LPCM
};

/// Application flag for audio values
enum EVRAudioApplicationFlag
{
    VR_StaticChannelNumber = 0,   ///< the number of channles value in the data structure is correct
    VR_DynamicChannelNumber,      ///< the number of channles value in the data structure may be incorrect, or variable
};

/// Audio DRC values
enum EVRAudioDRC
{
    DRC_Present = 0,
    DRC_Absent
};

/// Audio quantization values
enum EVRQuantization
{
    QUANT_16_bits = 0
};

/// Audio quantization/DRC parameter
union UVRQuantDRC
{
    enum EVRAudioDRC mpeg;
    enum EVRQuantization lpcm;
};

/// Audio sampling rate values
enum EVRAudioSamplingRate    
{
    FS_48_KHz = 0
};

/// Audio number of channel values
enum EVRAudioChannelCount
{
    Channels_1 = 0,
    Channels_2_stereo,
    Channels_3,
    Channels_4,
    Channels_5,
    Channels_6,
    Channels_7,
    Channels_8,
    Channels_2_dual_mono = 9
};

/// Audio bitrate values
enum EVRAudioBitrate
{
    kbps_64 = 1,
    kbps_80,
    kbps_96,
    kbps_128,
    kbps_160,
    kbps_192,
    kbps_224,
    kbps_256,
    kbps_320,
    kbps_384,
    kbps_448,
    kbps_768,
    kbps_1536
};

/// Audio stream attribute
///\ingroup VRMEDDEFS
struct SVR_A_ATR
{
    unsigned int AudCodingMode:3;           ///< Audio coding mode - uses #EVRAudioCodingType values
    unsigned int reserved:3;                ///< reserved
    unsigned int AppFlag:2;                 ///< Application Flag - uses #EVRAudioApplicationFlag values. Ignored for audio stream in Still Picture streams
    unsigned int Quantization:2;            ///< Quantization/DRC - uses #UVRQuantDRC values
    unsigned int fs:2;                      ///< fs - uses #EVRAudioSamplingRate values
    unsigned int NumAudChan:4;              ///< Number of audio channels - uses #EVRAudioChannelCount values
    unsigned char Bitrate;                  ///< Bitrate - uses #EVRAudioBitrate values. Ignored for audio stream in Still Picture streams
};

/// Sub-picture Color Palette Entry
struct SVR_SP_PLT
{
    unsigned char Y;		///< Luminance signal
    unsigned char Cr; 		///< Color difference signal (Cr=R-Y)
    unsigned char Cb; 		///< Color difference signal (Cb=B-Y)           
};

/// Sub-picture Color Palette
///\ingroup VRMEDDEFS
struct SVR_SP_ATR
{
	struct SVR_SP_PLT palette[16];	///< 16 entry palette
};
    

#endif //_MDEFS_VR_H_
