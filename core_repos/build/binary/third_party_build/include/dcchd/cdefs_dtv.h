/*****************************************
 Copyright  2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
 @file   cdefs_dtv.h
 @brief  DTV playback control header

 @author Jake Lee
 @date   2/20/2008

 $Revision: 1.14.2.2 $	$Date: 2010-08-30 16:56:47 $
 */
#ifndef _CDEF_DTV_PBC_H__
#define _CDEF_DTV_PBC_H__

#include "cdefs.h"
#include "samples/psfdemux_common.h"
//#define FIRST_STEP_ONLY 0

///\defgroup DTVMSDEFS DTV Media Space Control Definitions
/// These control definitions are common to any media space
///
/// Control commands, results and status are format and application specific,
/// so the syntax is defined in media spaces corresponding to each of the supported format and/or application.
///
/// A new media format or application can define a new media space and a new set of control elements
/// (commands, status and result definitions). Optionally it can reuse an existing media space by
/// inheriting its definitions.
///\ingroup MEDSPACES

///\defgroup DTV MSID Media Space identifiers
/// Values used in structures derived from SCommand, SStatus and SResult to identify a specific media format
///\ingroup DTVMSDEFS
//@{
#define MEDIA_SPACE_DTV      12     ///< DTV media space, to identify any structures derived from SDTVCommand, SDTVStatus and SDTVResult
///@}

///\defgroup SDTVFLAGS DTV playback flags for status validation and change notification
/// Constants identifying individual Linear Playback status fields and events. Used in addition to \ref SFLAGS
///\ingroup DTVCTRLDEFS
//@{
#define SDTVSTATUS_VIDEO        (SSTATUS_LAST_GENERIC << 1)  ///< identifies the video field; events are triggered when the stream identity or its parameters change

#define SDTVSTATUS_AUDIO        (SSTATUS_LAST_GENERIC << 2)  ///< identifies the audio field; events are triggered when the stream identity or its parameters change

#define SDTVSTATUS_SECTION      (SSTATUS_LAST_GENERIC << 3)  ///< identifies the media field; events are triggered when media or it's parameters change

#define SDTVSTATUS_MEDIA        (SSTATUS_LAST_GENERIC << 4)  ///< identifies the media field; events are triggered when media or it's parameters change

#define SDTVSTATUS_LAST_SPECIFIC   SDTVSTATUS_MEDIA          ///< other status flags values can be defined beyond this bit value

#define SDTVSTATUS_MODE         SSTATUS_MODE

#define SDTVSTATUS_FILELOOP     (SSTATUS_LAST_GENERIC << 5)  ///< File loop mode

///@}

/// Values used for identify the stream type from DTV playback control
///\ingroup DTVMSDEFS
//@{
enum enumDTVStreamType
{ ///< DTV stream type
    // reserved 0x00
    MPEG2TS_MPEG1v = 0x01,                      ///< MPEG1 video stream
    MPEG2TS_MPEG2v = 0x02,                      ///< MPEG2 video stream or MPEG1 constrained parameter video stream
    MPEG2TS_MPEG1a = 0x03,                      ///< MPEG1 audio
    MPEG2TS_MPEG2a = 0x04,                      ///< MPEG-2 multi-channel audio, backward compatible to MPEG-1
    MPEG2TS_MPEG2SystemPrivateSection = 0x05,   ///< ITU-T Rec.H.222.0|ISO/IEC 13818-1 private sections
    MPEG2TS_MPEG2PesPrivateData = 0x06,         ///< Teletext defined in SESF/DVB or
                                                ///< Subtitle defined in ISDB or
                                                ///< PES packets containing streaming, synchronized data defined in ATSC or
    MPEG2TS_ISO_13522_MHEG = 0x07,              ///< ISO/IEC 13522 MHEG
    MPEG2TS_ISO_13818_DSM_CC = 0x08,            ///< ITU-T Rec.H.222.0|ISO/IEC 13818-1 Annex A DSM CC
    MPEG2TS_ITU_H222_1 = 0x09,                  ///< ITU-T Rec.H.222.1
    MPEG2TS_ISO_13818_6_A = 0x0A,               ///< ISO/IEC 13818-6 type A
    MPEG2TS_ISO_13818_6_B = 0x0B,               ///< ISO/IEC 13818-6 type B
    MPEG2TS_ISO_13818_6_C = 0x0C,               ///< ISO/IEC 13818-6 type C
    MPEG2TS_ISO_13818_6_D = 0x0D,               ///< ISO/IEC 13818-6 type D
    MPEG2TS_ISO_13818_auxiliary = 0x0E,         ///< ISO/IEC 13818-1 auxiliary
    MPEG2TS_MPEG2AAC_ADTS_TS = 0x0F,            ///< MPEG-2 AAC audio with ADTS transport syntax
    MPEG2TS_ISO_14496_2_Visual=0x10,            ///< ISO/IEC 14496-2 Visual
    MPEG2TS_ISO_14496_3_Audio=0x11,             ///< ISO/IEC 14496-2 Audio with the LATM transport syntax
    MPEG2TS_ISO_14496_1_SL_PES=0x12,            ///< ISO/IEC 14496-2 SL-packetizzed stream or FlexMux stream carried in PES packets
    MPEG2TS_ISO_14496_1_SL_Section=0x13,        ///< ISO/IEC 14496-2 SL-packetizzed stream or FlexMux stream carried in ISO/IEC 14496_sections
    MPEG2TS_DSM_CC_ATSC = 0x14,                 ///< DSM-CC sections containing non-streaming, synchronized data defined in ATSC
    MPEG2TS_MPEG4AVC_H264 = 0x1B,               ///< MPEG4 part 10 AVC video
    // reserved 0x15 - 0x7F
    MPEG2TS_SESF_LPCM = 0x80,                   ///< SESF LPCM audio
    MPEG2TS_Dolby_AC3 = 0x81,                   ///< Dolby AC-3 audio
    MPEG2TS_DTS = 0x82,                         ///< DTS audio
    MPEG2TS_DolbyLossless = 0x83,               ///< DolbyLossless audio
    MPEG2TS_DDPlusPrimary = 0x84,               ///< DD+ for Primary audio
    MPEG2TS_DTSHDPrimary = 0x85,                ///< DTS-HD for Primary audio
    MPEG2TS_DTSHDXLLPrimary = 0x86,             ///< DTS-HD XLL for Primary audio
    // reserved 0x87 - 0x94
    MPEG2TS_DST_NRT_ATSC = 0x95,                ///< Sections conveying Data Service Table, Network Resources Table defined in ATSC
    // reserved 0x96 - 0xA1
    MPEG2TS_DDPlusSecondary = 0xA1,             ///< DD+ for Secondary audio
    MPEG2TS_DTSHDSecondary = 0xA2,              ///< DTS-HD for Secondary audio
    // reserved 0xA1 - 0xC1
    MPEG2TS_PES_SSD_ATSC = 0xC2,                ///< PES packets containing streaming, synchronous data defined in ATSC
    MPEG2TS_TIP_DATA_STREAM = 0xC3,             ///< Tip data stream
    // reserved 0xC4 - 0xFF
};
///@}


typedef enum PlayMode
{
    enmStop = 0,
    enmPlay,
    enmPause,
} ePlayMode_t;

#define MAX_NAME_SIZE         64            ///< maximum size of names

///Output stream info
struct SDTVStreamInfo
{
    int index;                              ///< index of the stream, a value from 0 to SStatus::SMedia::streams - 1
    char name[MAX_NAME_SIZE];     	        ///< stream name, from the media itself
    struct SMediaFormat format;             ///< detailed stream parameters
    unsigned short PID;                     ///< PID information for substream
    ePlayMode_t PlayMode;                   ///< Play mode for substream
};

struct SDTVDemuxInfo
{
    unsigned short PCRPid;
    unsigned int SkipBytes;
};

/// DTV specific types

///\defgroup DTV_EncryptionType Encryption type definition as application type
/// Values used for identify the encryption type for DTV playback control
///\ingroup DTVMSDEFS
//@{
/// Encryption Types
typedef enum application_type CipherType_t;
//typedef RMuint32 CipherType_t;
///@}

/// DTV Section match filter descriptor
typedef struct _SectionDescriptor_t
{
	unsigned short Pid;			/// PID for PSI table
	unsigned char Mask[12];		/// Mask for section match filter
	unsigned char Mode[12];		/// Mode for section match filter
	unsigned char Comp[12];		/// Comp for section match filter
	CipherType_t  Cipher;		/// Cipher info : 0 means not encrypted
	unsigned short EcmPid;		/// Ecm PID unless Cipher = 0
} SectionDescriptor_t;

/// DTV PES data descriptor
typedef struct _PESDescriptor_t
{
	unsigned short Pid;			/// PID for PES
	int Type;					/// PES type in PMT
	CipherType_t Cipher;		/// Cipher info
	unsigned short EcmPid;		/// Ecm PID unless Cipher = 0
} PESDescriptor_t;

// Special PID for Partial TS
#define ESP_PID_PTS             0x2FFF

#define MAX_TSPidArray_Size     16
/// DTV Partial TS Pid Array
typedef struct TSPidArray_t
{
    int Size;
    unsigned short PidArray[MAX_TSPidArray_Size];
    unsigned short VideoPid;        // For indexing
    unsigned VideoType;             // For indexing
} TSPidArray_t;

/// Section filter callback function
typedef void (*DTVSectionCBF_t) (unsigned short Pid, void *pBuffer,	size_t Size, int err);

/// PES data callback function
typedef void (*DTVPESDataCBF_t) (unsigned short Pid, void *pBuffer,	size_t Size, int err);

/// TS data callback function
typedef void (*DTVTSDataCBF_t) (unsigned short Pid, void *pBuffer, size_t Size, int err);

// Format change callback function
typedef void (*DTVFormatChng_t) (unsigned short Pid, void *pParam, size_t Size);

// CC and UserData callback function
typedef void (*DTVUserDataCBF_t) (void *pParam, size_t Size);

// GetParameter generic callback function  to pass info  to the upper layer (such as position,duration,EOS,BOS,etc ... used in VOD case)
typedef void (*DTVParameterCBF_t) (void *pParam, size_t Size);

/// VCXO speed adjustment type
typedef struct _VCXO_Adjustment_t
{
	RMuint32 Adjustment_N;
	RMuint32 Adjustment_M;
} VCXO_Adjustment_t;

typedef struct AESKeyStruct_t
{
    RMuint8 *pDataKey;
    RMuint8 *pIVKey;
    RMuint32 KeySize;
} AESKeyStruct_t;

typedef struct DVBCSAKeyStruct_t
{
    RMuint8 *pDataKey;      // Odd and even if PAIRKEY
} DVBCSAKeyStruct_t;

typedef struct Multi2KeyStruct_t
{
    RMuint8 *pSystemKey;
    RMuint8 *pIVKey;
    RMuint8 *pDataKey;
} Multi2KeyStruct_t;

/// Cipher Keys Type
typedef union Cipher_KeyStruct_t
{
	struct DemuxTask_DESKey_type 	DesKey;
	struct DemuxTask_TDESKey_type	TDesKey;
	struct AESKeyStruct_t	        AesKey;
	struct DemuxTask_RC4Key_type	RC4Key;
	struct DVBCSAKeyStruct_t        DVBCSAKey;
	struct Multi2KeyStruct_t        Multi2Key;
	struct DemuxTask_C2Key_type		C2Key;
} Cipher_KeyStruct_t;

typedef struct Cipher_Key_t
{
    enum key_type       KeyType;
    Cipher_KeyStruct_t  Keys;
} Cipher_Key_t;

#ifdef DTV_TUNER
// Tuner related info
typedef struct SDTVTunerConfig_t
{
    RMuint32 tunerModel;
    RMuint32 tunerMode;
    RMuint8  i2cAdd_0;
    RMuint8  i2cAdd_1;
    RMuint8  uiBandwidth;
    RMuint32 frequency;
    RMbool   bUseTuner;
} SDTVTunerConfig_t;
#endif //DTV_TUNER

/// DTV playback control commands

///\defgroup SDTVCMD DTV playback commands
/// This is the command list for communicating with DTV presentation engine.
///\ingroup DTVCTRLDEFS
//@{
enum EDTVCmd
{
	DTVCmd_PLAY = 1,                    /**< start presentation from the beginning of the file.
	                                     * \param No input parameter.
	                                     */
    DTVCmd_STOP,                        /**< stop presentation in the specified mode.
                                         * \param No input parameter.
                                         */
    DTVCmd_PAUSE_ON,                    /**< pause presentation.
                                         * \param No input parameter.
                                         */
    DTVCmd_PAUSE_OFF,                   /**< resume a paused presentation.
                                         * \param No input parameter.
                                         */
    DTVCmd_SET_SECTCBF,					/**< assign section match filter callback function.
                                         * \param SecDesc : Section descriptor.
                                         * \param fSecCallback :Section Callback.
                                         */
    DTVCmd_SET_DSMCCCBF,				/**< set DSMCC filter callback function.
                                         * \param SecDesc : DSCMCC descriptor.
                                         * \param fSecCallback : Callback function.
                                         */
    DTVCmd_SET_ECMKEYS,					/**< set cipher keys for ECM Pid
                                         * \param Pid(Ecm)
                                         * \param CipherKey(key data)
                                         * \param CipherType(Cipher tyep)
                                         */
    DTVCmd_START_FILTS,					/**< start section filter callback functions
                                         * \param  No input parameter
                                         */
    DTVCmd_STOP_FILTS,					/**< stop section filter callback functions
                                         * \param  No input parameter
                                         */
    DTVCmd_SET_PESCBF,					/**< set PES data callback function
                                         * \param  PesDesc(PES descriptor)
                                         * \param  fPesCallback(Callback function)
                                         */
    DTVCmd_SET_STCDRIFT,				/**< set STC drift mode
                                         * \param  Input(On/Off)
                                         */
    DTVCmd_GET_VCXO_ADJ,				/**< get VCXO adjustment value
                                         * \param  Adj (pointers)
                                         */
    DTVCmd_SET_VCXO_ADJ,				/**< set VCXO adjustment value
                                         * \param  Adj (Values)
                                         */
    DTVCmd_SET_AVSOURCE,				/**< set program information including pcr, video and audio
                                         * \param  PesDesc(video)
                                         * \param PesDesc(audio)
                                         * \param Pid (PCR Pid)
                                         */
    DTVCmd_SET_DOWNMIXTABLE,			/**< set audio down mix table
                                         * \param Table
                                         * \param Input (Enable/Disable)
                                         */
    DTVCmd_SET_CHANNEL_UP,		        /**< Channel up
                                         *
                                         */
    DTVCmd_SET_CHANNEL_DN,              /**< Channel up
                                         *
                                         */
    DTVCmd_SET_COLORSPACE,				/**< set default color space
                                         * \param  Input
                                         */
    DTVCmd_SET_FORMATMONCBF,            /**< set input video format change monitor callback function
                                         * \param  fFormatCallback
                                         */
    DTVCmd_SET_ENDOFFILECBF,            /**< set input video format change monitor callback function
                                         * \param  fFormatCallback
                                         */
    DTVCmd_SET_PARTIALTSCBF,            /**< set partial TS stream callback function
                                         * \param  TsPid (Pid array)
                                         * \param PesDesc (Descriptor)
                                         * \param fPTSCallback
                                         */
    DTVCmd_SET_PARTIALTS_ATSCBF,        /**< set partial TS stream with ATS callback function
                                         * \param  TsPid (Pid array)
                                         * \param PesDesc (Descriptor)
                                         * \param fPTSCallback
                                         */
    DTVCmd_SET_PARTIALTS_SCRAMBLE,      /**< set partial TS stream callback function
                                         * \param TsPid (EcmPid array)
                                         * \param PesDesc (Descriptor)
                                         * \param none
                                         */
    DTVCmd_SET_CC_USR_MON,              /**< set closed caption decode mode or userdata callback
                                         * \param param1.Input : On/Off
                                         * \param param2.Input : CC mode - a DCCHD::CPresEng::EEDType value
                                         * \param param3.fUserDataCallback - a #DTVUserDataCBF_t value
                                         */    
    DTVCmd_UPDATE_VID_SRC,				/**< set program information including pcr, video and audio
                                         * \param PesDesc (video)
                                         * \param Input (Stop/Play)
                                         * \param Pid (PCR Pid)
                                         */
    DTVCmd_UPDATE_AUD_SRC,				/**< set program information including pcr, video and audio
                                         * \param PesDesc (audio)
                                         * \param Input (Stop/Play)
                                         * \param Pid (PCR Pid)
                                         */
    DTVCmd_SET_TUNER,                   /**< set tuner setting
                                         * \param Input (Frequency on Mhz unit) 
                                         * \param Input (Tuner Model)
                                         * \param Input (Tuner Mode)   
                                         */
    DTVCmd_SET_AUDIOSPEED,              /**< set audio speed
                                         * \param Input (+1, or -1)
                                         */
    // Trick mode related commands
    DTVCmd_SET_INDEX_FILE,              /**< set index file for file playback
                                         * \param FileName (Index file name) 
                                         * \param Input (Video Pid)
                                         */
    DTVCmd_STEP,                        /**< step function for file playback.
	                                     * \param No input parameter.
	                                     */
    DTVCmd_SEEKPOS,                     /**< seek function in ms unit for file playback.
	                                     * \param Input (position in miliseconds)
	                                     */
    DTVCmd_FASTFWD,                     /**< fastforward function.
	                                     * \param Input (speed)
	                                     */
    DTVCmd_FASTRWD,                     /**< fast reverse function.
	                                     * \param Input (speed)
	                                     */
    DTVCmd_SLOWFWD,                     /**< fastforward function.
                                         * \param Input (1/speed)
                                         */
    DTVCmd_SLOWRWD,                     /**< fast reverse function.
                                         * \param Input (1/speed)
                                         */
    DTVCmd_SET_STREAM, 	                /**< set Stream setting
                                         * \param Stream path (Stream URL Example:udp:227.1.1.7:2007)  
                                         */
    DTVCmd_GET_PARAMETER,               /**< GetParameter function for VOD
                                         * \param parameter (parameter string) 
                                         */
    DTVCmd_SET_PARAMCBF,                /**< set GetParameter function callback
                                         * \param fParamCallback 
                                         */
    DTVCmd_LASTCMD						/**< last command for DTV */
};
///@}

///DTV media info and statistics
struct SDTVStats
{
			unsigned long long instantBitrate;	/// instantaneous Bitrate ,this is updated everytime we sent data to the demux	
			unsigned long long meanBitrate;  /// average bitrate ,calculated from the instantaneous bitrate 
			unsigned long long meanCount;	 /// number used to calculate the average bitrate
			unsigned long long lastStcTime;  /// last stc time when the bitrate was sampled
			unsigned long long lastTotalSent; /// previous total of bytes sent to the Demux
			unsigned long fileSize;			  /// size of the file [Bytes]
};

/// DTV media information
struct SDTVStatus_MediaInfo
{
        char name[MAX_NAME_SIZE];          	  ///< media name, from the media itself \status Not implemented for this version
        long clockTickN;                      ///< duration of media clock tick, in N/M seconds, or -1 if unknown
        long clockTickM;                      ///< duration of media clock tick, in N/M seconds, or -1 if unknown
        int duration;                         ///< media playback length in media clock ticks, or -1 if unknown
        struct SMediaFormat format;           ///< media format (input) info
        int streams;                          ///< number of streams in media available for output
        struct SDTVStats stats;				  ///< statistics and info about the stream (bitrate,size,...)	
};

//VOD media information
struct VodInfo
{
	bool EOSdetected;
	bool BOSdetected;
	int position;
	int duration;
};

struct SDTVStatus
#ifdef __cplusplus
: public SStatus
{
#else
{
    struct SStatus common;  ///< basic status info, common to any control object
#endif

    struct SDTVStreamInfo video;     ///< currently playing video stream
    struct SDTVStreamInfo audio;     ///< currently playing audio stream
    struct SDTVDemuxInfo  demux;
    /// Desciption of the currently playing media
    struct SDTVStatus_MediaInfo media; ///< Media info

#ifdef DTV_TUNER
    struct SDTVTunerConfig_t tuner;
#endif // DTV_TUNER
};


/// DTV playback command structure.
struct SDTVCommand
#ifdef __cplusplus
: public SCommand
{
#else
{
    struct SCommand common; ///< basic command info, common to any control object
#endif

    enum EDTVCmd cmd;  ///< command code

    union
    {
    	SectionDescriptor_t SecDesc;
    	PESDescriptor_t		PesDesc;
    	unsigned short      Pid;
    	int 				Input;
    	VCXO_Adjustment_t	Adj;
        TSPidArray_t        TsPids;
        DTVFormatChng_t     fFormatCallback;
        struct AudioEngine_Downmixing_tables_type ADownMix;
        const RMascii *     FileName;
        DTVParameterCBF_t	fParamCallback;
    } param1;
    union
    {
    	DTVSectionCBF_t		fSecCallback;
    	DTVPESDataCBF_t		fPesCallback;
    	Cipher_Key_t		CipherKey;
    	int					Input;
    	PESDescriptor_t		PesDesc;
    } param2;
    union
    {
    	CipherType_t        CipherType;
    	DTVTSDataCBF_t      fPTSCallback;
        DTVUserDataCBF_t    fUserDataCallback;
    	int				    Pid;
    	int                 Input;
    } param3;
};

/// Linear playback result definition
struct SDTVResult
#ifdef __cplusplus
: public SResult
{
#else
{
    struct SResult common; ///< basic result info, common to any control object
#endif
    struct SDTVStreamInfo streamInfo; ///< stream information
};

#include "dtvdbg.h"

#endif // _CDEF_DTV_PBC_H__
/*
  $Log: cdefs_dtv.h,v $
  Revision 1.14.2.2  2010-08-30 16:56:47  sorin
  BugId: none
  Added critical details in documentation

  Revision 1.14.2.1  2010-02-24 22:49:50  ssivaruban
  BugId:11694
  SEND_COMMENT_BUGZILLA
  -Added DTVCmd_GET_PARAMETER,DTVCmd_SET_PARAMCBF commands to handle EOS,BOS,GetPosition and GetDuration.
  This will be used also  for other purposes.(to get any kind of information from the server and to pass it to the client)
  -Added Seek Command.

  Revision 1.14  2009-10-07 20:02:56  ssivaruban
  BugId:none
  SEND_COMMENT_BUGZILLA
  Added Command "SET_STREAM" for  channel change.

  Revision 1.13  2009-10-05 22:00:18  jakel

  BugId:none
  Add audio speed control into DTV engine

  Revision 1.12  2009-05-22 00:44:34  ssivaruban
  BugId:none
  SEND_COMMENT_BUGZILLA
  Added UpdateStreamInfo() to monitor/update  the media info(bitrate,file duration ,etc ..).

  Revision 1.11  2009-04-21 01:01:31  jakel

  BugId:none
  Added slow forward and reverse commands

  Revision 1.10  2009-03-25 20:44:39  jakel

  BugId:ct-6424
  SEND_COMMENT_BUGZILLA
  Added updating video/audio substream functions

  Revision 1.9  2009-02-27 00:28:23  jakel

  BugId:none
  Added cipher entry and key setting function for recording

  Revision 1.8  2009-02-20 03:21:54  jakel

  BugId:none
  Added EOF monitor callback

  Revision 1.7  2009-02-20 02:52:24  jakel

  BugId:none
  Added ATS support on DTV presentation engine

  Revision 1.6  2008-12-15 18:30:17  jakel
  BugId:none
  Added trick mode commands for PVR implementation

  Revision 1.5  2008-12-10 20:02:53  jakel

  BugId:none
  generates index for partial TS

  Revision 1.4  2008-10-03 01:12:52  jakel

  BugId:none
  Added loop mode for file playback

  Revision 1.3  2008-09-25 22:54:57  jakel

  BugId:none
  Added tsskip 16 and 4 mode in DTV presentation engine file playback mode

  Revision 1.2  2008-09-16 23:12:56  jakel
  BugId:none
  Add tuner setup function to tune different channels from tuner

  Revision 1.1  2008-09-16 18:09:49  sorin
  BugId: none
  Applied established naming convention to control definitions file

  Revision 1.14  2008-09-16 17:47:43  sorin
  BugId: none
  Renamed debug utility definition file to avoid abuse of established naming convention (cdefs_xxx.h are high level public control definitions).

  Revision 1.13  2008-09-15 22:45:07  jakel

  BugId:none
  Add tuner support for DTV

  Revision 1.12  2008-08-28 22:59:42  jakel
  BugId:none
  Add channel up/down commands

  Revision 1.11  2008-08-22 01:17:42  jakel
  BugId:None
  Add audio downmix table control

  Revision 1.10  2008-05-20 23:31:43  jakel

  BugId:none
  Fix issues for doxygen

  Revision 1.9  2008-05-20 21:49:37  jakel

  BugId:none
  Rearrange comments for doxygen output

  Revision 1.8  2008-05-17 00:08:42  jakel
  BugId: none
  Add closed caption function in dtv presentation engine.

  Revision 1.7  2008-05-06 23:44:04  jakel

  BugId:none
  Added cipher functions for AES and DVB and operation for each mode was tested

  Revision 1.6  2008-04-30 22:54:13  jakel
  BugId:none
  Add basic decryption and encryption functions and tested with multi2 decryption

  Revision 1.5  2008-04-23 01:24:05  jakel
  BugId: none
  Add format change monitor function

  Revision 1.4  2008-04-04 21:16:51  jakel
  BugId: none
  Partial TS record sample code in PBC

  Revision 1.3  2008-04-02 02:15:45  jakel
  BugId: none
  Cleanup doxygen statements and add input selection

  Revision 1.2  2008-03-28 22:18:47  jakel

  BugId:none
  Fix section filter allocation/deallocation problem.

  Revision 1.1  2008-03-18 21:51:26  jakel

  BugId:none
  Initial check-in

 */
