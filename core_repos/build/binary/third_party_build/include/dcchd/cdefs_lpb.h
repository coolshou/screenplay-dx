/*****************************************
 Copyright  2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   cdefs_lpb.h
  @brief  Linear playback control definitions shared with middleware clients

  @author Dat Nguyen
  @date   2005-08-19

  $Log: cdefs_lpb.h,v $
  Revision 1.44.8.8  2011-06-08 21:06:22  klin
  BugId: 31690
  dcchd patch for rebuffering control support
  SEND_COMMENT_BUGZILLA

  Author: Dat Nguyen, Dat_Nguyen@sdesigns.com
  Verified by: Dat Nguyen, Dat_Nguyen@sdesigns.com
  Signed-off by: Sorin Papuc, sorin_papuc@sdesigns.com
  Branch approval: Cat Nguyen, Cat_Nguyen@sdesigns.com

  Revision 1.44.8.7  2011-03-25 22:22:02  klin
  BugId: 30457
  patch to integrate HLS support into dcchd/amp_test
  SEND_COMMENT_BUGZILLA

  Author: Dat Nguyen, Dat_Nguyen@sdesigns.com
  Verified by: Dat Nguyen, Dat_Nguyen@sdesigns.com
  Signed-off by: Sorin Papuc, sorin_papuc@sdesigns.com
  Branch approval: Cat Nguyen, Cat_Nguyen@sdesigns.com

  Revision 1.44.8.6  2010-09-17 18:03:52  dnguyen
  BugId: 28429
  SEND_COMMENT_BUGZILLA
  allow clients to customize pre-buffering parameters

  Revision 1.44.8.5  2010-09-16 00:42:15  dnguyen
  BugId: 12608
  SEND_COMMENT_BUGZILLA
  rolled back the changes (removed the callbacks)

  Revision 1.44.8.4  2010-07-30 13:36:41  isarkany
  BugId: none
  Merge from HEAD

  Revision 1.48  2010-07-22 00:16:43  dnguyen
  BugId: none
  SEND_COMMENT_BUGZILLA
  allow client to define callbacks as part of open params:
  - when playback starts: to modify RMFP's options
  - when playback reaches EOS: to perform special handling such as closing media

  Revision 1.47  2010-05-12 22:24:10  sorin
  BugId: none
  cdefs_xxx.h and mdefs_xxx.h files are included by DirectFB and other MRUA-unaware modules and thus must be free of MRUA definitions. Use only native compiler types for best performance or DCC-HD definitions (UINT32, etc).
  The immediate problem this check-in fixes is broken FlashLite compilation

  Revision 1.46  2010-04-28 01:13:47  dnguyen
  BugId: none
  Added open parameters for LPB

  Revision 1.45  2010-01-29 19:21:57  sorin
  BugId: none
  Added time shift buffer LPB status definition and propagated its support in the framework (but not actual population in CLpbNavigator)

  Revision 1.44  2009-08-29 01:02:39  sorin
  BugId: none
  Added stream sets (MPEG TS program) definitions in LPB media space and support for them in amp_test;
  Propagated changes

  Revision 1.43  2009-04-11 03:28:37  sorin
  BugId: none
  Doc

  Revision 1.42  2009-03-25 03:45:43  sorin
  BugId: 10519
  Added the file offset seek mode

  Revision 1.41  2009-03-25 01:09:24  dnguyen
  BugId: 10519
  SEND_COMMENT_BUGZILLA
  support for "seek to percentage"
  index creation progress status

  Revision 1.40  2009-01-16 19:45:38  dnguyen
  BugId: none
  Added subtitle support

  Revision 1.39  2007-06-06 16:17:13  smanciulea
  - replaced all occurences of wchar_t with char and done all related changes for string manipulation
  - DCCHD_MAX_PATH changed from 512 to 2048

  Revision 1.38  2007/02/20 23:32:32  sorinp
  doc updates

  Revision 1.37  2007/02/20 20:12:26  sorinp
  doc update

  Revision 1.36  2007/02/14 04:21:30  sorinp
  Doc upgrade

  Revision 1.35  2006/10/13 20:22:48  sorinp
  Moved the userTimeout and mode fields from LPB to generic status in order to allow single-point processing of the status in CPlaybackControl

  Revision 1.34  2006/10/07 00:20:27  sorinp
  Moved definitions used by other media spaces into cdefs.h

  Revision 1.33  2006/09/26 03:06:21  sorinp
  Updated to B.6.0 level

  Revision 1.32  2006/09/24 03:37:07  sorinp
  Working Media UIN for VFS-based access, propagated API changes

  Revision 1.31  2006/08/30 18:53:17  sorinp
  Changed the statistics info definition and moved the filed from the LPB into the generic media space

  Revision 1.30  2006/06/27 19:33:19  sorinp
  Upgraded doc to B.2.0 level

  Revision 1.29  2006/04/26 20:26:57  sorinp
  Added play item end action definition

  Revision 1.28  2006/04/25 04:37:24  sorinp
  doc upgrades

  Revision 1.27  2006/04/19 04:23:36  mfedoreanu
  moved Media time from specific format status to common status

  Revision 1.26  2006/04/04 01:04:39  sorinp
  Added buffer fullness measure in the statistics definition

  Revision 1.25  2006/03/20 23:54:14  dnguyen
  feature implementation status

  Revision 1.24  2006/01/30 02:46:19  sorinp
  Clarified media sapce - media type correspondence

  Revision 1.23  2006/01/16 00:13:35  sorinp
  typo

  Revision 1.22  2005/12/12 16:48:46  sorinp
  doc fix

  Revision 1.21  2005/12/12 16:43:39  sorinp
  renamed, synchronized and updated commands and flags

  Revision 1.20  2005/12/11 16:41:05  sorinp
  replaced aggregate Play Mode command with individual Scan Fwd and Scan Bwd

  Revision 1.19  2005/12/08 05:05:24  sorinp
  renamed position fields to make them more similar with the other media spaces

  Revision 1.18  2005/12/08 04:55:49  sorinp
  updates spec to separate pause on, off, play time, play position, to make it more similar with the other media spaces

  Revision 1.17  2005/11/29 00:26:42  sorinp
  changed media time definition from clock ticks to H,M,S,frames

  Revision 1.16  2005/11/16 00:05:47  dnguyen
  changed all bool struct members to int because the difference between mips
  C compiler (where bool is 32-bit) and C++ compiler (bool is 8-bit) can be
  catastrophic

  Revision 1.15  2005/11/03 13:13:17  mfedoreanu
  Moved some structs defs outside

  Revision 1.14  2005/10/29 02:03:24  dnguyen
  typo

  Revision 1.13  2005/10/18 02:45:41  sorinp
  typo

  Revision 1.12  2005/10/12 13:45:30  sorinp
  doc updates

  Revision 1.11  2005/10/05 18:44:19  sorinp
  Mostly doc upgrades

  Revision 1.10  2005/10/04 03:49:55  sorinp
  doc fix

  Revision 1.9  2005/10/03 20:26:41  sorinp
  Removed notification support

  Revision 1.8  2005/09/30 07:05:14  sorinp
  Added userActionTimeout field

  Revision 1.7  2005/09/30 05:31:29  sorinp
  Updated mediaID size to 128 bits, doc

  Revision 1.6  2005/09/28 11:41:23  sorinp
  Made C compatible

  Revision 1.5  2005/09/27 13:43:11  sorinp
  Syntax fix

  Revision 1.4  2005/09/27 13:15:19  sorinp
  Allowed play mode components to be agregated in a single command

  Revision 1.3  2005/09/27 10:57:33  rdemeter
  fix sintax of ELPBCmd enumeration

  Revision 1.2  2005/09/26 07:52:27  sorinp
  Made disc ID a lpb media ID field, since it will be used by all the interactive formats

  Revision 1.1  2005/09/26 06:47:12  sorinp
  finalized linear and blu-ray control and media definition
  placed public media and control definitions in separate (and new) files

  Revision 1.1  2005/09/23 14:39:10  sorinp
  Renamed from mdefs_mono to remove irrelevant Mono association
  Moved linear playback definitions from mdefs_nav.h

  Revision 1.1  2005/09/10 02:07:59  dnguyen
  define first few MONO specific commands
  : ----------------------------------------------------------------------


*/

#ifndef _MDEFS_LPB_
#define _MDEFS_LPB_

#include "cdefs.h"

///\defgroup LINMSDEFS Linear Playback Media Space Definitions
/// Definitions for file and stream playback.
/// They apply to #TMediaType values that specify any valid combination of \ref EMTYPE and \ref CMTYPE
///
/// Note: The linear playback media space uses the \ref COMMDEFS
///\ingroup MEDSPACES

///\defgroup LINCTRLDEFS Linear Playback Control Definitions
/// Control definitions for linear playback media space
///\ingroup LINMSDEFS
///@{
#define MEDIA_SPACE_LINEAR_MEDIA        1   ///< Linear playback media space, to identify SLPBCommand, SLPBStatus and SLPBResult structures \ingroup MSID

#define MAX_NAME_SIZE         64            ///< maximum size of names

#define MAX_URI_SIZE          1024          ///< maximum size of URIs

///@}

///\defgroup SLPBFLAGS Linear playback flags for status validation and change notification
/// Constants identifying individual Linear Playback status fields and events. Used in addition to \ref SFLAGS
///\ingroup LINCTRLDEFS
//@{
#define SLPBSTATUS_MEDIA        		(SSTATUS_LAST_GENERIC << 1)  ///< identifies the media field; events are triggered when media or it's parameters change
#define SLPBSTATUS_VIDEO        		(SSTATUS_LAST_GENERIC << 2)  ///< identifies the video field; events are triggered when the stream identity or its parameters change
#define SLPBSTATUS_AUDIO        		(SSTATUS_LAST_GENERIC << 3)  ///< identifies the audio field; events are triggered when the stream identity or its parameters change
#define SLPBSTATUS_SUBTITLE     		(SSTATUS_LAST_GENERIC << 4)  ///< identifies the subtitle field; events are triggered when the stream identity or its parameters change
#define SLPBSTATUS_INDEX_PROGRESS		(SSTATUS_LAST_GENERIC << 5)  ///< identifies the indexCreationProgress field; events are triggered when the stream identity or its parameters change
#define SLPBSTATUS_STREAM_SETS			(SSTATUS_LAST_GENERIC << 6)  ///< identifies the streamSets field; events are triggered when the stream set structure of the media changes, which can happen only upon opening the media
#define SLPBSTATUS_TIME_SHIFT_BUFFER	(SSTATUS_LAST_GENERIC << 7)  ///< identifies the timeSiftBuffer field; events are triggered when the time shift buffer parameters change
#define SLPBSTATUS_LAST_SPECIFIC		(SSTATUS_LAST_GENERIC << 7)  ///< other status flags values can be defined beyond this bit value

///@}

enum SLPBIndexMode
{
	LPBIndex_Auto = 0,                  ///< automatic indexing: use the specified index file if it exists otherwise create it on-the-fly
	LPBIndex_None,                      ///< no indexing
};

/// Linear playback rebuffering control

/// Specify whether rebuffering should be handled by the client or automatically by the playback controller
struct SLPBRebufferControl
{
	enum
	{
		LPBRebuffer_None, 				///< rebuffering will only be triggered by the client
		LPBRebuffer_Auto_byFullness, 	///< automatic based on fifo fullness
		LPBRebuffer_Auto_byPlayTime, 	///< automatic based on playback duration of bufferred data
	} mode;

	union
	{
		struct SLPBRebufferByFullnessParams
		{
			int audioLo; 				///< low water mark for audio fifo (in percentage, default is 3%) when auto rebuffering will start
			int audioHi; 				///< high water mark for audio fifo (in percentage, default is 90%) when auto rebuffering will stop
			int videoLo; 				///< low water mark for video fifo (in percentage, default is 3%) when auto rebuffering will start
			int videoHi; 				///< high water mark for video fifo (in percentage, default is 90%) when auto rebuffering will stop
		} fullness;

		struct SLPBRebufferByPlayTimeParams
		{
			int audioLo; 				///< low water mark for audio fifo (in milliseconds, default is 500ms) when auto rebuffering will start
			int audioHi; 				///< high water mark for audio fifo (in milliseconds, default is 10s) when auto rebuffering will stop
			int videoLo; 				///< low water mark for video fifo (in milliseconds, default is 500ms) when auto rebuffering will start
			int videoHi; 				///< high water mark for video fifo (in milliseconds, default is 10s) when auto rebuffering will stop

			int fullness;				///< high water mark percentage-wise (default is 90%) in case the time-wise marks cannot be reached
		} playTime;

	} params;

	int timeout;						///< maximum time auto rebuffering can spend (in seconds, default is 30s), auto rebuffering will stop when timeout expires
};

/// OpenMedia parameters
struct SLPBOpenParams
{
	int videoPID;
	int videoSubPID;
	struct SMediaFormat videoFormat;

	int audioPID;
	int audioSubPID;
	struct SMediaFormat audioFormat;

	enum SLPBIndexMode indexMode;           ///< indexing mode (for program and transport streams only)
	char indexName[MAX_NAME_SIZE];          ///< identifies the location of the index file

	int maxPrebufferSize;            ///< maximum size for pre-buffering (in bytes, use 0 for default)
	int stcOffset;                   ///< adjustment to the STC in milliseconds (a negative value results in a delay for start of presentation)

	struct SLPBRebufferControl rebufferControl;
};

/// Output stream info
struct SStreamInfo
{
    int index;                       ///< index of the stream, a value from 0 to SStatus::SMedia::streams - 1
    char name[MAX_NAME_SIZE];     	 ///< stream name, from the media itself
    struct SMediaFormat format;      ///< detailed stream parameters
};

/// Linear playback control commands

/// Enable playback
/// of a media file or stream
///\ingroup LINCTRLDEFS
enum ELPBCmd
{
     LPBCmd_PLAY = 1,                      ///< start presentation from the beginning of the file

     LPBCmd_PLAY_TIME,                     ///< start presentation from the specified time position

     LPBCmd_SEEK,                          ///< seek to specified time or percentage

     LPBCmd_FAST_FORWARD,                  ///< key frames only forward with the specified speed

     LPBCmd_FAST_BACKWARD,                 ///< key frames only backward with the specified speed

     LPBCmd_SCAN_FORWARD,                  ///< all frames forward with the specified speed

     LPBCmd_SCAN_BACKWARD,                 ///< all frames backward with the specified speed

	 LPBCmd_SET_PLAY_MODE,				   ///< play with the specified speed, direction and frame type \deprecated by Fast/Scan commands

     LPBCmd_PAUSE_ON,                      ///< pause presentation

     LPBCmd_STEP,                          ///< step to next frame, valid only while PAUSED

     LPBCmd_PAUSE_OFF,                     ///< resume a paused presentation

     LPBCmd_STOP,                          ///< stop presentation in the specified mode

     LPBCmd_NOTIFY_POSITION,               ///< Requests the specified notification upon reaching the specified position \status Not implemented for this version

     LPBCmd_CANCEL_NOTIFICATIONS,          ///< Cancel any pending notifications \status Not implemented for this version

     LPBCmd_GET_STREAM_INFO,               ///< Retrieves the SStreamInfo description of the stream with the specified index

     LPBCmd_SELECT_VIDEO_STREAM,           ///< Selects the video stream with the specified index

     LPBCmd_SELECT_AUDIO_STREAM,           ///< Selects the audio stream with the specified index

     LPBCmd_SELECT_SUBTITLE_STREAM,        ///< Selects the subtitle stream with the specified index; if the index is -1, it disables the subtitle stream

     LPBCmd_GET_VIDEO_STREAM_INFO,         ///< Retrieves the SStreamInfo description of the video stream with the specified index

     LPBCmd_GET_AUDIO_STREAM_INFO,         ///< Retrieves the SStreamInfo description of the audio stream with the specified index

     LPBCmd_GET_SUBTITLE_STREAM_INFO,      ///< Retrieves the SStreamInfo description of the subtitle stream with the specified index

     LPBCmd_GET_STREAM_SET_INFO,           ///< Retrieves the SLPBStatus_MediaInfo description of the stream set  with the specified 0-based index

     LPBCmd_SELECT_STREAM_SET,             ///< Selects the stream set with the specified 0-based index

     LPBCmd_REBUFFER,                      ///< pause presentation and starts rebuffering
};

/// Stream set information

/// A stream set is a collection of related streams that share the same timing information.
/// Example: a program in MPEG Transport Stream.
///
/// A media may contain one or more stream sets.
struct SLPBStatus_MediaInfo
{
        char uri[MAX_URI_SIZE];            	  ///< optional media URI
        char name[MAX_NAME_SIZE];          	  ///< optional media name, from the media itself
        long clockTickN;                      ///< duration of media clock tick, in N/M seconds, or -1 if unknown
        long clockTickM;                      ///< duration of media clock tick, in N/M seconds, or -1 if unknown
        int duration;                         ///< media playback length in media clock ticks, or -1 if unknown
        struct SMediaFormat format;           ///< media format (input) info

		int streams;                          ///< number of streams in media available for output
		int video_streams;
		int audio_streams;
		int subtitle_streams;

		int bitrate;                          ///< total bitrate, or -1 if unknown
};


struct SLPBStatus
#ifdef __cplusplus
: public SStatus
{
#else
{
    struct SStatus common;  ///< basic status info, common to any control object
#endif

	struct SLPBStatus_MediaInfo media; /// description of the currently playing stream set

    struct SStreamInfo video;     ///< currently playing video stream
    struct SStreamInfo audio;     ///< currently playing audio stream
	struct SStreamInfo subtitle;  ///< currently playing subtitle stream

	int indexCreationProgress;    ///< progress of index creation process (0 - 100)

	struct
	{
		unsigned count;			///< number of streams sets available in the media
		unsigned current;		///< 0-based index of the currently playing stream set (the one described in the media() field)
	}
	streamSets;				///< description of the available and current stream sets. This field may be invalid if the media has only one stream set.

	struct
	{
		UINT64 start;			///< Time Shift Buffer start index value
		UINT64 end;				///< Time Shift Buffer end index value
		UINT64 current;			///< index value at the current playback position in the Time Shift Buffer
	}
	timeShiftBuffer;		///< information about the current state of the Time Shift Buffer
};

/// Identifies the method for Seek
enum ESeekMode
{
    SM_BY_TIME= 0,		///< by absolute media time
    SM_BY_OFFSET,		///< by relative media position
    SM_BY_PERCENTAGE,	///< by absolute media position described as percentage of the entire data
};

///\ingroup LINCTRLDEFS

/// Linear playback command structure.
struct SLPBCommand
#ifdef __cplusplus
: public SCommand
{
#else
{
    struct SCommand common; ///< basic command info, common to any control object
#endif

    enum ELPBCmd cmd;  ///< command code

    /// first command parameter
    union
    {
        int playMode;               ///< play mode specified with /ref PMODE
        enum EStopMode stopMode;    ///< identifies the behavior upon stopping
		enum ESeekMode seekMode;	///< identifies method of seeking
        int scanOnOff;              ///< enters/leaves the SCAN mode
        int reverseOnOff;           ///< enters/leaves the reverse playback mode
//        struct SNotification note;  ///< notification details, refers to position in param2
        int streamIndex;            ///< identifies the stream by index into the media list ( a value from 0 to SStatus::SMedia::streams - 1)
        int streamSetIndex;         ///< identifies the stream set by index into the stream set list ( a value from 0 to SStatus::streamSets::count - 1)
    }
    param1;

    /// second command parameter
    union
    {
    	struct SMediaTime time;			///< media time position for #SM_BY_TIME seek mode
        UINT64 offset;           	    ///< media file position offset for #SM_BY_OFFSET seek mode
		int percentage;					///< media file position, in percentage of the entire data, for #SM_BY_PERCENTAGE seek mode
        int speed;                 		///< playback speed in nominal speed/1024 units
    }
    param2;
};

///\ingroup LINCTRLDEFS

/// Linear playback result definition
struct SLPBResult
#ifdef __cplusplus
: public SResult
{
#else
{
    struct SResult common; ///< basic result info, common to any control object
#endif

    union
    {
		struct SStreamInfo streamInfo; ///< stream information in reply to a #LPBCmd_GET_STREAM_INFO command
		struct SLPBStatus_MediaInfo media; /// stream set description in reply to a #LPBCmd_GET_STREAM_SET_INFO command
    }
    value;
};


#endif //_MDEFS_LPB_
