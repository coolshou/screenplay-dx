#ifndef __DLNA_H__
#define __DLNA_H__

#define DLNA_TRANSPORT_STRING_STREAM "Streaming"
#define DLNA_TRANSPORT_STRING_INTERACTIVE "Interactive"
#define DLNA_IFOFILEURI_PRAGMA "PRAGMA: getIfoFileURI.dlna.org\r\n"
#define DLNA_LOP_FLAGS_BYTE_RANGE "getAvailableSeekRange.dlna.org: 1\r\n"

typedef enum {
	NET_CONNECTION = 0, /*Network connection, such as http-get*/
	MIME_TYPE,          /*MIME_TYPE, such as video/mpeg*/
	MIME_TYPE_LPCM_CHANNELS,
	MIME_TYPE_LPCM_RATE,
	MIME_TYPE_DTCP,
	DLNA_PN,            /*DLNA.ORG_PN*/
	DLNA_OP,            /*DLNA.ORG_OP*/
	DLNA_CI,            /*DLNA.ORG_CI*/
	DLNA_PS,             /*DLNA.ORG_PS*/
	DLNA_FLAGS,             /* DLNA.ORG_FLAGS */
	INTEL_COM_VIDEOTYPE,
	DTCP1_HOST,
	DTCP1_PORT
}PROTOCOL_FIELD_TYPE;

#define DLNA_PS_FF_64X  0x0001          /*speed 64x  */
#define DLNA_PS_FF_32X  0x0002          /*speed 32x  */   
#define DLNA_PS_FF_16X  0x0004          /*speed 16x  */
#define DLNA_PS_FF_8X   0x0008          /*speed 8x   */
#define DLNA_PS_FF_4X   0x0010          /*speed 4x   */
#define DLNA_PS_FF_2X   0x0020          /*speed 2x   */
#define DLNA_PS_FB_1X   0x0040          /*speed -1x  */
#define DLNA_PS_FB_2X   0x0080          /*speed -2x  */
#define DLNA_PS_FB_4X   0x0100          /*speed -4x  */
#define DLNA_PS_FB_8X   0x0200          /*speed -8x  */
#define DLNA_PS_FB_16X  0x0400          /*speed -16x */
#define DLNA_PS_FB_32X  0x0800          /*speed -32x */
#define DLNA_PS_FB_64X  0x1000          /*speed -64x */

enum DLNA_TRANSPORT_MODE
{
	DLNA_TRANSPORT_STREAM,
	DLNA_TRANSPORT_INTERACTIVE	
};

typedef struct dlna_org_flags_s {
	int connection_stalling;                /* bit 21, bool */
	int lop_flags_byte_range; /* bit 29, bool, limited operations flag for byte-range */
}dlna_org_flags_t;

typedef struct _DLNAContext 
{
	int dlna_op; /* DLNA flag to indicate if server support time and file seek */
	int dlna_ci; /* DLNA flag to indicate if server has trancoded the streaming */
	unsigned int dlna_ps; /*DLNA flag to indicate if the server support trick-mode and list the speed*/
	char *dlna_ifofileuri;
	dlna_org_flags_t dlna_flags;
	enum DLNA_TRANSPORT_MODE dlna_transport_mode;
}DLNAContext;

void dlna_set_transport_mode(DLNAContext *p_dlna, enum DLNA_TRANSPORT_MODE i_mode);
char *dlna_get_transport_mode_string(DLNAContext *p_dlna);
void dlna_set_ifofile_uri(DLNAContext *p_dlna, char *p_ifofileuri);
char *dlna_get_ifofile_uri(DLNAContext *p_dlna);
char *dlna_get_ifofileuri_http_pragma(DLNAContext *p_dlna);
int dlna_get_protocol(const char* protocolstr,PROTOCOL_FIELD_TYPE type, void* value);
#endif
