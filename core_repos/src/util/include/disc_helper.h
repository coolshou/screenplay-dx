#ifndef _DISC_HELPER_H_
#define _DISC_HELPER_H_

typedef enum {
	DISC_HELPER_ERROR=-1,
	DISC_HELPER_NONE=0,
	DISC_HELPER_FOUND
}disc_helper_status;

typedef enum{
	DISC_HELPER_TYPE_NONE,
	DISC_HELPER_TYPE_VCD,
	DISC_HELPER_TYPE_DVD,
	DISC_HELPER_TYPE_BD
}dischelper_disc_type;

typedef struct{
	dischelper_disc_type disctype;
	char *streamfile;
	char *label;
	int   flag;
}disc_helper_info;

/* Use Strong Check Rule
  Ex: if set
  0  VIDEO_TS/VTS_00_1.VOB
  X  /VTS_00_1.VOB
  X  /STREAM/00001.m2ts
  0  /BDMV/STREAM/00001.m2ts 
*/
#define DISC_HELPER_FLAG_STRONG_CHECK  0x0001



/* Caller Must Free the return result*/
disc_helper_status dischelper_rip_detection(char *fullpath,int flag,disc_helper_info *output);
char *dischelper_rip_get_title(const char *fullpath);
char *dischelper_rip_get_disc_root_path(const char *fullpath);
void dischelper_destory_info(disc_helper_info *info);
#endif
