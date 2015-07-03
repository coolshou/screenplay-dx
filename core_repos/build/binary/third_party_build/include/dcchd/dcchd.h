/*****************************************
 Copyright  2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   dcchd.h
  @brief  Public definitions of the DCC-HD framework

  @author Sorin Papuc
  @date   2005-06-01

  $Header: /bigbig/dungeon/dcchd_project/dcchd/core/dcchd.h,v 1.298.8.2 2010-02-11 03:24:04 smanciulea Exp $

*/

/**
 * \defgroup preseng Presentation Engine API
 */

#ifndef _DCCHD_H_
#define _DCCHD_H_

// Include files
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   /* for `sleep()'   */

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#include <rmdef/rmdef.h>            ///< RUA basic definitions
#include <rua/include/rua.h>
#include <rua/include/rua_property.h>
#include <dcc/include/dcc.h>
#include <dcc/src/dcc_common.h>
#include <rmlibcw/include/rmlibcw.h>
#include <rmrtk/include/rmrtk.h>
#include <rmscc/include/rmscc.h>
#include <emhwlib/include/emhwlib_versions.h>

#ifndef __INTS_DEFINED__
#define __INTS_DEFINED__
typedef RMint16 INT16;      ///< INT16 must be defined before including mdefs.h

typedef RMuint16 UINT16;    ///< UINT16 must be defined before including mdefs.h

typedef RMint32 INT32;      ///< INT32 must be defined before including mdefs.h

typedef RMuint32 UINT32;    ///< UINT32 must be defined before including mdefs.h

typedef RMint64 INT64;      ///< INT64 must be defined before including mdefs.h

typedef RMuint64 UINT64;    ///< UINT64 must be defined before including mdefs.h

#endif

#ifdef __cplusplus
}
#endif // __cplusplus

#include "globals.h"        // implementation-specific shared resource definitions
#include "drive_defs.h"
#include "dcchddbg.h"


#if (EM86XX_CHIP >= EM86XX_CHIPID_TANGO3)
#ifdef __cplusplus
extern "C" {
#endif

#include "rmmpegsystemindex/include/rmmpegsystemindex.h"
#include "rmmpegsystemindex/include/rmmpegsystemindexcreator.h"
#include "rmvdemux/include/rmvdemuxapi.h"
#include "rmcore/include/rmcore.h"
#include "rmlibcw/include/rmstrcmp.h"
#include "rmproperties/include/rmexternalproperties.h"

#ifdef __cplusplus
}
#endif
#endif 

/// DCC-HD-wide useful definitions

#ifndef MAX_OUT_BUFS
    // number of outstanding stream data buffers - must be 1 for the current PlaybackControl implementation
    #define MAX_OUT_BUFS    1
#endif

#define MAX_PIDS_PER_TASK       37      ///< maximum pid entries per demux task  ( total 128 filters / 3 tasks but each task has 5 special pid filters reserved )

#define MAX_SECTION_PER_TASK    32      ///< maximum section entries per demux task

#define MAX_PCMX_CHANNELS   	8       ///< The maximum PCMX channel number ( !!! must be bigger than MAX_PCMX_ALSA_CHANNELS )
#define MAX_PCMX_ALSA_CHANNELS	4		///< The maximum alsa PCMX channel number

#define DCCHD_MAX_PATH 2048             ///< maximum length of resource URL/URI/path

typedef unsigned long TStreamID;        ///< (Sub)stream ID type, used to identify the (sub)stream in all things presentation engine. The (sub)stream ID is a 1 bit flag that can be checked in the availabiliyFlags and vizibilityFlags fields of the presentation engine status.

/// DCC-HD root code, common to all media formats
namespace DCCHD
{
    /// CPS parameters
    struct SCpsInfoParams
    {
            int xtask_pid;
            int xtask_info;
    };

    ///\defgroup SMBFLAGS SMetaBuffer flags
    /// Flags used to specify details about data in SMetaBuffer structures
    ///@{
    #define SMBF_MEDIA_DESCRIPTION                  0x0001      ///< the SMetaBuffer.dataDescription field has a valid value

	#define SMBF_TIME_1KHz                         	0x0002      ///< the SMetaBuffer.timeStamp field has a valid 1 KHz time value

    #define SMBF_TIME_90KHz                         0x0004      ///< the SMetaBuffer.timeStamp field has a valid 90 KHz time value

    #define SMBF_TIME_27MHz                         0x0008      ///< the SMetaBuffer.timeStamp field has a valid 27 MHz time value

    #define SMBF_TIME_DISCONTINUITY                 0x0010      ///< time line has been broken between this and the previous buffer

    #define SMBF_DATA_DISCONTINUITY                 0x0020      ///< data has been dropped between this and the previous buffer

    #define SMBF_EOS                                0x0040      ///< data in the buffer is last in the stream

    #define SMBF_LAST_IN_RUN                        0x0080      ///< flag for marking last data buffer before a temporary gap in data, needed to deliver time-sensitive data (example: Interactive Audio) without waiting for an entire buffer to be filled \change Added 10-16-2007

	#define SMBF_TAG_ACCESS_UNIT					0x0100		///< an access unit starts in the buffer

	#define SMBF_TAG_PRESENTATION_UNIT				0x0200		///< a presentation unit starts in the buffer

	#define SMBF_UNIT_OWNER                         0x0400      ///< validates the unitOwner field

	#define SMBF_TAG_SYSTEM_INFO					0x0800		///< the buffer contains system info (PAT. CAT, PMT, PCR, etc)

    #define SMBF_PRIVATE_DATA                       0x1000      ///< the SMetaBuffer.privateData is in use. The value it holds is valid but has meaning only to the module that has set it up

    #define SMBF_PRIVATE_FLAG_PRENG                 0x2000      ///< flag for the private use of the Presentation Engine module - no other module should touch it

    #define SMBF_PRIVATE_FLAG_PRENG_2               0x4000      ///< flag for the private use of the Presentation Engine module - no other module should touch it

    #define SMBF_INTRA_MODULE_RANGE             0xFFFF0000      ///< flag values reserved for intra-module use, i.e. each module can use them internally but can not expect to be preserved when the buffer leaves the module

    #define SMBF_INTRA_MODULE_SHIFT                     16      ///< left shift amount for placing a bit into intra-module range

    ///@}


    /// Generic buffer data type. Contains data and meta info about it.

    /// Meta buffers for more specific data types inherit from this type and append additional data fields and other meta info, together with definitions of flags.
    /// In that case, the size field reflects the new type size.
    struct SMetaBuffer
    {
        /// flags for field validation and binary conditions - use \ref SMBFLAGS values
        RMuint32 flags;

        /// Type of the data carried by the buffer
        struct SMediaFormat dataDescription;

        /// Timestamp associated with the data in the buffer
        RMuint64 timeStamp;

        /// Address of the buffer, NULL if no data buffer is associated with the meta buffer
        unsigned char *pBuffer;

        /// Size of the buffer
        RMuint32 bufferSize;

        /// Address of the actual data, NULL if the buffer is empty, otherwise may point anywhere inside the buffer
        unsigned char *pData;

        /// Size of the actual data, may not exceed the buffer boundaries
        RMuint32 dataSize;

        // ID of the owner of the unit tagged by the #SMBF_TIME_1KHz, #SMBF_TIME_90KHz, #SMBF_TIME_27MHz, #SMBF_TAG_ACCESS_UNIT, #SMBF_TAG_PRESENTATION_UNIT and/or #SMBF_TAG_SYSTEM_INFO flags
        struct
        {
        	RMuint32 id;
        	RMuint32 subId;
        }
        unitOwner;

        /// Implementation-specific data
        RMuint32 privateData;
        RMuint32 privateData2;

		void *pBPhandle;	// buffer pool handle. If buffer is cloned then this parameter will contain the handle of the bufferpool of the original buffer
    };

    ///\defgroup PSFLAGS Presentation Engine status flags
    ///@{
    #define PRENG_STATUS_STATE_STOPPED              0x0001      ///< set if the presentation engine is in the STOPPED state

    #define PRENG_STATUS_STATE_PAUSED               0x0002      ///< set if the presentation engine is in the PAUSED state

    #define PRENG_STATUS_STATE_PLAYING              0x0004      ///< set if the presentation engine is in the PLAYING state

    #define PRENG_STATUS_PLAYING_DIRECTION_FORWARD  0x0008      ///< set if the presentation engine is or will play forward

    #define PRENG_STATUS_PLAYING_DIRECTION_BACWARD  0x0010      ///< set if the presentation engine is or will play backward

    #define PRENG_STATUS_PLAYING_FRAMES_ALL         0x0020      ///< set if all frames are decoded, unless they are late in which case they are skipped, if possible

    #define PRENG_STATUS_PLAYING_FRAMES_KEY_ONLY    0x0040      ///< set if only key (standalone) frames are decoded, regardless of how late or early the other frames are.

    #define PRENG_STATUS_EVENT_AVAILABILITY         0x0080      ///< set if the DCCHD::CPresEng::SPrEngStatus.availabilityFlags field has been updated

    #define PRENG_STATUS_EVENT_COMPLETION           0x0100      ///< set if any of the pending asynchronous commands has completed, either successfully or not

    #define PRENG_STATUS_EVENT_EXTERNAL             0x0200      ///< set if one or more external events has occurred and their corresponding flags in DCCHD::CPresEng::SPrEngStatus.externalEvents has been set

    #define PRENG_STATUS_EVENT_CRT_TIME             0x0400      ///< set if the DCCHD::CPresEng::SPrEngStatus.sysTime field has been updated

    #define PRENG_STATUS_EVENT_FORMAT_CHANGE        0x0800      ///< set if any of the streams and or substreams has changed format

    #define PRENG_STATUS_EVENT_VISIBILITY           0x1000      ///< set if the DCCHD::CPresEng::SPrEngStatus.visibilityFlags field has been updated

    #define PRENG_STATUS_EVENT_STALLING             0x2000      ///< set if the DCCHD::CPresEng::SPrEngStatus.stalledFlags field has been updated \change Added 2-12-2007

    #define PRENG_STATUS_MEDIA_TIME_INVALID         0x4000      ///< set if the DCCHD::CPresEng::SPrEngStatus.mediaTime value is invalid due of stream change, it will be valid at the moment the first picture is displayed

    #define PRENG_STATUS_DISPLAY_SEGMENT            0x8000      ///< set if video is displayed on the screen

    #define PRENG_STATUS_ERROR                      0x10000     ///< set if an internal error occurs, validates the DCCHD::CPresEng::SPrEngStatus.errorCode field

    #define PRENG_STATUS_TIME_DISCONTINUITY         0x20000     ///< set if there has been a discontinuity in the time base of the master stream, resulting in a jump if the media and stream time values \change Added 2-27-2007 \status TBI

    #define PRENG_STATUS_PREBUFFERING               0x40000     ///< set if the presentation engine is in pre-buffering mode \change Added 11-13-2007

    #define PRENG_STATUS_FORMAT_SPECIFIC_FIRST      0x80000     ///< first Presentation Engine status flag available for format-specific information

    ///@}

    // **********************************************************************************************************************

    /// Implementation of presentation services common to all media formats

    /// <B>Concepts</B>
    /// - Presentation engine: An independent unit controlling a number of inter-dependent presentation streams.
    ///   A presentation engine can open multiple presentation streams. A presentation engine has three
    ///   states - STOPPED, PAUSED or PLAYING - that are shared by all of the presentation streams.
    /// - Presentation stream: a complex presentation derived from one single data source and having one single time line.
    ///   In addition to the presentation engine's states, a presentation stream can be also in the STILLED state,
    ///   in which the data flow stops but the interactive features remain functional.
    /// - Presentation substream: individual presentation element (video, audio, graphics, etc) derived from a presentation stream.
    ///   A presentation substream is similar but not identical with a data substream, as it may map dynamically to different data substreams.
    ///   For example, the audio presentation substream is opened once and then can be mapped to different audio substreams in the data when changing languages.
    /// - Inband commands: processing commands synchronized with the data injected in the presentation engine. The command is executed when the target presentation
    ///   module completes processing all the data preceding the inband command but before processing any of the succeeding data. Inband commands are the only way to
    ///   synchronize precisely the behavior of the engine with the incoming data.
    ///
    /// <B>Dynamic behavior</B><BR>
    /// The commands may be synchronous or asynchronous, depending on whether they can guarantee a 1 ms maximum completion time
    /// (ignoring time spent in unrelated threads due to multitasking), except where noted otherwise.
    ///
    /// Synchronous commands return either the #TRESULT_SUCCESS or #TRESULT_ERROR codes, together with an optional result value.
    ///
    /// Asynchronous commands return the #TRESULT_PENDING code and they become pending. The presentation engine monitors their execution
    /// in the background. When the execution terminates, the commands are considered completed (or failed) and the presentation
    /// engine informs the client about this through a #PRENG_STATUS_EVENT_COMPLETION event.
    ///
    /// As the result value, the asynchronous commands return an async command ID,
    /// which will identify the pending command in various presentation engine commands related to asynchronous command,
    /// used to check their status and retrieve information about their final result.
    /// At the beginning, the command will be considered pending. Upon command completion,
    /// it will become either completed or failed.
    /// Command completion/failure is checked for only during the WaitForStatusChange() call and constitutes a status change.
    ///
    /// The specification of presentation engines for individual media formats should clearly define the behavior of each call (sync/async)
    /// so that the calling code does not have to support async behavior unless absolutely necessary.
    ///
    /// Multiple commands may be pending at the same time. However, a command may fail with the #RESULT_BUSY value if internal resources needed
    /// for it are used by a pending command.
    ///
    /// The presentation engine does not guard against re-entrance and/or race conditions and assumes that only one method is called at any time.
    ///
    /// <B>State model</B><BR>
    /// The presentation engine has the following states: UNINITIALIZED, STOPPED, PLAYING, PAUSED.
    ///
    /// The same command may behave differently, depending the state the presentation engine is in at the time of the call.
    /// For details see the presentation engine state chart and/or the specification of the individual command.
    ///
    /// <B>Backward play</B><BR>
    /// In backward play mode only the time flows backward, data is always expected and decoded in the forward direction.
    /// It is the responsibility of the playback control module to supply samples (frames) in reversed order.
    ///
    /// <B>Implementation guidelines</B><BR>
    /// The class does not use hardwired values for the RUA calls, instead it uses values from the configuration table.
    /// The configTable will be supplied by derived classes, thus in effect providing the parameters for customized behavior.
    ///\ingroup preseng
    class CPresEng
    {

    public:

        /// Asynchronous command ID type, used to identify a pending command in all things presentation engine. The async cmd ID is a 1 bit flag that can be checked in the pendingCmds, completedCmds and FailedCmds fields of the presentation engine status.
        typedef unsigned long TAsyncCmdID;

        /// A function called by the presentation engine when a new video frame is for display
        typedef void (*TFrameDisplayCallback)(RMuint32 videoDecoderId, void* callback_param, bool IsError);

        /// Session parameters for the presentation engine
        struct SSessionParams
        {
            /// Session ID, used to identify accessible resource
            int sessionID;

            /// Optional callback for blit-based display

            /// When set to a non-NULL value, the presentation engine uses it
            /// instead of a scaler for display.
            TFrameDisplayCallback frame_callback;

            /// Optional parameter to pass to to the frame display callback frame_callback
            void *frame_callback_param;

            /// Optional decoder memory size; the presentation engine is not allowed to allocate more than this for the decoder.
            RMuint32 decoder_mem_size;

            /// Optional maximum picture width.
            RMuint32 max_picture_width;

            /// Optional maximum picture height.
            RMuint32 max_picture_height;

            /// Optional JPEG profile (detected by DirectFB).
            enum EMhwlibJPEGProfile jpeg_profile;

            /// Maximum acceptable error rate for media samples display, in 0.1 percentage units
            int max_output_error_ratio;
        };

        /// Presentation Engine status info structure.

        /// The time-sensitive flags denote "recent" events and are reset when  WaitForStatusChange() is entered so upon
        /// return the values reflect only the events that occurred since the last WaitForStatusChange() call.
        /// Consequently, the client must make sure that all time-sensitive are either processed or stored separately before a new WaitForStatusChange()
        ///
        /// Format-specific derived classes may use for format-specific purposes the unused portions of these fields
        /// or may add new fields altogether, in a format-specific status information definition.
        struct SPrEngStatus
        {
            /// Flags for engine-wide binary conditions - see \ref PSFLAGS

            /// If none of the PRENG_STATUS_STATE flags are set, the engine is the UNINITIALIZED or inconsistent state
            /// If none of the PRENG_STATUS_PLAYING_DIRECTION flags are set, the engine is the UNINITIALIZED or inconsistent state
            /// If none of the PRENG_STATUS_PLAYING_FRAMES status flags are set, the engine is the UNINITIALIZED or inconsistent state
            /// The PRENG_STATUS_EVENT flags are set if any event of the corresponding class has occurred since the last WaitForStatusChange() call
            RMuint32 statusFlags;

            /// Flags indicating that data can be send to streams or received from substreams

            /// Calling the SendData for a stream and GetSubstreamDataBuffer() for a substream
            /// when the bit corresponding to the stream/substream's ID is set in this field
            /// guarantees the call will return, successfully, immediately.
            ///
            /// The flags remain set as long as the condition continues, i.e. as long as buffers are available
            TStreamID availabilityFlags;

            /// Flags indicating the streams that are in STILLED state

            /// The bit corresponding to the stream/substream's ID is set in this field
            /// while the stream is in STILLED state.
            TStreamID stillFlags;

            /// Flags indicating the substreams for which some media format parameters have changed.

            /// The substreams are identified by the bit corresponding to the substream's ID.
            ///
            /// The new media formats can be retrieved through GetSubstreamParams().
            ///
            /// The flags are cleared at the next WaitForStatusChange() call.
            ///\note Only substreams for which format info is available (and hence are present in the #formatAvailableFlags filed) are monitored for changes.
            TStreamID formatChangedFlags;

            /// Flags indicating the substreams for which media format info is available.

            /// The substreams are identified by the bit corresponding to the substream's ID.
            ///
            /// The media format can be retrieved through GetSubstreamParams().
            TStreamID formatAvailableFlags;

            /// Flags identifying the currently visible substreams

            /// A substream is considered visible if it has not been disabled.
            ///
            ///The flags are set as long as the corresponding substreams are visible
            TStreamID visibilityFlags;

            /// Flags identifying the currently stalled substreams \change Added 2-12-2007

            /// A substream is stalled if it is PLAYING but has no data to render by the nominal schedule.
            /// The behavior in a stalling situation is stream type dependent - video substreams repeat last frame, audio substreams silence themselves.
            ///
            /// The flags are set as long as the corresponding substreams are stalled.
            ///
            /// \note This flag is not intended to reflect every stalling situation generated by normal playback conditions,
            /// but rather special, well defined cases, like the gaps in intermittently supplied streams.
            /// Currently, only the PCMX presentation engine generates stalling information - see DCCHD::CPXMCPresEng
            TStreamID stalledFlags;

            /// Field identifying the currently pending commands

            /// The commands are identified by their async ID flag that was returned in the result code when they were issued.
            /// This field changes both during the Wait... call and
            /// after each command that returned the #TRESULT_PENDING code.
            ///
            /// The flags are cleared at the next WaitForStatusChange() call
            TAsyncCmdID pendingCmds;

            /// Field identifying the commands completed since the last WaitForStatusChange() call.

            /// The commands are identified by their completion flag that was returned in the result code when they were issued.
            /// The result information can be retrieved through the GetCmdResult() call.
            ///
            /// The flags are cleared at the next WaitForStatusChange() call
            TAsyncCmdID completedCmds;

            /// Field identifying the commands that failed since the last WaitForStatusChange() call.

            /// The commands are identified by their completion flag that was returned in the result code when they were issued.
            /// The failure information can be retrieved through the GetCmdResult() call.
            ///
            /// The flags are cleared at the next WaitForStatusChange() call
            TAsyncCmdID failedCmds;

            /// Field of bits corresponding to the external events that have been signaled

            /// The flags are cleared
            /// at the next WaitForStatusChange() call
            RMuint32 externalEvents;

            /// Current media time, updated after each WaitForStatusChange()

            /// Media time is the presentation time of the currently displayed video sample in the first allocated stream
            /// or the one specified by SetMasterStream() call.
            /// \note For motion pictures, the media time closely follows the stream time, but for still or
            /// slow moving pictures the two values can become very different.
            RMuint64 mediaTime;

            /// Current offset between the mediaTime and the stream time

            /// The offset is established EInbandCmdID::INBAND_CMD_TIME_OFFSET in-band commands
            /// It should be taken into account when comparing the #mediaTime value with stream
            /// time values defined externally (for example, in navigation databases or another
            /// stream that must be synchronized with the master one)
            RMuint64 ptsOffset;

            /// system time in seconds. Counts the seconds since the last Start() command
            RMuint32 sysTime;

            /// Current playback speed, in fps*1000 given as a rational fraction.

            /// The playback speed given in N/M frames per second * 1000
            /// Regardless of speed each frame stays on the screen as long as prescribed in the video standard used for display
            RMuint32 playSpeedN, playSpeedM;

            /// Display segment number

            /// The display segment consists of the main video presented between a Start() and the next Stop() with black frame, Start() or Restart().
            /// The display segment number has no meaning in itself, but it can be used to detect different display segments.
            /// This field is validated by the #PRENG_STATUS_DISPLAY_SEGMENT flag.
            /// \note The display segment flag and number is provided for synchronizing of different visual components of the presentation with the main video component.
            RMuint32 displaySegmentNo;

            /// Internal error code, valid only when #PRENG_STATUS_ERROR flag is set

            /// The engine may be rescued from errors (result value smaller than 0x100) by stopping
            ///
            /// The engine may be rescued from failures (result value larger than 0x100) by resetting
            TResultCode errorCode;
        };

        /// Retrieves the status info structure (for inspection only)

        /// The client can retrieve the status pointer once
        /// and then use it repeatedly
        volatile const struct SPrEngStatus *GetStatus();

        /// Retrieves the STC of the master stream

        /// Unlike the mediaTime, the stream time is a constantly changing value,
        /// except during STOPPED and PAUSED states.
        RMuint64 GetStreamTime();

        /// Sets application callbacks for dynamic behavior customization
        static TResultCode SetApplicationCallbacks(struct SGlobals *globals,            ///< global structure to hold the new configuration
                                                   TConfigurationPreview configPreview, ///< new configuration preview callback
                                                   TConfigurationConfirm configConfirm  ///< new configuration preview callback
                                                  );

        /// Presets configuration, i.e. the rarely changing parameters that apply to all streams/substreams

        /// The same as SetConfiguration(), but can be called before a presentation engine is actually instantiated
        /// Unlike SetConfiguration(), the new configuration is simply recorded for future use, without being enforced
        ///
        /// Any of the parameters, except globals, can be NULL, in which case it will be ignored
        static TResultCode PreConfigure(struct SGlobals *globals,           ///< global structure to hold the new configuration
                                        struct SMRUAVideoOutConfig *vCfg,   ///< new video configuration
                                        struct SMRUAAudioOutConfig *aCfg,   ///< new audio configuration
                                        struct SAdjustment *av              ///< new adjustments
                                        );

        /// Sets configuration, i.e. the rarely changing parameters that apply to all streams/substreams

        /// The configuration will be changed regardless the current state of the presentation.
        /// If the presentation has not started yet, the new values will apply when it will start.
        /// If the presentation has already started, the new values will be be enforced,
        /// possibly with noticeable but temporary side effects - image/audio gaps, etc (no seamlessness guarantee).
        ///
        /// The new configuration applies to all presentation engines, present and future instances
        ///
        /// NULL parameters will simply generate a configuration cycle (i.e. callbacks will be called) with the current parameters.
        /// The application can force this way a low level parameter change.
        virtual TResultCode SetConfiguration(struct SMRUAVideoOutConfig *vCfg = NULL,   ///< new video configuration; if NULL, the existing one is kept
                                             struct SMRUAAudioOutConfig *aCfg = NULL    ///< new audio configuration; if NULL, the existing one is kept
                                            );

        /// Establishes the DRM rules
        virtual TResultCode SetDRMRules(struct rmcci *drm);

        /// Establishes the DRM rules when no pres eng is available
        static TResultCode SetDefaultDRMRules(struct SGlobals *pGlobal, struct rmcci *drm);

        /// Adjusts appearance

        /// If the presentation has not started yet, the new values will apply when it will start.
        /// If the presentation has already started, the new values will be be enforced.
        /// The change is guaranteed to be seamless.
        /// The values set through this method are not persistent, they will apply only during the life of the current presentation engine instance.
        /// The adjustments are guaranteed to apply only to the specified components
        /// (but the call may fail if the adjustment is not applicable to the specified components)
        virtual TResultCode AdjustOutput(TStreamID s,           ///< ID of the stream to be adjusted, use 0 for all streams
                                         TStreamID ss,          ///< ID of the substream to be adjusted, use 0 for all substreams
                                         enum EAdjustment as,   ///< adjustment(s) selector(s)
                                         struct SAdjustment *av ///< adjustment(s) value(s)
                                        );

        /// Structure for specifying stream configuration parameters

        /// By specifying transfer and internal buffers of different (total) size,
        /// an application can control separately the amount of pre-buffering done
        /// to account for channel jitter and the amount of internal buffering done
        /// to account for output (decoders) jitter. The later can be minimized in
        /// order to minimize the delay between the input and output thus maximizing
        /// the responsiveness of the system
        struct SStreamCfgParams
        {
            int bufferCount;        ///< number of DRAM transfer buffers, retrievable through GetDataBuffer()
            int bufferSize;         ///< size of each DRAM transfer buffers; actual size may be different due to allocation constraints, see RUA buffer allocation guidelines
            int internalBufferSize; ///< size of the internal buffer, in which data is delivered by SendData(). Determines the stream's contribution to the delay in the system. Can not be smaller than bufferSize or larger than bufferSize * bufferCount
        };

        /// Structure for specifying substream configuration parameters

        /// By specifying the internal buffer size, an application can control
        /// the substream's contribution to the system delay
        struct SSubstreamCfgParams
        {
            int                 bufferCount;            ///< number of DRAM transfer buffers, retrievable through GetSubstreamData(). It is used only for substreams processed externally, ignored for those processed internally
            int                 bufferSize;             ///< size of each DRAM transfer buffers; actual size may be different due to allocation constraints, see RUA buffer allocation guidelines. It is used only for substreams processed externally, ignored for those processed internally
            int                 internalBufferSize;     ///< size of the internal buffer, in which data is delivered from the stream
        };

        // Data buffer utilization info
        struct SBufferInfo
        {
            UINT32 buffer_size;
            UINT32 data_size;
        };

        /// Stream parameter selector
        enum ESParSel
        {
            SEL_PCR_ID = 1,             ///< parameter is the new PCR ID.
            SEL_MAX_DELAY,              ///< parameter is the maximum time discontinuity in stream which doesn't generate event
            SEL_SECTIONTABLE,           ///< parameter is the new section table.

            S_SEL_FIRST_SPECIFIC = 0x10	///< format-specific selectors can be defined from this value up
        };

        /// Stream parameters
        union USPars
        {
            unsigned int    PCR_PID;        ///< MPEG2 Transport Stream Packet ID for the packets carrying the PCR info
            RMuint32        Max_Delay;      ///< Maximum time discontinuity which doesn't generate event (in 90kHz units)
            struct PSFMatchSection_type SectionTable[ MAX_SECTION_PER_TASK ];   ///< Section filter table for a stream
        };

        /// Substream parameter selector for ChangeSubstreamParams() and GetSubstreamParams() methods
        enum ESSParSel
        {
              SEL_ID = 1,               ///< parameter is the stream selector. Exact meaning depends on the media and substream type at the time of the call
              SEL_DEMUX_BUFFER_STATUS,  ///< parameter is the buffer info for the stream demultiplexer - read-only parameter
              SEL_BUFFER_STATUS,        ///< parameter is the buffer info for the substream decoder - read-only parameter
              SEL_MEDIA_INFO,           ///< parameter is the media info for the substream - read-only parameter
              SEL_LUMA_KEY,             ///< parameter is the luma key value (luma value range to be rendered transparent) - write only parameter, valid only with video substreams \change Added for Blu-ray profile 1.1 support
              SEL_POSITION,             ///< parameter is the video area position - write only parameter, valid only with video substreams \change Added for Blu-ray profile 1.1 support
              SEL_PIDTABLE,             ///< parameter is the PID table for a substream (transport streams only)
              SEL_SECTIONMASK,          ///< parameter is the section mask used for the substream (demux output)
              SEL_TAGTABLE,             ///< parameter is the tag generation information (transport streams only)

              SS_SEL_FIRST_SPECIFIC = 0x10	///< format-specific selectors can be defined from this value up
        };

		/// Selection values for program/transport substreams
        struct STagSelectorType
        {
        	enum
        	{
        		TAG_BY_ID = 0,

				TAG_ANY_VIDEO,
				TAG_FIRST_VIDEO,

				TAG_ANY_AUDIO,
				TAG_FIRST_AUDIO,
        	}
        	method;

        	struct
        	{
        		unsigned id;				///< subpath ID
        		unsigned subId;				///< subpath SubID
				TMediaType mediaType;		///< type of the media from this subpath
        	}
        	id;

        };

        /// Substream parameters for ChangeSubstreamParams() and GetSubstreamParams() methods
        union USSPars
        {
            /// substream selection parameter (format specific)
            union UID
            {
                unsigned int PID;                        ///< MPEG2 Transport Stream Packet ID

                /// Program Stream substream identification info
                struct SPES_ID
                {
                    unsigned int stream_id;             ///< PES packet stream_id
                    unsigned int stream_id_extension;   ///< PES packet stream_id_extension field (optional - format specific)
                }
                PES;
            }
            id;

            /// Stream demux or substream decoder buffer info

            /// The stream demux buffer holds data that has been already sent to the presentation engine but not yet consumed.
            ///
            /// The substream decoder buffer holds data that has been extracted from the incoming stream
            /// but not yet consumed by the substream decoder.
            struct SBufferInfo fullness;

            /// Current media info as reported by the decoder
            struct SMediaFormat mediaInfo;

            /// luma key value - range of luma values that are rendered transparent
            struct SLumaKey
            {
                int firstTransparentValue;
                int lastTransparentValue;
                RMuint64 activationTime;    ///< master stream media time at which the specified values should become effective - if 0, they are applied immediately \change Added 4-24-2007 \status TBI
            }
            lumaKey;

            /// Video area position information, in pixels of the base video substream
            struct SVideoPosition
            {
                TStreamID baseSubstream;    ///< stream which the positioning is relative to
                int xOrigin;
                int yOrigin;
                int xSize;
                int ySize;
                RMuint64 activationTime;    ///< master stream media time at which the specified values should become effective - if 0, they are applied immediately \change Added 4-24-2007 \status TBI
            }
            videoPosition;

            /// PID table for a substream
            struct SSubstreamPIDtable
            {
                int tableSize;                          ///< size of the passed table - it is the number of pid value entries used for this substream. value 0 means "release all the pid filters"
                RMuint16 PID[ MAX_PIDS_PER_TASK ];      ///< pid values. Do not use duplicated values. In that case the ChangeSubstreamParams returns with error
            }
            PIDtable;

            /// substream tag generation information
            struct SSubstreamTagTable
            {
                int tableSize;                          			///< size of the passed table - it is the number of tag selectors used for this substream. Set to 0 to stop all tagging
                STagSelectorType selector[ MAX_PIDS_PER_TASK ];		///< tag selector values for the streams. Do not use duplicated values. In that case the ChangeSubstreamParams returns with error
            }
            tagTable;

            RMuint32 SectionMask;                       ///< section mask applied to a substream (demux output). The section table is updated by SetStreamParams()

        };

        /// Allocates a media stream, i.e. a set of output devices fed by a single data input.

        /// The allocated stream is identified from there on in applicable calls by the TStreamID value
        /// This value is a bit mask that can be used also to test various status flag fields, most importantly the availabilityFlags.
        ///
        /// A theoretical maximum of 32 streams and substreams can be opened at the same time in the presentation engine,
        /// Although specific implementations will most likely have a much lower limit (given by the format specification).
        ///
        /// Examples of streams:
        /// - main audio/video presentation of a multiplexed stream
        /// - either the video or the audio element of a audio/video presentation made of separate elementary streams
        /// - BRD audio or text subpaths
        /// - HDDVD secondary stream
        ///
        /// This command is always synchronous.
        virtual TResultCode AllocStream(int cfgTblIndex,                    ///< index into the format-specific configuration table, which determines the format-specific parameters (what type of codecs, etc.
                                        TStreamID *pSID,                    ///< retrieved ID of the allocated stream
                                        struct SStreamCfgParams *params = 0,///< optional config parameters; if not specified, the default values will be taken from the configuration table
                                        struct SCpsInfoParams *cpsInfo = 0  ///< optional CPS info
                                       );

        /// Selects the specified stream as master stream, which is the stream whose time is considered the media time.

        /// The first allocated stream becomes the master stream.
        /// If the master stream is released, one of the remaining streams will become the master stream.
        /// If more than one streams remain, the master stream should be set explicitly by calling this method.
        virtual TResultCode SetMasterStream(TStreamID s);


        /// Restricts the presentation interval of the specified stream to the specified PTS range

        /// All the media samples outside the presentation interval are discarded, for all the stream's substreams.
        ///
        /// By default the presentation interval is the entire duration of the stream.
        ///
        /// The presentation interval can be set only in PAUSED or PLAYING states,
        /// normally after Start() or Restart() but before feeding data into the presentation engine.
        ///
        /// The presentation interval is automatically reset to the default value upon Stop() (for all the streams) and Restart() (for the restarted stream).
        ///
        ///\note Since media is nevertheless decoded outside the presentation interval, the application should minimize the difference
        /// between the restricted presentation interval and the media span, to avoid noticeable breaks in presentation
        virtual TResultCode SetStreamPresentationInterval(TStreamID s,          ///< target stream
                                                          RMuint64 startPTS,    ///< start of the interval in 90 KHz clock ticks - use 0 to start from the beginning of the media
                                                          RMuint64 endPTS       ///< end of the interval in 90 KHz clock ticks - use -1 to play to the end of the media, same value as startPTS to reset the interval \change 02-26-2007: Implemented open-ended audio play, documented the on-demand reset syntax
                                                         );

        /// Restricts the presentation interval of the specified substream to the specified PTS range \change Added 3-3-2007

        /// All the media samples outside the presentation interval are discarded.
        ///
        /// By default the presentation interval is the entire duration of the stream.
        ///
        /// The presentation interval can be set only in PAUSED or PLAYING states,
        /// normally after Start() or Restart() but before feeding data into the presentation engine.
        ///
        /// The presentation interval is automatically reset to the default value upon Stop() (for all the streams) and Restart() (for the restarted stream).
        ///
        ///\note Since media is nevertheless decoded outside the presentation interval, the application should minimize the difference
        /// between the restricted presentation interval and the media span, to avoid noticeable breaks in presentation
        virtual TResultCode SetSubstreamPresentationInterval(TStreamID s,       ///< target stream
                                                             TStreamID ss,      ///< target substream(s) (multiple susbtream IDs may be ORed together)
                                                             RMuint64 startPTS, ///< start of the interval in 90 KHz clock ticks - use 0 to start from the beginning of the media
                                                             RMuint64 endPTS    ///< end of the interval in 90 KHz clock ticks - use -1 to play to the end of the media, same value as startPTS to reset the interval \change 02-26-2007: Implemented open-ended audio play, documented the on-demand reset syntax
                                                            );

        /// Release a previously allocated stream, together will all the associated resources.
        virtual TResultCode ReleaseStream(TStreamID s);

        /// Instantiates a playback path for the specified substream in the specified stream.

        /// A substream represents a specific media type, like video, audio, subpicture, etc.
        ///
        /// A substream may be processed internally (ex: video, audio) or extracted for processing in middleware (ex: Blu-ray IG, PG, etc).
        /// Data belonging to an externally processed substream will be retrieved through GetSubstreamData() calls.
        /// The client must retrieve the data in time otherwise the demux will block when the buffer associated with the substream fills up.
        /// The type of substream is defined in the configuration table.
        ///
        /// The allocated substream is identified by the TStreamID value returned as #TRESULT_VALUE.
        /// This value is a bit mask that can be used also to test various status flag fields, most importantly the availabilityFlags.
        ///
        /// A theoretical maximum of 32 streams and substreams can be opened at the same time in the presentation engine,
        /// although specific implementations will most likely have a much lower limit (given by the format specification).
        ///
        /// The source and parameters of the media may be changed by ChangeSubstreamParams() calls,
        /// as long as they refer to the same coding format. If a new coding format is used,
        /// the substream must be reallocated with ReallocSubstream()
        ///
        /// The call allocates the required resources except the output device.
        ///
        /// This command is always synchronous.
        virtual TResultCode AllocSubstream(TStreamID s,                                 ///< ID of the parent stream
                                           int cfgTblIndex,                             ///< index into the format-specific configuration table, which determines the processing type (internal/external) and format-specific parameters (what type of codecs, etc.)
                                           TStreamID *pSSID,                            ///< returned ID of the allocated substream
                                           struct SSubstreamCfgParams *params = NULL,   ///< optional configuration parameters; if not specified, the default values will be taken from the configuration table
                                           struct SMediaFormat *contentInfo = NULL      ///< optional content details beyond those available in the config table
                                          );

        #define EDT_DATA    0x10            ///< flag in CPresEng::EEDType values for specifying embedded data extraction. If this flag is specified in the dataType parameter of the AllocEmbeddedSubstream() call, embedded data can be extracted through GetSubstreamData() calls.

        #define EDT_SPU     0x20            ///< flag in CPresEng::EEDType values for specifying embedded data display on the SPU scaler

        #define EDT_FORMAT_MASK     0x0F    ///< mask for extracting the embedded data format from CPresEng::EEDType values

        /// Embedded data type - use #EDT_FORMAT_MASK to extract the format and #EDT_DATA and #EDT_SPU to extract processing mode
        enum EEDType
        {
            EDT_User_Data,                              ///< user data format as meta buffer payload
            EDT_CC_608,                                 ///< Closed Caption data in EIA-608 format sent directly to the (composite/SVideo) video output
            EDT_CC_708,                                 ///< Closed Caption data in EIA-708 format sent directly to the (composite/SVideo) video output
            EDT_CC_608_Data = EDT_CC_608 | EDT_DATA,    ///< Closed Caption data in EIA-608 format passed as meta buffer payload consisting of one or more MRUA #CCFifo_CCEntry_type structures
            EDT_CC_708_Data = EDT_CC_708 | EDT_DATA,    ///< Closed Caption data in EIA-708 format passed as meta buffer payload consisting of one or more MRUA #CCFifo_CCEntry_type structures
            EDT_CC_608_SPU = EDT_CC_608 | EDT_SPU,      ///< Closed Caption data in EIA-608 format decoded internally and displayed (on all video outputs) using the SPU scaler
            EDT_CC_708_SPU = EDT_CC_708 | EDT_SPU,      ///< Closed Caption data in EIA-708 format decoded internally and displayed (on all video outputs) using the SPU scaler
        };

        /// Instantiates an extraction point for data embedded in the specified substream

        /// Most common examples of embedded data is CC data, user data, etc.
        ///
        /// The associated embedded substream ID can be used in and only in the following substream-related methods:
        /// - EnableSubstream() (except for EDT_User_Data substream types)
        /// - GetSubstreamData()
        /// - ReleaseSubstreamDataBuffer()
        /// - ReleaseSubstream()
        ///
        /// This command is always synchronous.
        virtual TResultCode AllocEmbeddedSubstream(TStreamID s,                             ///< ID of the parent stream
                                                   TStreamID ss,                            ///< ID of the embedding substream
                                                   TStreamID *pESSID,                       ///< returned ID of the allocated embedded substream
                                                   enum EEDType dataType                    ///< embedded data type
                                                  );

        /// Reallocates a playback path for the specified substream in the specified stream.

        /// The method allocates a different substream decoder and releases the previous one,
        /// unless the current decoder can handle the new format, in which case the decoder is only
        /// reconfigured as needed.
        ///
        /// The reallocated stream reuses the ID of the previous instance, as well as the output device.
        ///
        /// The substream must be disabled and have no pending commands or embedded substreams associated with it
        /// at the time of this call.
        ///
        /// If the reallocation is done while PLAYING, all the buffers associated with the previous decoder will be discarded.
        /// It is best done synchronized with the position in the stream where the coding format changes
        ///
        /// This command is always synchronous.
        virtual TResultCode ReallocSubstream(TStreamID s,                               ///< ID of the parent stream
                                             TStreamID ss,                              ///< ID of the substream to be reallocated
                                             int cfgTblIndex,                           ///< index into the format-specific configuration table, which determines the format-specific parameters (what type of codecs, etc.)
                                             struct SSubstreamCfgParams *params = NULL, ///< optional configuration parameters; if not specified, the default values will be taken from the configuration table
                                             struct SMediaFormat *contentInfo = NULL    ///< optional content details beyond those available in the config table
                                            );

        /// Enables/disables a previously selected substream in the specified stream.

        /// Enabling a substream allocates the output device and disabling releases it.
        /// An enabled substream is observable by the user, a disabled one is not.
        /// Enabling a disabled substream is a low-impact operation, may be performed in the PLAYING state and
        /// the newly enabled substream is restored quickly and in sync with the rest of the substreams.
        virtual TResultCode EnableSubstream(TStreamID s,
                                            TStreamID ss,
                                            bool onOff);

        /// Retrieves the current parameters for the specified stream \change Added 2-27/2007
        virtual TResultCode GetStreamParams(TStreamID s,
                                            enum ESParSel sel,    ///< parameter selector, determines what parameters are retrieved
                                            union USPars *params  ///< returned parameter values
                                            );

        /// Updates the parameters of the specified stream \change Added 2-27/2007
        virtual TResultCode ChangeStreamParams(TStreamID s, enum ESParSel sel, union USPars *params );



        /// Retrieves the current parameters for the specified substream
        virtual TResultCode GetSubstreamParams(TStreamID s,
                                               TStreamID ss,
                                               enum ESSParSel sel,    ///< parameter selector, determines what parameters are retrieved
                                               union USSPars *params  ///< returned parameter values
                                              );

        /// Updates the parameters of the specified substream in the specified stream \change Changed 6-6-2007 behavior on ID change

        /// In case of substream ID change, any unprocessed data with the old ID is discarded
        /// and only data with the new ID is processed from the time of this call onward.
        virtual TResultCode ChangeSubstreamParams(TStreamID s,
                                                  TStreamID ss,
                                                  enum ESSParSel sel,    ///< parameter selector, determines what parameters are changed
                                                  union USSPars *params  ///< new parameter values
                                                 );

        /// Releases all the resources associated with the specified substream.

        /// The substream must have no pending commands or embedded substreams associated with it
        /// at the time of this call.
        virtual TResultCode ReleaseSubstream(TStreamID s,
                                             TStreamID ss
                                            );

        /// Sets things like playback direction, speed, frame type (I-only, etc) and others.

        /// Currently, reverse direction playback is supported only in key frames only mode and with no audio substream enabled
        /// Currently, speeds other than real time are supported only without any audio substream enabled
        virtual TResultCode SetPlaybackMode(RMuint32 mode,              ///< playback mode, expressed as combination of PRENG_STATUS_PLAYING_DIRECTION_ and PRENG_STATUS_PLAYING_FRAMES flags
                                            RMuint32 newPlaySpeedN = 0, ///< if specified, it becomes the new speed X component
                                            RMuint32 newPlaySpeedM = 0  ///< if specified, it becomes the new speed M component
                                           );

        /// Starts the data flow in all presentation streams

        /// The presentation engine enters the PLAYING state.
        /// Data is accepted; if not enough data is supplied, the processing blocks and resumes automatically when data become available.
        ///
        /// May allocate additional resources, unless when transitioning from PAUSED state.
        /// \note Prebuffering (if requested) is terminated and playback is actually started when any of the following situations occur:
        /// - the internal buffers are filled
        /// - An #INBAND_CMD_END_OF_STREAM inband command is received
        /// - a Start(FALSE) call is received
        virtual TResultCode Start(bool prebuffer = true ///< if TRUE, playback starts only after the internal buffers are full, otherwise it starts immediately
                         );

        /// Sets the initial value for the media time of the specified stream

        /// To be used when a stream may start with samples whose time stamps are not present in the stream
        /// but are known by other means (example: closed GOPs in DVD VOBUs)
        ///
        /// Can be issued only in STOPPED state.
        virtual TResultCode SetStreamInitialMediaTime(TStreamID s, UINT64 initialMediaTime);

        /// Stopping mode definition
        enum EFlushMode
        {
            SM_FlushInput = 1,  ///< input buffers are flushed to avoid reusing old data after restart. \note The application must have released all the data buffers the time of the Stop() or Restrat() call.
            SM_NoFlushInput,    ///< input buffers are preserved, will be reused after the next Start()/Restart()
        };

        /// Pauses the data flow in all presentation streams and flushes the internal buffers; playback can be resumed but there may be delays and data losses.

        /// There should be no data buffer in use at the time of this call (they all must have been released).
        /// All pending commands (class member and/or inband) are discarded.
        /// The presentation engine enters the STOPPED state.
        /// Resources that are strictly related to the PLAYING state can be released, unless reallocating them is a costly or lengthy operation.
        virtual TResultCode Stop(bool lastFrame = true,                 ///< if true, the last frame remains visible on the screen, otherwise it is replaced with a black frame
                                 enum EFlushMode mode = SM_FlushInput   ///< stopping mode
                        );


        /// Pauses the data flow without flushing the internal buffers; playback can be resumed without delay or data loss.

        /// All pending commands are preserved.
        /// The presentation engine enters the PAUSED state.
        /// Data continues to be accepted until the internal buffers are filled.
        /// None of the resources used in the PLAYING state are released.
        virtual TResultCode Pause();

        /// Puts the specified stream in or out of the STILLED state

        /// All pending commands are preserved.
        /// Data is not accepted during STILLED state.
        /// The streaming part of the presentation stream is paused but the interactive part (if any)
        /// remains functional (example: buttons, including animations).
        virtual TResultCode Still(TStreamID s, bool onOff = true);

        /// Cancels the current data and prepares the specified stream for new, unrelated data.

        /// It is equivalent with a Stop()/Start() cycle performed, however, only on the specified stream.
        /// Can be issued only while the presentation engine is in the PLAYING state. It does not change the state.
        /// No data buffer related to the stream should be in use at the time of this call (they all must have been released).
        /// All pending commands sent to the stream or its substreams (class member and/or inband) are discarded.
        ///\note This method is intended for making non-seamless transitions in one stream without disturbing other streams.
        virtual TResultCode Restart(TStreamID s,
                                    bool prebuffer = TRUE,                  ///< if TRUE, playback starts only after the internal buffers are full, otherwise it starts immediately
                                    enum EFlushMode mode = SM_FlushInput    ///< stopping mode
                                    );

        /// Internal reset, used to recover from failures

        /// The engine performs a deep reset of the internal state, including the hardware one, in an attempt to remove failure conditions.
        /// Upon return it enters the external #PRENG_STATUS_STATE_STOPPED state.
        /// All the existing streams and substreams, with their corresponding #TStreamID values remain valid.
        /// As in any other transition to #PRENG_STATUS_STATE_STOPPED state, all the pending asynchronous commands are canceled.
        ///
        /// If the call fails, the recovery may be possible only by driver reload or system reboot.
        virtual TResultCode Reset();

        /// Steps in the specified stream to the next presentation unit in the specified substream.

        /// The direction of the step is given  by the current playback mode.
        /// Only video substream support is mandated, the rest is optional.
        /// Valid only in PAUSED state, and only when all allocated audio substreams in the presentation engine are disabled at the time of this call.
        /// If multiple video and/or graphics are enabled, only the specified one is guaranteed to advance by one frame exactly,
        /// the others may advance by more frames or do not advance at all.
        /// A specific implementation may also fail the command if certain substream other than the mandated ones (video) are enabled.
        virtual TResultCode Step(TStreamID s,
                                 TStreamID ss);

/*
        /// Retrieves a sample of the specified stream and substream and places it in the buffer and format specified in the metaBuffer parameters.

        /// If in PAUSED mode, the sample is guaranteed to be the one currently displayed.
        /// In PLAYING mode, the sample is one of those that will be displayed during or immediately after the call.
        /// The specified data buffer must remain valid during the command execution.
        /// When in PAUSED state, the command is synchronous (completes immediately).
        /// When in PLAYING mode the command is asynchronous (it returns immediately but it completes later).
        TResultCode CaptureSample(TStreamID s,
                                  TStreamID ss,
                                  struct SMetaBuffer* metaBuffer);
*/

        /// Retrieves an empty buffer in which data for the specified presentation stream will be supplied.

        /// The call never blocks, but may fail if a buffer is not currently available.
        /// Once a call fails, it will keep failing until the availability status flag corresponding to the stream is set.
        ///
        /// If successful, this call reinitializes all the buffer's SMetaBuffer fields, except for the SMetaBuffer::dataDescription,
        /// SMetaBuffer::privateData and the corresponding #SMBF_MEDIA_DESCRIPTION and #SMBF_PRIVATE_DATA flags, whose incoming values are preserved.
        ///
        /// Once retrieved, buffers must be either consumed through SendData() or released through ReleaseDataBuffer()
        /// Buffers can be send or released in any order.
        ///
        /// This command is always synchronous.
        virtual TResultCode GetDataBuffer(TStreamID s,
                                          struct SMetaBuffer* metaBuffer);

        /// Creates a clone of a data buffer in which data for the specified presentation stream will be supplied.

        /// The clone will share the same storage with the original but will hold it's own reference to it.
        ///
        /// Cloning allows multiple SendData() calls to be made on the same buffer. The target application is
        /// software demuxing, where an initial buffer is retrieved and filled with multiplexed data, then a clone
        /// is made for each section of the data that must be sent to the decoders through a separate SendData() call.
        ///
        /// If successful, this call copies all the clone's SMetaBuffer fields.
        ///
        /// A clone buffer must be either consumed through SendData() or released through ReleaseDataBuffer().
        /// Buffers can be send or released in any order.
        ///
        /// This command is always synchronous.
        virtual TResultCode CloneDataBuffer(TStreamID s,
                                            struct SMetaBuffer* original,   ///< meta buffer to be cloned, must contained a valid data buffer retrieved by a GetDataBuffer() or a clone
                                            struct SMetaBuffer* clone       ///< meta buffer holding the clone
                                            );

        /// Supplies data in buffers previously retrieved by a GetDataBuffer() or CloneDataBuffer() call.

        /// The call never blocks, but may fail if the data path is full.
        /// For guaranteed success, it should be called only when the availability status flag corresponding to the stream is set.
        ///
        /// In STOPPED mode, the call will fail.
        ///
        /// If successful, this call automatically releases the buffer.
        ///
        /// This command is always synchronous.
        virtual TResultCode SendData(TStreamID s,                     ///< target stream
                                     struct SMetaBuffer* metaBuffer   ///< descriptor of the data buffer
                                    );

        /// Returns a data buffer obtained by a previous GetDataBuffer() or CloneDataBuffer() calls.

        /// Only buffers that are not consumed through SendData() must be explicitly released through this call.
        ///
        /// If successful, this call resets all the buffer's SMetaBuffer::pBuffer and SMetaBuffer::pData fields,
        /// while preserving the rest of them.
        ///
        /// This command is always synchronous.
        virtual TResultCode ReleaseDataBuffer(TStreamID s,
                                              struct SMetaBuffer* metaBuffer);

        /// Retrieves data from the specified substream. \change Added inband command synchronization support spec 3-22-2007

        /// Used for processing substreams in software.
        ///
        /// Only certain substreams are configured for data extraction and thus their data available through this function.
        /// They are configured as such in the format-specific configuration table and are usually used by
        /// the format-specific presentation engine (for example, the Blu-ray engine uses it for PG, IG and TS decoding).
        ///
        /// If an inband command has been issued on the parent stream, this function will partition the data so that
        /// the inband command bitstream position falls on a meta buffer boundary. Once that position is reached, this function
        /// will return #TRESULT_ERROR | #RESULT_OUT_OF_SYNC as long as inband commands are available at that position.
        /// The application must retrieve all the inband commands by calling GetSubstreamInbandCmd() for each command
        /// before it can retrieve new data.
        ///
        /// This command is always synchronous. It never blocks, but may fail if data is not currently available.
        /// For guaranteed success, the call must be made only when the availability status flag corresponding to the substream is set.
        ///
        /// \return
        /// - #TRESULT_ERROR | #RESULT_INVALID if the specified substream is NOT an extraction substream
        /// - #TRESULT_ERROR | #RESULT_BUSY if there is no data available at this time
        /// - #TRESULT_ERROR | #RESULT_OUT_OF_SYNC if there are inband commands at the current bitstream position
        /// - #TRESULT_SUCCESS if data was retrieved successfully
        /// \status Inband command synchronization TBI
        virtual TResultCode GetSubstreamData(TStreamID s,
                                             TStreamID ss,
                                             struct SMetaBuffer* metaBuffer);

        /// Returns a data buffer obtained by a previous GetSubstreamData() call.

        /// The buffers MUST be released in the same order they are retrieved.
        /// This command is always synchronous.
        virtual TResultCode ReleaseSubstreamDataBuffer(TStreamID s,
                                                       TStreamID ss,
                                                       struct SMetaBuffer* metaBuffer);

        /// Inband commands
        enum EInbandCmdID
        {
            INBAND_CMD_ASPECT_RATIO = INBAND_COMMAND_TAG_ASPECT_RATIO,          ///< sets the display aspect ratio to the specified value; used to overwrite the values encoded in the stream; valid target: video substream

            INBAND_CMD_SCALING_MODE = INBAND_COMMAND_TAG_SCALING_MODE,          ///< sets the display scaling mode to the specified value; used to overwrite the values encoded in the stream; valid target: video substream

            INBAND_CMD_TIME_OFFSET = INBAND_COMMAND_TAG_PTS_OFFSET,             ///< the time base of the stream is shifted by the specified amount for all the substreams, regardless of specified targets; valid target: streams

            INBAND_CMD_END_OF_STREAM  = INBAND_COMMAND_TAG_EOS,                 ///< there is no more data following this command; valid target: substreams

            INBAND_CMD_AACS = INBAND_COMMAND_TAG_AACS,                          ///< AACS command

            INBAND_CMD_CUSTOM = INBAND_COMMAND_TAG_USER0,                       ///< custom command, target will only generate the event and follow with the ACTION, no command specific processing; valid target: any stream and substream

            INBAND_CMD_STC_CONTROL,                                             ///< on-the-fly control of the System Time Clock associated with the stream; valid target: streams

            INBAND_CMD_SKIP_START,                                              ///< data after the specified offset (relative to command's position) is removed from stream; used when not all the encryption unit belongs to the playback path; valid target: streams. This tag is currently a mask and should be or'ed with any in band.

            INBAND_CMD_SKIP_END,                                                ///< data after the specified offset (relative to command's position) is included in the stream; used when not all the encryption unit belongs to the playback path; valid target: streams.  This tag is currently a mask and should be or'ed with any in band.
        };

        /// Action to be taken by a target upon execution of an inband command. These actions change only the local state of the target, not the global state of the presentation engine.
        enum EInbandCmdAction
        {
            INBAND_ACTION_STOP = INBAND_COMMAND_ACTION_STOP,        ///< target will stop upon processing the command, will be restarted automatically on the next WaitForStatusChange() call, unless the stream is stopped before that
            INBAND_ACTION_CONTINUE = INBAND_COMMAND_ACTION_CONTINUE ///< target will continue playback after processing the command
        };

        /// STC Synchronization mode, refers to how the system time clock is controlled
        /// (not to be confounded with synchronization between substreams)
        enum ESTCSyncMode
        {
            STC_SyncStreamNever     = EMhwlibTimerSync_None,                ///< STC is never synchronized with timing information present in the stream
            STC_SyncStreamAllways   = EMhwlibTimerSync_PcrUpdateStc,        ///< STC is synchronized every time there is timing information present in the stream
            STC_SyncStreamOnce      = EMhwlibTimerSync_FirstPcrSetStc,      ///< STC is synchronized with the first timing information found in the stream after a Start() or Restart() and then ignores any other other timing information
            STC_SyncValue                                                   ///< STC is loaded with the specified value, and never synchronized with the stream
        };

        /// Parameters for the EInbandCmdID::INBAND_CMD_STC_CONTROL inband command
        struct SSTCCtrlParams
        {
            enum ESTCSyncMode syncMode;     ///< STC synchronization mode
            RMuint64 stcValue;              ///< new STC value in syncMode is ESTCSyncMode::STC_SyncValue
        };


        /// Inband command parameter definition
        union UInbandCmdParam
        {
            /// aspect ratio parameters - see RUA emhwlib_displaytypes.h
            struct SurfaceAspectRatio_type aspectRatio;

            /// scaling mode parameters - see RUA emhwlib_displaytypes.h
            enum EMhwlibScalingMode scalingMode;

            /// offset applied to stream time stamps (for all substreams)
            RMuint64 ptsOffset;

            /// position, relative to the SKIP inband command, where the SKIP starts or ends
            RMuint32 skipOffset;

            /// AACS parameters - see RUA emhwlib_event.h
            struct aacs_params aacs;

            /// Parameters for the EInbandCmdID::INBAND_CMD_STC_CONTROL inband command
            struct SSTCCtrlParams stcParams;
        };

        /// Inserts an inband command into the data flow.

        /// Inband commands are used in order to synchronize actions with stream processing.
        /// They are delivered to the targets through the data stream (conceptually, at least) and this are
        /// processed after all the data that has been send before their issuance and before any data that has
        /// been send after them
        ///
        /// Most commands are processed by the decoders themselves, but the #INBAND_CMD_CUSTOM
        /// command is used only to notify the client module when the specified point in the stream has reached the target decoder
        /// However, all commands notify the client of their execution, so the client can always add its action
        /// to the one taken by the decoders.
        ///
        /// Commands that have the #INBAND_ACTION_STOP action code associated with them
        /// will stop the target until the next WaitForStatusChange() when they will be restarted automatically
        ///
        /// This command is always asynchronous. However, the async cmd ID is not returned in the result code, as usual.
        /// Instead, one async ID per target are returned in a table supplied by the caller (table must be large enough).
        /// IDs are placed in the table in the same order the targets are placed in the supplied targetTab table
        ///
        /// The async ID for one target appears in the completed/failedCmds fields of the status as soon as the command
        /// has been processed by target.
        ///
        /// Note: #INBAND_CMD_ASPECT_RATIO, #INBAND_CMD_SCALING_MODE and #INBAND_CMD_AACS inband commands
        /// do not provide completion notification.
        /// Consequently, they will return a TAsyncCmdID value of zero.
        virtual TResultCode SendInbandCmd(TStreamID s,             ///< target stream ID
                                          int targetCnt,                   ///< number of command targets listed in targetTab
                                          TStreamID *targetTab,            ///< table of command targets (stream and substream IDs
                                          enum EInbandCmdID cmd,           ///< command ID
                                          enum EInbandCmdAction action,    ///< action to be taken by decoders upon command execution
                                          union UInbandCmdParam *param,    ///< command parameter
                                          TAsyncCmdID *asyncCmdIDTab       ///< table of returned async cmd IDs, one for each target in targetTab
                                         );

        /// Retrieves an inband command from the specified substream. \change Added 3-22-2007, implemented 4-12-2007

        /// Used for synchronizing actions with the bitstream when processing substreams in software.
        ///
        /// Can be used only with extraction substreams.
        ///
        /// Inband commands can be retrieved only at their corresponding bitstream position.
        /// Multiple inband commands can be associated with one bitstream position.
        /// Each GetSubstreamInbandCmd() call retrieves one inband command and removes it from the queue.
        /// GetSubstreamData() calls will fail with #TRESULT_ERROR | #RESULT_OUT_OF_SYNC as long as there are inband commands at the current bitstream position.
        ///
        /// This command is always synchronous.
        ///
        /// \return
        /// - #TRESULT_ERROR | #RESULT_INVALID if the specified substream is NOT an extraction substream
        /// - #TRESULT_ERROR | #RESULT_NOT_AVAILABLE if there are no inband commands available at the current bitstream position
        /// - #TRESULT_SUCCESS if an inband command was retrieved successfully
        virtual TResultCode GetSubstreamInbandCmd(TStreamID s,
                                                  TStreamID ss,
                                                  enum EInbandCmdID *cmd,           ///< returned command ID
                                                  enum EInbandCmdAction *action,    ///< returned action to be taken by decoders upon command execution
                                                  union UInbandCmdParam *param      ///< returned command parameter
                                                 );

        /// Requests a notification when the presentation time becomes equal with the specified value

        /// This command is always asynchronous.
        /// The completion of the command denotes that the specified presentation time has arrived (delay subject to user mode limitations).
        virtual TResultCode WakeUpOnPresentationTime(UINT64 streamTime, ///< target presentation time
                                                     TStreamID s = 0    ///< optional target stream, default is the master stream
                                                    );

        /// Requests a notification on the next VSync (delay subject to user mode limitations).

        /// If the bottom field vsync is requested during a non-interlaced playback, the call will fail
        ///
        /// This command is always asynchronous.
        ///
        /// The completion of the command denotes that the VSync has occurred.
        virtual TResultCode WakeUpOnVSync(bool bottomField = FALSE    ///< if TRUE, the vsync of the bottom field is selected, otherwise that of the top field or frame
                                 );

        /// Cancels a pending command.

        /// Normally only WakeUpOnXXX commands can be canceled.
        /// This command is always synchronous.
        virtual TResultCode CancelPendingCmd(TAsyncCmdID cmdID);

        /// Wakes up the thread that is or will be waiting inside the WaitForStatusChange().

        /// The reason parameter must have one single bit set, which will be copied into the m_pStatus::externalEvents field.
        /// Upon returning from WaitForStatusChage(), m_pStatus::externalEvents will allow identification
        /// of all the external events that have occurred since the last time WaitForStatusChage() returned.
        ///
        /// The command must be called on a different thread than the one calling
        /// the rest of the presentation engine methods.
        ///
        /// This command is always synchronous.
        virtual void WakeUpNow(RMuint32 reason);

        /// Waits for any status changes (due to internal events).

        /// This command is always synchronous, although the duration of the execution
        /// is not subject to the regular limit, only to the occurrence of events.
        ///
        /// <B>Implementation guidelines</B><BR>
        /// When called, it may perform internal processing before entering the wait state.
        /// After waking up, it may process the internal events and return only if status info events are generated, otherwise go back to wait.
        virtual void WaitForStatusChange();

        /// Retrieves the result code of a command that has been pending and has just completed (or failed).

        /// This command is always synchronous.
        /// The command should have completed during the last WaitForStatusChange() call, otherwise the completion flag may refer to a different command.
        TResultCode GetCmdResult(TAsyncCmdID cmdID,         ///< async command ID that has been returned when the command has been issued. The caller must ensure that the command mask is still valid, by calling this functin immediately after completion and before the command mask is recycled
                                 TResultCode *pResult       ///< result of the completed command
                                );

        /// Retrieves the ID of the playback session serviced by the engine, as specified in the SessionParams parameter of the CPresEng() constructor
        int GetSessionID() { return sessionParams.sessionID; }

        /// Allow allocation in non-system memory
        void *operator new(size_t bytes);

        /// Free non-system memory, if applicable
        void operator delete(void *ptr, size_t bytes);

        /// Virtual destructor, ensuring that it is also called when the derived class is destroyed.
        virtual ~CPresEng();


#ifdef USE_ERROR_DETECTION_AND_RECOVERY
        virtual TResultCode ReinitHardware(void);
#endif




#if !defined(__DOC__) && !defined(CPP_EDIT_MODE)
        // include private definitions from separate file in order to exclude them from the Doxygen-generated documentation
        #include "src/_CPresEng.h"
        #include "src/CPresEngConfig.h"
        #include "src/CPresEngVideo.h"
        #include "src/CPresEngSPU.h"
        #include "src/CPresEngSCC.h"
        #include "src/CPresEngCC.h"
        #include "src/CPresEngDemux.h"
#ifdef USE_ERROR_DETECTION_AND_RECOVERY
        #include "src/CPresEngRecv.h"
#endif

#endif // __DOC__

protected:
        /// Protected constructor, ensuring that only derived classes can be actually instantiated.
        CPresEng(struct SGlobals *pGlobals,             ///< system-wide values
                 void *pConfigTable,                    ///< pointer to the format-specific configuration table supplied by the derived class
                 struct SPrEngStatus *pStatus,          ///< pointer to the format-specific status info structure supplied by the derived class
                 struct SSessionParams *pSession = NULL ///< session parameters
                );

        /// Pointer to the status info structure.

        /// The structure is actually provided by a derived class
        /// so that it can be customized with format-specific fields following the standard ones.
        struct SPrEngStatus *pStatus;


        /// Facility to allow derived classes to wait asynchronously on MRUA events

        /// The derived class must issue the MRUA command whose confirmation is the event waited upon by this method.
        ///
        /// This command is always synchronous. All the normal rules on asynchronous commands apply.
        TResultCode WakeUpOnEvent(RMuint32 ModuleID, RMuint32 RuaEventMask);

        /// Facility to allow derived classes to force an upper limit to the time it takes WaitForStatusChange() to return (with or without a status change
        virtual RMuint32 GetWaitForStatusChangeTimeout() {return 1000000; }

    };// END CLASS DEFINITION CPresEng

} // namespace DCC-HD

#ifdef __DOC__
///\defgroup RUAIBCDEFS Substream Parameters
/// RUA definitions related to inabnd commands (MRUA_src/emhwlib/include/emhwlib_displaytypes.h), included here only for reference
///
/// Please refer to RUA documenatation and Sigma RUA support team for additional information
///@{

struct EMhwlibAspectRatio {
    RMuint32 X;
    RMuint32 Y;
};

enum EMhwlibAspectRatioType {
    EMhwlibAspectRatio_Picture = 1, // use default picture aspect ratio and disable inband/outband
    EMhwlibAspectRatio_Pixel,       // pixel aspect ratio of the surface should be provided
    EMhwlibAspectRatio_Display      // display aspect ratio of the surface should be provided
};

struct SurfaceAspectRatio_type {
    // picture aspect ratio (default), pixel aspect ratio or display aspect ratio
    enum EMhwlibAspectRatioType type;
    // pixel or display aspect ratio of the surface, value ignored when picture aspect ratio is selected as type
    struct EMhwlibAspectRatio ar;
};
enum EMhwlibScalingMode {
    EMhwlibScalingMode_PanScan = 1,
    EMhwlibScalingMode_LetterBox
};

///@}
#endif //__DOC__

#endif //_DCCHD_H_
// vim:set shiftwidth=4 tabstop=4 expandtab:

/**
  $Log: dcchd.h,v $
  Revision 1.298.8.2  2010-02-11 03:24:04  smanciulea
  BugId: none

  - used the EMHWLIB version numbers in order to enable/disable code at compile time

  Revision 1.298.8.1  2009-12-22 14:22:23  anagy
  BugId:6854
  Ported ALSA PCMX implementation

  Revision 1.298  2009-09-03 22:08:00  jenniferZ
  BugId:None
  Add SMBF_TAG_SYSTEM_INFO

  Revision 1.297  2009-09-03 03:30:49  sorin
  BugId: none
  Added SMBF_TAG_SYSTEM_INFO meta buffer flag for identifying system info data in a Transport stream

  Revision 1.296  2009-07-10 22:13:57  sorin
  BugId: none
  Better style

  Revision 1.295  2009-04-23 00:37:08  anagy
  BugId: none
  ported substream extraction processing from branch

  Revision 1.294  2009-04-11 03:28:36  sorin
  BugId: none
  Doc

  Revision 1.293  2009-03-31 19:29:21  sorin
  BugId: none
  Gave the unit owner ID field its own meta buffer flag to avoid any ambiguities

  Revision 1.292  2009-03-20 00:21:51  sorin
  BugId: none
  Doc

  Revision 1.291  2009-03-19 01:56:28  sorin
  BugId: none
  Added session ID reporting method in order to allow presentation engine selection based on known session ID value that has been used at instantiation

  Revision 1.290  2009-02-23 17:07:11  sorin
  BugId: none
  Added tagging support in the presentnation engine API

  Revision 1.289  2008-12-19 20:14:41  pascal
  BugId: none
  This is Arpad's patch. It allows us to keep track of the buffer pool handle
  for DMA buffers. It's useful in the following situations:
  - a DMA buffer from a video stream is cloned
  - the cloned buffer is not pushed to the video decoder but to the audio
  decoder

  Revision 1.288  2008-12-15 23:49:56  sorin
  BugId: none
  Doc typo

  Revision 1.287  2008-12-10 02:45:45  sorin
  BugId: none
  Cleaned up meta buffer flags handling when getting, sending, cloning and releasing buffers

  Revision 1.286  2008-12-02 19:55:06  sorin
  BugId: none
  Typos

  Revision 1.285  2008-12-02 01:45:23  sorin
  BugId: none
  Added 1 KHz Windows media support

  Revision 1.284  2008-11-26 00:37:33  sorin
  BugId: none
  Typo

  Revision 1.283  2008-11-20 16:56:11  sorin
  BugId: none
  Merged the Fast Load changes (asynchronous AACS and BD+)

  Revision 1.282  2008-10-31 02:45:53  sorin
  BugId: CT-2426
  Allow one macroblock row worth of image errors for BD and DVD/VR

  Revision 1.281  2008-10-16 00:03:24  sorin
  BugId: none
  Removed WSS support as unsure of its actual functionality

  Revision 1.280  2008-10-15 20:10:01  sorin
  BugId: none
  Doc

  Revision 1.279  2008-10-15 19:29:52  sorin
  BugId: none
  Added WSS type of Embedded Data
  Typos

  Revision 1.278  2008-10-15 14:37:07  sorin
  BugId: none
  Redefined the custom value boundary so that it can be used for either mutually exclusive or additive values

  Revision 1.277  2008-10-07 23:24:26  sorin
  BugId: none
  Doc

  Revision 1.276  2008-10-07 04:05:09  sorin
  BugId: none
  Added support for global volume

  Revision 1.275  2008-05-21 12:52:36  sotescu
  BugId: none
  Added some JPEG session params.

  Revision 1.274  2008-03-25 03:10:25  sorin
  BugId: none
  Renamed and made public max PCMX channel definition

  Revision 1.273  2008-01-14 12:59:46  anagy
  BugId: none
  corrected bad selection flag

  Revision 1.272  2007-12-21 18:56:02  smanciulea
  BugId: none
  - replaced the defines CDROM_MOUNT_POINT and CDROM_DEVICE_NAME with global variables which are initialized from environment variables.

  Revision 1.271  2007-12-11 16:07:14  anagy
  BugId: 3099
  Secondary Audio Implementation

  Revision 1.267.2.2  2007-11-30 11:02:34  anagy
  BugId: none
  fixes:
  - shadow substream is handled only at SendData (buffer acquire, etc.)
  - fixes for PCMX shadow substream

  Revision 1.270  2007-11-29 14:30:52  sorin
  BugId: none
  Added 2nd preng private meta buffer flags for new audio code

  Revision 1.269  2007-11-13 23:57:38  sorin
  BugId: none
  Doc

  Revision 1.268  2007/11/13 17:25:37  anagy
  BugId:none
  Flag in pStatus->statusFlags for prebuffering state

  Revision 1.267  2007/11/07 11:04:07  anagy
  BugId:none
  Ported Generic PID and Section handling code

  Revision 1.266  2007/11/05 23:04:12  sorin
  BugId: none
  Converted boolean private status change to quantitative WaitForStatusChange timeout for more precise CPU load control

  Revision 1.265  2007/11/05 22:33:53  sorin
  BugId: none
  Added support for status changes that are private to the derived classes (example: missed PCMX buffer)

  Revision 1.264  2007/10/18 04:01:15  sorinp
  Optimized PCMX by writing the chunk headers in place rather than reaequencing the data from local intermediate copy

  Revision 1.263  2007/10/04 16:14:09  sotescu
  BUGCT: 3094
  Finished the support for JPEG decoder memory size computation and allocation.

  Revision 1.262  2007/08/09 14:49:07  sotescu
  BUGCT: 3664
  Integrated changes that expose the global allocator/deallocator DirectFB callbacks.

  Revision 1.261  2007/07/20 19:41:44  mignaszewski
  bug-ct: 3379
  Changed documentation regarding AACS inband commands

  Revision 1.260  2007/06/22 08:04:10  smanciulea
  BUGCT: NONE - revert again, the previous checkin was wrong

  Revision 1.258  2007/06/08 15:03:26  anagy
  BUGCT#3353 fix: applied the patches, made fixes

  Revision 1.257  2007/06/07 08:09:35  sorinp
  CT- 3351 -  discard the old data when changing the substream ID

  Revision 1.256  2007/06/07 07:50:40  sorinp
  BUGCT:3349 - Remove pres eng state restrictions on stream/substream lifecycle events

  Revision 1.255  2007/06/06 16:17:13  smanciulea
  - replaced all occurences of wchar_t with char and done all related changes for string manipulation
  - DCCHD_MAX_PATH changed from 512 to 2048

  Revision 1.254  2007/05/09 14:51:29  smanciulea
  renamed EStopMode to EFlushMode due to the newly introduced EStopMode enum for the stop mode parameter of the Stop command

  Revision 1.253  2007/04/26 10:00:27  anagy
  fix

  Revision 1.252  2007/04/24 23:14:37  sorinp
  Moved the LPCM downmixing parameters from the generic to the BD-specific pres eng
  Doc updates

  Revision 1.251  2007/04/24 20:49:00  sorinp
  BUGCT:3097, 3098 Added activation time for luma and PiP position parameters

  Revision 1.250  2007/04/24 19:43:08  sorinp
  BUGCT:3092, 3093 Added memory releasor, removed max native mem size

  Revision 1.249  2007/04/13 20:19:35  sorinp
  doc

  Revision 1.248  2007/04/13 20:18:21  sorinp
  removed redundant status tag

  Revision 1.247  2007/04/13 16:02:21  anagy
  status updated

  Revision 1.246  2007/04/13 05:52:05  sorinp
  Added support for external memory allocation per presentation engine session

  Revision 1.245  2007/03/27 20:31:51  sorinp
  spelling

  Revision 1.244  2007/03/27 16:02:58  sorinp
  doc

  Revision 1.243  2007/03/23 00:24:31  sorinp
  Added GetSubstreamInbandCmd method to allow retieving inband commands from extraction substreams

  Revision 1.242  2007/03/22 23:05:39  sorinp
  doc

  Revision 1.241  2007/03/22 09:29:53  anagy
  ChangeStreamParams can change the PCR Discontinuity Threshold

  Revision 1.240  2007/03/20 00:15:12  sbeysserie
  Add end of line.

  Revision 1.239  2007/03/19 16:31:09  sorinp
  Moved log at the end of the file

  Revision 1.238  2007/03/16 09:38:46  sorinp
  Added support for profile 1.1 in API

  Revision 1.237  2007/03/05 18:12:36  sorinp
  doc update

  Revision 1.236  2007/03/05 14:30:21  anagy
  SetSubstreamPresentationInterval() implemented

  Revision 1.235  2007/03/04 01:47:05  sorinp
  Added support for individual substream presenttaion interval setting

  Revision 1.234  2007/02/28 04:07:35  sorinp
  doc

  Revision 1.233  2007/02/27 21:07:19  sorinp
  doc, added time discontinuity flag

  Revision 1.232  2007/02/27 12:37:59  anagy
  ChangeStreamParams - change PCR PID

  Revision 1.231  2007/02/27 05:14:46  sorinp
  BUGCT:2502 Implemented open ended interval

  Revision 1.230  2007/02/14 04:21:30  sorinp
  Doc upgrade

  Revision 1.229  2007/02/13 02:42:58  sorinp
  BUGCT:2272 Added status field and flag to identify STALLED substream state (lack of output data due to starvation), to be used to expose the PCMX data starvation

  Revision 1.228  2006/12/13 12:02:57  anagy
  - UPDATE -
  updated PresEng. related modifications from Version.1 branch

  Revision 1.227.4.1  2006/12/12 17:32:44  sorinp
  Removed change doc tags in prepearation for the official 1.0.0 release

  Revision 1.227  2006/11/10 07:22:50  sorinp
  Added Reset and documented the error support in the API

  Revision 1.226  2006/10/26 21:34:26  anagy
  Moved SPU functions in separate file

  Revision 1.225  2006/10/26 20:28:25  anagy
  added ReinitHardware function prototype

  Revision 1.224  2006/10/23 23:43:46  anagy
  Added error detection and recovery (under construction - can be activated by defining USE_ERROR_DETECTION_AND_RECOVERY)

  Revision 1.223  2006/10/19 22:35:50  sorinp
  doc

  Revision 1.222  2006/10/18 20:14:47  anagy
  Added stopping mode support in Start and Restrat to allow the application to keep the data buffers accress non-seamless connections

  Revision 1.221  2006/10/18 01:06:18  sorinp
  documented prebuffering termination

  Revision 1.220  2006/10/05 21:16:57  sorinp
  Added error flag and field

  Revision 1.219  2006/10/04 01:45:22  sorinp
  Added the static SetDefaultDRMRules method to allow the CPS provider to change the DRM rules before and after the presentation (at that time there is no pres eng instance available)

  Revision 1.218  2006/10/03 03:47:11  sorinp
  doc

  Revision 1.217  2006/10/03 03:06:37  anagy
  Display segment counter and flag

  Revision 1.216  2006/09/29 01:03:33  sorinp
  Added SetStreamInitialMediaTime()

  Revision 1.215  2006/09/21 09:52:55  smanciulea
  - fixed compilation after introduction of CPresEng.[h,cpp]

  Revision 1.214  2006/09/16 05:00:52  sorinp
  Updated doc (status field)

  Revision 1.213  2006/09/02 23:13:17  sorinp
  doc clarifications

  Revision 1.212  2006/08/31 04:41:33  sorinp
  Updated doc change list to B.5.0

  Revision 1.211  2006/08/24 22:01:41  sorinp
  Adde support for configurable demux input buffer size and buffer pool buffer size fro the Blu-ray main path case

  Revision 1.210  2006/08/08 01:40:25  sorinp
  doc syntax

  Revision 1.209  2006/08/08 01:10:44  sorinp
  Updated doc to B.4.0 level

  Revision 1.208  2006/08/07 02:05:03  sorinp
  Added field to identify the substreams for which media info is available

  Revision 1.207  2006/08/06 05:09:59  sorinp
  doc

  Revision 1.206  2006/08/06 05:08:07  sorinp
  Re-defined the presentation interval API - made it a stream rather than substream concept

  Revision 1.205  2006/08/06 04:25:32  sorinp
  Added presentation interval restriction API

  Revision 1.204  2006/08/06 01:29:06  sorinp
  Added media info substream read-only parameter

  Revision 1.203  2006/08/02 15:01:06  sotescu
  New includes + better handling of non-C++ files.

  Revision 1.202  2006/08/02 12:56:34  sotescu
  Better editor support (includes namespace/class header if CPP_EDIT_MODE is defined).

  Revision 1.201  2006/08/02 05:30:31  sorinp
  Added software CC decoder support

  Revision 1.200  2006/07/29 01:38:57  sorinp
  Removed doc change notes older than B.2.0

  Revision 1.199  2006/07/28 23:50:47  sorinp
  syntax

  Revision 1.198  2006/07/28 23:48:39  sorinp
  syntax

  Revision 1.197  2006/07/28 17:58:19  sorinp
  Added new method: Restart()

  Revision 1.196  2006/07/25 23:10:55  anagy
  mediatime invalidity flag

  Revision 1.195  2006/07/11 19:24:31  sorinp
  Removed the direction parameter in Step, will use the playback mode for this.

  Revision 1.194  2006/07/10 20:31:33  dnguyen
  made most of CPresEng's public member functions virtual

  Revision 1.193  2006/06/28 20:52:02  anagy
  Step Back
  ( TBI )

  Revision 1.192  2006/06/27 19:33:19  sorinp
  Upgraded doc to B.2.0 level

  Revision 1.191  2006/06/24 03:55:06  anagy
  Signal video decoder error to directfb

  Revision 1.190  2006/06/15 05:46:56  sorinp
  doxygen fix

  Revision 1.189  2006/06/14 23:40:09  sorinp
  Replaced new DCC-HD structure with old MRUA one for CC data extraction

  Revision 1.188  2006/06/14 05:24:31  sorinp
  Added GetStreamTime() method for use in slide shows, when media time resolution is lower than control resolution.

  Revision 1.187  2006/06/03 03:54:58  sorinp
  Enabled pre-configuration

  Revision 1.186  2006/06/01 06:42:12  sorinp
  Added SetDRMRules methods

  Revision 1.185  2006/06/01 05:57:13  sorinp
  spellings

  Revision 1.184  2006/05/26 02:22:53  jlerouge
  Move SKIP_START/SKIP_END

  Revision 1.183  2006/05/25 11:31:59  sotescu
  Modified prototype for TFrameDisplayCallback.

  Revision 1.182  2006/05/25 03:35:36  sorinp
  Removed all the old config-related elements. Code does not compile !!!

  Revision 1.181  2006/05/24 18:39:06  anagy
  include CPresEngVideo.h

  Revision 1.180  2006/05/24 00:49:54  sorinp
  spelling error

  Revision 1.179  2006/05/16 22:20:40  sorinp
  Updates for level B.1.0

  Revision 1.178  2006/05/15 01:52:38  sorinp
  made config and callbacks separate methods

  Revision 1.177  2006/05/15 01:33:26  sorinp
  made config and callbacks separate methods

  Revision 1.176  2006/05/15 01:18:14  sorinp
  new configurationscheme related changes

  Revision 1.175  2006/05/14 19:27:59  sorinp
  Updated Get/SetConfiguration syntax

  Revision 1.174  2006/05/14 02:18:44  sorinp
  Added UpdateSettings callback

  Revision 1.173  2006/05/13 20:48:04  sorinp
  Added content info in RellocSubstream params

  Revision 1.172  2006/05/13 17:44:29  sorinp
  Moved content info in AllocSubstream parameters from field in 'params' to separate parameter, to avoid linking content with buffering

  Revision 1.171  2006/05/12 21:33:15  sorinp
  Added content info in AllocSubstream params

  Revision 1.170  2006/05/11 06:32:45  sorinp
  Changed SubstreamConfigParams and propagated changes
  Implemented support for A/V/SPU/Extraction custom substream params

  Revision 1.169  2006/05/11 03:13:52  sorinp
  moved buffer fullness reporting in GetSubstreamParams and implemented it

  Revision 1.168  2006/05/10 18:57:31  mfedoreanu
  Demux flush, removed overriden stop and start, not used anymore. Added notification for demux output flush

  Revision 1.167  2006/05/10 05:38:52  sorinp
  Removed old memory management references
  Use MRUA mem (usually in DRAM1) for DCC-HD object data in order to leave as much space as possible to Linux

  Revision 1.166  2006/05/05 23:03:11  mfedoreanu
  made start and stop virtual

  Revision 1.165  2006/05/05 00:54:09  anagy
  added CPresEngConfig.h

  Revision 1.164  2006/04/27 07:30:36  sorinp
  Updated A/V config spec, new memory allocation (static) spec

  Revision 1.163  2006/04/25 05:10:26  sorinp
  doc upgrades

  Revision 1.162  2006/04/25 04:37:24  sorinp
  doc upgrades

  Revision 1.161  2006/04/18 05:45:59  sorinp
  Updated CPS Provider support and completed integration with framework
  Not tested yet

  Revision 1.160  2006/04/15 02:52:44  sotescu
  Replaced RUAMallocs with C++ allocators (dram_*).

  Revision 1.159  2006/04/11 04:18:52  sorinp
  Changed AllocEmbeddedSubstream to support CC and user data directly.
  Verified and clarified audio output channel specification

  Revision 1.158  2006/03/16 18:25:57  sorinp
  made CPSInfo public structure

  Revision 1.157  2006/03/16 02:04:39  jlerouge
  Add AACS and skip start/end IbC tag.

  Revision 1.156  2006/03/15 03:49:19  sorinp
  Added CPS support

  Revision 1.155  2006/03/09 18:34:28  anagy
  status updated

  Revision 1.154  2006/03/04 06:14:07  sorinp
  Moved frame callback fields into more general session parameters structure and handling

  Revision 1.153  2006/03/04 00:50:51  sorinp
  Added AACS support spec

  Revision 1.152  2006/03/03 17:11:49  anagy
  Erased INBAND_CMD_LAST_BUFFER
  use Still() instead

  Revision 1.151  2006/03/02 15:35:09  anagy
  LASTBUFFER inband tag for buffer starwing

  Revision 1.150  2006/03/01 13:01:37  anagy
  status updated

  Revision 1.149  2006/02/24 06:43:41  sorinp
  doc

  Revision 1.148  2006/02/24 06:39:49  sorinp
  Added event registration facility

  Revision 1.147  2006/02/23 17:09:06  anagy
  Changed status

  Revision 1.146  2006/02/21 16:48:25  sotescu
  Modified PresEng SetConfiguration parameters to support frame notification callbacks.

  Revision 1.145  2006/02/17 20:38:54  sorinp
  removed the /change tags to start clean for the enxt release

  Revision 1.144  2006/02/17 04:49:48  sorinp
  Doc nicetities

  Revision 1.143  2006/02/15 17:54:54  sorinp
  doc updates

  Revision 1.142  2006/02/15 16:51:04  sorinp
  Added protected virtual playback control method to retrieve teh commend code from the format-specific command structure, in order to allow the framework to execute generic commands

  Revision 1.141  2006/02/03 19:52:05  sorinp
  Added Still() and buffer fullness reporting support

  Revision 1.140  2006/02/03 06:14:47  sorinp
  Added Still() and buffer fullness reporting support

  Revision 1.139  2006/02/01 23:46:34  sorinp
  Marked changes in last release as past changes

  Revision 1.138  2006/02/01 04:59:33  sorinp
  Updated doc, removed CaptureSample since the functionality is available at DFB level

  Revision 1.137  2006/01/30 09:00:57  sorinp
  Added configuration and adjustment definitions

  Revision 1.136  2006/01/27 19:21:56  sorinp
  Clarified depth of WakeUpPTS queue

  Revision 1.135  2006/01/25 01:11:27  sorinp
  doc and releaserelated changes

  Revision 1.134  2006/01/20 17:51:47  smanciulea
  from newDemux branch

  Revision 1.123.2.6  2006/01/20 13:13:47  anagy
  updated to head

  Revision 1.123.2.5  2006/01/16 11:38:40  anagy
  updated to head

  Revision 1.133  2006/01/20 01:25:28  sorinp
  avoid private includes in doxygen compilations

  Revision 1.132  2006/01/17 04:04:58  sorinp
  Clarified backward play requirements and behavior

  Revision 1.131  2006/01/16 21:49:03  sorinp
  docs

  Revision 1.130  2006/01/16 20:16:01  sorinp
  removed unnecessary virtual qualifications

  Revision 1.129  2006/01/12 05:02:31  sorinp
  typo

  Revision 1.128  2006/01/10 23:31:00  sorinp
  Added support for embedded data extraction (ex: CC)

  Revision 1.127  2005/12/30 07:08:19  sorinp
  fixed config info handling. Still incorrect though: config info should be initialized only in derived classes, the generic pres engine should only use it.

  Revision 1.126  2005/12/30 06:30:42  sorinp
  fixed config and status info sharing between the generic pres engine and the format-specific ones: the later provide the actual structure, whle the former only a pointer to it.

  Revision 1.125  2005/12/20 08:25:48  sorinp
  Added codec and hardware configuration support in SGlobals

  Revision 1.124  2005/12/19 20:15:16  bsimon
  use mStatus shared by BRD pres. eng. and generic pres. eng.

  Revision 1.123  2005/12/07 09:14:11  mfedoreanu
  IG/PG SOFTWARE DEMUX

  Revision 1.122  2005/11/29 05:03:40  sorinp
  Added EOS, time and data discontinuity flags for the meta buffer

  Revision 1.121  2005/11/28 23:09:52  sorinp
  Added lastFrame flag in Stop

  Revision 1.120  2005/11/22 18:13:01  anagy
  bug correcting

  Revision 1.119  2005/11/10 09:01:43  sorinp
  Hooked up the thread-based bitstream decoder for BRD IG/PG/TS

  Revision 1.118  2005/11/04 15:19:51  sorinp
  moved to dcchd.h, renamed and used consistently the DCC_MAX_PATH define (prevous MAX_PATH)

  Revision 1.117  2005/11/01 20:07:56  sorinp
  doc update

  Revision 1.116  2005/11/01 19:56:34  sorinp
  fixes

  Revision 1.115  2005/11/01 18:54:17  sorinp
  updated inband command doc

  Revision 1.114  2005/11/01 03:11:51  sorinp
  Added PES specific stream selection support

  Revision 1.113  2005/10/27 19:03:29  sorinp
  collapsed allocation for both internally and externally processed substreams

  Revision 1.112  2005/10/27 01:02:30  dnguyen
  added 16-bit integer types

  Revision 1.111  2005/10/20 18:22:59  sorinp
  Moved test-specific code from conditional-compilation blocks in regular files into test-specific class in test code.

  Revision 1.110  2005/10/19 00:15:17  sorinp
  Clarified doc

  Revision 1.109  2005/10/17 20:45:35  sorinp
  Imposed requirement to release all the pending data buffers BEFORE the pres engine Stop command

  Revision 1.108  2005/10/13 03:07:38  sorinp
  Fixed includes.

  Revision 1.107  2005/10/07 19:41:53  smanciulea
  ~CPresEng(); must be public

  Revision 1.106  2005/10/07 19:02:11  sorinp
  release  preparations

  Revision 1.105  2005/10/07 12:08:50  anagy
  remove protected for CPresEng constructor
  - preseng. test application doesn't work otherwise

  Revision 1.104  2005/10/05 18:43:29  sorinp
  Mostly doc upgrades

  Revision 1.103  2005/10/05 17:02:35  anagy
  added buffercount to Substream config params

  Revision 1.102  2005/10/05 08:15:31  anagy
  corrections

  Revision 1.101  2005/10/05 01:25:00  sorinp
  Moved RUA doc in globals.h

  Revision 1.100  2005/10/05 01:18:36  sorinp
  Removed high-level configuration stubs, will use low-level parameter setting

  Revision 1.99  2005/10/05 01:03:26  sorinp
  Removed RUA ouput parameter in AllocSubstream

  Revision 1.98  2005/09/30 11:12:19  sorinp
  fix

  Revision 1.97  2005/09/30 11:08:26  sorinp
  protected against douple declaration

  Revision 1.96  2005/09/30 10:13:54  sorinp
  Made globals definition a separate file

  Revision 1.95  2005/09/29 15:10:32  sotescu
  no message

  Revision 1.94  2005/09/29 13:19:07  sotescu
  no message

  Revision 1.93  2005/09/28 18:19:39  anagy
  modified USSPars

  Revision 1.92  2005/09/28 17:10:51  sotescu
  no message

  Revision 1.91  2005/09/27 13:38:50  sorinp
  Updated inband command method and notification scheme to allow for arbitrary number of commands with identical targets

  Revision 1.90  2005/09/27 11:23:05  sorinp
  Added decoder params set/get, STC control inband command, master stream concept, mediaTime status field and reqorked the Pause and Start methods

  Revision 1.89  2005/09/27 08:46:09  sorinp
  fixed syntax error

  Revision 1.88  2005/09/27 08:32:44  sorinp
  Added decoder parameters support

  Revision 1.87  2005/09/26 06:47:11  sorinp
  finalized linear and blu-ray control and media definition
  placed public media and control definitions in separate (and new) files

  Revision 1.86  2005/09/21 16:45:30  anagy
  minor adjustments

  Revision 1.85  2005/09/21 15:42:38  sorinp
  doc updates
  fixed function header syntax related to defualt parameters

  Revision 1.84  2005/09/21 09:01:50  anagy
  include multithreading

  Revision 1.83  2005/09/20 09:58:22  anagy
  syntax correcting

  Revision 1.82  2005/09/17 16:49:33  sorinp
  Made the returned stream/sunstream ID a searate parameter

  Revision 1.81  2005/09/16 08:04:23  anagy
  syntax correction

  Revision 1.80  2005/09/15 10:12:30  sorinp
  Added buffer management support for streams and substreams
  Added explicit substream extraction support

  Revision 1.79  2005/09/14 20:27:52  sorinp
  - removed STILL inband command as not actually needed - starvation followed by TIME_DISCONTINUITY is enough
  - documented the fact that WaitForStatusChange will restart targets of ACTION_STOP inband commands completed during the last call

  Revision 1.78  2005/09/12 10:43:31  anagy
  Syntax fixing

  Revision 1.77  2005/09/11 23:38:53  sorinp
  forgot the private include file commented out for doc purposes...

  Revision 1.76  2005/09/11 23:31:46  sorinp
  Multiple changes
  Completed presentation engine spec.
  Control framework spec at linear playback level.

  Revision 1.75  2005/09/11 03:08:13  sorinp
  More API updates

  Revision 1.74  2005/09/09 19:37:43  sorinp
  Changed SMetaBuffer fields and propagated changes
  Fixed ptoblems wih RUA pending calls and potential problems with event resetting

  Revision 1.73  2005/09/07 17:28:05  sorinp
  updated the global RUA data sharing scheme

  Revision 1.72  2005/09/06 21:24:32  sorinp
  fixed config parametre issue

  Revision 1.71  2005/09/06 18:51:25  sorinp
  Updated inband command spec (added param definition, some changes)

  Revision 1.70  2005/09/05 04:14:01  sorinp
  Added or moved around generic and blu-ray definitions

  Revision 1.69  2005/09/03 02:25:02  sorinp
  various syntax, functionality and doc changes

  Revision 1.68  2005/08/30 20:46:39  rdemeter
  adjust include path

  Revision 1.67  2005/08/24 09:50:45  anagy
  CPresEng constructor with void* configInfo

  Revision 1.66  2005/08/16 16:13:29  anagy
  - constructor config. for cPresEng  - rua, dcc, dram
  - config. params. for decoder output (scaler config.)

  Revision 1.65  2005/08/15 17:23:49  anagy
  added dcc_common.h

  Revision 1.64  2005/08/11 17:01:48  anagy
  corrected link errors

  Revision 1.63  2005/08/11 04:47:40  sorinp
  Updated Blu-ray pres engine API
  Split definitions in public an private files, to avoid poluting the documentation with implementation details

  Revision 1.62  2005/08/11 03:32:12  sorinp
  Added/changed Blu-ray specific API

  Revision 1.59  2005/08/05 21:32:02  sorinp
  Added helper definitions for format-specific flags
  made WaitForStatusChange void, since there is nothing to report

  Revision 1.58  2005/08/04 16:50:23  anagy
  small modifications

  Revision 1.57  2005/08/04 03:22:05  sorinp
  Added ChangeStreamParams, mainly to allow setting of the synchronizations modes between streams - to be defined later

  Revision 1.56  2005/08/03 22:13:50  sorinp
  Moved internal flag form *.h into cpp file

  Revision 1.52  2005/08/01 02:41:29  sorinp
  CplaybackControl code complete!!!

  Revision 1.51  2005/07/30 18:10:22  sorinp
  Added optional start time in CPresEng::Start

  Revision 1.46  2005/07/26 03:59:06  sorinp
  Implemented CPLaybackControl::ExecuteCmd; updated members, doc, naming and syntax and propagated the changes in deried/client classes

  Revision 1.44  2005/07/22 23:05:52  sorinp
  continued PlaybackImplementation, renamed some members, optimizations

  Revision 1.42  2005/07/20 03:24:58  sorinp
  updated BRD presentation engine API, doc

  Revision 1.24  2005/06/20 20:19:20  sorinp
  Made CPresEng implementation details private
  added documentation module support
  Revision 1.21  2005/06/16 18:20:34  sorinp
  Made substream data extraction methods public; optimized name; doc clean-up

  Revision 1.19  2005/06/11 17:28:51  sorinp
  removed garbage char

  Revision 1.18  2005/06/09 21:47:45  sorinp
  doc polishing

  Revision 1.17  2005/06/09 21:28:22  sorinp
  Added CPresEng::WaitOnVSync; changed soem names to more used ones; updated docuemntation; removed format ID from some names, the namespace should be enough

  Revision 1.16  2005/06/07 22:35:13  sorinp
  Added optional fillBuffers parameter to Pause

  Revision 1.15  2005/06/07 19:49:49  sorinp
  added xINT32/64 definitions

  Revision 1.14  2005/06/06 20:10:54  sorinp
  Upadated and documented the Blu-ray presentation engine module
  Other syntax and grammar fixes

  Revision 1.13  2005/06/06 18:34:58  sorinp
  Optimized architecture and documentation

  Revision 1.12  2005/06/06 17:17:35  sorinp
  small syntax fix

  Revision 1.11  2005/06/06 04:58:58  sorinp
  - updated syntax
  - updated and expanded comments
  - made the comments Doxygen compatible and friendly; first specification generated with Doxygen

  Revision 1.10  2005/06/05 17:16:14  sorinp
  Updated file headers

*/

