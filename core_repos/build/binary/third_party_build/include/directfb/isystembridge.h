/*****************************************
 Copyright  2009
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
#ifndef _ISYSTEMBRIDGE_H_
#define _ISYSTEMBRIDGE_H_

#include <directfb.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*
 * <A HREF="../group___d_f_b_a_m_p.html"><b>Sigma advanced media extension</b></A>: Platform-specific bridge between the application and the underlying system driver
 */
DECLARE_INTERFACE( ISystemBridge )

#ifdef __DOC__
#define MY_DEFINE_INTERFACE(IF)		struct IF {
#else
#define MY_DEFINE_INTERFACE(IF)		DEFINE_INTERFACE(IF,
#endif

/**
 * DirectFB extension interface for communication between the application and the underlying system driver.
 *
 * To be used by applications that control the hardware directly, at least to some extent,
 * but want to also use DirectFB. In this case it is useful to have a means of exchanging
 * state information between the DirectFB driver and the application.
 *
 * It is retrieved with IDirectFB::GetInterface() with the following specific parameters:
 * - type = "ISystemBridge"
 * - arg = NULL
 *
 * \ingroup DFBAMP
 */
MY_DEFINE_INTERFACE( ISystemBridge )

    /**
     * Get the underlying system name.
     */
    DFBResult (*GetSystemName) (
        ISystemBridge      *thiz,
        const char        **ret_name
    );

   /**
    * Sets a system variable.
    *
    * For Sigma Designs hardware, the currently supported variables
    * are: <ul>
    * <li>"sglobals" - pass a pointer to an application-initialized
    * SGlobals object</li>
    * <li>"mem-block" - pass the DRAM data (char*) of a memory
    * block to be used by DirectFB as video memory (for
    * surface allocations) - must be set before sglobals<br>
    * The format of the data is "<dram_index> <dram_address>
    * <mapped_address> <size>", where all but mapped_address
    * are u32 values in hexadecimal (%lx) and mapped_address is a
    * void* (%p).</li>
    * <li>"primary-layer-front" - pass the preallocation data
    * (char*) of a memory region to be used by DirectFB as
    * the front buffer of the primary layer surface.<br>
    * The format of the data is "<dram_address> <mapped_address>
    * <pitch> <width> <height> <format>", where all but
    * mapped_address are u32 values in hexadecimal (%lx) and
    * mapped_address is a void* (%p). format is a
    * DFBSurfacePixelFormat in hexadecimal.</li>
    * <li>"primary-layer-back" - pass the preallocation data
    * (char*) of a memory region to be used by DirectFB as the
    * back buffer of the primary layer surface (if double buffering
    * is to be used). Same format as primary-layer-front.
    * </ul>
    * They can only be set in GFX-only mode, as they are normally
    * controlled and initialized by DirectFB.
    */
    DFBResult (*SetVariable) (
        ISystemBridge      *thiz,
        const char         *name,
        void               *value
    );

   /**
    * Gets a system variable.
    *
    * System variables currently supported by the Sigma Designs platform:
    * - "sglobals": retrieves the address of the global data area to be used by the DirectFB driver
    */
    DFBResult (*GetVariable) (
        ISystemBridge      *thiz,
        const char         *name,
        void              **ret_value
    );
#ifdef __DOC__
};
#else
)
#endif

#ifdef __cplusplus
}
#endif

#endif //_ISYSTEMBRIDGE_H_

