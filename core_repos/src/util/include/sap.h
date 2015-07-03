/* Copyright (C) 2005, REDSonic, inc.
 * Author:  Wills Yin <wills_yin@redsonic.com>
 */
#ifndef  __SAP_H__
#define  __SAP_H__

#ifndef __SDP_H__
#include "sdp.h"
#endif

typedef struct sap_session_s sap_session_t;

struct sap_session_s {
        int              version;
        int              addrType;
        int              isDel;
        int              isEnc;
        int              isComp;
	unsigned int     hashID;
	char             sourceIP[32];
	sdp_desc_t*      sdp;
};

sap_session_t*  sap_parse(char* packet,  int packet_len);
void            sap_destroy(sap_session_t* sap);
#endif
