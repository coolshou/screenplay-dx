/*
 * wpa_supplicant / Wi-Fi Simple Configuration 7C Proposal
 * Copyright (c) 2005 Intel Corporation. All rights reserved.
 * Contact Information: Harsha Hegde  <harsha.hegde@intel.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Alternatively, this software may be distributed under the terms of BSD
 * license.
 *
 * See README, README_WSC and COPYING for more details.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <errno.h>

#include "common.h"
#include "driver.h"
#include "driver_wext.h"
#include "eloop.h"
#include "wpa_supplicant.h"
#include "wpa.h"
#include "wpa_supplicant_i.h"
#include "wireless_copy.h"

#include "UdpLib.h"
#include "wsc_ie.h"

// Comment out the next line if debug strings are not needed
#define U_DEBUG

void DEBUGF(char *, ...);

static WSC_IE_DATA * g_wsc_ie_data;
int g_wsc=0;


static void wsc_ie_read_callback(int sock, void *eloop_ctx, void *sock_ctx)
{
	WSC_IE_DATA * data = eloop_ctx;
	WSC_IE_COMMAND_DATA * cmdData;
	char readBuf[WSC_WLAN_DATA_MAX_LENGTH];
	int recvBytes;
	struct sockaddr_in from;
	u8 * bufPtr;
	// int i;
	int retval;
	char ssid[36];

	wpa_printf(MSG_INFO, "WSC_IE: Entered wsc_ie_read_callback. "
		"sock = %d", sock);

	recvBytes = udp_read(data->udpFdCom, readBuf,
		WSC_WLAN_DATA_MAX_LENGTH, &from);

	if (recvBytes == -1)
	{
		wpa_printf(MSG_ERROR, "WSC_IE: Reading Command message "
			"from upper layer failed");
		return;
	}

	/*
	for (i = 0; i < recvBytes; i ++)
	{
		printf("%02x ", (unsigned char) readBuf[i]);
	}
	printf("\n");
	*/

	cmdData = (WSC_IE_COMMAND_DATA *) readBuf;

	if (cmdData->type == WSC_IE_TYPE_SET_PROBE_REQUEST_IE)
	{
		wpa_printf(MSG_INFO, "WSC_IE: SET_PROBE_REQUEST_IE from upper layer");
		bufPtr = (u8 *) &(cmdData->data[0]);
		wpa_drv_set_wsc_probe_request_ie(data->wpa_s, bufPtr, cmdData->length);
	}
	else if (cmdData->type == WSC_IE_TYPE_SEND_BEACONS_UP)
	{
		wpa_printf(MSG_INFO, "WSC_IE: SEND_BEACONS_UP from upper layer");
		bufPtr = (u8 *) &(cmdData->data[0]);

		if (bufPtr[0] == 1)
		{
	 		g_wsc_ie_data->sendUp = 1;
			wpa_printf(MSG_INFO, "WSC_IE: Activate = 1\n");
			retval = wpa_drv_start_receive_beacons(data->wpa_s);
			printf("\n\n*** wpa_drv_start_receive_beacons return val = %d\n\n", retval);
		}
		else
		{
	 		g_wsc_ie_data->sendUp = 0;
			wpa_printf(MSG_INFO, "WSC_IE: Activate = 0\n");
			retval = wpa_drv_stop_receive_beacons(data->wpa_s);
			// printf("wpa_drv_stop_receive_beacons return val = %d\n", retval);
		}
    }
    else if (cmdData->type == WSC_IE_TYPE_SEND_PR_RESPS_UP)
    {
		wpa_printf(MSG_INFO, "WSC_IE: SEND_PR_RESPS_UP from upper layer");
		bufPtr = (u8 *) &(cmdData->data[0]);

		if (bufPtr[0] == 1)
		{
			wpa_printf(MSG_INFO, "WSC_IE: Activate = 1\n");
			retval = wpa_drv_start_receive_pr_resps(data->wpa_s);
			printf("wpa_drv_start_receive_pr_resps return val = %d\n", retval);
		}
		else
		{
			wpa_printf(MSG_INFO, "WSC_IE: Activate = 0\n");
			retval = wpa_drv_stop_receive_pr_resps(data->wpa_s);
			printf("wpa_drv_stop_receive_pr_resps return val = %d\n", retval);
		}
    }
    else if (cmdData->type == WSC_IE_TYPE_SEND_PROBE_REQUEST)
    {
		wpa_printf(MSG_INFO, "WSC_IE: SEND_PROBE_REQUEST from upper layer");
		bufPtr = (u8 *) &(cmdData->data[0]);
		strcpy(ssid, (char *) bufPtr);

		wpa_printf(MSG_INFO, "WSC_IE: SSID received from up = %s\n", ssid);
		retval = wpa_drv_scan(data->wpa_s, ssid, strlen(ssid));
		printf("wpa_drv_scan return val = %d\n", retval);
    }
    else
    {
		wpa_printf(MSG_ERROR, "WSC_IE: Wrong command type from upper layer");
		return;
    }

    return;
}

static void
wsc_handle_frames(void *ctx, const unsigned char *src_addr, const unsigned char *buf, size_t len)
{
	u8 newbuf[256];
	int newlen;
	WSC_IE_COMMAND_DATA * cmdData;
	struct sockaddr_in to;
	u8 frameType = 0;

	cmdData = (WSC_IE_COMMAND_DATA *) newbuf;
	newlen = 0;
	if (wpa_drv_process_frame(g_wsc_ie_data->wpa_s, ctx, src_addr, 
				buf, len, newbuf + sizeof(WSC_IE_COMMAND_DATA), &newlen, 
				&frameType) < 0)
	{
		wpa_printf(MSG_ERROR, "process_frame was not called or successful\n");
		return;
	}

//	printf("Process frames done; newlen = %d, frameType = %d\n", 
//			newlen, frameType);

	if (frameType != 1 && frameType != 3)
	{
		wpa_printf(MSG_ERROR, "Not a Beacon or Probe-Response\n");
		return;
	}

	if (newlen)
	{
		if (frameType == 1) {
			if (! g_wsc_ie_data->sendUp) 
				return;
			if ( (g_wsc_ie_data->sendCounter % 50) != 0) {
				g_wsc_ie_data->sendCounter++;
				return; // only send up 1 in 50 beacons
			}
			g_wsc_ie_data->sendCounter++;
			cmdData->type = WSC_IE_TYPE_BEACON_IE_DATA;
			wpa_printf(MSG_INFO, "\n\nWSC_IE: sending up WSC beacon\\nn");
		}
		else {
			cmdData->type = WSC_IE_TYPE_PROBE_RESPONSE_IE_DATA;
			wpa_printf(MSG_INFO, "WSC_IE: sending up WSC probe response\n");
		}

		cmdData->length = newlen;

		to.sin_addr.s_addr = inet_addr(WSC_WLAN_UDP_ADDR);
		to.sin_family = AF_INET;
		to.sin_port = htons(WSC_WLAN_UDP_PORT);

		newlen += sizeof(WSC_IE_COMMAND_DATA);

		if (udp_write(g_wsc_ie_data->udpFdCom, (char *) newbuf, 
				newlen, &to) < newlen)
		{
			wpa_printf(MSG_INFO, "WSC_IE: Sending Beacon Data to "
					"upper Layer failed");
			return;
		}

		// printf("udp_write done\n");
	}
}


int wsc_ie_init(struct wpa_supplicant *wpa_s)
{
	struct sockaddr_in to;
	char sendBuf[5];

	wpa_printf(MSG_INFO, "\n\n******WSC_IE: In wsc_ie_init\n\n");
	
	g_wsc_ie_data = malloc(sizeof(WSC_IE_DATA));
	
	if (g_wsc_ie_data == NULL)
	{
		return -1;
	}

	memset(g_wsc_ie_data, 0, sizeof(WSC_IE_DATA));

	g_wsc_ie_data->wpa_s = wpa_s;
	g_wsc_ie_data->sendUp = 0;
	g_wsc_ie_data->sendCounter = 0;
	g_wsc_ie_data->udpFdCom = udp_open();

	eloop_register_read_sock(g_wsc_ie_data->udpFdCom, wsc_ie_read_callback,
		g_wsc_ie_data, NULL);

	/* Send a start packet */
	strcpy(sendBuf, "PORT");
	to.sin_addr.s_addr = inet_addr(WSC_WLAN_UDP_ADDR);
	to.sin_family = AF_INET;
	to.sin_port = htons(WSC_WLAN_UDP_PORT);

	if (udp_write(g_wsc_ie_data->udpFdCom, sendBuf, 5, &to) < 5)
	{
		wpa_printf(MSG_ERROR, "WSC_IE: Sending Port message to "
			"upper Layer failed");
		return -1;
	}

	// register to get l2_packets
	wpa_drv_init_l2_packet(wpa_s, wsc_handle_frames);

	return 0;
}

int wsc_ie_deinit(struct wpa_supplicant *wpa_s)
{
	wpa_drv_deinit_l2_packet(wpa_s);

	if (g_wsc_ie_data->udpFdCom != -1)
	{
		eloop_unregister_read_sock(g_wsc_ie_data->udpFdCom);
		udp_close(g_wsc_ie_data->udpFdCom);
		g_wsc_ie_data->udpFdCom = -1;
	}

	g_wsc_ie_data->wpa_s = NULL;

	free(g_wsc_ie_data);
	g_wsc_ie_data = NULL;

	return 0;
}
