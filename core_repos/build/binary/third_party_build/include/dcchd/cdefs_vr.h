/*****************************************
 Copyright  2005  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   cdefs_vr.h
  @brief  DVD-VR definitions shared with middleware clients
  
  @author Sorin Papuc
  @date   2005-06-01
  
  $Log: cdefs_vr.h,v $
  Revision 1.62  2007-05-17 11:47:31  isarkany
  Added Step Backward

  Revision 1.61  2007/05/16 22:06:24  sorinp
  BUGCT:3206 Added backward step command specification

  Revision 1.60  2007/05/15 03:29:28  sorinp
  typo

  Revision 1.59  2007/05/15 03:24:25  sorinp
  Completion to the bookmark API

  Revision 1.58  2007/05/15 01:36:03  sorinp
  BUGCT:3254 Defined bookmark API

  Revision 1.57  2007/05/08 19:29:41  sorinp
  BUGCT:3208 - 3213 Added stopMode parameter to Stop command in all media spaces to allow client module to control behavior

  Revision 1.56  2007/03/12 19:06:45  isarkany
  Added VRCmd_Query_PG_Cell and VRCmd_Query_PL_Cell

  Revision 1.55  2007/02/22 09:39:05  isarkany
  Added new status info for EP and fixed some result bugs for EP. BUGCT:2504

  Revision 1.54  2007/02/20 23:32:32  sorinp
  doc updates

  Revision 1.53  2007/02/20 20:12:26  sorinp
  doc update

  Revision 1.52  2007/02/14 04:21:30  sorinp
  Doc upgrade

  Revision 1.51  2007/01/26 03:42:15  sbeysserie
  Fixed typos resulting in errors with Doxygen

  Revision 1.50  2007/01/24 13:13:44  isarkany
  Added support, on Sharp's request for VRCmd_Skip_To_Current

  Revision 1.49  2007/01/18 00:31:50  sorinp
  Added presentation time in the Entry Point info that can be retieved

  Revision 1.48  2006/12/16 02:59:35  sorinp
  Merged with the version_1_0 branch (at RC34 level)

  Revision 1.47  2006/12/07 12:39:29  isarkany
  Modified repeat to update it for the current specs.

  Revision 1.46  2006/11/27 20:25:41  sorinp
  Spec and doc

  Revision 1.44  2006/10/13 20:22:48  sorinp
  Moved the userTimeout and mode fields from LPB to generic status in order to allow single-point processing of the status in CPlaybackControl

  Revision 1.43  2006/09/26 03:06:21  sorinp
  Updated to B.6.0 level

  Revision 1.42  2006/09/24 03:37:07  sorinp
  Working Media UIN for VFS-based access, propagated API changes

  Revision 1.41  2006/08/30 18:53:17  sorinp
  Changed the statistics info definition and moved the filed from the LPB into the generic media space

  Revision 1.40  2006/08/22 19:49:40  sorinp
  doc

  Revision 1.39  2006/08/10 07:25:17  isarkany
  - Added VRCmd_Repeat
  - Added some other playback handling stuff
  - There is now a Repeat A-B functionality

  Revision 1.38  2006/08/04 01:35:57  isarkany
  - Added command VRCmd_Play

  Revision 1.37  2006/08/01 02:22:47  isarkany
  - Added Still Picture Manual playback option

  Revision 1.36  2006/07/29 03:34:39  isarkany
  Modified SVR_PTM and S_VR_VOB_ENTRY_NUM structures to fit my needs

  Revision 1.35  2006/06/01 18:47:58  isarkany
  Added duration support

  Revision 1.34  2006/05/31 19:43:42  sorinp
  Added entry point field and flag

  Revision 1.33  2006/05/31 19:32:47  sorinp
  doc fixes

  Revision 1.32  2006/04/25 05:10:26  sorinp
  doc upgrades

  Revision 1.31  2006/04/19 04:23:36  mfedoreanu
  moved Media time from specific format status to common status

  Revision 1.30  2006/03/20 19:45:16  isarkany
  Doc fix

  Revision 1.29  2006/03/19 00:32:41  sorinp
  mostly doc, some spec updates

  Revision 1.28  2006/03/01 16:45:54  isarkany
  status changes

  Revision 1.27  2006/02/17 18:14:48  sorinp
  doc fixes

  Revision 1.25  2006/01/30 02:46:22  sorinp
  Clarified media sapce - media type correspondence

  Revision 1.24  2006/01/09 18:38:21  isarkany
  small fix

  Revision 1.23  2005/12/09 15:53:21  sorinp
  doc and small spec changes

  Revision 1.22  2005/12/05 06:36:20  sorinp
  Added subpicture fields

  Revision 1.21  2005/12/05 06:23:07  sorinp
  Consolidated audio fields, propagated change

  Revision 1.20  2005/12/05 06:11:44  sorinp
  fixed status field order and identification...

  Revision 1.19  2005/11/29 10:11:22  isarkany
  typo fix

  Revision 1.18  2005/11/29 00:31:02  sorinp
  changed media time definition from clock ticks to H,M,S,frames

  Revision 1.17  2005/11/09 14:23:19  isarkany
  typo fix

  Revision 1.16  2005/11/09 11:43:48  isarkany
  Modified SVRProgram, moved video and audio attributes out of it since they are unrelated.

  Revision 1.15  2005/11/07 19:49:22  isarkany
  Small fix

  Revision 1.14  2005/11/03 13:13:17  mfedoreanu
  Moved some structs defs outside

  Revision 1.13  2005/11/02 15:03:36  isarkany
  small fixes

  Revision 1.12  2005/11/02 10:52:07  isarkany
  Integrated sorin's changes

  Revision 1.11  2005/10/26 19:15:47  sorinp
  reorganized media spece identifiers

  Revision 1.10  2005/10/19 09:32:35  isarkany
  Typo fix

  Revision 1.9  2005/10/18 18:03:38  sorinp
  initial CDDA, VCD and DVD control definitions
  Cleaned-up DVD-VR control definitions, work in progress

  Revision 1.8  2005/10/17 21:07:48  sorinp
  removed the VRCmd_Quit command as there is already the format-agnostic NAVBASE_STATS_COMMAND_TERMINATE and coresponding NAVBASE_ACTION_EXIT codes.

  Revision 1.7  2005/10/17 10:12:05  smanciulea
  adde new command: VRCmd_Quit

  Revision 1.6  2005/10/06 09:26:47  smanciulea
  - included cdefs_lpb.h from mono because of SLPBStatus
  - SStreamCodingInfo is still undefined

  Revision 1.5  2005/10/05 18:44:05  sorinp
  Mostly doc upgrades

  Revision 1.4  2005/10/05 16:50:24  isarkany
  more fixes

  Revision 1.3  2005/10/05 16:22:21  isarkany
  typo fix

  Revision 1.2  2005/09/30 10:42:54  sorinp
  updated mediaID definition

  Revision 1.1  2005/09/29 06:27:03  sorinp
  updated the file structure and started the definitions for the DVD-VR media space

*/

#ifndef _CDEFS_VR_H_
#define _CDEFS_VR_H_

#include <cdefs.h>
#include "mdefs_vr.h"	// DVD-VR media definitions

///\defgroup VRMSDEFS DVD-VR Media Space Definitions
/// Definitions for media with #TMediaType of #MTYPE_APP_DVDVR
///\ingroup MEDSPACES

///\defgroup VRCTRLDEFS DVD-VR Media Space Control Definitions
/// Control definitions for media with #TMediaType of #MTYPE_APP_DVDVR
///\ingroup VRMSDEFS
///@{
#define MEDIA_SPACE_DVD_VR           7     ///< DVD-VR media space, to identify SVRCommand, SVRStatus and SVRResult structures \ingroup MSID

///@}

///\defgroup SVRFLAGS DVD-VR status flags
/// Constants identifying individual DVD-VR status fields and events. Used in addition to \ref SFLAGS
///\ingroup VRCTRLDEFS
//@{
#define SVRSTATUS_VIDEO     	(SSTATUS_LAST_GENERIC << 1)		///< identifies the video field; events are triggered when the field changes

#define SVRSTATUS_AUDIO     	(SSTATUS_LAST_GENERIC << 2)		///< identifies the audio field; events are triggered when the field changes

#define SVRSTATUS_SPU       	(SSTATUS_LAST_GENERIC << 3)	///< identifies the spu field; events are triggered when the spu changes

#define SVRSTATUS_DISC      	(SSTATUS_LAST_GENERIC << 4)	///< identifies the disc field; events are triggered when the disc changes

#define SVRSTATUS_PROGRAM   	(SSTATUS_LAST_GENERIC << 5)	///< identifies the program field; events are triggered when the program changes

#define SVRSTATUS_PLAYLIST  	(SSTATUS_LAST_GENERIC << 6)	///< identifies the playList field; events are triggered when play-list changes

#define SVRSTATUS_ENTRY_POINT	(SSTATUS_LAST_GENERIC << 7)	///< identifies the entryPoint field; events are triggered when entry points are reached

///@}

///\defgroup VRMFLAGS DVD-VR specific flags for playback mode description
/// Constants identifying individual playback modes, used in the SBRDStatus::mode::flags field. Used in addition to \ref MFLAGS
///\ingroup VRCTRLDEFS 
///@{
#define SVRSTATUS_MODE_STILL				(SSTATUS_MODE_LAST << 1)    ///< playback stilled, will resume automatically or by still-off UO

#define SVRSTATUS_MODE_STILL_INFINITE		(SSTATUS_MODE_LAST << 2)    ///< playback stilled indefinitelly, must use still-off UO to resume

#define SVRSTATUS_MODE_SPU_ON				(SSTATUS_MODE_LAST << 3)    ///< if set sub-pictures are enabled, otherwise they are disabled

#define SVRSTATUS_MODE_REPEAT      			(SSTATUS_MODE_LAST << 4)    ///< if set, current program/playlist/pgc - whichever is valid - will be repeated forever

#define SVRSTATUS_MODE_REPEAT_AB			(SSTATUS_MODE_LAST << 5)    ///< if set, current title will be repeated forever between two points

#define SVRSTATUS_MODE_REPEAT_AB_PENDING	(SSTATUS_MODE_LAST << 6)    ///< if set, the starting point of #VR_REPEAT_AB mode has been set but not the ending point

#define SVRSTATUS_MODE_REPEAT_EP			(SSTATUS_MODE_LAST << 7)	///< if set the current EP will repeat itself

#define SVRSTATUS_MODE_REPEAT_AB_MASK		(SVRSTATUS_MODE_REPEAT_AB_PENDING | SVRSTATUS_MODE_REPEAT_AB)

///@}

/// DVD-VR-specific command values
///\ingroup VRCTRLDEFS
enum EVRCmd
{
    VRCmd_first_uo = 1,             ///< first valid uo value, can be used to test validity
    VRCmd_PG_Set_Play = VRCmd_first_uo, ///< Starts playback of a PG Set; the action SDVDCommand::param3::endAction will be performed upon title termination
    VRCmd_PG_Play,                  ///< Starts playback of the Program specified in SVRCommand::param1::selector (1-99); the action SDVDCommand::param3::endAction will be performed upon title termination
    VRCmd_PL_Play,                  ///< Starts playback of the Play-list specified in SVRCommand::param1::selector (1-99); the action SDVDCommand::param3::endAction will be performed upon title termination
    VRCmd_PG_Time_Play,             ///< Starts playback of the Program specified in SVRCommand::param1::selector (1-99) from the time specified in SVRCommand::param2::time; the action SDVDCommand::param3::endAction will be performed upon title termination
    VRCmd_PL_Time_Play,             ///< Starts playback of the Play-list specified in SVRCommand::param1::selector (1-99) from the time specified in SVRCommand::param2::time; the action SDVDCommand::param3::endAction will be performed upon title termination
    VRCmd_Forward_Scan,             ///< Starts scanning playback in forward direction with the speed specified in SVRCommand::param1::speed (in 1/1024 nominal speed) and of type SVRCommand::param2::selector (smooth = 0/scan = #LPBPLAY_MODE_KEY)
    VRCmd_Backward_Scan,            ///< Starts scanning playback in backward direction with the speed specified in SVRCommand::param1::speed (in 1/1024 nominal speed) and of type SVRCommand::param2::selector (smooth = 0/scan = #LPBPLAY_MODE_KEY)
    VRCmd_PG_EP_Play,               ///< Starts playback of the Program specified in SVRCommand::param1::selector (1-99) from the entry point specified in SVRCommand::param2::selector; the action SDVDCommand::param3::endAction will be performed upon title termination
    VRCmd_PL_EP_Play,               ///< Starts playback of the Play-list specified in SVRCommand::param1::selector (1-99) from the entry point specified in SVRCommand::param2::selector; the action SDVDCommand::param3::endAction will be performed upon title termination
    VRCmd_Stop,                     ///< Stops playback, behavior specified in SVRCommand::param1::stopMode \change Added stop mode parameter 5-8-2007
    VRCmd_Forward_Skip,             ///< Restarts playback from the next entry point
    VRCmd_Backward_Skip,            ///< Restarts playback from the previous entry point
    VRCmd_Still_Off,                ///< Releases the Still and continues playback
    VRCmd_Resume,                   ///< Restarts playback from the Resume Marker
    VRCmd_Audio_Select,             ///< Switches the audio to the stream specified by SVRCommand::param1::selector (0-1) and the channel specified by SVRCommand::param2::selector (0-3) - param2 is DM_Stereo, DM_LeftMono, DM_RightMono, DM_MixMono
    VRCmd_Sub_picture_On,           ///< Enables subpicture presentation
    VRCmd_Sub_picture_Off,          ///< Disables subpicture presentation
    VRCmd_Pause_On,                 ///< Pauses the presentation
    VRCmd_Pause_Off,                ///< Resumes a paused presentation
    
    VRCmd_Goto_Marker,              ///< In PAUSED state, advances to the position specified in SVRCommand::param1::marker and remains in PAUSED state

    VRCmd_Step,              		///< In PAUSED state, advances to the next video frame and remains in PAUSED state
    VRCmd_Backward_Step,       		///< In PAUSED state, rewind to the previous video frame and remains in PAUSED state \change Added 5-16-2007
    VRCmd_Query_PG,                 ///< Retrieves in SRResult::info::pg the details of the program specified in SVRCommand::param1::selector (1-99)
    VRCmd_Query_PL,                 ///< Retrieves in SRResult::info::pl the details of the play list specified in SVRCommand::param1::selector (1-99)
	VRCmd_Query_PG_Cell,			///< Retrieves in SVRResult::info::cell the details of the cell with index SVRCommand::param2::selector (1-999) in program SVRCommand::param1::selector (1-99) \change Added 3-12-2007
	VRCmd_Query_PL_Cell,			///< Retrieves in SVRResult::info::cell the details of the cell with index SVRCommand::param2::selector (1-999) in playlist SVRCommand::param1::selector (1-99) \change Added 3-12-2007
	VRCmd_Query_PG_EP_Info,         ///< Retrieves in SRResult::info::epInfo the information for the entry point specified in SVRCommand::param2::selector from the program specified in SVRCommand::param1::selector (1-99) \change Added 1-17-2007
    VRCmd_Query_PG_EP_Name = VRCmd_Query_PG_EP_Info,	///< Retrieves in SRResult::info::ep the name of the entry point specified in SVRCommand::param2::selector from the program specified in SVRCommand::param1::selector (1-99) \change \deprecated by EVRCmd::VRCmd_Query_PG_EP_Info 
    VRCmd_Query_PL_EP_Info,         ///< Retrieves in SRResult::info::epInfo the information for the entry point specified in SVRCommand::param2::selector from the play list specified in SVRCommand::param1::selector (1-99) \change Added 1-17-2007
    VRCmd_Query_PL_EP_Name = VRCmd_Query_PL_EP_Info,	///< Retrieves in SRResult::info::ep the name of the entry point specified in SVRCommand::param2::selector from the play list specified in SVRCommand::param1::selector (1-99) \change \deprecated by EVRCmd::VRCmd_Query_PL_EP_Info
    VRCmd_Query_Info_Size,          ///< Retrieves in SRResult::info::size the size of the text info with the index specified in SVRCommand::param1::selector
    VRCmd_Query_Info,               ///< Retrieves in SRResult::info::info the text info with the index specified in SVRCommand::param1::selector
	VRCmd_Manual_Still,				///< Enables/Disables Manual still operation SVRCommand::param1::selector (0 = Automatic, 1 = Manual)

	VRCmd_Play,						///< Resumes normal playback, previous state
	VRCmd_Repeat,					///< enters the repeat mode specified in SVRCommand::param1::repeat
	VRCmd_Skip_To_Current,	  		///< skips to the beginning of the current entry point

    VRCmd_Query_BookmarkSize,		///< retrieves in SVRResult::info::size the size of the storage needed for a bookmark \change Added 5-14-2007 \ status TBI
    VRCmd_Query_Bookmark,			///< retrieves in SVRCommand::param1::bookmarkBuf the bookmark for the current position \change Added 5-14-2007 \ status TBI
    VRCmd_Resume_Bookmark,         	///< resumes playback from bookmark specified in SVRCommand::param1::bookmarkBuf \change Added 5-14-2007 \ status TBI
};

/// DVD-VR Repeat Modes

/// Repeat mode is automatically canceled when a xxx_Play or Goto_Marker command is issued.
/// Repeating an item resets the playback mode automatically to normal (1x forward) playback.
enum EVRRepeatMode
{
    VR_REPEAT_NONE = 0,    		///< no repeat
	VR_REPEAT_ALL,		   		///< \deprecated by EVRRepeatMode::VR_REPEAT_DISC or EVRRepeatMode::VR_REPEAT_ITEM 
	VR_REPEAT = VR_REPEAT_ALL,		///< \deprecated by EVRRepeatMode::VR_REPEAT_DISC or EVRRepeatMode::VR_REPEAT_ITEM
	VR_REPEAT_DISC = VR_REPEAT_ALL,	///< repeat the entire Program Chain (programs from 0 to the end) if PG_Play is set or repeat from PL #0 to the last PL. \change Added
	VR_REPEAT_ITEM,					///< repeat the currently valid PG or PL. \change Added
    VR_REPEAT_AB,   	   		///< repeat between 2 user-defined positions, the command needs to be called twice: first to set the starting position (at the current position) and then the ending position
	VR_REPEAT_EP,	   	   		///< repeat the current EP in the current PG or PL (whichever is valid) 
};

// RTR's Date and Time describing format (4.1.2.2)
struct SVRDATE_TIME
{
    unsigned Year:14;                           ///< Year
    unsigned Month:4;                           ///< Month
    unsigned Day:5;                             ///< Day
    unsigned Hour:5;                            ///< Hour
    unsigned Minute:6;                          ///< Minute
    unsigned Second:6;                          ///< Second
};

/// DVD-VR Name info
struct SVRName
{
    char asciiName[65];             ///< max 64 ASCII characters plus ending zero
    unsigned char otherName[65];    ///< max 64 bytes plus ending zero
};

/// DVD-VR character code values
enum EVRCharCode
{
    ASCII_Set_Only = 0,
    ISO_8859_1 = 0x11,
    Shift_JIS_Kanji,
    KSC_5601,
    KSC_5700
};

/// DVD-VR text information definition
struct SVRInfo
{
    int           infoID;
    unsigned char info[256];
};

// RTR's PTM Describing format (4.2.3.3.1, p. VR4-28)
struct SVR_PTM
{
	UINT16 PTM_extension;						///< PTM extension measured by 27 MHz unit
	UINT32 PTM_base;							///< PTM base measured by 90 kHz unit
};

/// DVD-VR Entry Point information definition \change Added 1-17-2007
struct SVREPInfo
{
    int entryPoint;

	struct SVRName name;	///< name (text info) possibly associated with the entry point
	//struct SVR_PTM ptm;		///< entry point presentation time
	UINT64 mediatime;
	UINT16 S_VOB_ENTN;
};

// Still picture VOB Entry number
struct SVR_S_VOB_ENTRY_NUM
{
	unsigned char reserved[5];						///< reserved
	unsigned char S_VOB_ENTN;							///< Still Picture VOB Entry
};


/// DVD-VR Marker definition
struct SVRMarker
{
    int programChain;   ///< -1 if marker is invalid, 0 for Original PGC
    int program;
    int cell;
    union
    {
        struct SVR_PTM ptm;
        struct SVR_S_VOB_ENTRY_NUM svob_entn;
    }
    position;
    struct SVRDATE_TIME creationTime;
};

/// audio stream status
enum EVR_A_STATUS
{
    ORIGINAL_UNMODIFIED = 0,
    ORIGINAL_MODIFIED,
    DUBBING_TO_BE_DONE,
    DUBBING_DONE
};

/// DVD-VR Audio Stream definition    
struct SVRAudioStream
{
    enum EVR_A_STATUS status;       ///< stream status
    struct SVR_A_ATR attributes;    ///< stream atttributes
};

/// DVD-VR generic duration definition
struct SVR_Duration
{
    unsigned Hour:4;                            ///< Hour
    unsigned Minute:6;                          ///< Minute
    unsigned Second:6;                          ///< Second
};

/// DVD-VR cell info
struct SVRCell
{
	/// cell number
	int idx;
	/// cell type - 0 for movie cell, 1 for still picture cell
	int type;
	/// object creation time info
	struct SVRDATE_TIME create_time;
};

/// DVD-VR Play list definition
struct SVRPlayList
{
    /// play list number
    int number;
    
    /// play list type
    enum plType
    {
        VRPL_Movie = 0,
        VRPL_StillPicture,
        VRPL_Hybrid
    }
    type;

    /// play list creation time
    struct SVRDATE_TIME creationTime;
    
    /// play list Primary Text Information
    struct SVRName name;

    /// Index of the optional extra textual information, 0 if no extra info exists
    int infoIndex;
    
    ///Playlist Representative Picture (may be invalid if no picture is available)
    struct SVRMarker picture;

    /// number of Entry Points
    int entryPoints;

    /// Playlist duration
    struct SVR_Duration duration;

	/// Number of cells in the Playlist \change Added 3-12-2007
	int cellCount;

	/// Index of the currently playing cell \change Added 3-12-2007
	int crtCell;
};

/// DVD-VR Program definition    
struct SVRProgram
{
    /// program number
    int number;
    
    /// program Primary Text Information
    struct SVRName name;

    /// Index of the optional extra textual information, 0 if no extra info exists
    int infoIndex;
    
    /// program Representative Picture (may be invalid if no picture is available)
    struct SVRMarker picture;
    
    /// number of Entry Points
    int entryPoints;

    /// Program duration
    struct SVR_Duration duration;

	/// Number of cells in the Program \change Added 3-12-2007
	int cellCount;

	/// Index of the currently playing cell \change Added 3-12-2007
	int crtCell;
};

/// Status info structure for the DVD-VR control object (navigator)

/// Status information is contained in the PSR registers is not duplicated in explicit status fields,
/// rather the register must be queried
///
/// Uses \ref SVRFLAGS values in addition to the generic \ref SFLAGS and \ref SLPBFLAGS
///\ingroup VRCTRLDEFS
struct SVRStatus 
#ifdef __cplusplus
				: public SStatus
{
#else
{
    struct SStatus common;  ///< basic status info, common to any control object
#endif
    
	/// current video stream parameters
    struct SVR_V_ATR video;
    
    // available and current audio streams
    struct
    {
    	// number of available streams
    	int streams;	
    	
	    /// current audio streams parameters
	    struct SVRAudioStream streamTab[2];
	
	    /// currently playing audio stream
	    int crtStream;
    }
    audio;
        
    // available and current spu streams
    struct
    {
    	// number of available streams
    	int streams;	
    	
	    /// currently playing spu stream
	    int crtStream;
    }
    spu;
    
    /// Disc-level info
    struct SVRDisc
    {
        /// Time zone for SVRDATE_TIME values, as offset in minutes from GMT
        int timeZone;
        
        /// Character set (in addition to the ASCII one) used SVRName structures
        enum EVRCharCode nameOtherCharSet;
        
        /// Character set (in addition to the ASCII one) used by SVRInfo structures
        enum EVRCharCode infoOtherCharSet;
        
        /// Resume marker (may be invalid if no resume marker is available)
        struct SVRMarker resumeMarker;
    
        /// Disc representative picture (may be invalid if no picture is available)
        struct SVRMarker representativePicture;
        
        /// Disc Representative Name
        struct SVRName name;
        
        /// number of Programs
        int programs;
        
        /// number of available Play Lists 
        int playLists;

        /// Disc duration
        struct SVR_Duration duration;
	}
    disc;

	/// current program or part of program
    struct SVRProgram program;

    /// current play list
    struct SVRPlayList playList;

	/// last entry point reached
	struct SVREPInfo epinfo;
};

///\ingroup VRCTRLDEFS

/// DVD-VR specific command definition
struct SVRCommand
#ifdef __cplusplus
                 : public SCommand
{
#else
{
    struct SCommand common;  ///< basic command info, common to any control object
#endif
    enum EVRCmd cmd;

    /// first command parameter
    union
    {
        int selector;               ///< primary selector; -1 for default value
        int speed;                  ///< playback speed in nominal speed/1024 units
        struct SVRMarker marker;    ///< marker position
		enum EVRRepeatMode repeat;  ///< repeat mode
        enum EStopMode stopMode;    ///< identifies the behavior upon stopping \status TBI
        char *bookmarkBuf;          ///< buffer for bookmark data
    }
    param1;
    
    /// second command parameter
    union
    {
        int selector;               ///< secondary selector
        struct SMediaTime time;     ///< media position by media time, in H, M, S and frames
    }
    param2;

	/// 3rd command parameter
    union
    {
		enum EPlayItemEndAction endAction;
    }
    param3;

};

///\ingroup VRCTRLDEFS

/// DVD-VR specific result definition
struct SVRResult
#ifdef __cplusplus
                 : public SResult
{
#else
{
    struct SResult common;  ///< basic result info, common to any control object
#endif
    /// DVD-VR specific result value
    union
    {
        struct SVRProgram pg;
        struct SVRPlayList pl;
        struct SVRName ep;
		struct SVREPInfo epInfo;
        int size;
        struct SVRInfo info;
		struct SVRCell cell;
    }
    info;
};

/// \class DCCHD_DVDVR::CNavigator
/// Playback control class for DVD-VR media
///
/// The interface to this class is completely defined by \ref VRMSDEFS and DCCHD::IPlaybackControl
/// \ingroup controlimpl

#endif // _CDEFS_VR_H_
