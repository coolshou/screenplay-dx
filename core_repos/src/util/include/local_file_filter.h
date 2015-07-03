/* 
 * vim:cindent:ts=8:
 */
#ifndef __LOCAL_FILE_FILTER__H
#define __LOCAL_FILE_FILTER__H

struct local_file_media_info {
	char file_extension[128];
	char mime_type[128];
	char protinfo[128];
};

extern struct local_file_media_info local_media_info_audio[];
extern struct local_file_media_info local_media_info_image[];
extern struct local_file_media_info local_media_info_video[]; 
extern struct local_file_media_info local_media_info_bt_seed[]; 
extern struct local_file_media_info local_media_info_playlist[];
extern struct local_file_media_info local_media_info_flash[];  

#define LOCAL_FILTER_FILE_ALL			0xffffffff
#define LOCAL_FILTER_FILE_CONTAINER		0x00000001
#define LOCAL_FILTER_FILE_VIDEO			0x00000002
#define LOCAL_FILTER_FILE_AUDIO			0x00000004
#define LOCAL_FILTER_FILE_IMAGE			0x00000008
#define LOCAL_FILTER_FILE_BT_SEED		0x00000010
#define LOCAL_FILTER_FILE_PLAYLIST		0x00000020
#define LOCAL_FILTER_FILE_FLASH			0x00000040

#define LOCAL_FILTER_FILE_SYSTEM_ALL		0xffffffff
#define LOCAL_FILTER_FILE_SYSTEM_NONE		0x00000000
#define LOCAL_FILTER_FILE_SYSTEM_FAT		0x00000001
#define LOCAL_FILTER_FILE_SYSTEM_NTFS		0x00000002
#define LOCAL_FILTER_FILE_SYSTEM_HFS		0x00000004


enum lcb_file_type{
	FILE_TYPE_UNKNOW,
	FILE_CONTAINER,
	FILE_PLAYLIST,
	FILE_AUDIO,
	FILE_IMAGE,
	FILE_VIDEO,
	FILE_BT_SEED,
	FILE_FLASH,
};

struct local_file_data
{
	enum lcb_file_type file_type;
	unsigned short index;	
	unsigned long long size;
	unsigned long long ino;
	time_t atime;
	time_t mtime;
	time_t ctime;
};

int local_file_filter(char *file, unsigned int filter_type, struct local_file_data *file_data, int simple);
int local_file_filter_with_file_system(char *file, unsigned int filter_type, struct local_file_data *file_data, unsigned int file_system, int simple);
int local_file_filter_is_visible(char *file, unsigned int file_system);
int local_file_get_extension_by_minetype(char *minetype, char *ext);

#endif
