#ifndef _PROC_PIPE_H_
#define _PROC_PIPE_H_

//#include <linux/config.h>
#include <linux/fs.h>


//following depends on linux kernel menuconfig.
#ifdef CONFIG_KERNEL_PROC_PIPE
	#define KERNEL_PIPE
	#ifdef CONFIG_KERNEL_DIRECT_PROC_PIPE
		#define NO_KERNEL_PIPE_THREAD
	#endif
#endif


//#define KERNEL_PIPE
//#define NO_KERNEL_PIPE_THREAD
#ifndef KERNEL_PIPE
#undef NO_KERNEL_PIPE_THREAD   // it's always included in KERNEL_PIPE.
#endif


#ifdef KRSA
#include "rsaref.h"
#endif


#define BUFF_SIZE (16*1024)
#define CONTEXT   (2)

//this define ioctl command of proc_pipe
#define P_IOCMAGIC	'k'
#define P_IOCRESET	_IO (P_IOCMAGIC, 0)
#define P_IOCSIZE	_IOW(P_IOCMAGIC, 1, size_inf)
#define P_IOCREVS	_IOW(P_IOCMAGIC, 2, int)
#define P_IOCTELL	_IOR(P_IOCMAGIC, 3, tell_inf)
#define P_IOCRELS	_IO (P_IOCMAGIC, 4)
#define P_IOCPRED	_IOW(P_IOCMAGIC, 5, size_t)
#ifdef KRSA
#define P_IOCKRSA	_IOW(P_IOCMAGIC, 6, krsa_arg)
#endif

#define P_IOCPIPESTOP	 _IO (P_IOCMAGIC, 8)
#define P_IOCPIPESTART	 _IOW(P_IOCMAGIC, 9, kpipe_setup)

#define P_IOCPIPETYPE		_IOW(P_IOCMAGIC, 10, int)
#define P_IOCCLEAR  _IO (P_IOCMAGIC, 11)
#define P_IOCBREAD	_IO (P_IOCMAGIC, 12)

//our errno of seek
#define P_ESEEK	(1024)

/* Inside proc_pipe, all kinds of media have been arranged to be
 * a sequential space of media + index. But it provides an interface
 * that includes two independent proc files, such as "a.mda" and "a.idx",
 * in case that some mpeg video whose media part and index part are
 * splited into two different files.
 *
 * Corresponsively, we need know "mdas" that represents the size of
 * "a.mda", and "idxs" that represents the size of "a.idx".
 *
 * However, for the performance of playing avi file, there is a "dats"
 * that means the actual size of media data, because the media part
 * and index part of avi are integrated into a single file. Here, "mdas"
 * is the size of whole avi file, and "dats" is te size of media part
 * that should be less than "mdas".
 *
 *
 * For those audio or image who has no index part, we should set:
 *        dats = media file size;
 *        idxs = 0;
 *        mdas = media file size;
 *
 * For those general mpeg video whose media part and index part are
 * saved in two different files, we should set:
 *        dats = media file size;
 *        idxs = index file size;
 *        mdas = media file size;
 *
 * For optimizing avi file, we should set:
 *        dats = size of media part;
 *        idxs = size of index part;
 *        mdas = the whole file size;
*/
typedef struct size_inf {
	loff_t dats;
	loff_t idxs;
	loff_t mdas;
} size_inf;

typedef struct tell_inf {
	loff_t seek;
	size_t size;
} tell_inf;
#ifdef KRSA
typedef struct krsa_arg {
	unsigned char* buf;	//input and output buffer
	unsigned int*  len;	//input and output buffer len
	R_RSA_PRIVATE_KEY key;
} krsa_arg;
#endif
#ifdef KERNEL_PIPE
typedef  struct kpipe_setup{
//	char addr[16];
	loff_t size;
	char *path;	//http file
	int pathSize;
	char host[16];
	char procfile[16];	//proc file.
	short port;
	int	protection;
	char*	sessionid;
	int 	sessionidSize;

	int  type;
	int  nums;
	int index;	// a.dma or b.dma .
	int pathIndex; //dma or index.
} kpipe_setup;
typedef kpipe_setup http_setup;

#define		PIPE_CL			0
#define		PIPE_KP			1
#define 	PIPE_FILE		2


#define		PIPE_TYPE_USER_THREAD				0
#define 	   PIPE_TYPE_KERNEL_THREAD 			1
#define 		PIPE_TYPE_KERNEL_DIRECT				2

#endif

#endif
