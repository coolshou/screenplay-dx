/*****************************************
 Copyright  2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   cdefs_brd.h
  @brief  Blu-ray control definitions shared with middleware clients

  @author Sorin Papuc
  @date   2005-09-26

  $Header: /bigbig/dungeon/dcchd_project/dcchd/brd/cdefs_brd.h,v 1.148 2008-10-20 23:08:32 sorin Exp $

*/

#ifndef _CDEFS_BRD_H_
#define _CDEFS_BRD_H_

#include <cdefs.h>
#include "mdefs_brd.h"  // Blu-ray media definitions

///\defgroup BRDMSDEFS Blu-ray Media Space Definitions
/// Definitions for media with #TMediaType of #MTYPE_APP_BRD
///\ingroup MEDSPACES

///\defgroup BRDCTRLDEFS Blu-ray Control Definitions
/// Control definitions for media with #TMediaType of #MTYPE_APP_BRD
///\ingroup BRDMSDEFS
///@{
#define MEDIA_SPACE_BLU_RAY           9     ///< Blu-ray media space, to identify SBRDCommand, SBRDStatus and SBRDResult structures \ingroup MSID

#define MAX_NUMBER_OF_BRD_STREAMS   255     ///< maximum number of stream in a play item

#define BRDCMD2UOMASK(x)     ( ((x) & BRDCmd_not_maskable) ? 0 : ((UINT64)1 << (64 - (x))))  ///< macro for converting from command ID value to UO_mask_table test bit

#define ISMASKABLEBRDCMD(x)     (((x) >= 1) && ((x) <= 64))  ///< macro for checking whether a BRD command is maskable or not
///@}

///\defgroup SBRDFLAGS Blu-ray status flags
/// Constants identifying individual Blu-ray status fields and events. Used in addition to \ref SFLAGS
///\ingroup BRDCTRLDEFS
//@{
#define SBRDSTATUS_VIDEO     (SSTATUS_LAST_GENERIC << 1)   ///< validates the VIDEO field; events are triggered when the stream parameters change

#define SBRDSTATUS_AUDIO     (SSTATUS_LAST_GENERIC << 2)   ///< validates the AUDIO field; events are triggered when the stream parameters change

#define SBRDSTATUS_IG        (SSTATUS_LAST_GENERIC << 3)   ///< validates the IG field; events are triggered when the stream parameters change

#define SBRDSTATUS_PG_TS     (SSTATUS_LAST_GENERIC << 4)   ///< validates the PG_TS field; events are triggered when the stream parameters change

#define SBRDSTATUS_SEC_VIDEO (SSTATUS_LAST_GENERIC << 5)   ///< validates the SEC_VIDEO field; events are triggered when the stream parameters change

#define SBRDSTATUS_SEC_AUDIO (SSTATUS_LAST_GENERIC << 6)   ///< validates the SEC_AUDIO field; events are triggered when the stream parameters change

#define SBRDSTATUS_MEDIA_ID  (SSTATUS_LAST_GENERIC << 7)   ///< validates the MEDIA_ID field; events are triggered when the media change

#define SBRDSTATUS_UO_MASK   (SSTATUS_LAST_GENERIC << 8)   ///< validates the uo_mask_table field; events are triggered when the uo mask table changes

#define SBRDSTATUS_DISK      (SSTATUS_LAST_GENERIC << 9)   ///< validates the disc index field; events are triggered when the disc changes

#define SBRDSTATUS_TITLE     (SSTATUS_LAST_GENERIC << 10)  ///< validates the crt title field; events are triggered when the title changes

#define SBRDSTATUS_CHAPTER   (SSTATUS_LAST_GENERIC << 11)  ///< validates the crt chapter field; events are triggered when the chapter changes

#define SBRDSTATUS_PLAYLIST  (SSTATUS_LAST_GENERIC << 12)  ///< validates the crt play-list field; events are triggered when play-list changes

#define SBRDSTATUS_PLAYITEM  (SSTATUS_LAST_GENERIC << 13)  ///< validates the crt play-item field; events are triggered when the play-item changes

#define SBRDSTATUS_MARK		 (SSTATUS_LAST_GENERIC << 14)  ///< validates the lastMark field; events are triggered when a mark is reached

#define SBRDSTATUS_ANGLE     (SSTATUS_LAST_GENERIC << 15)  ///< validates the crt angle field; events are triggered when the angle changes

#define SBRDSTATUS_ROOT_CERT (SSTATUS_LAST_GENERIC << 16)  ///< validates the rootCertificate field, which is filled upon media open; no events are generated

#define SBRDSTATUS_PSR_102   (SSTATUS_LAST_GENERIC << 17)  ///< validates the psr102 field, events are triggered when PSR 102 changes

#define SBRDSTATUS_PSR_104   (SSTATUS_LAST_GENERIC << 18)  ///< validates the psr104 field, events are triggered when PSR 104 is changed by the BD+ layer (but not by the application layer)

#define SBRDSTATUS_SOUND_DATA	(SSTATUS_LAST_GENERIC << 19)	///< validates the soundDescriptor field, no events are triggered. If sound data is available, the field is validated during the OpenMedia call and remains valid throughout the rest of the session \change Added 2-8-2007

#define SBRDSTATUS_LAST_IN_TIME (SSTATUS_LAST_GENERIC << 20)	///< validates the lastIN_time field, events are triggered upon non-seamless transitions \change Added 11-20-2007

#define SBRDSTATUS_VIRTUAL_PACKAGE	(SSTATUS_LAST_GENERIC << 21)	///< validates the crtManifestFileName field, events are triggered when the Virtual Package changes or is replaced by the Disc Package \change Added 2-4-2008 in support of User Expandable Persistent Storage

///@}

/// \internal Custom values can be added from here
/// !!! MUST UPDATE THIS VALUE EVERY TIME A NEW STATUS FLAG IS ADDED ABOVE !!!
#define SBRDSTATUS_first_after_hdmv	(SSTATUS_LAST_GENERIC << 21)


// for backward compatibility (prior to version 1.0.0-B.7.4)
#define SBRDSTATUS_PSR_102_CHANGE   SBRDSTATUS_PSR_102
#define SBRDSTATUS_PSR_104_CHANGE   SBRDSTATUS_PSR_104
#define SBRDSTATUS_MODE_NONSEAMLESS SSTATUS_MODE_TRANSITION	///< \deprecated by #SSTATUS_MODE_TRANSITION


///\defgroup BRDMFLAGS Blu-ray specific flags for playback mode description
/// Constants identifying individual playback modes, used in the SBRDStatus::mode::flags field. Used in addition to \ref MFLAGS
///\ingroup BRDCTRLDEFS
///@{
#define SBRDSTATUS_MODE_STILL               (SSTATUS_MODE_LAST << 1)    ///< playback stilled, will resume automatically or by still-off UO

#define SBRDSTATUS_MODE_STILL_INFINITE      (SSTATUS_MODE_LAST << 2)    ///< playback stilled indefinitelly, must use still-off UO to resume

#define SBRDSTATUS_MODE_MENU_ACTIVE         (SSTATUS_MODE_LAST << 3)    ///< if set, menu is currently displayed

#define SBRDSTATUS_MODE_POPUP_AVAILABLE     (SSTATUS_MODE_LAST << 4)    ///< if set, IG popups are available

#define SBRDSTATUS_MODE_POPUP_ON            (SSTATUS_MODE_LAST << 5)    ///< if set, IG popups are enabled

#define SBRDSTATUS_MODE_PG_TS_ON            (SSTATUS_MODE_LAST << 6)    ///< if set, subtitles are enabled

#define SBRDSTATUS_MODE_REPEAT_TTILE        (SSTATUS_MODE_LAST << 7)    ///< if set, current title will be repeated as soon as it ends

#define SBRDSTATUS_MODE_REPEAT_CHAPTER      (SSTATUS_MODE_LAST << 8)    ///< if set, current chapter will be repeated as soon as it ends

#define SBRDSTATUS_MODE_TERMINATED          (SSTATUS_MODE_LAST << 10)	///< if set in STOPPED state, playback can resume only with First Play or Title/Time Search commands; invalid in any other state than STOPPED one \change Added 5-2-2007

#define SBRDSTATUS_MODE_SEC_VIDEO_ON		(SSTATUS_MODE_LAST << 11)	///< if set, secondary video (including associated audio, i.e. PiP) is enabled \change Added 3-16-2007

#define SBRDSTATUS_MODE_SEC_AUDIO_ON		(SSTATUS_MODE_LAST << 12)	///< if set, secondary audio is enabled \change Added 3-16-2007

///@}

#define BRD_FIRST_PLAY			0xFFFF	///< Title number to be used with the #BRDCmd_title_search command to launch the First Play title

#define BRD_TITLE_MENU			0		///< Title number to be used with the #BRDCmd_title_search command to launch the menu title


/// Blu-ray-specific command values
///
/// Consist of the following categories:
///
/// - maskable user operation. They are defined in the same order as they appear in the UO_mask_table
/// structres definition, so the mask can be easily tested with #BRDCMD2UOMASK
///
/// - non-maskable user operations - those that do not appear in UO_mask_table
///
/// - functions needed by BD-J - the subset of the Annex F Functions that are not accessible as user operations
/// and are accessed by the BD-J Module. Additional commands are added to support the BD-J API specified in the org.blu-ray.* Javadoc
///
/// - additional functions needed by a GUI application (including BD-J, in fact, altough they are not identified by the spec)
///
/// Item identification - specified in HDMV spec for UOs and PSRs:
/// - int xxx_number - one-based index into a list
/// - int xxx_id - zero-based index into a list
/// - TBRDItemID xxxxx - decimal representation of the xxxxx portion of the corresponding xxxxx.yyyy file in which the item is stored (used for play lists, clips and movie and BD-J objects)
///\ingroup BRDCTRLDEFS
enum EBRDCmd
{
    /// Maskable operations, defined to match the corresponding bit in UO_mask_table definition
	BRDCmd_first_UOP = 1,			       		///< first valid User Operation code value, can be used to verify whether a command is UOP or not
	BRDCmd_menu_call = BRDCmd_first_UOP,   		///< Menu Call UO, masked through Movie Object Terminal Info
    BRDCmd_title_search,                   		///< Title Search UO, title number (#BRD_FIRST_PLAY, #BRD_TITLE_MENU or title number >= 1) in SBRDCommand::param1::selector; if the current title is BD-J and SBRDCommand::param2::selector is non-zero, HDMV files will be reloaded; the action SBRDCommand::param3::endAction will be performed upon title termination. Operation masked through Movie Object Terminal Info
    BRDCmd_chapter_search,          	   		///< Chapter Search UO, chapter number in SBRDCommand::param1::selector; the action SBRDCommand::param3::endAction will be performed upon chapter termination
    BRDCmd_time_search,                    		///< Time Search UO, time in SBRDCommand::param2::time
    BRDCmd_skip_to_next_point,             		///< Skip to Next Point UO
    BRDCmd_skip_back_to_previous_point,    		///< Skip back to previous Point UO
    BRDCmd_first_play,                     		///< First Play UO, masked through Movie Object Terminal Info
    BRDCmd_stop,                           		///< Stop UO, behavior specified in SBRDCommand::param1::stopMode \change Added stop mode parameter 5-8-2007
    BRDCmd_pause_on,                       		///< Pause On UO
    BRDCmd_pause_off,                      		///< Pause Off UO, masked through Movie Object Terminal Info
    BRDCmd_still_off,                      		///< Still Off UO
    BRDCmd_forward_play,                   		///< Forward Play UO, speed in SBRDCommand::param1::speed and of type SBRDCommand::param2::selector (smooth = 0/scan = #LPBPLAY_MODE_KEY)
    BRDCmd_backward_play,                  		///< Backward Play UO, speed in SBRDCommand::param1::speed and of type SBRDCommand::param2::selector (smooth = 0/scan = #LPBPLAY_MODE_KEY)
    BRDCmd_resume,                         		///< Resume UO
    BRDCmd_move_up_selected_button,        		///< Move Up Selected Button UO
    BRDCmd_move_down_selected_button,      		///< Move Down Selected Button UO
    BRDCmd_move_left_selected_button,      		///< Move Left Selected Button UO
    BRDCmd_move_right_selected_button,     		///< Move Right Selected Button UO
    BRDCmd_select_button,                  		///< Select Button UO, button number in SBRDCommand::param1::selector
    BRDCmd_activate_button,                		///< Activate Button UO
    BRDCmd_select_button_and_activate,     		///< Select and Activate Button UO, button number in SBRDCommand::param1::selector
    BRDCmd_primary_audio_stream_number_change,	///< Primary Audio Change UO, stream number in SBRDCommand::param1::selector
    BRDCmd_reserved1,
    BRDCmd_angle_number_change,   				///< Angle Change UO, angle number in SBRDCommand::param1::selector
    BRDCmd_popup_on,                       		///< PopUp On UO
    BRDCmd_popup_off,                      		///< PopUp Off UO
    BRDCmd_PG_textST_enable_disable_flag,	   	///< Enable/disable PG textST UO, new state in SBRDCommand::param1::selector \change Added parameter in version 2.0, changed name to avoid old use
    BRDCmd_PG_textST_stream_number_change, 		///< PG textST Change UO, stream number in SBRDCommand::param1::selector
	BRDCmd_secondary_video_enable_disable_flag,	///< Enable/disable Secondary Video Stream UO, new state in SBRDCommand::param1::selector \change Added in version 2.0
	BRDCmd_secondary_video_stream_number_change,///< Secondary Video Stream Change UO, stream number in SBRDCommand::param1::selector \change Added in version 2.0
	BRDCmd_secondary_audio_enable_disable_flag,	///< Enable/disable Secondary Audio Stream UO, new state in SBRDCommand::param1::selector \change Added in version 2.0
	BRDCmd_secondary_audio_stream_number_change,///< Secondary Audio Stream Change UO, stream number in SBRDCommand::param1::selector \change Added in version 2.0
	BRDCmd_reserved2,
	BRDCmd_PiP_PG_textST_stream_number_change,	///< PiP PG textST Change UO, stream number in SBRDCommand::param1::selector \change Added in version 2.0

    // Non-maskable operations are defined with values beyond the 64 UO_mask_table bit positions
    BRDCmd_set_ts_style = 65,                   ///< set text subtitle style number SBRDCommand::param1::selector
	BRDCmd_last_UOP, 							///< last valid User Operation code value, can be used to verify whether a command is UOP or not

    /// BD-J commands
    BRDCmd_first_bdj_func,						///< first valid BD-J specific command value, can be used to test for validity
    BRDCmd_play_pl_playitem,        			///< play PlayList with ID SBRDCommand::param3::playListID from PlayItem with ID SBRDCommand::param1::selector
    BRDCmd_play_pl_mark,                   		///< play PlayList with ID SBRDCommand::param3::playListID from mark with ID SBRDCommand::param1::selector
    BRDCmd_play_pl_time,                   		///< play PlayList with ID SBRDCommand::param3::playListID from time SBRDCommand::param2::time
    BRDCmd_skip_to_next_mark,              		///< skip to next mark of type SBRDCommand::param1::markType in the crt playlist, or error if none exists
    BRDCmd_skip_back_to_previous_mark,     		///< skip to previous mark of type SBRDCommand::param1::markType in the crt playlist, or error if none exists
    BRDCmd_still_on,                       		///< freeze playback until a Still Off UO - per F.1.2.5 in ver 0.9r3
    BRDCmd_set_menu_language,              		///< sets the Menu Language PSR with language ID SBRDCommand::param1::language
    BRDCmd_set_audio_language,			   		///< sets the Audio Language PSR with language ID SBRDCommand::param1::language
    BRDCmd_set_subtitle_language,          		///< sets the Subtitle Language PSR with language ID SBRDCommand::param1::language
    BRDCmd_get_psr,                        		///< retrieves the PSR number SBRDCommand::param1::selector
    BRDCmd_set_psr,                        		///< sets the PSR number SBRDCommand::param1::selector with value SBRDCommand::param2::regValue
    BRDCmd_get_gpr,                        		///< retrieves the GPR number SBRDCommand::param1::selector
    BRDCmd_set_gpr,                        		///< sets the GPR number SBRDCommand::param1::selector with value SBRDCommand::param2::regValue
	BRDCmd_reset_backup_registers,				///< reset the backup registers (PSR 36,37,38,39,40,42,43,44) to the initial values \change Added in version 2.0
    BRDCmd_enable_secondary_video_full_screen,	///< enables/disables the full screen display of the secondary video stream based on the value in SBRDCommand::param1::selector: 1=enable, 0=disable \change Added in version 2.0
    BRDCmd_get_meta_data_value,					///< retrieves in SBRDResult::info::metaData the current or last valid metadata value \change Added in version 2.0
	BRDCmd_get_PiP_PG_textST_valid_flag,		///< retrieves the subtitle valid flag in the SBRDResult::info::regValue field \change Added in version 2.0
	BRDCmd_set_PiP_PG_textST_valid_flag,		///< enables/disables the subtitle valid flag based on the value in SBRDCommand::param1::selector: 1=enable, 0=disable \change Added in version 2.0
    BRDCmd_last_bdj_func,        	    		///< last valid BD-J specific command value, can be used to test for validity

    /// Miscelaneous/custom commands
    BRDCmd_first_misc_func,		          		///< first valid miscellaneous command value, can be used to test for validity
    BRDCmd_play = BRDCmd_first_misc_func,       ///< Play UO (resumes playback from the last position after a Stop)
    BRDCmd_step,  								///< frame stepping (only available in paused mode)
	BRDCmd_step_back,							///< frame stepping backward (only available in paused mode)
	BRDCmd_get_title_info,                 		///< retrieves information about the title number SBRDCommand::param1::selector
	BRDCmd_get_titles_info,                		///< retrieves information about the all titles from disc; the titles will be stored in SBRDCommand::param1::privateData (type SBRDTitle[1001]); the number of titles is saved in status::disc::number_of_titles (the array will contain number_of_titles + 2 elements (it includes TopMenu and FirstPlayback)
    BRDCmd_get_pl_id,                      		///< retrieves the ID of  the playlist with title enumeration index SBRDCommand::param1::selector
    BRDCmd_get_pl_info,                    		///< retrieves information about the playlist with ID SBRDCommand::param3::playListID
	BRDCmd_get_pi_info,                   		///< retrieves information about the play item with ID SBRDCommand::param1::selector in play list with ID SBRDCommand::param3::playListID
	BRDCmd_get_pl_items_info,              		///< retrieves information about the all playItems from playlist with ID SBRDCommand::param3::playListID; the playitems will be stored in SBRDCommand::param1::privateData (type SBRDPlayItem[999]); the number of playitems is saved in result::info::playList::number_of_items
    BRDCmd_get_app_type,                    	///< retrieves in result::info::appType the application type of the clip with ID SBRDCommand::param1::itemID \change Added 6-5-2007
    BRDCmd_get_mark_info,                  		///< retrieves information about the mark with PL_mark_id SBRDCommand::param1::selector in playlist with ID SBRDCommand::param3::playListID
	BRDCmd_get_pl_marks_info,              		///< retrieves information about the all marks from playlist with ID SBRDCommand::param3::playListID; the marks will be stored in SBRDCommand::param1::privateData (type SBRDMark[999]); the number of marks is saved in result::info::playList::number_of_marks
	BRDCmd_get_chapter_info,               		///< retrieves information about the chapter number SBRDCommand::param1::selector in play list with ID SBRDCommand::param3::playListID
    BRDCmd_get_video_stream_info,          		///< retrieves information about the video stream number SBRDCommand::param1::selector in play item with ID SBRDCommand::param2::selector of play list with ID SBRDCommand::param3::playListID
    BRDCmd_get_audio_stream_info,          		///< retrieves information about the audio stream number SBRDCommand::param1::selector in play item with ID SBRDCommand::param2::selector of play list with ID SBRDCommand::param3::playListID
    BRDCmd_get_pg_ts_stream_info,          		///< retrieves information about the PG/TS stream number SBRDCommand::param1::selector in play item with ID SBRDCommand::param2::selector of play list with ID SBRDCommand::param3::playListID
    BRDCmd_get_ig_stream_info,             		///< retrieves information about the IG stream number SBRDCommand::param1::selector in play item with ID SBRDCommand::param2::selector of play list with ID SBRDCommand::param3::playListID
	BRDCmd_get_sec_video_stream_info,      		///< retrieves information about the secondary video stream number SBRDCommand::param1::selector in play item with ID SBRDCommand::param2::selector of play list with ID SBRDCommand::param3::playListID \change Added in version 2.0
    BRDCmd_get_sec_audio_stream_info,      		///< retrieves information about the secondary audio stream number SBRDCommand::param1::selector in play item with ID SBRDCommand::param2::selector of play list with ID SBRDCommand::param3::playListID \change Added in version 2.0
	BRDCmd_get_PiP_PG_textST_stream_info, 		///< retrieves information about the PiP stream number SBRDCommand::param1::selector in play item with ID SBRDCommand::param2::selector of play list with ID SBRDCommand::param3::playListID \change Added in version 2.0

    BRDCmd_set_title_end_action,   				///< perform SBRDCommand::param3::endAction upon reaching the end of the current title, can be issued only in PLAYING or PAUSE mode
    BRDCmd_stop_on_title_end = BRDCmd_set_title_end_action,		///< \deprecated by EBRDCmd::BRDCmd_set_title_end_action
    BRDCmd_set_chapter_end_action,     			///< perform SBRDCommand::param3::endAction upon reaching the end of the current chapter, can be issued only in PLAYING or PAUSE mode
    BRDCmd_stop_on_chapter_end = BRDCmd_set_chapter_end_action,	///< \deprecated by EBRDCmd::BRDCmd_set_chapter_end_action

    BRDCmd_query_bookmark_size,			        ///< retrieves in SBRDResult::info::size the size of the storage needed for a bookmark \change Added 5-14-2007 \ status TBI
    BRDCmd_query_bookmark,			            ///< retrieves in SBRDCommand::param1::bookmarkBuf the bookmark for the current position \change Added 5-14-2007 \ status TBI
    BRDCmd_resume_bookmark,         			///< resumes playback from bookmark specified in SBRDCommand::param1::bookmarkBuf \change Added 5-14-2007 \ status TBI

    BRDCmd_aacs_gateway,						///< passes the parameters pointed to by SBRDCommand::param1::privateData to the AACS provider; used by matching implementation specific AACS provider and clients \change Added 6-23-2008 for AACS online use

    BRDCmd_last_misc_func,		           		///< last valid miscellaneous command value, can be used to test for validity

    BRDCmd_first_after_hdmv,			        ///< \internal custom commands can be defined starting from this value

	BRDCmd_not_maskable = 0x1000,				///< Flag for disabling the masking of UOPs. When applied to UOPs it makes them PCFs (Playback Control Functions) that are issued by the BD-J application and are never masked by the PCE (i.e. the HDMV navigator) \change Added 5-23-2007
};

typedef UINT32 TBRDItemID;  ///< Blu-ray item ID - value of the xxxxx portion of the "xxxxx.yyyy" name of the file in which the item is stored

/// Blu-ray application type definition \change Added 6-5-2007
enum EBDAppType
{
	BDMovie = 1,
	BDTimeBasedSlideShow,
	BDBrowsableSlideShow,
};

/// HDMV title playback type definition
enum EHDMVPlaybackType
{
    HDMVSequential = 0, ///< Current Chapter Number and Elapsed Time display recommended
    HDMVInteractive,	///< Current Chapter Number and Elapsed Time display NOT recommended
	HDMVUnknown			///< Unknown HDMV playback type if there is no FirstPlayback or TopMenu
};

/// BD-J title playback type definition
enum EBDJPlaybackType
{
	BDJUnknown = 0,		///< Unknown BDJ playback type if there is no FirstPlayback or TopMenu
    BDJSequential = 2,	///< Current Chapter Number and Elapsed Time display recommended ?
    BDJInteractive		///< Current Chapter Number and Elapsed Time display NOT recommended ?
};

/// Playlist playback type definition
enum EPLPlaybackType
{
	PBSequential = 1,
	PBRandom,
	PBShuffle,
};


/// Blu-ray title information
struct SBRDTitle
{
    int title_number;         ///< title number as per HDMV 5.2.3.3 (ver 0.9r3)

    /// title type
    enum EObjectType
    {
        ObjectType_HDMV = 1,  ///< HDMV object
        ObjectType_BDJ        ///< BD-J object
    }
    objectType;

    /// title access type (table 5.4)
    enum EAccessType
    {
        TitleAccessAndDisplay = 0,    ///< Title Search UO permitted and Title number should be displayed (unless id = -1)
        TitleDisplayOnly = 2,         ///< Title Search UO not permitted but Title number can be displayed (unless id = -1)
        NoTitleSupport                ///< Neither Title search nor Title number display
    }
    accessType;

    /// Detailed title info
    union
    {
        struct
        {
            enum EHDMVPlaybackType playbackType;
            int mobj_id_ref;                ///< index into the MovieObjects list

            /// number of play-lists in the title

            /// Playlists are counted as they appear in the first MovieObject in the title.
            /// Their number and order may be different at run-time
            ///
            /// The ID of individual playlists can be retrieved through EBRDCmd::BRDCmd_get_pl_id commands
            int playListCount;
        }
        HDMV;   ///< HDMV title info

        struct
        {
            enum EBDJPlaybackType playbackType;
            TBRDItemID bdjo_id;             ///< BD-J Object ID (value of the xxxxx portion of the "xxxxx.bdjo" object file name)
        }
        BDJ;    ///< BD-J title info
    }
    info;
};

/// Blu-ray sub-path type definition
enum EBRDSubPathType
{
	SPTAsyncAudio = 4,		///< Primary audio of browsable slideshow (SubPath_type 2 in BD-ROM Part 3-1 Table 5-9)
	SPTAsyncMenu = 8,		///< Out-of_Mux menu (SubPath_type 3 in BD-ROM Part 3-1 Table 5-9)
	SPTAsyncText = 16,		///< Text subtitles (SubPath_type 4 in BD-ROM Part 3-1 Table 5-9)
	SPTSyncComponents = 32,	///< Presentation component (elementary stream case of SubPath_type 5 in BD-ROM Part 3-1 Table 5-9)
	SPTAsyncPiP = 64,		///< Asynchronous secondary presentation (PiP) (SubPath_type 6 in BD-ROM Part 3-1 Table 5-9)
	SPTSyncPiP = 128,		///< Synchronous secondary presentation (PiP) (PiP case of SubPath_type 5 and SubPath_type 7 in BD-ROM Part 3-1 Table 5-9)
};

/// Blu-ray Play List definition
struct SBRDPlayList
{
    TBRDItemID playList_id;     		///< play-list id ((value of the xxxxx portion of the "xxxxx.mpls" play list file name)
    enum EPLPlaybackType playback_type;	///< Sequential/Random/Shuffle playback
    enum EBRDSubPathType subpaths;		///< the set of subpath types (ORed together) available in the playlist \change Added 11-20-2007
	UINT16 playback_count;				///< number of playitems to be played in the current random/shuffle playback session
	int random_access_flag;				///< random access in playlist, according to 5.3.2.3
    int number_of_playItems;    		///< number of play-items in the play-list
    int number_of_marks;        		///< number of marks in the play-list
    int number_of_chapters;     		///< number of chapters in the play-list
	int audio_mix_app_flag;				///< indicates whether secondary audio mixing and/or interactive sound mixing are aplied to the PlayList
    UINT32 startMediaTime;      		///< media time (in 45KHz) at the start if the playlist
    UINT32 endMediaTime;        		///< media time (in 45KHz) at the end if the playlist; if equal with startMediaTime, do not display playlist position information
};

/// Blu-ray Play Item connection type definition - see BD-ROM Part3-1 5.3.4.3 \change 11-20-2007
enum EPIConnectionType
{
	PIConNonSeamless = 1,	///< non seamless
	PIConSeamlessGap = 5,	///< seamless, with time gap
	PIConSeamless,			///< seamless, contiguous
};

/// Still mode definition
enum EBRDStillMode
{
	STILL_NO = 0,
	STILL_FINIT,
	STILL_INFINITE
};


/// Blu-ray Play Item definition
struct SBRDPlayItem
{
    int playItem_id;                        		///< play-item id as per HDMV 5.3.3.3 (ver 0.9r3)
    TBRDItemID clip_id;                     		///< movie clip id
    enum EPIConnectionType connection_condition;	///< connection condition between the IN_time of the current PlayItem and OUT_time of the previous PlayItem
    enum EBRDStillMode still_mode;					///< still mode \change Added 12-14-2007
    int number_of_angles;                   		///< number of angles available for selection; angles are identified by their position in this enumeration
    int number_of_video_streams;            		///< number of video streams available for selection; streams are identified by their one-based index in this enumeration
    int number_of_primary_audio_streams;    		///< number of audio streams available for selection; streams are identified by their one-based index in this enumeration
    int number_of_pg_ts_streams;            		///< number of PG and TS streams available for selection; streams are identified by their one-based index in this enumeration
    int number_of_ig_streams;               		///< number of IG streams available for selection; streams are identified by their one-based index in this enumeration
    int number_of_secondary_audio_streams;  		///< number of secondary audio streams available for selection; streams are identified by their one-based index in this enumeration
    int number_of_secondary_video_streams;  		///< number of secondary video streams available for selection; streams are identified by their one-based index in this enumeration
    int number_of_PiP_PG_textST_streams;			///< number of PiP_PG_textST streams available for selection; streams are identified by their one-based index in this enumeration
    UINT32 startMediaTime;                  		///< media time (in 45KHz) at the start if the play-item
    UINT32 endMediaTime;                    		///< media time (in 45KHz) at the end if the play-item; if equal with startMediaTime, do not display play-item position information
};

// Mark type definition
enum EBRDMarkType
{
	Any_mark = 0,
    Entry_mark,
    Link_point
};

/// Blu-ray Play List mark definition - see 5.3.7
struct SBRDMark
{
       int PL_mark_id;

	   enum EBRDMarkType mark_type;

       int ref_playitem_id;

       UINT32 mark_time_stamp;

       UINT32 duration;
};

/// Blu-ray chapter definition
struct SBRDChapter
{
    int chapter_number;    ///< chapter number as per HDMV 5.3.7.3 (ver 0.9r3)
    int ref_playitem_id;   ///< reference to playitem
    UINT32 startMediaTime; ///< media time (in 45KHz) at the start if the chapter
    UINT32 endMediaTime;   ///< media time (in 45KHz) at the end if the chapter
};

/// Blu-ray stream definition
struct SBRDStream
{
    int stream_number;                      ///< stream number as per HDMV 5.3.4.5.2 (ver 0.9r3) or -1 if no stream exists or not selected
    int enabled;                            ///< current status of an existing, selected stream
    int pid;                                ///< MPEG2 Transport stream PID of the stream, used internally by the decoder
	int subPathId;							///< subPathId, or -1 if this is the main path. See HDMV, 5.3.4.5.2.1
    struct SBRDStreamCodingInfo codingInfo; ///< stream coding info. Note: for video streams other than the currently playing one, only the frame_rate field is valid
};

/// Blu-ray individual button sound descriptor
struct SBRDSoundEntry
{
	/// Sound type defintion
	enum EType
	{
		SND_Mono = 1,
		SND_Stereo = 3,
	}
	channel_configuration;

	/// Sound rate definition
	enum ERate
	{
		SND_48K = 1,
	}
	sampling_frequency;

	/// Sound width definition
	enum EWidth
	{
		SND_16bps = 1,
	}
	bits_per_sample;

	UINT32 data_offset;			///< sound data's offset into the SBRDSoundDescriptor::sound_data field
	UINT32 data_length;			///< sound data's length
};

/// Blu-ray button/interactive sound data descriptor
struct SBRDSoundDescriptor
{
	int 					 sound_count;   ///< Number of sounds in sound_tab table
	struct SBRDSoundEntry 	*sound_tab;		///< Sound table
    unsigned char 			*sound_data;	///< Sound data (in pre-processed PCMX format - #MTYPE_ELEM_PCM | #MTYPE_CONT_RESERVED | #MTYPE_APP_BDJ media type) \change Changed field 2008-01-16
};


/// Blu-ray media definition
struct SBRDMedia
{
	UINT32 organizationID;	///< organization ID of the disc
	UINT64 discID[2];		///< disc ID of the disc
};

/// Status info structure for the Blu-ray control object (navigator)

/// Status information is contained in the PSR registers is not duplicated in explicit status fields,
/// rather the register must be queried
///
/// Uses \ref SBRDFLAGS values in addition to the generic \ref SFLAGS and \ref SLPBFLAGS
///\ingroup BRDCTRLDEFS
struct SBRDStatus
#ifdef __cplusplus
                    : public SStatus
{
#else
{
    struct SStatus common;  ///< basic status info, common to any control object
#endif

    struct SBRDStream video;     ///< currently playing video stream; all fields are valid
    struct SBRDStream audio;     ///< currently playing audio stream
    struct SBRDStream ig;        ///< currently playing IG stream
    struct SBRDStream pg_ts;     ///< currently playing PG/TS stream

    /// currently playing secondary video stream
    struct
    {
    	/// area of the primary video currently overlayed by the secondary video
    	struct
    	{
    		int x;
    		int y;
    		int w;
    		int h;
    	}					window;

    	int					trickPlay;	///< 0 if the stream should be hidden during trick play, non-zero otherwise

		struct SBRDStream	params;		///< secondary video stream parameters
    }									sec_video;
	struct SBRDStream 					sec_audio; ///< currently playing secondary audio stream

    /// BD-ROM media ID
    struct SBRDMedia mediaID;

    /// The currently applicable User Operation masking table

    /// The table is aggregated from all 3 tables in the system
    /// It is defined as a field of 96 bits, starting at LSB of byte 0 and ending at MSB of byte 11
    /// The bits are in the same order as the corresponding commands, making testing the table a simple shifting operation.
    /// Use the provided #BRDCMD2UOMASK macro to build the mask for testing the table.
    UINT64 UO_mask_table;

    /// disc level information
    struct SBRDDisc
    {
        char version[5];                    ///< the version index field
        char provider[33];                  ///< provider identifier
        struct SBRDTitle firstPlayTitle;    ///< first playback title
        struct SBRDTitle menuTitle;         ///< menu title
        int number_of_titles;               ///< number of available titles
    }
    disc;

    /// currently playing title
    struct SBRDTitle crtTitle;

    /// currently playing chapter
    struct SBRDChapter crtChapter;

    /// currently playing play-list
    struct SBRDPlayList crtPlayList;

    /// currently playing play-item
    struct SBRDPlayItem crtPlayItem;

    /// last mark reached
    struct SBRDMark lastMark;

    /// angle information \change Changed name (backwaed-compatible) and added functionality 3-28-08
    struct
    {
    	int crt;		///< currently playing angle (valid values: 1-9)

    	int pending;	///< angle to become current at the next switch point (immediatelly for non-seamlles angles, pre-defined points for seamless angles) (valid values: 1-9)
    }
    angle;

	#define crtAngle	angle.crt	///< \deprecated By angle.crt

    /// BD-J Root Certificate Hash
    unsigned char rootCertificate[20];

    /// value of PSR 102
    UINT32 psr102;

    /// value of PSR 104
    ///\note This value reflects changes by both BD+ and application layer, but only the BD+ changes trigger change events - see #SBRDSTATUS_PSR_104. The application should reflect its changes in its copy of the status, or force a status update, in order to keep the status info consistent.
    UINT32 psr104;

    /// Preloaded sound buffer (B7 in BDAV-STD) and its structure \change Added structure, rearranged fields 11-20-2007
	struct SBRDSoundDescriptor	soundDescriptor;

	/// IN_time of the last non-seamless connection in the current play list \change Added 11-20-2007
	RMuint32 lastIN_time;

	char *crtManifestFileName;
};

///\ingroup BRDCTRLDEFS


/// Blu-ray specific command definition
struct SBRDCommand
#ifdef __cplusplus
                    : public SCommand
{
#else
{
    struct SCommand common; ///< basic command info, common to any control object
#endif

    enum EBRDCmd cmd;

    /// first command parameter
    union
    {
        int selector;               ///< stream, button, register, etc selector; -1 for default value
        UINT32 language;			///< language code, using \ref BRDLANGS
        int speed;                  ///< playback speed in nominal speed/1024 units
        enum EStopMode stopMode;    ///< identifies the behavior upon stopping \status TBI
        char *bookmarkBuf;          ///< buffer for bookmark data
        int itemID;					///< item selector (based on file name)
        void *privateData;			///< private data passed between matching implementation-specific modules \change Added 6-23-2008 for AACS online use
        enum EBRDMarkType markType;	///< type of the target of a #BRDCmd_skip_to_next_mark or #BRDCmd_skip_back_to_previous_mark command
    }
    param1;

    /// second command parameter
    union
    {
        int selector;               ///< secondary selector (play item, mark, trick mode: 0-smoooth and 1-scan, etc)
        struct SMediaTime time;     ///< media position (h, m, s, frames)
        UINT32 regValue;            ///< register value for set_gps and set_psr commands
    }
    param2;

    /// third parameter
    union
    {
        TBRDItemID				playListID;     ///< play list selector (based on file name)
		enum EPlayItemEndAction endAction;		///< what to do at title or chapter end - see EBRDCmd::BRDCmd_title_search and EBRDCmd::BRDCmd_chapter_search commands
    }
    param3;
};

///\ingroup BRDCTRLDEFS

/// Blu-ray specific result definition
struct SBRDResult
#ifdef __cplusplus
                    : public SResult
{
#else
{
    struct SResult common; ///< basic result info, common to any control object
#endif

    /// Blu-ray specific result definitions
    union
    {
        UINT32 regValue;                ///< returned register value
        struct SBRDTitle title;         ///< returned title information
        struct SBRDPlayList playList;   ///< returned playlist information
        struct SBRDPlayItem playItem;   ///< returned playitem information
        struct SBRDChapter chapter;     ///< returned chapter information
        struct SBRDMark mark; 			///< returned mark information
        struct SBRDStream stream;       ///< returned stream information
        TBRDItemID playListID;     		///< returned play list ID
        int size;               		///< returned buffer size
        enum EBDAppType appType;		///< returned application type
        TAudioMetaData metaData;		///< returned metadata value
    }
    info;
};

/// \class DCCHD_BRD::CNavigator
/// Playback control class for BD-ROM media
///
/// The interface to this class is defined by \ref BRDMSDEFS and DCCHD::IPlaybackControl
/// \ingroup controlimpl


#endif //_CDEFS_BRD_H_

/**
  $Log: cdefs_brd.h,v $
  Revision 1.148  2008-10-20 23:08:32  sorin
  BugId: none
  Added mark type selection support in the skip to next/prev mark BRD command definition

  Revision 1.147  2008-10-07 23:24:26  sorin
  BugId: none
  Doc

  Revision 1.146  2008-09-26 13:33:49  cornel
  BugId: none
  Implemented "itles info "batch retrieval" for BDJ (it speeds up loading time on discs with hundreds of titles; e.g. MIB).

  Revision 1.145  2008-09-25 14:56:13  rdemeter
  BugId: none
  add get_titles_info batch command

  Revision 1.144  2008-07-16 18:36:38  cornel
  BugId: none
  Added support for batch title information retrieval (for playitems and playlistmarks info) for performance considerations. The support is active in BDJ by default. This addition fixes the Cars ocasional failure (no selection in secondary menu).

  Revision 1.143  2008-06-27 19:45:08  sorin
  BugId: none
  Added Quick status support for testing and certification
  Optimized doc/user info

  Revision 1.142  2008-06-24 02:27:39  sorin
  BugId: CT-4496
  Exposed the newly added AASC online co mands of the AACS provider at navi level and used them at JBI level

  Revision 1.141  2008-06-10 22:29:01  sorin
  BugId: none
  spell fix

  Revision 1.140  2008-05-27 23:31:07  sorin
  BugId: none
  Replaced the BD-specific NON_SEAM:ESS mode flag with the generic TRANSITION one

  Revision 1.139  2008-05-22 23:47:46  sorin
  BugId: none
  Optimized the HDMV file reloading upon VFS update

  Revision 1.138  2008-05-12 12:45:47  sorin
  BugId: none
  Doc

  Revision 1.137  2008-04-05 01:39:33  sorin
  BugId: none
  Made and propagated API changes related to the secondary audio gain, pan and mixing control

  Revision 1.136  2008-03-31 23:50:05  rdemeter
  BugId: none
  typo

  Revision 1.135  2008-03-28 22:24:07  sorin
  BugId: 4363
  Added pending angle status field in preparation for new seamless angle implementation

  Revision 1.134  2008-03-26 19:12:07  rdemeter
  BugId: none
  remove secondary available flags

  Revision 1.133  2008-03-19 18:08:43  sorin
  BugId: none
  Updated user event handling to latest spec
  Made HDMV and BD-J support in amp_test identical (in terms of exposed commands)

  Revision 1.132  2008-03-12 19:56:26  rdemeter
  BugId: none
  modify BRDCMD2UOMASK macro

  Revision 1.131  2008-03-11 02:19:41  rdemeter
  BugId: none
  add reset_backup_registers bdj command

  Revision 1.130  2008-02-05 08:52:35  sorin
  BugId: none
  Added SBRDSTATUS_VIRTUAL_PACKAGE status flag for allowing the GUI to handle the persistent storage depending on the package type.
  Updated doc

  Revision 1.129  2008-01-22 21:57:25  sorin
  BugId: none
  Updated the API and completed some implementation

  Revision 1.128  2008-01-21 19:08:11  rdemeter
  BugId: none
  add set_PiP_PG_textST_valid_flag

  Revision 1.127  2008-01-17 07:02:34  sorin
  BugId: none
  Changed sound descriptor definition to allow for pre-processed data

  Revision 1.126  2007-12-15 03:51:45  smanciulea
  BugId: none
  -  make rootCertificate unsigned char

  Revision 1.125  2007-12-14 18:46:37  sorin
  BugId: 4132
  Exposed the play item still mode info (port from 176 branch)

  Revision 1.124  2007-11-21 19:16:49  rdemeter
  BugId: none
  Propagated API changes

  Revision 1.123  2007-11-21 04:46:19  sorin
  BugId: ct-3095
  Expose secondary audio volume and pan control as generic adjustment commands rather than blu-ray special ones.

  Revision 1.122  2007/11/19 17:50:23  rdemeter
  BugId: none

  Revision 1.121  2007/11/19 16:29:26  rdemeter
  BugId: none

  Revision 1.120  2007/11/19 16:01:34  rdemeter
  BugId: none
  add panning commands for sec audio

  Revision 1.119  2007/11/09 14:31:40  rdemeter
  BugId: none
  docs

  Revision 1.118  2007/10/30 19:58:28  rdemeter
  add start playback status info

  Revision 1.117  2007/09/27 17:26:15  mfedoreanu
  Sound descriptor

  Revision 1.116  2007/09/27 16:54:18  mfedoreanu
  Sound descriptor

  Revision 1.115  2007/09/13 14:50:23  rdemeter
  BUGCT:3849 compile error for DISABLE_HDMV_UOMASK

  Revision 1.114  2007/07/04 01:41:45  rdemeter
  add nonseamless flag

  Revision 1.113  2007/06/20 13:09:25  rdemeter
  add sec_video and sec_audio in Status flags

  Revision 1.112  2007/06/18 13:17:38  rdemeter
  add sec_video and sec_audio in SBRDStatus

  Revision 1.111  2007/06/18 10:07:36  smanciulea
  BUGCT: NONE renamed bookmark related commands for consistency with the rest of the commands

  Revision 1.110  2007/06/11 15:22:44  rdemeter
  BUGCT:3315 Disable HDMV UOMASK in BDJ titles

  Revision 1.109  2007/06/07 13:23:21  rdemeter
  typo

  Revision 1.108  2007/06/06 21:29:12  sorinp
  doc update

  Revision 1.107  2007/06/06 07:01:19  sorinp
  BUGCT:3343 Added application type retrieval support
  Added BD-J support

  Revision 1.106  2007/05/29 22:03:34  sorinp
  doc

  Revision 1.105  2007/05/29 12:01:53  rdemeter
  BUGCT#3316 read video stream info, sec_video stream info from clip info

  Revision 1.104  2007/05/25 17:38:51  rdemeter
  BUGCT:3315 Diferentiate between UOs and PCFs

  Revision 1.103  2007/05/15 03:24:25  sorinp
  Completion to the bookmark API

  Revision 1.102  2007/05/15 01:35:38  sorinp
  BUGCT:3252 Defined bookmark API

  Revision 1.101  2007/05/11 12:59:50  rdemeter
  BUGCT#3130 Added Unknown playback type when there is no TopMenu or firstPlayback

  Revision 1.100  2007/05/08 19:29:41  sorinp
  BUGCT:3208 - 3213 Added stopMode parameter to Stop command in all media spaces to allow client module to control behavior

  Revision 1.99  2007/05/02 20:48:55  sorinp
  BUGCT:3142 Added TERMINATED mode flag

  Revision 1.98  2007/04/25 00:30:49  sorinp
  BUGCT:3108 Defined mixing metadata control API

  Revision 1.97  2007/04/12 09:55:42  rdemeter
  BUGCT#2933 BRDCmd_set_title_end_action and BRDCmd_set_chapter_end_action can be setted in PAUSE or PLAY mode

  Revision 1.96  2007/03/29 10:27:45  rdemeter
  changed all bool struct members to int

  Revision 1.95  2007/03/28 14:22:54  rdemeter
  *** empty log message ***

  Revision 1.94  2007/03/28 12:56:27  rdemeter
  exposed disc info

  Revision 1.93  2007/03/27 14:09:16  rdemeter
  add BRDCmd_get_PiP_PG_textST_stream_info in the command list

  Revision 1.92  2007/03/27 09:25:17  rdemeter
  add BRDCmd_get_sec_video_stream_info in the command list

  Revision 1.91  2007/03/20 00:15:12  sbeysserie
  Add end of line.

  Revision 1.90  2007/03/19 16:25:19  sorinp
  Moved log at the end of the file

  Revision 1.89  2007/03/16 09:38:46  sorinp
  Added support for profile 1.1 in API

  Revision 1.88  2007/02/20 23:32:32  sorinp
  doc updates

  Revision 1.87  2007/02/20 20:12:26  sorinp
  doc update

  Revision 1.86  2007/02/14 04:21:30  sorinp
  Doc upgrade

  Revision 1.85  2007/02/08 20:02:43  sorinp
  BUGCT:2554 Expose the sound buffer in the status structure

  Revision 1.84  2006/12/16 02:59:35  sorinp
  Merged with the version_1_0 branch (at RC34 level)

  Revision 1.83  2006/12/14 13:20:59  rdemeter
  merge title/chapter repeat

  Revision 1.82.6.3  2006/12/12 17:32:44  sorinp
  Removed change doc tags in prepearation for the official 1.0.0 release

  Revision 1.82.6.2  2006/12/11 21:25:57  sorinp
  Added title and chapter repeat mode flags

  Revision 1.82.6.1  2006/12/11 18:19:45  sorinp
  Added explicit repeat support

  Revision 1.82  2006/10/19 22:07:59  sorinp
  doc fixes

  Revision 1.81  2006/10/13 20:22:48  sorinp
  Moved the userTimeout and mode fields from LPB to generic status in order to allow single-point processing of the status in CPlaybackControl

  Revision 1.80  2006/10/12 06:24:48  sorinp
  doc

  Revision 1.79  2006/10/11 15:03:13  sorinp
  doc

  Revision 1.78  2006/10/11 14:55:21  sorinp
  doc

  Revision 1.77  2006/10/11 01:42:13  sorinp
  Exposed PSR 102 and 104 directly in the status structure to avoid teh overhead of additional GetPSR commands

  Revision 1.76  2006/10/07 05:17:59  sorinp
  docs

  Revision 1.75  2006/10/07 00:19:42  sorinp
  Added support for on-the-fly title and chapter end action change

  Revision 1.74  2006/10/05 04:48:51  sorinp
  Added endAction command parameter and doc

  Revision 1.73  2006/09/25 16:44:42  sorinp
  doc

  Revision 1.72  2006/09/24 03:37:07  sorinp
  Working Media UIN for VFS-based access, propagated API changes

  Revision 1.71  2006/09/21 06:59:01  rdemeter
  named a union

  Revision 1.70  2006/09/20 16:51:09  sorinp
  Split Play cmd into FirstPlay and Play

  Revision 1.69  2006/09/20 16:35:22  sorinp
  Split Play cmd into FirstPlay and Play

  Revision 1.68  2006/09/16 05:00:52  sorinp
  Updated doc (status field)

  Revision 1.67  2006/09/08 02:00:03  sorinp
  Reinstated redundant PSR 104 change event to avoid multiple code changes...

  Revision 1.66  2006/09/08 01:55:34  sorinp
  Removed unused event: PSR 104 change

  Revision 1.65  2006/08/30 18:53:17  sorinp
  Changed the statistics info definition and moved the filed from the LPB into the generic media space

  Revision 1.64  2006/08/03 04:13:04  rdemeter
  - audio_mix_app_flag added to playlist status info

  Revision 1.63  2006/07/29 01:38:57  sorinp
  Removed doc change notes older than B.2.0

  Revision 1.62  2006/06/28 03:40:33  rdemeter
  add step_back misc command for brd

  Revision 1.61  2006/05/30 20:13:38  rdemeter
  title instead of chapter

  Revision 1.60  2006/05/17 03:37:17  sorinp
  Updated UO mask table to 64 bits

  Revision 1.59  2006/05/16 22:20:41  sorinp
  Updates for level B.1.0

  Revision 1.58  2006/05/12 01:16:01  sorinp
  Replaced BDPLUS BRD sevent with PSR 102/104

  Revision 1.57  2006/05/11 21:33:33  rdemeter
  added BRDCmd_set_psr for BD+

  Revision 1.56  2006/04/25 04:37:24  sorinp
  doc upgrades

  Revision 1.55  2006/04/21 22:45:09  rdemeter
  ptsoffset fixup
  play, ffwd, play

  Revision 1.54  2006/04/19 04:23:36  mfedoreanu
  moved Media time from specific format status to common status

  Revision 1.53  2006/04/18 07:37:35  sorinp
  Adedd PlayList enumeration support in API
  Added mark enumeration and event in API

  Revision 1.52  2006/04/07 11:19:42  rdemeter
  added connection_condition to playitem status information

  Revision 1.51  2006/03/30 19:47:09  anagy
  Robert forgot to put this in CVS

  Revision 1.50  2006/03/27 18:43:29  rdemeter
  version and provider 0-terminated

  Revision 1.49  2006/03/19 00:32:41  sorinp
  mostly doc, some spec updates

  Revision 1.48  2006/03/10 23:30:34  sorinp
  qualified type name for C support

  Revision 1.47  2006/03/10 17:57:43  sorinp
  syntax fix

  Revision 1.46  2006/03/10 08:09:08  rdemeter
  modif SBRDChapter

  Revision 1.45  2006/02/26 04:00:32  sorinp
  Remove unused and redundant fields in status

  Revision 1.44  2006/02/26 02:53:28  sorinp
  doc typos

  Revision 1.43  2006/02/26 01:04:45  sorinp
  Added POPUP_AVAILABLE mode flag

  Revision 1.42  2006/02/21 08:03:52  rdemeter
  change language parameter type

  Revision 1.41  2006/02/17 20:38:54  sorinp
  removed the /change tags to start clean for the enxt release

  Revision 1.40  2006/02/17 04:49:48  sorinp
  Doc nicetities

  Revision 1.39  2006/02/15 17:54:54  sorinp
  doc updates

  Revision 1.38  2006/02/15 16:07:27  rdemeter
  current staus of UO implementation update

  Revision 1.37  2006/02/09 04:40:46  sorinp
  Added BD-J root certification reporting support

  Revision 1.36  2006/01/30 02:46:16  sorinp
  Clarified media sapce - media type correspondence

  Revision 1.35  2006/01/20 13:16:02  rdemeter
  *** empty log message ***

  Revision 1.34  2005/12/12 21:30:48  rdemeter
  maskable BRDCmd modification (BDROM v09r5)

  Revision 1.33  2005/12/09 15:53:24  sorinp
  doc and small spec changes

  Revision 1.32  2005/12/08 07:33:51  sorinp
  added ig, pg and menu mode flags

  Revision 1.31  2005/12/08 06:08:18  sorinp
  doc fix

  Revision 1.30  2005/12/08 03:47:11  sorinp
  use H:M:S:frames as search time format

  Revision 1.29  2005/12/05 06:52:48  sorinp
  updated status support for consolidated og-ts streams

  Revision 1.28  2005/12/05 06:49:15  sorinp
  onsolidated pg and ts stream info

  Revision 1.27  2005/11/18 01:26:23  sorinp
  Added BD+ event definition and support

  Revision 1.26  2005/11/16 00:05:47  dnguyen
  changed all bool struct members to int because the difference between mips
  C compiler (where bool is 32-bit) and C++ compiler (bool is 8-bit) can be
  catastrophic

  Revision 1.25  2005/11/03 13:13:17  mfedoreanu
  Moved some structs defs outside

  Revision 1.24  2005/10/26 19:15:57  sorinp
  reorganized media spece identifiers

  Revision 1.23  2005/10/26 04:17:52  sorinp
  Added stream visibility status info. No way to change it though...

  Revision 1.22  2005/10/12 13:45:24  sorinp
  doc updates

  Revision 1.21  2005/10/11 21:22:12  rdemeter
  playback type is different for BDJ and HDMV. see table 5.2

  Revision 1.20  2005/10/11 01:02:03  sorinp
  fixed C compatibility

  Revision 1.19  2005/10/06 19:08:25  rdemeter
  get_pg_ts_stream_info instead get_ps_ts_stream_info

  Revision 1.18  2005/10/05 18:44:14  sorinp
  Mostly doc upgrades

  Revision 1.17  2005/10/05 16:21:41  rdemeter
  syntax fix

  Revision 1.16  2005/10/04 23:43:19  sorinp
  doc fixes

  Revision 1.15  2005/10/04 23:26:34  sorinp
  improved naming convention (made it similar with the HDMV spec)

  Revision 1.14  2005/10/04 23:18:29  sorinp
  doc clarification#MTYPE_APP_BRD

  Revision 1.13  2005/10/04 23:17:11  sorinp
  Made item identification scheme identical with the one used in the HDMV spec

  Revision 1.12  2005/10/04 03:22:17  sorinp
  Made stream number usage clear and consistent
  Removed costly and redundant langTab field in playItem
  Made language code UINT32 and made definition compiler and platform independent

  Revision 1.11  2005/09/30 09:01:35  sorinp
  doc typo

  Revision 1.10  2005/09/30 07:36:07  sorinp
  Still some changes...

  Revision 1.9  2005/09/30 07:05:13  sorinp
  Added userActionTimeout field

  Revision 1.8  2005/09/30 06:51:50  sorinp
  Updated status info definition and content; should be complete now

  Revision 1.7  2005/09/28 11:37:31  sorinp
  Made C compatible

  Revision 1.6  2005/09/27 16:26:55  sorinp
  Removed unused command field

  Revision 1.5  2005/09/27 15:55:36  sorinp
  propagated BRD name tag

  Revision 1.4  2005/09/27 11:05:04  rdemeter
  syntax update

  Revision 1.3  2005/09/26 07:52:25  sorinp
  Made disc ID a lpb media ID field, since it will be used by all the interactive formats

  Revision 1.2  2005/09/26 07:34:26  sorinp
  Added disc ID status field

  Revision 1.1  2005/09/26 06:47:09  sorinp
  finalized linear and blu-ray control and media definition
  placed public media and control definitions in separate (and new) files

  Revision 1.18  2005/09/21 17:31:55  rdemeter
  UO_mask_table is unsigned long long type

  Revision 1.17  2005/09/11 23:31:41  sorinp
  Multiple changes
  Completed presentation engine spec.
  Control framework spec at linear playback level.

  Revision 1.16  2005/09/03 02:25:41  sorinp
  various syntax, functionality and doc changes

  Revision 1.15  2005/08/19 14:40:28  rdemeter
  add playback_type status info

  Revision 1.14  2005/08/19 01:47:16  sorinp
  typo

  Revision 1.13  2005/08/12 17:40:06  rdemeter
  ;

  Revision 1.12  2005/08/06 20:24:27  sorinp
  Adding external API details: commands, status fields, etc

  Revision 1.11  2005/07/28 18:33:44  rdemeter
  fwd/rwd playback

  Revision 1.10  2005/07/26 17:45:25  rdemeter
  *** empty log message ***

  Revision 1.9  2005/07/26 04:14:32  sorinp
  Implemented CPLaybackControl::ExecuteCmd; updated members, doc, naming and syntax and propagated the changes in deried/client classes

  Revision 1.8  2005/07/25 18:34:54  rdemeter
  update according to base class modif

  Revision 1.7  2005/07/19 14:42:30  rdemeter
  delete event redefinition;
  add event flags mapping

  Revision 1.6  2005/07/15 18:10:14  rdemeter
  add brd specific events

  Revision 1.5  2005/07/11 16:04:42  rdemeter
  *** empty log message ***

  Revision 1.4  2005/06/20 20:19:08  sorinp
  Made CPresEng implementation details private
  added documentation module support

  Revision 1.3  2005/06/06 20:10:51  sorinp
  Upadated and documented the Blu-ray presentation engine module
  Other syntax and grammar fixes

  Revision 1.2  2005/06/05 17:16:09  sorinp
  Updated file headers

*/

