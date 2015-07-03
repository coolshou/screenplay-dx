/*****************************************
 Copyright  2005  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   cdefs_vcd.h
  @brief  (Super) VideoCD definitions shared with middleware clients
  
  @author Sorin Papuc
  @date   2005-10-18
  
  $Log: cdefs_vcd.h,v $
  Revision 1.12  2007-05-08 19:29:41  sorinp
  BUGCT:3208 - 3213 Added stopMode parameter to Stop command in all media spaces to allow client module to control behavior

  Revision 1.11  2006/10/13 20:22:48  sorinp
  Moved the userTimeout and mode fields from LPB to generic status in order to allow single-point processing of the status in CPlaybackControl

  Revision 1.10  2006/09/24 03:37:07  sorinp
  Working Media UIN for VFS-based access, propagated API changes

  Revision 1.9  2006/08/30 18:53:16  sorinp
  Changed the statistics info definition and moved the filed from the LPB into the generic media space

  Revision 1.8  2006/04/19 04:23:36  mfedoreanu
  moved Media time from specific format status to common status

  Revision 1.7  2006/01/30 02:46:12  sorinp
  Clarified media sapce - media type correspondence

  Revision 1.6  2005/11/16 00:05:47  dnguyen
  changed all bool struct members to int because the difference between mips
  C compiler (where bool is 32-bit) and C++ compiler (bool is 8-bit) can be
  catastrophic

  Revision 1.5  2005/11/09 22:23:31  sorinp
  work in progress

  Revision 1.4  2005/10/29 16:56:29  sorinp
  work in progress

  Revision 1.3  2005/10/26 19:17:50  sorinp
  typo

  Revision 1.2  2005/10/26 19:15:50  sorinp
  reorganized media spece identifiers

  Revision 1.1  2005/10/18 18:03:32  sorinp
  initial CDDA, VCD and DVD control definitions
  Cleaned-up DVD-VR control definitions, work in progress

*/

#ifndef _CDEFS_VCD_H_
#define _CDEFS_VCD_H_

#include <cdefs.h>

///\defgroup VCDMSDEFS (Super) VideoCD Media Space Definitions
/// Definitions for media with #TMediaType of #MTYPE_APP_VCD
///\ingroup MEDSPACES

///\defgroup VCDCTRLDEFS VCD Control Definitions
/// Control definitions for media with #TMediaType of #MTYPE_APP_VCD
///\ingroup VCDMSDEFS
///@{
#define MEDIA_SPACE_VCD           3     ///< (Super) VideoCD media space, to identify structures derived from SCommand, SStatus and SResult 
///@}

///\defgroup VCDMFLAGS CD-DA specific flags for playback mode description
/// Constants identifying individual playback modes, used in the SVCDStatus::mode::flags field. Used in addition to \ref MFLAGS
///\ingroup VCDCTRLDEFS 
///@{

#define SVCDSTATUS_MODE_REPEAT_ENTRY              (SSTATUS_MODE_LAST << 1)    ///< if set, entry will be repeated forever

#define SVCDSTATUS_MODE_REPEAT_TRACK              (SSTATUS_MODE_LAST << 2)    ///< if set, current track will be repeated forever

#define SVCDSTATUS_MODE_REPEAT_DISC               (SSTATUS_MODE_LAST << 3)    ///< if set, disc will be repeated forever with tracks in the number order

///@}

/// VCD-specific command values
///
///\ingroup VCDCTRLDEFS
enum EVCDCmd
{
    VCDCmd_PBCControl = 1,      ///< enables/disables PBC as specified in SVCDCommand::param1::enable

    VCDCmd_Play,

    VCDCmd_Pause,    

    VCDCmd_Stop,

    VCDCmd_Next,

    VCDCmd_Previous,

    VCDCmd_FastForward,     ///< enter fast forward playback mode with the speed specified in the speed in SVCDCommand::param1::speed

    VCDCmd_Rewind,          ///< enter fast reverse playback mode with the speed specified in the speed in SVCDCommand::param1::speed

    VCDCmd_Seek,            ///< Seeks to the track or play item specified in SVCDCommand::param1::selector at time position specified in SCDDACommand::param2:pos (seconds)
    
    VCDCmd_DefaultSelection,

    VCDCmd_Return,

    VCDCmd_NumericSelection,     ///< makes the numeric selection specfied in SVCDCommand::param1::selector
    
};

/*
    
    VCDCmd_GetTrackDuration (RMTvcdNavApi self, RMuint32 TrackNumber, RMuint32 *pSeconds);

    ///////////////////////////////////////////////////////////////////////////
    // karaoke specific functions
    ///////////////////////////////////////////////////////////////////////////
    
    VCDCmd_SetCountryCode_GetCharacterSet (RMTvcdNavApi self, RMint8 *pCountryCode, RMuint8 *pCharacterSet);
    VCDCmd_GetDiscTitle (RMTvcdNavApi self, RMint8 *pTitle, RMuint32 *pTitleLength);
    VCDCmd_GetDiscCatalogNumber (RMTvcdNavApi self, RMint8 *pCatalogNumber, RMuint32 *pCatalogNumberLength);
    VCDCmd_GetTotalNumberOfSequences (RMTvcdNavApi self, RMint8 *pNumberOfSequences, RMuint32 *pNumberOfSequencesLength);
    VCDCmd_GetDiscDescription (RMTvcdNavApi self, RMint8 *pCatalogNumber, RMuint32 *pCatalogNumberLength);
    VCDCmd_GetSequenceISRCcode (RMTvcdNavApi self, RMuint32 Sequence, RMint8 *pISRCcode, RMuint32 *pISRCcodeLength);
    VCDCmd_GetSequenceTitle (RMTvcdNavApi self, RMuint32 Sequence, RMint8 *pTitle, RMuint32 *pTitleLength);
    VCDCmd_GetSequenceTitleForSorting (RMTvcdNavApi self, RMuint32 Sequence, RMint8 *pTitle, RMuint32 *pTitleLength);
    VCDCmd_GetPerformersName (RMTvcdNavApi self, RMuint32 Sequence, RMint8 *pPerformersName, RMuint32 *pPerformersNameLength);
    VCDCmd_GetPerformersNameForSorting (RMTvcdNavApi self, RMuint32 Sequence, RMint8 *pPerformersName, RMuint32 *pPerformersNameLength);
    VCDCmd_GetSongWritersName (RMTvcdNavApi self, RMuint32 Sequence, RMint8 *pSongWritersName, RMuint32 *pSongWritersNameLength);
    VCDCmd_GetComposersName (RMTvcdNavApi self, RMuint32 Sequence, RMint8 *pComposersName, RMuint32 *pComposersNameLength);
    VCDCmd_GetArrangersName (RMTvcdNavApi self, RMuint32 Sequence, RMint8 *pArrangersName, RMuint32 *pArrangersNameLength);
    VCDCmd_GetPlayersName (RMTvcdNavApi self, RMuint32 Sequence, RMint8 *pPlayersName, RMuint32 *pPlayersNameLength);
    VCDCmd_GetSongHeader (RMTvcdNavApi self, RMuint32 Sequence, RMint8 *pSongHeader, RMuint32 *pSongHeaderLength);
    VCDCmd_GetSongText (RMTvcdNavApi self, RMuint32 Sequence, RMint8 *pSongText, RMuint32 *pSongTextLength);
    VCDCmd_GetKaraokeKey (RMTvcdNavApi self, RMuint32 Sequence, RMint8 *pKaraokeKey, RMuint32 *pKaraokeKeyLength);
    VCDCmd_GetOriginalKey (RMTvcdNavApi self, RMuint32 Sequence, RMint8 *pOriginalKey, RMuint32 *pOriginalKeyLength);
    VCDCmd_GetSequenceDescription (RMTvcdNavApi self, RMuint32 Sequence,RMint8 *pSequenceDescription, RMuint32 *pSequenceDescriptionLength);
*/

/// Status info structure for the VCD control object (navigator)

/// Status information is contained in the PSR registers is not duplicated in explicit status fields,
/// rather the register must be queried
///
/// Uses \ref SVCDFLAGS values in addition to the generic \ref SFLAGS and \ref SLPBFLAGS
///\ingroup VCDCTRLDEFS
struct SVCDdStatus 
#ifdef __cplusplus
                : public SStatus
{
#else
{
    struct SStatus common;  ///< basic status info, common to any control object
#endif
    
//     struct SStreamCodingInfo video;     ///< currently playing video stream
//     struct SStreamCodingInfo audio;     ///< currently playing audio stream
//     struct SStreamCodingInfo spu;       ///< currently playing sub-picture stream

    struct
    {
	    VCDCmd_GetFirstTrackNumber (RMTvcdNavApi self, RMuint32 *pNumberOfFirstTrack);
	    VCDCmd_GetLastTrackNumber(RMTvcdNavApi self, RMuint32 *pNumberOfLastTrack);
	    VCDCmd_GetCurrentTrackNumber(RMTvcdNavApi self, RMuint32 *pTrackNumber);
	    VCDCmd_GetNumberOfTracks (RMTvcdNavApi self, RMuint32 *pNumberOfTracks);
	
	    VCDCmd_GetDiscType (RMTvcdNavApi self, RMuint32 *pDiscType);
	    VCDCmd_GetNumberOfVolumes (RMTvcdNavApi self, RMuint32 *pNumberOfVolumes);
	    VCDCmd_GetVolumeNumber (RMTvcdNavApi self, RMuint32 *pVolumeNumber);
	    
	    VCDCmd_GetNumberOfAudioStreams (RMTvcdNavApi self, RMuint32 *pNumberOfAudioStreams);
    };
    


};

///\ingroup VCDCTRLDEFS

/// VCD specific command definition
struct SVCDCommand
#ifdef __cplusplus
                 : public SCommand
{
#else
{
    struct SCommand common;  ///< basic command info, common to any control object
#endif
    enum EVCDCmd cmd;

    /// first command parameter
    union
    {
        int selector;
        int enable;
        
        int speed;                  ///< playback speed in nominal speed/1024 units
        enum EStopMode stopMode;	///< identifies the behavior upon stopping \status TBI
    }
    param1;
    
    /// second command parameter
    union
    {
        unsigned int pos;     ///< seek position inside the track/play item (in seconds)
    }
    param2;     
};

///\ingroup VCDCTRLDEFS

/// VCD specific result definition
struct SVCDResult
#ifdef __cplusplus
                : public SResult
{
#else
{
    struct SResult common;  ///< basic result info, common to any control object
#endif
    /// VCD specific result value
    union
    {
    }
    info;
};

#endif // _CDEFS_VCD_H_
