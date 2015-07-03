/*****************************************
 Copyright  2005  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   cdefs_cdda.h
  @brief  CD-DA definitions shared with middleware clients
  
  @author Sorin Papuc
  @date   2005-10-18
  
  $Header: /bigbig/dungeon/dcchd_project/dcchd/curacao/cdefs_cdda.h,v 1.31 2007-05-14 23:34:26 dnguyen Exp $
*/

#ifndef _CDEFS_CDDA_H_
#define _CDEFS_CDDA_H_

#include <cdefs.h>

///\defgroup CDDAMSDEFS CD-DA Media Space Definitions
/// Definitions for media with #TMediaType of #MTYPE_APP_CDA
///\ingroup MEDSPACES

///\defgroup CDDACTRLDEFS CD-DA Control Definitions
/// Control definitions for media with #TMediaType of #MTYPE_APP_CDA
///\ingroup CDDAMSDEFS
///@{
#define MEDIA_SPACE_CDDA           2     ///< CD-DA media space, to identify SCDDACommand, SCDDAStatus and SCDDAResult structures \ingroup MSID
 
///@}

///\defgroup SCDDAFLAGS CD-DA flags for status validation and change notification
/// Constants identifying individual status fields in the changes and flags fields.
///
///\ingroup CDDACTRLDEFS 
//@{
#define SCDDASTATUS_DISC         (SSTATUS_LAST_GENERIC << 1)  ///< identifies the disc field; events are trigered when the disc changes

#define SCDDASTATUS_TRACK        (SSTATUS_LAST_GENERIC << 2)  ///< identifies the track field; events are triggered when the track changes

///@}

/// kept around for backward compatibility \deprecated
#define SCDDASTATUS_MODE         	SSTATUS_MODE

///\defgroup CDDAMFLAGS CD-DA specific flags for playback mode description
/// Constants identifying individual playback modes, used in the SCDDAStatus::mode::flags field.
/// Used in addition to \ref MFLAGS
///\ingroup CDDACTRLDEFS 
///@{

#define SCDDASTATUS_MODE_REPEAT_TRACK              (SSTATUS_MODE_LAST << 1)    ///< if set, current track will be repeated forever

#define SCDDASTATUS_MODE_REPEAT_DISC               (SSTATUS_MODE_LAST << 2)    ///< if set, disc will be repeated forever with tracks in the number order

#define SCDDASTATUS_MODE_REPEAT_RANDOM             (SSTATUS_MODE_LAST << 3)    ///< if set, disc will be repeated forever with tracks in random order

#define SCDDASTATUS_MODE_REPEAT_AB             	   (SSTATUS_MODE_LAST << 4)    ///< if set, disc will be repeated forever between two points

#define SCDDASTATUS_MODE_REPEAT_AB_PENDING     	   (SSTATUS_MODE_LAST << 5)    ///< if set, the starting point of #CDDA_REPEAT_AB mode has been set but not the ending point

#define SCDDASTATUS_MODE_REPEAT_MASK               (SCDDASTATUS_MODE_REPEAT_TRACK | SCDDASTATUS_MODE_REPEAT_DISC | SCDDASTATUS_MODE_REPEAT_RANDOM | SCDDASTATUS_MODE_REPEAT_AB | SCDDASTATUS_MODE_REPEAT_AB_PENDING)

///@}

/// CD-DA specific command values
///
///\ingroup CDDACTRLDEFS
enum ECDDACmd
{
    CDDACmd_Play = 1,	///< Starts or resumes the playback process
    
    CDDACmd_Pause,		///< Pauses the playback process
    
    CDDACmd_Seek,		///< Seeks to the track specified in SCDDACommand::param1::track at time position specified in SCDDACommand::param2:time

    CDDACmd_NextTrack,	///< Go to the next track. If the current track is the last track of the cd, the first track is selected.

    CDDACmd_PrevTrack,	///< Go to the previous track. If the current track is the first track of the cd, this function has no effect.

    CDDACmd_Repeat,		///< Enters the repeat mode specified in SCDDACommand::param1::repeat

    CDDACmd_FastForward,///< enter fast forward playback mode with the speed specified in the speed in SCDDACommand::param1::speed

    CDDACmd_Rewind,     ///< enter fast reverse playback mode with the speed specified in the speed in SCDDACommand::param1::speed
    
    CDDACmd_Stop,    	///< Stops the playback process
    
    CDDACmd_GetTrackInfo,  	///< Retrieves in SCDDAResult::info.track the information about the track specified in SCDDACommand::param1.track \change Added 3-30-2007
};


/// Track info definition \change Added 3-30-2007
struct SCDDATrackInfo
{
    UINT32 number;      ///< track number
    UINT32 start;       ///< track start time (in seconds, relative to beginning of the disc)
    UINT32 duration;    ///< track duration (in seconds)

    int copyrighted;    ///< whether digital copy is prohibited
    int preemphasis;    ///< whether the audio is with or without pre-emphasis
    TMediaType type;    ///< track audio type (PCM or DTS)
};

/// Status info structure for the CD-DA control object (navigator)

/// Status information is contained in the PSR registers is not duplicated in explicit status fields,
/// rather the register must be queried
///
/// Uses \ref SCDDAFLAGS values in addition to the generic \ref SFLAGS and \ref SLPBFLAGS
///\ingroup CDDACTRLDEFS
struct SCDDAStatus 
#ifdef __cplusplus
                : public SStatus
{
#else
{
    struct SStatus common;  ///< basic status info, common to any control object
#endif

    /// Disc info
    struct
    {
        UINT32 duration;    ///< disc duration
        UINT32 tracks;      ///< number of tracks on disc
		UINT32 firstTrack;  ///< first track number \change Added 05/10/2007
    }
    disc;
    
    /// Current track info
    struct SCDDATrackInfo track;
};

/// CDDA Repeat Modes
enum ECDDARepeatMode
{
    CDDA_REPEAT_NONE = 0,   ///< no repeat
    CDDA_REPEAT_TRACK = 1,  ///< repeat current track
    CDDA_REPEAT_DISC = 2,   ///< repeat all tracks in sequential order
    CDDA_REPEAT_RANDOM = 3, ///< repeat all tracks in random order
    CDDA_REPEAT_AB = 4      ///< repeat between 2 user-defined positions, the command needs to be called twice: first to set the starting position (at the current position) and then the ending position
};

/// CD-DA specific command definition
///\ingroup CDDACTRLDEFS
struct SCDDACommand
#ifdef __cplusplus
					 : public SCommand
{
#else
{
	struct SCommand common;	///< basic command atructure, common to any control object
#endif
    enum ECDDACmd cmd;

    /// first command parameter
    union
    {
        enum ECDDARepeatMode repeat;    ///< repeat mode
        int track;          			///< track number
        int speed;          			///< playback speed in nominal speed/1024 units
    }
    param1;
    
    /// second command parameter
    union
    {
        struct SMediaTime time;     ///< seek position (h, m, s, frames)
    }
    param2;
};

/// CDDA specific result definition
///\ingroup CDDACTRLDEFS
struct SCDDAResult 
#ifdef __cplusplus
                  : public SResult
{
#else
{
    struct SResult common;  ///< basic result info, common to any control object
#endif
    /// CDDA specific result value
    union
    {
    	struct SCDDATrackInfo track;
    }
    info;
};

/// \class DCCHD_CDDA::CCddaNavigator
/// Playback control class for CD-Audio media
///
/// The interface to this class is completely defined by \ref CDDAMSDEFS and DCCHD::IPlaybackControl
/// \ingroup controlimpl

#ifdef __DOC__
/// CD-DA specific code
namespace DCCHD_CDDA
{
}
#endif

#endif // _CDEFS_CDDA_H_
