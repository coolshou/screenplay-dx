/*****************************************
 Copyright  2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   mdefs.h
  @brief  Media definitions shared with middleware clients, which may not be aware of Sigma implementation

  @author Sorin Papuc
  @date   2005-06-01

  $Header: /bigbig/dungeon/dcchd_project/dcchd/core/mdefs.h,v 1.127.10.7 2011-05-05 22:55:22 klin Exp $

*/

#ifndef _MDEFS_H_
#define _MDEFS_H_

///\defgroup MEDSPACES Media Space Definitions
/// Media spaces are format-specific data and control definitions.
/// They allow a single functional interface to support any number of media formats
///
/// There are two types of media space definitions:
/// - media definitions, related to the format-specific content
/// - control definitions, related to the format-specific handling of the content
///\ingroup control
///\ingroup DFBAMP

///\defgroup COMMSDEFS Common Media Space Definitions
/// These definitions are common to any media space
///
/// The following basic types must be defined by the modules using these definitions:
/// - INT32 - 32 bit integer
/// - UINT32 - 32 bit unsigned integer
/// - INT64 - 64 bit integer
/// - UINT64 - 64 bit unsigned integer
///\ingroup MEDSPACES

///\defgroup COMMDEFS Common Media Space Media Definitions
/// These media definitions are common to any media space
///\ingroup COMMSDEFS

///\defgroup TRES Common Result Code and Value Definitions
///\ingroup COMMDEFS
///@{

/// Result code returned by all media-related methods.

/// A complex type coded in an UINT32:
/// - 1 bit (MSB) error flag
/// - 1 bit (MSB-1) success flag
/// - 30 bits for call specific result value, described in the call specification
///
/// Beside the error/success status flags, the rest of the TResultCode carries values that are specific to
/// each of the function and can have different meaning depending on whether it is an error or a success result.
/// The most general values are defined here, although may be overwritten by individual function specifications
typedef UINT32 TResultCode;

//
// TResultCode flags handling
//
#define TRESULT_ERROR       (1 << 31)                                       ///< TResultCode flag denoting that the operation failed

#define TRESULT_SUCCESS     (1 << 30)                                       ///< TResultCode flag denoting that the operation succeeded

#define TRESULT_PENDING     0                                               ///< TResultCode flag value denoting that the operation is pending

#define IS_ERROR(a)         (((INT32)(a)) < 0)                                ///< verifies that the operation failed

#define IS_SUCCESS(a)       (((a) & TRESULT_SUCCESS) != 0)                    ///< verifies that the operation succeeded

#define IS_PENDING(a)       (((a) & (TRESULT_ERROR | TRESULT_SUCCESS)) == 0)  ///< verifies that the operation is pending (neither success nor error)

//
// TResultCode value handling
//
#define TRESULT_VALUE(a)        ((a) & ~(TRESULT_ERROR | TRESULT_SUCCESS))    ///< extracts the value of the result

///
/// Result value definitions (error or success codes)
///
#define RESULT_DEFAULT              0   ///< generic success code

#define RESULT_ERROR                0   ///< generic error code (recoverable in the current state)

#define RESULT_BUSY                 1   ///< the specified action can not be taken at this time; it may succeed later

#define RESULT_NOT_AVAILABLE        2   ///< the specified item is currently not available

#define RESULT_NOT_PERMITTED        3   ///< the specified action is not permitted in the current context

#define RESULT_INVALID              4   ///< the specified action or parameter are invalid

#define RESULT_NO_MEM               5   ///< there is not enough memory

#define RESULT_UNIMPLEMENTED        7   ///< feature not implemented

#define RESULT_NOT_READY            8   ///< not initialized/not ready for use

#define RESULT_PROTECTED            9   ///< info/item is protected, may require access credentials

#define RESULT_OUT_OF_SYNC          10  ///< timing does not match

#define RESULT_IO                   11  ///< Input/Output problem

#define RESULT_FAILURE              0x100   ///< generic failure (must reset failed entity)

///@}


///\defgroup EMTYPE Elementary Media Formats
/// Identifies the format of the individual media component.
///
/// May be further characterized by the container and application formats.
///
/// Not all the formats listed must be supported, they have been listed for completion and clarity.
/// Check capability for actual support info.
///@{
#define MTYPE_ELEM_NONE             0x0000  ///< no elementary data exists or the format is irrelevant

#define MTYPE_ELEM_UNKNOWN          0x00FF  ///< elementary data exists, is relevant but the format is unknown


#define MTYPE_ELEM_VIDEO_FIRST      0x0010      ///< video formats are enumerated from this to #MTYPE_ELEM_VIDEO_LAST
#define MTYPE_ELEM_MPEG1            0x0010
#define MTYPE_ELEM_MPEG2            0x0011
#define MTYPE_ELEM_MPEG4            0x0012
#define MTYPE_ELEM_AVC              0x0013

#define MTYPE_ELEM_VC1              0x0014

#define MTYPE_ELEM_DIVX3            0x0015
#define MTYPE_ELEM_DIVX4            0x0016

#define MTYPE_ELEM_WMV              0x0017
#define MTYPE_ELEM_VIDEO_UNKNOWN	0x003F  	///< any video type or the primary video in complex media formats
#define MTYPE_ELEM_VIDEO_LAST       0x003F      ///< video formats are enumerated from #MTYPE_ELEM_VIDEO_FIRST to this

#define MPTYPE_ELEM_IS_VIDEO(x)     (((x & MTYPE_ELEMENTARY_MASK)>=MTYPE_ELEM_VIDEO_FIRST) && ((x & MTYPE_ELEMENTARY_MASK)<=MTYPE_ELEM_VIDEO_LAST)) ///< macro for checking whether a #TMediaType value is an elementary video value
#define MTYPE_ELEM_HAS_VIDEO(x)     MPTYPE_ELEM_IS_VIDEO(x)

#define MTYPE_ELEM_AUDIO_FIRST      0x0040      ///< audio formats are enumerated from this to #MTYPE_ELEM_AUDIO_LAST, in the same order as HDMI (see CEA-861 specification)
#define MTYPE_ELEM_PCM              0x0040      ///< any form of PCM, details must be provided (usually through #SMediaFormat)
#define MTYPE_ELEM_AC3              0x0041      ///< AAC (Dolby Digital)
#define MTYPE_ELEM_MP1              0x0042      ///< MPEG1 layer 1&2
#define MTYPE_ELEM_MP2              0x0042      ///< same as #MTYPE_ELEM_MP1
#define MTYPE_ELEM_MP3              0x0043      ///< MPEG1 layer 3
#define MTYPE_ELEM_MP2MC            0x0044      ///< MPEG2 multichannel
#define MTYPE_ELEM_MPA              0x0044      ///< same as #MTYPE_ELEM_MP2MC
#define MTYPE_ELEM_AAC              0x0045      ///< AAC
#define MTYPE_ELEM_DTS              0x0046      ///< DTS
#define MTYPE_ELEM_ATRAC            0x0047      ///< ATRAC
#define MTYPE_ELEM_OneBit           0x0048      ///< One Bit Audio (SACD)
#define MTYPE_ELEM_DDP              0x0049      ///< Dolby Digital +
#define MTYPE_ELEM_DTSHD            0x004A      ///< DTS-HD, use bitrate info for identification of normal, LBR and MA subtypes
#define MTYPE_ELEM_DLLS             0x004B      ///< MAT(MLP) DolbyDigital Lossless (TrueHD)
#define MTYPE_ELEM_DST              0x004C      ///< ISO/IEC 14496-3 subpart 10
#define MTYPE_ELEM_WMAPRO           0x004D      ///< WMA Pro
#define MTYPE_ELEM_WMA              0x004E      ///< WMA - (not listed by HDMI, inserted in a whole in the HDMI enumeration)
#define MTYPE_ELEM_AACP             0x004F      ///< AAC Plus (ISO/IEC 14496-3:2005)
#define MTYPE_ELEM_AACPv2           0x0050      ///< AAC Plus v2 (ISO/IEC 14496-3:2005/AMD2:2006)
#define MTYPE_ELEM_MPSR             0x0051      ///< MPEG Surround (ISO/IEC 23003-1:2007)
#define MTYPE_ELEM_DRA              0x0052      ///< DRA (not listed by HDMI), use bitrate info for identification of normal or extension subtypes
#define MTYPE_ELEM_AUDIO_UNKNOWN    0x0053      ///< any audio type or the primary audio in complex media formats
#define MTYPE_ELEM_AUDIO_LAST       0x0053      ///< audio formats are enumerated from #MTYPE_ELEM_AUDIO_FIRST to this, in the same order as HDMI
#define MPTYPE_ELEM_IS_AUDIO(x)     (((x & MTYPE_ELEMENTARY_MASK)>=MTYPE_ELEM_AUDIO_FIRST) && ((x & MTYPE_ELEMENTARY_MASK)<=MTYPE_ELEM_AUDIO_LAST)) ///< macro for checking whether a #TMediaType value is an elementary audio value

#define MTYPE_ELEM_SPU              0x0090
#define MTYPE_ELEM_SPUHD            0x0091


#define MTYPE_ELEM_IG               0x00A0
#define MTYPE_ELEM_PG               0x00A1
#define MTYPE_ELEM_TS               0x00A2


#define MTYPE_ELEM_IMAGE_FIRST      0x00B0      ///< image formats are enumerated from this to #MTYPE_ELEM_IMAGE_LAST
#define MTYPE_ELEM_JPEG             0x00B0
#define MTYPE_ELEM_GIF              0x00B1
#define MTYPE_ELEM_PNG              0x00B2
#define MTYPE_ELEM_BMP              0x00B3
#define MTYPE_ELEM_TIFF             0x00B4
#define MTYPE_ELEM_PIXMAP           0x00BF      ///< uncompressed pixel map, details must be provided (usually through #SMediaFormat)
#define MTYPE_ELEM_IMAGE_LAST       0x00BF      ///< image formats are enumerated from #MTYPE_ELEM_IMAGE_FIRST to this
#define MPTYPE_ELEM_IS_IMAGE(x)     (((x & MTYPE_ELEMENTARY_MASK)>=MTYPE_ELEM_IMAGE_FIRST) && ((x & MTYPE_ELEMENTARY_MASK)<=MTYPE_ELEM_IMAGE_LAST)) ///< macro for checking whether a #TMediaType value is an elementary image value


#define MTYPE_ELEM_ASCII            0x00C1
#define MTYPE_ELEM_UTF8             0x00C2
#define MTYPE_ELEM_TTFONT           0x00C3  ///< TrueType font data

#define MTYPE_ELEM_OTFONT           0x00C4  ///< OpenType font data


#define MTYPE_ELEM_BINDATA          0x00F0  ///< any binary data

#define MTYPE_ELEM_FONT             0x00F1  ///< any graphics type

#define MTYPE_ELEM_VIDEO            0x00F2  ///< any video type or the primary video in complex media formats

#define MTYPE_ELEM_AUDIO            0x00F3  ///< any audio type or the primary audio in complex media formats

#define MTYPE_ELEM_GRAPHICS         0x00F4  ///< any graphics type or the primary graphics in complex media formats

#define MTYPE_ELEM_RESERVED         0x00FE  ///< reserved value

///@}

///\defgroup CMTYPE Container Media Formats
/// Identifies the format of the container for the individual media component.
///
/// May be further characterized by the application format.
///@{
#define MTYPE_CONT_NONE             0x0000  ///< no container data exists or the format is irrelevant

#define MTYPE_CONT_UNKNOWN          0xFF00 ///< container data exists, is relevant but the format is unknown

#define MTYPE_CONT_M1SYS            0x0100  ///< MPEG1 System format

#define MTYPE_CONT_M2PES            0x0200  ///< MPEG2 PES format

#define MTYPE_CONT_M2TS             0x0300  ///< MPEG2 Transport format

#define MTYPE_CONT_AVI              0x0400  ///< Microsoft AVI format

#define MTYPE_CONT_ASF              0x0500  ///< Microsoft ASF format

#define MTYPE_CONT_JFIF             0x0600  ///< JPEG JFIF format

#define MTYPE_CONT_WNOISE           0x0700  ///< White noise generator - use it with #MTYPE_ELEM_PCM | #MTYPE_APP_CALIBRATION

#define MTYPE_CONT_MP4              0x0800  ///< MPEG4 format

#define MTYPE_CONT_MKV              0x0900  ///< MKV format

#define MTYPE_CONT_RESERVED         0xFE00  ///< reserved value

///@}

///\defgroup AMTYPE Application Media Formats
/// Identifies the composite media format.
///
/// May be futher characterized by the implementation format
///@{
#define MTYPE_APP_NONE              0x000000    ///< no application data exists or the format is irrelevant

#define MTYPE_APP_UNKNOWN           0xFF0000    ///< application data exists, is relevant but the format is unknown

#define MTYPE_APP_CDA               0x010000   ///< Audio compact disc (CD-DA)

#define MTYPE_APP_VCD               0x020000   ///< VideoCD disc

#define MTYPE_APP_SVCD              0x030000   ///< Super VideoCD disc

#define MTYPE_APP_DVD               0x040000   ///< DVD-Video disc

#define MTYPE_APP_DVDA              0x050000   ///< DVD-Audio disc

#define MTYPE_APP_DVDVR             0x060000   ///< DVD re(writable) disc (DVD-VR)

#define MTYPE_APP_HDDVD             0x070000   ///< HD-DVD disc

#define MTYPE_APP_BDROM             0x080000   ///< Blu-ray movie disc

#define MTYPE_APP_BDRE              0x090000   ///< BD-RE 2.x (re)writable video disc

#define MTYPE_APP_BDRE_RREF         0x0A0000   ///< Blu-ray editable video recording (BD-RE 3.x RREF)

#define MTYPE_APP_BDRE_PBCA         0x0B0000   ///< Blu-ray movie recording (BD-RE 3.x write once)

#define MTYPE_APP_AVCHD             0x0C0000   ///< AVCHD video disc

#define MTYPE_APP_ATSC              0x0D0000   ///< ATSC broadcast

#define MTYPE_APP_DVB               0x0E0000   ///< DVB broadcast

#define MTYPE_APP_CAP               0x0F0000   ///< A/V capture application

#define MTYPE_APP_CALIBRATION       0x100000   ///< A/V calibration tool - use it with #MTYPE_ELEM_PCM | #MTYPE_CONT_WNOISE

#define MTYPE_APP_INTERACTIVE       0x110000   ///< generic interactive application; when used with #MTYPE_ELEM_PCM it identifies interactive (asynchronous) PCM data with arbitrary parameters

#define MTYPE_APP_RESERVED          0xFE0000   ///< reserved value
#define MTYPE_APP_ACAP                      0x200000   /// Audio capture

///@}

#define MTYPE_APP_HDMV              MTYPE_APP_AVCHD  ///< \deprecated by #MTYPE_APP_AVCHD

#define MTYPE_APP_BRD               MTYPE_APP_HDMV   ///< \deprecated by #MTYPE_APP_HDMV

#define MTYPE_APP_BDJ               MTYPE_APP_BDROM  ///< \deprecated by #MTYPE_APP_BDROM


///\defgroup IMTYPE Implementation Media Formats
/// Implementation-specific media format identifiers
///@{
#define MTYPE_IMPL_DEFAULT          0x0000000   ///< default implementation

#define MTYPE_IMPL_SHELL            0x1000000   ///< Shell application that handles multiple media types

#define MTYPE_IMPL_ACCESS_DENIED    0x2000000   ///< Access to the media is denied

///@}

///\defgroup MTYPEHELP Media Type Macros
/// Useful utilities for manipulating #TMediaType values
///@{
#define MTYPE_ELEMENTARY_MASK       0x000000FF  ///< mask for extracting the elementary format from #TMediaType values

#define MTYPE_CONTAINER_MASK        0x0000FF00  ///< mask for extracting the container format from #TMediaType values

#define MTYPE_APPLICATION_MASK      0x00FF0000  ///< mask for extracting the application format from #TMediaType values

#define MTYPE_IMPLEMENTATION_MASK   0xFF000000  ///< mask for extracting the implementation format from #TMediaType values

#define GET_ELEMENTARY_MTYPE(x)     (((TMediaType)x) & MTYPE_ELEMENTARY_MASK)   ///< macro for extracting the elementary format from #TMediaType values

#define GET_CONTAINER_MTYPE(x)      (((TMediaType)x) & MTYPE_CONTAINER_MASK)    ///< macro for extracting the container format from #TMediaType values

#define GET_APPLICATION_MTYPE(x)    (((TMediaType)x) & MTYPE_APPLICATION_MASK)  ///< macro for extracting the application format from #TMediaType values

#define GET_IMPLEMENTATION_MTYPE(x) (((TMediaType)x) & MTYPE_IMPLEMENTATION_MASK)  ///< macro for extracting the implementation format from #TMediaType values

#define GET_ELEMENTARY_MINDEX(x)    GET_ELEMENTARY_MTYPE(x)                 ///< macro for extracting the elementary format index from #TMediaType values

#define GET_CONTAINER_MINDEX(x)     (GET_CONTAINER_MTYPE(x) >> 8)           ///< macro for extracting the container format index from #TMediaType values

#define GET_APPLICATION_MINDEX(x)   (GET_APPLICATION_MTYPE(x) >> 16)        ///< macro for extracting the application format index from #TMediaType values

#define GET_IMPLEMENTATION_MINDEX(x) (GET_IMPLEMENTATION_MTYPE(x) >> 24)    ///< macro for extracting the implementation format index from #TMediaType values

///@}

/// Media type identifier

/// The media type contains four fields: \ref EMTYPE, \ref CMTYPE, \ref AMTYPE and \ref IMTYPE
///
/// By combining them media can be identified in complex and precise ways, for example:
///
/// Blu-ray disc: #MTYPE_APP_BRD
///
/// Blu-ray navigation data: #MTYPE_APP_BRD | #MTYPE_ELEM_BINDATA
///
/// Blu-ray transport stream: #MTYPE_APP_BRD | #MTYPE_CONT_M2TS . In this case,
/// specifying the application type is mandatory as it identifies the specific
/// 192-byte Transport Stream packet used by Blu-ray
///
/// BD-J video drips (low delay mode MPEG2): #MTYPE_ELEM_MPEG2 | #MTYPE_APP_BDJ
///
/// Blu-ray interactive audio: #MTYPE_ELEM_PCM | #MTYPE_APP_BDJ
///
/// Blu-ray LPCM audio (LPCM with Blu-ray specific header): #MTYPE_ELEM_PCM | #MTYPE_APP_BRD
///
/// The \ref MTYPEHELP are useful for manipulating media type definitions
///\ingroup COMMDEFS
typedef UINT32 TMediaType;


/// Pixel format, used to describe pixmaps
enum EPixelFormat
{
    PF_NONE = 0,   ///< no format, invalidates the rest of the storage parameters
    PF_RGB8,       ///< paletezized 8 bpp
    PF_RGB555,     ///< 16 bpp, MSB empty
    PF_RGB565,     ///< 16 bpp
    PF_RGB24,      ///< 24 bpp
    PF_ARGB32,     ///< alpha in MSByte
    PF_I420,       ///< color implicit of half stride, aligned on 2xstride boundary
    PF_I422,
    PF_I444
};

/// image color space
enum EColorSpace
{
    CS_Default = 0,
    CS_RGB_16_235,
    CS_RGB_0_255,
    CS_YUV_601,
    CS_YUV_709
};

/// image sampling mode
enum ESamplingMode
{
    SM_Default = 0,
    SM_4_2_0,
    SM_4_2_2,
    SM_4_4_4
};


enum EAspectRatioType
{
    ARType_Picture = 1, // use default picture aspect ratio and disable inband/outband
    ARType_Pixel,       // pixel aspect ratio of the surface should be provided
    ARType_Display      // display aspect ratio of the surface should be provided
};

/// Content to display aspect ratio matching method definition
enum EAspectRatioMatch      // the order counts; DON'T CHANGE IT
{
    ARM_NotSet = 0, ///< Not set, select best ARM
    ARM_Auto,       ///< Use the best mode for the current display and content
    ARM_LetterBox,  ///< Display is 4:3, letterbox 16:9 content
    ARM_PanScan,    ///< Display is 4:3, pan scan 16:9 content
    ARM_SidePanel,  ///< Display is 16:9, side panel 4:3 content
    ARM_Crop,       ///< Display is 16:9, crop top and bottom of 4:3 content (letterbox removal)
    ARM_Zoom,       ///< Display is 4:3, show center of 16:9 content
    ARM_Panorama,   ///< Display is 16:9, nonlinear stretch of 4:3 content
    ARM_No,         ///< No matching, pass through the source as is
};

/// Stereoscopic image format definition
enum EStereoscopicFormat
{
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    //
    // !!!!! Order here must match that of the DirectFB signal definitions in directfb.h::DFBStereoscopicFormat  !!!!!!!!!!!!
    // !!!!! Update also the format name table in test/config_dump.c                                             !!!!!!!!!!!!
    //
    // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	SSFMT_Unknown = 0,			///< None/Unknown/Autodetected stereoscopic format
	SSFMT_SideBySideHalf,		///< Side by Side (Half) stereoscopic format
	SSFMT_TopAndBottomHalf,		///< Top and Bottom (Half) stereoscopic format
	///\todo List all 3D formats
};

/// Parameters for displaying an image
struct SImageDisplayDesc
{
    int width;          						///< width in pixels
	int height;         						///< height in pixels
	int aspectX;        						///< if non-zero, pixel aspect ratio X
    int aspectY;        						///< if non-zero, pixel aspect ratio Y
    int interlaced;     						///< if non-zero, the alternate lines belong to different moments in time
    int telecine;       						///< if non-zero, the content is a tele-cine conversion of film material
    int rateM;          						///< if non-zero, display field rate, in rateM/rateN fields per second
    int rateN;          						///< if non-zero, display field rate, in rateM/rateN fields per second
    enum EColorSpace colorSpace;    			///< color space in which the pixel value are encoded in
    int rotation;								///< rotation to be applied to the image, in 0-359 degrees counter clockwise
    UINT32 aspectMatchCaps;						///< bitmask - see #ASPECT_MATCH_TO_BITMASK - identifying the aspect ratio matching strategies compatible with the image. Set to 0 if no particular preference exists.
	enum EAspectRatioType ARtype;				///< AspectRatio type (display, picture, pixel)
	int pixelAligned;							///< if TRUE, the pixels are aligned with pixels of other, overlapped media

	enum EStereoscopicFormat stereoscopicFormat;///< Stereoscopic format
};

#define ASPECT_MATCH_TO_BITMASK(a)  ((1L << ((UINT32)a)) >> 1)      ///< Aspect ratio match to bitmask conversion utility, to be used in SImageDisplayDesc::aspectMatchCaps manipulations


/// Parameters for storing an image (storage buffer not included, must be provided separately)
struct SImageStorageDesc
{
    enum EPixelFormat format;
    int stride;         ///< number of bytes between the start of two consecutive lines. For planar formats, it refers to luma plane
};

/// Pixmap parameters definition
struct SPixmapDesc
{
    struct SImageDisplayDesc display; ///< display parameters
    struct SImageStorageDesc storage; ///< storage parameters
};

/// Windows Media Video parameters definition
struct SWMVDesc
{
    struct SImageDisplayDesc image;     ///< display parameters (usually width and height), leave 0 if unknown
    UINT32 sequence_code;               ///< sequence code
};

/// PCM sample format, used to describe PCM buffers

/// It specify implicitly direction, alignment, etc
/// Add identifiers here as new types are exposed
enum EPCMSampleFormat
{
    SF_NONE = 0,    ///< no format, invalidates the rest of the storage parameters
    SF_PCM,
    SF_LPCM,
};

/// Audio channel configuration

/// - L = front left, R = front right, C = front center,
/// - S = surround center, Sl = surround left, Sr = surround right
/// - B = back center, Bl = back left,  Br = back right
///
/// Conventions:
/// - bit 0 = C channel
/// - values 1-15 equal the number of channels
enum EChannelConfig
{
    CCf_default = -1,           ///< configuration not specified, use default/best match
    CCf_none,                   ///< no channels available
    CCf_C,                      ///< 1/0
    CCf_LR,                     ///< 2/0
    CCf_LCR,                    ///< 3/0
    CCf_LRSlSr,                 ///< 2/2
    CCf_LCRSlSr,                ///< 3/2
    CCf_LRSlSrBlBr,             ///< 2/2/2
    CCf_LCRSlSrBlBr,            ///< 3/2/2
    CCf_DualMono = 0x10,        ///< 1+1
    CCf_CS,                     ///< 1/1
    CCf_LRS,                    ///< 2/1
    CCf_LCRS,                   ///< 3/1
    CCf_LCRB = CCf_LCRS + 2,    ///< 3/0/1
    CCf_LRBlBr,                 ///< 2/0/2
    CCf_LCRBlBr,                ///< 3/0/2
    CCf_LRSlSrB,                ///< 2/2/1
    CCf_LCRSlSrB,               ///< 3/2/1
    CCf_unsupported = 0x7FFF,
    CCf_FormatSpecific = 0x8000,///< if set, the rest of the value is defined by content standard (ex.: DVD LPCM)
};


enum EChannelConfiguration
{
    CCfg_default = -1,   ///< configuration not specified, use default/best match
    CCfg_none,           ///< no channels available

    CCfg_l=1,           ///< front left channel identifier
    CCfg_c=2,           ///< front center channel identifier
    CCfg_r=4,           ///< front right channel identifier

    CCfg_sl=CCfg_l << 4,    ///< surround left channel identifier
    CCfg_s=CCfg_c << 4, ///< surround center channel identifier
    CCfg_sr=CCfg_r << 4,    ///< surround right channel identifier

    CCfg_bl=CCfg_l << 8,    ///< back left channel identifier
    CCfg_b=CCfg_c << 8, ///< back center channel identifier
    CCfg_br=CCfg_r << 8,    ///< back right channel identifier

    CCfg_lfe=0x00100000,    ///< low frequency effects (sub-woofer) channel identifier, to be used for testing/ adding channels in complete configuration codes

    CCfg_all=CCfg_l|CCfg_c|CCfg_r|CCfg_sl|CCfg_s|CCfg_sr|CCfg_bl|CCfg_b|CCfg_br|CCfg_lfe,   ///< all individual channels

    CCfg_normal     = 0x00000008,   ///< flag (bit 3) signaling normal stereo, rather than dual mono
    CCfg_generic        = 0x00800000,   ///< flag (bit 26) signaling a generic, rather than actual configuration. The difference is in the way LFE is counted - separate for an actual configuration, included in the main channel count for a generic one

    CCfg_all_ch_ids = CCfg_lfe | CCfg_l | CCfg_c | CCfg_r | CCfg_sl | CCfg_s | CCfg_sr | CCfg_bl | CCfg_b | CCfg_br,    ///< the set of all channels (used mostly internally)
    CCfg_1      = 0x01000000 | CCfg_generic | CCfg_normal | CCfg_all_ch_ids,///< any 1 channel configuration, compares greater than any 1 channel actual configuration
    CCfg_2      = 0x02000000 | CCfg_generic | CCfg_normal | CCfg_all_ch_ids,///< any 2 channel configuration, compares greater than any 2 channel actual configuration
    CCfg_3      = 0x03000000 | CCfg_generic | CCfg_normal | CCfg_all_ch_ids,///< any 3 channel configuration, compares greater than any 3 channel actual configuration
    CCfg_4      = 0x04000000 | CCfg_generic | CCfg_normal | CCfg_all_ch_ids,///< any 4 channel configuration, compares greater than any 4 channel actual configuration
    CCfg_5      = 0x05000000 | CCfg_generic | CCfg_normal | CCfg_all_ch_ids,///< any 5 channel configuration, compares greater than any 5 channel actual configuration
    CCfg_6      = 0x06000000 | CCfg_generic | CCfg_normal | CCfg_all_ch_ids,///< any 6 channel configuration, compares greater than any 6 channel actual configuration
    CCfg_7      = 0x07000000 | CCfg_generic | CCfg_normal | CCfg_all_ch_ids,///< any 7 channel configuration, compares greater than any 7 channel actual configuration
    CCfg_8      = 0x08000000 | CCfg_generic | CCfg_normal | CCfg_all_ch_ids,///< any 8 channel configuration, compares greater than any 8 channel actual configuration
    CCfg_9      = 0x09000000 | CCfg_generic | CCfg_normal | CCfg_all_ch_ids,///< any 9 channel configuration, compares greater than any 9 channel actual configuration
    CCfg_10     = 0x0A000000 | CCfg_generic | CCfg_normal | CCfg_all_ch_ids,///< any 10 channel configuration, compares greater than any 10 channel actual configuration

    CCfg_C          = (0x01000000 | CCfg_normal        | CCfg_c),                                                               ///< 1/0
    CCfg_Mono       = CCfg_C,                                                                                                   ///< normal mono, same as #CCfg_C
    CCfg_1pt0       = CCfg_C,                                                                                                   ///< 1.0, same as #CCfg_C
    CCfg_LR         = (0x02000000 | CCfg_normal | CCfg_l| CCfg_r),                                                      ///< 2/0
    CCfg_Stereo     = CCfg_LR,                                                                                                  ///< stereo, same as #CCfg_LR
    CCfg_2pt0       = CCfg_LR,                                                                                                  ///< 2.0, same as #CCfg_LR
    CCfg_DualMono   = (0x02000000               | CCfg_l           | CCfg_r),                                                       ///< dual mono (1+1), compares smaller than stereo, but has the same channel count and values
    CCfg_LCR        = (0x03000000 | CCfg_normal | CCfg_l | CCfg_c| CCfg_r),                                                     ///< 3/0
    CCfg_CS         = (0x02000000 | CCfg_normal          | CCfg_c                   | CCfg_s),                                      ///< 1/1
    CCfg_LRS        = (0x03000000 | CCfg_normal | CCfg_l | CCfg_r | CCfg_s),                                                        ///< 2/1
    CCfg_LCRS       = (0x04000000 | CCfg_normal | CCfg_l | CCfg_c | CCfg_r          | CCfg_s),                                      ///< 3/1
    CCfg_LRSlSr     = (0x04000000 | CCfg_normal | CCfg_l           | CCfg_r | CCfg_sl           | CCfg_sr),                             ///< 2/2
    CCfg_LCRSlSr    = (0x05000000 | CCfg_normal | CCfg_l | CCfg_c | CCfg_r | CCfg_sl            | CCfg_sr),                             ///< 3/2
    CCfg_5pt1       = (CCfg_LCRSlSr | CCfg_lfe),                                                                                    ///< 3/2.1
    CCfg_CSB        = (0x03000000 | CCfg_normal          | CCfg_c                   | CCfg_s                      | CCfg_b),                ///< 1/1/1
    CCfg_LRSlSrBlBr = (0x06000000 | CCfg_normal | CCfg_l           | CCfg_r | CCfg_sl           | CCfg_sr | CCfg_bl       | CCfg_br),   ///< 2/2/2
    CCfg_LCRSlSrB   = (0x06000000 | CCfg_normal | CCfg_l | CCfg_c | CCfg_r | CCfg_sl            | CCfg_sr         | CCfg_b),                ///< 3/2/1
    CCfg_6pt1       = (CCfg_LCRSlSrB | CCfg_lfe),                                                                                   ///< 3/2/1.1
    CCfg_LCRSlSrBlBr= (0x07000000 | CCfg_normal | CCfg_l | CCfg_c | CCfg_r | CCfg_sl            | CCfg_sr | CCfg_bl       | CCfg_br),   ///< 3/2/2
    CCfg_7pt1       = (CCfg_LCRSlSrBlBr | CCfg_lfe),                                                                                ///< 3/2/2.1
    CCfg_LCRB       = (0x04000000 | CCfg_normal | CCfg_l | CCfg_c | CCfg_r                                | CCfg_b),                ///< 3/0/1
    CCfg_LCRBlBr    = (0x05000000 | CCfg_normal | CCfg_l | CCfg_c | CCfg_r                      | CCfg_bl | CCfg_br),   ///< 3/0/2

    CCfg_FormatSpecific = 0x80000000,   ///< if set, the rest of the value is defined by content standard (ex.: DVD LPCM)
};


#define CHANNEL_COUNT_TO_CONFIG(cnt)    ((enum EChannelConfig)cnt)  ///< Macro for converting audio channel count in channel configuration code
#define MPTYPE_ELEM_IS_AUDIO(x)     (((x & MTYPE_ELEMENTARY_MASK)>=MTYPE_ELEM_AUDIO_FIRST) && ((x & MTYPE_ELEMENTARY_MASK)<=MTYPE_ELEM_AUDIO_LAST)) ///< macro for checking whether a #TMediaType value is an elementary audio value

#define CONFIG_TO_CHANNEL_COUNT(cfg)    ((int)cfg)                  ///< Macro for converting audio channel configuration code in channel count

/// Parameters for rendering audio
struct SAudioRenderDesc
{
    UINT32 samplingFreq;                    ///< sampling frequency in Hz, 0 if unknown
    enum EChannelConfig channels;           ///< input channels (excluding lfe)/configuration
    int lfe;                                ///< 1 if low frequency input channel present, 0 if missing
    enum EChannelConfig channelAssignment;  ///< input channel to speaker mapping (use #CCf_none for direct or unspecified mapping)
    int emphasis;                           ///< emphasis value

    /// parameters of the alternate audio (i.e. independently accessible substream of the nominal stream), if any
    struct SAltAudioDesc
    {
        TMediaType mediaType;                   ///< alternate audio type, #MTYPE_ELEM_NONE (i.e. 0) if no alternate audio is available
        UINT32 samplingFreq;                    ///< alternate audio sampling frequency (in Hz)
        enum EChannelConfig channels;           ///< alternate audio channels (excluding lfe)
        int lfe;                                ///< alternate audio low frequency input channel (1 if present, 0 if missing)
        enum EChannelConfig channelAssignment;  ///< input channel to speaker mapping (use #CCf_none for direct or unspecified mapping)
        int isExclussive;                       ///< 1 if nominal and alternate audios are mutually exclusive (separate streams), 0 if they are both part of the same stream and the decoder can picke either of them
    }
    alt;
};

/// Parameters for storing audio (storage buffer not included, must be provided separately)
struct SPCMStorageDesc
{
    enum EPCMSampleFormat format;   ///< sample format
    int  bitsPerSample;             ///< bits per sample
    int  samplesPerChannel;         ///< number of consecutive sample in one channel before advancing to the next channel (1 for interleaved formats)
    bool MsbFirst;                  ///< if the PCM format is MSBfirst
};

/// PCM parameters definition
struct SPCMDesc
{
    struct SAudioRenderDesc rend;   ///< rendering parameters
    struct SPCMStorageDesc storage; ///< storage parameters
};

/// Windows Media Audio format definitions
enum EWMACodecID
{
    WMA_Version_1 = 0x160,
    WMA_Version_2,
    WMA_Pro,
    WMA_Lossless,

    WMA_Version_2_alt1 = 0x7A21,    ///< alternative codec for version 2
    WMA_Version_2_alt2,             ///< alternative codec for version 2
    WMA_Version_2_alt3,             ///< alternative codec for version 2
};

/// Parameters for storing Windows Media Audio (storage buffer not included, must be provided separately)
struct SWMAStorageDesc
{
    enum EWMACodecID format;        ///< WMA version identifier
    int bitsPerSample;              ///< bits per sample

    UINT32 bitrate;                 ///< average bitrate in bits per second
    UINT32 packetSize;              ///< frame size in bits
    int encoderOptions;             ///< encoding options (specific to WMA payload)
    int wmaProValidBitsPerSample;   ///< valid bits per sample (specific to WMA PRO)
    int wmaProChannelMask;          ///< channel mask (specific to WMA PRO)
    int wmaProVersionNumber;        ///< version number (specific to WMA PRO)
};

/// Windows Media Audio parameters definition
struct SWMADesc
{
    struct SAudioRenderDesc rend;   ///< rendering parameters
    struct SWMAStorageDesc storage; ///< storage parameters
};

/// Media descriptor

/// Provides information on media type, rendering and,
/// in case of pixmap and PCM formats, storage
///\ingroup COMMDEFS
struct SMediaFormat
{
    TMediaType mediaType; ///< media type identifier, a combination of \ref EMTYPE. \ref CMTYPE or \ref AMTYPE

    int formatValid;      ///< if non-zero, the format field is valid

    /// Optional media type-specific description

    /// Only elementary media types can have an explicit format description
    ///
    /// For compressed media types (i.e. any except pixmap and PCM) the explicit
    /// description is optional, as they are described implicitly in the media.
    /// Even when present, it may contain default (zero values) deferring to the values in the stream
    /// (for example, for JPEG images only the rotation field may be set to request a certain orientation).
    union
    {
        struct SImageDisplayDesc image;     ///< image display parameters
        struct SPixmapDesc pixmap;          ///< pixmap parameters, the display parameter portion is the same at compile and run-time with that of the rest of the formats
        struct SWMVDesc wmv;                ///< Windows Media Video parameters, the display parameter portion is the same at compile and run-time with that of the rest of the formats

        struct SAudioRenderDesc sound;      ///< audio rendering parameters
        struct SPCMDesc pcm;                ///< PCM parameters, the rendering parameter portion same at compile and run-time with that of the rest of the formats
        struct SWMADesc wma;                ///< Windows Media Audio parameters, the rendering parameter portion same at compile and run-time with that of the rest of the formats
    }
    format;

    /// Bitrate-based media type modifier
    enum
    {
        DefaultBitrate = 0, ///< identify the default version of the mediaType format (ex: DTS-HD, DRA, etc)
        LowBitrate,         ///< identify the low-bitrate version of the mediaType format (ex: DTS-HD LBR vs DTS-HD)
        HighBitrate,        ///< identify the high-bitrate version of the mediaType format (ex: DTS-HD XLL vs DTS-HD, DRA Extension vs DRA)
    }
    bitrateType;
};

#endif //_MDEFS_H_

/**
  $Log: mdefs.h,v $
  Revision 1.127.10.7  2011-05-05 22:55:22  klin
  BugId: 30908
  2011-04-21_DCCHD_380_Stereoscopic3D.patch
  SEND_COMMENT_BUGZILLA

  Author: Christian Wolff, Christian_Wolff@sdesigns.com
  Verified by: QA
  Signed-off by: Yanquan Zhang, Yanquan_Zhang@sdesigns.com
  Branch approval: Cat Nguyen, Cat_Nguyen@sdesigns.com

  Revision 1.127.10.6  2010-04-30 14:42:30  sotescu
  BugId: ct-7899
  SEND_COMMENT_BUGZILLA
  * using hdmi_pending_loop() to decide the sleep time for the HDMI thread
  * added ccSamplingMode and to DCCHD configuration and modified ccDepth, to
  control HDMI color depth and sampling mode from configPreview user functions

  Revision 1.127.10.5  2010-04-21 21:27:46  dnguyen
  BugId: ct-8088
  SEND_COMMENT_BUGZILLA
  define MTYPE_ELEM_AUDIO_UNKNOWN and MTYPE_ELEM_VIDEO_UNKNOWN (already exist on HEAD)

  Revision 1.127.10.4  2010-04-21 02:20:04  benoit
  BugId: none
  Fixed MTYPE_ELEM_HAS_VIDEO

  Revision 1.127.10.2  2009-12-22 14:22:23  anagy
  BugId:6854
  Ported ALSA PCMX implementation

  Revision 1.127.10.1  2009-11-18 23:08:11  ksshah
  Adding support for audio capture engine.
  BugId: none
  SEND_COMMENT_BUGZILLA

  Revision 1.127  2009-07-16 20:21:31  sorin
  BugId: CT-6813
  SEND_COMMENT_BUGZILLA
  Generate ACCESS DENIED flag in the media detection module and propagate and use it throughout the stack

  Revision 1.126  2009-07-08 12:32:59  anagy
  BugId: 6802
  support for audio contents of unknown sampling rate

  Revision 1.125  2009-03-21 05:52:39  sorin
  BugId: CT-6111
  SEND_COMMENT_BUGZILLA
  Added DRA support, tested with Red Cliff

  Revision 1.124  2009-03-05 02:41:57  sorin
  BugId: none
  Reversed flag-based Blu-ray type definition to avoid complications with values used as indices.
  Propagated the changes

  Revision 1.123  2009-03-04 06:05:44  sorin
  BugId: none
  Redefined Blu-ray TMediaType values to enable identification of all the different flavors.
  Propagated the changes

  Revision 1.122  2009-03-04 02:06:56  sorin
  BugId: none
  Partially redefined TMediaType values;
  Added AVCHD media type definition and detection support

  Revision 1.121  2009-01-27 18:45:10  sorin
  BugId: CT-6111
  Added DCC-HD audio type code for DRA
  Added support for WMAPro and AAC+ compressed formats over HDMI

  Revision 1.120  2009-01-17 00:48:13  dnguyen
  BugId: none
  Changed value for MTYPE_CONT_MKV

  Revision 1.119  2009-01-16 19:45:00  dnguyen
  BugId: none
  Added MKV container type

  Revision 1.118  2008-12-18 01:13:29  sorin
  BugId: none
  Added WMA parameter support

  Revision 1.117  2008-12-17 01:58:27  sorin
  BugId: none
  Fixed macro

  Revision 1.116  2008-12-16 01:03:17  ssivaruban
  BugId:None
  -Integration of Capture PBC to amptest.
  -Added Play/Stop commands to Capture PBC.

  Revision 1.115  2008-12-02 19:59:00  sorin
  BugId: none
  Typos

  Revision 1.114  2008-12-02 00:07:05  sorin
  BugId: none
  Added WMV parameters support

  Revision 1.113  2008-10-07 23:24:26  sorin
  BugId: none
  Doc

  Revision 1.112  2008-08-11 17:59:54  sorin
  BugId: none
  Replaced bool with int in interface definition shared by both C ad C++ code in order to avoid confusions with regard of the underlying storage requirements

  Revision 1.111  2008-06-27 03:51:30  sorin
  BugId: none
  Added pixel alignment flag in image descriptor

  Revision 1.110  2008-05-28 04:18:12  sorin
  BugId: none
  Added I/O error code

  Revision 1.109  2008-03-23 22:40:51  sorin
  BugId: none
  Simplified disc unbound BDJ app handling by GUI - just a result of the ejecting/inserted commands

  Revision 1.108  2008-01-23 05:05:42  sorin
  BugId: CT-3099
  Added low bitrate media format modifier
  Added DTS-HD LBR support from the stream allocation to deocder configuration

  Revision 1.107  2007-11-20 18:01:57  dnguyen
  BugId:ct-4088
  added MP4 container format

  Revision 1.106  2007-07-07 23:11:53  sorinp
  Added support for external audio DSP by:
  - renaming and fixing pass-through for all for formats
  - forcing the default config with full support HDMI settings
  Also fixed some audio media types

  Revision 1.105  2007/07/05 17:02:55  anagy
  ported testtone fixes

  Revision 1.100.2.4  2007/07/04 00:29:57  sorinp
  BugID:CT-3346 Accept and report the correct channel config values, support delayed (non-auto play) presentation

  Revision 1.100.2.3  2007/07/02 21:22:39  pvu
  BugId:ct-3346
  (Sorin O) Fix the problem introduced by the TTone implementation which prevents all discs from being played.

  Revision 1.100.2.2  2007/07/01 05:19:27  pvu
  BugId:ct-3346
  Arpad's patches for test-tone from comment #11,12,13 of ct-3346.

  Revision 1.100.2.1  2007/06/25 21:36:43  pvu
  BugId:ct-3308
  Christian's patch in ct-3308 for DD+, DTS-HD and TrueHD over HDMI.

  Revision 1.100  2007/04/26 20:56:57  sorinp
  BUGCT:2991 Adde and use emphasis audio parameter
  BUGCT:? Disable TrueHD DRC on custom zero parameters

  Revision 1.99  2007/04/19 16:10:24  sbeysserie
  Fix incorrect doxygen tags

  Revision 1.98  2007/04/19 04:49:18  sorinp
  Optimized media type ID values
  Added utility macros

  Revision 1.97  2007/04/17 02:38:51  sorinp
  Added channel config values newly supported in MRUA

  Revision 1.96  2007/04/04 03:02:00  sorinp
  Merged experimental_core_audio_config_support branch

  Revision 1.95.2.2  2007/04/02 05:06:03  sorinp
  work in progress

  Revision 1.95.2.1  2007/03/29 22:55:29  sorinp
  work in progress

  Revision 1.95  2007/03/23 00:12:50  sorinp
  doc fix

  Revision 1.94  2007/03/21 01:25:11  sorinp
  Made separate SPDIF and I2S connections to the HDMI output

  Revision 1.93  2007/03/20 12:02:51  anagy
  BUGCT#2689 fix: added AspectRatio type to ContentInfo structure

  Revision 1.92  2007/03/20 00:15:12  sbeysserie
  Add end of line.

  Revision 1.91  2007/03/19 16:31:09  sorinp
  Moved log at the end of the file

  Revision 1.90  2007/03/19 16:19:08  sorinp
  doc/code values

  Revision 1.89  2007/02/28 03:58:17  sorinp
  Added implementation component to media type and moved the shell flag into it

  Revision 1.88  2007/01/12 22:49:26  sorinp
  Propagated changes in MRUA channel assignment enumeration (and made the driver code enumeration value independent)

  Revision 1.87  2006/12/13 12:02:58  anagy
  - UPDATE -
  updated PresEng. related modifications from Version.1 branch

  Revision 1.86.4.2  2006/12/12 17:32:44  sorinp
  Removed change doc tags in prepearation for the official 1.0.0 release

  Revision 1.86.4.1  2006/12/09 02:55:16  sorinp
  doc

  Revision 1.86  2006/11/10 07:22:50  sorinp
  Added Reset and documented the error support in the API

  Revision 1.85  2006/09/26 03:03:54  sorinp
  Updated to B.6.0 level

  Revision 1.84  2006/09/22 01:55:03  sotescu
  Changed the ARM modes order (the first ones have preferential treatment).

  Revision 1.83  2006/09/21 22:55:31  cwolff
  * Sort the ARM and DARM values by preference

  Revision 1.82  2006/09/20 22:06:46  sorinp
  Added aspect ratio matching capabilities in the video media format info to assist with DVD run-time configuration

  Revision 1.81  2006/09/11 19:12:46  sorinp
  Changed speaker configuration naming convention to generally accepted one

  Revision 1.80  2006/08/31 04:41:33  sorinp
  Updated doc change list to B.5.0

  Revision 1.79  2006/08/20 00:47:05  sorinp
  Added support to dual mono (1+1) channel assignment

  Revision 1.78  2006/08/20 00:17:00  sorinp
  doc

  Revision 1.77  2006/08/19 20:21:26  sorinp
  channel assignemnt updates

  Revision 1.76  2006/08/19 02:23:32  sorinp
  Added single back channel support in ESpeakerConfig

  Revision 1.75  2006/08/17 07:30:30  sorinp
  doc

  Revision 1.74  2006/08/17 02:06:02  sorinp
  Simplified rotation spec

  Revision 1.73  2006/08/17 02:04:00  sorinp
  Added rortation spec

  Revision 1.72  2006/07/31 19:59:59  sorinp
  Added dedicated app ID for Mono

  Revision 1.71  2006/07/29 01:38:57  sorinp
  Removed doc change notes older than B.2.0

  Revision 1.70  2006/07/12 21:04:32  sorinp
  Added channel assignment parameter in audio format description

  Revision 1.69  2006/06/16 22:36:19  sorinp
  removed separate channel count in PCM descriptor to avoid conflicts

  Revision 1.68  2006/06/14 03:09:32  sorinp
  Changed field order in SPCMDesc to make it polimorfic with SAudioRendDesc for uniform handling of audio rendering parameters

  Revision 1.67  2006/06/01 20:49:23  dnguyen
  added WMV elementary type definition

  Revision 1.66  2006/05/30 09:02:20  sorinp
  allow detailed bitstream settings in digital audio connections

  Revision 1.65  2006/05/28 22:06:48  sorinp
  audio configuration related changes

  Revision 1.64  2006/05/15 16:21:47  sorinp
  Removed generic multichannel setting

  Revision 1.63  2006/05/15 01:18:14  sorinp
  new configurationscheme related changes

  Revision 1.62  2006/05/13 22:44:46  sorinp
  Added content info passing in AllocSubstream

  Revision 1.61  2006/05/04 07:36:38  sorinp
  syntax fix

  Revision 1.60  2006/05/04 04:55:02  sorinp
  Added reserved MTYPE values

  Revision 1.59  2006/05/03 00:44:00  anagy
  added "format specific" flag to auido channels enum

  Revision 1.58  2006/04/29 04:15:18  sorinp
  Updates

  Revision 1.57  2006/04/27 07:30:36  sorinp
  Updated A/V config spec, new memory allocation (static) spec

  Revision 1.56  2006/04/22 19:24:32  sorinp
  Integrated PCMX PBC support
  Started new audio config support

  Revision 1.55  2006/04/22 18:17:18  anagy
  MTYPE_APP_BDJ

  Revision 1.54  2006/04/04 01:04:01  sorinp
  Added support for linked lists of meta buffers

  Revision 1.53  2006/03/31 13:16:28  anagy
  Added MSBfirst option in PCMStrorageDescriptor

  Revision 1.52  2006/03/22 22:03:03  sorinp
  added paranthesis around macro parametes to allow inline assignments

  Revision 1.51  2006/03/19 00:32:41  sorinp
  mostly doc, some spec updates

  Revision 1.50  2006/03/14 01:24:14  sorinp
  Straighten up XPEG decoder spec

  Revision 1.49  2006/03/13 18:36:10  anagy
  beginned config.info structure for XPEG PresEng

  Revision 1.48  2006/03/04 06:14:07  sorinp
  Moved frame callback fields into more general session parameters structure and handling

  Revision 1.47  2006/02/23 17:56:25  anagy
  Added parameter to FrameCallback function

  Revision 1.46  2006/02/23 17:42:51  sotescu
  Modified PresEng SetConfiguration parameters to support frame notification callbacks.

  Revision 1.45  2006/02/21 16:48:25  sotescu
  Modified PresEng SetConfiguration parameters to support frame notification callbacks.

  Revision 1.44  2006/01/30 23:34:23  sorinp
  Added conversion macros

  Revision 1.43  2006/01/30 09:00:57  sorinp
  Added configuration and adjustment definitions

  Revision 1.42  2005/12/20 08:25:48  sorinp
  Added codec and hardware configuration support in SGlobals

  Revision 1.41  2005/12/15 23:14:15  sorinp
  Added PROTECTED result code

  Revision 1.40  2005/12/07 00:17:53  sorinp
  Added BD-RE app format code

  Revision 1.39  2005/11/16 00:05:47  dnguyen
  changed all bool struct members to int because the difference between mips
  C compiler (where bool is 32-bit) and C++ compiler (bool is 8-bit) can be
  catastrophic

  Revision 1.38  2005/11/14 04:51:12  sorinp
  Added not-ready result code

  Revision 1.37  2005/10/22 02:59:23  sotescu
  Added helper class for IG, PG and subtitle rendering.

  Revision 1.36  2005/10/05 18:43:29  sorinp
  Mostly doc upgrades

  Revision 1.35  2005/10/04 03:57:34  sorinp
  Doc updates

  Revision 1.34  2005/10/04 03:47:45  sorinp
  doc update

  Revision 1.33  2005/09/30 06:50:31  sorinp
  Moved globals definition into separate file since that is Sigma specific definition and these is not

  Revision 1.32  2005/09/29 18:08:42  sotescu
  no message

  Revision 1.31  2005/09/29 15:10:32  sotescu
  no message

  Revision 1.30  2005/09/29 13:19:07  sotescu
  no message

  Revision 1.29  2005/09/27 16:24:38  sorinp
  improved inteligibility

  Revision 1.28  2005/09/26 15:09:21  sorinp
  removed duplicate definitions

  Revision 1.27  2005/09/26 06:47:11  sorinp
  finalized linear and blu-ray control and media definition
  placed public media and control definitions in separate (and new) files

  Revision 1.26  2005/09/23 14:50:33  sorinp
  Moved result code definitions from dcchd.h

  Revision 1.25  2005/09/12 10:44:05  anagy
  Syntax fixing

  Revision 1.24  2005/09/11 23:31:46  sorinp
  Multiple changes
  Completed presentation engine spec.
  Control framework spec at linear playback level.

  Revision 1.23  2005/09/11 18:04:49  sorinp
  Completed SMediaFormat spec

  Revision 1.22  2005/09/08 02:31:04  sorinp
  Fix constant typo

  Revision 1.21  2005/09/03 02:25:02  sorinp
  various syntax, functionality and doc changes

  Revision 1.20  2005/08/30 21:22:27  rdemeter
  MTYPE_ELEM_WMA duplicated

  Revision 1.19  2005/08/21 16:18:08  sorinp
  doc fixes

  Revision 1.18  2005/08/19 01:46:43  sorinp
  Added media type definitions and doc

  Revision 1.17  2005/07/26 03:59:06  sorinp
  Implemented CPLaybackControl::ExecuteCmd; updated members, doc, naming and syntax and propagated the changes in deried/client classes

  Revision 1.16  2005/06/20 21:16:34  sorinp
  Split mdefs in presentation and control definitions

  Revision 1.15  2005/06/20 20:19:20  sorinp
  Made CPresEng implementation details private
  added documentation module support

  Revision 1.14  2005/06/17 00:53:15  sorinp
  Renamed busy to cmdPending

  Revision 1.13  2005/06/15 12:14:55  anagy
  sintax error fixing

  Revision 1.12  2005/06/14 15:30:53  sorinp
  fixed some compilation problems ?

  Revision 1.11  2005/06/11 17:13:31  sorinp
  Added multiple status listener support in order to accomodate planned dual control between UI and GUI
  Added event of interest support in UpdateStatusInfo; updated documentation

  Revision 1.10  2005/06/10 21:03:30  sorinp
  Updated syntax and documentation

  Revision 1.9  2005/06/10 16:16:19  sorinp
  Defining bthe status structure

  Revision 1.8  2005/06/07 19:50:51  sorinp
  Removed SLongInteger definition

  Revision 1.7  2005/06/06 04:58:58  sorinp
  - updated syntax
  - updated and expanded comments
  - made the comments Doxygen compatible and friendly; first specification generated with Doxygen

  Revision 1.6  2005/06/05 17:16:14  sorinp
  Updated file headers

*/

