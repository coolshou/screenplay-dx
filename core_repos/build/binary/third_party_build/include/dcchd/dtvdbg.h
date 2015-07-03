/*****************************************
 Copyright  2007 -2008
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *******************************************/

/**
 @file   dtvdbg.h
 @brief  DTV playback control header

 @author Jake Lee
 @date   2/20/2008

 $Revision: 1.2 $  $Date: 2008-09-16 18:09:49 $
 */
#ifndef DTVDBG_H_
#define DTVDBG_H_

/// DTV debugging flags
#define DFN_ENTER       DCCHD_DBG_TRACE | DCCHD_DBG_CODE_ISSUE  ///< messages at entering in the main functions
#define DFN_CHK         DCCHD_DBG_CHECK | DCCHD_DBG_CODE_ISSUE  ///< messages in the functions - important
#define DFN_INFO        DCCHD_DBG_INFO  | DCCHD_DBG_DATA_ISSUE  ///< message for info
#define DFN_DATA        DCCHD_DBG_TRACE | DCCHD_DBG_DATA_ISSUE  ///< message for data trace

// errors
#define DFN_FATAL        DCCHD_DBG_FATAL | DCCHD_DBG_CODE_ISSUE          // fatal error (*#Iii$^Buff@$*&%)
#define DFN_ERR          DCCHD_DBG_UNEXPECTED    | DCCHD_DBG_CODE_ISSUE  // soft error - execution can be continued


#endif /*DTVDBG_H_*/

/*
  $Log: dtvdbg.h,v $
  Revision 1.2  2008-09-16 18:09:49  sorin
  BugId: none
  Applied established naming convention to control definitions file

  Revision 1.1  2008-09-16 17:47:43  sorin
  BugId: none
  Renamed debug utility definition file to avoid abuse of established naming convention (cdefs_xxx.h are high level public control definitions).

  Revision 1.1  2008-09-15 22:45:07  jakel

  BugId:none
  Add tuner support for DTV

 */
