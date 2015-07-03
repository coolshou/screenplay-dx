/*****************************************
 Copyright  2005  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

#ifndef __DRM_CONFIG_H__
#define __DRM_CONFIG_H__

/// \defgroup drmslots DRM Xtask Preloading slot management
///
/// Controls the order in which DRM xtasks are loaded.
///
/// Place unused DRMs after #DRM_UNUSED, place used ones, in loading order, after #DRM_USED
///
///	Attempting to load an unused DRM generates an error.
/// \ingroup config
///@{
enum {
	DRM_UNUSED=-100,			///< Head of the unused DRM list, place any unused DRM declaration after it but  before #DRM_USED
	
	DRM_USED=-1, 				///< Head of the used DRM list, place any used DRM declaration after it
	DRM_AACS_XTASK_SLOT,		///< Slot # for the pre-loaded AACS xtask.
	DRM_BDPLUS_XTASK_SLOT,		///< Slot # for the pre-loaded BD+ xtask.
	DRM_CSS_XTASK_SLOT,			///< Slot # for the pre-loaded CSS xtask.
	DRM_CPRM_XTASK_SLOT,		///< Slot # for the pre-loaded CPRM xtask.
	DRM_AWM_XTASK_SLOT,             ///< Slot # for the pre-loaded Verrance Audio watermark xtask.
	DRM_CARDEA_XTASK_SLOT, 		///< Slot # for the pre-loaded Cardea xtask.
	DRM_BDCPS_XTASK_SLOT,		///< Slot # for the pre-loaded BDCPS xtask.
	DRM_DTCPIP_XTASK_SLOT,		///< Slot # for the pre-loaded DTCPIP xtask.
	DRM_JANUS_XTASK_SLOT,		///< Slot # for the pre-loaded JANUS xtask.
};
///@}

#endif //__DRM_CONFIG_H__

