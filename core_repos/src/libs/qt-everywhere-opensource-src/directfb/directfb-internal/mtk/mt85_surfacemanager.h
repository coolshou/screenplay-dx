/********************************************************************************************
 *     LEGAL DISCLAIMER 
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES 
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED 
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS 
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED, 
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR 
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY 
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, 
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK 
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION 
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *     
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH 
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, 
 *     TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE 
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE. 
 *     
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS 
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.  
 ************************************************************************************************/
/*
*
* \par Description
*   The definition of mt85 surface manager
*
*/


#ifndef __SURFACEMANAGER_H__
#define __SURFACEMANAGER_H__

#include <directfb.h>

#include <core/coretypes.h>
#include "mt85.h"

typedef struct _SurfaceManager SurfaceManager;
typedef struct _Chunk          Chunk;

/*
 * initially there is one big free chunk,
 * chunks are splitted into a free and an occupied chunk if memory is allocated,
 * two chunks are merged to one free chunk if memory is deallocated
 */
struct _Chunk {
     int                  magic;

     int                  offset;      /* offset in memory,
                                          is greater or equal to the heap offset */
     int                  length;      /* length of this chunk in bytes */

     int                  pitch;

#if CONFIG_DIRECTFB_MULTI_MEM_POOL
     int                  poolno;
#endif
     
     CoreSurfaceBuffer   *buffer;      /* pointer to surface buffer occupying
                                          this chunk, or NULL if chunk is free */
     CoreSurfaceAllocation *allocation;

     int                  tolerations; /* number of times this chunk was scanned
                                          occupied, resetted in assure_video */

     Chunk               *prev;
     Chunk               *next;
};

struct _SurfaceManager {
     int                  magic;

     FusionSHMPoolShared *shmpool;
     
#if CONFIG_DIRECTFB_MULTI_MEM_POOL
     Chunk               *m_chunks[FB_MEM_SLICE_NUM];

     int                  m_offset[FB_MEM_SLICE_NUM];
     int                  m_length[FB_MEM_SLICE_NUM];
     int                  m_avail[FB_MEM_SLICE_NUM];

     int                  m_min_toleration[FB_MEM_SLICE_NUM];
#else
     Chunk               *chunks;

     int                  offset;
     int                  length;         /* length of the heap in bytes */
     int                  avail;          /* amount of available memory in bytes */

     int                  min_toleration;
#endif
     
     bool                 suspended;
};


DFBResult dfb_surfacemanager_create ( CoreDFB             *core,
                                      unsigned int         length,
                                      SurfaceManager     **ret_manager );

void      dfb_surfacemanager_destroy( SurfaceManager      *manager );

/*
 * finds and allocates one for the surface or fails,
 * after success the video health is CSH_RESTORE.
 * NOTE: this does not notify the listeners
 */
DFBResult dfb_surfacemanager_allocate( CoreDFB            *core,
                                       SurfaceManager     *manager,
                                       CoreSurfaceBuffer  *buffer,
                                       CoreSurfaceAllocation  *allocation,
                                       Chunk             **ret_chunk );

DFBResult dfb_surfacemanager_displace( CoreDFB           *core,
                                       SurfaceManager    *manager,
                                       CoreSurfaceBuffer *buffer );

/*
 * sets the video health to CSH_INVALID frees the chunk and
 * notifies the listeners
 */
DFBResult dfb_surfacemanager_deallocate( SurfaceManager *manager,
                                         Chunk          *chunk );

#endif

