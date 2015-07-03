/*****************************************
 Copyright  2005  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   mdefs_bdre.h
  @brief  Blu-ray rewritable media definitions shared with middleware clients
  
  @author Sebastian Manciulea
  @date   2005-11-21
  
  $Header: /bigbig/dungeon/dcchd_project/dcchd/brd/mdefs_bdre.h,v 1.26 2009-06-22 17:16:58 bsimon Exp $

*/

#ifndef _MDEFS_BDRE_
#define _MDEFS_BDRE_

#include "bd_common.h"

///\defgroup BDREMEDDEFS Blu-ray Rewritable Media Definitions, v. 2.0
/// Definitions for media with #TMediaType of #MTYPE_APP_BDRE
///\ingroup BDREMSDEFS

/// Blu-ray rewritable character codes (table 4-1, v. 2.0)
enum EBDRECharSet
{
	// 0x00 reserved
	BDRE_ISDB_J = 0x01,						/// Japanese character set for Service Information of ISDB defined in ARIB TR-B15 Ver.1.1[25]
	// 0x02 - 0x0F reserved
	BDRE_ASCII = 0x10,
	BDRE_ISO_8859_1 = 0x11,
	BDRE_ISO_8859_2 = 0x12,
	BDRE_ISO_8859_3 = 0x13,
	BDRE_ISO_8859_4 = 0x14,
	BDRE_ISO_8859_5 = 0x15,
	BDRE_ISO_8859_6 = 0x16,
	BDRE_ISO_8859_7 = 0x17,
	BDRE_ISO_8859_8 = 0x18,
	BDRE_ISO_8859_9 = 0x19,
	// 0x1A - 0x1F reserved
	BDRE_ISO_10646_1 = 0x20					/// Unicode
	// 0x21 - 0xFF reserved
};

/// Blu-ray rewritable elementary stream types

/// The values between 0 and 0xFF are defined in the BD-RE specification (table 4-14, v. 2.12D1)
///
/// Values beyond 0xFF are added by the DCC-HD specification to identify PSI/SI streams needed for playback
/// \status Video, audio, PAT, PMT, SIT and DIT implemented; the rest TBI version 2
enum EBDRECodingType
{
	// reserved 0x00
	BDRE_MPEG1v = 0x01,						/// MPEG1 video stream
	BDRE_MPEG2v = 0x02,						/// MPEG2 video stream or MPEG1 constrained parameter video stream
	BDRE_MPEG1a = 0x03,						/// MPEG1 audio
	BDRE_MPEG2a = 0x04,						/// MPEG-2 multi-channel audio, backward compatible to MPEG-1
	BDRE_MPEG2SystemPrivateSection = 0x05,	/// ITU-T Rec.H.222.0|ISO/IEC 13818-1 private sections
	BDRE_MPEG2PesPrivateData = 0x06,		/// Teletext defined in SESF/DVB or
											/// Subtitle defined in ISDB or
											/// PES packets containing streaming, synchronized data defined in ATSC or
	BDRE_ISO_13522_MHEG = 0x07,				/// ISO/IEC 13522 MHEG
	BDRE_ISO_13818_DSM_CC = 0x08,			/// ITU-T Rec.H.222.0|ISO/IEC 13818-1 Annex A DSM CC
	BDRE_ITU_H222_1 = 0x09,					/// ITU-T Rec.H.222.1
	BDRE_ISO_13818_6_A = 0x0A,				/// ISO/IEC 13818-6 type A
	BDRE_ISO_13818_6_B = 0x0B,				/// ISO/IEC 13818-6 type B
	BDRE_ISO_13818_6_C = 0x0C,				/// ISO/IEC 13818-6 type C
	BDRE_ISO_13818_6_D = 0x0D,				/// ISO/IEC 13818-6 type D
	BDRE_ISO_13818_auxiliary = 0x0E,		/// ISO/IEC 13818-1 auxiliary
	BDRE_MPEG2AAC_ADTS_TS = 0x0F,			/// MPEG-2 AAC audio with ADTS transport syntax
	// reserved 0x10 - 0x13
	BDRE_DSM_CC_ATSC = 0x14,				/// DSM-CC sections containing non-streaming, synchronized data defined in ATSC
	// reserved 0x15 - 0x1A
 	BDRE_MPEG4_AVC = 0x1B,					/// MPEG4 AVC video stream
  	// reserved 0x1C - 0x1F
	BDRE_SESF_LPCM = 0x80,					/// SESF LPCM audio
	BDRE_Dolby_AC3 = 0x81,					/// Dolby AC-3 audio
	// reserved 0x82 - 0x8F
 	BDRE_PG = 0x90,							/// Presentation graphics stream
  	// reserved 0x91 - 0x94
	BDRE_DST_NRT_ATSC = 0x95,				/// Sections conveying Data Service Table, Network Resources Table defined in ATSC
	// reserved 0x96 - 0xC1
	BDRE_PES_SSD_ATSC = 0xC2,				/// PES packets containing streaming, synchronous data defined in ATSC
	BDRE_TIP_DATA_STREAM = 0xC3,			/// Tip data stream
	// reserved 0xC4 - 0xFF
    
    BDRE_PAT = 0x100,                 		/// Program Association Table
    BDRE_PMT,                         		/// Program Map Table
    BDRE_DIT,                         		/// Discontinuuity Information Table
    BDRE_SIT,                         		/// Selection Information Table
};


/// Blu-ray rewritable video formats (table 4-15, v. 2.12D1)
enum EBDREVideoFormat
{
	// 0 reserved
	VideoFormatRE_reserved = 0,
    VideoFormatRE_480i = 1,
    VideoFormatRE_576i,
    VideoFormatRE_480p,
    VideoFormatRE_1080i,
    VideoFormatRE_720p,
    VideoFormatRE_1080p
	// 7 -14 reserved
	// 15 no information
};


/// Blu-ray rewritable video frame rates (table 4-16, v. 2.12D1)
enum EBDREVideoRate
{
	// 0 reserved
	VideoRateRE_reserved =0,
    VideoRateRE_23_97 = 1,
    VideoRateRE_24,
    VideoRateRE_25,
    VideoRateRE_29_97,
	VideoRateRE_30,
    VideoRateRE_50,
    VideoRateRE_59_94,
	VideoRateRE_60
	// 9 - 14 reserved
	// 15 no information
};

/// Blu-ray rewritable video aspect ratio (table 4-17, v. 2.12D1)
enum EBDREAspectRatio
{
	// 0 reserved
	// 1 reserved
    VideoAspectRE_4_3 = 2,
    VideoAspectRE_16_9,
	VideoAspectRE_221_100
	// 5 - 14 reserved
	// 15 no information
};

/// Blu-ray rewritable stream format identifiers
enum EBDREFormatIdentifier
{
	FormatINVALID = 0,
	FormatSESF = 1,
	FormatATSC,
	FormatISDB,
	FormatDVB,
 	FormatHDMV
};

/// 4.4.4.3.1
/// Blu-ray rewritable coding information for video elementary streams
struct SBDREVideoCodingInfo
{
#if (RMENDIANNESS == RMBIGENDIAN)
    /// specifies the video format of the video stream, s. Table 4-14
    /// #EBDREVideoFormat values
    unsigned int video_format:4;
    /// specifies the frame rate of the video stream, s. Table 4-15
    /// #EBDREVideoRate values
    unsigned int frame_rate:4;
    /// specifies aspect ratio of the video stream, s. Table 4-16
    /// #EBDREAspectRatio values
    unsigned int aspect_ratio:4;
    unsigned int reserved1:2;
    /// 1: Line 21 data as specified in SESF or ATSC exists in the picture user data of the video stream\n
    /// 0: there is no such data
    unsigned int cc_flag:1;
    /// 1: it indicates that original_video_format field and the original_aspect_ratio field exist in the StreamCodingInfo
    /// 0: these two fields do not exist
    unsigned int original_video_format_flag:1;
    /// indicates the original video format of the video stream before being transcoded
    /// #EBDREVideoFormat values
    unsigned int original_video_format:4;
    /// indicates original aspect ratio of the video stream before being transcoded
    /// #EBDREAspectRatio values
    unsigned int original_aspect_ratio:4;
    /// word alignment
    unsigned int reserved2:8;
#elif (RMENDIANNESS == RMLITTLEENDIAN)
    /// word alignment
    unsigned int reserved2:8;
    /// indicates original aspect ratio of the video stream before being transcoded
    /// #EBDREAspectRatio values
    unsigned int original_aspect_ratio:4;
    /// indicates the original video format of the video stream before being transcoded
    /// #EBDREVideoFormat values
    unsigned int original_video_format:4;
    /// 1: it indicates that original_video_format field and the original_aspect_ratio field exist in the StreamCodingInfo
    /// 0: these two fields do not exist
    unsigned int original_video_format_flag:1;
    /// 1: Line 21 data as specified in SESF or ATSC exists in the picture user data of the video stream\n
    /// 0: there is no such data
    unsigned int cc_flag:1;
    unsigned int reserved1:2;
    /// specifies aspect ratio of the video stream, s. Table 4-16
    /// #EBDREAspectRatio values
    unsigned int aspect_ratio:4;
    /// specifies the frame rate of the video stream, s. Table 4-15
    /// #EBDREVideoRate values
    unsigned int frame_rate:4;
    /// specifies the video format of the video stream, s. Table 4-14
    /// #EBDREVideoFormat values
    unsigned int video_format:4;
#endif
    /// SESF, ATSC, ISDB or DVB stream
    enum EBDREFormatIdentifier TS_format_identifier;
};

/// Blu-ray rewritable audio coding types (table 4-18, v. 2.12D1)
enum EBDREAudioType
{
	// 0 reserved
	AudioTypeRE_reserved = 0,
    AudioTypeRE_single_mono = 1,
	AudioTypeRE_dual_mono = 2,
    AudioTypeRE_stereo = 3,
	AudioTypeRE_multilingual = 4,
	AudioTypeRE_surround = 5,
    AudioTypeRE_multichannel = 6,
	// 7 - 12 reserved
    AudioTypeRE_audio_description = 13,				/// audio description for the visually impaired
	AudioTypeRE_audio_hard_hearing = 14				/// audio for the hard of hearing
	// 15 no information
};

/// Blu-ray rewritable audio sampling frequencies (table 4-19, v. 2.12D1)
enum EBDRESamplingFrequency
{
	// 0 reserved
	AudioSamplFreqRE_reserved = 0,
    AudioSamplFreqRE_48 = 1,						/// 48 kHz
    AudioSamplFreqRE_44_1 = 2,	   					/// 44.1 kHz
    AudioSamplFreqRE_32 = 3,						/// 32 kHz
	AudioSamplFreqRE_96 = 4,						/// 96 kHz
 	AudioSamplFreqRE_192 = 5,						/// 192 kHz
  	AudioSamplFreqRE_last = AudioSamplFreqRE_192
    // 6 - 14 reserved
    // 15 no information
};

/// Blu-ray rewritable SESF LPCM audio bits per sample (table 8-27, v. 2.0)
enum EBDREAudioBitsPerSample
{
	// 0 reserved
	AudioBitsPerSampleRE_16 = 1,
	AudioBitsPerSampleRE_20 = 2,
	AudioBitsPerSampleRE_24 = 3
};

/// Blu-ray rewritable main or auxiliary audio
enum EBDREAudioPathType
{
	AudioMainPath = 0,
	AudioAuxPath = 1
};
        
/// 4.4.4.3.1
/// Blu-ray rewritable coding information for audio elementary streams
struct SBDREAudioCodingInfo
{
#if (RMENDIANNESS == RMBIGENDIAN)
    /// specifies the presentation type of the audio stream, s. Table 4-17
    /// #EBDREAudioType values
    unsigned int audio_presentation_type:4;
    /// specifies the sampling frequency of the audio stream, s. Table 4-18
    /// #EBDRESamplingFrequency values
    unsigned int sampling_frequency:4;
    unsigned int reserved:8;
#elif (RMENDIANNESS == RMLITTLEENDIAN)
    unsigned int reserved:8;
    /// specifies the sampling frequency of the audio stream, s. Table 4-18
    /// #EBDRESamplingFrequency values
    unsigned int sampling_frequency:4;
    /// specifies the presentation type of the audio stream, s. Table 4-17
    /// #EBDREAudioType values
    unsigned int audio_presentation_type:4;
#endif
    enum EBDREAudioBitsPerSample bits_per_pcm_sample;   ///< bits per sample, valid only for PCM audio (retrieved from PMT)
    enum EBDREAudioPathType audio_path_type;            ///< main or auxiliary audio
};

///\ingroup BDREMEDDEFS 

/// Coding information associated with a Blu-ray rewritable elementary stream
struct SBDREStreamCodingInfo
{
    enum EBDRECodingType stream_coding_type;

    /// video/audio/pg stream coding info (not used for the other stream types)
    union 
    {
        struct SBDREVideoCodingInfo video;
        struct SBDREAudioCodingInfo audio;
        struct SPGCodingInfo pg;			///< coding info for presentation graphics substream
    }
    stream;
};

#endif //_MDEFS_BDRE_

