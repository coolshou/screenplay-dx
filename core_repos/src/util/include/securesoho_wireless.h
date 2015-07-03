/* 
 * Copyright (C) 2006, Alphanetworks, inc.
 * Author: wills_yin@alphanetworks.com 
 * vim:cindent:ts=8:sw=8
 */
#ifndef __SECURESOHO_WIRELESS_H__
#define __SECURESOHO_WIRELESS_H__

#include "external_util_path.h"

#define RTPRIV_IOCTL_SET	(SIOCIWFIRSTPRIV + 0x02)
#define RTPRIV_IOCTL_SHOW	(SIOCIWFIRSTPRIV + 0x11)

#define IW_MAX_PRIV_DEF	160
/* Some usefull constants */
#define KILO	1e3
#define MEGA	1e6
#define GIGA	1e9
/* For doing log10/exp10 without libm */
#define LOG10_MAGIC	1.25892541179

#define SSID_MAX_WPA_IE_LEN 	40
#define GENERIC_INFO_ELEM 	0xdd
#define RSN_INFO_ELEM 		0x30

/* ------------------------- PRIVATE INFO ------------------------- */
/*
 * The following is used with SIOCGIWPRIV. It allow a driver to define
 * the interface (name, type of data) for its private ioctl.
 * Privates ioctl are SIOCIWFIRSTPRIV -> SIOCIWLASTPRIV
 */

#define IW_PRIV_TYPE_MASK	0x7000	/* Type of arguments */
#define IW_PRIV_TYPE_NONE	0x0000
#define IW_PRIV_TYPE_BYTE	0x1000	/* Char as number */
#define IW_PRIV_TYPE_CHAR	0x2000	/* Char as character */
#define IW_PRIV_TYPE_INT	0x4000	/* 32 bits int */
#define IW_PRIV_TYPE_FLOAT	0x5000	/* struct iw_freq */
#define IW_PRIV_TYPE_ADDR	0x6000	/* struct sockaddr */

#define IW_PRIV_SIZE_FIXED	0x0800	/* Variable or fixed number of args */

#define IW_PRIV_SIZE_MASK	0x07FF	/* Max number of those args */

/**
 *    WEP validation funtion return value
 */

#define WEP_OK   0
#define WEP_INVALID_WEP		1
#define WEP_INVALID_WPAPSK	2
#define WEP_INVALID_CHARACTER	3
#define WEP_INVALID_64HEX	4
#define WEP_INVALID_128HEX	5
#define WEP_INVALID_64ASCII	6
#define WEP_INVALID_128ASCII	7

#define	WIRELESS_ENCRYPT_GTK_KEY		0x0
#define	WIRELESS_ENCRYPT_PTK_KEY		0x1
#define WIRELESS_ENCRYPT_WPA_PSK		0x0020
#define WIRELESS_ENCRYPT_WPA2_PSK		0x0040

#define WIRELESS_ENCRYPT_WPAPSK_GTK_TKIP	0x0080
#define WIRELESS_ENCRYPT_WPAPSK_GTK_CCMP	0x0100
#define WIRELESS_ENCRYPT_WPAPSK_PTK_TKIP	0x0200
#define WIRELESS_ENCRYPT_WPAPSK_PTK_CCMP 	0x0400
#define WIRELESS_ENCRYPT_WPAPSK_GTK_WEP40	0x0800
#define WIRELESS_ENCRYPT_WPAPSK_GTK_WEP104	0x1000
#define WIRELESS_ENCRYPT_WPAPSK_PTK_WEP40	0x2000
#define WIRELESS_ENCRYPT_WPAPSK_PTK_WEP104	0x4000

#define WIRELESS_ENCRYPT_WPA2PSK_GTK_TKIP	0x8000
#define WIRELESS_ENCRYPT_WPA2PSK_GTK_CCMP 	0x10000
#define WIRELESS_ENCRYPT_WPA2PSK_PTK_TKIP 	0x20000
#define WIRELESS_ENCRYPT_WPA2PSK_PTK_CCMP 	0x40000
#define WIRELESS_ENCRYPT_WPA2PSK_GTK_WEP40	0x80000
#define WIRELESS_ENCRYPT_WPA2PSK_GTK_WEP104	0x100000
#define WIRELESS_ENCRYPT_WPA2PSK_PTK_WEP40	0x200000
#define WIRELESS_ENCRYPT_WPA2PSK_PTK_WEP104	0x400000

#define WIRELESS_ENCRYPT_NONE			0
#define WIRELESS_ENCRYPT_WEP			1
#define WIRELESS_ENCRYPT_WPAPSK_TKIP		2
#define WIRELESS_ENCRYPT_WPAPSK_AES		4
#define WIRELESS_ENCRYPT_WPAPSK_TKIPAES		8
#define WIRELESS_ENCRYPT_WPA2PSK_TKIP		16
#define WIRELESS_ENCRYPT_WPA2PSK_AES		32
#define WIRELESS_ENCRYPT_WPA2PSK_TKIPAES	64
#define WIRELESS_ENCRYPT_WPS_PBC		128
#define WIRELESS_ENCRYPT_WPS_PIN		256

#define WIRELESS_SITESURVEY_CACHE_NUM		5

/* Wireless AP type */
#define WIRELESS_AP_TYPE_11B			1
#define WIRELESS_AP_TYPE_11G			2
#define WIRELESS_AP_TYPE_11A			4
#define WIRELESS_AP_TYPE_11N			8
	
/* Wireless WEP encrypt level */
#define WIRELESS_WEP_ENCRYPT_LEVEL_DISABLE	0   
#define WIRELESS_WEP_ENCRYPT_LEVEL_64_HEX	1
#define WIRELESS_WEP_ENCRYPT_LEVEL_128_HEX	2
#define WIRELESS_WEP_ENCRYPT_LEVEL_64_ASCII	3
#define WIRELESS_WEP_ENCRYPT_LEVEL_128_ASCII	4

/* Wireless status type */
#define	WIRELESS_STATUS_WPS_PBC			1
#define	WIRELESS_STATUS_WPS_PIN			2

typedef enum{
	WIRELESS_ADHOC = 0,
	WIRELESS_INFRASTRUCTURE = 1,
	WIRELESS_MASTER = 2,
	WIRELESS_REPEATER = 3,
	WIRELESS_SECONDARY = 4,
	WIRELESS_MONITOR = 5,
	WIRELESS_AUTO = 6,
	WIRELESS_BOTH = 7	/* It's means Ad-Hoc and Infrastrcture */
}WIRELESS_MODE;

typedef struct {
	WIRELESS_MODE mode;
	char         ssid[33];
	int          channel;
	int	     wireless_type; //1 for 11bg, 2 for 11a, 4 for 11n
	int          security_method; /* 0x00:Disable, 0x01:WEP, 0x02: WPA-PSK */
	int          encrypt_mode; /* 1: TKIP, 2: WEP */
	int          wep_encrypt_level; /* 0: Disable, 1:64bit-Hex, 2:128bit-Hex, 3:64bit-Ascii, 4:128bit-Ascii */
	int          wep_key_index;
	char         wep_hexkey[4][27];
	char         wep_asciikey[4][16];
	char         wpa_psk[65]; // Kanuka, 2004/12/2
} SecureSOHO_Wireless;

struct usb_id_s {
	unsigned int idVendor;
	unsigned int idProduct;
};

struct wireless_driver_ops {
	/**
	 * vender name
	 */
	const char *wlan_vendor;
	
	/**
	 * chip id
	 */
	const char *wlan_chip_id;
	
	/**
	 * usb_dongle - usb interface
	 */
	int wlan_usb_dongle;

	/**
	 * address - address of mini pci card. Or vid and pid list of usb dongle
	 */
	struct usb_id_s *wlan_addr;

	/**
	 * id - vid and pid of usb dongle
	 */
	struct usb_id_s wlan_id;

	/**
	 * devpath - USB device path
	 */
	char wlan_devpath[255];

	/**
	 * interface name
	 */
	char wlan_name[16];
	
	/**
	 * delay time after send scan command
	 */
	const int wlan_scan_delay;
	
	/**
	 * associate value 
	 */
	const int wlan_associated;
	
	/**
	 * associate value 
	 */
	int wlan_enc_supported;
	
	/**
	 * support wps
	 */
	int wlan_wps_supported;
	
	/**
	 * link up time
	 */
	int wlan_linkup_time;

	/**
	 * link down time
	 */
	int wlan_linkdown_time;

	/**
	 * link status
	 */
	int wlan_linkstatus;

	/**
	 * User Data for scan completed call back function
	 */
	void *wlan_user_data;

	/**
	 * 
	 */
	int wlan_wpa_ie_offset;

	/**
	 * 
	 */
	int wlan_rsn_ie_offset;

	/**
	 * Wireless driver support scan completed event or not.
	 */
	int wlan_scan_event;
	
	/**
	 * socket for ioctl
	 */
	int wlan_skfd;

	/**
	 * index for wireless profile
	 */
	int profile_index;
	
	/**
	 * wireless status control
	 * 1: Running WPS connection
	 * 2: Restart wireless connection
	 */
	unsigned int wlan_status;
	
	/**
	 * driver name of wpa_supplicant
	 */
	const char *wlan_wpa_supplicant_drv;
	
	/**
	 * site survey completed call back function
	 */
	void (*wlan_scan_completed_cb)(void (*cb)(void *UserData));

	/**
	 * insert - insert driver
	 */
	int (*wlan_insert)(struct wireless_driver_ops *wlan);

	/**
	 * remove - remove driver
	 */
	void (*wlan_remove)(struct wireless_driver_ops *wlan);

	/**
	 * down - ifconfig down driver
	 */
	void (*wlan_down)(struct wireless_driver_ops *wlan);

	/**
	 * init - initialize driver interface
	 */
	void (*wlan_init)(struct wireless_driver_ops *wlan);

	/**
	 * reset - down then up wireless interface
	 */
	void (*wlan_reset)(struct wireless_driver_ops *wlan);

	/**
	 * scan - request the driver to initiate scan
	 * @priv: private driver interface data
	 * @ssid: specific SSID to scan for (ProbeReq) or %NULL to scan for
	 *	all SSIDs (either active scan with broadcast SSID or passive
	 *	scan
	 * @ssid_len: length of the SSID
	 *
	 * Return: 0 on success, -1 on failure
	 *
	 * Once the scan results are ready, the driver should report scan
	 * results event for wpa_supplicant which will eventually request the
	 * results with wpa_driver_get_scan_results().
	 */
	int (*wlan_scan)(struct wireless_driver_ops *wlan, const char *ssid, int ssid_len);

	/**
	 * Making assocate with Access Point according config settings
	 *
	 * Return: 0 on success, -1 on failure
	 */
	int (*wlan_do_assocate)(struct wireless_driver_ops *wlan);

	/**
	 * get link status
	 * @status: store wireless status
	 *
	 * Return: 0 on success, -1 on failure
	 */
	int (*wlan_get_status)(struct wireless_driver_ops *wlan, int *ststus);
	
	/**
	 * get link signal strength
	 * @signal: link signal strength with access point
	 *
	 * Return: 0 on success, -1 on failure
	 */
	int (*wlan_get_signal_strength)(struct wireless_driver_ops *wlan, int *signal);

	/**
	 * get_scan_results - fetch the latest scan results
	 * @priv: private driver interface data
	 * @results: pointer to buffer for scan results
	 * @max_size: maximum number of entries (buffer size)
	 *
	 * Return: number of scan result entries used on success, -1 on failure
	 *
	 * If scan results include more than @max_size BSSes, @max_size will be
	 * returned and the remaining entries will not be included in the
	 * buffer.
	 */
	struct SITE_OBJ *(*wlan_get_scan_results)(struct wireless_driver_ops *wlan, int *cnt, WIRELESS_MODE mode);

	/**
	 * link up - set link status and assocated time.
	 */
	void (*wlan_linkup)(struct wireless_driver_ops *wlan);

	/**
	 * link down - set link status.
	 */
	void (*wlan_linkdown)(struct wireless_driver_ops *wlan);

	/**
	 * site survey completed
	 */
	void (*wlan_scan_completed)(struct wireless_driver_ops *wlan);

	/**
	 * Set site survey completed call back function
	 */
	void (*wlan_set_scan_completed_cb)(struct wireless_driver_ops *wlan, void (*cb)(void *UserData), void *UserData);

	/**
	 * In WPS Enrollee mode, get 8 digitals pin code from application of wireless station.
	 * Note: The buffer length of pin code must greater then 8.
	 */
	int (*wlan_wps_pin_enrollee_get_code)(struct wireless_driver_ops *wlan, char *code, int len);

	struct wireless_driver_ops *next;
};

typedef enum _site_sort_type_e{
	SITE_SORT_TYPE_SSID=0,
	SITE_SORT_TYPE_SIGNAL,
	SITE_SORT_TYPE_SPEED,
	SITE_SORT_TYPE_BAND,
	SITE_SORT_TYPE_SECURITY
}SITE_SORT_TYPE_E;

typedef enum {
	INTERSIL = 0,
	RALINK = 1,
	ATHEROS = 2,		/* add for atheros yangzheng 2006/04/30 */
} WIRELESS_CARD_TYPE;

struct SITE_OBJ {
	char essid[33];
	char bssid[18];
	int channel;
	int signal_dbm;
	int signal_percentage;
	int crypt;
	int wpa;
	WIRELESS_MODE mode;
        int wireless_type; //0 for 11bg, 1 for 11a
	struct SITE_OBJ *next;
	char wpa_ie[81];
	char rsn_ie[81];
};

struct SWAP_OBJ {
	struct SITE_OBJ *site_head, *site1, *site2;
};

extern void reset_wireless(void);
extern void securesoho_site_survey_init(void);
extern void securesoho_site_survey_start(void);
extern void securesoho_site_survey_end(void);
extern struct SITE_OBJ *securesoho_site_survey(int *cnt, WIRELESS_MODE mode);
extern void securesoho_free_site_obj(struct SITE_OBJ *object);
void securesoho_dump_site_obj(struct SITE_OBJ *site);

/* Check ssid. return 1 1 if is an invalidate value otherwise return 0*/
extern int invalidate_ssid(const char *ssid);
/* Check WEP key. retrun 1 if is an invalidate value otherwise return 0*/
extern int invalidate_wep_key(const char *key, int crypt_bit);
/* Detect wireless card plug */
void securesoho_detect_wireless_card(void);
struct wireless_driver_ops *securesoho_get_wireless_card(void);
int securesoho_is_wireless_card_dummy(void);
int securesoho_is_wireless_available(void);
int securesoho_wireless_plug(void);
int set_private(int skfd, char *ifname, char *cmdname, void **ret, int count, void *args[]);
struct SITE_OBJ *sort_site(struct SITE_OBJ *site, SITE_SORT_TYPE_E sort_type);
struct SITE_OBJ **get_arSiteObj(void);
int dbm2percentage(int dbm);
int securesoho_dongle_callback(int vid, int pid, int available, char *devpath);
int get_associated_essid_info(int skfd, char *ifname, char *essid);
int check_associated_ap_address(int skfd, char *ifname);
int securesoho_is_wireless_dongle_available(void);
#endif				//__SECURESOHO_WIRELESS_H__
