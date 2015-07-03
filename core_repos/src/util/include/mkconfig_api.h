#ifndef __MKCONFIG_API_H__
#define __MKCONFIG_API_H__

#define MAX_FULL_PATH_LEN	(512)
#define MAX_NAME_LENGTH		(32)
#define CONFIG_MAGIC_NAME_LENGTH	(64)

#ifdef  AMP
/* fixme: 
 *   we need a uniform MAX_FILE_NUM definition, in order to compatiable with previous AMP releasel(1.01.x,1.02.x),
 *   so add the AMP protection and definie it to 6
 *
 */
#define MAX_FILE_NUM		(6)
#else
#define MAX_FILE_NUM		(20)
#endif
#define BUF_SIZE                (1024)

#define WMDRM_LOCK_FILE    	"/tmp/wmdrm_lock"
#define WMDRM_DIR		"/tmp/drm"
#define SECURESTORE1		4*1024*1024		// CONF_MTD_IMAT_PARTITION offset from 4M
#define SECURESTORE2		10*1024*1024		// CONF_MTD_IMAT_PARTITION offset from 10M

#define LICENSE_FILENAME	"sigma.hds"

typedef enum
{
        MKCONFIG_READ_CONFIG=0,
        MKCONFIG_READ_CONFIG_MIRROR=1,
        MKCONFIG_READ_CONFIG_FAIL=2
}MKCONFIG_READ;

typedef struct CFILE { 
	char filename[MAX_NAME_LENGTH];
	int size;
} CFILE;

typedef struct CONFIG_HEADER { 
	union { 
		struct { 
			char magicname[MAX_NAME_LENGTH];
			char dirname[MAX_NAME_LENGTH];
			CFILE sfile[MAX_FILE_NUM];
			unsigned long crc;
			int id; /* use to find the latest conf, if you have 2 conf*/
		} s;
		unsigned char unused[1024];
	} u;
} CONFIG_HEADER;

typedef struct CONFIG_FILES_HEADER { 
	char magicname[CONFIG_MAGIC_NAME_LENGTH];
	char type; 		/* type of header format, it is used for distinguish with older header format.*/
	char version;		/* version of header format */
	unsigned long crc;
	int id;			/* use to find the latest conf, if you have 2 conf*/
	int filecounts;
	int fullsizes;
	unsigned char reserved[508];
} CONFIG_FILES_HEADER;

typedef struct CONFIG_FILE_INFO { 
	char filename[MAX_FULL_PATH_LEN];
	int size;
} CONFIG_FILE_INFO;


int mkconfig_translate_config_dir_to_file (char *i_dir, char *o_filename, char *o_filenmae_mirror, char *product, char *version);
int mkconfig_translate_file_to_config_dir (char *i_filename, char *i_filename_mirror, char *product, char *version);
int mkconfig_translate_file_to_config_dir_old (char *i_filename, char *i_filename_mirror, char *product, char *version);
int mkconfig_translate_config_dir_to_secure_store (char *i_dir, char *o_filename, unsigned long write_offset, char *product, char *version); 
int mkconfig_translate_secure_store_to_config_dir (char *i_filename, unsigned long read_offset, char *product, char *version);
int mkconfig_is_old_config_files_header(char *i_filename);
int checkCRC(char *config_file, unsigned long offset);
#ifdef DEBUG
void dump_file_content (char *filename);
#endif
#endif
