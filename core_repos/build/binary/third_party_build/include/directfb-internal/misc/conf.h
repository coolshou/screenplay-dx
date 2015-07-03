/*
   (c) Copyright 2001-2007  The DirectFB Organization (directfb.org)
   (c) Copyright 2000-2004  Convergence (integrated media) GmbH

   All rights reserved.

   Written by Denis Oliver Kropp <dok@directfb.org>,
              Andreas Hundt <andi@fischlustig.de>,
              Sven Neumann <neo@directfb.org>,
              Ville Syrjälä <syrjala@sci.fi> and
              Claudio Ciccani <klan@users.sf.net>.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the
   Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.

   Sigma modified.
*/

#ifndef __CONF_H__
#define __CONF_H__

#include <signal.h>

#include <directfb.h>
#include <fusion/types.h>

typedef struct
{
     DFBDisplayLayerBackgroundMode layer_bg_mode; /* background mode for
                                                     primary layer */
     DFBColor  layer_bg_color;                    /* background color for
                                                     primary layer */
     char     *layer_bg_filename;                 /* background image for
                                                     primary layer */

     bool      mouse_motion_compression;          /* use motion compression? */
     char     *mouse_protocol;                    /* mouse protocol */
     char     *mouse_source;                      /* mouse source device name */
     bool      mouse_gpm_source;                  /* mouse source is gpm? */

     int       window_policy;                     /* swapping policy for the
                                                     surface of a window */
     int       buffer_mode;                       /* default buffer mode for
                                                     primary layer */

     bool      pollvsync_after;
     bool      pollvsync_none;

     bool      software_only;                     /* disable hardware acceleration */
     bool      hardware_only;                     /* disable software fallbacks */

     bool      mmx;                               /* mmx support */

     bool      banner;                            /* startup banner */

     bool      force_windowed;                    /* prohibit exclusive modes */

     bool      deinit_check;

     bool      vt_switch;                         /* allocate a new VT */
     int       vt_num;                            /* number of TTY to use or -1
                                                     if the default */
     bool      kd_graphics;                       /* put terminal into graphics
                                                     mode */

     DFBScreenEncoderTVStandards matrox_tv_std;   /* Matrox TV standard */
     int       matrox_cable;                      /* Matrox cable type */
     bool      matrox_sgram;                      /* Use Matrox SGRAM features */
     bool      matrox_crtc2;                      /* Experimental CRTC2 stuff */

     bool      sync;                              /* Do sync() in core_init() */
     bool      vt_switching;                      /* Allow VT switching by
                                                     pressing Ctrl+Alt+<F?> */

     char     *fb_device;                         /* Used framebuffer device,
                                                     e.g. "/dev/fb0" */

     struct {
          int  bus;                               /* PCI Bus */
          int  dev;                               /* PCI Device */
          int  func;                              /* PCI Function */
     } pci;

     bool      lefty;                             /* Left handed mouse, swaps
                                                     left/right mouse buttons */
     bool      no_cursor;                         /* Never create a cursor */
     bool      translucent_windows;               /* Allow translucent
                                                     windows */

     struct {
          int                   width;            /* primary layer width */
          int                   height;           /* primary layer height */
          int                   depth;            /* primary layer depth */
          DFBSurfacePixelFormat format;           /* primary layer format */
     } mode;

     struct {
          int                   width;            /* scaled window width */
          int                   height;           /* scaled window height */
     } scaled;

     int       videoram_limit;                    /* limit amount of video
                                                     memory used by DirectFB */

     char     *screenshot_dir;                    /* dump screen content into
                                                     this directory */

     char     *system;                            /* FBDev, SDL, etc. */

     bool      capslock_meta;                     /* map CapsLock -> Meta */

     bool      block_all_signals;                 /* block all signals */

     int       session;                           /* select multi app world */

     int       primary_layer;                     /* select alternative primary
                                                     display layer */

     bool      force_desktop;                     /* Desktop background is
                                                     the primary surface. */

     bool      linux_input_ir_only;               /* Ignore non-IR devices. */

     struct {
          char *host;                             /* Remote host to connect to. */
          int   session;                          /* Remote session number. */
     } remote;

     char      *wm;                               /* Window manager to use. */

     bool       vt;                               /* Use VT stuff at all? */

     bool       decorations;                      /* Enable window decorations. */

     DFBSurfacePixelFormat font_format;           /* Preferred font format. */

     char      *h3600_device;                     /* H3600 Touchscreen Device */

     char      *mut_device;                       /* MuTouch Device */

     char      *penmount_device;                  /* PenMount Device */

	 DFBScreenEncoderTVStandards dtv_tv_standard;       	/* Selected TV standard. */
     DFBScreenOutputSignals      dtv_out_signals;       	/* Selected encoder signal(s). */
     DFBScreenOutputConnectors   dtv_out_connectors;    	/* Selected output connector(s). */
     DFBScreenOutputConnectors   dtv_available_connectors;  /* Available output connector(s). */

	 DFBScreenEncoderTVStandards component_tv_standard;       	/* Selected TV standard. */
	 DFBScreenOutputSignals      component_out_signals;       	/* Selected encoder signal(s). */
	 DFBScreenOutputConnectors   component_out_connectors;    	/* Selected output connector(s). */
	 DFBScreenOutputConnectors   component_available_connectors;  /* Available output connector(s). */

	 DFBScreenEncoderTVStandards analog_tv_standard;       	/* Selected TV standard. */
	 DFBScreenOutputSignals      analog_out_signals;       	/* Selected encoder signal(s). */
	 DFBScreenOutputConnectors   analog_out_connectors;    	/* Selected output connector(s). */
	 DFBScreenOutputConnectors   analog_available_connectors;  /* Available output connector(s). */

     char driver_cfg_file_name[256];					/* File name for driver-specific configurations */

	 DFBDisplayLayerFlickerFilter osd_flicker_filter;	/* OSD layer flicker filtering mode. */
	 DFBDeinterlacingMode deint_mode;	/* OSD layer flicker filtering mode. */

	 void		(*wm_repaint_stack_callback)(void);		/* If not NULL, called by the default window stack repaint_stack after the repaint is done */

     bool       smp_gfx_only;                     /* Disable outputs and layer control for Sigma driver */

     int        unichrome_revision;               /* Unichrome hardware
                                                     revision number override */

     bool       dma;                              /* Enable DMA */

     int        agp;                              /* AGP mode */
     int        agpmem_limit;                     /* Limit of AGP memory
                                                     used by DirectFB */
     bool       i8xx_overlay_pipe_b;              /* video overlay output via pixel pipe B */
     bool       primary_only;                     /* tell application only about primary layer */

     bool       thrifty_surface_buffers;          /* don't keep system instance while video instance is alive */
} DFBConfig;

extern DFBConfig *dfb_config;

/*
 * Allocate Config struct, fill with defaults and parse command line options
 * for overrides. Options identified as DirectFB options are stripped out
 * of the array.
 */
DFBResult dfb_config_init( int *argc, char *(*argv[]) );

/*
 * Pointer to generic config setting function, allows chipset driver to use
 * the configuration mechanism (i.e. dfb_config_read())
 */
typedef DFBResult (*config_set_type)( const char *name, const char *value );

/*
 * Read configuration options from file. Called by config_init().
 *
 * Returns DFB_IO if config file could not be opened.
 * Returns DFB_UNSUPPORTED if file contains an invalid option.
 * Returns DFB_INVARG if an invalid option assignment is done,
 * e.g. "--desktop-buffer-mode=somethingwrong".
 */
DFBResult dfb_config_read( const char *filename, config_set_type config_set );

/*
 * Set indiviual option. Used by config_init(), config_read() and
 * DirectFBSetOption()
 */
DFBResult dfb_config_set( const char *name, const char *value );

const char *dfb_config_usage( void );

#endif

