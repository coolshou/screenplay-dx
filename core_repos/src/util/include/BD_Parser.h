#ifndef _BD_PARSER_H_
#define _BD_PARSER_H_

/*
 *	purpose : check the file is in the BD or not
 *	arguments:
 *		1) the filename (Ex: /abc/cde/BDMV/STREAM/xxxxx.m2ts)
 *	return:
 *		1) return the path when this file is in the BD
 *			Ex: /abc/cde
 *		2) return NULL when this file is not in the BD
 *	remarks:
 *		the caller should free the return pointer when the pointer is not NULL
 *
 */
char* BD_Parser_CheckFile(const	char *filename);

/*
 *	purpose : get the movie filename  in the BD
 *	arguments:
 *		1) the BD path (Ex: /abc/cde)
 *		2) get the filesize of movie file
 *	return:
 *		1) it is the BD , return the max filesize filename
 *			Ex: /abc/cde/BDMV/STREAM/00019.m2ts
 *		2) it is not BD, return NULL
 *	remarks:
 *		1) we will scan the xxxx/BDMV/STREAM/ path to get the filename with max filesize.
 *		2) the caller should free the return pointer when the pointer is not NULL
 *
 */
char* BD_Parser_GetMaxSizeFile(const char *path,long long int *filesize);

/*
 *	purpose : use max fileszie filename to get whole movie
 *	arguments : max filesize filename
 *	return :
 *		return the private data
 *	remarks:
 *		we use the same pmt(the same pid) to guess the whole movie
 *
 */
void *BD_Parser_Guess_Max_PlayList_Init(const char *filename);

/*
 *	purpose : destroy private data
 *
 */
void BD_Parser_Guess_Max_PlayList_UnInit(void *_pdata);

/*
 *	purpose : dump the info. of private data
 */
void BD_Parser_Guess_Max_PlayList_Dump(void *_pdata);

/*
 *	purpose : get duration of whole movie
 */
int BD_Parser_Guess_Max_PlayList_GetDuration(void *_pdata);
/*
 *	purpose : get total filesize of whole movie
 */
long long int BD_Parser_Guess_Max_PlayList_GetTotalFileSize(void *_pdata);
/*
 *	purpose : get first filename in the whole movie
 */
char* BD_Parser_Guess_Max_PlayList_GetFirstFileName(void *_pdata);
/*
 *	purpose : get prev filename 
 */
char* BD_Parser_Guess_Max_PlayList_GetPrevFileName(void *_pdata);
/*
 *	purpose : get next filename 
 */
char* BD_Parser_Guess_Max_PlayList_GetNextFileName(void *_pdata);
/*
 *	purpose : get time then get which filename with that seek_time
 *	arguments :
 *		1) private data
 *		2) seek time (second)
 *		3) return the position where we should seek to according seek_time
 */
char* BD_Parser_Guess_Max_PlayList_SearchFileName(void *_pdata,int seek_time,long long int *pos);
/*
 *	purpose : get the duration of current playing file
 */
long long int BD_Parser_Guess_Max_PlayList_GetCurrentFileSize(void *_pdata);
#endif //_BD_PARSER_H_
