#ifndef __NEW_HTTP_WRAPPER_H__
#define __NEW_HTTP_WRAPPER_H__

#include <sys/types.h>


/**
 * A refined http wrapper 
 */

#include "url.h"
#include "util.h"
//#include "httpwrapper.h"

#define HTTP_ERROR_INVALID_SOCKET -1
#define	HTTP_ERROR_READ_TIMEOUT -2

/**
 * The HttpSeek works with HTTP servers that understand HTTP/1.1 and 
 * ftp servers that support  the  REST command.
 */
typedef struct {
	int len;
	char buf[BUFSIZE]; 
}HTTPDATA,*LPHTTPDATA;

int HttpInit(UrlResource **rsrc, char *url);
int HttpOpen(UrlResource *rsrc);
int HttpResume(UrlResource *rsrc, loff_t offset);
int HttpRead(UrlResource *rsrc, LPHTTPDATA data);
int HttpSeek(UrlResource *rsrc, loff_t offset);
int HttpClose(UrlResource *rsrc);
int HttpDestroy(UrlResource *rsrc);

/**
 * redundant wrapper for DataSource framwork 
 */
/*
static int DSHttpInit(UrlResource **r, struct StreamInstance *si) {
	return  HttpInit(r, si->Uri);
}

static int DSHttpOpen(UrlResource *r, struct StreamInstance *si) {
	return HttpOpen(r);
}

static int DSHttpClose(UrlResource *r, struct StreamInstance *si) {
	return HttpClose(r);
}

*/

#endif
