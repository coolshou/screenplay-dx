/*****************************************
 Copyright  2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   cdefs_bdre.h
  @brief  Blu-ray rewritable control definitions shared with middleware clients

  @author Sebastian Manciulea
  @date   2005-11-22

  $Header: /bigbig/dungeon/dcchd_project/dcchd/brd/cdefs_bdre.h,v 1.62 2009-05-07 13:29:37 bsimon Exp $

*/

#ifndef _CDEFS_BDRE_H_
#define _CDEFS_BDRE_H_

#include <cdefs.h>
#include "mdefs_bdre.h" // Blu-ray rewritable media definitions

///\defgroup BDREMSDEFS Blu-ray Rewritable Media Space Definitions
/// Definitions for media with #TMediaType of #MTYPE_APP_BDRE
///\ingroup MEDSPACES

///\defgroup BDRECTRLDEFS Blu-ray Rewritable Control Definitions
/// Control definitions for media with #TMediaType of #MTYPE_APP_BDRE
///\ingroup BDREMSDEFS
///
/// \par OpenMedia mode of operation:
///		Because BDRE allows for more than one BDAV directory the OpenMedia() call needs to be called at least twice:
///		- First an instance of a navigator calls OpenMedia() with the 'root' directory of the media which returns
///		the number of BDAV directories, one or at most 5 (if there are any auxiliary BDAV directories). Afterwards the
///		navigator instance is deleted.
///		- Second another instance of a navigator calls OpenMedia() with the BDAV directory chosen by the user.
/// 	If the BDAV_protect_flag is "1" the user will have to enter the PIN in order to access the directory.
/// 	If the BDAV_protect_flag is "0"	the user is allowed to see the directory contents but he/she will have to
/// 	enter later on the PIN for PlayLists with the playback_protect_flag set to "1".
///
///		NOTE: Once the correct PIN is entered it will not be requested even if there are protected PlayLists
///
///	Returned status:
///		SBDRESTATUS_DISK - the status variable contains disc-level information
///		SBDRESTATUS_DIR - the status variable contains directory-level information
///		SBDRESTATUS_REQ_PIN - the user must enter the PIN in order to access the directory
///
///	Returned result codes:
///		TRESULT_SUCCESS - successful open, number of BDAV directories is returned in status structure or
///						  status contains information about the chosen BDAV directory
///		TRESULT_ERROR with error code: RESULT_FAILURE - fatal error
///									   RESULT_INVALID - invalid parameters
///									   RESULT_NOT_AVAILABLE - no BDAV directories? invalid disc?
///									   RESULT_PROTECTED - invalid PIN was entered
///
/// \par OpenPresentation mode of operation:
///		After starting the presentation the user can issue commands to the navigator.
/// 	If BDAV_protect_flag = 1 the PIN has already been entered and even if there are PlayLists with
///		playback_protect_flag = 1 the PIN will not be requested again.
///		If BDAV_protect_flag = 0 and there are PlayLists with playback_protect_flag = 1 the PIN will be
///		requested upon encountering such a PlayList. After entering the correct PIN no more requests
///		will be issued for the rest of the protected PlayLists.
///
///@{
#define MEDIA_SPACE_BDRE    10     ///< Blu-ray rewritable media space, to identify SBDRECommand, SBDREStatus and SBDREResult structures \ingroup MSID

///@}

///\defgroup SBDREFLAGS Blu-ray rewritable status flags
/// Constants identifying individual Blu-ray rewritable status fields and events. Used in addition to \ref SFLAGS
///\ingroup BDRECTRLDEFS
//@{

#define SBDRESTATUS_VIDEO		(SSTATUS_LAST_GENERIC << 1)	///< identifies the video field; events are triggered when the stream parameters change

#define SBDRESTATUS_AUDIO		(SSTATUS_LAST_GENERIC << 2)	///< identifies the audio field; events are triggered when the stream parameters change

#define SBDRESTATUS_PG			(SSTATUS_LAST_GENERIC << 3)	///< identifies the pg field; events are triggered when the stream parameters change

#define SBDRESTATUS_PES_PRIV	(SSTATUS_LAST_GENERIC << 4)	///< identifies the PES private (teletext) field; events are triggered when the stream parameters change

#define SBDRESTATUS_DISK      	(SSTATUS_LAST_GENERIC << 5) ///< identifies the disc index field; events are triggered when the disc changes

#define SBDRESTATUS_DIR		  	(SSTATUS_LAST_GENERIC << 6)	///< identifies the current BDAV directory; events are triggered when the BDAV directory changes

#define SBDRESTATUS_PLAYLIST	(SSTATUS_LAST_GENERIC << 7) ///< identifies the crt play-list field; events are triggered when play-list changes

#define SBDRESTATUS_PROGSEQ	  	(SSTATUS_LAST_GENERIC << 8) ///< identifies the crt program sequence field; events are triggered when the program sequence changes

#define SBDRESTATUS_PL_MARK	  	(SSTATUS_LAST_GENERIC << 9) ///< identifies the crt play-list mark field; events are triggered when the play-list mark changes

#define SBDRESTATUS_REQ_PIN   	(SSTATUS_LAST_GENERIC << 10)	///< no associated status field, events are triggered when the PIN has to be entered

///@}

///\defgroup BDREMFLAGS Blu-ray rewritable specific flags for playback mode description
/// Constants identifying individual playback modes, used in the SBDREStatus::mode::flags field. Used in addition to \ref MFLAGS
///\ingroup BDRECTRLDEFS
///@{
//#define SBDRESTATUS_MODE_MENU_ACTIVE         (SSTATUS_MODE_LAST_LPB << 1)    ///< if set, menu is currently displayed

///@}


/// Blu-ray rewritable specific command values

/// The standard does not enumerate playback functions for the PLayList files (s. Annex F.3.3),
///	so we define some usual operations.
///\ingroup BDRECTRLDEFS
enum EBDRECmd
{
	BDRECmd_invalid = 0,
	BDRECmd_first_uo = 1,          				///< first valid uo value, can be used to test validity
	BDRECmd_play = BDRECmd_first_uo,			///< Play/Resume playback of the current PlayList, works only after a PlayList has been selected \change Changed 8-23-2007
	BDRECmd_stop,                           	///< Stop playback of the currently playing PlayList, behavior specified in SBDRECommand::param1::stopMode \change Added stop mode parameter 5-8-2007
	BDRECmd_pause_on,                       	///< Pause On: pause the playback of the currently playing PlayList
	BDRECmd_pause_off,                      	///< Pause Off: resume from pause the playback of the currently playing PlayList
	BDRECmd_step_fwd,							///< Step forward
	BDRECmd_step_rev,							///< Step backward
	BDRECmd_forward_play,                   	///< Forward Play, of type SBDRECommand::param2::selector (smooth = 0/scan = #LPBPLAY_MODE_KEY) and speed in SBDRECommand::param1::speed (1024 units)
	BDRECmd_backward_play,                  	///< Backward Play, of type SBDRECommand::param2::selector (smooth = 0/scan = #LPBPLAY_MODE_KEY) and speed in SBDRECommand::param1::speed (1024 units)
	BDRECmd_audio_change,                   	///< Audio change to audio stream with PID specified in SBDRECommand::param1::selector
	BDRECmd_select_dual_mono_ch,				///< Select the channel of a dual mono audio stream based on the value of SBDRECommand::param1::selector (left = 0 / right = 1)
	BDRECmd_view_change,						///< View change in a multi-view program sequence, to video stream with PID specified in SBDRECommand::param1::selector

	BDRECmd_play_pl_mark,                   	///< play the PlayList with ID SBDRECommand::param3::playListID from mark with number SBDRECommand::param2::selector, using PIN SBDRECommand::param1::PIN (10000 for no PIN) \change Changed 8-23-2007
	BDRECmd_play_pl_time,                   	///< play the PlayList with ID SBDRECommand::param3::playListID from time SBDRECommand::param2::time expressed in 45 kHz units, using PIN SBDRECommand::param1::PIN (10000 for no PIN) \change Changed 8-23-2007
	BDRECmd_skip_to_next_mark,              	///< skip to next mark of type SBDRECommand::param1::selector in the current playlist or ignore if none exists. Use \ref BDREMARKTYPE values.
	BDRECmd_skip_to_previous_mark,     			///< skip to previous mark of type SBDRECommand::param1::selector in the current playlist or ignore if none exists. Use \ref BDREMARKTYPE values.

	BDRECmd_get_pl_info,                    	///< retrieves in SBDREResult::info::play_list information about the playlist with ID SBDRECommand::param3::playListID, using PIN SBDRECommand::param1::PIN (10000 for no PIN); must be called first for a PlayList (Note: works only in STOPPED state) \change Changed 8-23-2007
	BDRECmd_get_pl_mark_info,					///< retrieves in SBDREResult::info::pl_mark_info information of mark with index SBDRECommand::param2::selector from the playlist with ID SBDRECommand::param3::playListID; must be called after BDRECmd_get_pl_info for that PlayList (Note: works only in STOPPED state) \change Changed 8-23-2007
	BDRECmd_get_pi_info,						///< retrieves in SBDREResult::info::play_item information about the PlayItem with index SBDRECommand::param2::selector from the playlist with ID SBDRECommand::param3::playListID; must be called after BDRECmd_get_pl_info for that PlayList (Note: works only in STOPPED state) \change Changed 8-23-2007
	BDRECmd_get_clip_mark_info,					///< retrieves in SBDREResult::info::clip_mark_info information of mark with index SBDRECommand::param1::selector from Clip with ID SBDRECommand::param2::selector; must be called after BDRECmd_get_pl_info for that PlayList
												///< (Note: works only in STOPPED state and the PlayList ID must be passed in SBDRECommand::param3::playListID)
	BDRECmd_get_thumbnail,						///< retrieves in SBDRECommand::param2::bookmarkBuf the thumbnail picture with ref_to_XXXX_index in SBDRECommand::param1::selector (bits 28..0),
												///< bit 31 of SBDRECommand::param1::selector indicates a menu thumbnail, bit 30 a Play List mark thumbnail and bit 29 a Clip mark thumbnail,
												///< and in SBDREResult::info::thumbnail the associated information (H, W, size); must be called after BDRECmd_get_pl_info for a PlayList
												///< (Note: works only in STOPPED state and the PlayList ID must be passed in SBDRECommand::param3::playListID)	\change Changed 8-23-2007
	BDRECmd_get_mark_pict,						///< TBI - decode the picture associated with the mark of type SBDRECommand::param1::selector (0 - Play List mark; 1 - Clip mark)
												///< with index SBDRECommand::param2::selector.
												///< Note1: command requires in SBDRECommand::param3::playListID the ID of the current PlayList for Play List marks or the Clip ID for Clip marks
												///< Note2: Play List marks can be only of type 0x01 (s. Table 4-9)

    BDRECmd_query_bookmark_size,		        ///< retrieves in SBDREResult::info::size the size of the storage needed for a bookmark \change Added 5-14-2007
    BDRECmd_query_bookmark,			            ///< retrieves in SBDRECommand::param1::bookmarkBuf the bookmark for the current position
    BDRECmd_resume_bookmark         			///< resumes playback from bookmark specified in SBDRECommand::param2::bookmarkBuf using PIN SBDRECommand::param1::PIN (10000 for no PIN) \change Changed 8-23-2007
};

typedef UINT32 TBDREItemID;  					///< Blu-ray rewritable item ID - value of the xxxxx portion of the "xxxxx.yyyy" name of the file in which the item is stored

typedef enum { T_REAL_PLAYLIST, T_VIRTUAL_PLAYLIST } T_PLAYLIST_TYPE;	/// BD-RE playlist type

#define	MENU_THMBN_FLAG			0x80000000			///< BD-RE Play List menu thumbnail
#define PLST_MARK_THMBN_FLAG	0x40000000			///< BD-RE Play List mark thumbnail
#define CLIP_MARK_THMBN_FLAG	0x20000000			///< BD-RE Clip mark thumbnail
#define THMBN_TYPE_MASK			0xE0000000			///< BD-RE thumbnail type mask

#define BDRE_TN_BUFF_SIZE	(16*1024 - 4)		/// maximum size for a thumbnail picture buffer

/// disc level information
struct SBDREDisc
{
	/// number of BDAV directories on disc (one Basic BDAV directory and at most 4 Aux BDAV directories)
	int numBDAVDirectories;
};


/// BDAV directory level information
struct SBDAVDir
{
    int is_valid;                           ///< 0/1 - invalid/valid BDAV directory entry (invalid in case of error reading a BDAV directory)
	int BDAV_dir_idx;						///< BDAV directory index, 0: basic BDAV, 1 - 4: auxiliary BDAV
    char version[5];                        ///< the version index field, shall have the value "0100"
    int valid_PIN;                          ///< 0/1 - invalid or non-existent PIN / valid PIN value was entered
	int BDAV_protect_flag;                  ///< indicates whether the contents in the BDAV directory can be shown to the user or not											//
    enum EBDRECharSet BDAV_character_set;   ///< specifies a way that characters are coded in the BDAV_name field
	TBDREItemID resume_PlayList_file_id;	///< the xxxxx portion of the playlist file name xxxxx.rpls/.vpls
	unsigned short ref_menu_thmb_idx;       ///< thumbnail index in menu.tidx
    int BDAV_name_length;                   ///< length in bytes of the BDAV directory's name in the BDAV_name field
    char BDAV_name[256];                    ///< name of the BDAV directory
    int number_of_PlayLists;                ///< number of available play-lists
	TBDREItemID PlayListID[200];			///< PlayList IDs
};

/// image of the TUIAppInfoPlayList structure
struct _ui_info
{
	enum EBDRECharSet PlayList_char_set;

#if (RMENDIANNESS == RMBIGENDIAN)
	struct
	{
		unsigned int reserved:4;

		/// 1: the user has to enter the PIN in order to play back the PlayList; 0: no PIN required for playback.
		unsigned int playback_protect_flag:1;

		/// 1: the PlayList except the write_protect_flag should not be changed or deleted; 0: the user is free to change or delete the PlayList
		unsigned int write_protect_flag:1;

		/// 1: the PlayList has been played at least once; 0: the PlayList has never been played since it was created
		unsigned int is_played_flag:1;

		/// 1: the PlayList has been changed at least once; 0: the PlayList keeps the original data
		unsigned int is_edited_flag:1;
	} flags;

	struct
	{
		unsigned int padding_bit:1;
		unsigned int daylight_saving_time_flag:1;
		unsigned int time_zone_sign:1;
		unsigned int time_zone_val:4;
		unsigned int half_hour_flag:1;
	} time_zone;
#elif (RMENDIANNESS == RMLITTLEENDIAN)
	struct
	{
		/// 1: the PlayList has been changed at least once; 0: the PlayList keeps the original data
		unsigned int is_edited_flag:1;

		/// 1: the PlayList has been played at least once; 0: the PlayList has never been played since it was created
		unsigned int is_played_flag:1;

		/// 1: the PlayList except the write_protect_flag should not be changed or deleted; 0: the user is free to change or delete the PlayList
		unsigned int write_protect_flag:1;

		/// 1: the user has to enter the PIN in order to play back the PlayList; 0: no PIN required for playback.
		unsigned int playback_protect_flag:1;

		unsigned int reserved:4;
	} flags;

	struct
	{
		unsigned int half_hour_flag:1;
		unsigned int time_zone_val:4;
		unsigned int time_zone_sign:1;
		unsigned int daylight_saving_time_flag:1;
		unsigned int padding_bit:1;
	} time_zone;
#endif

	int valid_PIN;

	struct
	{
		unsigned short year;
		unsigned short month;
		unsigned short day;
		unsigned short hour;
		unsigned short minute;
		unsigned short second;
	} record_time_and_date;

	struct
	{
		unsigned short hours;
		unsigned short minutes;
		unsigned short seconds;
	} PlayList_duration;

	unsigned short maker_ID;
	unsigned short maker_model_code;
	unsigned short channel_number;
	int channel_name_length;
	char channel_name[21];
	int PlayList_name_length;
	char PlayList_name[256];
	int PlayList_detail_length;
	char PlayList_detail[1201];
};


/// Blu-ray rewritable Play List definition
struct SBDREPlayList
{
	TBDREItemID playList_id;    				///< play-list id (value of the xxxxx portion of the "xxxxx.rpls/.vpls" play list file name)
	T_PLAYLIST_TYPE pl_type;					///< play-list type: real or virtual
	struct _ui_info ui_info;					///< User Interface info regarding a PlayList
	int number_of_PlayList_marks;    			///< number of Mark entries in PlayListMark()
	unsigned short ref_menu_thmb_idx;       	///< menu thumbnail index in menu.tidx extracted from PlayListMark()
	int number_of_PlayItems;					///< number of PlayItems in the PlayList, needed to query for Clip Marks in each PlayItem
};

/// Blu-ray rewritable PlayItem definition
struct SBDREPlayItem
{
	int number_of_Clip_marks;					///< number of Clip Marks, -1 if none
	int number_of_BridgeClip_marks;				///< number of Bridg Clip Marks, -1 if none
	TBDREItemID clip_id;						///< "zzzzz" part of Clip name zzzzz.clpi
	TBDREItemID bridge_clip_id;					///< "zzzzz" part of Bridge Clip name zzzzz.clpi
};

/// Blu-ray rewritable stream definition
struct SBDREStream
{
	unsigned short stream_PID;					///< PID value for the elementary stream described in the PMT referred to by the program-sequence
	struct SBDREStreamCodingInfo StreamCodingInfo;
};

/// Blu-ray rewritable Program Sequence definition
struct SBDREProgrSequence
{
	unsigned char num_of_streams_in_ps;			///< number of elementary streams defined in the program-sequence
	unsigned char num_of_groups;				///< indicates the number of groups of elementary streams defined in the program-sequence

	struct SBDREStream stream[32];

	struct SGroup
	{
		unsigned char num_of_streams_in_group;	///< number of elementary streams contained in the j-th group of elementary streams of the program-sequence
		unsigned char ref_to_stream_index[32];	///< stream_index value referred to by the elementary stream that is contained in the j-th group of elementary streams of the program-sequence
	}
	group[3];
};

///\defgroup BDREMARKTYPE Blu-ray rewritable mark types
/// Constants identifying mark types that can be use in playback commands.
/// It is a subset of the values in Table 4-9
///@{
#define BDRE_MARK_SKIP_START	6	///< identifies skip-start marks

#define BDRE_MARK_CHAPTER		5	///< identifies chapter marks

#define BDRE_MARK_FAVORITE		4	///< identifies favorite (bookmark) marks

#define BDRE_MARK_RESUME		3	///< identifies resume marks

#define DCCHD_BDRE_MARK_ANY		-1	///< DCC-HD convention for specifying mark of any of the above types
///@}


/// Blu-ray rewritable Mark definition
struct SBDREMark
{
#if (RMENDIANNESS == RMBIGENDIAN)
	/// 1: Mark entry has invalid information; Otherwise, mark entry has valid information
	unsigned int mark_invalid_flag:1;

	/// Type of the Mark, coded according to Table 4-9; Allowed values 0x00 - 0x3F
	unsigned int mark_type:7;
#elif (RMENDIANNESS == RMLITTLEENDIAN)
	/// type of the Mark, coded according to Table 4-9; Allowed values 0x00 - 0x3F
	unsigned int mark_type:7;

	/// 1: Mark entry has invalid information; Otherwise, mark entry has valid information
	unsigned int mark_invalid_flag:1;
#endif

	/// Length (in bytes) of the mark name

	/// The mark name is found
	/// in the mark_name field
    unsigned char mark_name_length;

	/// Identifies the manufacturer of the recorder that made the mark
	unsigned short maker_ID;

	/// PlayItem_id value of the PlayItem on which the Mark is placed
	unsigned short ref_to_PlayItem_id;

	/// Time position of the mark
	unsigned int mark_time_stamp;

	/// The PID of the transport packets that contain the elementary stream that is pointed to by the Mark

	/// If -1 (0xFFFF), the Mark is a pointer to the time-line that is common for all elementary streams
	/// used by the PlayList
	unsigned short entry_ES_PID;

	/// The thumbnail_index value defined in the menu.tidx file that corresponds to the thumbnail attached to the mark

	/// If -1 (0xFFFF) the Mark
	/// has no thumbnail-picture attached to it
	unsigned short ref_to_menu_thumbnail_index;

	/// The thumbnail_index value defined in the mark.tidx file that corresponds to the thumbnail attached to the mark

	/// If -1 (0xFFFF) the Mark
	/// has no thumbnail-picture attached to it
	unsigned short ref_to_mark_thumbnail_index;

	/// Duration of the segment identified by the mark

	/// Measured in 45 kHz units on the global time axis of the PlayList, starts from #mark_time_stamp
	/// If set to 0, mark has no duration, identifies only a position
	unsigned int duration;

	/// Optional recorder-specific mark information
	unsigned int makers_information;

	/// Name of the Mark

	/// Coded in SBDREPlayListMark::PlayList_character_set characters
	/// and of length #mark_name_length
	char mark_name[25];
};

/// Blu-ray rewritable PlayList Mark definition
struct SBDREPlayListMark
{
	/// character set used in the mark name
	enum EBDRECharSet PlayList_char_set;

	/// Current mark index
	/// \note  This value is updated ONLY during playback with the index
	///        of the current mark from the PlayListMark list sorted
	///        in ascending order by ref_to_STC_id and mark_time_stamp.
	///        This index might be NOT the same as the index in the original
	///        PlayListMark structure read from the PlayList file because
	///        in the original PlayListMark the marks are unsorted.
	int mark_id;

	/// detailed mark information
	struct SBDREMark mark;
};

/// Blu-ray rewritable Clip Mark definition
struct SBDREClipMark
{
#if (RMENDIANNESS == RMBIGENDIAN)
	unsigned int mark_invalid_flag:1;
	unsigned int mark_type:7;
#elif (RMENDIANNESS == RMLITTLEENDIAN)
	unsigned int mark_type:7;
	unsigned int mark_invalid_flag:1;
#endif
	unsigned char ref_to_STC_id;
	unsigned int mark_time_stamp;
	unsigned short entry_ES_PID;
	unsigned short ref_to_mark_thumbnail_index;
	unsigned int representative_picture_time_stamp;
	unsigned int duration;
	unsigned int makers_information;
};

/// Blu-ray rewritable Thumbnail information
struct SBDREThumbnail
{
	unsigned int thmbn_type;
	unsigned int picture_byte_size;
	unsigned short horizontal_picture_size;
	unsigned short vertical_picture_size;
};


/// Status info structure for the Blu-ray rewritable control object (navigator)

/// Uses \ref SBDREFLAGS values
/// in addition to the generic \ref SFLAGS and \ref SLPBFLAGS
///\ingroup BDRECTRLDEFS
struct SBDREStatus
#ifdef __cplusplus
                    : public SStatus
{
#else
{
    struct SStatus common;  /// basic status info, common to any control object
#endif

	/// currently playing video stream; all fields are valid
    struct SBDREStream video;

	/// currently playing audio stream
    struct SBDREStream audio;

	/// currently playing pg stream
	struct SBDREStream pg;

	/// MPEG2 PES private stream (teletext), it present
	struct SBDREStream pes_private;

	/// general information about the media
	struct SBDREDisc disc;

	/// information about a BDAV directory
    struct SBDAVDir bdavDir;

    /// currently playing play-list
    struct SBDREPlayList crtPlayList;

    /// current Program Sequence
    struct SBDREProgrSequence crtProgSeq;

	/// currently displayed play-list mark
	struct SBDREPlayListMark crtPlayListMark;
};

/// Blu-ray rewritable specific command definition
///\ingroup BDRECTRLDEFS
struct SBDRECommand
#ifdef __cplusplus
                    : public SCommand
{
#else
{
    struct SCommand common; ///< basic command info, common to any control object
#endif

    enum EBDRECmd cmd;

    /// first command parameter
    union
    {
        int selector;               ///< stream, button, register etc selector; -1 for default value
        int speed;                  ///< playback speed in nominal speed/1024 units
		char PIN[4];				///< PIN entered by the user
        enum EStopMode stopMode;    ///< identifies the behavior upon stopping
    }
    param1;

    /// second command parameter
    union
    {
        int selector;               ///< secondary selector (play item, mark, etc)
        UINT64 time;                ///< media position by media time
		char *bookmarkBuf;          ///< buffer for bookmark data or a user supplied buffer (e.g., thumbnail picture)
		/*void *buff_addr;			///< address of a user supplied buffer (e.g., thumbnail picture)*/
    }
    param2;

    /// third parameter
    union
    {
        TBDREItemID playListID;     ///< play list selector (based on file name)
    }
    param3;
};

/// Blu-ray rewritable specific result definition \ingroup BDRECTRLDEFS
struct SBDREResult
#ifdef __cplusplus
                    : public SResult
{
#else
{
    struct SResult common; ///< basic result info, common to any control object
#endif

    /// Blu-ray rewritable specific result definitions
    union
    {
        struct SBDREPlayList play_list;			///< returned play list information
		struct SBDREPlayListMark pl_mark_info;	///< returned play list mark information
		struct SBDREPlayItem play_item;			///< returned play item information
		struct SBDREClipMark clip_mark_info;	///< returned clip mark information
        struct SBDREStream stream;    			///< returned stream information
		struct SBDREThumbnail thumbnail;		///< returned thumbnail information
        int size;               				///< returned buffer size
    }
    info;
};

/// \class DCCHD_BDRE::CNavigator
/// Playback control class for BD-RE media.
///
/// The interface to this class is completely defined by \ref BDREMSDEFS and DCCHD::IPlaybackControl
/// \ingroup controlimpl

#endif //_CDEFS_BDRE_H_

