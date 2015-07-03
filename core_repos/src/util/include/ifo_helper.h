#ifndef _IFO_HELPER_H_
#define _IFO_HELPER_H_


void* IFO_HELPER_Init(void *pUserData);
int IFO_HELPER_Uninit(void *_p);
int IFO_HELPER_Open(void *_p,char *path);
int IFO_HELPER_ShowInfo(void *_p);
int IFO_HELPER_GetNumberFilms(void *_p);
int IFO_HELPER_SetFilms(void *_p,int FilmNumber);
int IFO_HELPER_GetDuration(void *_p);
char * IFO_HELPER_GetPalette(void *_p);
long long IFO_HELPER_GetFileSize(void *_p);
int IFO_HELPER_GetCurFilmsNum(void *_p);

//video
char *IFO_HELPER_GetVideoCodec(void *_p);
char *IFO_HELPER_GetTVSystem(void *_p);
int IFO_HELPER_GetResolution(void *_p,int *Width,int *Height);
int IFO_HELPER_GetAspectRatio(void *_p,int *ARw,int *ARh);
int IFO_HELPER_GetFrameRate(void *_p,int *fps);
int IFO_HELPER_GetCurVideoNum(void *_p);
//auido
int IFO_HELPER_GetNumberAudioTrack(void *_p);
int IFO_HELPER_SetAudioTrack(void *_p,int AudioNumber);
int IFO_HELPER_GetAudioInfo(void *_p,int *SampleRate,int *Channels,int *BPS);
char *IFO_HELPER_GetAudioCodec(void *_p);
char *IFO_HELPER_GetAudioLanguage(void *_p,int num);
char *IFO_HELPER_GetCurAudioLanguage(void *_p);
int IFO_HELPER_GetCurAudioNum(void *_p);
int IFO_HELPER_GetCurAudioID(void *_p);
char *IFO_HELPER_GetAudioOrgLang(void *_p,int num);

//sub picture
int IFO_HELPER_GetNumberSubPictureTrack(void *_p);
int IFO_HELPER_SetSubPictureTrack(void *_p,int SubNumber);
char *IFO_HELPER_GetSubPictureLanguage(void *_p,int num);
char *IFO_HELPER_GetCurSubPictureLanguage(void *_p);
int IFO_HELPER_GetCurSubPictureNum(void *_p);
char *IFO_HELPER_GetSubPictureOrgLang(void *_p,int num);
int IFO_HELPER_GetCurSubPictureID(void *_p);

//vob file
int IFO_HELPER_GetNumberVobFile(void *_p);
int IFO_HELPER_SetVobFile(void *_p,int VobNumber);
char *IFO_HELPER_GetVobFileName(void *_p);
int IFO_HELPER_GetCurVobNum(void *_p);
int IFO_HELPER_GetCurVobInfo(void *_p,int *duration,int *start,int *end,long long *filesize);
int IFO_HELPER_GetVobInfo(void *_p,int num,int *duration,int *start,int *end,long long  *filesize);

char *ifo_playback_rule(char *fullpath);


#endif
