/*
 * WPA Supplicant - driver interaction with Otus 802.11 driver
 * Copyright (c) 2007 Atheros Communication Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README and COPYING for more details.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <errno.h>

#include "common.h"
#include "driver.h"
#include "driver_wext.h"
#include "eloop.h"
#include "wpa_supplicant.h"
#include "wpa.h"

#include "otus_common.h"

#include <net/if_arp.h>
#include <linux/wireless.h>

#include "l2_packet.h"

struct wpa_driver_otus_data {
	void *wext; /* private data for driver_wext */
	void *ctx;
	char ifname[IFNAMSIZ + 1];
	int sock;
	struct l2_packet_data * l2_sock;
};

static int otus_ioctl(struct wpa_driver_otus_data *drv, struct otus_wlan_param *param,
			 int len, int show_err)
{
	int s;
	struct iwreq iwr;

	s = socket(PF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		perror("socket");
		return -1;
	}
	memset(&iwr, 0, sizeof(iwr));
	strncpy(iwr.ifr_name, drv->ifname, IFNAMSIZ);
	iwr.u.data.pointer = (caddr_t) param;
	iwr.u.data.length = len;

	if (ioctl(s, ZD_IOCTL_WPA, &iwr) < 0) {
		int ret;
		close(s);
		ret = errno;
		if (show_err) 
			perror("ioctl[ZD_IOCTL_WPA]");
		return ret;
	}
	close(s);

	return 0;
}

static int
otus_set_param(struct wpa_driver_otus_data *drv, int op, int arg, int show_err)
{
	struct iwreq iwr;
	int *i, s, ret = 0;

	s = socket(PF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		perror("socket[PF_INET,SOCK_DGRAM]");
		return -1;
	}

	memset(&iwr, 0, sizeof(iwr));
	strncpy(iwr.ifr_name, drv->ifname, IFNAMSIZ);
	i = (int *) iwr.u.name;
	*i++ = op;
	*i++ = arg;

	if (ioctl(s, ZD_IOCTL_PARAM, &iwr) < 0) {
		perror("ioctl[ZD_IOCTL_PARAM]");
		ret = -1;
	}
	close(s);

	return ret;
}

#if 0
static int
getifflags(const char *ifname, int *flags)
{
	struct ifreq ifr;
	int s;

	s = socket(PF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		perror("socket");
		return -1;
	}

	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, ifname, sizeof (ifr.ifr_name));
	if (ioctl(s, SIOCGIFFLAGS, (caddr_t)&ifr) < 0) {
		perror("SIOCGIFFLAGS");
		return errno;
	}
	*flags = ifr.ifr_flags & 0xffff;
	return 0;
}

static int
setifflags(const char *ifname, int flags)
{
	struct ifreq ifr;
	int s;

	s = socket(PF_INET, SOCK_DGRAM, 0);
	if (s < 0) {
		perror("socket");
		return -1;
	}

	memset(&ifr, 0, sizeof(ifr));
	strncpy(ifr.ifr_name, ifname, sizeof (ifr.ifr_name));
	ifr.ifr_flags = flags & 0xffff;
	if (ioctl(s, SIOCSIFFLAGS, (caddr_t)&ifr) < 0) {
		perror("SIOCSIFFLAGS");
		return errno;
	}
	return 0;
}
#endif

static int
wpa_driver_otus_set_wpa_ie(struct wpa_driver_otus_data *drv,
	const char *wpa_ie, size_t wpa_ie_len)
{
	struct otus_wlan_param *param;
	int res;
	size_t blen = ZD_GENERIC_ELEMENT_HDR_LEN + wpa_ie_len;
	if (blen < sizeof(*param))
		blen = sizeof(*param);

	param = (struct otus_wlan_param *) malloc(blen);
	if (param == NULL)
		return -1;

	memset(param, 0, blen);
	param->cmd = ZD_CMD_SET_GENERIC_ELEMENT;
	param->u.generic_elem.len = wpa_ie_len;
	memcpy(param->u.generic_elem.data, wpa_ie, wpa_ie_len);
	res = otus_ioctl(drv, param, blen, 1);

	free(param);

	return res;
}

#if 0
static int
wpa_driver_otus_set_wpa(void *priv, int enabled)
{
	struct wpa_driver_otus_data *drv = priv;
	int ret = 0;

	wpa_printf(MSG_DEBUG, "%s: enabled=%d", __FUNCTION__, enabled);

	if (!enabled && wpa_driver_otus_set_wpa_ie(drv, NULL, 0) < 0)
		ret = -1;
	if (otus_set_param(drv, ZD_PARAM_ROAMING, enabled, 1) < 0)
		ret = -1;
	if (otus_set_param(drv, ZD_PARAM_PRIVACY, enabled, 1) < 0)
		ret = -1;
	if (otus_set_param(drv, ZD_PARAM_WPA, enabled, 1) < 0)
		ret = -1;

	return ret;
}
#endif

static int
wpa_driver_otus_set_key(void *priv, wpa_alg alg,
				     const u8 *addr, int key_idx, int set_tx,
				     const u8 *seq, size_t seq_len,
				     const u8 *key, size_t key_len)
{
	struct wpa_driver_otus_data *drv = priv;
	struct otus_wlan_param *param;
	u8 *buf;
	size_t blen;
	int ret = 0;
	char *alg_name;

	switch (alg) {
		case WPA_ALG_NONE:
			alg_name = "NONE";
			break;
		case WPA_ALG_WEP:
			alg_name = "WEP";
			break;
		case WPA_ALG_TKIP:
			alg_name = "TKIP";
			break;
		case WPA_ALG_CCMP:
			alg_name = "CCMP";
			break;
		default:
			return -1;
	}

	wpa_printf(MSG_DEBUG, "%s: alg=%s key_idx=%d set_tx=%d seq_len=%d "
		   "key_len=%d", __FUNCTION__, alg_name, key_idx, set_tx,
		   seq_len, key_len);

	if (seq_len > 8)
		return -2;

	blen = sizeof(*param) + key_len;
	buf = malloc(blen);
	if (buf == NULL)
		return -1;
	memset(buf, 0, blen);

	param = (struct otus_wlan_param *) buf;
	param->cmd = ZD_CMD_SET_ENCRYPT_KEY;
	/* TODO: In theory, STA in client mode can use five keys; four default
	 * keys for receiving (with keyidx 0..3) and one individual key for
	 * both transmitting and receiving (keyidx 0) _unicast_ packets. Now,
	 * keyidx 0 is reserved for this unicast use and default keys can only
	 * use keyidx 1..3 (i.e., default key with keyidx 0 is not supported).
	 * This should be fine for more or less all cases, but for completeness
	 * sake, the driver could be enhanced to support the missing key. */
#if 1
	if (addr == NULL)
		memset(param->sta_addr, 0xff, ETH_ALEN);
	else
		memcpy(param->sta_addr, addr, ETH_ALEN);
#else
	if (addr != NULL)
		memcpy(param->sta_addr, addr, ETH_ALEN);
#endif

	strncpy((char *)param->u.crypt.alg, alg_name, ZD_CRYPT_ALG_NAME_LEN);
	param->u.crypt.flags = set_tx ? ZD_FLAG_SET_TX_KEY : 0;
	param->u.crypt.idx = key_idx;
	memcpy(param->u.crypt.seq, seq, seq_len);
	param->u.crypt.key_len = key_len;
	memcpy((u8 *) param->u.crypt.key, key, key_len);

	/* Dump key context */
#if 0
	if(alg != WPA_ALG_NONE) {
		int ii;

		wpa_printf(MSG_DEBUG, "Key Context:");
		for(ii = 0; ii < key_len; ) {
			printf("0x%02x ", key[ii]);

			if((++ii % 16) == 0)
				printf("\n");
		}

		printf("\n");
	}
#endif
	if (otus_ioctl(drv, param, blen, 1)) {
		wpa_printf(MSG_WARNING, "Failed to set encryption.");
		//show_set_key_error(param);
		ret = -1;
	}
	free(buf);

	return ret;
}

static int
wpa_driver_otus_set_countermeasures(void *priv, int enabled)
{
	struct wpa_driver_otus_data *drv = priv;

	/* Enable the countermeasure */
	wpa_printf(MSG_DEBUG, "%s: enabled=%d", __FUNCTION__, enabled);
	return otus_set_param(drv, ZD_PARAM_COUNTERMEASURES, enabled, 1);
}

static int
wpa_driver_otus_set_drop_unencrypted(void *priv, int enabled)
{
	struct wpa_driver_otus_data *drv = priv;
	/* Enable the countermeasure */
	wpa_printf(MSG_DEBUG, "%s: enabled=%d", __FUNCTION__, enabled);
	return otus_set_param(drv, ZD_PARAM_DROPUNENCRYPTED, enabled, 1);
}

static int
wpa_driver_otus_deauthenticate(void *priv, const u8 *addr, int reason_code)
{
	struct wpa_driver_otus_data *drv = priv;
	struct otus_wlan_param *param;
	int blen;
        int ret;

	blen = sizeof(*param);
	param = (struct otus_wlan_param *) malloc(blen);
	if (param == NULL)
		return -1;

	memset(param, 0, blen);
	param->cmd = ZD_CMD_SET_MLME;
	param->u.mlme.cmd = MLME_STA_DEAUTH;
	param->u.mlme.reason_code = reason_code;
	memcpy(param->sta_addr, addr, ETH_ALEN);
	ret = otus_ioctl(drv, param, blen, 1);
        usleep(100000);
        free(param);
        return ret;
}

static int
wpa_driver_otus_disassociate(void *priv, const u8 *addr, int reason_code)
{
	struct wpa_driver_otus_data *drv = priv;
	struct otus_wlan_param *param;
	int blen;
        int ret;

	blen = sizeof(*param);
	param = (struct otus_wlan_param *) malloc(blen);
	if (param == NULL)
		return -1;

	memset(param, 0, blen);
	param->cmd = ZD_CMD_SET_MLME;
	param->u.mlme.cmd = MLME_STA_DISASSOC;
	param->u.mlme.reason_code = reason_code;
	memcpy(param->sta_addr, addr, ETH_ALEN);
	ret = otus_ioctl(drv, param, blen, 1);
        free(param);
        return ret;
}

static int
wpa_driver_otus_associate(void *priv,
			     struct wpa_driver_associate_params *params)
/*static int
wpa_driver_otus_associate(const char *ifname, const char *bssid,
				       const char *ssid, size_t ssid_len,
				       int freq,
				       const char *wpa_ie, size_t wpa_ie_len,
				       wpa_cipher pairwise_suite,
				       wpa_cipher group_suite,
				       wpa_key_mgmt key_mgmt_suite)*/
{
	struct wpa_driver_otus_data *drv = priv;

	int ret = 0, privacy=1;

	wpa_printf(MSG_DEBUG, "%s", __FUNCTION__);

	/* Because there might be the case, two or more APs with the same
	 * SSID, in order to identify them, we need to set the BSSID. */
 	if (wpa_driver_otus_set_wpa_ie(drv, (char *)params->wpa_ie, params->wpa_ie_len) < 0)
		ret = -1;
	
	if (params->pairwise_suite == CIPHER_NONE &&
	    params->group_suite == CIPHER_NONE &&
	    params->key_mgmt_suite == KEY_MGMT_NONE &&
	    params->wpa_ie_len == 0)
		privacy = 0;

	if (otus_set_param(drv, ZD_PARAM_PRIVACY, privacy, 1) < 0)
		ret = -1;

	if (params->wpa_ie_len &&
	    otus_set_param(drv, ZD_PARAM_WPA,
			  params->wpa_ie[0] == RSN_INFO_ELEM ? 2 : 1, 1) < 0)
		ret = -1;

	if (params->bssid == NULL) {
		/* ap_scan=0 or 2 mode - driver takes care of AP selection and
		 * roaming */
		/* FIX: this does not seem to work; would probably need to
		 * change something in the driver */
		if (otus_set_param(drv, ZD_PARAM_ROAMING, 0, 1) < 0)
			ret = -1;
	//	if (wpa_driver_wext_set_ssid(drv->wext, params->ssid, params->ssid_len) < 0)
	//		ret = -1;
	}

	if (wpa_driver_wext_set_ssid(drv->wext, params->ssid, params->ssid_len) < 0)
		ret = -1;

	// Mark for test
	//if (wpa_driver_wext_set_bssid(ifname, bssid) < 0)
	//	ret = -1;
	if (params->bssid)
	{
		wpa_printf(MSG_DEBUG, "wpa_supplicant initiates scan and AP selection\n");
		if (otus_set_param(drv, ZD_PARAM_ROAMING, 1, 1) < 0)
			ret = -1;
		if (wpa_driver_wext_set_bssid(drv->wext, params->bssid) < 0)
			ret = -1;
	}
			

#if 0
	/* Allow unencrypted EAPOL messages even if pairwise keys are set when
	 * not using WPA. IEEE 802.1X specifies that these frames are not
	 * encrypted, but WPA encrypts them when pairwise keys are in use. */
	if (key_mgmt_suite == KEY_MGMT_802_1X ||
	    key_mgmt_suite == KEY_MGMT_PSK)
		allow_unencrypted_eapol = 0;
	else
		allow_unencrypted_eapol = 1;
	
	if (prism2param(ifname, PRISM2_PARAM_IEEE_802_1X,
			allow_unencrypted_eapol) < 0) {
		wpa_printf(MSG_DEBUG, "hostap: Failed to configure "
			   "ieee_802_1x param");
		/* Ignore this error.. driver_hostap.c can also be used with
		 * other drivers that do not support this prism2_param. */
	}
#endif

	return ret;
}

static int
wpa_driver_otus_scan(void *priv, const u8 *ssid, size_t ssid_len)
{
	struct wpa_driver_otus_data *drv=priv;
	struct otus_wlan_param param;
	int ret;

	if (ssid == NULL) {
		/* Use standard Linux Wireless Extensions ioctl if possible
		 * because some drivers using hostap code in wpa_supplicant
		 * might not support Host AP specific scan request (with SSID
		 * info). */
		return wpa_driver_wext_scan(drv->wext, ssid, ssid_len);
	}

	if (ssid_len > 32)
		ssid_len = 32;

	memset(&param, 0, sizeof(param));
	param.cmd = ZD_CMD_SCAN_REQ;
	param.u.scan_req.ssid_len = ssid_len;
	memcpy(param.u.scan_req.ssid, ssid, ssid_len);
	ret = otus_ioctl(drv, &param, sizeof(param), 1);

	/* Not all drivers generate "scan completed" wireless event, so try to
	 * read results after a timeout. */
	eloop_register_timeout(3, 0, wpa_driver_wext_scan_timeout, NULL, drv->ctx);

	return ret;
}

static int wpa_driver_otus_set_auth_alg(void *priv, int auth_alg)
{
	struct wpa_driver_otus_data *drv=priv;
	int algs = 0;

	if (auth_alg & AUTH_ALG_OPEN_SYSTEM)
		algs = 0;
	if (auth_alg & AUTH_ALG_SHARED_KEY)
		algs = 1;

	return otus_set_param(drv, ZD_PARAM_AUTH_ALGS, algs, 1);
}

static int wpa_driver_otus_get_bssid(void *priv, u8 *bssid)
{
    struct wpa_driver_otus_data *drv=priv;
    int ret;
    
    ret = wpa_driver_wext_get_bssid(drv->wext, bssid);

    printf("wpa_driver_otus_get_bssid : %2x:%2x:%2x:%2x:%2x:%2x\n",
            bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);
    return ret;
}

static int wpa_driver_otus_get_ssid(void *priv, u8 *ssid)
{
	struct wpa_driver_otus_data *drv=priv;
	return wpa_driver_wext_get_ssid(drv->wext, ssid);
}

#ifdef WSC_NEW_IE
static int wpa_driver_otus_set_wsc_probe_request_ie(void *priv, u8 *iebuf, int iebuflen)
{
    /* TODO */

    return 0;
}

static int wpa_driver_otus_start_receive_beacons(void *priv)
{
    struct wpa_driver_otus_data *drv = priv;

    printf("%s : Enable WPS Filter Beacon/ProbeRsp\n", __func__);

    if(otus_set_param(drv, ZD_PARAM_WPS_FILTER, 1, 1))
    {
        printf("set ZD_PARAM_WPS_FILTER failed\n");
        return -1;
    }

    return 0;
}

static int wpa_driver_otus_stop_receive_beacons(void *priv)
{
    struct wpa_driver_otus_data *drv = priv;

    printf("%s : Enable WPS Filter Beacon/ProbeRsp\n", __func__);

    if(otus_set_param(drv, ZD_PARAM_WPS_FILTER, 0, 1))
    {
        printf("set ZD_PARAM_WPS_FILTER failed\n");
        return -1;
    }

    return 0;
}

static int wpa_driver_otus_process_frame(void *driver, void *ctx, const unsigned char *src_addr, const unsigned char *buf, size_t len, unsigned char *newbuf, int *newlen, u8 *frameType)
{
    // int i;
    static int j = 0;
    u8 *frm;
    u8 *endfrm;
    char ssid[32];
    u8 bssid[6];
    struct ieee80211_frame *wh;
    u8 *tmpptr;
    u8 subtype;

    //printf("********************** In %s\n", __FUNCTION__);
    printf("Received %d bytes; beacon or pr-resp number %d\n", len, j++);

    wh = (struct ieee80211_frame *) buf;
    frm = (u8 *)&wh[1];
    endfrm = (u8 *) (buf + len);

    subtype = wh->i_fc[0] & IEEE80211_FC0_SUBTYPE_MASK;

    if (subtype == IEEE80211_FC0_SUBTYPE_BEACON)
        *frameType = 1;
    else if (subtype == IEEE80211_FC0_SUBTYPE_PROBE_RESP)
        *frameType = 3;
    else
        *frameType = 0;

    printf("frameType = %d\n", *frameType);
    memcpy(bssid, wh->i_addr3, IEEE80211_ADDR_LEN);
    // printf("bssid = %02X:%02X:%02X:%02X:%02X:%02X\n", 
    // 		bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5]);

    // skip timestamp(8), beac interval(2), cap info (2)
    frm += 12;
    // get ssid
    while (frm < endfrm)
    {
        switch (*frm)
        {
        case IEEE80211_ELEMID_SSID:
            if (frm[1] > 1)
            {
                // printf("ssid len = %d\n", frm[1]);
                memset(ssid, 0, 32);
                memcpy(ssid, &frm[2], frm[1]);
                printf("ssid: %s\n", ssid);
            }
            else
            {
                // printf("ssid: <hidden>\n");
            }

            break;

         case IEEE80211_ELEMID_VENDOR:
            // check for WFA OUI
            if (frm[1] > 4 && frm[2] == 0x00 && frm[3] == 0x50 && frm[4] == 0xF2 && frm[5]==0x04)
            {
                tmpptr = newbuf;
                memcpy(tmpptr, ssid, 32);
                tmpptr += 32;
                memcpy(tmpptr, bssid, 6);
                tmpptr += 6;
                memcpy(tmpptr, &frm[6], frm[1] - 4);
                tmpptr += (frm[1] - 4);
                *newlen = (int) (tmpptr - newbuf);
                printf("Got WSC IE; ssid = %s, IE len = %d, newlen = %d\n", ssid, frm[1], *newlen);

                /*
                for (i = 0; i < frm[1]; i ++)
                {
                    printf("%02x", (unsigned char) frm[i + 2]);
                    
                    if ( (i > 0) && (!(i % 20)))
                    {
                        printf("\n");
                    }
                }
                printf("\n");
                */
            }
            default:
                break;
        } // switch

        frm += frm[1] + 2;
    } // while

    return 0;
}

static int wpa_driver_otus_start_receive_pr_resps(void *priv)
{
    struct wpa_driver_otus_data *drv = priv;

    printf("%s : Enable WPS Filter Beacon/ProbeRsp\n", __func__);

    if(otus_set_param(drv, ZD_PARAM_WPS_FILTER, 1, 1))
    {
        printf("set ZD_PARAM_WPS_FILTER failed\n");
        return -1;
    }

    return 0;
}

static int wpa_driver_otus_stop_receive_pr_resps(void *priv)
{
    struct wpa_driver_otus_data *drv = priv;

    printf("%s : Enable WPS Filter Beacon/ProbeRsp\n", __func__);

    if(otus_set_param(drv, ZD_PARAM_WPS_FILTER, 0, 1))
    {
        printf("set ZD_PARAM_WPS_FILTER failed\n");
        return -1;
    }

    return 0;
}

#endif /* WSC_NEW_IE */

static void * wpa_driver_otus_init(void *ctx, const char *ifname)
{
	struct wpa_driver_otus_data *drv;

	drv = malloc(sizeof(*drv));
	if (drv == NULL)
		return NULL;
	memset(drv, 0, sizeof(*drv));
	drv->wext = wpa_driver_wext_init(ctx, ifname);
	if (drv->wext == NULL)
		goto fail;

	drv->ctx = ctx;
	strncpy(drv->ifname, ifname, sizeof(drv->ifname));
	drv->sock = socket(PF_INET, SOCK_DGRAM, 0);
	if (drv->sock < 0)
		goto fail2;

	if (otus_set_param(drv, ZD_PARAM_ROAMING, 0, 1) < 0) {
		wpa_printf(MSG_DEBUG, "%s: failed to set wpa_supplicant-based "
			   "roaming", __FUNCTION__);
		goto fail3;
	}

	if (otus_set_param(drv, ZD_PARAM_WPA, 3, 1) < 0) {
		wpa_printf(MSG_DEBUG, "%s: failed to enable WPA/WPA2 support",
			   __FUNCTION__);
		goto fail3;
	}

	return drv;

fail3:
	close(drv->sock);
fail2:
	wpa_driver_wext_deinit(drv->wext);
fail:
	free(drv);
	return NULL;
}


static void wpa_driver_otus_deinit(void *priv)
{
	struct wpa_driver_otus_data *drv = priv;

	if (wpa_driver_otus_set_wpa_ie(drv, NULL, 0) < 0) {
		wpa_printf(MSG_DEBUG, "%s: failed to clear WPA IE",
			   __FUNCTION__);
	}
	if (otus_set_param(drv, ZD_PARAM_ROAMING, 0, 1) < 0) {
		wpa_printf(MSG_DEBUG, "%s: failed to enable driver-based "
			   "roaming", __FUNCTION__);
	}
	if (otus_set_param(drv, ZD_PARAM_PRIVACY, 0, 1) < 0) {
		wpa_printf(MSG_DEBUG, "%s: failed to disable forced Privacy "
			   "flag", __FUNCTION__);
	}
	if (otus_set_param(drv, ZD_PARAM_WPA, 0, 1) < 0) {
		wpa_printf(MSG_DEBUG, "%s: failed to disable WPA",
			   __FUNCTION__);
	}

	wpa_driver_wext_deinit(drv->wext);

	close(drv->sock);
	free(drv);
}
#if 0
static void
wpa_driver_otus_cleanup(const char *ifname)
{
	int flags;

	/* NB: mark interface down */
	if (getifflags(ifname, &flags) == 0)
		(void) setifflags(ifname, flags &~ IFF_UP);
}
#endif

static int wpa_driver_otus_get_scan_results(void *priv,
					    struct wpa_scan_result *results,
					    size_t max_size)
{
	struct wpa_driver_otus_data *drv = priv;
	return wpa_driver_wext_get_scan_results(drv->wext, results, max_size);
}

#ifdef WSC_NEW_IE
int wpa_driver_otus_init_l2_packet(void *priv, void (*handler)(void *ctx, const unsigned char *src_addr, const unsigned char *buf, size_t len))
{
        struct wpa_driver_otus_data *drv = priv;
        u8 own_addr[ETH_ALEN + 1];

        drv->l2_sock = l2_packet_init(drv->ifname, NULL, 0x0019/*ETH_P_EAPOL*/,
                                handler, drv, 1);
        if (drv->l2_sock == NULL)
        {
                printf("l2_packet_init failed\n");
                return -1;
        }

        if (l2_packet_get_own_addr(drv->l2_sock, own_addr))
                return -1;

        printf("l2_packet_init Successful\n");
        return 0;
}

int wpa_driver_otus_deinit_l2_packet(void *priv)
{
        struct wpa_driver_otus_data *drv = priv;

        l2_packet_deinit(drv->l2_sock);

        return 0;
}
#endif /*  WSC_NEW_IE */

struct wpa_driver_ops wpa_driver_otus_ops = {
	.name			= "otus",
	.desc			= "Otus 802.11 WPA support interface",
	.get_bssid		= wpa_driver_otus_get_bssid,
	.get_ssid		= wpa_driver_otus_get_ssid,
//	.set_wpa		= wpa_driver_otus_set_wpa,
	.set_key		= wpa_driver_otus_set_key,
	.init			= wpa_driver_otus_init,
	.deinit			= wpa_driver_otus_deinit,
	.set_countermeasures	= wpa_driver_otus_set_countermeasures,
	.set_drop_unencrypted	= wpa_driver_otus_set_drop_unencrypted,
	.scan			= wpa_driver_otus_scan,
	.get_scan_results	= wpa_driver_otus_get_scan_results,
	.deauthenticate		= wpa_driver_otus_deauthenticate,
	.disassociate		= wpa_driver_otus_disassociate,
	.associate		= wpa_driver_otus_associate,
	.set_auth_alg		= wpa_driver_otus_set_auth_alg,

#ifdef WSC_NEW_IE
	.set_wsc_probe_request_ie = wpa_driver_otus_set_wsc_probe_request_ie,
	.start_receive_beacons    = wpa_driver_otus_start_receive_beacons,
	.stop_receive_beacons     = wpa_driver_otus_stop_receive_beacons,
	.init_l2_packet           = wpa_driver_otus_init_l2_packet,
	.deinit_l2_packet         = wpa_driver_otus_deinit_l2_packet,
	.process_frame            = wpa_driver_otus_process_frame,
	.start_receive_pr_resps   = wpa_driver_otus_start_receive_pr_resps,
	.stop_receive_pr_resps    = wpa_driver_otus_stop_receive_pr_resps,
#endif
};

