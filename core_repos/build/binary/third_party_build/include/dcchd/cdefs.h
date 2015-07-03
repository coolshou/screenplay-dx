/*****************************************
 Copyright  2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   cdefs.h
  @brief  Media navigation definitions shared with middleware clients, which may not be aware of Sigma implementation

  @author Sorin Papuc
  @date   2005-06-01

  $Header: /bigbig/dungeon/dcchd_project/dcchd/core/cdefs.h,v 1.69 2009-03-05 02:41:57 sorin Exp $

*/

#ifndef _CDEFS_H_
#define _CDEFS_H_

#include <limits.h>
#include "mdefs.h"
#include "cdefs_av.h"

///\defgroup COMCDEFS Common Media Space Control Definitions
/// These control definitions are common to any media space
///
/// Control commands, results and status are format and application specific,
/// so the syntax is defined in media spaces corresponding to each of the supported format and/or application.
///
/// A new media format or application can define a new media space and a new set of control elements
/// (commands, status and result definitions). Optionally it can reuse an existing media space by
/// inheriting its definitions.
///\ingroup COMMSDEFS

///\defgroup MSID Media Space identifiers
/// Values used in structures derived from SCommand, SStatus and SResult to identify a specific media format
///\ingroup COMCDEFS
//@{
#define MEDIA_SPACE_UNKNOWN      0     ///< unknown media space, to identify any structures derived from SCommand, SStatus and SResult

///@}


///\defgroup SFLAGS Common flags for status validation and change notification
/// Constants identifying common events and state information.
///
/// Media spaces define additional constants in the remaining bit positions
/// to identify format-specific status fields.
//@{
#define SSTATUS_CMD_PENDING  0x0001   ///< a command is being executed and no new commands can be accepted

#define SSTATUS_FLAGS        0x0002   ///< validates the flags field; events are triggered on changes in this field

#define SSTATUS_MEDIA_UIN	 0x0004   ///< validates the mediaUIN field; no events are triggered (field is set during IPlaybackControl::OpenMedia())

#define SSTATUS_MEDIA_TIME	 0x0008   ///< validates the media time field; events are triggered on validity changes and on PTS notifications (but not on normal time value changes to avoid excessive event rate) \change Added 6-15-2007

#define SSTATUS_ELAPSED_TIME 0x0010   ///< validates the elapsed time field; events are triggered on changes in this field (every second or when reinitialized)

#define SSTATUS_EXCEPTION    0x0020   ///< validates the exception field; events are triggered when the exception appears or disappears

#define SSTATUS_COMMAND      0x0040   ///< validates the command status field; events are triggered when a new result is available

#define SSTATUS_STATS        0x0080   ///< validates the statistics field; no events are triggered, but the field is updated as often as possible with minimal overhead

#define SSTATUS_MEDIA_INFO   0x0100   ///< validates the mediaInfo field; events are triggered when media parameters change

#define SSTATUS_UA_TIMEOUT   0x0200	  ///< identifies the user action timeout field; events are triggered only when the field changes from/to zero (no action needed); otherwise the timeout count is updated and can be examined on the regular second beat

#define SSTATUS_MODE		 0x0400	  ///< identifies the playback mode field; events are triggered when the mode changes

#define SSTATUS_LAST_GENERIC SSTATUS_MODE  ///< format-specific status flags values can be defined beyond this bit value

///@}

/// Playback mode definition
///
/// Media spaces may define additional constants in the remaining bit positions
/// to identify format-specific status fields.
struct SPlaybackMode
{
	UINT32 flags;   ///< \ref MFLAGS identifying individual modes
	UINT32 speed;   ///< current speed in (nominal speed / 1024 ) units
};


///\defgroup MFLAGS Flags for playback mode description
/// Constants identifying individual playback modes, used in the SStatus::mode::flags field.
///
/// Derived classes may define additional constants in the remaining bit positions
/// to identify format-specific modes.
///@{
#define SSTATUS_MODE_STOPPED        	0x0001  ///< playback is stopped, mutually exclusive with PAUSED and PLAYING

#define SSTATUS_MODE_PAUSED         	0x0002  ///< playback is paused, no output is generated

#define SSTATUS_MODE_PLAYING        	0x0004  ///< playback is enabled, output is generated

#define SSTATUS_MODE_PLAYING_NO_OUTPUT	0x0006  ///< playback is enabled but no output is generated (for example for lack of input data). \change Added 2-12-2007

#define SSTATUS_MODE_PLAY_REVERSE   	0x0008  ///< if set, crt direction is reverse, otherwise it is forward

#define SSTATUS_MODE_PLAY_KEY       	0x0010  ///< if set, key frames only mode is active, otherwise all frames mode is active

#define SSTATUS_MODE_PLAY_NONRT     	0x0020  ///< if set, a different playback speed that the normal one is used

#define SSTATUS_MODE_TRANSITION         0x0040	///< is set, a non-seamless transition is taking place \change Added 5-27-2007

#define SSTATUS_MODE_LAST	       		0x0040  ///< other mode flags values can be defined beyond this bit value

///@}

///\defgroup PMODE Playback mode definition
/// Flags identifying playback mode dimensions. Any comnbination of flags can be aggregated in a playback mode.
//@{
#define PLAY_MODE_REVERSE        SSTATUS_MODE_PLAY_REVERSE  ///< set for playback in reversed, clear for forward playback

#define PLAY_MODE_KEY            SSTATUS_MODE_PLAY_KEY      ///< set for key-frame only playback, clear for all frames playback

#define PLAY_MODE_NONRT          SSTATUS_MODE_PLAY_NONRT    ///< set for non-real time playback, clear for nominal speed playback

#define PLAY_MODE_PLAY_MASK      (SSTATUS_MODE_PLAY_REVERSE | \
                                  SSTATUS_MODE_PLAY_KEY     | \
                                  SSTATUS_MODE_PLAY_NONRT)///< mask for extracting the play mode from the status mode field

///@}

// deprecated definitions kept around for backward compatibility
#define SLPBSTATUS_UA_TIMEOUT   	SSTATUS_UA_TIMEOUT
#define SLPBSTATUS_MODE         	SSTATUS_MODE
#define SSTATUS_MODE_LAST_LPB       SSTATUS_MODE_LAST
#define LPBPLAY_MODE_REVERSE        PLAY_MODE_REVERSE
#define LPBPLAY_MODE_KEY            PLAY_MODE_KEY
#define LPBPLAY_MODE_NONRT          PLAY_MODE_NONRT
#define LPBPLAY_MODE_PLAY_MASK      PLAY_MODE_PLAY_MASK
#define SSTATUS_RESULT				SSTATUS_COMMAND
#define lastCmdResult				lastCmd.result


/// Media time definition (H, M, S, frames)
struct SMediaTime
{
    unsigned long Hour : 8;                            ///< Hour
    unsigned long Minute : 8;                          ///< Minute
    unsigned long Second : 8;                          ///< Second
    unsigned long Frame : 8;						   ///< Frame
};

/*
/// Identifies the action to be performed upon triggering a notification
enum ENotificationAction
{
     NA_CONT = 0     ///< continue presentation, can not guarantee that the position is still current by the time the client gets the notification
    ,NA_PAUSE        ///< pause presentation in order to guarantee that the position is still current by the time the client gets the notification
};

/// Notification request definition
struct SNotification
{
    enum EPositionType posType;     ///< type of the position specification
    enum ENotificationAction action;///< action to be taken upon reaching the position
};
*/

#ifdef __cplusplus
extern "C"
{
#endif


#define CMD_INVALID_CALLBACK	((void *)(-1))	///< Invalid callback value, ignore it

///\typedef typedef int (*TAVAccessWait)(int dataPathIndex, UINT32 time, void *abortObject);
///\brief Callback for spending CPU cycles while waiting for AV media access to be granted
///
/// The callback is called by the #TAVAccessRequest arbiter whenever the access to AV data can not be granted right away.
///
/// The client module can use this callback to perform operations that are mutually exclusive with AV data access, namely disc access.
///
/// The callback must return ON OR BEFORE time milliseconds pass or AS SOON AS the abort object is signaled.
///
/// Suggested use: trigger some disc-accessing operations.
///
///\param dataPathIndex Zero-based index of the AV data path accessing the media.
/// In the Sigma AV access arbiter implementation, different values identify different OS threads.
///\param pastTime Time, in milliseconds, already spent waiting for the current AV media access grant.
///\param time Time, in milliseconds, to be spent in the callback.
///\param abortObject Implementation-specific abort object, signaled when the wait is to be aborted
///\param context Call context
///\return
/// -  1 if the callback has returned due to time expiration or close to it
/// -  0 if the callback has returned immediately, without waiting or doing any significant (in terms of time spent) processing
/// - -1 if the callback has returned due to abortObject being signaled

typedef int (*TAVAccessWait)(int dataPathIndex,
							 UINT32 pastTime,
							 UINT32 time,
							 void *abortObject,
							 void *context);


///\typedef typedef int (*TAVAccessRequest)(int dataPathIndex, char *fileName, UINT64 fileOffset, UINT32 dataAmount, UINT32 bufferFullness, UINT32 maxBitRate, void *abortObject, void *pathExclusionObject, TAVAccessWait whileWaiting);
///\brief Call to AV media arbiter for acquiring exclusive access
///
/// The arbiter is called on the input thread of each data path, right before reading the AV data.
/// Once the access request is granted (the arbiter returns 1 or -1), the arbiter will not be called again but
/// #TAVAccessNotify will be called AFTER each AV data read until it revokes the access grant.
///
/// The client module can use this arbiter, together with the #TAVAccessNotify one, for controlling its media access
/// so that it does not interfere with the AV playback process. It does this, basically, by granting AV media access before
/// the time it takes the media device to access and provide the requested data becomes longer than the time it takes the AV buffer to drain.
///
/// The arbiter MUST RETURN WITHOUT GRANTING THE ACCESS when the abort object is signaled.
///
/// Suggested use: switch from data to AV access when the buffer fullness is too low to guarantee that no underflow will occur if data access continues.
///
///\param dataPathIndex Zero-based index of the AV data path accessing the media. Usually a single data path exists, but some formats (example: Blu-ray) may have more data paths active at the same time
///\param fileName File name of the AV clip being accessed.
/// The client module can use the file name to determine the media device being used and handle each device separately.
///\param fileOffset Offset into the file being accessed.
/// The client module can use the file name and offset to determine the position on the media device to be accessed.
///\param dataAmount Amount of new AV data (in bytes) requested from the media device.
/// The client module can use the data position and amount to determine the time it takes to access and provide the requested data.
///\param bufferFullness Amount of AV data (in bytes) that is currently buffered for playback.
///\param maxBitRate Maximum bit rate (in bits/sec) at which buffered data can be consumed.
/// The client module can use the buffer fullness and maximum bit rate to determine how long the request can be denied without causing AV buffer underflow.
///\param abortObject Implementation-specific abort object, signaled when the request is to be aborted
///\param pathExclusionObject Implementation-specific path exclusion object, signaled when the path is granted exclusive access
///\param waitCall If not NULL, this callback will be called whenever AV access is not granted right away.
///\param context Context to be used in the #TAVAccessWait call
///\return
/// -  1 if the data access request is granted for this resource; this callback should not be called again until the request grant is taken away by a #TAVAccessNotify call
/// -  0 if the data access request is NOT granted and must be made again, with updated parameters
/// - -1 if data access restrictions do not apply and the request is granted perpetually for this resource; neither the request nor the notification calls should be ever called for it
/// - -2 if the data access request has been aborted by signaling the abortObject
///\note
/// - The client module can use or delay the arbiter thread as long the delay does not cause an AV buffer underflow.
/// - The arbiter is not called when the AV playback is stopped, paused or not accessing the media device for any other reason (example: pre-loaded media).

typedef int (*TAVAccessRequest)(int dataPathIndex,
								char *fileName,
								UINT64 fileOffset,
								UINT32 dataAmount,
								UINT32 bufferFullness,
								UINT32 maxBitRate,
								void *abortObject,
								void *pathExclusionObject,
								TAVAccessWait waitCall,
								void *context);

///\typedef typedef int (*TAVAccessNotify)(int dataPathIndex, UINT32 bufferEmptyness, RMtimeoutSemaphore pathExclusionObject);
///\brief Optional call to AV media access arbiter for releaseing exclusive access.
///
/// The arbiter is called on the input thread of each data path, right after reading the AV data.
///
/// The client module can use this arbiter, together with the #TAVAccessRequest one, for controlling its media access
/// so that it does not interfere with the AV playback process.
///
/// Suggested use: switch from AV to data access when the buffer emptiness becomes negative, meaning that the AV buffers are full.
///
///\param dataPathIndex Zero-based index of the AV data path accessing the media. Usually a single data path exists, but some formats (example: Blu-ray) may have more data paths active at the same time
///\param bufferEmptyness Amount of AV data (in bytes) that can still be buffered for playback.
/// It can hold negative values, meaning that data that has just been read will not fit in the AV buffers.
/// The client module can use the buffer emptiness to determine when to start accessing the media device for its own purposes while blocking the AV data accesses.
///\param pathExclusionObject Implementation-specific path exclusion object, the same one passed in the #TAVAccessRequest call
///\return
/// -  1 if the data access request remains granted, this arbiter should be called again after the next data access cycle
/// -  0 if the data access request is revoked and must be requested again before the next data access cycle
///\note
/// - The client module should return without any significant delay.
/// - A call with bufferEmptyness set to #END_OF_MEDIA_ACCESS is made when the data path becomes inactive, to notify the client that it has free access to the media device.
/// - The arbiter is not called when the AV playback is stopped, paused or not accessing the media device for any other reason (example: pre-loaded media).

typedef int (*TAVAccessNotify)(int dataPathIndex, long bufferEmptyness, void *pathExclusionObject);


#define END_OF_MEDIA_ACCESS		LONG_MIN	///< special emptiness value signaling that no more A/V media accesses are planned for now

#ifdef __cplusplus
} //extern "C"
#endif


/// Identifies the behavior upon Stop
enum EStopMode
{
    SM_BLANK= 0,		///< display blank frame
    SM_LAST_FRAME,		///< display the last frame
};


/// Definition of action to be taken at play item end

/// Used by applications that want to enforce their own navigation
/// strategy rather than the one mandated by the standard
enum EPlayItemEndAction
{
	PIEA_Default = 0,	///< standard-mandated action
	PIEA_Stop,			///< stop playback (application must take over)
	PIEA_Repeat,		///< repeat the play item
};



/// Common media commands

/// These commands must be supported by all media spaces.
/// Each media space may (and usually does) define additional commands starting at value 1
///\ingroup COMCDEFS
enum ECmd
{
	/// Sets the output configuration specified in control.configuration field of the SCommand structure
	Cmd_SetConfig = -128,

	/// Installs the application callbacks specified in the control.callback field of the SCommand structure
	Cmd_SetCallbacks,

	/// Makes the output parameter adjustments identified in control.adjustment field of the SCommand structure
	Cmd_Adjust,

	/// Generates a #SSTATUS_MEDIA_TIME event when reaching the media time specified in the control.notification.pts field of the SCommand structure \change Assigned 6-15-2007 explicit event
	Cmd_WakeUpOnPTS,

	/// Generates a #SSTATUS_COMMAND event, used to insert external commands completion
	Cmd_NOP,

	/// Notifies the playback controller that the user is about to eject the disc \change Added 3-23-2008

	/// The command should be always issued in synchronous mode. The actions to be taken depend on the returned value:
	/// - on error or #RESULT_DEFAULT success code, the media must be closed and then the the disc must be ejected
	/// - on #RESULT_OUT_OF_SYNC success code, the disc must be ejected without closing the media
	Cmd_disk_ejecting,

	/// Notifies the playback controller that the user has inserted a new disc \change Added 3-23-2008

	/// The command should be issued only when the previous disc has been ejected without closing the media
	/// as a result of a #Cmd_disk_ejecting command that has returned a #RESULT_OUT_OF_SYNC success code.
	///
	/// The command should be always issued in synchronous mode. The possible returned values are:
	/// - #TRESULT_SUCCESS - the media was inserted successfully and can be used
	/// - #TRESULT_ERROR | #RESULT_OUT_OF_SYNC - a different media than the one expected has been inserted, there are two options:
	///   - eject and insert another media, then issue the command again
	///   - leave the media inserted and restart the playback controller, the current media chain will be canceled
	/// - any other #TRESULT_ERROR code - media or internal error, check the code for details.
	Cmd_disk_inserted,

	/// Notifies the playback controller that the user has removed the persistent storage \change Added 6-5-2008

	/// The command should be always issued in synchronous mode. The actions to be taken depend on the returned value:
	/// - on error, the media must be closed and then re-opened, since the storage was part of the current session
	/// - on success, the playback session can continue
	Cmd_storage_removed,

	/// Notifies the playback controller that the user has installed the persistent storage \change Added 6-5-2008
	Cmd_storage_installed,
};

/// Command information common for any control object

/// All controllers must support the common media commands #ECmd and their corresponding parameters in this structure.
///
/// New command info structures are defined by format-specific controllers by inheriting from the basic type
///
/// The controller must use a newly defined media space value, unless it can reuse an existing media namespace
/// (in that case it also reuses existing #SCommand, #SResult and #SStatus or derived structures).
///
/// All the data should be stored contiguously inside the structure (no external references), so that
/// it can be accurately duplicated by copying dataSize bytes.
///\ingroup COMCDEFS
struct SCommand
{
    UINT32 dataSize;    		///< size of the relevant data
    int mediaSpace;     		///< Media space to which the command belongs. The structure can be then casted to the corresponding struct type.

	/// control parameters common to all media spaces
    union
    {
    	/// parameter for the #Cmd_Adjust command

		/// \note Because it violates the contiguous storage requirement, it is always handled as synchronous command by framework,
		/// in order to make sure the pointer stays valid during command execution
	    struct SAdjustment *adjustment;

		/// parameters for the #Cmd_SetConfig command.
	    struct
	    {
    		/// Pointer to the video config parameters

    		/// May point to implementation-specific structure derived from the generic one,
    		/// so the SVideoOutConfig::size field must be set properly
    		/// \note Because it violates the contiguous storage requirement, it is always handled as synchronous command by framework,
    		/// in order to make sure the pointer stays valid during command execution
	    	struct SVideoOutConfig *video;

    		/// Pointer to the audio config parameters

    		/// May point to implementation-specific structure derived from the generic one,
    		/// so the SAudioOutConfig::size field must pe set properly
    		/// \note Because it violates the contiguous storage requirement, it is always handled as synchronous command by framework,
    		/// in order to make sure the pointer stays valid during command execution
	    	struct SAudioOutConfig *audio;
	    }
	    configuration;

		/// Parameters for the #Cmd_SetCallbacks command. \note To set only some of the callbacks, use the #CMD_INVALID_CALLBACK value for those that are to be left unchanged.
	    struct
	    {
	    	void *configPreview;				///< implementation-specific configuration preview callback
	    	void *configConfirm;				///< implementation-specific configuration confirmation callback
	    	TAVAccessRequest avAccessRequest;	///< AV media access request call, can be set only once and never reset in a playback session
	    	TAVAccessNotify  avAccessNotify;	///< AV media access notification call, can be set only once and never reset in a playback session
	    }
	    callback;

	    /// parameters for the #Cmd_WakeUpOnPTS command. \change Changed #Cmd_WakeUpOnPTS parameter structure as added overwriting option 6-4-2007
	    struct
	    {
			TResultCode	oldID;	///< ID of the pending request to be overwritten by the new notification request (the result code of the old request can be used); if 0, the new request will be added to the list
	    	UINT64		pts;	///< target media time for the notification request
	    }
	    notification;

	    /// parameter for the #Cmd_NOP command
	    TResultCode result;
    }
    control;
};

/// Media statistics
struct SMediaStats
{
//    UINT32 videoBufferFullness;	///< decoder buffer fullness
    UINT32 bufferFullness;    	///< input buffer fullness (bytes)
//	UINT32 avgBitrate;          ///< average bitrate of the crt playback item
	UINT32 crtBitrate;          ///< current input bitrate (KB/sec)
};

///\typedef typedef bool (*TAtomicLargeRead)(void *presentation, UINT64 *pMediaTime, UINT64 *pStreamTime)
/// Function to retrieve a consistent set of media and presentation time values
///\param presentation Presentation identifier.
///\param pMediaTime Buffer in which the media time is to be returned. Media time is the presentation time of the currently displayed (video) sample, and thus does not advance during stills or after the last (video) sample of the content has been displayed.
///\param pStreamTime Buffer in which the presentation time is to be returned. Presentation time is the presentation time line, and thus advances even during stills and after the last (video) sample of the content has been displayed (but not during PAUSED and of course STOPPED states).
///\return If true, the returned values are valid and consistent (belong to the same point in time), otherwise they are invalid (no presentation is active or it is in a transitional state - for example STARTING).

typedef bool (*TAtomicLargeRead)(void *presentation, UINT64 *pMediaTime, UINT64 *pPresentationTime);

/// Status info common for any control object

/// New status info structures are defined by format-specific controllers by inheriting from the basic type
///
/// The controller must use a newly defined mediaSpace value, unless it can reuse an existing media namespace
/// (in that case it also reuses existing SCommand, SResult and SStatus or derived structures).
///
/// All the data should be stored contiguously inside the structure (no external references), so that
/// it can be accurately duplicated by copying dataSize bytes.
///\ingroup COMCDEFS
struct SStatus
{
    /// Size of the structure at the top of the derivation tree
    UINT32 size;

    /// Media space to which the status belongs. The structure can be then casted to the corresponding struct type.
    int mediaSpace;

    /// Type of the particular media being presented. Multiple related types may be handled in the same media space.
    TMediaType mediaType;

    /// Function to retrieve a consistent set of media and presentation time values \change Added 9-19-2007

    /// The field is self-validating, i.e. a non-NULL value is valid, NULL is invalid.
    ///
    /// IMPORTANT: The function must be called on a thread of lower priority than the control thread.
    /// \note Use the #presentationId value as the #TAtomicLargeRead 'presentation' argument.
    TAtomicLargeRead getMediaAndPresentationTime;

    /// Presentation identifier

    /// To be used in #getMediaAndPresentationTime calls.
    /// Guaranteed to be valid whenever #getMediaAndPresentationTime is valid.
    void *presentationId;

    /// Flags identifying the status categories (fields) that have changed since the the last time the status has been inspected.

	/// See \ref SFLAGS and \ref MEDSPACES
	/// for values used in this field
    UINT32 changes;

    /// Flags validating the status categories (fields)

	/// See \ref SFLAGS and \ref MEDSPACES
	/// for values used in this field
    UINT32 flags;

    /// media unique identifier
    UINT64 mediaUIN;

	/// Current media time (in media clock ticks)

    /// This field is a live pointer, can be read any time while valid.
	///
    /// For static images (JPEG), the media time is actually the 0-based index of the displayed picture in the sequence starting at the last Start() command
    /// \deprecated Use SStatus::getMediaAndPresentationTime instead, to avoid race conditions on non-atomic UINT64 reads/writes
	UINT64 *mediaTime;

	/// Elapsed time, in seconds. The reference event is format-specific (for example title start, playlist-start, etc)
	UINT32 elapsedTime;

    /// Exceptions condition

    /// The client has to understand only the fatal and delay exceptions and act on them
    /// The rest of the exception info is for user feed-back (if any) or diagnostics
    struct SException
    {
        UINT32 fatal    : 1;    ///< the exception is fatal, the module must be terminated
        UINT32 delay    : 1;    ///< the exception is correctable, module is working on it until successful or abort request is received
        UINT32 padding  : 14;   ///< padding to make debugging easier

        UINT32 type     : 16;   ///< optional exception code (for display purposes only), contains result values defined in \ref TRES \change Clarified usage 4-16-2007

        UINT32 param;           ///< optional, type-dependent parameter (for display purposes only)
    }
    exception;

    /// Last command status \change Added 2-28-2008 to allow identification of the executed command. Backward compatibility preserved by way of #lastCmdResult macro.
    struct SCmdStatus
    {
    	TResultCode result;	///< Result of the last command executed

    	TResultCode id;		///< ExecuteCmd-assigned ID of the last asynchronous command executed
    }
    lastCmd;

    /// Playback statistics
	struct SMediaStats statistics;

    /// Real-time media info for audio/video decoders in the system

    /// This media information complements the format-specific one
    /// that is normally offered by derived classes.
    ///\note Currently only info on the following decoders is exposed here:
    /// - the main audio decoder - an event in generated every time the information changes
    /// - the JPEG decoder - an event is generated for each decoded picture, can be used for both extracting the image size and for successful completion confirmation
    struct SMediaFormat mediaInfo[4];

    /// seconds left for user to provide input before an automatic action is taken; 0 = no user action needed; -1 = infinite wait for user action
    int userActionTimeout;

    /// Current playback mode
    struct SPlaybackMode mode;
};

/// Synchronous command result definition common for any control object

/// Synchronous results are delivered through this specialized structure and can be
/// arbitrarily complex, as opposed to asynchronous commands which can hold only a TResultCode value
///
/// New result info structures are defined by format-specific controllers by inheriting from the basic type
///
/// The controller must use a newly defined mediaSpace value, unless it can reuse an existing media namespace
/// (in that case it also reuses existing SCommand, SResult and SStatus or derived structures).
///
/// All the data should be stored contiguously inside the structure (no external references), so that
/// it can be accurately duplicated by copying dataSize bytes.
///\ingroup COMCDEFS
struct SResult
{
    UINT32 dataSize;        ///< size of relevant data
    int mediaSpace;         ///< Media space to which the result belongs. The structure can be then casted to the corresponding struct type.
    TResultCode value;      ///< scalar value result, command-specific
};

#endif //_CDEFS_H_

/**
  $Log: cdefs.h,v $
  Revision 1.69  2009-03-05 02:41:57  sorin
  BugId: none
  Reversed flag-based Blu-ray type definition to avoid complications with values used as indices.
  Propagated the changes

  Revision 1.68  2009-01-16 19:42:16  dnguyen
  BugId: none
  SLPBSTATUS_AUDIO and SLPBSTATUS_VIDEO to be used only by LPB module

  Revision 1.67  2009-01-14 00:39:29  sorin
  BugId: none
  Added total delay time info in the waiting call of the disc access arbiter, in order to allow a client to select only the top-of-the-buffer moments

  Revision 1.66  2008-11-20 16:56:11  sorin
  BugId: none
  Merged the Fast Load changes (asynchronous AACS and BD+)

  Revision 1.65  2008-10-07 23:24:26  sorin
  BugId: none
  Doc

  Revision 1.64  2008-07-17 03:43:32  sorin
  BugId: none
  Doc

  Revision 1.63  2008-06-05 22:43:23  sorin
  BugId: none
  Added geenric commands for sending notifications about storage events to the playback controller
  Implemented the storage event commands in the BD controller

  Revision 1.62  2008-05-27 23:31:07  sorin
  BugId: none
  Replaced the BD-specific NON_SEAM:ESS mode flag with the generic TRANSITION one

  Revision 1.61  2008-03-23 22:40:51  sorin
  BugId: none
  Simplified disc unbound BDJ app handling by GUI - just a result of the ejecting/inserted commands

  Revision 1.60  2008-03-03 22:50:13  sorin
  BugId: none
  Added NOP generic command in order to allow insertion of external command completion notifications (needed in BD-J)

  Revision 1.59  2008-03-03 22:27:24  sorin
  BugId: none
  Added command ID in the result code returned by ExecuteCmd, in order to allow unequivocal association of  asynchronous commands and results.

  Revision 1.58  2008-02-29 03:49:26  sorin
  BugId: none
  Added last command code status field

  Revision 1.57  2007/11/15 18:05:31  sorin
  BugId: none
  doc

  Revision 1.56  2007/10/30 08:35:16  sorin
  Updated the AV access API, fixed implementation

  Revision 1.55  2007/09/24 14:10:03  sorinp
  doc

  Revision 1.54  2007/09/20 19:28:01  sorinp
  BugId:NONE
  Added thread-safe media and presentation time retrieval mechanism

  Revision 1.53  2007/09/04 19:32:37  sorinp
  fixed compiler error

  Revision 1.52  2007/09/04 19:27:41  sorinp
  Rolled back changer in order to be able to generate a patch for them

  Revision 1.50  2007/09/01 15:34:10  sorinp
  BUG-CT:3818 Fix the end-o-data signalling in AV access callbacks

  Revision 1.49  2007/08/31 19:57:45  sorinp
  BUG-CT:3818 Add media access arbitration mechanism

  Revision 1.48  2007/08/28 18:13:27  sorinp
  Fixed problems with the initial command execution profiling implementation:
  - using a Sigma-specific construct in cdefs.h (and all the other header files included by a DirectFB client) is prohibited and generates unresolved symbol compilation errors
  - profiling is an internal feature and should not affect the interface
  - profiling is a debugging feature and should not affect the production code

  Define the TRACE_COMMAND_EXECUTION compiler symbol in order to enable the profiling code

  Revision 1.46  2007/08/28 10:47:32  rdemeter
  BUGCT#none add timestamp to command struct

  Revision 1.45  2007/06/18 12:10:23  anagy
  BUGCT#3353 fix: New patches applied

  Revision 1.44  2007/06/08 15:03:26  anagy
  BUGCT#3353 fix: applied the patches, made fixes

  Revision 1.43  2007/05/08 19:29:41  sorinp
  BUGCT:3208 - 3213 Added stopMode parameter to Stop command in all media spaces to allow client module to control behavior

  Revision 1.42  2007/04/17 00:10:10  sorinp
  BUGCT:2988 Clarified exception.type field usage

  Revision 1.41  2007/03/20 00:15:12  sbeysserie
  Add end of line.

  Revision 1.40  2007/03/19 16:31:09  sorinp
  Moved log at the end of the file

  Revision 1.39  2007/02/21 20:25:08  sorinp
  doc update

  Revision 1.38  2007/02/20 23:17:22  sorinp
  restored generic media space ID

  Revision 1.37  2007/02/20 20:12:26  sorinp
  doc update

  Revision 1.36  2007/02/13 05:07:38  sorinp
  typo in previous check in

  Revision 1.35  2007/02/13 05:02:25  sorinp
  BUGCT:2272 Added PLAYING_NO_OUTPUT playback mode (lack of output data due to starvation), to be used for exposing the PCMX sound completion

  Revision 1.34  2006/12/14 13:18:27  rdemeter
  merge title/chapter repeat

  Revision 1.33  2006/10/13 20:22:48  sorinp
  Moved the userTimeout and mode fields from LPB to generic status in order to allow single-point processing of the status in CPlaybackControl

  Revision 1.32  2006/10/07 00:20:27  sorinp
  Moved definitions used by other media spaces into cdefs.h

  Revision 1.31  2006/10/05 21:52:53  sorinp
  doc updates

  Revision 1.30  2006/09/26 03:03:54  sorinp
  Updated to B.6.0 level

  Revision 1.29  2006/09/24 03:37:07  sorinp
  Working Media UIN for VFS-based access, propagated API changes

  Revision 1.28  2006/09/23 07:33:39  sorinp
  Media UIN code complete, the UDF library's dopen not working though

  Revision 1.27  2006/09/21 19:52:44  sorinp
  Added WakeUpOnPTS command in CPlaybackControl

  Revision 1.26  2006/08/31 04:41:33  sorinp
  Updated doc change list to B.5.0

  Revision 1.25  2006/08/30 18:53:17  sorinp
  Changed the statistics info definition and moved the filed from the LPB into the generic media space

  Revision 1.24  2006/08/07 02:09:52  sorinp
  doc, reduce wastefull memory

  Revision 1.23  2006/08/06 02:12:18  sorinp
  updated constant

  Revision 1.22  2006/08/06 02:11:29  sorinp
  Added real-time media info support

  Revision 1.21  2006/06/15 05:26:41  sorinp
  Updated and propagated changes in adjustments API

  Revision 1.20  2006/06/07 02:11:39  sorinp
  Added API to set callbacks, configuration and adjustments in AMP inside and outside a media cycle and propagated changes

  Revision 1.19  2006/06/06 02:47:02  sorinp
  fixes and updates, mostly related to av config

  Revision 1.18  2006/06/03 03:54:58  sorinp
  Enabled pre-configuration

  Revision 1.17  2006/05/15 01:52:38  sorinp
  made config and callbacks separate methods

  Revision 1.16  2006/05/15 01:18:14  sorinp
  new configurationscheme related changes

  Revision 1.15  2006/05/14 19:27:59  sorinp
  Updated Get/SetConfiguration syntax

  Revision 1.14  2006/04/27 07:30:36  sorinp
  Updated A/V config spec, new memory allocation (static) spec

  Revision 1.13  2006/04/19 04:23:36  mfedoreanu
  moved Media time from specific format status to common status

  Revision 1.12  2006/03/19 03:20:54  sorinp
  Added UNKNOWN media speace definition

  Revision 1.11  2006/02/17 20:38:54  sorinp
  removed the /change tags to start clean for the enxt release

  Revision 1.10  2006/02/15 16:52:00  sorinp
  Implemented the configurationnd adjustment generic commands in the framework

  Revision 1.9  2006/02/01 23:46:34  sorinp
  Marked changes in last release as past changes

  Revision 1.8  2006/02/01 05:46:53  sorinp
  doc typos

  Revision 1.7  2006/01/30 09:00:57  sorinp
  Added configuration and adjustment definitions

  Revision 1.6  2005/12/07 16:06:44  sorinp
  Clarified documentation

  Revision 1.5  2005/11/05 20:20:06  sorinp
  replaced the second beat event with the elapsed time field and event

  Revision 1.4  2005/10/11 12:47:56  sorinp
  Renamed lastAsyncCmdResult to lastCmdResult to avoid confusion over where to look for results

  Revision 1.3  2005/10/05 18:43:29  sorinp
  Mostly doc upgrades

  Revision 1.2  2005/09/28 11:35:04  sorinp
  minor typo

  Revision 1.1  2005/09/26 06:47:11  sorinp
  finalized linear and blu-ray control and media definition
  placed public media and control definitions in separate (and new) files

  Revision 1.10  2005/09/23 14:51:34  sorinp
  Moved Linear playback definitions in new file mdefs_lpb.h
  Various changes for more consistent approach

  Revision 1.9  2005/09/12 11:25:48  rdemeter
  syntax fix

  Revision 1.8  2005/09/12 00:09:47  sorinp
  Small fixes

  Revision 1.7  2005/09/11 23:31:46  sorinp
  Multiple changes
  Completed presentation engine spec.
  Control framework spec at linear playback level.

  Revision 1.6  2005/09/05 03:54:02  sorinp
  Made CMD_PENDING a top level status flag to simplify code

  Revision 1.5  2005/09/03 02:25:02  sorinp
  various syntax, functionality and doc changes

  Revision 1.4  2005/08/06 20:24:22  sorinp
  Adding external API details: commands, status fields, etc

  Revision 1.3  2005/07/26 03:59:06  sorinp
  Implemented CPLaybackControl::ExecuteCmd; updated members, doc, naming and syntax and propagated the changes in deried/client classes

  Revision 1.2  2005/07/22 23:05:52  sorinp
  continued PlaybackImplementation, renamed some members, optimizations

  Revision 1.1  2005/06/20 21:16:34  sorinp
  Split mdefs in presentation and control definitions

*/

