#ifndef __DEBUG_IO_H__
#define __DEBUG_IO_H__

extern void redirect_stdout(char *filename);
extern void redirect_stdout_back(void);

extern void redirect_stderr(char *filename);
extern void redirect_stderr_back(void);

#endif
