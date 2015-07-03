/*****************************************
 Copyright  2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   cdefs_bdj.h
  @brief  BD-J control definitions
  
  @author Sorin Papuc
  @date   2007-05-24

  $Header: /home/cvsroot/dcchd/brd/cdefs_bdj.h,v 1.3 2007/06/06 19:26:39 sorinp Exp $
  
*/

#ifndef CDEFS_BDJ_H_
#define CDEFS_BDJ_H_

// include HDMV media space definitions
#include "cdefs_brd.h"


///\defgroup BDJMSDEFS BD-J Media Space Definitions
/// Definitions for Blu-ray BD-J playback.
///
/// They apply to #MTYPE_APP_BDJ #TMediaType values
///
/// Note: BD-J media space includes the \ref BRDMSDEFS
///\ingroup MEDSPACES

///\defgroup BDJCTRLDEFS BD-J Control Definitions
/// Control definitions for the BD-J media space.
///
/// Consist in the \ref BRDCTRLDEFS
/// plus BD-J specific flags, values and commands defined here
///\ingroup BDJMSDEFS
///@{

#define MEDIA_SPACE_BDJ	11     ///< identifies BD-J media space parameters for IPlaybackControl interface \ingroup MSID 

///@}

///\defgroup SBDJFLAGS BD-J status flags
/// Constants identifying individual BD-J events.
///


/// BD-J commands, in addition to #EBRDCmd

/// Use these values in the SBRDCommand::cmd field, as if they were #EBRDCmd values
///
/// All the #EBRDCmd HDMV user operation values are also supported and used either as such or
/// mapped onto the corresponding #BDJCmd_key_event event, as per Part 3-1 par. 3.6
///\ingroup BDJCTRLDEFS
enum EBDJCmd
{
	BDJCmd_key_event = BRDCmd_first_after_hdmv, ///< triggers the key event in SBRDCommand::param2::selector
}; 


/// BD-J key event codes, see Blu-ray spec Part 3-1 paragraph 3.6.3

/// When appropriate, the key events are mapped onto HDMV user operations
/// as described in each case
enum EBDKeyCode
{
	BDJ_VK_0=0,								///< mapped onto EBRDCmd::BRDCmd_select_button 0
	BDJ_VK_1,								///< mapped onto EBRDCmd::BRDCmd_select_button 1
	BDJ_VK_2,								///< mapped onto EBRDCmd::BRDCmd_select_button 2
	BDJ_VK_3,								///< mapped onto EBRDCmd::BRDCmd_select_button 3
	BDJ_VK_4,								///< mapped onto EBRDCmd::BRDCmd_select_button 4
	BDJ_VK_5,								///< mapped onto EBRDCmd::BRDCmd_select_button 5
	BDJ_VK_6,								///< mapped onto EBRDCmd::BRDCmd_select_button 6
	BDJ_VK_7,								///< mapped onto EBRDCmd::BRDCmd_select_button 7
	BDJ_VK_8,								///< mapped onto EBRDCmd::BRDCmd_select_button 8
	BDJ_VK_9,								///< mapped onto EBRDCmd::BRDCmd_select_button 9

	BDJ_VK_LEFT,							///< mapped onto EBRDCmd::BRDCmd_move_left_selected_button
	BDJ_VK_UP,								///< mapped onto EBRDCmd::BRDCmd_move_up_selected_button
	BDJ_VK_RIGHT,							///< mapped onto EBRDCmd::BRDCmd_move_right_selected_button
	BDJ_VK_DOWN,							///< mapped onto EBRDCmd::BRDCmd_move_down_selected_button
	BDJ_VK_ENTER,							///< mapped onto EBRDCmd::BRDCmd_activate_button

	BDJ_VK_COLORED_KEY_0,					///< not mapped on any HDMV commands
	BDJ_VK_COLORED_KEY_1,					///< not mapped on any HDMV commands
	BDJ_VK_COLORED_KEY_2,					///< not mapped on any HDMV commands
	BDJ_VK_COLORED_KEY_3,					///< not mapped on any HDMV commands

	BDJ_VK_A,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_A java key code
	BDJ_VK_B,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_B java key code
	BDJ_VK_C,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_C java key code
	BDJ_VK_D,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_D java key code
	BDJ_VK_E,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_E java key code
	BDJ_VK_F,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_F java key code
	BDJ_VK_G,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_G java key code
	BDJ_VK_H,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_H java key code
	BDJ_VK_I,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_I java key code
	BDJ_VK_J,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_J java key code
	BDJ_VK_K,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_K java key code
	BDJ_VK_L,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_L java key code
	BDJ_VK_M,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_M java key code
	BDJ_VK_N,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_N java key code
	BDJ_VK_O,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_O java key code
	BDJ_VK_P,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_P java key code
	BDJ_VK_Q,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_Q java key code
	BDJ_VK_R,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_R java key code
	BDJ_VK_S,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_S java key code
	BDJ_VK_T,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_T java key code
	BDJ_VK_U,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_U java key code
	BDJ_VK_V,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_V java key code
	BDJ_VK_W,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_W java key code
	BDJ_VK_X,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_X java key code
	BDJ_VK_Y,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_Y java key code
	BDJ_VK_Z,								///< defined in addition to the Blu-ray spec in order to support Blu-ray discs, mapped to the VK_Z java key code

	BDJ_VK_CANCEL,							///< defined in addition to the Blu-ray spec in order to support Blu-ray test discs, mapped to the VK_CANCEL java key code

	BDJ_VK_code_count,						///< number of key codes handled
	
	BDJ_VK_KEYPRESSED = 0x100,				///< flag for specifying the key press action \note Multiple #BDJ_VK_KEYPRESSED events for the same key code may be generated, denoting the key is being autorepeated
	BDJ_VK_KEYRELEASED = 0x200,				///< flag for specifying the key release action \note One and only one #BDJ_VK_KEYRELEASED event is generated after one or more #BDJ_VK_KEYPRESSED events for the same key code, denoting the key has being released
	BDJ_VK_SINGLEKEY = 0x400,				///< flag for identifying the key action to be use for single key event processing
};

/* Current implementation (BRD navi class is inherited by the BD-J navi class)
 * does not allow BD-J specific structures, only additional values for the fields
 * in the BRD structures. Fortunatelly no new fields are needed 

/// Status info structure for the BD-J control object (navigator)

/// Includes the HDMV status annd associated flags
///
/// The additional BD-J fields use \ref SBDJFLAGS for validation and change notification
///\ingroup BDJCTRLDEFS
struct SBDJStatus
#ifdef __cplusplus
                    : public SBRDStatus
{
#else
{
    struct SBRDStatus hdmv;  ///< HDMV status
#endif
};

/// BD-J specific command definition
///\ingroup BDJCTRLDEFS
struct SBDJCommand 
#ifdef __cplusplus
                    : public SBRDCommand
{
#else
{
    struct SBRDCommand hdmv; ///< HDMV command parameters
#endif

    /// BD-J command parameters
    union
    {
    	enum EBDKeyCodes key;	///< key event key code
    }
    bdj;
};

/// BD-J specific result definition
///\ingroup BDJCTRLDEFS
struct SBDJResult 
#ifdef __cplusplus          
                    : public SBRDResult
{
#else
{
    struct SBRDResult hdmv; ///< HDMV results
#endif

    /// BD-J result definitions
    union
    {
    }
    bdj;
};

*/

/// \class DCCHD_BDJ::CNavigator
/// Playback control class for BD-J media
///
/// Implements the BD-J processing shared by any BD-J stack implementation and 
/// integrates the IBDJProvider interface into the DCC-HD/DirectFB framework.
///
/// The interface to this class is defined by \ref BDJMSDEFS and DCCHD::IPlaybackControl
/// \ingroup controlimpl


#endif /*CDEFS_BDJ_H_*/

/**
  $Log: cdefs_bdj.h,v $
  Revision 1.3  2007/06/06 19:26:39  sorinp
  typo

  Revision 1.2  2007/06/06 07:44:13  sorinp
  typo

  Revision 1.1  2007/06/06 07:01:41  sorinp
  Adding BD-J support

 */

