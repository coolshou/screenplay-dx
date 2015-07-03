/*****************************************
 Copyright  2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/*
 * \file iadvancedmediaprovider.h
 * \brief DirectFB Advanced Media Provider interface definition

 * $Log: iadvancedmediaprovider.h,v $
 * Revision 1.8  2009-07-29 01:03:05  sorin
 * BugId: none
 * Added ability to force unique sourceID AMP instantiation in order to allow the coexistence between independent AMP instances
 *
 * Revision 1.7  2008-12-19 03:24:48  sorin
 * BugId: none
 * Replaced the DFB internal __u64 type with the externally visible u64, to fix compilation errors in flashlite client
 *
 * Revision 1.6  2008-11-20 16:56:11  sorin
 * BugId: none
 * Merged the Fast Load changes (asynchronous AACS and BD+)
 *
 * Revision 1.5  2008-11-04 00:09:48  sorin
 * BugId: none
 * Doc
 *
 * Revision 1.4  2008-10-07 23:24:26  sorin
 * BugId: none
 * Doc
 *
 * Revision 1.3  2007-08-31 19:57:45  sorinp
 * BUG-CT:3818 Add media access arbitration mechanism
 *
 * Revision 1.2  2007/06/06 16:17:08  smanciulea
 * - replaced all occurences of wchar_t with char and done all related changes for string manipulation
 * - DCCHD_MAX_PATH changed from 512 to 2048
 *
 * Revision 1.1  2007/05/11 21:15:37  sorinp
 * Unified DirectFB and DCC-DOC shared doc
 *
 *
 * Revision 1.4  2005/10/18 02:30:35  sorinp
 * removed custome event definition, not needed
 *
 * Revision 1.3  2005/10/14 15:20:56  mfedoreanu
 * Fixed wait functions
 *
 * Revision 1.2  2005/10/12 13:45:20  sorinp
 * doc updates
 *
 * Revision 1.1  2005/10/10 17:17:02  sorinp
 * Re-arranged package
 *
 * Revision 1.16  2005/10/06 16:06:33  sotescu
 * DirectFB: removed some unneeded files.
 *
 * Revision 1.15  2005/10/05 18:44:24  sorinp
 * Mostly doc upgrades
 *
 * Revision 1.14  2005/10/05 17:39:49  sotescu
 * DirectFB: preliminary hardware blit support.
 *
 * Revision 1.13  2005/10/04 04:19:38  sorinp
 * doc update
 *
*/

#ifndef _IADVANCEDMEDIAPROVIDER_H_
#define _IADVANCEDMEDIAPROVIDER_H_

#include <directfb.h>
#ifndef __INTS_DEFINED__
#define __INTS_DEFINED__
typedef   int32_t INT32;     // 32 bits signed integer
typedef u_int32_t UINT32;    // 32 bits unsigned integer
typedef   int64_t INT64;     // 64 bits signed integer
typedef u_int64_t UINT64;    // 64 bits unsigned integer
#endif
#include <cdefs.h> // generic media and control definitions

/// \defgroup DFBAMP DirectFB Advanced Media Extensions
/// New DirectFB interfaces for presenting complex media like DVDs, HD-DVDs, Blu-ray discs, etc.
///
/// For the rest of the DirectFB API, see the <A HREF="directfb/index.html">SMP8634 DirectFB Driver Reference Manual</A>

#ifdef __cplusplus
extern "C"
{
#endif

/// \defgroup ampid DirectFB Advanced Media Provider ID
/// IAdvancedMediaProvider instances with the first #MAX_VIDEO_AMP_INSTANCES sourceID values are assigned the available DirectFB video layers
/// (sourceID values #MAIN_VIDEO_AMP_ID and #SECONDARY_VIDEO_AMP_ID are mapped on the video layers #EM86LAYER_MAINVIDEO and #EM86LAYER_SECVIDEO respectively).
/// Instances with other sourceID values can not display video directly; they can be used for:
/// - video-only media with video rendered to a DirectFB surface using StartPresentationTo() method
/// - interactive audio media (type #MTYPE_ELEM_PCM | #MTYPE_APP_BDJ)
/// - opening complex media (DVDs, etc) for examination only (without calling StartPresentation() or StartPresentationTo())
/// \see \ref preng_dfb_integration
/// \ingroup hiconf
///@{

/**
 * Maximum number of concurent provider instances <b>Sigma extension</b>.
 */
#define MAX_AMP_INSTANCES   12

/**
 * Maximum number of concurrent provider instances that can output video on separate layers - the rest must be either audio only or use a graphic areas as output <b>Sigma extension</b>.
 */
#define MAX_VIDEO_AMP_INSTANCES   2

/*
 * This AMP ID is assigned the main video layer <b>Sigma extension</b>
 */
#define MAIN_VIDEO_AMP_ID   0  /**< This AMP ID is assigned the \ref EM86LAYER_MAINVIDEO */

/*
 * This AMP ID is assigned the secondary video layer <b>Sigma extension</b>
 */
#define SECONDARY_VIDEO_AMP_ID   1  /**< This AMP ID is assigned the \ref EM86LAYER_SECVIDEO */

/*
 * This AMP ID and all the rest up to MAX_AMP_INSTANCES-1 are NOT assigned to any DirectFB display layers <b>Sigma extension</b>
 */
#define FIRST_NO_LAYER_AMP_ID   2  /**< This AMP ID and all the rest up to MAX_AMP_INSTANCES-1 are NOT assigned to any DirectFB display layers */

/*
 * This flag can be set in an AMP ID to force the IDirectFB::GetInterface() call to fail
 * if AMP with the same ID (not counting the flag) is already instantiated
 */
#define UNIQUE_AMP_ID_FLAG   128  /**< This flag can be set in an AMP ID
 to force the IDirectFB::GetInterface() call to fail if AMP with the same ID
 (not counting the flag) is already instantiated */

///@}

/**
 * AMP event announcing that the media session has closed <b>Sigma extension</b>.
 */
#define AMP_EVENT_CLOSED			0

/**
 *  AMP event announcing an AMP status change <b>Sigma extension</b>.
 */
#define AMP_EVENT_STATUS_CHANGE		1

/**
 * Capabilities of an IAdvancedMediaProvider object <b>Sigma extension</b>.
 */
typedef enum {
    DAMPCAPS_NAV_VCD        = 0x00000001,   /**< Can navigate VCD discs */
    DAMPCAPS_NAV_SVCD       = 0x00000002,   /**< Can navigate SVCD discs */
    DAMPCAPS_NAV_DVD        = 0x00000004,   /**< Can navigate DVD discs */
    DAMPCAPS_NAV_DVDA       = 0x00000008,   /**< Can navigate DVD-Audio discs */
    DAMPCAPS_NAV_DVDVR      = 0x00000010,   /**< Can navigate DVD-VR discs */
    DAMPCAPS_NAV_DVDHD      = 0x00000020,   /**< Can navigate DVD-HD discs */
    DAMPCAPS_NAV_BDROM      = 0x00000040,   /**< Can navigate Blu-ray discs */
    DAMPCAPS_NAV_BDRE       = 0x00000080,   /**< Can navigate Blu-ray rewritable discs */
    DAMPCAPS_NAV_MP3        = 0x00000100,   /**< Can navigate MP3 discs */
    DAMPCAPS_NAV_JPEG       = 0x00000200,   /**< Can navigate JPEG discs */
    DAMPCAPS_NAV_DIVX       = 0x00000400,   /**< Can navigate DIVX discs */
    DAMPCAPS_NAV_CDDA       = 0x00000800,   /**< Can navigate CD-DA discs */
    DAMPCAPS_NAV_CDDTS      = 0x00001000,   /**< Can navigate CD-DTS discs */
    DAMPCAPS_NAV_SACD       = 0x00002000,   /**< Can navigate SACD discs */
    DAMPCAPS_JPEG      		= 0x00004000,   /**< Can play JPEG */
    DAMPCAPS_VIDEO_DIVX    	= 0x00008000,   /**< Can play DIVX video */
    DAMPCAPS_VIDEO_MPEG2    = 0x00010000,   /**< Can play MPEG1 & 2 video */
    DAMPCAPS_VIDEO_MPEG4    = 0x00020000,   /**< Can play MPEG4 video */
    DAMPCAPS_VIDEO_MPEG4AVC = 0x00040000,   /**< Can play MPEG4 AVC video */
    DAMPCAPS_VIDEO_VC1      = 0x00080000,   /**< Can play VC1 video */
    DAMPCAPS_AUDIO_MPEG     = 0x00100000,   /**< Can play MPEG audio */
    DAMPCAPS_AUDIO_WMA      = 0x00200000,   /**< Can play Windows Media audio */
    DAMPCAPS_AUDIO_AAC      = 0x00400000,   /**< Can play AAC audio */
    DAMPCAPS_AUDIO_DD       = 0x00800000,   /**< Can play Dolby Digital audio */
    DAMPCAPS_AUDIO_DDP      = 0x01000000,   /**< Can play Dolby Digital Plus audio */
    DAMPCAPS_AUDIO_DTS      = 0x02000000,   /**< Can play DTS audio */
    DAMPCAPS_AUDIO_DTSHD    = 0x04000000,   /**< Can play DTS-HD audio */
    DAMPCAPS_HD             = 0x08000000,   /**< Can play high-definition video */
    DAMPCAPS_BRIGHTNESS     = 0x10000000,   /**< Supports Brightness adjustment */
    DAMPCAPS_CONTRAST       = 0x20000000,   /**< Supports Contrast adjustment */
    DAMPCAPS_HUE            = 0x40000000,   /**< Supports Hue adjustment */
    DAMPCAPS_SATURATION     = 0x80000000    /**< Supports Saturation adjustment */
} DFBAdvancedMediaProviderCapabilities;


/**
 * Maximum length of description strings <b>Sigma extension</b>.
 */
#define DFB_AMP_NAME_LENGTH 32

/**
 * Description of an IAdvancedMediaProvider object <b>Sigma extension</b>.
 */
typedef struct {
    DFBAdvancedMediaProviderCapabilities caps;      /**< Provider capabilities */
    void *privateInfo;                              /**< Provider-specific information */
    char name[DFB_AMP_NAME_LENGTH];                 /**< Provider name */
    char vendor[DFB_AMP_NAME_LENGTH];               /**< Device vendor */
} DFBAdvancedMediaProviderDescription;


/*
 * <A HREF="../group___d_f_b_a_m_p.html"><b>Sigma advanced media extension</b></A>: Interface for complex media playback control
 */
DECLARE_INTERFACE( IAdvancedMediaProvider )

#ifdef __DOC__
#define MY_DEFINE_INTERFACE(IF)		struct IF {
#else
#define MY_DEFINE_INTERFACE(IF)		DEFINE_INTERFACE(IF,
#endif

/**
 * DirectFB extension interface for services of the format-specific provider.
 *
 * It is retrieved with IDirectFB::GetInterface() with the following specific parameters:
 * - type = "AdvancedMediaProvider" (AMP)
 * - arg = (void *)sourceID - a number between 0 and #MAX_AMP_INSTANCES identifying the new AMP instance.
 *
 * After an AMP instance is instantiated, a specific media (of explicit or autodetected type) can be assigned to it
 * through a IAdvancedMediaProvider::OpenMedia() call, its presentation can be initiated through a IAdvancedMediaProvider::StartPresentation()
 * or IAdvancedMediaProvider::StartPresentationTo() call and then it can be controlled interactively through
 * IAdvancedMediaProvider::PostPresentationCmd() / IAdvancedMediaProvider::ExecutePresentationCmd() / IAdvancedMediaProvider::UploadStatusChanges() calls.
 *
 * One AMP instance encapsulates one instance of the available \ref controlimpl that corresponds to the type of the media assigned to the AMP.
 *
 * The AMP instances with the first #MAX_VIDEO_AMP_INSTANCES sourceID values are assigned the available DirectFB video layers
 * (sourceID values #MAIN_VIDEO_AMP_ID and #SECONDARY_VIDEO_AMP_ID are mapped on the video layers #EM86LAYER_MAINVIDEO and #EM86LAYER_SECVIDEO respectively).
 * Instances with other sourceID values can not display video directly; they can be used for:
 * - video-only media with video rendered to a DirectFB surface using IAdvancedMediaProvider::StartPresentationTo() method
 * - interactive audio media (type #MTYPE_ELEM_PCM | #MTYPE_APP_BDJ)
 * - opening complex media (DVDs, etc) for examination only (without calling IAdvancedMediaProvider::StartPresentation() or IAdvancedMediaProvider::StartPresentationTo())
 *
 * All the AMP instances with presentations active in the same time must use different sourceID values.
 * A presentation is active between the StartPresentation() call and the IAdvancedMediaProvider::CloseMedia() or IAdvancedMediaProvider::Release() calls.
 * Using the same sourceID for multiple concurrent AMP instances is useful if the underlying DCC-HD playback control class
 * supports pre-buffering - medias can be opened in advance and, by the time they are serially presented, they have accumulated
 * data so they can start the presentation immediately. In this case, the pre-buffered AMPs must use the same sourceIDs
 * in order to use the same system resources. For details on prebuffering, see DCCHD_MONO::CMonoNavigator class documentation.
 *
 *\note The sourceID parameter is used to identify resources in the \link #EDCCHDMemoryMap DCC-HD memory map\endlink
 *\note In order to make sure a sourceID is not already in use, the #UNIQUE_AMP_ID_FLAG can be set in the saourceID value used in the IDirectFB::GetInterface() call.
 * In this case, the call will fail if an AMP with specified source id (not counting the flag) is already allocated; otherwise, the AMP with the specified source ID
 * (not counting the flag) is allocated.
 *\ingroup DFBAMP
 */
MY_DEFINE_INTERFACE( IAdvancedMediaProvider )

    /**
    * Retrieves the provider description.
	*
    * The provider name matches the name of the layer playback source
    * corresponding to this provider.
    */
    DFBResult (*GetDescription) (
        IAdvancedMediaProvider      *thiz,
        DFBAdvancedMediaProviderDescription *ret_desc
    );

    /**
     * Installs implementation-specific callbacks
     *
     * To set only some of the callbacks, use the #CMD_INVALID_CALLBACK value for those that are to be left unchanged.
     *
     * This method can be called either inside or outside a media session
     * (IAdvancedMediaProvider::OpenMedia()/IAdvancedMediaProvider::CloseMedia() cycle).
     */
    DFBResult (*SetApplicationCallbacks) (
        IAdvancedMediaProvider *thiz,
        void *configPreview,				/**< called before applying the configuration, the application may change it on the fly */
        void *configConfirm,				/**< called after applying the configuration */
        TAVAccessRequest avAccessRequest,	/**< called before reading A/V data, can be set only once and never reset in a playback session */
        TAVAccessNotify avAccessNotify		/**< called after reading A/V data, can be set only once and never reset in a playback session */
    );

    /**
     * Sets user-level configuration options and capabilities.
     *
     * This method can be called either inside or outside a media session (OpenMedia/CloseMedia cycle).
     * It generates a configuration cycle though only during active media presentations.
     *
     * Either one or both of the configuration structure pointers may be NULL.
     */
    DFBResult (*SetConfiguration) (
        IAdvancedMediaProvider *thiz,
        struct SVideoOutConfig *vConfig,	/**< video preferences and capabilities */
        struct SAudioOutConfig *aConfig		/**< audio  preferences and capabilities */
    );

    /**
     * Adjusts transitory output parameters.
     *
     * This method can be called either inside or outside
     * a media session (OpenMedia/CloseMedia cycle).
     */
	DFBResult (*SetAdjustment) (
		IAdvancedMediaProvider *thiz,
		struct SAdjustment *adjust
	);

    /**
     * Retrieves a IDirectFBEventBuffer object that delivers media event notifications.
     *
     * The Advanced Video Provider generates DFBUserEvent events of two types:
     * - #AMP_EVENT_STATUS_CHANGE events. The status is retrieved separately through the UploadStatusChanges() method.
     * - #AMP_EVENT_CLOSED events. The user must release the event buffer after this event.
     *
     * The event buffer must be retrieved BEFORE the OpenMedia() call
     * and must be released after the CloseMedia() call. Thus, a separate event buffer is used for each media session.
     *
     * Repeated calls to GetEventBuffer() can be made any time during a media session but they return the same object
     * as the first call. Consequently, only one file descriptor can be acquired per media session. Nevertheless,
     * a CloseMedia() call must still be issued for every GetEventBuffer() call.
     */
    DFBResult (*GetEventBuffer) (
        IAdvancedMediaProvider *thiz,
        IDirectFBEventBuffer  **pBuffer
    );

    /**
     * Provides a IDirectFBDataBuffer buffer for delivering media data of the specified type.
     *
     * For PCM and pixel map media types, the SMediaFormat::format field must be valid,
     * except for the cases when the media is a component of a complex type
     * that contains all the formating information necessary for rendering.
     *
     * The data buffer for the main media type of a presentation must be set BEFORE the OpenMedia() call
     * unless, of course, it is provided in URL form to that call.
     *
     * Multiple data buffers for media components can be set any time BEFORE the StartPresentation() call
     *
     * Once set, a data buffer object can not be unset during the same media presentation.
     *
     * All data buffer objects are released upon the CloseMedia() call (or the release of the IAdvancedMediaProvider interface).
     *
     * While a presentation is open, SetDataBuffer() calls will fail
     */
    DFBResult (*SetDataBuffer) (
        IAdvancedMediaProvider *thiz,
        IDirectFBDataBuffer    *buffer,
        struct SMediaFormat    *dataFormat
    );

    /**
     * Opens the specified media.
     *
     * If the media type is not specified (the UNKNOWN value is passed in), the method attempts to detect it.
     * The method will be successful only if a supported media type is detected.
     *
     * The call may block for up to 500 ms. If by that time the media has not been opened, the call returns
     * and the result of the operation is delivered later as a status change event.
     *
     * The method consumes media data up to the point where it can detect or confirm the format and extract
     * high level information. Data read up to that point will be discarded (this is an issue only with
     * streaming media). Upon successful completion of the operation, high level media information is
     * available in the status.
     *
     * If the url parameter is NULL, a data buffer must have been set up prior to this call and must have been
     * associated with the media type specified in this call.
     *
     * The param parameter is passed as is to the provider and is format-specific (example: BD-RE PIN)
     *
     * The same Advanced Video Provider interface can be used in multiple OpenMedia()/CloseMedia() cycles.
     *
     * If url specifies a file on disc, it must be of <device name>//<file path on device> format (note the double slashes),
     * so that the device can be mounted automatically, otherwise the entire url's treated as a device.
     * If a device url is specified, the device is mounted automatically.
     *
     * \note Implementation detail: AMP uses an internal file system library to mount UDF and CD-FS devices,
     * different than the Linux FS. This library can be used by the application too, through the IMediaSupportAccess interface.
     * The same device can be mounted by both the application and AMP independently, although the library will
     * mount the device only once, resulting in shorter mount time.
     *
     * The application can force AMP to use the Linux FS by mounting the device in Linux and then opening the media
     * with the Linux VFS url.
     */
    DFBResult (*OpenMedia) (
        IAdvancedMediaProvider *thiz,
        char                   *url,
        struct SMediaFormat    *dataFormat,	/**< media format */
        void                   *param       /**< format-specific parameter, is passed as is to the provider (example: BD-RE PIN) */
    );

    /**
     * Starts the actual presentation of the opened media.
     *
     * The standard DFB interfaces are used to control the appearance of the display layer used for the
     * presentation.
     *
     * The actual behavior is format-specific. For example, a linear file will start playing, a DVD with
     * First Play data will start the auto-play feature while a DVD without First Play (and auto-play disabled)
     * will wait for user input without actually playing.
     */
    DFBResult (*StartPresentation) (
        IAdvancedMediaProvider *thiz,
        DFBBoolean                      defaultPlay /**< if FALSE, the default presentation action is ignored and presentation must be started with an explicit command */
    );

    /**
     * The same as StartPresentation(), but video is rendered into the specified surface.
     *
     * Optionally a callback can be registered that is called
     * for each rendered frame. This is especially important if
     * you are playing to a flipping surface. In this case, you
     * should flip the destination surface in your callback.
     *
     * Not all media types and/or assets can be presented in a surface,
     * due to content protection restrictions.
     * The feature is intended mostly for simple presentations of low-risk content,
     * for example animated backgrounds.
     *
     * The default media behavior is always enforced and can not be disabled.
     *
     * \note To render in a rectangle inside a surface, create a subsurface for the area and pass it to StartPresentationTo()
     */
    DFBResult (*StartPresentationTo) (
        IAdvancedMediaProvider *thiz,
        IDirectFBSurface         *destination,
        DVFrameCallback           callback,
        void                     *ctx
    );

    /**
     * Asynchronous execution of presentation commands.
     *
     * The outcome and a 32 bit result value can be retrieved from the status information. To retrieve more
     * complex results, use ExecutePresentationCmd().
     *
     * Meaning and syntax of the #SCommand parameter are format-specific and are documented in the provider
     * specification.
     */
    DFBResult (*PostPresentationCmd) (
        IAdvancedMediaProvider *thiz,
        struct SCommand                *buffer
    );

    /**
     * Requests a notification upon reaching the specified presentation time.
     *
     * The notification will be in the form of a regular status change event and the status info will contain
     * the presentation time, which may be slightly off the requested values in case it did not fit
     * the presentation schedule exactly (i.e. there was no frame with the specified presentation time value).
     *
     * \status TBI
     */
    DFBResult (*PostPresentationTimeNotificationRequest) (
        IAdvancedMediaProvider *thiz,
        u64                   time
    );

    /**
     * Uploads the entire status, or only those parts that have changed since the last call.
     *
     * Usually called after receiving a status change event.
     *
     * The meaning and syntax of the #SStatus parameter are format-specific and are documented in the
     * provider specification.
     *
     * If allStatus is TRUE, the entire status information is copied into the supplied buffer, regardless of
     * when was the last time it has changed. If it is FALSE, only those portions that has changed since the
     * last time the UploadStatusChanges() was called are written in the supplied buffer. In this way, the client
     * is given an efficient mechanism for having a copy of the status info always up-to-date. The #SStatus
     * structure provides mechanisms for identification of the information that has changed, in effect making
     * the DFB event a collection of media format-specific events.
     */
    DFBResult (*UploadStatusChanges) (
        IAdvancedMediaProvider *thiz,
        struct SStatus                 *buffer,
        DFBBoolean                      allStatus
    );

    /**
     * Synchronous execution of presentation commands.
     *
     * The complete result of the commands is returned in the specified buffer.
     *
     * The meaning and syntax of the #SCommand and #SResult parameters are format-specific and are documented
     * in the provider specification.
     */
    DFBResult (*ExecutePresentationCmd) (
        IAdvancedMediaProvider *thiz,
        struct SCommand                *cmd_buffer,
        struct SResult                 *res_buffer
    );

    /**
     * Captures the current video sample into the specified destination surface, making all the necessary
     * adjustments in terms of image size and color format.
     *
     * Limitations on the quality of the captured data (i.e. down-sampled versions) may be enforced,
     * depending on the corresponding Copy Protection status.
     */
    DFBResult (*CaptureTo) (
        IAdvancedMediaProvider *thiz,
        IDirectFBSurface       *destination
    );

    /**
     * Forcefully aborts the pending operation and recovers in the most gracefully way possible.
     *
     * Called usually to terminate an operation that is taking too long to complete (due, for example,
     * to unresponsive inputs).
     */
    DFBResult (*AbortPendingOperation) (
        IAdvancedMediaProvider *thiz
    );

    /**
     * Closes the currently opened media.
     *
     * The call is synchronous.
     * A new OpenMedia() call can be issued after this call.
     */
    DFBResult (*CloseMedia) (
        IAdvancedMediaProvider *thiz
    );
#ifdef __DOC__
};
#else
)
#endif

#ifdef __cplusplus
}
#endif

#endif //_ADVANCEDMEDIAPROVIDER_H_
