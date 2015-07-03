/*****************************************
 Copyright  2009
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   bd_common.h
  @brief  Blu-ray media definitions shared with middleware clients
  
  @author Simon Botond
  @date   2009-02-01
  
  $Header: /bigbig/dungeon/dcchd_project/dcchd/brd/bd_common.h,v 1.2 2009-06-24 14:37:07 bsimon Exp $

*/

#ifndef _BD_COMMON_
#define _BD_COMMON_



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





/// Coding information for Blu-ray presentation graphics elementary streams    
struct SPGCodingInfo
{
    RMuint32 PG_language_code;
};

/// Coding information for Blu-ray interactive graphics elementary streams    
struct SIGCodingInfo
{
    RMuint32 IG_language_code;
};

/// Coding information for Blu-ray text subtitles elementary streams   
struct STSCodingInfo
{
    RMuint32          TS_language_code;
    enum EBDCharCode  character_code;
};


#endif /* _BD_COMMON_ */

