/*****************************************
 Copyright  2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   globals.h
  @brief  Definition of information on hardware resources shared between DCC-HD and any number of clients

  @author Sorin Papuc
  @date   2005-09-30

  $Header: /bigbig/dungeon/dcchd_project/dcchd/core/globals.h,v 1.137.8.1 2011-03-02 01:28:33 klin Exp $

 */
#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(PRIORITY_BOOST) || defined(REAL_TIME_THREADS)
#ifdef REAL_TIME_THREADS
#define REAL_TIME_THREADS_DEFINED       (1)
#else
#define REAL_TIME_THREADS_DEFINED       (0)
#endif
#ifndef PRIORITY_BOOST
#define PRIORITY_BOOST  0
#endif
#define RMCreateThread(a, b, c)         RMCreateThreadWithPriority(a, b, c, REAL_TIME_THREADS_DEFINED, PRIORITY_BOOST)
#endif

/// \defgroup VUBIDs Video Output Block IDs
///@{
#define RMCFG_VOUTPUT_MAIN_DIGITAL      1       ///< Main digital out block

#define RMCFG_VOUTPUT_MAIN_ANALOG       2       ///< Main analog out block

#define RMCFG_VOUTPUT_CAV_ANALOG        4       ///< CAV analog out block

#define RMCFG_VOUTPUT_CVBS_ANALOG       8       ///< CVBS analog out block
///@}

#include "mdefs.h"          // implementation-independedent media definitions
#include "cdefs_av.h"       // implementation-independedent output control definitions
#include "dcchd_config.h"   // platform-dependedent definitions
#include "rmcci/include/output_cci.h"

    /**
     * \defgroup globals Definition of hardware resources shared among DCC-HD and each and every client
     *
     * This information is initialized by the DCC-HD client. Normally this is the DirectFB driver,
     * but DFB is not used, the application must initialize it.
     */

    /// RUA decoder params
    struct SDecoderParams
    {
        TMediaType type;    ///< media type for decoder selection
        union
        {
            struct AudioDecoder_AACParameters_type aac;             ///< use #MTYPE_ELEM_AAC or #MTYPE_ELEM_AACP as type
            struct AudioDecoder_Ac3Parameters_type ac3;             ///< use #MTYPE_ELEM_AC3 or #MTYPE_ELEM_DDP as type
            struct AudioDecoder_DVDAParameters_type dvda;           ///< use #MTYPE_ELEM_DLLS as type
            struct AudioDecoder_DtsParameters_type dts;             ///< use #MTYPE_ELEM_DTS or #MTYPE_ELEM_DTSHD as type
            struct AudioDecoder_DtslbrParameters_type dtsLBR;       ///< use #MTYPE_ELEM_DTSHD and low bitrate option in the content
            struct AudioDecoder_LpcmVobParameters_type lpcmVOB;     ///< use #MTYPE_ELEM_PCM | #MTYPE_APP_DVD as type
            struct AudioDecoder_LpcmAobParameters_type lpcmAOB;     ///< use #MTYPE_ELEM_PCM | #MTYPE_APP_DVDA as type
            struct AudioDecoder_PcmCdaParameters_type pcmCDA;       ///< use #MTYPE_ELEM_PCM | #MTYPE_APP_CDA as type
            struct AudioDecoder_MpegParameters_type mpeg;           ///< use #MTYPE_ELEM_MPA as type
            struct AudioDecoder_WMAParameters_type wma;             ///< use #MTYPE_ELEM_WMA as type
            struct AudioDecoder_DraParameters_type dra;             ///< use #MTYPE_ELEM_DRA or MTYPE_ELEM_DRAEXT
            struct AudioDecoder_LpcmBDParameters_type lpcmBD;       ///< use #MTYPE_ELEM_PCM | #MTYPE_APP_BRD
            struct AudioDecoder_PCMXParameters_type PCMXParams;     ///< use #MTYPE_ELEM_PCM | #MTYPE_APP_BDJ
            struct AudioDecoder_TToneParameters_type TToneParams;   ///< use #MTYPE_ELEM_PCM | #MTYPE_CONT_WNOISE | #MTYPE_APP_CALIBRATION
            enum SpuDecoder_StreamType_type spu;                    ///< use #MTYPE_ELEM_SPU as type
        }
        params; ///< decoder parameters - see MRUA specifications
    };


    /// Video scalers available in hardware \note never change or remove values, only add them here, to maintain binary compatibility
    enum EScalerID
    {
        SCALERID_FIRST = 1,
        SCALERID_VC = SCALERID_FIRST,
        SCALERID_MV,
        SCALERID_SPU,
        SCALERID_VCR,
        SCALERID_CRT,
        SCALERID_GFX,
        SCALERID_OSD,
        SCALERID_LAST = SCALERID_OSD
    };

    /// Resource group ID - resources with the same ID are treated as a unit
    enum EGroupID
    {
        GRID_First = 0,
        GRID_Free = GRID_First,     ///< not allocated, free to use
        GRID_Main,                  ///< main AV presentation
        GRID_Secondary,             ///< secondary AV presentation (PIP)
        GRID_Interactive,           ///< interactive audio presentation
        GRID_Deinterlacing,         ///< deinterlacing resource
        GRID_Graphics,              ///< graphics device
        GRID_SecondaryGraphics,     ///< secondary graphics device
        GRID_GFXEngineSlave,        ///< for GFX multiscaler when used as a scaling companion in a stretch operation
        GRID_SubpicSlave,           ///< for SPU multiscaler when used in subpicture mode
        GRID_Background,            ///< for the DFB background plane
        GRID_NotAvailable,          ///< not available in current configuration
        GRID_Last
    };

    struct SRectangle
    {
        int x;
        int y;
        int width;
        int height;
    };

    /// Structure for specifying per-group parameters (size, position etc.)
    struct SGroupInfo
    {
        bool valid;                                     // true if all parameters have been initialized

        struct EMhwlibDisplayWindow mixer_source_window;
        struct EMhwlibDisplayWindow input_window;

        struct SRectangle content_active_area;          // assuming the group is 4096x4096 units, the rectangle containing the useful content (e.g. [1536,0,3072,4096]
                                                        // is the rectangle for 4:3 content if the group is displayed pixel-accurate on a 16:9 monitor); slave groups
                                                        // are positioned relative to the active area of the master group
        RMbool visible;

        RMuint32 depth;                                 // depth of the group on the global Z axis (no master group) or the master's Z axis (0 is bottom, positive values are above)

        RMint8  brightness;
        RMuint8 contrast;
        RMint8  hue;
        RMuint8 cb_saturation;
        RMuint8 cr_saturation;

        enum EMhwlibScalingMode scaling_mode;
        struct EMhwlibBlackStripMode black_strip_mode;
        struct EMhwlibCutStripMode cut_strip_mode;
        struct EMhwlibNonLinearScalingMode non_linear_scaling_mode;

        RMuint32 master_scaler;                         // scaler used as master for LockMixerSourceScalingMode

        enum EGroupID master_group;                     // if != GRID_Free, the current group will be positioned and sized relative to the master group; if the master group is
                                                        // invisible then the current group will be invisible too (the opposite however is not true)

        RMbool opaque;                                  // set e.g. for main video; indicates that the group doesn't blend with groups behind it, so they can be removed from
                                                        // the mixer when their contents are completely inside this group's perimeter

        RMbool dirty;                                   // set by code that touches the group without changing its stored properties (e.g. enabling/disabling a scaler without
                                                        // changing the 'visible' property of the group)
    };

    /// Structure for specifying a media component's output
    struct SOutputInfo
    {
        RMbool valid;                       ///< TRUE if the module is present in the current hardware

        /// ID of the group which this component belongs to.
        /// For example, in Blu-ray, MainVideo, IG, PG and Main Audio
        /// all belong to GRID_Main group
        enum EGroupID groupID;

        RMuint32 moduleID;                  ///< MRUA ID of the output module (scaler)

        RMuint32 masterModuleID;            ///< master scaler (valid only for GRID_Deinterlacing scaler)

        RMuint32 depth;                     ///< depth of the scaler on the group Z axis (0 is bottom, positive values are above)
    };

    /// Sigma-specific audio output configuration definition

    /// Can be used for specifying both potential and actual
    /// configurations
    struct SMRUAAudioOutConfig
#ifdef __cplusplus
    : public SAudioOutConfig
    {
#else
    {
        struct SAudioOutConfig common;
#endif
        UINT32 hdmiEngines;         ///< Engines that can be/are routed to HDMI output (through I2S or SPDIF connections) (as bit flags: engine 0 = bit 0, etc)
        UINT32 analogEngines;       ///< Engines that can be/are routed to multichannel analog output (as bit flags: engine 0 = bit 0, etc)
        UINT32 stereoEngines;       ///< Engines that can be/are routed to stereo output (as bit flags: engine 0 = bit 0, etc)
        UINT32 spdifEngines;        ///< Engines that can be/are routed to SPDIF output (as bit flags: engine 0 = bit 0, etc)

        struct STC_AudioOffset_type audioDelay;             ///< delay between audio and video

        UINT32 hdmiI2sEngines;      ///< Engines that can be routed to HDMI output through I2S connections (as bit flags: engine 0 = bit 0, etc) \change Added 3-20-2007 to support separate SPDIF and I2S connections to the HDMI output
        UINT32 hdmiSpdifEngines;    ///< Engines that can be routed to HDMI output through SPDIF connections (as bit flags: engine 0 = bit 0, etc) \change Added 3-20-2007 to support separate SPDIF and I2S connections to the HDMI output
        UINT32 noMainAudioEngines;  ///< Engines on which main audio should not be sent to \change Added 7-2-2007
        UINT32 noOtherAudioEngines; ///< Engines on which audio other than main should not be sent to \change Added 7-2-2007
    };

    /// Sigma-specific video output configuration definition

    /// Can be used for specifying both potential and actual
    /// configurations
    struct SMRUAVideoOutConfig
#ifdef __cplusplus
    : public SVideoOutConfig
    {
#else
    {
        struct SVideoOutConfig common;
#endif
        UINT32 hdmiOutputBlocks;            ///< Output block routed to HDMI output (identified with \ref VUBIDs)
        UINT32 componentOutputBlocks;       ///< Output block routed to component output (identified with \ref VUBIDs)
        UINT32 compositeOutputBlocks;       ///< Output block routed to composite output (identified with \ref VUBIDs)
    };

    ///\typedef typedef int (*TSuspendOutput)(int suspendCountChange)
    ///\ingroup loconf
    ///\brief Called by DCC-HD or DirectFB clients to temporarily suspend and then resume A/V output.
    ///
    /// Suspension of the output consists in blocking the data path at the extreme downward end.
    /// It does not affect the state of the rest of the data and control path. All the A/V data generated during
    /// the suspension period remains available and will be automatically played back upon output resumption.
    ///
    /// Clients would normally suspend the output in the following situations:
    /// - the content information is incomplete and does not allow a precise output configuration; the client can
    /// suspend the output until real-time content info becomes available (from the decoders) and the output
    /// can be configured correctly, at which time the client will resume the output.
    /// - the output must be reconfigured in the middle of playback and the reconfiguration process may disturb
    /// the data path and/or the receiver; the client can suspend the output before starting the reconfiguration process
    /// and resume the output when the reconfiguration process is complete.
    ///
    /// The suspend calls are reference counted.
    /// Output is suspended when the suspend count reaches a positive value (1 or higher).
    /// Resuming occurs when the suspend count reaches zero or a negative value.
    ///
    ///\param suspendCountChange Amount (including zero) to be added (with sign) to the current state value.
    /// Normally use +1 to suspend and -1 to resume A/V output.
    ///\return The new state value.
    ///\note Full control and visibility over the suspend count is given only for assiting in problem diagnostics.
    /// Clients should make any effort to not cause suspend count underflows (reaching negative values).

    typedef int (*TSuspendOutput)(int suspendCountChange);


    /// Sigma-specific output configuration definition

    /// Can be used for specifying both potential and actual
    /// configurations
    struct SMRUAOutputConfig
    {
        struct SMRUAVideoOutConfig video;       ///< video output configuration parameters
        struct SMRUAAudioOutConfig audio;       ///< audio output configuration parameters
        TSuspendOutput suspendOutputCall;       ///< entry point for controlling the A/V output (suspend/resume) \change Added 4-5-2007 \status TBI
    };

    /// Elementary content real-time information definition \change Added 4-4-2007

    /// Media information as reported by the decoder,
    /// may contain greater detail than the SContentInfo structure
    ///
    /// This structure should be always associated with a #SContentInfo structure
    /// containing the nominal content parameters.
    struct SRTContentInfo
    {
        RMbool isValid;                                 ///< set to TRUE if the structure is valid
        RMbool isDirty;                                 ///< set to TRUE each time any of the fields changes, user may set it to FALSE after using the updated information

        /// Polymorphic content paramers, meaning decided by the media type of the corresponding #SContentInfo structure

        /// A zero value, when invalid,
        /// means the information corresponding to that field is not available
        union
        {
            /// Video parameters
            struct
            {
                struct SImageDisplayDesc generic;       ///< Generic video parameters (common to all media types)

                /// Type-specific video parameters
                union
                {
                    /// MPEG1/2 video specific parameters
                    struct
                    {
                        RMuint32 horizontal_size_value;         ///< value in MPEG sequence header
                        RMuint32 vertical_size_value;           ///< value in MPEG sequence header
                        RMuint32 aspect_ratio_information;      ///< value in MPEG sequence header
                        RMuint32 progressive_sequence;          ///< value in MPEG sequence header
                        RMuint32 display_horizontal_size;       ///< value in MPEG2 sequence display extension, 0 if not present
                        RMuint32 display_vertical_size;         ///< value in MPEG2 sequence display extension, 0 if not present
                    }
                    mpeg2;
                }
                specific;
            }
            video;

            /// Audio parameters, per audio engine

            /// The content info can vary between engines if:
            /// - the configuration of the corresponding decoders lead to the processing of different subsets of the nominal content.
            ///   Example: TrueHD configured for 2 channels output will appears as 2.0, configured for 6 channels will appear 5.1
            /// - Some engines receive the nominal content, while others receive the alternate content.
            ///   Example: engine 0 sends TrueHD to HDMI while engine 1 sends the alternate content AC3 to analog and SPDIF
            struct AudioDecoderInfo audio[RMCFG_AUDIO_ENGINE_CNT];
        }
        params;
    };

    /// Elementary content information definition \change Moved decoder info in own #SRTContentInfo structure and SGlobals::rtContentTab storage

    /// Contains nominal media information, as pre-defined in the presentation engine configuration table
    /// or provided by the platyback controller at substream allocation and/or reallocation.
    struct SContentInfo
    {
        struct SMediaFormat format;     ///< Content format as described by side/external information

        /// ID of the group which the content belongs to.

        /// For example, in Blu-ray, MainVideo, IG, PG and Main Audio
        /// all belong to GRID_Main group
        enum EGroupID groupID;

        void *presEng;                  ///< DCC-HD presentation engine which this content belongs to (if applicable)
        RMuint32 streamID;              ///< ID of the DCC-HD stream which this content belongs to (if applicable).
        RMuint32 substreamID;           ///< DCC-HD substream ID of this content (if applicable).
        RMuint32 ccSubstreamID;         ///< Substream ID of the associated closed captioning substream (if any)

        /// Pointer to content parameters as reported by the decoder in real time.

        /// May be NULL if no report has been received yet.
        /// Updated as soon as the report is received.
        /// Mid-stream parameter changes cause new reports, which update the parameters and set SRTContentInfo::isDirty to TRUE.
        struct SRTContentInfo *decoderInfo;
    };


    /// MRUA audio decoder configuration definition.
    struct SMRUAAudioDecoderConfig
    {
        /** MRUA module ID, -1 if codec not instantiated yet */
        RMuint32 decoderID;

        /** MRUA codec type */
        enum AudioDecoder_Codec_type type;

        /** MRUA codec subtype: 0:PCMcda, 1:VOB, 2:AOB, 3:BDpcm*/
        RMuint32 subType;

        /** Index into #SGlobals::contentTab parameter table */
        int contentIndex;

        /** Flag set if the alternative audio content (described in the 'alt; portion of the audio parameters structure) is used for PCM output \change Added 3-25-2007  */
        int useAltContent;

        /** Flag set if the alternative audio content (described in the 'alt; portion of the audio parameters structure) is used for SPDIF output \change Added 3-25-2007  */
        int spdifAltContent;

        /** Format-specific configuration parameters */
        struct SDecoderParams params;

        /** Mixing weights */
        struct AudioDecoder_MixerWeight_type mixWeight;

        /** Indicates the current status of the decoder **/
        enum AudioDecoder_State_type DecoderStatus;

        /** Indicates whether shadow audio decoder is needed - in that case two decoders will be used on different engines with the same datapath */
        bool UseShadowAudio;
    };

#define MAKE_SPDIF_STATUS(val, pos, length)     ((unsigned long)(val) << (32-pos-length))       ///< macro to generate SPDIF status from components

#define GET_SPDIF_STATUS(val, pos, length)      ((((unsigned long)(val)) >> (32-pos-length)) & ((1 << length) - 1))     ///< macro to generate SPDIF status from components

    /// MRUA audio engine configuration definition

    /// One and only one engine can and must be instantiated per audio DSP.
    /// An engine can driver multiple output lines with their corresponding formats, but they all share the same sampling rate.
    /// The correspondence between audio DSP output lines and user-level audio connectors is determined by a specific platform configuration.
    ///
    /// Multiple (currently 2) decoders can be instantiated per engine.
    /// The output of all the decoders associated with one engine is automatically mixed in the engine's output.
    struct SMRUAAudioEngineConfig
    {
        /** MRUA module ID, -1 if engine not instantiated yet */
        RMuint32 engineID;

        /** Set the decoder PLL input and Audio output frequencies (in Hz). @note @li This property should be called before sending any DSP command using ::RMAudioDecoderPropertyID_Command.@li An auto-detection frequency mechanism for compressed audio (i.e. not PCM data) may be added in later releases.@li The same output frequencies apply to all Audio decoders. All audio decoders other then PCM used on a single DSP currently require to be encoded at the same input frequency. PCM supports some frequency adjustments. */
        RMuint32 sampleFrequency;

        /** Set forced sample frequency (FALSE) or sample frequency set from stream information by audio decoder (TRUE). */
        RMbool sampleFrequencyFromStream;

        /** Volume per channel - see enum AudioChannelMap_type MRUA definition */
        RMuint32 volume[12];

        /** Audio output delay (in milliseconds, range 0-32) for each channel  - see enum AudioChannelMap_type MRUA definition */
        RMuint32 delay[8];

        /** Enables/disables I2S output */
        enum AudioEngine_SerialOut_type i2sEnable;

        /** I2S output configuration */
        struct AudioEngine_I2SConfig_type i2sConfig;

        /** Enables/disables SPDIF output */
        enum AudioEngine_SpdifOut_type spdifEnable;

        /** SPDIF output configuration */
        struct AudioEngine_ChannelStatus_type spdifConfig;

        /** If true, data over SPDIF is 16 bits, otherwise 24 bits */
        RMbool force16bitsSpdif;

        /** Number of decoders associated with the engine, described in the decoder() table */
        int decoderCnt;

        /** Configuration of the decoders associated with the engine */
        struct SMRUAAudioDecoderConfig decoder[RMCFG_AUDIO_DECODER_CNT];

        /** flag to do downmixing in the post-processing phase rather than decoding phase */
        RMbool forcePostProcessingDownmixing;

        /** flag to raise the center channel volume by 6 db */
        RMbool centerUp;

        /** output channels - duplicate decoder info, to avoid format-specific processing */
        enum AudioOutputChannels_type outputChannels;

        /** output LFE channel - duplicate decoder info, to avoid format-specific processing */
        RMbool lfe;

        /** this parameter tells if the current engine is master or slave if inter-engine mixing is used */
        RMbool MasterEngine;

		/** when HDMI passthrough is used and multichannel analog and spdif output is on same engine then need to disable engine datapads to avoid noise on those outputs */
		RMbool DisableI2SPads;
		RMbool DisableSPDIFPads;
    };

    /// MRUA video decoder configuration definition.
    struct SMRUAVideoDecoderConfig
    {
        RMuint32                        engineID;                   /**< MRUA module ID, -1 if engine not instantiated yet */

        RMuint32                        decoderID;                  /**< MRUA module ID, -1 if codec not instantiated yet */

        enum VideoDecoder_Codec_type    type;                       /**< MRUA codec type */

        int                             contentIndex;               /**< Index into #SGlobals::contentTab parameter table */

        RMuint32                        surfaceID;

        struct VideoDecoder_NextPicture_type *currentPic;
    };

    /// MRUA video layer configuration definition.
    struct SMRUAVideoLayerConfig
    {
        enum EGroupID groupID;                                          /** GRID_Main for main video etc. */
        struct SRectangle source_window;                                /** Size and position of the visible window within the content (same as the ones obtained via IDirectFBDisplayLayer::GetSourceRectangle) */
        struct SRectangle output_window;                                /** Size and position of the content on screen (same as the ones obtained via IDirectFBDisplayLayer::GetScreenRectangle) */
        struct DispMainVideoScaler_FilterSelection_type filter_mode;    /** Filter selection (main video layer only) */
    };

    /// Driver configuration parameters
    struct SMRUAConfig
    {
        /// output configuration
        struct SMRUAOutputConfig output;

        /// audio resources configuration
        struct
        {
            /** Number of active engines, described in the engine() table */
            int engineCnt;

            /** Configuration of the active engines */
            struct SMRUAAudioEngineConfig engine[RMCFG_AUDIO_ENGINE_CNT];

            /** Secondary audio is used and inter-engine mixing is used */
            RMbool InterEngineMixing;
        }
        audio;

        /// video resources configuration
        struct
        {
            /** Number of active decoders, described in decoder() table */
            int decoderCnt;

            /** Configuration of the decoders */
            struct SMRUAVideoDecoderConfig decoder[RMCFG_VIDEO_ENGINE_CNT * RMCFG_VIDEO_DECODER_CNT];

            /** Configuration of the video layers */
            struct SMRUAVideoLayerConfig videoLayer[2];
        }
        video;
    };

    ///\typedef typedef bool (*TConfigurationPreview)(const struct SContentInfo *content, const struct rmcci *drm, const struct SMRUAOutputConfig *settings, struct SMRUAConfig *configuration)
    ///\brief Called by the presentation engine whenever A/V configuration is about to change
    ///
    /// The module being called may modify the configuration parameter in place.
    /// The changes will be applied without any verification though, resulting in undefined consequences if the changes
    /// are incorrect.
    ///\ingroup loconf
    ///\param pRUA current MRUA handle
    ///\param content content parameters
    ///\param drm DRM restrictions
    ///\param settings capabilities and preferences
    ///\param adjustments Currently active output adjustments
    ///\param configuration suggested configuration on entry, requested configuration on exit
    ///\return If true, the caller is to enforce the requested configuration, if false the caller should only save it as current (the callback has enforced the configuration itself)

    typedef bool (*TConfigurationPreview)(const struct RUA *pRUA,
                                          const struct SContentInfo *content,
                                          const struct rmcci *drm,
                                          const struct SMRUAOutputConfig *settings,
                                          const struct SAdjustment *adjustments,
                                          struct SMRUAConfig *configuration);

    ///\typedef typedef bool (*TConfigurationConfirm)(const struct SMRUAConfig *configuration)
    ///\ingroup loconf
    ///\brief Called by the presentation engine whenever A/V configuration has changed
    ///
    /// The module being call can only accept or reject the configuration, but not change it.
    ///\param pRUA current MRUA handle
    ///\param content content parameters
    ///\param configuration configuration that has just been enforced
    ///\return If true, the configuration is accepted, if false the caller is to repeat the configuration (including the #TConfigurationPreview call)

    typedef bool (*TConfigurationConfirm)(const struct RUA *pRUA, const struct SContentInfo *content, const struct SMRUAConfig *configuration);

    ///\typedef typedef UINT32 (*TDynamicMemAlloc)(UINT32 size)
    ///\ingroup loconf
    ///\brief External dynamic memory allocator (optional) \change Added 7-26-2007

    typedef UINT32 (*TDynamicMemAlloc)(UINT32 size);

    ///\typedef typedef void (*TDynamicMemFree)(UINT32 address)
    ///\ingroup loconf
    ///\brief External dynamic memory dealocator (optional, for memory allocated with #dynMemAlloc allocator). \change Added 7-26-2007

    typedef void (*TDynamicMemFree)(UINT32 address);

    /// HDCP SRM info
    struct SMediaSRM
    {
        RMbool update;
        RMuint32 size;
        RMuint8 SRM[5 * 1024];
    };

#define         CONTENT_TABLE_LENGTH            (RMCFG_VIDEO_ENGINE_CNT * RMCFG_VIDEO_DECODER_CNT + RMCFG_AUDIO_ENGINE_CNT * RMCFG_AUDIO_DECODER_CNT)


    /// System-wide configuration values, shared between Mono, Curacao, DCC-HD and DirectFB
    ///\ingroup globals
    struct SGlobals
    {
        /// Underlying RUA layer handle
        struct RUA *pRUA;

        /// Underlying DCC layer handle
        struct DCC *pDCC;

        /// Microcode scheduler shared memory (per engine)
        struct MpegEngine_SchedulerSharedMemory_type shmem[2];

        /// Shared memory per engine for decoders - used mainly for VC1/JPEG codec - once allocated it will be reused for every decoder on that engine (per engine)
        struct MpegEngine_DecoderSharedMemory_type decmem[2];

        /// Shared memory per audio engine
        struct AudioEngine_DecoderSharedMemory_type audioSharedMem[2];

        /// Lock for exclusive access to global information excluding information protected by other locks (scalers, groups etc.).
        /// Make sure that if you need to modify the complete global information, you lock this first and then the other globals locks. The locking order is important.
        RMcriticalsection globalsLock;

        /// Semaphore released at every vsync
        RMtimeoutSemaphore vSyncLock;

        /// Number threads waiting on vSyncLock
        int vSyncLockCount;

        /// Media time when the vsync occurred
        RMuint64 vSyncMediaTime;

        /// Scaler allocation and configuration info

        /// Per-group configuration
        struct SGroupInfo groupTab[GRID_Last - GRID_First];

        /// Per-group current configuration
        struct SGroupInfo groupTabCurrent[GRID_Last - GRID_First];

        /// Scalers are allocated by the DCC-HD presentation engine
        /// and controlled by the output control module (DirectFB)
        struct SOutputInfo scalerTab[10];

        /// Set by the outside code whenever it reconfigures the GFX scaler and reset by DirectFB when it
        /// reacquires the scaler
        RMbool gfxScalerDirty;

        /// Group ID of the "MainVideo" DirectFB layer - managed by the DirectFB driver
        enum EGroupID mainVideoLayerGroupID;

        /// Group ID of the "2ndVideo" DirectFB layer - managed by the DirectFB driver
        enum EGroupID secondVideoLayerGroupID;

        /// Lock for exclusive access to global group and scaler information (groupTab*, scalerTab, gfxScalerDirty, *VideoLayerGroupID)
        RMcriticalsection groupsScalersLock;

        /// Semaphore to signal the existence of at least one presentation engine to the reconfiguration thread in DirectFB, making it suspend itself
        RMtimeoutSemaphore presEngExistenceLock;

        struct SMRUAOutputConfig    preferences;            ///< Output capabilities and preferences as specified by user/UI

        struct SMRUAOutputConfig    settings;               ///< Output capabilities and preferences as detected at run-time

        struct SAdjustment          adjustments;            ///< Currently active adjustments as specified by user/UI \note Can contain #ADJ_VOLUME, #ADJ_MUTE or #ADJ_VOLUME + #ADJ_MUTE (i.e. volume set but currently muted) adjustments

        struct rmcci                restrictions;           ///< Currently active output restrictions

        struct SMRUAConfig          configuration;          ///< Current output configuration (settings applied to current content and restrictions)

        char                        mediaDeviceName[2048];  ///< Name of the device on which the disc-based media is mounted - may be empty if disc-based content exists

        struct SMediaSRM            mediaSRM;               ///< Media SRM info

        /// Current content parameter table
        struct SContentInfo         contentTab[CONTENT_TABLE_LENGTH];

        /// Content run-time parameter table \change Added 4-9-2007

        /// Entries here are reset on DCCHD::CPresEng::AllocSubstream and DCCHD::CPresEng::ReallocSubstream
        /// but not on configuration cycles.
        /// They are updated by the core presentation engine upon decoder notification events.
        ///
        /// This information can be used for fine-tuning the external connections
        /// with the most detailed level of content information.
        ///
        /// Normally the clients do not access this table directly, but rather through SContentInfo::decoderInfo pointers
        /// from the associated #contentTab entries holding the nominal content parameters.
        ///
        /// \internal Entries in this and #contentTab tables for a given content have the same index.
        struct SRTContentInfo       rtContentTab[CONTENT_TABLE_LENGTH];

        /// Callbacks provided by DCC-HD clients
        struct
        {
            /// Optional: configuration change preview
            TConfigurationPreview previewConfig;

            /// Optional: configuration change confirmation
            TConfigurationConfirm confirmConfig;

            /// Optional: output configuration monitoring

            /// Called by the presentation engine periodically to check the output configuration status.
            /// Returns true if the output configuration has changed since the last #checkOutput or #previewConfig calls
            bool (*checkOutput)(void);

            /// Optional: conversion of preferences into settings

            /// Called by the presentation engine
            /// to convert the new preferences into settings
            void (*updateSettings)(void);

            /// External dynamic memory allocator (optional) \change Added 7-26-2007

            /// The allocator returns the physical address of the memory.
            /// The memory must still come from the DCC-HD memory map, so that dcchd_mruamem_address2mapped(), dcchd_mruamem_address2id(),
            /// dcchd_mruamem_id2dramindex(), etc can be used to determine it's virtual address or location.
            ///
            /// \note
            /// - Normally this call allocates DirectFB "video" memory and is used by the Presentation Engine
            /// to allocate memory for JPEG, Blu-ray IG and other decoders that are used in only a few of the use cases.
            /// - Objects allocated by this call disrupt the memory defragmentation mechanism in DirectFB. Consequently,
            /// this call should be used sparingly and the memory should be freed as soon as possible.
            TDynamicMemAlloc dynMemAlloc;

            /// External dynamic memory dealocator (optional, for memory allocated with #dynMemAlloc allocator). \change Added 7-26-2007
            TDynamicMemFree dynMemFree;

        }
        callback;

        /// Callbacks provided by DirectFB clients
        struct
        {
            /// Optional: configuration change preview (installed normally through the AdvancedMediaProvider #Cmd_SetCallbacks command)
            TConfigurationPreview previewConfig;

            /// Optional: configuration change confirmation (installed normally through the AdvancedMediaProvider #Cmd_SetCallbacks command)
            TConfigurationConfirm confirmConfig;
        }
        user_callback;
    };

    ///\defgroup loconf Low-level Output Configuration
    /// API elements for customizing the A/V output configuration.
    ///
    /// Allow a client application to control dynamically and in detail the low (platform) level A/V output configuration.
    ///
    /// The low-level configuration is updated every time the client application changes the \ref hiconf or a media or DRM
    /// change is detected in the presentation content.
    ///
    /// Client applications install their configuration change callbacks through the #Cmd_SetCallbacks common media command
    /// (at DirectFB or \ref control level).
    ///
    /// Client playback control modules install their configuration change callbacks through the DCCHD::CPresEng::SetApplicationCallbacks call (at \ref preseng level).
    ///
    /// \note
    /// - New callbacks overwrite old ones.
    /// - There is only one set of callbacks, that apply to all presentation engine, playback control and/or AMP instances
    /// in the system in the same time. Consequently, the low level configuration is typically handled in one single place,
    /// at any level.

    ///\defgroup outconf Output Configuration
    /// API elements for controlling the A/V output configuration.
    ///
    /// There are two levels of control:
    /// - \ref hiconf
    /// - \ref loconf
	int AlphaApplyAudioConfig(struct SGlobals *pGlobals,struct SMediaFormat *audio_format,void *pPrivateData);
#ifdef __cplusplus
}
#endif

#endif // _GLOBALS_H_

/**
  $Log: globals.h,v $
  Revision 1.137.8.1  2011-03-02 01:28:33  klin
  BugId:31498
  fix noise on the stereo output when doing HDMI passthrough with DD+
  SEND_COMMENT_BUGZILLA

  Revision 1.137  2009-09-02 15:08:07  sotescu
  BugId: none
  Typedefs for dynamic memory functions.

  Revision 1.136  2009-07-01 14:24:07  sotescu
  BugId: none
  Moved the config cycle from HDMI check thread to a new, dedicated thread that will only reconfigure the outputs when there's no presentation engine; otherwise the reconfiguration will be done by PresEng.

  Revision 1.135  2009-06-30 18:02:13  sorin
  BugId: none
  Doc spelling

  Revision 1.134  2009-05-07 15:46:22  sotescu
  BugId: none
  Added back the CRT scaler.

  Revision 1.133  2009-04-27 22:18:01  sorin
  BugId: none
  Removed the CRT scaler definition for now as the code does not support unavailable scalers yet

  Revision 1.132  2009-04-25 00:38:01  sorin
  BugId: none
  Make the scaler table of a size that is independent of the compile-time scaler definitions and big enough for all practical architectures in order to maintain future binary compatibility.

  Revision 1.131  2009-04-25 00:33:29  sorin
  BugId: none
  Allow both-compile time and run-time configuration of available scalers

  Revision 1.130  2009-03-21 05:52:39  sorin
  BugId: CT-6111
  SEND_COMMENT_BUGZILLA
  Added DRA support, tested with Red Cliff

  Revision 1.129  2009-03-12 04:49:59  sorin
  BugId: none
  Moved the Video Module ID definitions from the configuration file to the globals one.

  Revision 1.128  2008-12-02 19:55:06  sorin
  BugId: none
  Typos

  Revision 1.127  2008-10-07 23:24:26  sorin
  BugId: none
  Doc

  Revision 1.126  2008-10-07 17:03:12  sorin
  BugId: none
  Hide internal adjustment value, used to store the volume during the MUTED state

  Revision 1.125  2008-10-07 04:05:09  sorin
  BugId: none
  Added support for global volume

  Revision 1.124  2008-06-27 03:54:08  sorin
  BugId: none
  Replaced pixel alignment flag in SOutputInfo with similar in SMediaInfo in order to facilitate its setting (the output info structures are no accessible at the navi layer, where the alignment decision is made)

  Revision 1.123  2008-06-17 14:17:39  sotescu
  BugId: none
  Added alignedWithGraphics flag to content info for BDJ graphics/video alignment.

  Revision 1.122  2008-06-06 12:53:07  sotescu
  BugId: none
  New groups_and_scalers lock.

  Revision 1.121.2.1  2008-06-04 09:42:22  sotescu
  BugId: none
  New groups_and_scalers lock.

  Revision 1.121  2008-05-22 16:26:33  sorin
  BugId: none
  Audio channel delay doc update

  Revision 1.120  2008-02-21 23:06:10  sotescu
  BugId: ct-4245
  Added support for content "active area" (the screen pixels occupied by the useful content of the video). Slave groups are positioned and sized relative to this active area (e.g. secondary video in BDJ).

  Revision 1.119  2008-01-24 03:49:41  sorin
  BugId: CT-3099
  Expanded DTS-LBR support to BD pres eng and config dump

  Revision 1.118  2007-12-11 16:07:14  anagy
  BugId: 3099
  Secondary Audio Implementation

  Revision 1.115.10.4  2007-12-07 13:09:52  anagy
  BugId: None
  Updated to HEAD

  Revision 1.117  2007-12-06 11:29:02  sotescu
  BugId: none
  Added "opaque" attribute to groups.

  Revision 1.116  2007-11-07 16:31:28  sotescu
  BugId: none
  Added copy of groupTab for group settings optimization.

  Revision 1.115  2007/09/30 09:32:50  sorinp
  optimized scheduling type signaling

  Revision 1.114  2007/09/19 18:37:26  sorinp
  BugId:NONE
  Added support for real time/user mode thread selector

  Revision 1.113  2007/08/29 20:02:55  sorinp
  doc

  Revision 1.112  2007/08/20 20:01:31  sorinp
  doc updates

  Revision 1.111  2007/08/20 17:48:03  sorinp
  doc update

  Revision 1.110  2007/08/14 18:02:15  sbeysserie
  BugId: none
  Doxygen fix: reference TDynMemAlloc instead of dynMemalloc

  Revision 1.109  2007/08/09 17:00:40  sotescu
  BUGCT: 3674
  When optimizing outports config take into account the change in 1080p24 vfreq (23.97 or 24).

  Revision 1.108  2007/08/09 14:49:07  sotescu
  BUGCT: 3664
  Integrated changes that expose the global allocator/deallocator DirectFB callbacks.

  Revision 1.107  2007/07/07 23:42:58  sotescu
  BUGCT: none
  Added secondary graphics layer and exposed video layer src/dst rectangles and filter selection.

  Revision 1.106  2007/07/03 21:51:15  sorinp
  Fix doc

  Revision 1.105  2007/07/03 17:35:10  anagy
  Audio Shared memory

  Revision 1.104  2007/07/02 23:48:03  anagy
  TestTone Implementation

  Revision 1.103  2007/07/02 22:18:44  sorinp
  Added audio type engine selection

  Revision 1.102  2007/04/10 02:50:50  sorinp
  renamed the suspend output callback

  Revision 1.101  2007/04/10 02:13:00  sorinp
  Made the run-time conntent info a separate structure in prepapration for using it in the configuration cycle

  Revision 1.100  2007/04/09 19:32:04  sorinp
  Added real-time info for core audio and generic video

  Revision 1.99  2007/04/06 23:22:30  sorinp
  fix compilation problem

  Revision 1.98  2007/04/06 04:43:08  sorinp
  doc typo

  Revision 1.97  2007/04/06 00:57:58  sorinp
  Removed redundant and wrongly used callback.
  Added A/V control entry point in the A/V configuration structure, in preparation for implementation of real-time info-based configuration mechanism.

  Revision 1.96  2007/04/05 15:34:23  sorinp
  Added MPEG2 video run-time info definition

  Revision 1.95  2007/04/04 03:02:00  sorinp
  Merged experimental_core_audio_config_support branch

  Revision 1.94  2007/04/03 17:37:43  sotescu
  BUGCT: none
  Added depth support for groups.

  Revision 1.93  2007/03/21 01:25:11  sorinp
  Made separate SPDIF and I2S connections to the HDMI output

  Revision 1.92  2007/03/20 00:15:12  sbeysserie
  Add end of line.

  Revision 1.91  2007/03/19 16:31:09  sorinp
  Moved log at the end of the file

  Revision 1.90  2007/02/21 20:41:00  sorinp
  doc update

  Revision 1.89  2007/02/21 20:25:08  sorinp
  doc update

  Revision 1.88  2006/12/13 12:02:57  anagy
  - UPDATE -
  updated PresEng. related modifications from Version.1 branch

  Revision 1.87.8.2  2006/12/12 17:32:44  sorinp
  Removed change doc tags in prepearation for the official 1.0.0 release

  Revision 1.87.8.1  2006/12/09 02:57:20  sorinp
  fixed MLP support: MRUA codec type is DVDA, not AC3!

  Revision 1.87  2006/10/14 05:02:51  sorinp
  Added priority boost support

  Revision 1.86  2006/10/06 19:23:09  anagy
  spec

  Revision 1.85  2006/09/26 03:03:54  sorinp
  Updated to B.6.0 level

  Revision 1.84  2006/09/22 17:43:01  anagy
  Define for the Content table length

  Revision 1.83  2006/09/21 19:12:09  sorinp
  Added cc substream ID in the content info structure

  Revision 1.82  2006/09/16 05:00:52  sorinp
  Updated doc (status field)

  Revision 1.81  2006/09/07 17:52:21  sotescu
  Added callback to force a PresEng reconfiguration whenever the HDMI cable is inserted/removed.

  Revision 1.80  2006/09/06 23:21:53  cwolff
  * Read HDCP SRM file from disc and pass to internals code

  Revision 1.79  2006/09/03 01:10:05  sorinp
  Added support for audio decoder info posting in SGlobals, in order to allow DFB to set the audio config corectly

  Revision 1.78  2006/09/02 23:18:42  sorinp
  Added decoder info to the content info

  Revision 1.77  2006/08/31 04:41:33  sorinp
  Updated doc change list to B.5.0

  Revision 1.76  2006/08/29 23:03:53  cwolff
  * Use HDCP SRM stored on flash volume
  * Add support to read updated HDCP SRM file from content medium

  Revision 1.75  2006/08/28 23:09:17  sorinp
  Simplified use of media locator - made it a simple device name.

  Revision 1.74  2006/08/28 21:13:52  sorinp
  Added main content locator to allow retrieval of media-related info from the disc (example: SRM file)

  Revision 1.73  2006/08/25 02:06:03  sorinp
  Added support for downmixing position in the processing chain selection
  Added support for center channel automatic amplification

  Revision 1.72  2006/08/05 02:40:07  sorinp
  Added SPDIF downsampling (16 bits) support

  Revision 1.71  2006/08/01 18:19:38  sorinp
  doc fix

  Revision 1.70  2006/07/24 22:22:44  anagy
  12 channel volume

  Revision 1.69  2006/07/11 06:20:20  sorinp
  reversed SPDIF related change

  Revision 1.68  2006/07/08 07:06:23  anagy
  normal byte order for channel status

  Revision 1.67  2006/07/02 21:37:12  sotescu
  Fixed DVD hang when using SPU as Subpicture slave.

  Revision 1.66  2006/06/30 06:24:05  sotescu
  Major changes to group/layer handling (grouped in em86xx_group_config.c/h).

  Revision 1.65  2006/06/27 19:33:19  sorinp
  Upgraded doc to B.2.0 level

  Revision 1.64  2006/06/26 19:27:47  sorinp
  Fixed SPID status word setting and reporting

  Revision 1.63  2006/06/24 07:25:21  sorinp
  updated SPDIF status word, still needs work

  Revision 1.62  2006/06/15 05:26:41  sorinp
  Updated and propagated changes in adjustments API

  Revision 1.61  2006/06/07 12:38:47  anagy
  shared memory for decoders per engine

  Revision 1.60  2006/06/06 02:47:02  sorinp
  fixes and updates, mostly related to av config

  Revision 1.59  2006/05/30 09:02:20  sorinp
  allow detailed bitstream settings in digital audio connections

  Revision 1.58  2006/05/30 01:50:18  sorinp
  more configuration related changes

  Revision 1.57  2006/05/29 18:35:13  sotescu
  Now setting a dirty flag whenever the GFX scaler is acquired.

  Revision 1.56  2006/05/25 03:35:36  sorinp
  Removed all the old config-related elements. Code does not compile !!!

  Revision 1.55  2006/05/24 02:16:45  sorinp
  Added MRUA pointer as config callback parameter to allow custom MRUA setup

  Revision 1.54  2006/05/16 22:11:18  sorinp
  renamed config.h to more specific dcchd_config.h to avoid conflict with DFB

  Revision 1.53  2006/05/16 07:14:28  sorinp
  Fixes for new audio config

  Revision 1.52  2006/05/15 02:24:47  sorinp
  updates

  Revision 1.51  2006/05/14 19:27:59  sorinp
  Updated Get/SetConfiguration syntax

  Revision 1.50  2006/05/14 18:49:25  sorinp
  integrated rmcci

  Revision 1.49  2006/05/14 02:18:44  sorinp
  Added UpdateSettings callback

  Revision 1.48  2006/05/12 15:44:25  sotescu
  Fixed typo + added user callbacks.

  Revision 1.47  2006/05/11 19:56:43  anagy
  mixerWeight is allready a structure with 8 channels

  Revision 1.46  2006/05/06 04:58:53  sorinp
  doxygen fixes

  Revision 1.45  2006/05/05 23:07:52  sorinp
  moving to new memory management. Not compiling yet!

  Revision 1.44  2006/05/05 18:19:56  sorinp
  Updates, fixes

  Revision 1.43  2006/05/05 01:44:56  sorinp
  spec updates

  Revision 1.42  2006/05/02 00:59:40  sorinp
  Added dynamic memory pools support in the static memory map
  Removed the mem management callback form SGlobals, will use static linking

  Revision 1.41  2006/04/29 04:23:08  mfedoreanu
  no message

  Revision 1.40  2006/04/29 04:15:18  sorinp
  Updates

  Revision 1.39  2006/04/28 22:07:42  anagy
  beginned using of the new config structures

  Revision 1.38  2006/04/27 07:30:36  sorinp
  Updated A/V config spec, new memory allocation (static) spec

  Revision 1.37  2006/04/22 22:25:59  anagy
  audio engine select

  Revision 1.36  2006/04/22 19:24:31  sorinp
  Integrated PCMX PBC support
  Started new audio config support

  Revision 1.35  2006/04/22 18:30:31  anagy
  pcmx params

  Revision 1.34  2006/04/21 02:37:15  sorinp
  Allocate MRUA memory only when  starting up a presentation engine, to avoid memory conflicts with Mono and to maintain DirectFB independence.

  Revision 1.33  2006/04/11 23:05:11  sorinp
  Adedd RGB_16_235 color space format
  Updated the audio globals definitions

  Revision 1.32  2006/04/11 19:58:47  anagy
  PCM_BR added to audio config structs.

  Revision 1.31  2006/04/11 06:56:23  sorinp
  Updated global and configuration definitions, to add support for channel delay and multiple simultaneous audio output formats

  Revision 1.30  2006/04/01 02:31:20  sorinp
  Made the layer IDs public definitions

  Revision 1.29  2006/03/09 14:25:32  anagy
  updated audio config structures

  Revision 1.28  2006/03/09 13:49:27  sotescu
  Changes for playing a video to a surface / capture.

  Revision 1.27  2006/03/04 06:14:07  sorinp
  Moved frame callback fields into more general session parameters structure and handling

  Revision 1.26  2006/02/28 18:20:40  sotescu
  Fixed a memory overwrite situation due to a miscalculated buffer size.

  Revision 1.25  2006/02/23 18:06:47  sotescu
  Modified PresEng SetConfiguration parameters to support frame notification callbacks.

  Revision 1.24  2006/02/23 17:42:51  sotescu
  Modified PresEng SetConfiguration parameters to support frame notification callbacks.

  Revision 1.23  2006/02/21 16:48:25  sotescu
  Modified PresEng SetConfiguration parameters to support frame notification callbacks.

  Revision 1.22  2006/02/17 20:38:54  sorinp
  removed the /change tags to start clean for the enxt release

  Revision 1.21  2006/02/17 04:49:48  sorinp
  Doc nicetities

  Revision 1.20  2006/02/07 19:56:43  sorinp
  Added vSyncMediaTime

  Revision 1.19  2006/01/31 00:33:44  sorinp
  Added vsync lock count to support multiple threads

  Revision 1.18  2006/01/31 00:22:46  sorinp
  Added VSync support through tmeout seaphore

  Revision 1.17  2006/01/30 09:00:57  sorinp
  Added configuration and adjustment definitions

  Revision 1.16  2006/01/16 17:22:58  sorinp
  typo

  Revision 1.15  2006/01/16 17:21:43  sorinp
  Added layer to group ID correspondence info

  Revision 1.14  2005/12/23 01:10:03  sorinp
  made memory size and banks configurable

  Revision 1.13  2005/12/22 22:49:14  sorinp
  Updates in globals

  Revision 1.12  2005/12/21 15:08:24  sorinp
  added new hw config items

  Revision 1.11  2005/12/20 18:30:38  sorinp
  removed config change detection callback, as it must work without DCC-HD presentation engine also

  Revision 1.10  2005/12/20 08:25:48  sorinp
  Added codec and hardware configuration support in SGlobals

  Revision 1.9  2005/11/29 11:04:06  mfedoreanu
  empty struct generates nice code

  Revision 1.8  2005/11/29 10:22:38  mfedoreanu
  empty struct generates nice code

  Revision 1.7  2005/11/11 18:42:07  sotescu
  DirectFB: working support for: layer size&positioning, mixer background color, layer enable/disable.

  Revision 1.6  2005/10/06 17:21:25  sotescu
  DirectFB: moved SDecoderParams to the end of the file.

  Revision 1.5  2005/10/06 08:07:48  anagy
  added streamID definition

  Revision 1.4  2005/10/05 18:43:29  sorinp
  Mostly doc upgrades

  Revision 1.3  2005/10/05 13:28:33  sotescu
  changed scaler ID value

  Revision 1.2  2005/09/30 11:33:25  sorinp
  typo fix

  Revision 1.1  2005/09/30 10:13:54  sorinp
  Made globals definition a separate file

*/

