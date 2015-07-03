#include "Target.h"

#define _LARGEFILE64_SOURCE 1
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#ifndef __MYMALLOC_H
#define __MYMALLOC_H

#ifdef CONF_MALLOC_DEBUG
#ifndef IS_MYMALLOC
#define malloc(s) mymalloc(s,__FILE__,__LINE__)
#define calloc(s,t) mycalloc(s,t,__FILE__,__LINE__)
#define free(s) myfree(s,__FILE__,__LINE__)
#define strdup(s) mystrdup(s,__FILE__,__LINE__)
#define realloc(s,size) myrealloc(s,size,__FILE__,__LINE__)

void *mymalloc(size_t size, const char *file, int line);
void *myfree(void *ptr, const char *file, int line);
void *mystrdup(const char *s, const char *file, int line);
void *myrealloc(void *ptr, size_t size, const char *file, int line);
#endif // IS_MYMALLOC
#endif // CONF_MALLOC_DEBUG

#define MYMALLOC_NORMAL 1
#define MYMALLOC_UNDERFLOW_PROTECTION 2
#define MYMALLOC_OVERFLOW_PROTECTION 3

void mymalloc_init(void);

#endif
