#ifndef _SOCKET_MESSAGE_DELIVER_H_
#define _SOCKET_MESSAGE_DELIVER_H_

typedef enum _SMD_MESSAGE_CODE {
	SMD_MESSAGE_CODE_DISCONNECT,
	SMD_MESSAGE_CODE_MALLOC_BUF,
	SMD_MESSAGE_CODE_FREE_BUF,
} SMD_MESSAGE_CODE;

#define SMD_LOCAL_PORT 1357
/******* server *********/
void *SMD_OpenLocalServer(int port,int max_client);
int SMD_CloseLocalServer(void *_pData);
int SMD_ListenClient(void *_pData,int wait_time);
int SMD_GetNumberOfClient(void *_pData);
int SMD_GetMallocSize(char *buf,int len);
char *SMD_GetFreeBuffer(char *buf,int len);

/******* client ********/
void *SMD_OpenLocalClient(int port);
int SMD_CloseLocalClient(void *_pData);
char *SMD_GetMallocBuffer(char *buf,int len);
int SMD_SendMallocCommand(void *_pData);
int SMD_SendFreeCommand(void *_pData);

/******* public  ********/
char *SMD_BuildCommand(int code,char *buf,int len,int *getlen);
char *SMD_GetCodeAndData(char *buf,int len,int *getlen,int *code);
int SMD_SendCommand(void *_pData,char *buf,int len,int wait_time);
char *SMD_GetCommand(void *_pData,int wait_time,int *getlen);
int SMD_SendCommandAndWaitBack(void *_pData,char *buf,int len,int wait_time,int max_number);
int SMD_GetCommandFD(void *_pData);



#endif
