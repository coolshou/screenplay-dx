#ifndef OTUS_COMMON_H
#define OTUS_COMMON_H

#define ZD_IOCTL_WPA			(SIOCDEVPRIVATE + 1)
#define ZD_IOCTL_PARAM			(SIOCDEVPRIVATE + 2)
#define ZD_IOCTL_GETWPAIE		(SIOCDEVPRIVATE + 3)
#define ZD_PARAM_ROAMING		0x0001
#define ZD_PARAM_PRIVACY		0x0002
#define ZD_PARAM_WPA			0x0003
#define ZD_PARAM_COUNTERMEASURES	0x0004
#define ZD_PARAM_DROPUNENCRYPTED	0x0005
#define ZD_PARAM_AUTH_ALGS		0x0006
#define ZD_PARAM_WPS_FILTER             0x0007
                                                                                                                                                                
#define ZD_CMD_SET_ENCRYPT_KEY		0x0001
#define ZD_CMD_SET_MLME			0x0002
#define ZD_CMD_SCAN_REQ			0x0003
#define ZD_CMD_SET_GENERIC_ELEMENT	0x0004
#define ZD_CMD_GET_TSC			0x0005

#define ZD_FLAG_SET_TX_KEY              0x0001

#define ZD_GENERIC_ELEMENT_HDR_LEN \
((int) (&((struct otus_wlan_param *) 0)->u.generic_elem.data))

#define ZD_CRYPT_ALG_NAME_LEN		16
#define ZD_MAX_KEY_SIZE			32
#define ZD_MAX_GENERIC_SIZE		64

#define IEEE80211_ADDR_LEN		6
#define IEEE80211_MAX_IE_SIZE		256

#define IEEE80211_FC0_SUBTYPE_MASK      0xf0

/* for TYPE_MGT */
#define IEEE80211_FC0_SUBTYPE_ASSOC_REQ         0x00
#define IEEE80211_FC0_SUBTYPE_ASSOC_RESP        0x10
#define IEEE80211_FC0_SUBTYPE_REASSOC_REQ       0x20
#define IEEE80211_FC0_SUBTYPE_REASSOC_RESP      0x30
#define IEEE80211_FC0_SUBTYPE_PROBE_REQ         0x40
#define IEEE80211_FC0_SUBTYPE_PROBE_RESP        0x50
#define IEEE80211_FC0_SUBTYPE_BEACON            0x80
#define IEEE80211_FC0_SUBTYPE_ATIM              0x90
#define IEEE80211_FC0_SUBTYPE_DISASSOC          0xa0
#define IEEE80211_FC0_SUBTYPE_AUTH              0xb0
#define IEEE80211_FC0_SUBTYPE_DEAUTH            0xc0
#define IEEE80211_FC0_SUBTYPE_ACTION            0xd0

enum {
        IEEE80211_ELEMID_SSID           = 0,
        IEEE80211_ELEMID_RATES          = 1,
        IEEE80211_ELEMID_FHPARMS        = 2,
        IEEE80211_ELEMID_DSPARMS        = 3,
        IEEE80211_ELEMID_CFPARMS        = 4,
        IEEE80211_ELEMID_TIM            = 5,
        IEEE80211_ELEMID_IBSSPARMS      = 6,
        IEEE80211_ELEMID_COUNTRY        = 7,
        IEEE80211_ELEMID_REQINFO        = 10,
        IEEE80211_ELEMID_CHALLENGE      = 16,
        /* 17-31 reserved for challenge text extension */
        IEEE80211_ELEMID_PWRCNSTR       = 32,
        IEEE80211_ELEMID_PWRCAP         = 33,
        IEEE80211_ELEMID_TPCREQ         = 34,
        IEEE80211_ELEMID_TPCREP         = 35,
        IEEE80211_ELEMID_SUPPCHAN       = 36,
        IEEE80211_ELEMID_CHANSWITCHANN  = 37,
        IEEE80211_ELEMID_MEASREQ        = 38,
        IEEE80211_ELEMID_MEASREP        = 39,
        IEEE80211_ELEMID_QUIET          = 40,
        IEEE80211_ELEMID_IBSSDFS        = 41,
        IEEE80211_ELEMID_ERP            = 42,
        IEEE80211_ELEMID_RSN            = 48,
        IEEE80211_ELEMID_XRATES         = 50,
        /* 128-129 proprietary elements used by Agere chipsets */
        IEEE80211_ELEMID_AGERE1         = 128,
        IEEE80211_ELEMID_AGERE2         = 129,
        IEEE80211_ELEMID_TPC            = 150,
        IEEE80211_ELEMID_CCKM           = 156,
        IEEE80211_ELEMID_VENDOR         = 221,  /* vendor private */
};

/* structure definition */

struct otus_wlan_param {
	u32 cmd;
	u8 sta_addr[ETH_ALEN];
	union {
		struct {
			u8 alg[ZD_CRYPT_ALG_NAME_LEN];
			u32 flags;
			u32 err;
			u8 idx;
			u8 seq[8]; /* sequence counter (set: RX, get: TX) */
			u16 key_len;
			u8 key[ZD_MAX_KEY_SIZE];
		} crypt;
		struct {
			u32 flags_and;
			u32 flags_or;
		} set_flags_sta;
		struct {
			u8 len;
			u8 data[ZD_MAX_GENERIC_SIZE];
		} generic_elem;
		struct {
#define MLME_STA_DEAUTH 0
#define MLME_STA_DISASSOC 1
			u16 cmd;
			u16 reason_code;
		} mlme;
		struct {
			u8 ssid_len;
			u8 ssid[32];
		} scan_req;
	} u;
};

struct ieee80211req_wpaie {
	u8 wpa_macaddr[IEEE80211_ADDR_LEN];
	u8 wpa_ie[IEEE80211_MAX_IE_SIZE];
};

/*
 * generic definitions for IEEE 802.11 frames
 */
struct ieee80211_frame {
        u_int8_t i_fc[2];
        u_int16_t i_dur;
        u_int8_t i_addr1[IEEE80211_ADDR_LEN];
        u_int8_t i_addr2[IEEE80211_ADDR_LEN];
        u_int8_t i_addr3[IEEE80211_ADDR_LEN];
        u_int8_t i_seq[2];
        /* possibly followed by addr4[IEEE80211_ADDR_LEN]; */
        /* see below */
} __packed;

#endif

