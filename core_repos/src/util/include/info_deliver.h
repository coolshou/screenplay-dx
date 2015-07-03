#ifndef _INFO_DELIVER_H_
#define _INFO_DELIVER_H_
#include <stdio.h>


typedef enum _InfoExtendedCommand {
	InfoExtendedCommandSavePic,
	InfoExtendedCommandVideoInfo, //fps * 1000
	InfoExtendedCommandServerType,
	InfoExtendedCommandDIVXDrmInfo,
	InfoExtendedCommandForceDIVXDrmPlay,
	InfoExtendedCommandPlayBackTitleInfo,
} InfoExtendedCommand;

typedef enum _InfoExtendedCommandRet {
	InfoExtendedCommandRetError = -1,
	InfoExtendedCommandRetOK = 0,
}InfoExtendedCommandRet;

typedef struct _INFO_EXTENDED_COMMAND {
	int size;
	char *data;
} INFO_EXTENDED_COMMAND;

enum _VIDEO_INFO_DRM_TYPE { //please ref src/mediaplayer/player/MediaPlayer.h
	VIDEO_INFO_DRM_TYPE_DCA = 0,
	VIDEO_INFO_DRM_TYPE_DUA = 1,
	VIDEO_INFO_DRM_TYPE_DUV = 2,
	VIDEO_INFO_DRM_TYPE_AV = 3,
	VIDEO_INFO_DRM_TYPE_APSTB = 4,
};
typedef struct _INFO_EXTENDED_COMMAND_VIDEO_INFO_DATA {
	int width;
	int height;
	int fps; //fps *1000
	int codec;
	int DRM_Level[5]; //DCA,DUA,DUV,AV(compontent),APSTB
} INFO_EXTENDED_COMMAND_VIDEO_INFO_DATA;

typedef struct _INFO_EXTENDED_COMMAND_SAVE_PIC_DATA {
	int id;
	int mode;
	int w;
	int h;
	int result;
	char *file_path;
} INFO_EXTENDED_COMMAND_SAVE_PIC_DATA;

typedef struct _INFO_EXTENDED_COMMAND_SERVER_TYPE_DATA {
	int server_type;
	int private_data_len;
	char *private_data;
}INFO_EXTENDED_COMMAND_SERVER_TYPE_DATA;

typedef enum _INFO_EXTENDED_COMMAND_DIVX_DRM_INFO_RESULT {
	INFO_EXTENDED_COMMAND_DIVX_DRM_INFO_RESULT_OK = 0,
	INFO_EXTENDED_COMMAND_DIVX_DRM_INFO_RESULT_ERROR = -1,
	INFO_EXTENDED_COMMAND_DIVX_DRM_INFO_RESULT_NOT_AUTHORIZED = -2,
	INFO_EXTENDED_COMMAND_DIVX_DRM_INFO_RESULT_RENTAL_EXPIRED = -3,
	INFO_EXTENDED_COMMAND_DIVX_DRM_INFO_RESULT_UNSUPPORTED_VERSION = -4,
} INFO_EXTENDED_COMMAND_DIVX_DRM_INFO_RESULT;

typedef struct _INFO_EXTENDED_COMMAND_DIVX_DRM_INFO_DATA {
	int is_update;
	int is_DRM;
	int Result;
	int Version;
	int RentalCount;
	int RentalLimit;
	int CGMSA;
	int ACPTB;
	int HDCP;
	int ICT;
} INFO_EXTENDED_COMMAND_DIVX_DRM_INFO_DATA;

#define MAX_PLAYBACK_TITLE_NUMBER 10
#define MAX_PLAYBACK_TITLE_NAME_SIZE 60

typedef struct _INFO_EXTENED_COMMAND_PLAYBACK_TITLE_DATA {
	int total_title;
	int current_title;
	int current_edition;
	int edition_number[MAX_PLAYBACK_TITLE_NUMBER];
	char title_name[MAX_PLAYBACK_TITLE_NUMBER][MAX_PLAYBACK_TITLE_NAME_SIZE];
	int title_seek_time; //<= 0 means do nothing.  0 also means do nothink that is incase we use memset function, so we need ot plus 1 when we use seek time
} INFO_EXTENED_COMMAND_PLAYBACK_TITLE_DATA;

/*
 * format is 
 *		(4bytes) -> command
 *		(nbytes) -> data
 */
char *InfoGetExtendedCommand(char *buf,int len,InfoExtendedCommand *command,int *data_size);
char *InfoBuildExtendedCommand(InfoExtendedCommand command,char *data,int len,int *ret_size);
char *InfoBuildIntExtendedCommand(InfoExtendedCommand command,int *value,int *ret_size,int num);
InfoExtendedCommandRet InfoGetIntExtendedCommand(char *buf,int len,int *value,int num);

void BuildInfoExtendedCommandSavePicData(INFO_EXTENDED_COMMAND_SAVE_PIC_DATA *pPicData,int id,int w,int h,int result,char *file_path);
void DestroyInfoExtendedCommandSavePicData(INFO_EXTENDED_COMMAND_SAVE_PIC_DATA *pPicData);
char *InfoBuildExtendedCommandSavePic(INFO_EXTENDED_COMMAND_SAVE_PIC_DATA *pPicData,int *ret_size);
InfoExtendedCommandRet InfoParseExtendedCommandSavePic(char *buf,int len,INFO_EXTENDED_COMMAND_SAVE_PIC_DATA *pPicData);

char *InfoBuildExtendedCommandVideoInfo(INFO_EXTENDED_COMMAND_VIDEO_INFO_DATA *Data,int *ret_size);
InfoExtendedCommandRet InfoParseExtendedCommandVideoInfo(char *buf,int len,INFO_EXTENDED_COMMAND_VIDEO_INFO_DATA *pData);

void BuildInfoExtendedCommandServerTypeData(INFO_EXTENDED_COMMAND_SERVER_TYPE_DATA *pData,int server_type,char *private_data,int private_data_len);
void DestroyInfoExtendedCommandServerTypeData(INFO_EXTENDED_COMMAND_SERVER_TYPE_DATA *pData);
char *InfoBuildExtendedCommandServerType(INFO_EXTENDED_COMMAND_SERVER_TYPE_DATA *pData,int *ret_size);
InfoExtendedCommandRet InfoParseExtendedCommandServerType(char *buf,int len,INFO_EXTENDED_COMMAND_SERVER_TYPE_DATA *pData);

char *InfoBuildExtendedCommandDIVX_DRM_Info(INFO_EXTENDED_COMMAND_DIVX_DRM_INFO_DATA *Data,int *ret_size);
InfoExtendedCommandRet InfoParseExtendedCommandDIVX_DRM_Info(char *buf,int len,INFO_EXTENDED_COMMAND_DIVX_DRM_INFO_DATA *pData);

char *InfoBuildExtendedCommandPlayBackTitleInfo(INFO_EXTENED_COMMAND_PLAYBACK_TITLE_DATA *Data,int *ret_size);
InfoExtendedCommandRet InfoParseExtendedCommandPlayBackTitleInfo(char *buf,int len,INFO_EXTENED_COMMAND_PLAYBACK_TITLE_DATA *pData);
int InfoShowExtendedCommandPlayBackTitleInfo(INFO_EXTENED_COMMAND_PLAYBACK_TITLE_DATA *pData);
int InfoExtendedCommandIsMultiTitle(INFO_EXTENED_COMMAND_PLAYBACK_TITLE_DATA *pData);

InfoExtendedCommandRet InfoParseExtendedCommandVaryStructure(char *buf,int len,int struct_size,void *pData);
char *InfoBuildExtendedCommandVaryStructure(InfoExtendedCommand command,int struct_size,void *Data,int *ret_size);

int subtitle_deliver_build(char *buf,int pid,char *name,char *codec,int output);
int subtitle_deliver_get_pid(char *buf);
char *subtitle_deliver_get_name(char *buf);
char *subtitle_deliver_get_codec(char *buf);
int subtitle_deliver_get_output(char *buf);

int audio_deliver_build(char *buf,int pid,char *name,int codec,int output);
int audio_deliver_get_pid(char *buf);
char *audio_deliver_get_name(char *buf);
int audio_deliver_get_codec(char *buf);
int audio_deliver_get_output(char *buf);


#define BUFFERING_STATUS_DELIVER_BUF_SIZE 40

/*	
	format:
	1d:4d:4d:4d:10d
	1d -> is_buffering or not
	4d -> buffering_time (second)
	4d -> buffering_start_time (second)
	4d -> buffering_start_time (second)
	10d -> buffering_size (bytes)
*/
int buffering_status_deliver_zero(char *buf);
int buffering_status_deliver_build(char *buf,int is_buffering,int buffering_size,int buffering_time,int buffering_start_time,int buffering_end_time);
int buffering_status_deliver_get(char *buf,int *is_buffering,int *buffering_size,int *buffering_time,int *buffer_start_time,int *buffering_end_time);
#endif
