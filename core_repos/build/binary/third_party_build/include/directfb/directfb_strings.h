#ifndef __DIRECTFB_STRINGS_H__
#define __DIRECTFB_STRINGS_H__

#define DirectFBPixelFormatNames(Identifier) struct DFBPixelFormatName { \
     DFBSurfacePixelFormat format; \
     const char *name; \
} Identifier[] = { \
     { DSPF_ARGB1555, "ARGB1555" }, \
     { DSPF_RGB16, "RGB16" }, \
     { DSPF_RGB24, "RGB24" }, \
     { DSPF_RGB32, "RGB32" }, \
     { DSPF_ARGB, "ARGB" }, \
     { DSPF_A8, "A8" }, \
     { DSPF_YUY2, "YUY2" }, \
     { DSPF_RGB332, "RGB332" }, \
     { DSPF_UYVY, "UYVY" }, \
     { DSPF_I420, "I420" }, \
     { DSPF_YV12, "YV12" }, \
     { DSPF_LUT8, "LUT8" }, \
     { DSPF_ALUT44, "ALUT44" }, \
     { DSPF_AiRGB, "AiRGB" }, \
     { DSPF_A1, "A1" }, \
     { DSPF_NV12, "NV12" }, \
     { DSPF_NV16, "NV16" }, \
     { DSPF_ARGB2554, "ARGB2554" }, \
     { DSPF_ARGB4444, "ARGB4444" }, \
     { DSPF_NV21, "NV21" }, \
     { DSPF_AYUV, "AYUV" }, \
     { DSPF_A4, "A4" }, \
     { DSPF_ARGB1666, "ARGB1666" }, \
     { DSPF_ARGB6666, "ARGB6666" }, \
     { DSPF_RGB18, "RGB18" }, \
     { DSPF_LUT2, "LUT2" }, \
     { DSPF_I422, "I422" }, \
     { DSPF_AVYU, "AVYU" }, \
     { DSPF_UNKNOWN, "UNKNOWN" } \
};

#define DirectFBInputDeviceTypeFlagsNames(Identifier) struct DFBInputDeviceTypeFlagsName { \
     DFBInputDeviceTypeFlags type; \
     const char *name; \
} Identifier[] = { \
     { DIDTF_KEYBOARD, "KEYBOARD" }, \
     { DIDTF_MOUSE, "MOUSE" }, \
     { DIDTF_JOYSTICK, "JOYSTICK" }, \
     { DIDTF_REMOTE, "REMOTE" }, \
     { DIDTF_VIRTUAL, "VIRTUAL" }, \
     { DIDTF_NONE, "NONE" } \
};

#define DirectFBSurfaceDrawingFlagsNames(Identifier) struct DFBSurfaceDrawingFlagsName { \
     DFBSurfaceDrawingFlags flag; \
     const char *name; \
} Identifier[] = { \
     { DSDRAW_BLEND, "BLEND" }, \
     { DSDRAW_DST_COLORKEY, "DST_COLORKEY" }, \
     { DSDRAW_SRC_PREMULTIPLY, "SRC_PREMULTIPLY" }, \
     { DSDRAW_DST_PREMULTIPLY, "DST_PREMULTIPLY" }, \
     { DSDRAW_DEMULTIPLY, "DEMULTIPLY" }, \
     { DSDRAW_XOR, "XOR" }, \
     { DSDRAW_NOFX, "NOFX" } \
};

#define DirectFBSurfaceBlittingFlagsNames(Identifier) struct DFBSurfaceBlittingFlagsName { \
     DFBSurfaceBlittingFlags flag; \
     const char *name; \
} Identifier[] = { \
     { DSBLIT_BLEND_ALPHACHANNEL, "BLEND_ALPHACHANNEL" }, \
     { DSBLIT_BLEND_COLORALPHA, "BLEND_COLORALPHA" }, \
     { DSBLIT_COLORIZE, "COLORIZE" }, \
     { DSBLIT_SRC_COLORKEY, "SRC_COLORKEY" }, \
     { DSBLIT_DST_COLORKEY, "DST_COLORKEY" }, \
     { DSBLIT_SRC_PREMULTIPLY, "SRC_PREMULTIPLY" }, \
     { DSBLIT_DST_PREMULTIPLY, "DST_PREMULTIPLY" }, \
     { DSBLIT_DEMULTIPLY, "DEMULTIPLY" }, \
     { DSBLIT_DEINTERLACE, "DEINTERLACE" }, \
     { DSBLIT_SRC_PREMULTCOLOR, "SRC_PREMULTCOLOR" }, \
     { DSBLIT_XOR, "XOR" }, \
     { DSBLIT_INDEX_TRANSLATION, "INDEX_TRANSLATION" }, \
     { DSBLIT_NOFX, "NOFX" } \
};

#define DirectFBInputDeviceCapabilitiesNames(Identifier) struct DFBInputDeviceCapabilitiesName { \
     DFBInputDeviceCapabilities capability; \
     const char *name; \
} Identifier[] = { \
     { DICAPS_KEYS, "KEYS" }, \
     { DICAPS_AXES, "AXES" }, \
     { DICAPS_BUTTONS, "BUTTONS" }, \
     { DICAPS_NONE, "NONE" } \
};

#define DirectFBDisplayLayerTypeFlagsNames(Identifier) struct DFBDisplayLayerTypeFlagsName { \
     DFBDisplayLayerTypeFlags type; \
     const char *name; \
} Identifier[] = { \
     { DLTF_GRAPHICS, "GRAPHICS" }, \
     { DLTF_VIDEO, "VIDEO" }, \
     { DLTF_STILL_PICTURE, "STILL_PICTURE" }, \
     { DLTF_BACKGROUND, "BACKGROUND" }, \
     { DLTF_NONE, "NONE" } \
};

#define DirectFBDisplayLayerCapabilitiesNames(Identifier) struct DFBDisplayLayerCapabilitiesName { \
     DFBDisplayLayerCapabilities capability; \
     const char *name; \
} Identifier[] = { \
     { DLCAPS_SURFACE, "SURFACE" }, \
     { DLCAPS_OPACITY, "OPACITY" }, \
     { DLCAPS_ALPHACHANNEL, "ALPHACHANNEL" }, \
     { DLCAPS_SCREEN_LOCATION, "SCREEN_LOCATION" }, \
     { DLCAPS_FLICKER_FILTERING, "FLICKER_FILTERING" }, \
     { DLCAPS_DEINTERLACING, "DEINTERLACING" }, \
     { DLCAPS_SRC_COLORKEY, "SRC_COLORKEY" }, \
     { DLCAPS_DST_COLORKEY, "DST_COLORKEY" }, \
     { DLCAPS_BRIGHTNESS, "BRIGHTNESS" }, \
     { DLCAPS_CONTRAST, "CONTRAST" }, \
     { DLCAPS_HUE, "HUE" }, \
     { DLCAPS_SATURATION, "SATURATION" }, \
     { DLCAPS_COLOR_SPACE, "COLOR_SPACE" }, \
     { DLCAPS_LEVELS, "LEVELS" }, \
     { DLCAPS_FIELD_PARITY, "FIELD_PARITY" }, \
     { DLCAPS_WINDOWS, "WINDOWS" }, \
     { DLCAPS_SOURCES, "SOURCES" }, \
     { DLCAPS_ALPHA_RAMP, "ALPHA_RAMP" }, \
     { DLCAPS_PREMULTIPLIED, "PREMULTIPLIED" }, \
     { DLCAPS_SCREEN_POSITION, "SCREEN_POSITION" }, \
     { DLCAPS_SCREEN_SIZE, "SCREEN_SIZE" }, \
     { DLCAPS_CLIP_REGIONS, "CLIP_REGIONS" }, \
     { DLCAPS_ASPECT_MATCHING, "ASPECT_MATCHING" }, \
     { DLCAPS_STEREO_FORMATS, "STEREO_FORMATS" }, \
     { DLCAPS_STEREO_SOURCE, "STEREO_SOURCE" }, \
     { DLCAPS_STEREO_UPMIX, "STEREO_UPMIX" }, \
     { DLCAPS_NONE, "NONE" } \
};

#define DirectFBDisplayLayerBufferModeNames(Identifier) struct DFBDisplayLayerBufferModeName { \
     DFBDisplayLayerBufferMode mode; \
     const char *name; \
} Identifier[] = { \
     { DLBM_FRONTONLY, "FRONTONLY" }, \
     { DLBM_BACKVIDEO, "BACKVIDEO" }, \
     { DLBM_BACKSYSTEM, "BACKSYSTEM" }, \
     { DLBM_TRIPLE, "TRIPLE" }, \
     { DLBM_WINDOWS, "WINDOWS" }, \
     { DLBM_UNKNOWN, "UNKNOWN" } \
};

#define DirectFBScreenCapabilitiesNames(Identifier) struct DFBScreenCapabilitiesName { \
     DFBScreenCapabilities capability; \
     const char *name; \
} Identifier[] = { \
     { DSCCAPS_VSYNC, "VSYNC" }, \
     { DSCCAPS_POWER_MANAGEMENT, "POWER_MANAGEMENT" }, \
     { DSCCAPS_MIXERS, "MIXERS" }, \
     { DSCCAPS_ENCODERS, "ENCODERS" }, \
     { DSCCAPS_OUTPUTS, "OUTPUTS" }, \
     { DSCCAPS_NONE, "NONE" } \
};

#define DirectFBScreenEncoderCapabilitiesNames(Identifier) struct DFBScreenEncoderCapabilitiesName { \
     DFBScreenEncoderCapabilities capability; \
     const char *name; \
} Identifier[] = { \
     { DSECAPS_TV_STANDARDS, "TV_STANDARDS" }, \
     { DSECAPS_TEST_PICTURE, "TEST_PICTURE" }, \
     { DSECAPS_MIXER_SEL, "MIXER_SEL" }, \
     { DSECAPS_OUT_SIGNALS, "OUT_SIGNALS" }, \
     { DSECAPS_SCANMODE, "SCANMODE" }, \
     { DSECAPS_BRIGHTNESS, "BRIGHTNESS" }, \
     { DSECAPS_CONTRAST, "CONTRAST" }, \
     { DSECAPS_HUE, "HUE" }, \
     { DSECAPS_SATURATION, "SATURATION" }, \
     { DSECAPS_CONNECTORS, "CONNECTORS" }, \
     { DSECAPS_SLOW_BLANKING, "SLOW_BLANKING" }, \
     { DSECAPS_COLOR_SPACE, "COLOR_SPACE" }, \
     { DSECAPS_ASPECT_MATCH, "ASPECT_MATCH" }, \
     { DSECAPS_DEINTERLACING_MODE, "DEINTERLACING_MODE" }, \
     { DSECAPS_STEREO_FORMATS, "STEREO_FORMATS" }, \
     { DSECAPS_NONE, "NONE" } \
};

#define DirectFBScreenEncoderTypeNames(Identifier) struct DFBScreenEncoderTypeName { \
     DFBScreenEncoderType type; \
     const char *name; \
} Identifier[] = { \
     { DSET_CRTC, "CRTC" }, \
     { DSET_TV, "TV" }, \
     { DSET_DTV, "DTV" }, \
     { DSET_UNKNOWN, "UNKNOWN" } \
};

#define DirectFBScreenEncoderTVStandardsNames(Identifier) struct DFBScreenEncoderTVStandardsName { \
     DFBScreenEncoderTVStandards standard; \
     const char *name; \
} Identifier[] = { \
     { DSETV_PAL, "PAL" }, \
     { DSETV_NTSC, "NTSC" }, \
     { DSETV_SECAM, "SECAM" }, \
     { DSETV_PAL_60, "PAL_60" }, \
     { DSETV_HDTV60, "HDTV60" }, \
     { DSETV_HDTV50, "HDTV50" }, \
     { DSETV_VESA, "VESA" }, \
     { DSETV_CVT, "CVT" }, \
     { DSETV_UNKNOWN, "UNKNOWN" } \
};

#define DirectFBScreenOutputCapabilitiesNames(Identifier) struct DFBScreenOutputCapabilitiesName { \
     DFBScreenOutputCapabilities capability; \
     const char *name; \
} Identifier[] = { \
     { DSOCAPS_CONNECTORS, "CONNECTORS" }, \
     { DSOCAPS_ENCODER_SEL, "ENCODER_SEL" }, \
     { DSOCAPS_SIGNAL_SEL, "SIGNAL_SEL" }, \
     { DSOCAPS_CONNECTOR_SEL, "CONNECTOR_SEL" }, \
     { DSOCAPS_SLOW_BLANKING, "SLOW_BLANKING" }, \
     { DSOCAPS_STEREOSCOPIC_FORMATS, "STEREOSCOPIC_FORMATS" }, \
     { DSOCAPS_NONE, "NONE" } \
};

#define DirectFBScreenOutputConnectorsNames(Identifier) struct DFBScreenOutputConnectorsName { \
     DFBScreenOutputConnectors connector; \
     const char *name; \
} Identifier[] = { \
     { DSOC_VGA, "VGA" }, \
     { DSOC_SCART, "SCART" }, \
     { DSOC_YC, "YC" }, \
     { DSOC_CVBS, "CVBS" }, \
     { DSOC_DVI, "DVI" }, \
     { DSOC_HDMI, "HDMI" }, \
     { DSOC_COMPONENT, "COMPONENT" }, \
     { DSOC_YCrCb, "YCrCb" }, \
     { DSOC_SCART2, "SCART2" }, \
     { DSOC_UNKNOWN, "UNKNOWN" } \
};

#define DirectFBScreenOutputSignalsNames(Identifier) struct DFBScreenOutputSignalsName { \
     DFBScreenOutputSignals signal; \
     const char *name; \
} Identifier[] = { \
     { DSOS_NTSC, "NTSC" }, \
     { DSOS_NTSC_J, "NTSC_J" }, \
     { DSOS_SECAM, "SECAM" }, \
     { DSOS_PAL, "PAL" }, \
     { DSOS_PAL_M, "PAL_M" }, \
     { DSOS_PAL_60, "PAL_60" }, \
     { DSOS_SDTV, "SDTV" }, \
     { DSOS_EDTV, "EDTV" }, \
     { DSOS_640x480, "640x480" }, \
     { DSOS_800x600, "800x600" }, \
     { DSOS_1024x768, "1024x768" }, \
     { DSOS_1152x864, "1152x864" }, \
     { DSOS_720p, "720p" }, \
     { DSOS_1280x768, "1280x768" }, \
     { DSOS_1280x960, "1280x960" }, \
     { DSOS_1280x1024, "1280x1024" }, \
     { DSOS_1360x768, "1360x768" }, \
     { DSOS_1366x768, "1366x768" }, \
     { DSOS_1400x1050, "1400x1050" }, \
     { DSOS_1440x900, "1440x900" }, \
     { DSOS_1600x1200, "1600x1200" }, \
     { DSOS_1680x1050, "1680x1050" }, \
     { DSOS_1792x1344, "1792x1344" }, \
     { DSOS_1856x1392, "1856x1392" }, \
     { DSOS_1080i, "1080i" }, \
     { DSOS_1080p24, "1080p24" }, \
     { DSOS_1080p, "1080p" }, \
     { DSOS_1920x1200, "1920x1200" }, \
     { DSOS_1920x1440, "1920x1440" }, \
     { DSOS_EDID, "EDID" }, \
     { DSOS_NONE, "NONE" } \
};

#define DirectFBScreenOutputSlowBlankingSignalsNames(Identifier) struct DFBScreenOutputSlowBlankingSignalsName { \
     DFBScreenOutputSlowBlankingSignals slow_signal; \
     const char *name; \
} Identifier[] = { \
     { DSOSB_16x9, "16x9" }, \
     { DSOSB_4x3, "4x3" }, \
     { DSOSB_FOLLOW, "FOLLOW" }, \
     { DSOSB_MONITOR, "MONITOR" }, \
     { DSOSB_OFF, "OFF" } \
};

#define DirectFBScreenMixerCapabilitiesNames(Identifier) struct DFBScreenMixerCapabilitiesName { \
     DFBScreenMixerCapabilities capability; \
     const char *name; \
} Identifier[] = { \
     { DSMCAPS_FULL, "FULL" }, \
     { DSMCAPS_SUB_LEVEL, "SUB_LEVEL" }, \
     { DSMCAPS_SUB_LAYERS, "SUB_LAYERS" }, \
     { DSMCAPS_BACKGROUND, "BACKGROUND" }, \
     { DSMCAPS_NONE, "NONE" } \
};

#define DirectFBScreenMixerTreeNames(Identifier) struct DFBScreenMixerTreeName { \
     DFBScreenMixerTree tree; \
     const char *name; \
} Identifier[] = { \
     { DSMT_FULL, "FULL" }, \
     { DSMT_SUB_LEVEL, "SUB_LEVEL" }, \
     { DSMT_SUB_LAYERS, "SUB_LAYERS" }, \
     { DSMT_UNKNOWN, "UNKNOWN" } \
};

#define DirectFBScreenEncoderTestPictureNames(Identifier) struct DFBScreenEncoderTestPictureName { \
     DFBScreenEncoderTestPicture test_picture; \
     const char *name; \
} Identifier[] = { \
     { DSETP_MULTI, "MULTI" }, \
     { DSETP_SINGLE, "SINGLE" }, \
     { DSETP_WHITE, "WHITE" }, \
     { DSETP_YELLOW, "YELLOW" }, \
     { DSETP_CYAN, "CYAN" }, \
     { DSETP_GREEN, "GREEN" }, \
     { DSETP_MAGENTA, "MAGENTA" }, \
     { DSETP_RED, "RED" }, \
     { DSETP_BLUE, "BLUE" }, \
     { DSETP_BLACK, "BLACK" }, \
     { DSETP_OFF, "OFF" } \
};

#define DirectFBScreenEncoderScanModeNames(Identifier) struct DFBScreenEncoderScanModeName { \
     DFBScreenEncoderScanMode scan_mode; \
     const char *name; \
} Identifier[] = { \
     { DSESM_INTERLACED, "INTERLACED" }, \
     { DSESM_PROGRESSIVE, "PROGRESSIVE" }, \
     { DSESM_UNKNOWN, "UNKNOWN" } \
};

#define DirectFBAccelerationMaskNames(Identifier) struct DFBAccelerationMaskName { \
     DFBAccelerationMask mask; \
     const char *name; \
} Identifier[] = { \
     { DFXL_FILLRECTANGLE, "FILLRECTANGLE" }, \
     { DFXL_DRAWRECTANGLE, "DRAWRECTANGLE" }, \
     { DFXL_DRAWLINE, "DRAWLINE" }, \
     { DFXL_FILLTRIANGLE, "FILLTRIANGLE" }, \
     { DFXL_BLIT, "BLIT" }, \
     { DFXL_STRETCHBLIT, "STRETCHBLIT" }, \
     { DFXL_TEXTRIANGLES, "TEXTRIANGLES" }, \
     { DFXL_GEOMETRIC_XFORM, "GEOMETRIC_XFORM" }, \
     { DFXL_DRAWSTRING, "DRAWSTRING" }, \
     { DFXL_NONE, "NONE" } \
};

#define DirectFBScreenEncoderConfigFlagsNames(Identifier) struct DFBScreenEncoderConfigFlagsName { \
     DFBScreenEncoderConfigFlags flag; \
     const char *name; \
} Identifier[] = { \
     { DSECONF_TV_STANDARD, "TV_STANDARD" }, \
     { DSECONF_TEST_PICTURE, "TEST_PICTURE" }, \
     { DSECONF_MIXER, "MIXER" }, \
     { DSECONF_OUT_SIGNALS, "OUT_SIGNALS" }, \
     { DSECONF_SCANMODE, "SCANMODE" }, \
     { DSECONF_TEST_COLOR, "TEST_COLOR" }, \
     { DSECONF_ADJUSTMENT, "ADJUSTMENT" }, \
     { DSECONF_CONNECTORS, "CONNECTORS" }, \
     { DSECONF_SLOW_BLANKING, "SLOW_BLANKING" }, \
     { DSECONF_ASPECT_MATCH, "ASPECT_MATCH" }, \
     { DSECONF_DEINTERLACING_MODE, "DEINTERLACING_MODE" }, \
     { DSECONF_DELAYED_CONFIG, "DELAYED_CONFIG" }, \
     { DSECONF_STEREO_FORMAT, "STEREO_FORMAT" }, \
     { DSECONF_STEREO_AUTO_FORMAT, "STEREO_AUTO_FORMAT" }, \
     { DSECONF_NONE, "NONE" } \
};

#define DirectFBAspectRatioMatchNames(Identifier) struct DFBAspectRatioMatchName { \
     DFBAspectRatioMatch match; \
     const char *name; \
} Identifier[] = { \
     { DARM_AUTO, "AUTO" }, \
     { DARM_LETTER_BOX, "LETTER_BOX" }, \
     { DARM_PAN_SCAN, "PAN_SCAN" }, \
     { DARM_SIDE_PANEL, "SIDE_PANEL" }, \
     { DARM_CROP, "CROP" }, \
     { DARM_ZOOM, "ZOOM" }, \
     { DARM_PANORAMA, "PANORAMA" }, \
     { DARM_NONE, "NONE" }, \
     { DARM_NOT_SET, "NOT_SET" } \
};

#define DirectFBDisplayLayerFlickerFilterNames(Identifier) struct DFBDisplayLayerFlickerFilterName { \
     DFBDisplayLayerFlickerFilter filter; \
     const char *name; \
} Identifier[] = { \
     { DLFF_LOW, "LOW" }, \
     { DLFF_MEDIUM, "MEDIUM" }, \
     { DLFF_OFF, "OFF" } \
};

#define DirectFBDeinterlacingModeNames(Identifier) struct DFBDeinterlacingModeName { \
     DFBDeinterlacingMode mode; \
     const char *name; \
} Identifier[] = { \
     { DDM_WEAVE, "WEAVE" }, \
     { DDM_ADAPTIVE, "ADAPTIVE" }, \
     { DDM_IVTC, "IVTC" }, \
     { DDM_PROGRESSIVE, "PROGRESSIVE" }, \
     { DDM_ADAPTIVE_TWO_FIELDS, "ADAPTIVE_TWO_FIELDS" }, \
     { DDM_NONE, "NONE" } \
};

#define DirectFBColorSpaceNames(Identifier) struct DFBColorSpaceName { \
     DFBColorSpace space; \
     const char *name; \
} Identifier[] = { \
     { DCS_RGB, "RGB" }, \
     { DCS_RGB_16_235, "RGB_16_235" }, \
     { DCS_YUV_601, "YUV_601" }, \
     { DCS_YUV_709, "YUV_709" }, \
     { DCS_UNKNOWN, "UNKNOWN" } \
};

#define DirectFBColorAdjustmentFlagsNames(Identifier) struct DFBColorAdjustmentFlagsName { \
     DFBColorAdjustmentFlags flag; \
     const char *name; \
} Identifier[] = { \
     { DCAF_BRIGHTNESS, "BRIGHTNESS" }, \
     { DCAF_CONTRAST, "CONTRAST" }, \
     { DCAF_HUE, "HUE" }, \
     { DCAF_SATURATION, "SATURATION" }, \
     { DCAF_COLOR_SPACE, "COLOR_SPACE" }, \
     { DCAF_SATURATION_CB, "SATURATION_CB" }, \
     { DCAF_SATURATION_CR, "SATURATION_CR" }, \
     { DCAF_NONE, "NONE" } \
};

#define DirectFBStereoscopicFormatNames(Identifier) struct DFBStereoscopicFormatName { \
     DFBStereoscopicFormat flag; \
     const char *name; \
} Identifier[] = { \
     { DSSF_SIDE_BY_SIDE_HALF, "SIDE_BY_SIDE_HALF" }, \
     { DSSF_TOP_AND_BOTTOM_HALF, "TOP_AND_BOTTOM_HALF" }, \
     { DSSF_NONE, "NONE" } \
};

#endif
