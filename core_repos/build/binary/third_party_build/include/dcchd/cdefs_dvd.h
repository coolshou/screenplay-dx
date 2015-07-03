/*****************************************
 Copyright  2005  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   cdefs_dvd.h
  @brief  DVD definitions shared with middleware clients
  
  @author Sorin Papuc
  @date   2005-10-18
  
  $Log: cdefs_dvd.h,v $
  Revision 1.66  2007-07-26 00:06:44  dnguyen
  BugId:ct-3657
  added DVDCmd_Numeric_Button_Select_And_Activate

  Revision 1.65  2007/06/27 23:31:28  dnguyen
  BugId:ct-3404
  added video attributes to title info

  Revision 1.64  2007/05/16 23:32:53  sorinp
  doc

  Revision 1.63  2007/05/08 19:29:41  sorinp
  BUGCT:3208 - 3213 Added stopMode parameter to Stop command in all media spaces to allow client module to control behavior

  Revision 1.62  2007/02/20 23:32:32  sorinp
  doc updates

  Revision 1.61  2007/02/20 20:12:26  sorinp
  doc update

  Revision 1.60  2007/02/20 18:17:11  sorinp
  doc improvements

  Revision 1.59  2007/02/20 17:42:23  sorinp
  doc - replace link with textual reference since the implementation class itself is not included in the docuemntation.

  Revision 1.58  2007/02/17 00:11:45  sbeysserie
  Use NO_BLUE/NO_RED_SUPPORT flags instead of lite/core_documentation when
  generating documentation with Doxygen
  Make input files more readable in Doxygen's configuration files.

  Revision 1.57  2007/02/16 02:16:49  sbeysserie
  Deactivate reference to CCddaNavigator and CDvdNavigator when generating
  the DCCHD Core documentation.

  Revision 1.56  2007/02/14 04:21:30  sorinp
  Doc upgrade

  Revision 1.55  2006/12/16 02:59:35  sorinp
  Merged with the version_1_0 branch (at RC34 level)

  Revision 1.54.6.1  2006/12/12 17:32:44  sorinp
  Removed change doc tags in prepearation for the official 1.0.0 release

  Revision 1.54  2006/11/01 23:27:30  sorinp
  doc

  Revision 1.53  2006/10/13 20:22:48  sorinp
  Moved the userTimeout and mode fields from LPB to generic status in order to allow single-point processing of the status in CPlaybackControl

  Revision 1.52  2006/10/06 00:09:15  sorinp
  Replaced bool with int as bool has different sizes in C and C++, making possibly nasty mismatches

  Revision 1.51  2006/10/05 23:33:35  dnguyen
  added a boolean in initial settings to specify whether the intial subtitle should be displayed or not (requires curacao 142)

  Revision 1.50  2006/09/26 03:03:54  sorinp
  Updated to B.6.0 level

  Revision 1.49  2006/09/24 03:37:07  sorinp
  Working Media UIN for VFS-based access, propagated API changes

  Revision 1.48  2006/09/07 20:16:39  sorinp
  doc

  Revision 1.47  2006/09/07 00:57:21  dnguyen
  added TopMenu title type

  Revision 1.46  2006/08/31 21:59:23  dnguyen
  added supported for reverse i-frame step command

  Revision 1.45  2006/08/31 02:44:09  sorinp
  used strong type for menu existence

  Revision 1.44  2006/08/31 01:31:10  dnguyen
  added support for menu availability in title status (requires curacao 136)

  Revision 1.43  2006/08/30 18:53:17  sorinp
  Changed the statistics info definition and moved the filed from the LPB into the generic media space

  Revision 1.42  2006/07/29 01:38:57  sorinp
  Removed doc change notes older than B.2.0

  Revision 1.41  2006/07/28 22:57:22  dnguyen
  removed scaling modes from title info

  Revision 1.40  2006/07/28 20:43:36  sorinp
  Updated scaling mode info syntax, added test display support

  Revision 1.39  2006/07/25 02:17:34  dnguyen
  made sure scaling mode availablities are sent prior to ReallocSubstream video

  Revision 1.38  2006/07/13 02:08:52  dnguyen
  audio/spu stream index is set to -1 in status if none is available

  Revision 1.37  2006/07/07 01:50:38  dnguyen
  availability of PS and LB in status

  Revision 1.36  2006/06/27 19:33:19  sorinp
  Upgraded doc to B.2.0 level

  Revision 1.35  2006/06/15 23:26:32  dnguyen
  more initial settings to be passed through CDvdNavigator::Open()

  Revision 1.34  2006/06/09 00:12:56  sorinp
  Changed region code setting method

  Revision 1.33  2006/04/26 20:40:16  dnguyen
  fixed typo

  Revision 1.32  2006/04/26 20:27:43  sorinp
  Added play item end action support
  Added chapter status and query support

  Revision 1.31  2006/04/25 05:10:26  sorinp
  doc upgrades

  Revision 1.30  2006/04/19 04:23:36  mfedoreanu
  moved Media time from specific format status to common status

  Revision 1.29  2006/03/20 23:54:14  dnguyen
  feature implementation status

  Revision 1.28  2006/03/19 00:32:41  sorinp
  mostly doc, some spec updates

  Revision 1.27  2006/03/09 02:57:55  dnguyen
  removed redundant isSequential from title status info (type already has that info)
  added title duration

  Revision 1.26  2006/02/17 20:38:54  sorinp
  removed the /change tags to start clean for the enxt release

  Revision 1.25  2006/02/10 03:18:45  dnguyen
  removed hasMenu from Volume status info

  Revision 1.24  2006/01/30 02:46:12  sorinp
  Clarified media sapce - media type correspondence

  Revision 1.23  2005/12/09 15:53:26  sorinp
  doc and small spec changes

  Revision 1.22  2005/12/08 07:33:53  sorinp
  added ig, pg and menu mode flags

  Revision 1.21  2005/12/05 06:42:26  sorinp
  added audio and spu stream counters

  Revision 1.20  2005/12/05 02:00:02  sorinp
  typoRobert:
-	chapter search (PRA reports problems in last versions)

Sorin P
- 
  

  Revision 1.19  2005/11/29 00:31:05  sorinp
  changed media time definition from clock ticks to H,M,S,frames

  Revision 1.18  2005/11/16 00:05:47  dnguyen
  changed all bool struct members to int because the difference between mips
  C compiler (where bool is 32-bit) and C++ compiler (bool is 8-bit) can be
  catastrophic

  Revision 1.17  2005/11/12 02:37:07  sorinp
  syntax fix

  Revision 1.16  2005/11/12 00:13:27  dnguyen
  modified REPEAT command implementation

  Revision 1.15  2005/11/03 13:13:17  mfedoreanu
  Moved some structs defs outside

  Revision 1.14  2005/11/03 03:38:29  sorinp
  enabled time play command, it seems to be implemented!

  Revision 1.13  2005/11/02 05:00:45  sorinp
  Updates - changed time units in h:m:s:frames !

  Revision 1.12  2005/11/02 01:34:Robert:
-	chapter search (PRA reports problems in last versions)

Sorin P
- 
  26  sorinp
  Added QuesryTitle cmd
  Clarified title numbering (1-99)
  Added title type enumeration for clarity
BDRE
  Revision 1.11  2005/10/29 01:42:37  dnguyen
  added STEP command

  Revision 1.10  2005/10/28 00:22:05  dnguyen
  completed command handling and status notifications

  Revision 1.9  2005/10/27 23:33:38  dnguyen
  added Play command and 2nd parameter for Subpicture_Stream_Change

  Revision 1.8  2005/10/27 01:15:50  dnguyen
  fixed name of header file

  Revision 1.7  2005/10/26 19:15:50  sorinp
  reorganized media spece identifiers

  Revision 1.6  2005/10/26 19:06:30  sorinp
  doc typo

  Revision 1.5  2005/10/26 19:05:12  sorinp
  typo

  Revision 1.4  2005/10/26 18:06:52  sorinp
  Draft version

  Revision 1.3  2005/10/25 23:07:06  sorinp
  typo

  Revision 1.2  2005/10/25 02:25:16  sorinp
  work in progrress

  Revision 1.1  2005/10/18 18:03:32  sorinp
  initial CDDA, VCD and DVD control definitions
  Cleaned-up DVD-VR control definitions, work in progress

*/

#ifndef _CDEFS_DVD_H_
#define _CDEFS_DVD_H_

#include <cdefs.h>
// not currently used, using proprietary definitions below instead #include "mdefs_dvd.h"
#include <rmdvdtypes/dvdtypes.h>  // !!! Proprietary !!! - reuse Curacao definitions

///\defgroup DVDMSDEFS DVD Media Space Definitions
/// Definitions for media with #TMediaType of #MTYPE_APP_DVD
///\ingroup MEDSPACES

///\defgroup DVDCTRLDEFS DVD Control Definitions
/// Control definitions for media with #TMediaType of #MTYPE_APP_DVD
///
/// DVD initial settings can be set at run-time only through the format-specific parameter of
/// IPlaybackControl::OpenMedia().
///\ingroup DVDMSDEFS
///@{
#define MEDIA_SPACE_DVD           5  ///< DVD media space, to identify SDVDCommand, SDVDStatus and SDVDResult structures \ingroup MSID 

///@}

/// DVD-specific command values
///
///\ingroup DVDCTRLDEFS
enum EDVDCmd
{
    DVDCmd_first_uo = 1,             ///< first valid uo value, can be used to test validity
    DVDCmd_Play = DVDCmd_first_uo,   ///< Starts playback from the last position if possible, otherwise as defined in FirstPlay
    DVDCmd_Title_Play,               ///< Starts playback of the Title number (1-99) specified in SDVDCommand::param1::selector; the action SDVDCommand::param3::endAction will be performed upon title termination
    DVDCmd_PTT_Play,                 ///< Starts playback of the Title number (1-99) specified in SDVDCommand::param1::selector at the PTT specified in SDVDCommand::param2::selector; the action SDVDCommand::param3::endAction will be performed upon chapter termination
    DVDCmd_Time_Play,                ///< Starts playback of the Title number (1-99) specified in SDVDCommand::param1::selector at the Time specified in SDVDCommand::param2::time (h, m, s, frames) \status Not implemented for this version
    DVDCmd_Stop,                     ///< see J.1.4, behavior specified in SDVDCommand::param1::stopMode \change Added stop mode parameter 5-8-2007
    DVDCmd_GoUp,                     ///< see J.1.5
    DVDCmd_Time_Search,              ///< Starts playback of the current title at the Time specified in SDVDCommand::param2::time
    DVDCmd_PTT_Search,               ///< Starts playback of the current title at the PTT specified in SDVDCommand::param1::selector (1-999)
    DVDCmd_PrevPG_Search,            ///< see J.1.8
    DVDCmd_TopPG_Search,             ///< see J.1.9
    DVDCmd_NextPG_Search,            ///< see J.1.10
    DVDCmd_Forward_Scan,             ///< Starts playback in forward direction of type SDVDCommand::param2::selector (smooth = 0/scan = #PLAY_MODE_KEY) and with speed specified in SDVDCommand::param1::speed
    DVDCmd_Backward_Scan,            ///< Starts playback in backward direction of type SDVDCommand::param2::selector (smooth = 0/scan = #PLAY_MODE_KEY) and with speed specified in SDVDCommand::param1::speed
    DVDCmd_Menu_Call,                ///< Calls the PGC of the menu specified in SDVDCommand::param1::menuID
    DVDCmd_Resume,                   ///< Resumes the playback after a EDVDCmd::DVDCmd_Menu_Call operation
    DVDCmd_Upper_Button_Select,      ///< see J.1.15
    DVDCmd_Lower_Button_Select,      ///< see J.1.16
    DVDCmd_Left_Button_Select,       ///< see J.1.17
    DVDCmd_Right_Button_Select,      ///< see J.1.18
    DVDCmd_Button_Activate,          ///< see J.1.19
    DVDCmd_Button_Select_And_Activate, ///< Select and activate the button specified in SDVDCommand::param1::selector
    DVDCmd_Still_Off,                ///< see J.1.21
    DVDCmd_Pause_On,                 ///< see J.1.22
    DVDCmd_Pause_Off,                ///< see J.1.23
    DVDCmd_Menu_Language_Select,     ///< selects the language with code specified in SDVDCommand::param1::language
    DVDCmd_Audio_Stream_Change,      ///< selects the audio stream with number specified in SDVDCommand::param1::selector 
    DVDCmd_Subpicture_Stream_Change, ///< selects the subpicture stream with number specified in SDVDCommand::param1::selector and whether the subpicture should be displayed or not with SDVDCommand::param2::spuDisplay
    DVDCmd_Angle_Change,             ///< selects the angle with number specified in SDVDCommand::param1::selector (1-8 or 0 for "disaled")
    DVDCmd_Parental_Level_Select,    ///< selects the parental level with number specified in SDVDCommand::param1::level 
    DVDCmd_Parental_Country_Select,  ///< selects the country with code specified in SDVDCommand::param1::country
//?    DVDCmd_Audio_Mode_Change,        ///< changes the audio mixing mode to that specified in SDVDCommand::param1::audioMode
    DVDCmd_Video_Mode_Change,        ///< changes the display mode to that specified in SDVDCommand::param1::videoMode
    
    DVDCmd_Config_Audio_Language,       ///< Sets the initial audio language and extension to that specified in SDVDCommand::param1::iniLCD
    DVDCmd_Config_Subpicture_Language,  ///< Sets the initial subpicture language and extension to that specified in SDVDCommand::param1::iniLCD
//    DVDCmd_Config_Region_Code,          ///< Sets the player region code to that specified in SDVDCommand::param1::region
        
    DVDCmd_Query_BookmarkSize,        ///< retrieves in SDVDResult::info::size the size of the storage needed by a bookmark
    DVDCmd_Query_Bookmark,            ///< retrieves in SDVDCommand::param1::bookmarkBuf the bookmark for the current position
    DVDCmd_Resume_Bookmark,           ///< resumes playback from bookmark specified in SDVDCommand::param1::bookmarkBuf

    DVDCmd_Repeat,                   ///< enters the repeat mode specified in SDVDCommand::param1::repeat
    DVDCmd_Step,                     ///< frame stepping (only available in paused mode)
    DVDCmd_Backward_Step,            ///< reverse frame stepping (only available in paused mode)

    DVDCmd_QueryTitle,               ///< retrieves in SDVDResult::info::title the info for title number number (1-99) specified in SDVDCommand::param1::selector
    DVDCmd_QueryChapter,             ///< retrieves in SDVDResult::info::chapter the info for chapter number specified in SDVDCommand::param2::selector from title number number (1-99) specified in SDVDCommand::param1::selector
    DVDCmd_QueryTXTDT,               ///< retrieves in SDVDResult::info::TXTDT the TXTDT info for title number number (1-99) specified in SDVDCommand::param2::selector in language specified in SDVDCommand::param1::language
    DVDCmd_QuerySPRMs,               ///< retrieves in SDVDResult::info::SPRMs the SPRM registers
    DVDCmd_QueryGPRMs,               ///< retrieves in SDVDResult::info::GPRMs the GPRM registers

    DVDCmd_Numeric_Button_Select_And_Activate, ///< Select and activate the "user" button specified in SDVDCommand::param1::selector ("user" button number is entered by the user using the numeric keys on the remote control, it's different than the button number as defined by navigation data used with Button_Select_And_Activate) \change Added 2007/07/25
};

///\defgroup SDVDFLAGS DVD status flags
/// Constants identifying individual DVD status fields and events. Used in addition to \ref SFLAGS
///\ingroup DVDCTRLDEFS
//@{

#define SDVDSTATUS_VIDEO     (SSTATUS_LAST_GENERIC << 1)	///< identifies the video field; events are triggered when the field changes

#define SDVDSTATUS_AUDIO     (SSTATUS_LAST_GENERIC << 2)	///< identifies the audio field; events are triggered when the field changes

#define SDVDSTATUS_SPU       (SSTATUS_LAST_GENERIC << 3)	///< identifies the spu field; events are triggered when the stream parameters change

#define SDVDSTATUS_ANGLE     (SSTATUS_LAST_GENERIC << 4)	///< identifies the angle field; events are triggered when the angle changes

#define SDVDSTATUS_CHAPTER   (SSTATUS_LAST_GENERIC << 5)	///< identifies the chapter field; events are triggered when the chapter changes

#define SDVDSTATUS_VOLUME    (SSTATUS_LAST_GENERIC << 6)	///< identifies the volume field; events are triggered when the volume changes

#define SDVDSTATUS_TITLE     (SSTATUS_LAST_GENERIC << 7)	///< identifies the title field; events are triggered when the title changes

#define SDVDSTATUS_PERMISSIONS     (SSTATUS_LAST_GENERIC << 8)	///< identifies the permissions field; events are triggered when permissions change

#define SDVDSTATUS_SCALING_MODE    (SSTATUS_LAST_GENERIC << 9)	///< identifies the scaling mode field; events are triggered when scaling mode availabilities change

///@}

///\defgroup DVDMFLAGS DVD specific flags for playback mode description
/// Constants identifying individual playback modes, used in the SDVDStatus::mode::flags field. Used in addition to \ref MFLAGS
///\ingroup DVDCTRLDEFS 
///@{
#define SDVDSTATUS_MODE_STILL               (SSTATUS_MODE_LAST << 1)    ///< playback stilled, will resume automatically or by still-off UO

#define SDVDSTATUS_MODE_STILL_INFINITE      (SSTATUS_MODE_LAST << 2)    ///< playback stilled indefinitelly, must use still-off UO to resume

#define SDVDSTATUS_MODE_SPU_ON              (SSTATUS_MODE_LAST << 3)    ///< if set sub-pictures are enabled, otherwise they are disabled

#define SDVDSTATUS_MODE_REPEAT_CHAPTER      (SSTATUS_MODE_LAST << 4)    ///< if set, current chapter will be repeated forever

#define SDVDSTATUS_MODE_REPEAT_TITLE        (SSTATUS_MODE_LAST << 5)    ///< if set, current title will be repeated forever

#define SDVDSTATUS_MODE_REPEAT_AB           (SSTATUS_MODE_LAST << 6)    ///< if set, current title will be repeated forever between two points

#define SDVDSTATUS_MODE_REPEAT_AB_PENDING   (SSTATUS_MODE_LAST << 7)    ///< if set, the starting point of #DVD_REPEAT_AB mode has been set but not the ending point

#define SDVDSTATUS_MODE_REPEAT_MASK         (SDVDSTATUS_MODE_REPEAT_CHAPTER | SDVDSTATUS_MODE_REPEAT_TITLE | SDVDSTATUS_MODE_REPEAT_AB | SDVDSTATUS_MODE_REPEAT_AB_PENDING)

#define SDVDSTATUS_MODE_MENU_ACTIVE         (SSTATUS_MODE_LAST << 8)    ///< if set, one or more navigation buttons are active (regardless of the current domain)

///@}

/// DVD initial settings
struct SDVDInitialSettings
{
	int region;							///< the player's region code (0 through 6, 0 is region-free)
	int menuLanguageCode;				///< language to be used in menu presentation (ISO-639, e.g. 0x656e for en:English)
	int initialAudioLanguageCode;		///< initial language for audio (ISO-639)
	int initialSubtitleLanguageCode;	///< initial language for subtitle (ISO-639 or 0 for none)
	int countryCode;					///< country code for parental management (ISO3166, e.g. 0x5553 for US)
	int parentalLevel;					///< parental settings (0 through 8, 0 for no parental management)
	int (*verificationCallback) (int level, void *context);	///< callback for the application to verify parental password (the callback to return 0 if the password does not match)
	void *verificationContext;			///< application specific context to be used with verificationCallback
	int initialSubtitleDisplay;			///< whether the subtitle specified by initialSubtitleLanguageCode should be displayed by default 
};

/// DVD title type values
enum EDVDTitleType
{
    TT_FirstPlay = 1,					///< FP_PGC domain
    TT_Top_Menu,						///< the title/menu is from VMGM domain 
    TT_Menu,							///< the title/menu is from VTSM domain 
    TT_Sequential_Title,				///< the title is from VTS_TT domain and playback type is sequential
    TT_Random_Title						///< the title is from VTS_TT domain and playback type is random or shuffle
};

/// DVD title status information definition
struct SDVDTitle 
{
    enum EDVDTitleType type;            ///< title type
    int number;                         ///< title number (1-99)
    int duration;                       ///< length of title in seconds
    int angles;                         ///< number of angles available in the title
    int chapters;                       ///< number of chapters (title parts) available in the title
    int audios;							///< number of available audio streams available in the title
    RMdvdAudioStreams audioStreams;     ///< table of audio streams available in the title
    int spus;							///< number of SPU streams available in the title
    RMdvdSubPictureStreams spuStreams;  ///< table of SPU streams available in the title
    RMdvdMenuExistence menus;			///< bit mask specifying which menus are available
	RMdvdVideoStream videoStream;       ///< attributes of video stream (\change Added 2007/06/22)
};

/// DVD title status information definition
struct SDVDChapter 
{
    int number;                         ///< chapter number (1-999)
    struct SMediaTime startTime;        ///< chapter start time
    struct SMediaTime duration;         ///< length of chapter
};

/// DVD Repeat Modes
enum EDVDRepeatMode
{
    DVD_REPEAT_NONE = 0,    ///< no repeat
    DVD_REPEAT_CHAPTER = 1, ///< repeat current chapter
    DVD_REPEAT_TITLE = 2,   ///< repeat current title
    DVD_REPEAT_AB = 3       ///< repeat between 2 user-defined positions, the command needs to be called twice: first to set the starting position (at the current position) and then the ending position
};

/// Status info structure for the DVD control object (navigator)

/// Status information is contained in the PSR registers is not duplicated in explicit status fields,
/// rather the register must be queried
///
/// Uses \ref SDVDFLAGS values in addition to the generic \ref SFLAGS and \ref SLPBFLAGS
///\ingroup DVDCTRLDEFS
struct SDVDStatus 
#ifdef __cplusplus
                : public SStatus
{
#else
{
    struct SStatus common;  ///< basic status info, common to any control object
#endif
    
    RMdvdVideoMode video;       	///< current video stream attributes
    int audio;                  	///< current audio stream - index into SDVDStatus::title::audioStreams::audioStreams table (or -1 if no audio)
    int spu;                    	///< current SPU stream - index into SDVDStatus::title::audioStreams::subPictureStreams table (or -1 if no spu)
    int angle;                  	///< current angle number
    struct SDVDChapter chapterInfo;	///< current chapter info
    
    /// volume information
    struct SVolume
    {
        int setSize;        ///< number of volumes in set
        int number;         ///< number of this volume
        char providerID[32];///< Provider ID
        char posCode[8];    ///< UPC/EAN/JAN code
        int discSide;       ///< Side A (1), B (2)
        int hasFirstPlay;   ///< non-zero if autoplay is enabled on disc
        int titles;         ///< number of available titles;
    }
    volume;
    
    struct SDVDTitle title; ///< current title info
  
    RMdvdValidUOPFlag permissions; ///< flags indicating which User Ops are currently permitted      

	/// scaling mode info
	struct
	{
	    int letterboxAvail;					///< whether letterbox mode is allowed
	    int panscanAvail;					///< whether pan&scan mode is allowed
	}
	scaling_mode;
};


///\ingroup DVDCTRLDEFS

/// DVD specific command definition
struct SDVDCommand
#ifdef __cplusplus
                    : public SCommand
{
#else
{
    struct SCommand common;  ///< basic command info, common to any control object
#endif
    enum EDVDCmd cmd;

    /// first command parameter
    union
    {
        int selector;                ///< title, button, stream, angle etc selector; -1 for default value
        RMdvdLanguageCode language;  ///< language selector
        RMdvdCountryCode country;    ///< country selector
        RMdvdParentalLevel level;    ///< parental level selector
        RMdvdRegionCode region;      ///< region code
        RMdvdMenuId menuID;          ///< ID of the menu to call
        RMdvdVideoMode videoMode;    ///< video configuration mode
//      ? audioMode;                 ///< audio karaoke mode
        enum EDVDRepeatMode repeat;  ///< repeat mode
        struct
        {
            RMdvdLanguageCode langCode;
            int langCodeExt;      ///< Annex B values
        }
        iniLCD;                      ///< initial language code
        char *bookmarkBuf;           ///< buffer for bookmark data
        RMdvdPlaylistItem item;      ///< play-list item
        int speed;                   ///< playback speed in nominal speed/1024 units
        enum EStopMode stopMode;    ///< identifies the behavior upon stopping \status TBI
    }
    param1;
    
    /// second command parameter
    union
    {
        int selector;               ///< PTT etc selector; -1 for default value
        struct SMediaTime time;     ///< media position (h, m, s, frames)
        int spuDisplay;             ///< whether the subpicture should be displayed (non-zero) or not (zero)
    }
    param2;     
    
    /// 3rd command parameter
    union
    {
		enum EPlayItemEndAction endAction;
    }
    param3;     
};

///\ingroup DVDCTRLDEFS

/// DVD specific result definition
struct SDVDResult 
#ifdef __cplusplus
                  : public SResult
{
#else
{
    struct SResult common;  ///< basic result info, common to any control object
#endif
    /// DVD specific result value
    union
    {
        int size;               	///< returned buffer size
        struct SDVDTitle title; 	///< returned title info
        struct SDVDChapter chapter;	///< returned chapter info
        RMdvdTitleTXTDT TXTDT;  	///< title text info
        RMdvdSPRMs SPRMs;       	///< snapshot of SPRM register file
        RMdvdGPRMs GPRMs;       	///< snapshot of GPRM register file
    }
    info;
};

/// \class DCCHD_DVD::CDvdNavigator
/// Playback control class for DVD-Video media
///
/// The interface to this class is completely defined by \ref DVDMSDEFS and DCCHD::IPlaybackControl
/// \ingroup controlimpl

#ifdef __DOC__
/// DVD-Video specific code
namespace DCCHD_DVD
{
}
#endif


#endif // _CDEFS_DVD_H_
