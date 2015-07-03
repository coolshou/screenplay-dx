#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__

extern int OS_touch(const char *path);
extern int OS_GetDirectoryChildCount(const char *path);
extern int OS_fileexist(const char *name);
extern void OS_SaveConfig();

#endif//__DIRECTORY_H__
