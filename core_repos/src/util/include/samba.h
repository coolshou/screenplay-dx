
#ifndef __SAMBA_INFO_H__
#define __SAMBA_INFO_H__

#define SAMBA_CMD_LEN 256
typedef enum
{
    SMB_CMD_QUIT = 0,
    SMB_CMD_QUIT_RESPONSE,
	SMB_CMD_BROWSE,
	SMB_CMD_BROWSE_RESPONSE,
	SMB_CMD_REFRESH_SERVER,
	SMB_CMD_REFRESH_SERVER_RESPONSE,
	SMB_CMD_UMOUNT,
	SMB_CMD_UMOUNT_RESPONSE,
	SMB_CMD_ACCESS,
	SMB_CMD_ACCESS_RESPONSE
}smb_cmd_t;

typedef enum _smb_cmd_status_s{
        SMB_CMD_STATUS_NONE = 0,
        SMB_REFRESHING,
	SMB_REFRESHED_OK,
	SMB_REFRESHED_FAILED,
        SMB_MOUNTING,
        SMB_MOUNT_OK,
        SMB_MOUNT_FAILED,
        SMB_UMOUNT_OK,
        SMB_UMOUNT_FAILED,
	SMB_ACCESS_OK,
	SMB_ACCESS_LOGIN_FAILED,
	SMB_ACCESS_FAILED,
	SMB_CMD_OK
}smb_cmd_status_t;

struct smbEventProxyCmd
{
  int id;
  smb_cmd_t cmd;
  smb_cmd_status_t status; 		
  unsigned int datalen;
  unsigned char data[SAMBA_CMD_LEN];
};

#define SMB_P2SFIFO	"smb_p2sfifo"
#define SMB_S2PFIFO	"smb_s2pfifo"

typedef void(*samba_callback_generic)(int id,
                     int errorcode,
                     void* userdata);

#endif /*__SAMBA_INFO_H__*/

