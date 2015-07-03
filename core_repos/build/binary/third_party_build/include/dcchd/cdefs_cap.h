/**
 @file   cdefs_cap.h
 @brief  Capture playback control header

 @author Sivalingam Sivaruban
 @date   12/15/2008
*/

#ifndef _CDEF_CAP_PBC_H__
#define _CDEF_CAP_PBC_H__

#include "cdefs.h"

#define MEDIA_SPACE_CAP      13


enum ECAPCmd
{
	CAPCmd_PLAY = 1,
	CAPCmd_STOP,
	CAPCmd_LASTCMD	

};

struct SCAPStatus
#ifdef __cplusplus
: public SStatus
{
#else
{
struct SStatus common;  ///< basic status info, common to any control object
#endif
//    struct SCAPStreamInfo video;     ///< currently playing video stream
//    struct SCAPStreamInfo audio;     ///< currently playing audio stream
};


/// Capture playback command structure.
struct SCAPCommand
#ifdef __cplusplus
: public SCommand
{
#else
{
    struct SCommand common; ///< basic command info, common to any control object
#endif
    enum ECAPCmd cmd;  ///< command code
};

struct SCAPResult
#ifdef __cplusplus
: public SResult
{
#else
{
    struct SResult common; ///< basic result info, common to any control object
#endif
//    struct SCAPStreamInfo streamInfo; ///< stream information
};



#endif



