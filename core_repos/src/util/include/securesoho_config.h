/* 
 * Copyright (C) 2006, Alphanetworks, inc.
 * Author: wills_yin@alphanetworks.com 
 * vim:cindent:ts=8:sw=8
 */
#ifndef __SECURESOHO_CONFIG_H__
#define __SECURESOHO_CONFIG_H__

#include "securesoho_wireless.h"
#include "securesoho_config.h"

#define WIRELESS_NIC_NAME    "wlan_name"

#define CONFIG_BGM_PLAYMODE  "CONFIG_BGM_PLAYMODE"
#define CONFIG_VIDEO_PLAYMODE  "CONFIG_VIDEO_PLAYMODE"
#define CONFIG_PHOTO_PLAYMODE  "CONFIG_PHOTO_PLAYMODE"
#define CONFIG_AUDIO_TRACK_DISPLAY "CONFIG_AUDIO_TRACK_DISPLAY"
#define CONFIG_AUTOPLAY_DEVICE "CONFIG_AUTOPLAY_DEVICE"
#define CONFIG_AUTO_PLAY		"CONFIG_AUTO_PLAY"
#define CONFIG_IPCAM_MD		"CONFIG_IPCAM_MD"

#define CONFIG_AUTO_AUDIO_OUT   "AUTO_AUDIO_OUT"

/*
 * The maximum and minimum value of the slideshow and screen saver period
 */
#define MAX_SCREEN_SAVER_PERIOD 60
#define MIN_SCREEN_SAVER_PERIOD 1
#define MAX_SLIDE_SHOW_PERIOD 30
#define MIN_SLIDE_SHOW_PERIOD 1

typedef enum _ENUM_securesoho_config_browse_type{
       SECURESOHO_BROWSE_TYPE_COMMON = 0,
       SECURESOHO_BROWSE_TYPE_MUSIC,
       SECURESOHO_BROWSE_TYPE_PHOTO,
       SECURESOHO_BROWSE_TYPE_MOVIE,
       SECURESOHO_BROWSE_TYPE_FILEOP,
       SECURESOHO_BROWSE_TYPE_DESKTOP,
       SECURESOHO_BROWSE_TYPE_LOCAL_THEME,
       SECURESOHO_BROWSE_TYPE_ONLINE,
       SECURESOHO_BROWSE_TYPE_DASHBOARD,
       SECURESOHO_BROWSE_TYPE_YOUTUBE,
}ENUM_securesoho_config_browse_type;

typedef enum{
	BROWSE_LIST = 0,
	BROWSE_THUMB,
	BROWSE_ALBUM_BOOK,
	BROWSE_PREVIEW,
	BROWSE_GALLERY,
	BROWSE_LIST_WITH_FILEOP,
}BROWSEMODE;

typedef enum {
	CON_WIRED = 0,
	CON_WIRELESS = 1,
	CON_UNKNOWN = 2

}CONNECTION;

typedef enum{
	AUTO 	= 0,
	MANUAL	= 1
}SET_DNS_SRV;

typedef enum{
	LAN_FIXEDIP = 0,
	LAN_DHCP = 1
}LANTYPE;

typedef struct {
        char name[64];
        char fwupcond;
	char run_wizard;
        long mediaserver_version;
} SecureSOHO_General;

typedef struct {
	char mac[32];
        char ip[16];
        char netmask[16];
	char gateway[16];
	char dns[16];
	char dns1[16];
	char domain[64];
	char host[65];
	char lan_ifname[10]; //Steven Kuo: Wireless interface name of Marvell chip is wdev0sta0
	LANTYPE lan_type;
	CONNECTION con_type;
	SET_DNS_SRV set_dns_srv;
} SecureSOHO_LAN;

/**
 * The object that represent the WAN seeting. It is the partial list of 
 * all SecureSOHO variables. The definition of each fields is quite 
 * self-describe. The type if WAN connection type,
 *  0: Disable.
 *  1: Static
 *  2: Dynamic
 *  3-4 : Obsolete
 *  5: PPPOE
 *  6: PPTP
 *  7: Wireless client mode
 */
typedef struct {
        int type;
	char ip[16];
	char mask[16];
	char gateway[16];
	char dns1[128];
	char dns2[128];
	char dns3[128];
} SecureSOHO_WAN;

typedef enum{
	TS_4_3_LB=0,
	TS_4_3_PS,
	TS_16_9_SD=32
}TV_SCAN_MODE;
/*
 * General settings 
 */
extern int securesoho_general_set(SecureSOHO_General *w, int restart);
extern int securesoho_general_get(SecureSOHO_General *w);

/*
 *  Update the LAN setup and restart the system to use the new value if the 
 * <restart> is 1.
 */
extern int securesoho_lan_set(SecureSOHO_LAN *lan, int restart);
extern int securesoho_lan_get(SecureSOHO_LAN *lan);

/*
 *  Update the wireless setting and restart the system to use the new value if
 *  the 'restart' is 1.
 */
extern int securesoho_wireless_set(SecureSOHO_Wireless *wireless, int restart);
extern int securesoho_wireless_get(SecureSOHO_Wireless *wireless);


/* 
 * Preset module
 */
extern int securesoho_preset_map_get(int preset_key, int *index);
extern int securesoho_preset_map_set(int preset_key, int index);
extern int securesoho_preset_url_set(int preset_key,const char *url);
extern int securesoho_preset_url_get(int preset_key,char **url);

/* 
 * Firmware update module
 */
extern int securesoho_get_curversion(char *pVer);
extern int securesoho_get_curbuilddate(char *pBuild);

extern int securesoho_get_fwup_server (char *FWUDSERVER);
extern int securesoho_get_fwup_version_file(char *FWUDVERINFOFILE);
extern int securesoho_get_fwup_server_usrpwd (char *FWUDUSRPWD);

extern int securesoho_firmware_checker_status_get(int *status);
extern int securesoho_firmware_checker_status_set(int status);

/*
 *  Slide show interval
 */
extern int securesoho_slideshow_set(int slideshow);  
extern int securesoho_slideshow_get(int *slideshow);  

/*
 * Idle time of screensaver 
 */
extern int securesoho_screensaver_set(int minute,int enable);
extern int securesoho_screensaver_get(int *minute,int *enable);

/*
 * Now playing infomation option 
 */
extern int securesoho_bgm_info_bar_set(int enable);
extern int securesoho_bgm_info_bar_get(int *enable);

/*
 * standby mode
 */
extern int securesoho_standby_mode_set(int enable);
extern int securesoho_standby_mode_get(int *enable);

/*
 * Current lan interface type being used
 */
extern int securesoho_lif_get(char *lif);
extern int securesoho_lif_type_get(CONNECTION *type);
extern int securesoho_lif_type_set(CONNECTION type);

/*
 *  Media Server
 */
extern int securesoho_media_server_set(const char *ServerHandle, const char*ServerName);
extern int securesoho_media_server_name_get(char *ServerName);
extern int securesoho_media_server_get(char *ServerHandle);

/*
 * Filename ???
 */
extern int securesoho_filename_set(int filename);
extern int securesoho_filename_get(int *filename);


/*
 * EULA(End User Licene Agreement) confirm
 */
extern void securesoho_eula_set(const char * confirmed);
extern void securesoho_eula_get(char * confirmed);

/*
 * Local for multilan
 */
extern void securesoho_locale_set(const char * localename);
extern void securesoho_locale_get(char * localename);

/*
 *Remote type
 */
extern int securesoho_remotetype_get(int* remotetype);
extern void securesoho_remotetype_set(int remotetype);

/*
 * DMA Device name
 */
extern int securesoho_devicename_set(char *devicename);
extern int securesoho_devicename_get(char *devicename);

/*
 * Voulume
 */
extern int config_set_volume(int iVolumn);
extern int config_get_volume(int *piVolumn);


/* 
 * The audo output interface mode 
 */
extern int securesoho_audiochannel_get(int* _5_1_or_2_channel);
extern void securesoho_audiochannel_set(int _5_1_or_2_channel);
extern int securesoho_tv_scan_get(TV_SCAN_MODE *tv_scan);
/* 
 * Photo show mode: slideshow/list 
 */
void securesoho_browsemode_set(int browsemode, ENUM_securesoho_config_browse_type browse_type);
int securesoho_browsemode_get(int* browsemode, ENUM_securesoho_config_browse_type browse_type);



extern void securesoho_mass_product_test_procedure_get(int *mass_product_test_procedure);

/*
 * The type of remote controller
 */
extern int securesoho_remote_controller_get(char *rtype);
extern void securesoho_remote_controller_set(char *rtype);

/*
 * Scart
 */
extern	int securesoho_scart_set(int mode);
extern  int securesoho_model_name_get(char *model_name);

/*
 * Content aggregation
 */
extern int securesoho_content_aggregation_get(int *scan);
extern int securesoho_content_aggregation_set(int scan);

extern int securesoho_content_aggregation_on_samba_get(int* scan);
extern int securesoho_content_aggregation_on_samba_set(int scan);

extern int securesoho_tvoutmode_get(int *piTvOutMode);
extern void securesoho_tvoutmode_set(int iTvOutMode);
extern int securesoho_tvoutres_get(int *piTvOutResolution);
extern void securesoho_tvoutres_set(int iTvOutResolution);
extern int securesoho_ntsc_pal_set(int ntsc_pal);

/*
 * slideshow effect for picture player
 */
#define CONFIG_SLIDESHOW_EFFECT_OFF     "0"
#define CONFIG_SLIDESHOW_EFFECT_FADE_IN "1"
#define CONFIG_SLIDESHOW_EFFECT_WIPE_IN "2"
#define CONFIG_SLIDESHOW_EFFECT_RANDOM  "3"
#define CONFIG_SLIDESHOW_EFFECT_WIPE_LEFT "4"
#define CONFIG_SLIDESHOW_EFFECT_WIPE_RIGHT "5"
#define CONFIG_SLIDESHOW_EFFECT_ZOOM	 "6"
#define CONFIG_SLIDESHOW_EFFECT_PUSH "7"
#define CONFIG_SLIDESHOW_EFFECT_REPLACE "8"
#define CONFIG_SLIDESHOW_EFFECT_CHECKER "9"
 
extern int securesoho_photo_slideshow_effect_get(char *slideshow_effect);
extern void securesoho_photo_slideshow_effect_set(char *slideshow_effect);

/*
 * mcx auto startup 
 */
#ifdef CONF_MCX
extern int securesoho_boot_first_get(int* is_boot_first);
extern int securesoho_boot_fist_set(int is_boot_first);
extern int securesoho_mcx_cert_partition_get(char *cert, int len);
extern int securesoho_mcx_setting_partition_get(char *path, int len);
extern int securesoho_mcx_auto_startup_get(char* autostartup);
extern void securesoho_mcx_auto_startup_set(char* autostartup);
extern int securesoho_mcx_green_btn_get(char* enable);
extern void securesoho_mcx_green_btn_set(char* enable);
extern int securesoho_is_green_button_triggered(void);
#endif
/* 
 *         tv mode atribute setting
 *
 */
#define  CONFIG_DMA_ENABLE_PAL   "CONFIG_DMA_ENABLE_PAL"
#define CONFIG_AUDIO_OUT        "AUDIO_OUT"
#define CONFIG_VIDEO_OUT        "VIDEO_OUT"
#define CONFIG_VIDEO_OUT_RES    "VIDEO_OUT_RESOLUTION"
#define CONFIG_VIDEO_PIP        "VIDEO_PIP"
#define CONFIG_TV_SCAN          "CONFIG_TV_SCAN"
#define CONFIG_SCAN_MODE        "SCAN_MODE"
#define  CONFIG_TV_TRICK        "CONFIG_TV_TRICK"
#define CONFIG_NTSC_OR_PAL	"NTSC_OR_PAL"
#define CONFIG_TV_COLOR_SPACE	"TV_COLOR_SPACE"
#define CONFIG_HDMI_DEEP_COLOR	"HDMI_DEEP_COLOR"
#define CONFIG_HDMI_AUTO_SWITCH	"HDMI_AUTO_SWITCH" /* HDMI auto native mode */
#define CONFIG_UI_DISPLAY_PERCENTAGE "UI_DISPLAY_PERCENTAGE"
/*
 * HDMI HD screen resolution 
 */ 
#define HDMI_HD_SCREEN_WIDHT_16x9  1024 
#define HDMI_HD_SCREEN_HEIGHT_16x9 576
#define HDMI_HD_SCREEN_WIDTH_4x3   768
#define HDMI_HD_SCREEN_HEIGHT_4x3  576 

#define SCREEN_WIDHT_SD_16x9	   853
#define SCREEN_HEIGHT_SD_16x9      480
#define SCREEN_WIDHT_SD_4x3        640 
#define SCREEN_HEIGHT_SD_4x3       480

#define  MSK_NTSC_PAL           0x00000001
#define  MSK_TV_SCAN            0x00000002
#define  MSK_VIDEO_OUT          0x00000004
#define  MSK_VIDEO_OUT_RES      0x00000008
#define  MSK_AUDIO_OUT          0x00000010
#define  MSK_VIDEO_PIP          0x00000020
#define  MSK_SCAN_MODE          0x00000040
#define  MSK_TRICK_MODE         0x00000080

typedef enum{
	VM_COMPOSITE = 0,
	VM_COMPONENT,
	VM_HDMI,
	VM_RGB,
	VM_RGB_SCART_INTERLACE,
	VM_RGB_SCART_PROGRESSIVE,
	VM_S_VIDEO_AV
}VIDEO_MODE;

/*
 * DO NOT CHANGE THE ORDER.
 *
 * If the order changes, the code in setup_entry_item_options.c
 * will be broken. 
 *
 * This is the ugliest fucking code I've ever seem in my life and
 * I don't have fucking time to wipe somebody's shit ass! Fuck!
 * 	-- William Chen
 */
typedef enum{
	VRM_480I60 = 0,
	VRM_480P60,
	VRM_576I50,
	VRM_576P50,
	VRM_720P50,
	VRM_720P60,
	VRM_1080I50,
	VRM_1080I60,
	VRM_AUTO,
	VRM_1080P50,
	VRM_1080P60,
	VRM_1080P24,
	VRM_1080P23,
	VRM_1080P25,
	VRM_1080P29,
	VRM_1080P30,
}VIDEO_RES_MODE;

typedef enum{
	NPM_PAL=0,
	NPM_NTSC,
}NTSC_PAL_MODE;

typedef enum{
	AOM_ANALOG=0,
	AOM_DIGITAL,
	AOM_DIGITAL_WITHOUT_HDMI_AUDIO,
	AOM_DIGITAL_HDMI_AUDIO_ONLY
}AUDIO_OUT_MODE;

typedef enum{
	VTM_FF_REV=0,
	VTM_JUMP
}VIDEO_TRICK_MODE;

typedef enum{
	VPM_NO=0,
	VPM_YES
}VIDEO_PIP_MODE;


typedef enum{
	SM_PROGRESSIVE=0,
	SM_INTERLACE
}SCAN_MODE;

typedef enum{
	VCS_AUTO=0,
	VCS_RGB_HIGH,
	VCS_RGB_LOW,
	VCS_YUV,
	VCS_YUV_FULL,
	VCS_XVYCC,
	VCS_XVYCC_FULL
}VIDEO_COLOR_SPACE;



typedef struct  _tv_av_setting_t_
{
	unsigned int set_mask;
	unsigned char ntsc_pal;
	TV_SCAN_MODE tv_scan;
	unsigned char  video_out;
	unsigned char video_out_res;
	unsigned char audio_out;
	unsigned char video_pip;
	unsigned char scan_mode;
	unsigned char trick_mode;
	unsigned char reserved[4];
}tv_av_setting_t;

void securesoho_get_tv_setting(tv_av_setting_t *tv_mode);
void securesoho_save_tv_setting(tv_av_setting_t *tv_mode);
unsigned char securesohu_init_tv_setting(void);
void securesoho_tvout_trick_get(int* tvtrickmode);
void securesoho_tvout_trick_set(int trickmode);
int securesoho_real_tvouttype_get(int *video_out, int *video_out_res);
int securesoho_real_tvouttype_set(int video_out, int video_out_res);
int securesoho_get_osd_page_info(int *width, int *height);
/*
 * get the TV mode from IrDA device
 */
int securesoho_ntsc_pal_get(int* ntsc_pal);

int backup_config(void);
int restore_config(void);

/* get device model number string */
void securesoho_get_model_magic_number(char *magic_number);

/*
 * This API is used to do factory default
 *   1) replace the config with factory default ('/conf_src/config_factory_default'->'/conf/config')
 *   2) remove wireless profile settings ('/conf/wireless_profile.xml')
 */
int securesoho_factory_default(void);

void securesoho_wcn_status_led(int ok);
int securesoho_save_cert_dir(char *i_dir, char *o_filename);

void securesoho_additional_encoding_set(const char * additional_encoding);
void securesoho_additional_encoding_get(char * additional_encoding,int len);
void securesoho_additional_encoding_get_no_cache(char * additional_encoding,int len);

#ifdef CONF_SUBTITLE_POSITION_ADJUSTMENT
void securesoho_subtitle_base_line_set(const char *subtitle_base_line);
void securesoho_subtitle_base_line_get(char *subtitle_base_line);
#endif

#ifdef CONF_SUBTITLE_CHANGE_COLOR
void securesoho_subtitle_text_color_set(const char * subtitle_text_color);
void securesoho_subtitle_text_color_get(char *subtitle_text_color);
void securesoho_subtitle_border_color_set(const char * subtitle_border_color);
void securesoho_subtitle_border_color_get(char *subtitle_border_color);
#endif

/*get/set subititle font size*/
void securesoho_subtitle_font_size_set(const char * subtitle_font_size);
void securesoho_subtitle_font_size_get(char *subtitle_font_size);
#ifdef CONF_SUBTITLE_OUTLINE_SHAPE
void securesoho_subtitle_outline_shape_set(const char * subtitle_outline_shape);
void securesoho_subtitle_outline_shape_get(char *subtitle_outline_shape);
#endif
#ifdef CONF_SUBTITLE_TURN_ON_OR_OFF_BY_DEFAULT
void securesoho_subtitle_default_on_or_off_set(const char * subtitle_default);
void securesoho_subtitle_default_on_or_off_get(char *subtitle_default);
#endif
#ifdef CONF_SETTING_HDMI_VIDEO_RESOLUTION_BY_EDID
int securesoho_set_vic_list(int *vic, int size);
int securesoho_get_vic_list(int *vic);
#endif
#ifdef CONF_TWONKYMEDIA_SERVER
void securesoho_twkyshare_set(int twkyshare_state);
int securesoho_twkyshare_get(void);
#endif //CONF_TWONKYMEDIA_SERVER
#ifdef CONF_ITUNE_SUPPORT
void securesoho_itunes_set(int twkyshare_state);
int securesoho_itunes_get(void);
#endif //CONF_ITUNE_SUPPORT
#ifdef CONF_SAMBA_SERVER
void securesoho_smbshare_set(int smbshare_state);
int securesoho_smbshare_get(void);
#endif //CONF_SAMBA_SERVER
#ifdef CONF_SAMBA_SERVER_SUPPORT_SECURITY
int securesoho_smbshare_protection_set(int smbshare_protection_state);
int securesoho_smbshare_protection_get(void);
void securesoho_smbshare_protection_username_password_set(char* username, char* password);
void securesoho_smbshare_protection_username_password_get(char* username, char* password);
#endif //CONF_SAMBA_SERVER_SUPPORT_SECURITY
#ifdef CONF_SUPPORT_SYSTEM_ACCOUNT
void securesoho_system_username_password_set(char* username, char* password);
void securesoho_system_username_password_get(char* username, char* password);
#endif //CONF_SUPPORT_SYSTEM_ACCOUNT
#ifdef CONF_DMA_BT
void securesoho_bt_set(int bt_state);
int securesoho_bt_get(void);
#endif //CONF_DMA_BT
#ifdef CONF_DMA_NZB
void securesoho_nzb_set(int nzb_state);
int securesoho_nzb_get(void);
#endif //CONF_DMA_NZB
void securesoho_device_name_set(char* device_name);
void securesoho_device_name_get(char* device_name);
void securesoho_samba_workgroup_set(char* samba_workgroup);
void securesoho_samba_workgroup_get(char* samba_workgroup);
#ifdef CONF_DMA_FLICKR
void securesoho_flickr_tag_list_get(char* tag_list);
void securesoho_flickr_tag_list_set(char* tag_list);
void securesoho_flickr_contact_list_get(char* contact_list);
void securesoho_flickr_contact_list_set(char* contact_list);
#endif //CONF_DMA_FLICKR
#ifdef CONF_NETATALK
void securesoho_afpshare_set(int afpshare_state);
int securesoho_afpshare_get(void);
#endif
#ifdef CONF_AUTO_LOGIN
void securesoho_autologin_set(int autologin_state);
int securesoho_autologin_get(void);
#endif

#ifdef CONF_QUICK_START_MODE
void securesoho_quick_start_set(int quickflag);
int securesoho_quick_start_get(int *quickflag);
#endif
#ifdef CONF_PARENTAL_CONTROL
void securesoho_parental_control_password_set(char* password);
void securesoho_parental_control_password_get(char* password);
#endif
void securesoho_proxy_state_set(int state);
int securesoho_proxy_state_get(void);
void securesoho_proxy_server_set(char* server);
void securesoho_proxy_server_get(char* server);
void securesoho_proxy_port_set(char* port);
void securesoho_proxy_port_get(char* port);


void securesoho_sync_network_share_folder_state_set(int state);
int securesoho_sync_network_share_folder_state_get(void);
void securesoho_sync_network_interval_set(int interval);
int securesoho_sync_network_interval_get(void);
void securesoho_sync_network_server_NetBIOS_name_get(char *netbios_name);
void securesoho_sync_network_server_NetBIOS_name_set(char *netbios_name);
void securesoho_sync_network_server_sharefolder_get(char *server_sharefolder);
void securesoho_sync_network_server_sharefolder_set(char *server_sharefolder);
void securesoho_sync_network_server_path_get(char *path);
void securesoho_sync_network_server_path_set(char *path);
void securesoho_sync_network_server_username_get(char *username);
void securesoho_sync_network_server_username_set(char *username);
void securesoho_sync_network_server_password_get(char *password);
void securesoho_sync_network_server_password_set(char *password);

void securesoho_UPNP_DEVICE_MODEL_NUM_get(char* modelNumber, int size);

#ifdef CONF_SHOW_FILESIZE
void securesoho_showfilesize_set(int showfilesize);  
int securesoho_showfilesize_get(int *showfilesize);  
#endif //CONF_SHOW_FILESIZE

void securesoho_timezone_set(char *timezone);
void securesoho_timezone_get(char *timezone);
void securesoho_daylight_set(int daylight);
void securesoho_daylight_get(int *daylight);
void securesoho_metric_set(int metric);
void securesoho_metric_get(int *metric);

#ifdef CONF_ENABLE_FADING_UI_EFFECT
void securesoho_enable_fading_effect_set(int enable_fading_effect);  
int securesoho_enable_fading_effect_get(int *enable_fading_effect);  
#endif //CONF_ENABLE_FADING_UI_EFFECT

#ifdef CONF_SUPPORT_LOCAL_SYNC
void securesoho_transfer_sync_set(int state);
int securesoho_transfer_sync_get(void);
#endif //CONF_SUPPORT_LOCAL_SYNC

#ifdef CONF_OSD_ENABLE_SLIDESHOW_SCREENSAVER
void securesoho_slideshow_screensaver_set(int state);
int securesoho_slideshow_screensaver_get(void);
#endif //CONF_OSD_ENABLE_SLIDESHOW_SCREENSAVER

void securesoho_dashboard_last_accessed_item_set(int item);
int securesoho_dashboard_last_accessed_item_get(void);

/* hidden page settings */
int securesoho_dev_firmware_set(int enable);
int securesoho_dev_firmware_get();
int securesoho_pandora_dev_server_set(int enable);
int securesoho_pandora_dev_server_get();
int securesoho_premium_content_set(int enable);
int securesoho_premium_content_get();



/* auto get content info */
void securesoho_auto_get_content_info_set(int enable);
int securesoho_auto_get_content_info_get(void);

#endif //__SECURESOHO_CONFIG_H__
