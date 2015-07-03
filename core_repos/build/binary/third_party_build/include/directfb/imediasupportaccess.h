/*****************************************
 Copyright  2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/*
 * \file imediasupportaccess.h
 * \brief Media support (optical disc, etc) access interface
*/

#ifndef IMEDIASUPPORTACCESS_H_
#define IMEDIASUPPORTACCESS_H_

#ifdef LINUX
#include <linux/limits.h>
#else
#define PATH_MAX 4096
#endif

#include <directfb.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * Media support directory entry info - see IMediaSupportAccess <b>Sigma extension</b>.
 */
typedef struct {
    bool  	isDirectory;
    char  	name[PATH_MAX+1];
    char  	parentDirName[PATH_MAX+1];
} DFBDirEntryInfo;

/*
 * <A HREF="../group___d_f_b_a_m_p.html"><b>Sigma advanced media extension</b></A>: Interface for accessing the media support (optical disc, for example)
 */
DECLARE_INTERFACE( IMediaSupportAccess )

#ifdef __DOC__
#define MY_DEFINE_INTERFACE(IF)		struct IF {
#else
#define MY_DEFINE_INTERFACE(IF)		DEFINE_INTERFACE(IF,
#endif

/**
 * Interface for accessing the media support (disc, for example).
 *
 * Media supports that are suuported by the OS will fail to mount,
 * client application should use the OS I/O functions to access it.
 * \ingroup DFBAMP
 */
MY_DEFINE_INTERFACE( IMediaSupportAccess)

    DFBResult (*fopen) (IMediaSupportAccess *thiz, char *pFullFileName, void **phFileHandle);
    DFBResult (*fclose) (IMediaSupportAccess *thiz, void *hFileHandle);
    DFBResult (*fread) (IMediaSupportAccess *thiz, void *hFileHandle, unsigned char *pbBufUser, unsigned long nBytesToRead, unsigned long *pnBytesRead);
    DFBResult (*fsize) (IMediaSupportAccess *thiz, void *hFileHandle, unsigned long long *pdwFileSize);
    DFBResult (*ftell) (IMediaSupportAccess *thiz, void *hFileHandle, unsigned long long *pdwInternalCurPos);
    DFBResult (*fseek) (IMediaSupportAccess *thiz, void *hFileHandle, long dwPosRel, long dwFlagRel);
    DFBResult (*feof) (IMediaSupportAccess *thiz, void *hFileHandle, unsigned long *pdwFEOF);

    DFBResult (*dopen) (IMediaSupportAccess *thiz, char *pFullDirName, void **phDirHandle);
    DFBResult (*dclose) (IMediaSupportAccess *thiz, void *hDirHandle);
    DFBResult (*dread) (IMediaSupportAccess *thiz, void *hDirHandle, DFBDirEntryInfo *pDirInfo);
    DFBResult (*dseek) (IMediaSupportAccess *thiz, void *hDirHandle, unsigned long dwZeroBasedIndexValidEntry);

	/**
	 * Mounts the media support at the specified URL.
	 *
	 * Releasing the interface unmounts the media (possiby delayed until AMP terminates too).
	 *
	 * If url specifies a file on disc, it must be of /dev/cdroms/cdrom0//directory/file format (note the double slashes),
	 * so that the device can be mounted automatically, otherwise the entire url's treated as a device
	 */
	DFBResult (*MountMedia) (
		IMediaSupportAccess *thiz,
		char             	*url
	);

	/**
	 * Unmounts the currently mounted media support.
	 *
	 * Releasing the interface automatically unmounts the media.
	 */
	DFBResult (*UnmountMedia) (
		IMediaSupportAccess *thiz
	);
#ifdef __DOC__
};
#else
)
#endif

#ifdef __cplusplus
}
#endif

#endif /*IMEDIASUPPORTACCESS_H_*/
