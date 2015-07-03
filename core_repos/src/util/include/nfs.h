#ifndef __NFS_INFO_H__
#define __NFS_INFO_H__

#define NFS_P2SFIFO	"nfs_p2sfifo"
#define NFS_S2PFIFO	"nfs_s2pfifo"
#define NFS_CMD_LEN 256

typedef enum _nfs_cmd_status {
	NFS_CMD_STATUS_NONE=0,
	NFS_CMD_STATUS_MOUNT_OK,
	NFS_CMD_STATUS_MOUNT_FAIL,
} NFS_CMD_STATUS_E;

typedef enum _nfs_cmd_type {
	NFS_CMD_TYPE_NONE=0,
	NFS_CMD_BROWSE,
	NFS_CMD_BROWSE_RESPONSE,
} NFS_CMD_TYPE_E;

struct nfsEventProxyCmd {
  int id;
  NFS_CMD_TYPE_E cmd;
  NFS_CMD_STATUS_E status; 		
  unsigned int datalen;
  unsigned char data[NFS_CMD_LEN];
};

typedef void(*nfs_callback_generic)(int id, int errorcode, void* userdata);
#endif /*end of __NFS_INFO_H__*/
