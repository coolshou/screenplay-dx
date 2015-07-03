#ifndef __MYDEBUG_H__
#define __MYDEBUG_H__

#include "Target.h"

#include  <stdlib.h>
#include  <string.h>

#define   DBG_MSG_VERBOSE       "VERBOSE"
#define   DBG_MSG_FATAL         "FATAL"
#define   DBG_MSG_WARNING       "WARNING"
#define   DBG_MSG_STDERR        "stderr"
#define   DBG_MSG_STDOUT        "stdout"

#ifdef  CONF_MYDEBUG
#define   DBGSTART(argc, argv)           mydbgstart(argc, argv)
#define   DBGEND()                       mydbgend(__FILE__, __LINE__)
#define   DBGPRINTF(x)                   mydbgprintf(__FILE__, __LINE__, mydbginfor x)
#define   DBGDATA(dbgname, data, len)    mydbgdata(__FILE__, __LINE__, dbgname, data, len)
#define   DBGSTRDATA(dbgname, data, len) mydbgstrdata(__FILE__, __LINE__, dbgname, data, len)

void   mydbgstart(int argc, char * argv[]);
void   mydbgend(const char * fname, int lineno);
void   mydbgprintf(const char * fname, int lineno, char * dbgstr);
char * mydbginfor(const char * dbgname, const char * format, ...);
void   mydbgdata(const char * fname, int lineno,
		 const char * dbgname, const void * data, int len);
void   mydbgstrdata(const char * fname, int lineno,
		    const char * dbgname, const void * data, int len);
#else

#define   DBGSTART(argc, argv)   ((void)0)
#define   DBGEND                 ((void)0)
#define   DBGPRINTF(x)           ((void)0)
#define   DBGDATA(dbgname, data, len)     ((void)0)
#define   DBGSTRDATA(dbgname, data, len)  ((void)0)

#endif

#endif  /* __MYDEBUG_H__ */

