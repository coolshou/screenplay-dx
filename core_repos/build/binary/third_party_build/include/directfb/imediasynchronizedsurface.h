/*****************************************
 Copyright  2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/*
 * \file imediasynchronizedsurface.h
 * \brief Declarations for surface which can be updated at specific media times
 *
 * $Log: imediasynchronizedsurface.h,v $
 * Revision 1.2  2008-11-04 00:09:48  sorin
 * BugId: none
 * Doc
 *
 * Revision 1.1  2007-05-11 21:15:37  sorinp
 * Unified DirectFB and DCC-DOC shared doc
 *
 *
 * Revision 1.10  2006/02/17 20:39:02  sorinp
 * removed the /change tags to start clean for the enxt release
 *
 * Revision 1.9  2006/02/17 06:40:38  sorinp
 * doc fixes
 *
 * Revision 1.8  2006/02/17 05:39:17  sorinp
 * better doc
 *
 * Revision 1.7  2006/02/17 04:49:55  sorinp
 * Doc nicetities
 *
 * Revision 1.6  2006/02/16 02:17:02  sorinp
 * doc
 *
 * Revision 1.5  2006/02/16 02:08:58  sorinp
 * doc
 *
 * Revision 1.4  2006/02/14 07:52:53  sorinp
 * yet more doc fixes
 *
 * Revision 1.3  2006/02/14 07:20:46  sorinp
 * doc
 *
 * Revision 1.2  2006/02/14 05:00:07  sorinp
 * doc
 *
 * Revision 1.1  2006/02/14 04:17:04  sorinp
 * Made MediaSynchronizedSurface a stand-alone interface, retrieved by GetInterface
 * Updated documentation
 *
 */

#ifndef IMEDIASYNCHRONIZEDSURFACE_H_
#define IMEDIASYNCHRONIZEDSURFACE_H_

#include <directfb.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Initialization data for the construction of a IMediaSynchronizedSurface <b>Sigma extension</b>.
 *
 * It is passed as the "args" parameter of IDirectFB::GetInterface().
 */
typedef struct {
	bool transparent;				/**< whether the MSS is transparent (slower drawing, but blends with the windows below)*/
	int layer_id;					/**< the video layer the surface is to be synchronized with */
    DFBRectangle window_rect;       /**< the size and position of the surface in the graphic layer */
} DFBMediaSynchronizedSurfaceConstructionData;


/// \defgroup mss_events Media Synchronized Surface events
///@{

/*
 * Media Synchronized Surface operation has been canceled due to being late <b>Sigma extension</b>.
 */
#define MSS_EVENT_CANCELED			0

/*
 * Media Synchronized Surface operation has been performed <b>Sigma extension</b>.
 */
#define MSS_EVENT_PERFORMED			1

///@}


/**
 * DirectFB event sent by IMediaSynchronizedSurface objects to acknowledge the execution or cancelation of each requested operation <b>Sigma extension</b>.
 */
typedef struct {
	DFBEventClass clazz;	/**< DFEC_USER */
	unsigned int  type;		/**< uses \ref mss_events values (MSS_EVENT_CANCELED / MSS_EVENT_PERFORMED) */
	void		 *context;	/**< context value supplied by the user in the corresponding IMediaSynchronizedSurface::NotifyMediaTime() call (if appicable) */
    u64     	  pts;		/**< current media time */
} DFBMediaSynchronizedEvent;

/*
 * <A HREF="../group___d_f_b_a_m_p.html"><b>Sigma advanced media extension</b></A>: DirectFB surface whose updating is synchronized with a media presentation
 */
DECLARE_INTERFACE( IMediaSynchronizedSurface )

#ifdef __DOC__
#define MY_DEFINE_INTERFACE(IF)		struct IF {
#else
#define MY_DEFINE_INTERFACE(IF)		DEFINE_INTERFACE(IF,
#endif

/**
 * Graphic surface whose updating is synchronized with a media presentation.
 *
 * The target media presentation is selected upon the surface's creation by the video layer
 * specified in the #DFBMediaSynchronizedSurfaceConstructionData structure.
 *
 * Display functionality is limited to atomic synchronized blits - IMediaSynchronizedSurface::Blit() and IMediaSynchronizedSurface::StretchBlit()
 *
 * The applications must either blit simple, pre-build images or generate the images in a separate, off-screen surface and then blit them
 * into the synchronized surface.
 * \ingroup DFBAMP
 */
MY_DEFINE_INTERFACE( IMediaSynchronizedSurface)

     /**
      * Return the capabilities of this surface.
      */
     DFBResult (*GetCapabilities) (
          IMediaSynchronizedSurface *thiz,
          DFBSurfaceCapabilities    *ret_caps
     );

     /**
      * Get the surface's width and height in pixels.
      */
     DFBResult (*GetSize) (
          IMediaSynchronizedSurface *thiz,
          int                       *ret_width,
          int                       *ret_height
     );

     /**
      * Created sub surfaces might be clipped by their parents,
      *
      * This function returns the resulting rectangle relative to this surface.
      *
      * For non sub surfaces this function returns{ 0, 0, width, height }.
      */
     DFBResult (*GetVisibleRectangle) (
          IMediaSynchronizedSurface *thiz,
          DFBRectangle              *ret_rect
     );

     /**
      * Get the current pixel format.
      */
     DFBResult (*GetPixelFormat) (
          IMediaSynchronizedSurface *thiz,
          DFBSurfacePixelFormat     *ret_format
     );

     /**
      * Get a mask of drawing functions that are hardware accelerated with the current settings.
      *
      * If a source surface is specified the mask will also
      * contain accelerated blitting functions.  Note that there
      * is no guarantee that these will actually be accelerated
      * since the surface storage (video/system) is examined only
      * when something actually gets drawn or blitted.
      */
     DFBResult (*GetAccelerationMask) (
          IMediaSynchronizedSurface *thiz,
          IMediaSynchronizedSurface *source,
          DFBAccelerationMask       *ret_mask
     );


     /**
      * Get access to the surface's palette.
      *
      * Returns an interface that can be used to gain
      * read and/or write access to the surface's palette.
      */
     DFBResult (*GetPalette) (
          IMediaSynchronizedSurface *thiz,
          IDirectFBPalette         **ret_interface
     );

     /**
      * Change the surface's palette.
      */
     DFBResult (*SetPalette) (
          IMediaSynchronizedSurface *thiz,
          IDirectFBPalette          *palette
     );

     /**
      * Set the alpha ramp for formats with one or two alpha bits.
      *
      * Either all four values or the first and the
      * last one are used, depending on the format.
      * Default values are: 0x00, 0x55, 0xaa, 0xff.
      */
     DFBResult (*SetAlphaRamp) (
          IMediaSynchronizedSurface *thiz,
          __u8                       a0,
          __u8                       a1,
          __u8                       a2,
          __u8                       a3
     );

     /**
      * Set the color used for drawing/text functions or
      * alpha/color modulation (blitting functions).
      *
      * If you are not using the alpha value it should be set to
      * 0xff to ensure visibility when the code is ported to or
      * used for surfaces with an alpha channel.
      *
      * This method should be avoided for surfaces with an indexed
      * pixelformat, e.g. DSPF_LUT8, otherwise an expensive search
      * in the color/alpha lookup table occurs.
      */
     DFBResult (*SetColor) (
          IMediaSynchronizedSurface *thiz,
          __u8                       r,
          __u8                       g,
          __u8                       b,
          __u8                       a
     );

     /**
      * Set the color like with SetColor() but using
      * an index to the color/alpha lookup table.
      *
      * This method is only supported by surfaces with an
      * indexed pixelformat, e.g. DSPF_LUT8. For these formats
      * this method should be used instead of SetColor().
      */
     DFBResult (*SetColorIndex) (
          IMediaSynchronizedSurface *thiz,
          unsigned int               index
     );

     /**
      * Set the blend function that applies to the source.
      */
     DFBResult (*SetSrcBlendFunction) (
          IMediaSynchronizedSurface *thiz,
          DFBSurfaceBlendFunction    function
     );

     /**
      * Set the blend function that applies to the destination.
      */
     DFBResult (*SetDstBlendFunction) (
          IMediaSynchronizedSurface *thiz,
          DFBSurfaceBlendFunction    function
     );

     /**
      * Set the source and destination blend function by
      * specifying a Porter/Duff rule.
      */
     DFBResult (*SetPorterDuff) (
          IMediaSynchronizedSurface *thiz,
          DFBSurfacePorterDuffRule   rule
     );

     /**
      * Set the source color key, i.e. the color that is excluded
      * when blitting FROM this surface TO another that has
      * source color keying enabled.
      */
     DFBResult (*SetSrcColorKey) (
          IMediaSynchronizedSurface *thiz,
          __u8                       r,
          __u8                       g,
          __u8                       b
     );

     /**
      * Set the source color key like with SetSrcColorKey() but using
      * an index to the color/alpha lookup table.
      *
      * This method is only supported by surfaces with an
      * indexed pixelformat, e.g. DSPF_LUT8. For these formats
      * this method should be used instead of SetSrcColorKey().
      */
     DFBResult (*SetSrcColorKeyIndex) (
          IMediaSynchronizedSurface *thiz,
          unsigned int               index
     );

     /**
      * Set the destination color key, i.e. the only color that
      * gets overwritten by drawing and blitting to this surface
      * when destination color keying is enabled.
      */
     DFBResult (*SetDstColorKey) (
          IMediaSynchronizedSurface *thiz,
          __u8                       r,
          __u8                       g,
          __u8                       b
     );

     /**
      * Set the destination color key like with SetDstColorKey() but using
      * an index to the color/alpha lookup table.
      *
      * This method is only supported by surfaces with an
      * indexed pixelformat, e.g. DSPF_LUT8. For these formats
      * this method should be used instead of SetDstColorKey().
      */
     DFBResult (*SetDstColorKeyIndex) (
          IMediaSynchronizedSurface *thiz,
          unsigned int               index
     );

     /**
      * Set the flags for all subsequent blitting commands.
      */
     DFBResult (*SetBlittingFlags) (
          IMediaSynchronizedSurface *thiz,
          DFBSurfaceBlittingFlags    flags
     );

     /**
      * Retrieves a IDirectFBEventBuffer object that delivers #DFBMediaSynchronizedEvent events as notifications that the synchronized blit has been executed
      */
     DFBResult (*GetEventBuffer) (
         IMediaSynchronizedSurface *thiz,
         IDirectFBEventBuffer     **pBuffer
     );

     /**
      * Synchronized blit - present an image at a certain media time.
      *
      * The call returns immediatelly. If the call succeeds, the blit will be performed at the specified presentation time of the media associated with the surface.
      * When the blit is performed, a notification is generated and delivered as a #DFBMediaSynchronizedEvent event through
      * the DirectFBEventBuffer object retrived by the #GetEventBuffer method.
      *
      * If there are too many blits pending, the call fails with the DFB_LIMITEXCEEDED code. The same applies
      * to all the other methods of the surface that change the blitting behavior.
      *
      * The application should wait until it receives a notification that one of the pending blits has been
      * performed before making the blit request again.
      *
      * Blits that are issues passed the frame for which they are intended are automatically dropped.
      */
     DFBResult (*Blit) (
          IMediaSynchronizedSurface *thiz,
          IDirectFBSurface          *source,	/**< source surface */
          int                        source_x,	/**< X origin of the area in the source surface to be presented at the specified time, size is equal with that of the destination */
          int                        source_y,	/**< Y origin of the area in the source surface to be presented at the specified time, size is equal with that of the destination */
          u64                        pts        /**< media time at which the blit is to be performed */
     );
/*
     ///
     /// \note Currently only one single blit (either #Blit or #StretchBlit) commands can be pending. This gives
     /// the application an entire FAA frame interval to submit the next frame. This should be sufficient for most
     /// situations. If significant jitter is expected in the generation of the frames, the application must
     /// create an intermediate buffer and generate the frames in advance of their submission.
*/

     /**
      * Synchronized scaled blit - see IMediaSynchronizedSurface::Blit().
      */
     DFBResult (*StretchBlit) (
          IMediaSynchronizedSurface *thiz,
          IDirectFBSurface          *source,		/**< source surface */
          const DFBRectangle        *source_rect,	/**< area of the source surface to be presented at the specified time */
          u64                        pts			/**< media time at which the blit is to be performed */
     );

     /**
      * Media time notification mechanism for custom synchronized drawing.
      *
      * A notification is delievered at the specified presentation time of the media associated with the surface.
      * The notification is delivered as a #DFBMediaSynchronizedEvent event through
      * the IDirectFBEventBuffer object retrived by the IMediaSynchronizedSurface::GetEventBuffer() method.
      *
      * If there are too many blits and/or notification requests pending, the call fails with the DFB_LIMITEXCEEDED code.
      * The application should wait until it receives a notification that one of the pending blits/requests has been
      * performed before making the request again.
      */
     DFBResult (*NotifyMediaTime) (
          IMediaSynchronizedSurface *thiz,
          void 						*ctxt,			/**< user-defined context */
          u64                        pts			/**< media time at which the notification is to be sent */
     );

     /**
      * Cancel all pending blits and/or notification requests, if any.
      *
      * The image of the last completed blit will remain displayed
      */
     DFBResult (*CancelPendingBlits) (
          IMediaSynchronizedSurface *thiz
     );

	 /**
	  * Get the current PTS.
	  */
	 DFBResult (*GetCurrentPTS) (
          IMediaSynchronizedSurface *thiz,
          u64                       *pts
     );

     /**
      * Dump the contents of the surface to one or two files.
      *
      * Creates a PPM file containing the RGB data and a PGM file with
      * the alpha data if present.
      *
      * The complete filenames will be
      * <b>directory</b>/<b>prefix</b>_<i>####</i>.ppm for RGB and
      * <b>directory</b>/<b>prefix</b>_<i>####</i>.pgm for the alpha channel
      * if present. Example: "/directory/prefix_0000.ppm". No existing files
      * will be overwritten.
      */
     DFBResult (*Dump) (
          IMediaSynchronizedSurface         *thiz,
          const char               *directory,
          const char               *prefix
     );
#ifdef __DOC__
};
#else
)
#endif


#ifdef __cplusplus
}
#endif

#endif /*MEDIASYNCHRONIZEDSURFACE_H_*/
