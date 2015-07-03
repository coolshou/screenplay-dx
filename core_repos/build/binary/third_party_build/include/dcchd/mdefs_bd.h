/*****************************************
 Copyright  2009
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   mdefs_bd.h
  @brief  Blu-ray media definitions shared with middleware clients
  
  @author Simon Botond
  @date   2009-02-01
  
  $Header: /bigbig/dungeon/dcchd_project/dcchd/brd/mdefs_bd.h,v 1.2 2009-05-07 13:29:37 bsimon Exp $

*/

#ifndef _MDEFS_BD_
#define _MDEFS_BD_


/// Blu-ray elementary stream types (table 5-16)  
//
//  As PG is used commonly by BD-ROM and BD-RE, the it's coding type _must_
//  be the same in both, the same AllocSubstream() is called by both of them
enum EBDCodingType
{
    BD_PG = 0x90,      		///< Presentation Graphics
    BD_IG,             		///< Interactive Graphics
    BD_TS,             		///< Text Subtitles
};

/// Blu-ray video formats
// 
//   Note: each navigator/pres. eng. can define it's own list of video
//      formats, but care must be taken to list every possible video
//      format in this table.
enum EBDVideoFormat
{
    BD_VideoFormat_Uninitialized,
    BD_VideoFormat_480i,
    BD_VideoFormat_576i,
    BD_VideoFormat_480p,
    BD_VideoFormat_1080i,
    BD_VideoFormat_720p,
    BD_VideoFormat_1080p,
    BD_VideoFormat_576p
};


/// Coding information for Blu-ray presentation graphics elementary streams    
struct SPGCodingInfo
{
    RMuint32 PG_language_code;    /// the navigator tells the pres. eng. the language code when AllocSubtream()-s the PG
};

/// Coding information for Blu-ray interactive graphics elementary streams    
struct SIGCodingInfo
{
    RMuint32 IG_language_code;    /// the navigator tells the pres. eng. the language code when AllocSubtream()-s the IG
};

/// Blu-ray subtitle character codes (table 5-22)
enum EBDCharCode
{
    CharCode_UTF8 = 1,
    CharCode_UTF16_BigEndian,
    CharCode_JIS,
    CharCode_KSC,
    CharCode_GB18030,
    CharCode_GB2312,
    CharCode_BIG5
};

/// Coding information for Blu-ray text subtitles elementary streams   
struct STSCodingInfo
{
    UINT32 TS_language_code;      /// the navigator tells the pres. eng. the language code when AllocSubtream()-s the TS
    char character_code;          /// #EBDCharCode values
};


///\ingroup BRDMEDDEFS 

/// Coding information associated with a Blu-ray elementary stream
struct SBDStreamCodingInfo
{
    unsigned char stream_coding_type; ///< #EBDCodingType values
    
    union 
    {
        struct SPGCodingInfo pg;			///< coding info for presentation graphics substream
        struct SIGCodingInfo ig;			///< coding info for interactive graphics substream
        struct STSCodingInfo ts;			///< coding info for text subtitle substream
    }
    stream;
};

#endif /* _MDEFS_BD_ */

