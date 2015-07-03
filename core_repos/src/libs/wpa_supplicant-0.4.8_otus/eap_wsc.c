/*
 * WPA Supplicant / Wi-Fi Simple Configuration 7C Proposal
 * Copyright (c) 2004-2005, Jouni Malinen <jkmaline@cc.hut.fi>
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
#include <string.h>
/*#include <netinet/in.h> */
#ifdef __linux__
#include <netinet/in.h>
#include <arpa/inet.h>
#endif
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/dh.h>
#include <openssl/bn.h>
#include <openssl/rand.h>

#include "common.h"
#include "eloop.h"
#include "eap_i.h"
#include "wpa_supplicant.h"
#include "eap_wsc.h"
#include "UdpLib.h"

#define WSC_EAP_UDP_PORT            37000
#define WSC_EAP_UDP_ADDR            "127.0.0.1"
// #define WSC_COMMANDS_UDP_PORT       38000

/*
static void wsc_read_callback(int sock, void *eloop_ctx, void *sock_ctx)
{
    struct eap_wsc_data *data = eloop_ctx;
    struct wsc_command_data comData;
    int recvBytes;
    struct sockaddr_in from;

    wpa_printf(MSG_DEBUG, "EAP-WSC: Entered wsc_read_callback. "
            "sock = %d\n", sock);

    recvBytes = udp_read(data->udpFdCom, (u8 *) &comData, 
            sizeof(struct wsc_command_data), &from);

    if (recvBytes == -1 || recvBytes < sizeof(struct wsc_command_data))
    {
        wpa_printf(MSG_INFO, "EAP-WSC: Reading Command message "
                "from upper layer failed\n");
	    return;
    }

    if (comData.type == WSC_CTYPE_NEW_SETTINGS)
    {
        // write file; send command to reload
    }
    else
    {
        wpa_printf(MSG_INFO, "EAP-WSC: Wrong command type from upper layer\n");
	    return;
    }
   
    return;
}
*/

static void * eap_wsc_init(struct eap_sm *sm)
{
    struct eap_wsc_data *data;

    wpa_printf(MSG_DEBUG,"@#*@#*@#*EAP-WSC: Entered eap_wsc_init *#@*#@*#@");

    data = malloc(sizeof(*data));
    if (data == NULL)
        return data;
    memset(data, 0, sizeof(*data));

    data->udpFdEap = udp_open();

	/*
    data->udpFdCom = udp_open();
    if (udp_bind(data->udpFdCom, WSC_COMMANDS_UDP_PORT) == -1)
    {
        wpa_printf(MSG_DEBUG, "EAP-WSC: udp_bind failed!");
        free(data);
        return NULL;
    }

    eloop_register_read_sock(data->udpFdCom, wsc_read_callback,
				 data, NULL);
	*/

    sm->eap_method_priv = data;

    return data;
}


static void eap_wsc_deinit(struct eap_sm *sm, void *priv)
{
    wpa_printf(MSG_DEBUG,"@#*@#*@#*EAP-WSC: Entered eap_wsc_reset *#@*#@*#@");

    struct eap_wsc_data *data = (struct eap_wsc_data *)priv;
    if (data == NULL)
        return;

    if (data->udpFdEap != -1)
    {
        udp_close(data->udpFdEap);
        data->udpFdEap = -1;
    }

	/*
    if (data->udpFdCom != -1)
    {
		eloop_unregister_read_sock(data->udpFdCom);
        udp_close(data->udpFdCom);
        data->udpFdCom = -1;
    }
	*/

    free(data);
}

static u8 * eap_wsc_process(struct eap_sm *sm, void *priv,
                            struct eap_method_ret *ret,
                            u8 *reqData, size_t reqDataLen,
                            size_t *respDataLen)
{
    struct eap_wsc_data *data = priv;
    struct eap_hdr *req;
    int recvBytes;
    u8 * resp;
    u8 * sendBuf;
    u32 sendBufLen;
    struct sockaddr_in from;
    struct sockaddr_in to;
    WSC_NOTIFY_DATA notifyData;
    WSC_NOTIFY_DATA * recvNotify;

    wpa_printf(MSG_DEBUG,"@#*@#*@#*EAP-WSC: Entered eap_wsc_process *#@*#@*#@");

    req = (struct eap_hdr *) reqData;
    wpa_printf(MSG_DEBUG, "EAP-WSC : Received packet(len=%lu) ",
               (unsigned long) reqDataLen);
    if(ntohs(req->length) != reqDataLen)
    {
        wpa_printf(MSG_INFO, "EAP-WSC: Pkt length in pkt(%d) differs from" 
			" supplied (%d)\n", ntohs(req->length), reqDataLen);
        ret->ignore = TRUE;
	    return NULL;
    }

    notifyData.type = WSC_NOTIFY_TYPE_PROCESS_REQ;
    notifyData.length = reqDataLen;
    notifyData.u.process.state = data->state;
   
    sendBuf = (u8 *) malloc(sizeof(WSC_NOTIFY_DATA) + reqDataLen);
    if ( ! sendBuf)
    {
        wpa_printf(MSG_INFO, "EAP-WSC: Memory allocation "
                "for the sendBuf failed\n");
        ret->ignore = TRUE;
	    return NULL;
    }

    memcpy(sendBuf, &notifyData, sizeof(WSC_NOTIFY_DATA));
    memcpy(sendBuf + sizeof(WSC_NOTIFY_DATA), reqData, reqDataLen);
	sendBufLen = sizeof(WSC_NOTIFY_DATA) + reqDataLen;

    to.sin_addr.s_addr = inet_addr(WSC_EAP_UDP_ADDR);
    to.sin_family = AF_INET;
    to.sin_port = htons(WSC_EAP_UDP_PORT);

    if (udp_write(data->udpFdEap, (char *) sendBuf, sendBufLen, &to) < 
            sendBufLen)
    {
        wpa_printf(MSG_INFO, "EAP-WSC: Sending Eap message to "
                "upper Layer failed\n");
        ret->ignore = TRUE;
        free(sendBuf);
	    return NULL;
    }

    free(sendBuf);

    recvBytes = udp_read_timed(data->udpFdEap, (char *) data->recvBuf, 
            WSC_RECVBUF_SIZE, &from, 5);

    if (recvBytes == -1)
    {
        wpa_printf(MSG_INFO, "EAP-WSC: Reading EAP message "
                "from upper layer failed\n");
        ret->ignore = TRUE;
	    return NULL;
    }

    recvNotify = (WSC_NOTIFY_DATA *) data->recvBuf;
    if ( (recvNotify->type != WSC_NOTIFY_TYPE_PROCESS_RESULT) ||
    //     (recvNotify->length == 0) ||
    (recvNotify->u.processResult.result != WSC_NOTIFY_RESULT_SUCCESS) )
    {
        wpa_printf(MSG_INFO, "EAP-WSC: Process Message failed "
                "somewhere\n");
        ret->ignore = TRUE;
	    return NULL;
    }
	
    resp = (u8 *) malloc(recvNotify->length);
    if (!resp)
    {
        wpa_printf(MSG_INFO, "EAP-WSC: Memory allocation "
                "for the resp failed\n");
        ret->ignore = TRUE;
	    return NULL;
    }

    memcpy(resp, recvNotify + 1, recvNotify->length);
    *respDataLen = recvNotify->length;
    ret->ignore = FALSE;
    ret->decision = DECISION_COND_SUCC;
    ret->allowNotifications = FALSE;

    /*check if we're done*/
    if (recvNotify->u.processResult.done)
    {
        ret->methodState = METHOD_DONE;
    }
    else
    {
        wpa_printf(MSG_INFO, "Always setting it to METHOD_CONT\n");
        ret->methodState = METHOD_CONT;
    }

    return resp;
}

const struct eap_method eap_method_wsc =
{
    .method = EAP_TYPE_WSC ,
    .name = "WSC",
    .init = eap_wsc_init,
    .deinit = eap_wsc_deinit,
    .process = eap_wsc_process,
};


