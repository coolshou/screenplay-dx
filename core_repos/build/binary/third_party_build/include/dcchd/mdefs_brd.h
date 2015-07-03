/*****************************************
 Copyright  2005  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   mdefs_brd.h
  @brief  Blu-ray media definitions shared with middleware clients
  
  @author Sorin Papuc
  @date   2005-06-01
  
  $Header: /bigbig/dungeon/dcchd_project/dcchd/brd/mdefs_brd.h,v 1.55 2009-06-22 17:16:58 bsimon Exp $

*/

#ifndef _MDEFS_BRD_
#define _MDEFS_BRD_

#include "bd_common.h"

///\defgroup BRDMEDDEFS Blu-ray Media Definitions
/// Definitions for media with #TMediaType of #MTYPE_APP_BRD
///\ingroup BRDMSDEFS

#if (RMENDIANNESS == RMBIGENDIAN)
#define BYTE_1_SHIFT    24
#define BYTE_2_SHIFT    16
#define BYTE_3_SHIFT     8
#else
#define BYTE_1_SHIFT     0
#define BYTE_2_SHIFT     8
#define BYTE_3_SHIFT    16
#endif

///\defgroup BRDRGNS Blu-ray region codes
///\ingroup BRDMEDDEFS
///@{

#define BRD_REGION_FROM_CHAR(x) (toupper(x) == 'A') ? 1 : ((toupper(x) == 'B') ? 2 : ((toupper(x) == 'C') ? 4 : 0))

#define BRD_DEFAULT_REGION		BRD_REGION_FROM_CHAR('a')

///@}


///\defgroup BRDLANGS Blu-ray language codes
/// See ISO 639-2 at 
/// http://www.loc.gov/standards/iso639-2/frelangn_ascii.html
///\ingroup BRDMEDDEFS
///@{

#define BRD_LANGUAGE_FROM_STRING(x)  (((UINT32)tolower(x[0]) << BYTE_3_SHIFT) | ((UINT32)tolower(x[1]) << BYTE_2_SHIFT) | ((UINT32)tolower(x[2]) << BYTE_1_SHIFT))

#define BRD_LANGUAGE_INVALID	BRD_LANGUAGE_FROM_STRING("---")

#define BRD_DEFAULT_LANGUAGE	BRD_LANGUAGE_FROM_STRING("eng")

///@}

///\defgroup BRDCOUNTRIES Blu-ray country codes
/// See ISO 3166
///\ingroup BRDMEDDEFS
///@{

#define BRD_COUNTRY_FROM_STRING(x)  (((UINT32)toupper(x[0]) << BYTE_2_SHIFT) | ((UINT32)toupper(x[1]) << BYTE_1_SHIFT))

#define BRD_DEFAULT_COUNTRY		BRD_COUNTRY_FROM_STRING("US")

///@}

/// Blu-ray elementary stream types (table 5-16)  
enum EBRDCodingType
{
    MPEG2 = 2,          	///< MPEG2 video
    AVC = 0x1B,     		///< MPEG4 Part 10 (AVC) video
    VC1 = 0xEA,				///< SMPTE VC-1 video

    LPCM = 0x80,    		///< LPCM for Primary audio
    DolbyDigital,   		///< AC3 for Primary audio
    DTS,            		///< DTS for Primary Audio
    DolbyLossless,  		///< Dolby Losseless for Primary audio
    DDPlusPrimary,			///< DD+ for Primary audio
    DTSHDPrimary, 			///< DTS-HD (no XLL) for Primary audio
    DTSHDXLLPrimary,		///< DTS-HD XLL for Primary audio
	DRA,					///< DRA for Primary audio
	DRAextension,			///< DRA Extension for Primary audio
    DDPlusSecondary = 0xA1,	///< DD+ for Secondary audio
    DTSHDSecondary,			///< DTS-HD for Secondary audio

    PG = 0x90,      		///< Presentation Graphics
    IG,             		///< Interactive Graphics
    TS,             		///< Text Subtitles
};

/// Blu-ray video formats (table 5-17)
enum EBRDVideoFormat
{
    VideoFormat_480i = 1,
    VideoFormat_576i,
    VideoFormat_480p,
    VideoFormat_1080i,
    VideoFormat_720p,
    VideoFormat_1080p,
    VideoFormat_576p
};

/// Blu-ray video frame rates (table 5-18)
enum EBRDVideoRate
{
    VideoRate_23_97 = 1,
    VideoRate_24,
    VideoRate_25,
    VideoRate_29_97,
    VideoRate_50 = 6,
    VideoRate_59_94
};

/// Blu-ray video aspect ratio (table 5-19)
enum EBRDAspectRatio
{
    VideoAspect_4_3 = 2,
    VideoAspect_16_9
};

/// Blu-ray coding information for video elementary streams    
struct SBRDVideoCodingInfo
{
    /// video format, frame rate, aspect ratio and cc_flag of video stream
#if (RMENDIANNESS == RMBIGENDIAN)
    unsigned char video_format:4;    ///< #EBRDVideoFormat values
    unsigned char frame_rate:4;      ///< #EBRDVideoRate values
    unsigned char aspect_ratio:4;    ///< #EBRDAspectRatio values
    unsigned char reserved1:2;
    unsigned char cc_flag:1;         ///< if 1, closed captioning data present in the stream
    unsigned char reserved2:1;
#else
    unsigned char reserved2:1;       ///< #EBRDVideoRate values
    unsigned char cc_flag:1;         ///< if 1, closed captioning data present in the stream
    unsigned char reserved1:2;
    unsigned char aspect_ratio:4;    ///< #EBRDAspectRatio values
    unsigned char frame_rate:4;
    unsigned char video_format:4;    ///< #EBRDVideoFormat values
#endif
};
    
/// Blu-ray audio coding types (table 5-20)
enum EBRDAudioType
{
    AudioType_mono = 1,
    AudioType_stereo = 3,
    AudioType_multiChannel = 6,
    AudioType_stereoBase_multiChannelExt = 12
};

/// Blu-ray audio sampling frequencies (table 5-21	)
enum EBRDAudioFrequency
{
    AudioFreq_48 = 1,
    AudioFreq_96 = 4,
    AudioFreq_192,
    AudioFreq_48Base_192Ext = 12,
    AudioFreq_48Base_96Ext = 14
};
        
/// Blu-ray coding information for audio elementary streams    
struct SBRDAudioCodingInfo
{
#if (RMENDIANNESS == RMBIGENDIAN)
    unsigned char audio_presentation_type:4; ///< #EBRDAudioType values
    unsigned char sampling_frequency:4;      ///< #EBRDAudioFrequency values
#else
    unsigned char sampling_frequency:4;      ///< #EBRDAudioFrequency values
    unsigned char audio_presentation_type:4; ///< #EBRDAudioType values
#endif
    UINT32 audio_language_code;              ///< \ref BRDLANGS
};        

/// Internation Standard Recording Code defintion - see ISO 3901. Fields coded as per ISO 646. Inavlis fields contain '0x0'
struct SISRC
{
    char country_code[2];
    char copyright_holder[3];
    char recording_year[2];
    char recording_number[5];
};

///\ingroup BRDMEDDEFS 

/// Coding information associated with a Blu-ray elementary stream
struct SBRDStreamCodingInfo
{
    unsigned char stream_coding_type; ///< #EBRDCodingType values

    union 
    {
        struct SBRDVideoCodingInfo video;	///< coding info for main and secondary video substream
        struct SBRDAudioCodingInfo audio;	///< coding info for main and secondary audio substream
        struct SPGCodingInfo pg;			///< coding info for presentation graphics substream
        struct SIGCodingInfo ig;			///< coding info for interactive graphics substream
        struct STSCodingInfo ts;			///< coding info for text subtitle substream
    }
    stream;

    struct SISRC ISRC;  ///< recording information
//    char reserved[4];
};

#endif //_MDEFS_BRD_

/**
  $Log: mdefs_brd.h,v $
  Revision 1.55  2009-06-22 17:16:58  bsimon
  BugId: none
  clean up global structures used DCCHD_BD::CPresEng class (to be continued)

  Revision 1.54  2009-05-07 13:29:37  bsimon
  BugId: none
    * BDRE/BDROM: moved all IG/PG/TS processing to DCCHD_BD::CPresEng
    * BDRE: ShowPG(true) / ShowPG(false) when playback mode changes
    * BDRE: added PG info to PBC status
    * BDRE: ChangeSubstreamParams() of PG to the PID from the clipinfo file
    * BDRE: send PTS offset inbands for PG

  New pres. engine scheme is:
    DCCHD::CPresEng <- DCCHD_BD::CPresEng <- DCCHD_BRD::CPresEng
    DCCHD::CPresEng <- DCCHD_BD::CPresEng <- DCCHD_BDRE::CPresEng

  The DCCHD_BD::CPresEng class doesn't have it's own config tables, so it can't exist on it's own. The entries for the IG/PG/TS substreams are defined by the derived class.

  Revision 1.53.2.3  2009-04-22 13:05:59  bsimon
  BugId: none
  coding info struct

  Revision 1.53.2.2  2009-03-27 12:29:39  bsimon
  BugId: none
  made mdefs headers C compiler compatible

  Revision 1.53.2.1  2009-03-26 21:44:42  bsimon
  BugId: none
  added BD specific mdefs.h

  Revision 1.53  2009-01-26 16:38:54  rdemeter
  BugId: none
  DRA implementation

  Revision 1.52  2009-01-26 16:31:12  rdemeter
  BugId: none
  DRA implementation

  Revision 1.51  2008-06-27 19:45:08  sorin
  BugId: none
  Added Quick status support for testing and certification
  Optimized doc/user info

  Revision 1.50  2008-06-27 17:40:15  rdemeter
  BugId: none
  define macro for disc region

  Revision 1.49  2008-06-02 17:19:49  sorin
  BugId: none
  Clarified coding type info

  Revision 1.48  2008-03-18 18:36:37  rdemeter
  BugId: none
  add case insensitivity for country and language code

  Revision 1.47  2007-03-28 10:29:39  rdemeter
  syntax

  Revision 1.46  2007/03/27 14:44:26  rdemeter
  add sec_video and sec_audio in SBRDStreamCodingInfo

  Revision 1.45  2007/03/23 16:18:27  rdemeter
  clean brd language list

  Revision 1.44  2007/03/20 00:15:12  sbeysserie
  Add end of line.

  Revision 1.43  2007/03/19 16:31:09  sorinp
  Moved log at the end of the file

  Revision 1.42  2007/02/14 04:21:30  sorinp
  Doc upgrade

  Revision 1.41  2006/08/17 06:54:38  sorinp
  Removed unauthorized and inconsistent definitions

  Revision 1.40  2006/08/10 06:31:57  rdemeter
  - c

  Revision 1.39  2006/08/10 01:55:00  mfedoreanu
  added vide ofrmat for ig/pg/ts

  Revision 1.38  2006/07/27 13:50:18  bsimon
  corrected lang. code for Romanian

  Revision 1.37  2006/07/21 02:10:00  rdemeter
  no message

  Revision 1.36  2006/03/27 18:42:44  rdemeter
  invalid language

  Revision 1.35  2006/02/26 02:28:43  sorinp
  feild order change for easy handling

  Revision 1.34  2006/02/08 17:38:55  sorinp
  Removed custom PCM coding type, updated doc to spec version 0.99 rev 2

  Revision 1.33  2006/02/03 15:28:11  rdemeter
  update EBRDCodingType enum to spec 99r1

  Revision 1.32  2006/01/30 02:46:16  sorinp
  Clarified media sapce - media type correspondence

  Revision 1.31  2006/01/20 14:12:03  bsimon
  changed comment

  Revision 1.30  2006/01/20 12:08:10  rdemeter
  added stream_type

  Revision 1.29  2005/10/12 13:45:24  sorinp
  doc updates

  Revision 1.28  2005/10/05 18:44:14  sorinp
  Mostly doc upgrades

  Revision 1.27  2005/10/05 16:21:07  rdemeter
  fix LE - BE VideoCodingInfo

  Revision 1.26  2005/10/04 03:50:19  sorinp
  doc fixes

  Revision 1.25  2005/10/04 03:22:17  sorinp
  Made stream number usage clear and consistent
  Removed costly and redundant langTab field in playItem
  Made language code UINT32 and made definition compiler and platform independent

  Revision 1.24  2005/09/28 14:51:19  sorinp
  doc typo

  Revision 1.23  2005/09/27 15:27:00  sorinp
  Made Blu-ray specific name unique

  Revision 1.22  2005/09/26 07:52:25  sorinp
  Made disc ID a lpb media ID field, since it will be used by all the interactive formats

  Revision 1.21  2005/09/26 07:02:01  sorinp
  removed unnecessary include

  Revision 1.20  2005/09/26 06:59:15  sorinp
  specified unsigned type

  Revision 1.19  2005/09/26 06:47:09  sorinp
  finalized linear and blu-ray control and media definition
  placed public media and control definitions in separate (and new) files
  
*/

