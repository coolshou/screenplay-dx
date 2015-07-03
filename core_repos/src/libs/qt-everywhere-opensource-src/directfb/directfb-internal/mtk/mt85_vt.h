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
*   The definition of mt85 vt
*
*/

#ifndef __VT_H__
#define __VT_H__

#include <signal.h>
#include <linux/vt.h>

#include <directfb.h>

typedef struct {
     int fd0;                      /* file descriptor of /dev/tty0 */
     int fd;                       /* file descriptor of /dev/ttyN
                                      where N is the number of the allocated VT,
                                      may be equal to 'fd0' if VT allocation
                                      is disabled by "--no-vt-switch" */

     int num;                      /* number of vt where DirectFB runs */
     int prev;                     /* number of vt DirectFB was started from */

     int old_fb;                   /* original fb mapped to vt */

     struct sigaction sig_usr1;    /* previous signal handler for USR1 */
     struct sigaction sig_usr2;    /* previous signal handler for USR2 */

     struct vt_mode   vt_mode;     /* previous VT mode */

     DirectThread    *thread;
     pthread_mutex_t  lock;
     pthread_cond_t   wait;

     int              vt_sig;
} VirtualTerminal;

/*
 * allocates and switches to a new virtual terminal
 */
DFBResult dfb_vt_initialize();
DFBResult dfb_vt_join();

/*
 * deallocates virtual terminal
 */
DFBResult dfb_vt_shutdown( bool emergency );
DFBResult dfb_vt_leave( bool emergency );

DFBResult dfb_vt_detach( bool force );

bool dfb_vt_switch( int num );

#endif
