/*****************************************
 Copyright  2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   cdefs_av.h
  @brief  A/V control definitions shared with middleware clients, which may not be aware of Sigma implementation

  @author Sorin Papuc
  @date   2006-04-25

  $Header: /bigbig/dungeon/dcchd_project/dcchd/core/cdefs_av.h,v 1.90.22.6 2011-05-05 22:55:22 klin Exp $

*/

#ifndef _CDEFS_AV_H_
#define _CDEFS_AV_H_

#include "mdefs.h"          // implementation-independent media definitions
#include "dfbdefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

///\defgroup hiconf High-level Output Configuration
/// API elements for specifying and controlling the user-level A/V output capabilities, preferences and current configuration.
///
/// DirectFB clients use <A HREF="directfb/IDirectFBScreen.html">IDirectFBScreen</A>, <A HREF="directfb/IDirectFBLayer.html">IDirectFBLayer</A>,
/// IAdvancedMediaProvider::SetConfiguration and IAdvancedMediaProvider::SetAdjustment calls.
///
/// \ref control level clients use the #Cmd_SetConfig and #Cmd_Adjust commands.
///
/// \ref preseng level clients use the DCCHD::CPresEng::SetConfiguration, DCCHD::CPresEng::PreConfigure or DCCHD::CPresEng::AdjustOutput calls.
///
/// All sets of calls, as well as certain internal events (media or DRM changes), generate configuration cycles
/// in which these high (user) level configuration options are converted into low (platform) level parameters
/// that are exposed through the \ref loconf mechanism to allow a client application to monitor and optionally
/// modify the configuration before it is applied.
///
/// \note
/// - The DCC-HD configuration API (except the adjustments) is best for setting long-term capabilities and preferences.
/// - The DirectFB API is best for setting short-term adjustments to the configuration resulted from the long term
/// capabilities and preferences.


/// Audio volume definition

/// Expressed as audio attenuation from +24db to -infinite
/// 0db is represented by Volume=0x10000000.
/// Shifting this value by 1 bit on the left will increase the volume by 6db. Maximum gain is 0xFFFFFFFF ~=24db.
/// Shifting the 0db value by 1 bit on the right will decrease the volume by 6db until the value reaches 0 (infinite, i.e. mute).
/// @note @li Volume is a 4.28 fix point number. Volume = 0x10000000 * 2^(Gain/6), where Gain has unit dB. range 0 -> 0xFFFFFFFF
typedef UINT32 TAudioVolume;

/// Configuration choice definition
enum EToggle
{
	TOGGLE_AUTO = 0,
	TOGGLE_OFF,
	TOGGLE_ON,
};

/// Connection status definition
enum EConnectionStatus
{
	CS_Unknown = 0,
	CS_Connected,
	CS_ConnectedSecure = 3,
	CS_Disconnected
};

/// Bass management modes \ note DO NOT CHANGE THE ORDER AS IMPLEMENTATION RELIES ON THE BINARY VALUE
enum EBassMode
{
	BM_None = 0,	///< no bass management
	BM_all_2_lfe,	///< low frequencies from all channels are extracted and passed to LFE speaker
	BM_CLsRs_2_LR,	///< low frequencies from C, Ls and Rs are extracted and passed to L and R speakers
	BM_CLsRs_2_lfe,	///< low frequencies from C, Ls and Rs are extracted and passed to LFE speaker
	BM_LsRs_2_LCR, 	///< low frequencies from Ls and Rs (Lss,Rss) are extracted and passed to L, C and R speakers
	BM_LsRs_2_lfe, 	///< low frequencies from Ls and Rs (Lss,Rss) are extracted and passed to LFE speaker
	BM_C_2_LR,  	///< low frequencies from C is extracted and passed to L and R speakers
	BM_C_2_lfe,  	///< low frequencies from C is extracted and passed to LFE speaker
	BM_Auto,		///< #BM_CLsRs_2_lfe if LFE speaker present, #BM_CLsRs_2_LR otherwise
};

/// Dynamic Range Control parameters \change Changed definition, documented 4-10-2007

/// Generic DRC parameters, mapped to format-specific DRC parameters during the configuration cycle.
///
/// Client applications can access the format-specific DRC parameters through the \ref loconf API.
///
/// \note Currently, only Dolby Digital (AC3) and Dolby TrueHD formats support DRC.
/// The settings will be ignored for all other formats.
struct SDRCParams
{
	/// DRC boost point

	/// Expressed as proportion (0 - 1=default), in 4.28 fixed decimal point format.
	/// Used only in #DRC_Custom mode, ignored in all the other #mode settings.
	/// \note Corresponds to DynScaleLo in AC3, drcboost (converted) in TrueHD
	UINT32 boost;

	/// DRC cut point

	/// Expressed as proportion (0 - 1=default), in 4.28 fixed decimal point format.
	/// Used only in #DRC_Custom mode, ignored in all the other #mode settings.
	/// \note Corresponds to DynScaleHi in AC3, drccut (converted) in TrueHD
	UINT32 cut;

	/// DRC partial compression

	/// Expressed as proportion (0 - 1=default), in 4.28 fixed decimal point format.
	/// Used only in #DRC_Custom mode, ignored in all the other #mode settings.
	/// \note Corresponds to PcmScale in AC3
	UINT32 partComp;

	/// DRC operation mode (predefined value sets of the DRC parameters boost, cut and partComp)
	enum
	{
		DRC_Off = 0,	///< no DRC is enforced
		DRC_Auto,		///< the DRC parameters in the stream are enforced.
		DRC_Custom,		///< the DRC parameters in this structure are enforced
		DRC_Max,		///< the DRC parameters with maximum possible values are enforced. Corresponds to the RF mode in AC3
	}
	mode;

	/// Dialog normalization strength

	/// Expressed as decibels of attenuation (0=default to -31) of the dialog.
	/// This parameter is independent of the #mode setting
	/// \note Corresponds to drcdialref in TrueHD
	int dialogRef;
};

// deprecated definitions, for backward compatibility
#define compressionType mode
#define COMP_analog 	DRC_Off
#define COMP_digital 	DRC_Auto
#define COMP_lineOut 	DRC_Custom
#define COMP_RF		 	DRC_Max

#define scaleLo			boost
#define scaleHi 		cut
#define scalePCM		partComp


/// Dual mode identification (for 2 channel sources only)
enum EDualMode
{
    DM_Stereo = 0,
    DM_LeftMono,
    DM_RightMono,
    DM_MixMono,
};

/// Audio Surround mode for 2.0 output
enum ESurroundMode
{
	SRND_Default = 0, ///< as specified in bitstream
	SRND_OFF = 4,
	SRND_ON
};

/// Speaker configuration definition
struct SSpeakerConfig
{
    enum EChannelConfig     speakers;   	///< Number of output channels/configuration
    int						lfe;    		///< 1 if low frequency/subwofer present, 0 if missing
    int	 					delay[8];		///< delay (in milliseconds, 0 - 33 range) per channel
    TAudioVolume 			volume[8];		///< channel volume (L, C, R, Sl, Sr, Lfe, Bl, Br for HDMI/multichannel; L, R for SPDIF) for sound field balancing
    enum ESurroundMode		surroundMode;	///< surround mode
	enum EBassMode			bassMode;		///< bass management mode
	int						centerUp;		///< raises the center channel volume by 6 db
	bool					hdmiEnable;		///< if FALSE, the HDMI chip output is disabled, but the engine is still running (bug #12254)
};

/// Audio sampling rate identifiers
enum EAudioSamplingRate
{
	FREQ_BEFORE_FIRST = 0,
	FREQ_8000,
	FREQ_11025,
	FREQ_16000,
	FREQ_22050,
	FREQ_32000,
	FREQ_44100,
	FREQ_48000,
	FREQ_88200,
	FREQ_96000,
	FREQ_176400,
	FREQ_192000,
};

#define ASRATE_TO_BITMASK(a)	(1L << (a-1))		///< #EAudioSamplingRate to bitmask conversion utility

#define AUDIO_MTYPE_TO_BITMASK(a)	(1L << (a-MTYPE_ELEM_AUDIO_FIRST))	///< Audio media type to bitmask conversion utility


/// Digital audio connection configuration definition
struct SDigitalAudioConfig
{
	enum EConnectionStatus	status;			///< connection status, updated automatically whenever possible (ex: HDMI)
	UINT32 					formats;		///< set of supported formats in bitmask form - use #AUDIO_MTYPE_TO_BITMASK to convert from #TMediaType. Set to 0 for unknown/autodetection (no format should deactivate the connection)

	/// table with supported parameters for the supported formats

	/// Index into the table is the same as the index into the bitmask
	/// (i.e. mtype - #MTYPE_ELEM_AUDIO_FIRST)
	///
	/// If the parameters are missing, assume full support
	struct
	{
		UINT32	samplingRates;					///< set of sampling rates in bitmask form - use #ASRATE_TO_BITMASK to convert from #EAudioSamplingRate
		int		maxBitrate;						///< max bitrate for compressed formats, bits per sample bitmask (bit 0 for 16 bits, bit 1 for 20 bits, bit 2 for 24 bits) for PCM
	}
	formatParamTab[MTYPE_ELEM_AUDIO_LAST + 1 - MTYPE_ELEM_AUDIO_FIRST];

	enum EChannelConfig 	pcmChannels;	///< number of channels on PCM link \note Use EChannelConfig::CCf_default for auto selection, EChannelConfig::CCf_None for PCM disable
	int 					pcmRate;		///< sample rate on PCM link \note Use 0 for auto selection

	int 					preserveOriginalBitstream;	///< if non-zero, the original compressed bitstream is send unless the receiver is not capable of using it. Any additional sounds are ignored
	int 					preserveOriginalQuality;	///< if non-zero, any additional sounds are ignored if adding them would incur quality loss (less channels, lower sampling rate). \change Added 3-15-2007
};

/// Audio output configuration definition

/// Can be used for specifying both potential and actual
/// configurations
///\ingroup hiconf
struct SAudioOutConfig
{
	int size;	///< size of the structure, to allow identification of implementation-specific structures derived from this one

	/// HDMI connection configuration
	struct
	{
		struct SDigitalAudioConfig	bitstream;			///< configuration of the bitstream link

		/// speaker configuration
		///\note Applies only for the PCM link
		///\note bassMode field is ignored (no bass management performed), as it is done by the receiver
		struct SSpeakerConfig		output;
	}
	hdmi;

	/// Multichannel analog connection configuration
	struct
	{
		enum EConnectionStatus		status;						///< connection status
		struct SSpeakerConfig		output;						///< speaker configuration
		int 						preserveOriginalQuality;	///< if non-zero, any additional sounds are ignored if adding them would incur quality loss (less channels, lower sampling rate). \change Added 3-15-2007
	}
	multiChannel;

	/// Stereo analog connection configuration \note Must be independent from the multichannel one
	struct
	{
		enum EConnectionStatus		status;			///< connection status
	    TAudioVolume 				volume[2];		///< offset from 0db, per channel
	    enum ESurroundMode			surroundMode;	///< surround mode
		enum EBassMode				bassMode;		///< bass management mode \deprecated ignored
	}
	stereo;

	/// SPDIF connection configuration
	struct
	{
		struct SDigitalAudioConfig	bitstream;	///< configuration of the bitstream link

		/// speaker configuration
		///\note Applies only for the PCM link
		///\note bassMode field is ignored (no bass management performed), as all channels are downmixed to LR anyway
		struct SSpeakerConfig		output;
	}
	spdif;

	struct SDRCParams drc;		///< Dynamic Range Control (valid only for applicable content formats - for example AC3)

    enum EDualMode dualMode;	///< dual mode (for 2 channel sources only)
};

/// TV standard definition (defined in reversed preference order)
enum ETVSystem
{
	TVSYS_Unknown = 0,
	TVSYS_VESA,
	TVSYS_CVT,
	TVSYS_SECAM,
	TVSYS_PAL,
	TVSYS_NTSC,
	TVSYS_HDTV50,	///< 50 fields/second-based High-Definition television system
	TVSYS_HDTV60,	///< 60 fields/second-based High-Definition television system
};

#define TV_SYSTEM_TO_BITMASK(a)	((1L << (a)) >> 1)		///< #ETVSystem to bitmask conversion utility

/// TV signal definition (defined in reversed preference order inside the standard-specific ranges)
enum ETVSignal
{
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //
    // !!!!! Order here must match that of the DirectFB signal definitions in directfb.h::DFBScreenOutputSignals !!!!!!!!!!!!
    // !!!!! Update also the signal name table in test/config_dump.c                                             !!!!!!!!!!!!
    //
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	TVS_Unknown = 0,
	TVS_NTSC,		///< NTSC
 	TVS_NTSC_J,		///< NTSC Japan
	TVS_SECAM,		///< SECAM
 	TVS_PAL,		///< PAL
 	TVS_PAL_M,		///< PAL M
 	TVS_PAL_60,		///< PAL 60
 	TVS_SDTV,		///< SDTV 480I/576I
 	TVS_EDTV,		///< EDTV 480P/576P
 	TVS_640x480,	///< VESA/CVT 640x480
 	TVS_800x600,	///< VESA/CVT 800x600
 	TVS_1024x768,	///< VESA/CVT 1024x768
 	TVS_1152x864,	///< VESA/CVT 1152x864
 	TVS_720p,		///< HDTV 720P/VESA 1280x720
    TVS_1280x768,	///< VESA 1280x768
 	TVS_1280x960,	///< VESA/CVT 1280x960
 	TVS_1280x1024,	///< VESA/CVT 1280x1024
    TVS_1360x768,	///< VESA 1360x768
    TVS_1366x768,	///< VESA 1366x768
 	TVS_1400x1050,	///< VESA/CVT 1400x1050
    TVS_1440x900,	///< VESA 1440x900
 	TVS_1600x1200,	///< VESA/CVT 1600x1200
    TVS_1680x1050,	///< VESA 1680x1050
    TVS_1792x1344,	///< VESA 1792x1344
    TVS_1856x1392,	///< VESA 1856x1392
 	TVS_1080i,		///< HDTV 1080I/VESA 1920x1080
 	TVS_1080p24,	///< HDTV 1080P24 (cinema source direct)
 	TVS_1080p,		///< HDTV 1080P (60/50)
    TVS_1920x1200,	///< VESA 1920x1200
    TVS_1920x1440,	///< VESA 1920x1440
 	TVS_EDID,		///< selected by HDMI EDID
};

#define TV_SIGNAL_TO_BITMASK(a)	((1L << (UINT32)(a)) >> 1)		///< #ETVSignal to bitmask conversion utility
#define STEREO_FORMAT_TO_BITMASK(a)	((1L << (UINT32)(a)) >> 1)		///< #EStereoscopicFormat to bitmask conversion utility


/// TV aspect ratio definition
enum ETVAspectRatio
{
	TVAR_Unknown = 0,
	TVAR_4x3,
	TVAR_16x9,
};

/// Closed Caption data format
enum ECCType
{
	ECC_Unknown = 0,	///< unknown
	ECC_608,			///< EIA-608 format
	ECC_708,			///< EIA-708 format
};

/// Display configuration definition
struct SDisplayConfig
{
	UINT32					system;							///< TV system(s) bitmask - use #TV_SYSTEM_TO_BITMASK to convert to and from #ETVSystem
	UINT32 					signal;							///< TV signal(s) bitmask - use #TV_SIGNAL_TO_BITMASK to convert to and from #ETVSignal
	UINT32 					preferred_signal;				///< Receiver-preferred TV signal(s) bitmask - use #TV_SIGNAL_TO_BITMASK to convert to and from #ETVSignal
	enum ETVAspectRatio		aspectRatio;					///< display's aspect ratio
	enum ETVAspectRatio		preferred_aspectRatio;			///< HDMI-preferred aspect ratio
	enum EColorSpace		colorSpace;						///< display's color space in HD modes
	enum ECCType			ccType;							///< Closed caption type
	UINT32					unsupportedHDTV50Signals;		///< signals listed in signal field (because they are supported in #TVSYS_HDTV60 mode) but are not supported in #TVSYS_HDTV50 mode; valid only when data describes capabilities rather than actual configuration \change Added 7-9-2007
	UINT32					unsupportedHDTV60Signals;		///< signals listed in signal field (because they are supported in #TVSYS_HDTV50 mode) but are not supported in #TVSYS_HDTV60 mode; valid only when data describes capabilities rather than actual configuration \change Added 7-9-2007
	UINT32					ccDepth;						///< color component depth (only valid for the HDMI output)
	enum ESamplingMode		ccSamplingMode;					///< color component sampling mode (only valid for the HDMI output)

	UINT32					stereoscopicFormat;				///< Stereoscopic TV signal format(s) bitmask - use #STEREO_FORMAT_TO_BITMASK to convert to and from #EStereoscopicFormat
	UINT32					preferred_stereoscopicFormat;	///< Receiver-preferred stereoscopic TV signal format(s) bitmask - use #STEREO_FORMAT_TO_BITMASK to convert to and from #EStereoscopicFormat
};

/// Deinterlacing mode
enum EDeXingMode
{
	DEINT_None = 0,				///< no deinterlacing, bob single field (scale up to frame size)
	DEINT_Weave,				///< weave deinterlacing, (assemble two fields to one frame)
	DEINT_Adaptive,				///< weave with best motion adaptive fallback to bob, (best results, but takes over the VCR scaler)
	DEINT_ConstantBlend = DEINT_Adaptive,	///< \deprecated by EDeXingMode::DEINT_Adaptive
	DEINT_ReverseTeleCine,		///< autodetect 3:2 pulldown content and display the original progressive frames. May cause combing artifacts in interlaced areas edited on top of the original content. Requires the VCR scaler also \change Added 2-15-2007
	DEINT_Progressive,			///< progressive deinterlacing (force 24/25fps conversion to 50/60fps using 2:3 or 2:2 pulldown)
	DEINT_Adaptive2Fields,		///< like #DEINT_Adaptive, but with only 2 reference fields \change Added 5-22-2008 for Tango3 support
};

/// Video connector configuration definition
struct SVideoOutConfigModule
{
	enum EConnectionStatus			status;		///< connection status
	struct SDisplayConfig			display;	///< display configuration
	enum EAspectRatioMatch			arMatch;	///< aspect ratio matching method
	enum EDeXingMode 				dexType;	///< de-interlacing method
	enum EToggle					cc;			///< closed caption status
};

/// Video output configuration definition

/// Can be used for specifying both potential and actual
/// configurations
///\ingroup hiconf
struct SVideoOutConfig
{
	int size;	///< size of the structure, to allow identification of implementation-specific structures derived from this one

	struct SVideoOutConfigModule hdmi;		///< HDMI/DVI-D connection configuration

	struct SVideoOutConfigModule component;	///< component/VGA/DVI-A connection configuration

	struct SVideoOutConfigModule composite;	///< composite/s-video/scart connection configuration

    unsigned int hdmiPhysicalAddress;		///< HDMI Physical Address of the device as reported by the sink \change Added 1-12-2007

	bool trueSixtyHertz;					///< if TRUE, use 60Hz for video modes, otherwise use 59Hz (and 24Hz/23Hz, respectively)
};

/// Audio panning position definition
typedef struct
{
    float x;  ///< left-right position, from -1 (left) to +1 (right)
    float y;  ///< rear-front position, from -1 (rear) to +1 (front)
}
TAudioPanning;

/// Audio metadata definition
typedef struct
{
    TAudioVolume gain;

    TAudioPanning pan;
}
TAudioMetaData;

/// Output adjustment identifiers
enum EAdjustment
{
    ADJ_MUTE = 1,				///< System-wide audio ON/OFF switch
    ADJ_VOLUME,					///< System-wide audio volume \note Does not apply to original bitstream outputs
    ADJ_MIXER_VOLUME_MAIN = 4,	///< Audio volume of the main audio substream in the media component the adjustment is applied to \note Applicable only when the audio output consists of multiple sources mixed together
    ADJ_MIXER_PAN_MAIN,			///< Position in the audio field of the main audio substream in the media component the adjustment is applied to \note Applicable only for for mono sounds of type #MTYPE_ELEM_PCM | #MTYPE_APP_BDJ and only when mixed with other audio sources
    ADJ_MIXER_VOLUME_SECONDARY,	///< Audio volume of the secondary audio substream in the media component the adjustment is applied to
    ADJ_MIXER_PAN_SECONDARY,	///< Position in the audio field of the secondary audio substream in the media component the adjustment is applied to
    ADJ_MIXER_MODE,				///< Mixing adjustments mode: automatic (based on metadata embedded in the stream) or explicit (based on the adjustment calls made by the client)
};

/// Output adjustment definition

/// Adjustments are seamless and immediate changes
/// in A/V output initiated by the user
///\ingroup hiconf
struct SAdjustment
{
	enum EAdjustment type;	///< Identifies the adjustment contained in the SAdjustment#value field

	/// Adjustment value
	union
	{
	    TAudioVolume volume; ///< value for #ADJ_VOLUME, #ADJ_MIXER_VOLUME_MAIN and #ADJ_MIXER_VOLUME_SECONDARY adjustments

	    TAudioPanning pan;	///< value for #ADJ_MIXER_PAN_MAIN and #ADJ_MIXER_PAN_SECONDARY adjustments

	    int	mute;	///< value for #ADJ_MUTE adjustment: audio output is turned ON if 0, OFF otherwise (default: 0 = audio ON)

	    int autoAdjust;	///< value for #ADJ_MIXER_MODE adjustment: explicit mixing if 0, automatic otherwise (default: 0 = automatic)
	}
	value;
};

#ifdef __cplusplus
}
#endif

#endif // _CDEFS_AV_H_

/**
  $Log: cdefs_av.h,v $
  Revision 1.90.22.6  2011-05-05 22:55:22  klin
  BugId: 30908
  2011-04-21_DCCHD_380_Stereoscopic3D.patch
  SEND_COMMENT_BUGZILLA

  Author: Christian Wolff, Christian_Wolff@sdesigns.com
  Verified by: QA
  Signed-off by: Yanquan Zhang, Yanquan_Zhang@sdesigns.com
  Branch approval: Cat Nguyen, Cat_Nguyen@sdesigns.com

  Revision 1.90.22.5  2010-05-20 11:56:19  sotescu
  BugId: none
  * added trueSixtyHertz to SGlobals; it offers the functionality of teh SIXTY_HERTZ define dynamically
  * updated audio/video config constant structures to include the new fields (the wrong fields were initialized, leading to incorrect behavior)

  Revision 1.90.22.4  2010-05-13 16:45:18  sotescu
  BugId: none
  SEND_COMMENT_BUGZILLA
  Added preferred_aspectRatio field to keep the aspect ratio of the preferred HDMI video mode.
  This field has only informational value - its contents don't change the DirectFB behavior in any way.

  Revision 1.90.22.3  2010-05-11 09:19:11  sotescu
  BugId: 12254
  SEND_COMMENT_BUGZILLA
  Added hdmiEnable field for enabling/disabling the HDMI chip output.

  Revision 1.90.22.2  2010-04-30 14:42:30  sotescu
  BugId: ct-7899
  SEND_COMMENT_BUGZILLA
  * using hdmi_pending_loop() to decide the sleep time for the HDMI thread
  * added ccSamplingMode and to DCCHD configuration and modified ccDepth, to
  control HDMI color depth and sampling mode from configPreview user functions

  Revision 1.90.22.1  2010-02-11 16:19:37  sotescu
  BugId: none
  SEND_COMMENT_BUGZILLA
  Added ccDepth parameter for HDMI color depth to SGLobals video configuration.

  Revision 1.90  2008-12-24 04:16:39  sorin
  BugId: CT-5987
  Brought the sampling rate definitions in DCC-HD and HDMI back in sync

  Revision 1.89  2008-12-16 22:52:17  sorin
  BugId: none
  Added 16 KHz sampling rate support

  Revision 1.88  2008-12-02 19:55:06  sorin
  BugId: none
  Typos

  Revision 1.87  2008-10-07 23:24:26  sorin
  BugId: none
  Doc

  Revision 1.86  2008-10-07 17:03:12  sorin
  BugId: none
  Hide internal adjustment value, used to store the volume during the MUTED state

  Revision 1.85  2008-10-07 04:05:09  sorin
  BugId: none
  Added support for global volume

  Revision 1.84  2008-09-03 23:56:26  sorin
  BugId: none
  Spelling

  Revision 1.83  2008-05-23 20:44:51  sorin
  BugId: none
  Added 2 fields adaptive deinterlacing mode

  Revision 1.82  2008-05-23 02:47:59  sorin
  BugId: none
  Audio channel delay doc update

  Revision 1.81  2008-04-29 01:14:45  sorin
  BugId: none
  Added seamless DVI display support (not working yet though due to problem in MRUA's set_outports)

  Revision 1.80  2008-04-05 01:39:32  sorin
  BugId: none
  Made and propagated API changes related to the secondary audio gain, pan and mixing control

  Revision 1.79  2007-11-20 22:23:39  sorin
  BugId: ct-3095
  Added secondary audio adjustment support

  Revision 1.78  2007/07/13 05:44:58  sbeysserie
  Fix typo (tTVSYS_HDTV50/60 instead of TVSYS_...)

  Revision 1.77  2007/07/10 03:21:36  sorinp
  BUGCT:3520 Added separate support level per TV system

  Revision 1.76  2007/07/07 23:41:42  sotescu
  BUGCT: none
  Moved scaler definitions to dfbdefs.h to reuse them in DirectFB.

  Revision 1.75  2007/07/07 23:11:53  sorinp
  Added support for external audio DSP by:
  - renaming and fixing pass-through for all for formats
  - forcing the default config with full support HDMI settings
  Also fixed some audio media types

  Revision 1.74  2007/07/05 20:33:42  sorinp
  Added SECAM TV signal

  Revision 1.73  2007/04/20 23:34:25  sorinp
  Corrected automatic merging error

  Revision 1.72  2007/04/20 21:01:59  sorinp
  BUGCT:2859 Added partComp mapped on pcmScale in AC3, changed definition of DialogRef

  Revision 1.71  2007/04/19 02:10:41  sorinp
  One more DRC fix, as per David instructions

  Revision 1.70  2007/04/13 03:22:43  sorinp
  Another typo

  Revision 1.69  2007/04/13 01:50:47  sorinp
  Ported the new DRC API and TrueHD implementation from the 1.5 branch

  Revision 1.68  2007/04/04 03:02:00  sorinp
  Merged experimental_core_audio_config_support branch

  Revision 1.67.2.1  2007/03/29 22:55:29  sorinp
  work in progress

  Revision 1.67  2007/03/21 11:59:38  sotescu
  BUGCT: none
  Added layers count.

  Revision 1.66  2007/03/19 20:54:20  sbeysserie
  Fix doxygen command typo

  Revision 1.65  2007/03/19 16:31:09  sorinp
  Moved log at the end of the file

  Revision 1.64  2007/03/15 15:15:38  sorinp
  Added Preserve Original Quality audio setting

  Revision 1.63  2007/02/21 20:25:08  sorinp
  doc update

  Revision 1.62  2007/02/15 22:09:48  sorinp
  Deprecated ConstandBlend deinterlacing mode as performance is not acceptable.
  Added ReverseTeleCine (DFB: IVTC) deinterlacing mode.

  Revision 1.61  2007/02/14 04:21:30  sorinp
  Doc upgrade

  Revision 1.60  2007/01/16 09:49:08  sotescu
  Renamed PureCinema to Progressive.

  Revision 1.59  2007/01/13 03:45:37  sorinp
  Added support for dual mono PCM sources (currently initiated only by DVD-VR). BUGCT:2175

  Revision 1.58  2007/01/13 02:20:04  sorinp
  Added HDMI physical address as per BUGCT:2254

  Revision 1.57  2006/12/22 15:34:05  sotescu
  Renamed PureCinema to Progressive.

  Revision 1.56  2006/12/22 14:08:10  sotescu
  Added PureCinema deinterlacing mode.

  Revision 1.55  2006/12/16 02:59:35  sorinp
  Merged with the version_1_0 branch (at RC34 level)

  Revision 1.54.2.1  2006/12/12 17:32:44  sorinp
  Removed change doc tags in prepearation for the official 1.0.0 release

  Revision 1.54  2006/11/29 23:58:08  sorinp
  Changed BM_Auto mapping from all_2_lfe to CLsRs_2_lfe
  Documented the fact that bass management for all but the multichannel output is ignored

  Revision 1.53  2006/11/14 05:16:34  sorinp
  Rolled back unauthorized API change.

  Revision 1.51  2006/11/02 03:53:50  sorinp
  Force compatibility between bass management option and channel configuration

  Revision 1.50  2006/10/24 16:52:48  sorinp
  Added 22, 11 and 8 KHz defintiions

  Revision 1.49  2006/10/10 03:37:12  sotescu
  Removed the OSD16 layer def.

  Revision 1.48  2006/09/26 03:06:21  sorinp
  Updated to B.6.0 level

  Revision 1.47  2006/09/20 22:06:46  sorinp
  Added aspect ratio matching capabilities in the video media format info to assist with DVD run-time configuration

  Revision 1.46  2006/09/10 21:21:42  sorinp
  doc

  Revision 1.45  2006/08/31 18:35:55  cwolff
  * Remove default use of ContstantBlend de-interlacing, use Bob instead
  * Add new driver options:
  - hdcp-always-on  (to force HDCP)
  - debug-disable-hdcp  (to disable HDCP, needs to be removed for final release!)
  - hdmi-force-rx-detection  (use HDMI Rx signal correctly at startup)
  * Initially and on exit, set up PAL/576p when NTSC/HDTV60 is excluded by driver config

  Revision 1.44  2006/08/30 00:44:32  sorinp
  set the default values to 0 fo implicit initializations

  Revision 1.43  2006/08/26 02:06:05  sorinp
  Reversed previous change, to avoid API changes

  Revision 1.41  2006/08/22 17:11:09  sotescu
  Added OSD16 layer.

  Revision 1.40  2006/08/17 23:14:16  cwolff
  * Added DARM_CROP to the aspect ratio match values: crop 4:3 content to 16:9
  * Allow to handle DARM_AUTO as intended, add new DARM_NOT_SET to take it's place

  Revision 1.39  2006/08/17 21:56:28  sorinp
  Added center up spec

  Revision 1.38  2006/08/08 01:10:44  sorinp
  Updated doc to B.4.0 level

  Revision 1.37  2006/07/29 01:38:57  sorinp
  Removed doc change notes older than B.2.0

  Revision 1.36  2006/07/27 06:03:20  sorinp
  doc update: channle map for volume values

  Revision 1.35  2006/07/19 02:20:05  sotescu
  Added AUTO aspect ratio matching.

  Revision 1.34  2006/07/13 03:53:33  sotescu
  Using proper constant names for deinterlacing modes.

  Revision 1.33  2006/07/12 21:05:15  sorinp
  Added original bitstream preservation mechanism

  Revision 1.32  2006/06/28 23:40:00  sorinp
  Added surround and bass control to the stereo connection

  Revision 1.31  2006/06/28 19:51:16  sorinp
  improved BM_Auto definition

  Revision 1.30  2006/06/27 19:33:19  sorinp
  Upgraded doc to B.2.0 level

  Revision 1.29  2006/06/27 01:22:36  sorinp
  Implemented PCMX volume and pan control

  Revision 1.28  2006/06/20 21:36:38  sorinp
  made the preferred signals a separate field to avoid conflicts with existing code (multiple bits set in the signals field)

  Revision 1.27  2006/06/19 18:25:05  sorinp
  Added preferred signals

  Revision 1.26  2006/06/19 18:09:35  sorinp
  replaced 1080pl with 1080p24

  Revision 1.25  2006/06/15 05:26:41  sorinp
  Updated and propagated changes in adjustments API

  Revision 1.24  2006/06/07 21:17:27  sorinp
  changed TV system from single value to bitfield
  Implemenetd update_video_settings by parsing the actual HDMI info
  Work in progress, compiles but may not work

  Revision 1.23  2006/06/06 02:47:02  sorinp
  fixes and updates, mostly related to av config

  Revision 1.22  2006/05/30 09:02:20  sorinp
  allow detailed bitstream settings in digital audio connections

  Revision 1.21  2006/05/30 01:50:18  sorinp
  more configuration related changes

  Revision 1.20  2006/05/28 22:06:48  sorinp
  audio configuration related changes

  Revision 1.19  2006/05/26 02:08:43  sorinp
  Added the new bass mode values as per David e-mail

  Revision 1.18  2006/05/24 08:45:06  sorinp
  implemented (not tested) HDMI audio auto detection and SPDIF/bitstream/channels control

  Revision 1.17  2006/05/24 00:51:54  sorinp
  Added DRC parameter

  Revision 1.16  2006/05/18 21:50:48  sorinp
  keep out DRC for now...

  Revision 1.15  2006/05/18 21:00:23  sorinp
  doc

  Revision 1.14  2006/05/18 18:32:45  sorinp
  added DRC param

  Revision 1.13  2006/05/16 22:20:40  sorinp
  Updates for level B.1.0

  Revision 1.12  2006/05/15 02:24:47  sorinp
  updates

  Revision 1.11  2006/05/15 01:18:14  sorinp
  new configurationscheme related changes

  Revision 1.10  2006/05/14 19:27:59  sorinp
  Updated Get/SetConfiguration syntax

  Revision 1.9  2006/05/12 15:43:39  sotescu
  Consistent output module structure.

  Revision 1.8  2006/05/10 20:02:05  sorinp
  Allow separate max rate settings for digital and analog connections

  Revision 1.7  2006/05/10 19:59:43  sorinp
  doc

  Revision 1.6  2006/05/09 03:31:01  sorinp
  Added max unsecure rate field

  Revision 1.5  2006/05/05 18:19:56  sorinp
  Updates, fixes

  Revision 1.4  2006/05/05 01:44:56  sorinp
  spec updates

  Revision 1.3  2006/05/01 17:43:40  sorinp
  Update: cjannel delay is in .1 feet rather than full feets

  Revision 1.2  2006/04/29 04:15:18  sorinp
  Updates

  Revision 1.1  2006/04/27 07:30:36  sorinp
  Updated A/V config spec, new memory allocation (static) spec

*/
