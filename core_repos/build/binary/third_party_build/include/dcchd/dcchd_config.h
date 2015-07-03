/*****************************************
 Copyright  2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   dcchd_config.h
  @brief  Sigma Designs DCC-HD SDK definitions for SMP 8652

  @author Sorin Papuc
  @date   2009-04-01

  $Log: dcchd_config.h,v $
  Revision 1.7  2009-08-15 02:27:15  sorin
  BugId: none
  Fixed DFB memory size calculation

  Revision 1.6  2009-08-15 02:05:44  sorin
  BugId: none
  Better fix for incompatibility for non Bluray configuration.

  Revision 1.4  2009-06-26 01:49:10  sorin
  BugId: CT-6905
  SEND_COMMENT_BUGZILLA
  Move  video, audio and MONO objects inside the DirectFB area in order to maximize the amount of memory available to each of them when used individually.

  Revision 1.3  2009-05-13 23:20:21  smanciulea
  BugId: none
  -  move the group 'dspres' before 'awiring' because RMCFG_AUDIO_ENGINE_CNT might not be defined in the compile command

  Revision 1.2  2009-04-27 22:22:01  sorin
  BugId: none
  Fixed single bank memory map

  Revision 1.1  2009-04-25 01:41:11  sorin
  BugId: none
  Added CRT scaler definition support

  Revision 1.4  2009-04-25 00:33:29  sorin
  BugId: none
  Allow both-compile time and run-time configuration of available scalers

  Revision 1.3  2009-04-01 22:37:12  sorin
  BugId: none
  Typo

  Revision 1.2  2009-04-01 22:24:45  sorin
  BugId: none
  Added Blu-ray objects, limited to AVCHD level

  Revision 1.1  2009-04-01 16:22:18  sorin
  BugId: none
  Initial 8652 memory map


*/

#ifndef DCCHD_CONFIG_H_
#define DCCHD_CONFIG_H_

/// \defgroup config Platform Configuration Definitions
/// Compile-time definitions of platform-specific parameters.

/// \defgroup dspres Media Processing Resources
///
/// Define the number of media processing resources available
///
/// Each of the definitions can be overwritten by compiler options (usually defined in the DCCHD.flags.xxx files)
/// \ingroup config
///@{

#ifndef RMCFG_AUDIO_ENGINE_CNT
	#define RMCFG_AUDIO_ENGINE_CNT		1	///< number of audio engines (DSPs)
#endif

#ifndef RMCFG_AUDIO_DECODER_CNT
	#define RMCFG_AUDIO_DECODER_CNT		2	///< number of audio decoders per engine
#endif

#ifndef RMCFG_VIDEO_ENGINE_CNT
	#define RMCFG_VIDEO_ENGINE_CNT		1	///< number of video engines (DSPs)
#endif

#ifndef RMCFG_VIDEO_DECODER_CNT
	#define RMCFG_VIDEO_DECODER_CNT		2	///< number of video decoders per engine
#endif

///@}

/// \defgroup awiring Audio Wiring Definitions
///
/// Define how the audio DSPs are wired to the audio connectors on a specific platform
///
/// The bit corresponding to each engine is set if the engine is connected to the specified connector
/// (engine 0 = bit 0, etc)
///
/// Each of the definitions can be overwritten by compiler options (usually defined in the DCCHD.flags.xxx files)
/// \ingroup config
///@{
#ifndef RMCFG_HDMI_ENGINES
	#if !defined(RMCFG_HDMI_I2S_ENGINES) && !defined(RMCFG_HDMI_SPDIF_ENGINES)
		#define RMCFG_HDMI_ENGINES		1	///< Engines capable of HDMI output over I2S lines \deprecated by #RMCFG_HDMI_I2S_ENGINES and #RMCFG_HDMI_SPDIF_ENGINES
	#else
		#define RMCFG_HDMI_ENGINES		0
	#endif
#endif

#ifndef RMCFG_HDMI_I2S_ENGINES
	#define RMCFG_HDMI_I2S_ENGINES		RMCFG_HDMI_ENGINES	///< Engines capable of HDMI output over I2S lines \change Made separate SPDIF and I2S connections to the HDMI output 3-20-2007
#endif

#ifndef RMCFG_HDMI_SPDIF_ENGINES
	#ifdef WITH_EXTERNAL_AUDIO_CONNECTORS
		#define RMCFG_HDMI_SPDIF_ENGINES	0	///< Link to external connectors is over I2S lines only
	#else
		#define RMCFG_HDMI_SPDIF_ENGINES	RMCFG_HDMI_ENGINES	///< Engines capable of HDMI output over SPDIF lines \change Made separate SPDIF and I2S connections to the HDMI output 3-20-2007
	#endif
#endif

#ifndef RMCFG_ANALOG_ENGINES
	#ifdef WITH_EXTERNAL_AUDIO_CONNECTORS
		#define RMCFG_ANALOG_ENGINES		0	///< Link to external connectors is using engine 0 (normally HDMI) only
	#else
		#define RMCFG_ANALOG_ENGINES		RMCFG_AUDIO_ENGINE_CNT	///< Engines capable of multichannel analog output
	#endif
#endif

#ifndef RMCFG_STEREO_ENGINES
	#ifdef WITH_EXTERNAL_AUDIO_CONNECTORS
		#define RMCFG_STEREO_ENGINES		0	///< Link to external connectors is using engine 0 (normally HDMI) only
	#else
		#define RMCFG_STEREO_ENGINES		RMCFG_AUDIO_ENGINE_CNT	///< Engines capable of stereo analog output that is different than the multichannel one
	#endif
#endif

#ifndef RMCFG_SPDIF_ENGINES
	#ifdef WITH_EXTERNAL_AUDIO_CONNECTORS
		#define RMCFG_SPDIF_ENGINES			0	///< Link to external connectors is using engine 0 (normally HDMI) only
	#else
		#define RMCFG_SPDIF_ENGINES			RMCFG_AUDIO_ENGINE_CNT	///< Engines capable of SPDIF output
	#endif
#endif

#ifndef RMCFG_ANALOG_CHANNELS
	#define RMCFG_ANALOG_CHANNELS		5	///< Number of channels available on the multichannel analog output. LFE is not included and assumed present if and only if more than 2 channels.
#endif
///@}


#ifndef RMCFG_VOUTPUT_BLOCKS
	#define RMCFG_VOUTPUT_BLOCKS		(RMCFG_VOUTPUT_MAIN_DIGITAL | RMCFG_VOUTPUT_MAIN_ANALOG | RMCFG_VOUTPUT_CAV_ANALOG)	///< Video output blocks present on a specific platform, as a \ref VUBIDs mask \ingroup config
#endif


#include "drm_config.h"

/// Name of the CRT and GFX scalers
#ifndef CRT_SCALER
	#define CRT_SCALER	DispCRTMultiScaler
#endif
#ifndef GFX_SCALER
	#define GFX_SCALER	DispGFXMultiScaler
#endif

// Orientative video decoder memory requirements for the most usual cases (may depend on architecture and/or firmware version)
#define MMAP_VIDEO_MPEG2SD_SIZE	 5*1024*1024
#define MMAP_VIDEO_AVCSD_SIZE  (18*1024+800)*1024
#define MMAP_VIDEO_VC1SD_SIZE	 9*1024*1024
#define MMAP_VIDEO_MPEG2HD_SIZE	20*1024*1024
#define MMAP_VIDEO_AVCHD_SIZE   31*1024*1024
#define MMAP_VIDEO_VC1HD_SIZE	24*1024*1024

/// \defgroup memcfg Memory Configuration
///
/// Describe the amount of memory installed on the platform and its static allocation for DCC-HD objects
///
/// Each of the definitions can be overwritten by compiler options (usually defined in the DCCHD.flags.xxx files)
///\ingroup config
///@{
#ifndef MMAP_DRAM0_SIZE
	#define MMAP_DRAM0_SIZE 	80 ///< size of DRAM 0 memory (in MBs) without the Linux memory
#endif

#ifndef MMAP_DRAM1_SIZE
	#define MMAP_DRAM1_SIZE 	0 ///< size of DRAM 1 memory (in MBs)
#endif

#ifndef MMAP_MONO_SIZE
	#define MMAP_MONO_SIZE		30	///< size of the memory used by the file/stream playback engine (Mono/libsamples), in MBs.
#endif

#ifndef MMAP_CPS_SIZE
	#define MMAP_CPS_SIZE 		0 ///< size of CPS memory (in MBs)
#endif

#ifndef BD_MPATH_DMXBUF_SZ6K
	#define BD_MPATH_DMXBUF_SZ6K	320	// Blu-ray main path demux buffer size, in 6 KB units (default: 1.875 MB)
#endif

#ifdef OBJECT_DATA_IN_MRUA_MEMORY
	#define MMAP_DCCHD_DATA_SIZE		16	// DCC-HD objects data members to be allocated in MRUA memory, set it aside (in MB units)
#else
	#define MMAP_DCCHD_DATA_SIZE		0	// DCC-HD objects data members to be allocated in system memory, no MRUA memory must be set aside
#endif

#ifndef MMAP_VIDEO_SD_SIZE
	#define MMAP_VIDEO_SD_SIZE	MMAP_VIDEO_AVCSD_SIZE	///< Size of memory required by the worst case SD video content
#endif

#ifndef MMAP_VIDEO_HD_SIZE
	#define MMAP_VIDEO_HD_SIZE	MMAP_VIDEO_AVCHD_SIZE	///< Size of memory required by the worst case HD video content
#endif

#ifndef MMAP_AUDIO1_SIZE
	#define MMAP_AUDIO1_SIZE 	2000*1024+512*1024 ///< size of the memory used by main audio decoder
#endif

#ifndef MMAP_AUDIO2_SIZE
	#define MMAP_AUDIO2_SIZE 	0 ///< size of the memory used by secondary audio decoder
#endif


#ifndef MMAP_AUDIOENGINE0_SHAREDMEMORY_DRAM_BANK
	#define MMAP_AUDIOENGINE0_SHAREDMEMORY_DRAM_BANK	0	///< DRAM bank selector for the main audio shared memory
#endif
#ifndef MMAP_AUDIOENGINE1_SHAREDMEMORY_DRAM_BANK
	#define MMAP_AUDIOENGINE1_SHAREDMEMORY_DRAM_BANK	0	///< DRAM bank selector for the secondary audio shared memory
#endif

#ifndef MMAP_DirectFB_SIZE
	#define MMAP_DirectFB_SIZE 	(MMAP_DRAM0_SIZE - ((MMAP_DirectFB_BASE - MMAP_DRAM0_UNMAPPED_BASE)/(1024*1024) + MMAP_DCCHD_DATA_SIZE + 1)) ///< size of the memory used by DirectFB as graphic RAM (in MBs). If left undefined, the maximum amount available will be automatically allocated
#endif

#ifndef NO_BLUE_SUPPORT
	//
	//Table 8-2-BDAV-STD model parameters of Buffers
	//
	#define IG_EB_SIZE 		(1024*1024 + 1040*1024) // 1MB EB + 16KB PES overhead + internal overhead
	#define PG_EB_SIZE 		(1024*1024 + 1040*1024) // 1MB EB + 16KB PES overhead + internal overhead

	#define PG_DB_SIZE 		4*1024*1024

	#define IG_PG_PLANE_SIZE	(2*(1920*1080 + 2*1024))	// 1920*1080 for picture, double buffered, 2*1024 for structures

	#ifndef ONLY_AVCHD_SUPPORT
		#define IG_CB_SIZE		(1048576 + 200*1024)
		#define PG_CB_SIZE		10670

		#define IG_DB_SIZE 		16*1024*1024

		#define TS_EB_SIZE		512*1024

		#define TS_FONT_SIZE	4*1024*1024

		#ifdef INCLUDE_PCMX_HEADERS
			#define BDMV_SOUND_SIZE	2*1024*1024 + (2*1024*1024/512)*8 + 128*1024 // add the maximum PCMX header overhead to allow pre-inserted headers for performance optimization
		#else
			#define BDMV_SOUND_SIZE	2*1024*1024
		#endif
	#else
		//
		//Table 8-2-AVCHD-STD model parameters of Buffers
		//
		#define IG_CB_SIZE 		(1024 + 200)*1024
		#define PG_CB_SIZE 		(2048 + 400)*1024

		#define IG_DB_SIZE 		4*1024*1024

		#define TS_EB_SIZE		0

		#define TS_FONT_SIZE	0

		#define BDMV_SOUND_SIZE	0
	#endif
#endif

///@}

// Demux memory requirements for the most usual cases
#define MMAP_DEMUX_BRD_MAIN_SIZE	BD_MPATH_DMXBUF_SZ6K*6*1024
#define MMAP_DEMUX_BRD_SECOND_SIZE 	512*1024	///< Secondary path (combined A/V/IG/PG)
#define MMAP_DEMUX_BRD_2nd_SIZE	 	256*1024	///< Secondary path (separate A, IG or TS)
#define MMAP_DEMUX_DVD_SIZE			512*1024

/// DCC-HD Memory Map definition

/// Defines the location (DRAM0 or DRAM1) and size (in bytes) of MRUA memory objects.
/// The objects are allocated sequentially in the order they appear in the list. They form one
/// single block of contiguous physical memory in each DRAM bank.
///
/// Using a static allocation map prevents memory fragmentation and avoids
/// unexpected failures due to unforeseen dynamic behavior.
///
/// The memory map also clarifies for the SDK users how the memory is used
/// and allows them to customize the allocation based on their specific platform and needs.
///
/// Customizing the memory map consists of either of:
/// - Moving a base/top definition pair from one BANK or \ref mempool to another.
///   This should always work as long as the total memory allocated in a bank is available.
///   Special attention must be made to the overlapped areas - they should be defined one after another,
///   with the largest one last.
/// - Moving a base/top definition pair from inside a \ref mempool to outside of it or viceversa.
///   This switches the object from statically to dynamically allocated.
/// - Changing the size (difference between the top and the base of the pair). This will work
///   only if the application using the SDK restricts the usage to match the reduced memory size
///   (for example, never requesting AVC video playback, which requires additional video memory).
///
/// The memory size requirements are determined experimentally by recording the values requested by
/// the MRUA decoders.
///
/// Memory objects (and the corresponding processing resources) are selected based on the
/// DCCHD::CPresEng::SSessionParams::sessionID parameter of the presentation engine constructor.
/// This way the application can control the availability of resources by controlling the identity
/// and relative order of instantiated presentation engines.
///
/// The objects in the memory map can be accessed through the \ref mruamem functions.
/// \ingroup memcfg
enum EDCCHDMemoryMap
{
	MMAP_DRAM0_UNMAPPED_BASE = 1,									///< reserved value, must be first DRAM0 unmapped definition

		MMAP_DRAM0_MEMPOOL_UNMAPPED_BASE,	///< base of the area used for dynamic suballocation of unmapped DRAM0 memory \ingroup mempool

			MMAP_DEMUX_BASE,
			MMAP_DEMUX_TOP = MMAP_DEMUX_BASE + MMAP_DEMUX_BRD_MAIN_SIZE + MMAP_DEMUX_BRD_2nd_SIZE - 1,

			MMAP_MISC_BASE,
			MMAP_MISC_TOP = MMAP_MISC_BASE + 256*1024 - 1,

		MMAP_DRAM0_MEMPOOL_UNMAPPED_TOP,	///< top of the area used for dynamic suballocation of unmapped DRAM0 memory

	MMAP_DRAM0_UNMAPPED_TOP,							///< reserved value, must be last DRAM0 unmapped definition
	MMAP_DRAM0_BASE,									///< reserved value, must be first DRAM0 definition

		MMAP_CPS_BASE,														///< CPS provider can use only DRAM0 memory
		MMAP_CPS_TOP = MMAP_CPS_BASE + MMAP_CPS_SIZE*1024*1024 - 1,

		MMAP_DirectFB_BASE,

		MMAP_MONO_BASE,
		MMAP_MONO_TOP = MMAP_MONO_BASE + 0 - 1,		///< by setting the size to 0 (or any insufficient value), DirectFB memory will be used

		MMAP_MONO_EXT_BASE,							///< extra memory MONO uses for WMApro only
		MMAP_MONO_EXT_TOP = MMAP_MONO_EXT_BASE + 0 - 1,

		MMAP_JPEG_BASE,
		MMAP_JPEG_TOP = MMAP_JPEG_BASE + 0 - 1,		///< JPEG memory is always allocated dynamically from DirectFB memory

		MMAP_VIDEO_0_BASE,							///< video for session ID 0 (HD capable)
		MMAP_VIDEO_0_TOP = MMAP_VIDEO_0_BASE + 0 - 1,

		MMAP_SPU_BASE,		///< DVD SPU decoder, always associated with and following Video 0 (assumed MPEG2 SD)
		MMAP_SPU_TOP = MMAP_SPU_BASE + 0 - 1,

		MMAP_VIDEO_1_BASE,							///< video for session ID 1 (SD capable only)
		MMAP_VIDEO_1_TOP = MMAP_VIDEO_1_BASE + 0 - 1,

		MMAP_VIDEO_2_BASE,							///< video for session ID 2 (MPEG2 SD capable only), mutually exclusive with Mono and HD session ID 0 (but compatible with SD/DVD session ID 0)
		MMAP_VIDEO_2_TOP = MMAP_VIDEO_2_BASE + 0 - 1,

		MMAP_VIDEO_3_BASE,							///< video for session ID 3 (MPEG2 SD capable only), mutually exclusive with Mono and HD session ID 0 (but compatible with SD session ID 0)
		MMAP_VIDEO_3_TOP = MMAP_VIDEO_3_BASE + 0 - 1,

		MMAP_VIDEO_4_BASE,							///< video for session ID 4 (MPEG2 SD capable only), mutually exclusive with Mono and HD session ID 0 (but compatible with SD session ID 0)
		MMAP_VIDEO_4_TOP = MMAP_VIDEO_4_BASE + 0 - 1,

		MMAP_AUDIO_0_BASE,							///< audio for session ID 0
		MMAP_AUDIO_0_TOP = MMAP_AUDIO_0_BASE + 0 - 1,

		MMAP_AUDIO_0_SHADOW_BASE,					///< shadow decoder for multiple output support
		MMAP_AUDIO_0_SHADOW_TOP = MMAP_AUDIO_0_SHADOW_BASE + 0 - 1,

		MMAP_AUDIO_1_BASE,							///< audio for session ID 1 \note All PCMX sessions are mapped in session 1
		MMAP_AUDIO_1_TOP = MMAP_AUDIO_1_BASE + 0 - 1,

		MMAP_AUDIO_1_SHADOW_BASE,			///< shadow decoder for multiple output support
		MMAP_AUDIO_1_SHADOW_TOP = MMAP_AUDIO_1_SHADOW_BASE + 0 - 1,

#ifndef NO_BLUE_SUPPORT
		bd_objects_base,
		_objects_top = bd_objects_base - 1,

		MMAP_PG_EB_BASE,					///< Blu-ray PG elementary stream buffer
		MMAP_PG_EB_TOP = MMAP_PG_EB_BASE + 0 - 1, ///< by setting the size to 0 (or any insufficient value), DirectFB memory will be used

		MMAP_PG_DB_BASE,					///< Blu-ray PG decoded objects buffer
		MMAP_PG_DB_TOP = MMAP_PG_DB_BASE + 0 - 1, ///< by setting the size to 0 (or any insufficient value), DirectFB memory will be used

		MMAP_PG_CB_BASE,					///< Blu-ray PG composition data
		MMAP_PG_CB_TOP = MMAP_PG_CB_BASE + 0 - 1, ///< by setting the size to 0 (or any insufficient value), DirectFB memory will be used

		MMAP_PG_PLANE_BASE,					///< Blu-ray PG plane (double buffered)
		MMAP_PG_PLANE_TOP = MMAP_PG_PLANE_BASE + 0 - 1, ///< by setting the size to 0 (or any insufficient value), DirectFB memory will be used

		MMAP_IG_EB_BASE,					///< Blu-ray IG elementary stream buffer
		MMAP_IG_EB_TOP = MMAP_IG_EB_BASE + 0 - 1, ///< by setting the size to 0 (or any insufficient value), DirectFB memory will be used

		MMAP_IG_DB_BASE,					///< Blu-ray IG decoded objects buffer
		MMAP_IG_DB_TOP = MMAP_IG_DB_BASE + 0 - 1, ///< by setting the size to 0 (or any insufficient value), DirectFB memory will be used

		MMAP_IG_CB_BASE,
		MMAP_IG_CB_TOP = MMAP_IG_CB_BASE + 0 - 1, ///< by setting the size to 0 (or any insufficient value), DirectFB memory will be used

		MMAP_IG_PLANE_BASE,					///< Blu-ray IG plane (double buffered)
		MMAP_IG_PLANE_TOP = MMAP_IG_PLANE_BASE + 0 - 1, ///< by setting the size to 0 (or any insufficient value), DirectFB memory will be used

		MMAP_TS_EB_BASE,					///< Blu-ray TS is preloaded so it can coexist with HD video
		MMAP_TS_EB_TOP = MMAP_TS_EB_BASE + 0 - 1, ///< by setting the size to 0 (or any insufficient value), DirectFB memory will be used

		MMAP_TS_FONT_BASE,					///< Blu-ray TS is low bandwidth so it can coexist with HD video
		MMAP_TS_FONT_TOP = MMAP_TS_FONT_BASE + 0 - 1, ///< by setting the size to 0 (or any insufficient value), DirectFB memory will be used

		MMAP_BDMV_SOUND_BASE,				///< Blu-ray sound data buffer is low bandwidth as it is accessed only by the CPU, so it can coexist with HD video
		MMAP_BDMV_SOUND_TOP = MMAP_BDMV_SOUND_BASE + 0 - 1, ///< by setting the size to 0 (or any insufficient value), DirectFB memory will be used

		bd_objects_top = bd_objects_base + ((PG_EB_SIZE + PG_DB_SIZE + PG_CB_SIZE + IG_PG_PLANE_SIZE +
											 IG_EB_SIZE + IG_DB_SIZE + IG_CB_SIZE + IG_PG_PLANE_SIZE +
											 TS_EB_SIZE + TS_FONT_SIZE + BDMV_SOUND_SIZE + 1023) & ~1023) - 1,
#endif
		directfb_top,
		MMAP_DirectFB_TOP = directfb_top > MMAP_DirectFB_BASE + MMAP_DirectFB_SIZE*1024*1024
				? directfb_top - 1
				: MMAP_DirectFB_BASE + MMAP_DirectFB_SIZE*1024*1024 - 1,

		MMAP_DRAM0_MEMPOOL_BASE,					///< base of the area used for dynamic suballocation of DRAM0 memory \ingroup mempool

			MMAP_DCCHD_DATA_BASE,						///< Data fields of the DCC-HD class library
			MMAP_DCCHD_DATA_TOP = MMAP_DCCHD_DATA_BASE + MMAP_DCCHD_DATA_SIZE*1024*1024 - 1,

			MMAP_DEMUX_OUTPUT_BASE,
			MMAP_DEMUX_OUTPUT_TOP = MMAP_DEMUX_OUTPUT_BASE + 256*1024 - 1,

		MMAP_DRAM0_MEMPOOL_TOP,						///< top of the area used for dynamic suballocation of DRAM0 memory

	MMAP_DRAM0_TOP,										///< reserved value, must be last DRAM0 definition

	// no DRAM1 bank
	MMAP_DRAM1_UNMAPPED_BASE,
	MMAP_DRAM1_UNMAPPED_TOP,

	MMAP_DRAM1_MEMPOOL_UNMAPPED_BASE,
	MMAP_DRAM1_MEMPOOL_UNMAPPED_TOP,

	MMAP_DRAM1_BASE,
	MMAP_DRAM1_TOP,

	MMAP_DRAM1_MEMPOOL_BASE,
	MMAP_DRAM1_MEMPOOL_TOP,
};

///\defgroup mempool MRUA Memory Pool
/// Portion of the DCC-HD static memory map sub-allocated dynamically.
///
/// Memory map objects defined inside memory pool objects are automatically sub-allocated dynamically in the pool.
/// Alternatively, memory objects not explicitelly defined in the memory map can be sub-allocated by specifying the
/// memory pool top memory map ID in the allocation call (dcchd_mruamem_alloc()).


// #if (MMAP_DRAM0_TOP - MMAP_DRAM0_BASE + MMAP_DRAM0_UNMAPPED_TOP - MMAP_DRAM0_UNMAPPED_BASE) > (MMAP_DRAM0_SIZE - 16)
// 	#error Memory map exceeds DRAM 0 size minus minimum margin for Linux. Abort!!!
// #endif
//
// #if (MMAP_DRAM1_TOP - MMAP_DRAM1_BASE + MMAP_DRAM1_UNMAPPED_TOP - MMAP_DRAM1_UNMAPPED_BASE) > (MMAP_DRAM1_SIZE)
// 	#error Memory map exceeds DRAM 1 size. Abort!!!
// #endif

#endif /*DCCHD_CONFIG_H_*/
