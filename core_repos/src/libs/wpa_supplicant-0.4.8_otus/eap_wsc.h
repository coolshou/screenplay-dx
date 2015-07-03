
#ifndef EAP_WSC_H
#define EAP_WSC_H

#pragma pack(push, 1)

#define WSC_RECVBUF_SIZE    2048

struct eap_wsc_data {
    enum { START, CONTINUE, SUCCESS, FAILURE } state;
    int udpFdEap;
    int udpFdCom;
    u8 recvBuf[WSC_RECVBUF_SIZE];
};

#define WSC_NOTIFY_TYPE_BUILDREQ              1
#define WSC_NOTIFY_TYPE_BUILDREQ_RESULT       2
#define WSC_NOTIFY_TYPE_PROCESS_REQ           3
#define WSC_NOTIFY_TYPE_PROCESS_RESP          4
#define WSC_NOTIFY_TYPE_PROCESS_RESULT        5

#define WSC_NOTIFY_RESULT_SUCCESS			  0x00
#define WSC_NOTIFY_RESULT_FAILURE			  0xFF

typedef struct wsc_notify_buildreq_tag {
    u32    id;
    u32 state;
} WSC_NOTIFY_BUILDREQ;

typedef struct wsc_notify_process_buildreq_result_tag {
	u8 result;
} WSC_NOTIFY_BUILDREQ_RESULT;

typedef struct wsc_notify_process_tag {
	u32 state;
} WSC_NOTIFY_PROCESS;

typedef struct wsc_notify_process_result_tag {
	u8 result;
	u8 done;
} WSC_NOTIFY_PROCESS_RESULT;

typedef struct wsc_notify_data_tag {
    u8 type;
    union {
        WSC_NOTIFY_BUILDREQ bldReq;
        WSC_NOTIFY_BUILDREQ_RESULT bldReqResult;
        WSC_NOTIFY_PROCESS process;
        WSC_NOTIFY_PROCESS_RESULT processResult;
    } u;
	u32 length; // length of the data that follows
} WSC_NOTIFY_DATA;


/*
#define WSC_CTYPE_NEW_SETTINGS      1
#define WSC_CTYPE_MAX               2

#define WSC_MAX_SSID_LEN            32
#define WSC_MAX_PSK_LEN             32

struct wsc_command_data {
    u8 type;
    union {
        struct wsc_new_settings
        {
            u16 ssidLen;
            char ssid[WSC_MAX_SSID_LEN];
            u16 pskLen;
            u8 psk[WSC_MAX_PSK_LEN];
        } new_set;
    } u;
};
*/

#pragma pack(pop)

#endif /*EAP_WSC_H*/
