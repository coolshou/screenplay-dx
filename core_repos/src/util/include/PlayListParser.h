#ifndef PLAYLISTPARSER_H
#define PLAYLISTPARSER_H

#if defined  __cplusplus
extern "C"      {
#endif


#ifdef _POSIX
#include <sys/time.h>
#include <unistd.h>
#include <netinet/in.h>
typedef off_t seek_unit;
#define user_lseek lseek
#endif

#ifdef WIN32
#include <io.h>
typedef	__int64 seek_unit;
#define user_lseek _lseeki64
#define strcasecmp stricmp
#define strncasecmp strnicmp
#endif

#define PL_MAX_SAVE_URL 10
#define LINE_BUF_MAX_SIZE 1024

#ifndef CONF_LOCAL_PLAYLIST_PARSE_BUFFER_SIZE
#define CONF_LOCAL_PLAYLIST_PARSE_BUFFER_SIZE 100*1024
#endif

enum PLParserId {
	PLParserId_NONE,
	PLParserId_M3U,
	PLParserId_PLS,
	PLParserId_ASX,
	PLParserId_REF,  //Reference
	PLParserId_WPL,
	PLParserId_iTunes,
};

enum PLParserReturn {
	PLParserReturn_Error	= -1,
	PLParserReturn_OK		= 0,
	PLParserReturn_End		= 1,
};

typedef struct _PLInfo {	
	int duration; //second
	char *title;
	char *author;
	int num_sub_items;
	char *url[PL_MAX_SAVE_URL];  //I do not want to use another structure, so I just use multi-url to save the url(s)
	struct _PLInfo *next;
} PLInfo;

typedef struct _PLHandler PLHandler;


typedef struct _PLParser {
	const char *name;
	const char *long_name;
	const char *mime_type;
	const char *reg_exts; // Registered supporting extention name 
	int id;
	int priv_data_size;
	void *priv_data;
	int (*init)(PLHandler *,void *priv_data);
	int (*check)(PLHandler *,void *priv_data,char *buf,int size); //use 16bytes to check which format playlist format
	int (*extcheck)(PLHandler *,void *priv_data,const char *extname,const char *reg_exts,char *buf,int size); //use extension name as checking criteria
	int (*parser)(PLHandler *,void *priv_data,char *buf,int size);
	int (*parserfile)(PLHandler *,void *priv_data,int fd,int size);
	int (*uninit)(PLHandler *,void *priv_data);
	struct _PLParser *next;
}PLParser;

struct _PLHandler {
	int num_items;
	int cur_item; //0 means the first
	int parser_id;
	PLParser *pParser;
	PLInfo	*pInfo;
	PLInfo	*pCurInfo;
	int (*User_Read) (int fd,void *buf,unsigned int size); //for PlayListParser_Parse_File
};

/*
	purpose: to create a playlist parser handler
	remarks:
		we will register all playlist parser here
		when success we return a pointer otherwise return NULL
*/
void *PlayListParser_Init(void); 

/*
	purpose: to re-init all parser
	remarks:
		we will call uninit / init of all registered parser
*/
int PlayListParser_ReInit(void *ptmp); 

/*
	purpose : to un init the parser handler
	remarks:
		
*/
int PlayListParser_UnInit(void *ptmp);

/*
	purpose : use a few bytes (16bytes) to detect which parser we should use
	remarks:
		return percentage, if return 100 means we get correct parser
*/
int PlayListParser_Check(void *ptmp,char *buf,int size, char *filename);

/*
	purpose : use all data buffer to parse/get all informance
*/
int PlayListParser_Parse(void *ptmp,char *buf,int size);

/*
	purpose : use a fd to parse/get all informance
	remarks:
		we will use User_Read to read data
*/
int PlayListParser_Parse_File(void *ptmp,int fd,int max_parse_size);

/*
	purpose : set read function
*/
int PlayListParser_Set_ReadCPFunction(void *ptmp,int(*User_Read) (int fd,void *buf,unsigned int size));

/*
	purpose : to get how many songs in the playlist file.
*/

int PlayListParser_Get_NumberSongs(void *ptmp);

/*
	purpose : to get how many urls in the song
	remarks:
			the value of num_song is begin with 1
			when we want to get url, we should run this function firstly
			this function will get correct url structure, 
			then other functions (ex: PlayListParser_Get_URL) will use it~
*/

int PlayListParser_Get_NumberUrls(void *ptmp,int num_song);

/*
	purpose : to get url
	remarks:
			the value of num_url is begin with 1
			we shold run PlayListParser_Get_NumberSongs before we call this function.
*/
int PlayListParser_Get_URL(void *ptmp,int num_url,char **url);

/*
	purpose : to get duration
	remarks:
			we shold run PlayListParser_Get_NumberSongs before we call this function.
			
*/
int PlayListParser_Get_Duration(void *ptmp,int *duration);
/*
	purpose : to get author
	remarks:
			we shold run PlayListParser_Get_NumberSongs before we call this function.
*/
int PlayListParser_Get_Author(void *ptmp,char **Author);
/*
	purpose : to get title
	remarks:
			we shold run PlayListParser_Get_NumberSongs before we call this function.

*/
int PlayListParser_Get_Title(void *ptmp,char **Title);

int PlayListParser_GetLine(char *inBuf,int inBufSize,char *outBuf,int outBufSize);




#if defined  __cplusplus
};
#endif

#endif
