#ifndef _QUEUE_LINKED_UNIT_H_
#define _QUEUE_LINKED_UNIT_H_
enum RUN_TYPE{
	QL_Queue = 0,
	QL_Linked_List
};

enum QL_PROPERTY{
	QL_RUN_TYPE = 0,
	QL_QBUF_SIZE,
	QL_READ_BUF_SIZE,
	QL_MAX_NODE_NUM,
	QL_READ_FUNC,
	QL_GETBUF_FUNC,
	QL_FREEBUF_FUNC,
	QL_INIT_BUF,
	QL_INIT_BUFSIZE,
	QL_CURRENT_BUF_SIZE,
	QL_LAST_READ_SIZE,		// Read Only. If read error, last reading length will be -1
	QL_STOP_FUNC,
	QL_STOP_DATA,
};

typedef int (*QL_User_Read) (int fd,unsigned char *buf,int size);
typedef unsigned char* (*QL_User_getBuf) (int len);
typedef int (*QL_User_freeBuf) (unsigned char *buf);
typedef int (*QL_User_StopFunc) (void *data);
typedef int (*QL_User_FuncInStop) (void *data);

void* fp_QL_Init(int fd);
void fv_QL_Destroy(void **_pQL_Data);
int fn_QL_Stop(void *_pQL_Data,QL_User_FuncInStop func,void *data);
int fn_QL_Run(void *_pQL_Data);
int fn_QL_SetProperty(void *_pQL_Data,int type,void *value);
int fn_QL_GetProperty(void *_pQL_Data,int type,void *value);
int fn_QL_PreRead(void *_pQL_Data,unsigned char *pBuf,int nSize);
int fn_QL_CheckBufSize(void *_pQL_Data);
int fn_QL_isEOS(void *_pQL_Data);

#endif
