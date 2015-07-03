#ifndef _DEVICE_H_
#define _DEVICE_H_

#ifndef __KERNEL__
#define __KERNEL__
#endif
#ifndef MODULE
#define MODULE
#endif
#define __NO_VERSION__

#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/errno.h>
#include <linux/fcntl.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <asm/uaccess.h>
#include <asm/io.h>
//#include <net/sock.h>
#define __PIPE_SELECT__  /* define macro for support select op*/
#define DOUBLE_DEV


#undef PDEBUG
#ifdef P_DEBUG
#  define PDEBUG(fmt, args...) printk( KERN_ERR fmt, ## args)
#else
#  define PDEBUG(fmt, args...) /* not debugging: nothing */
#endif

#define BLOCK_NUM	(32)
#define PRE_READ	(2*BUFF_SIZE)

#define DEV_FULL	(-1)
#define DEV_SEEK	(-2)
#define DEV_FAULT	(-3)

#define SEEK(ct)	((ct)->seek)
#define SIZE(ct)	((ct)->size)
#define BPOS(ct)	((ct)->bpos)
#define EPOS(ct)	((ct)->epos)
#define HOTP(ct)	((ct)->hotp)
#define REVS(ct)	((ct)->reverse)
#define W_ABLE(ct)	((ct)->w_able)
#define R_ABLE(ct)	((ct)->r_able)

typedef struct block block;

typedef struct context {
	pid_t	pid;
	loff_t	seek;		//seek position
	size_t	size;		//needed size
	loff_t	bpos;		//begin position of W&R
	loff_t	epos;		//end position of W&R
#ifdef KERNEL_PIPE
	loff_t	pos;	//record current position.
#endif
	block*	hotp;		//hot point
	int reverse;		//reverse pre_read
	int w_able, r_able;
	unsigned long life;
} context;

struct block {
	char	buff[BUFF_SIZE];
	loff_t	position;	//position of the buff in the file
	size_t	a_size;		//available size in the buff
	block*	prev;
	block*	next;
};

typedef struct media_dev {
	block	block_pool[BLOCK_NUM];
	block*	head;		//list of buff ordered by position
	block*	tail;
	block*	free;		//list of freed buff
	context* ctp;
	size_t  pred;		//pre read len
} media_dev;

typedef struct pipe_file {
	struct semaphore   semapho;
	wait_queue_head_t  r_queue;
	wait_queue_head_t  w_queue;
#ifdef	CONFIG_PROC_PIPE_64_BITS_SUPPORT
	loff_t	mda_size;
	loff_t	idx_size;
#endif	// CONFIG_PROC_PIPE_64_BITS_SUPPORT
	struct proc_dir_entry* mda;
	struct proc_dir_entry* idx;
#ifdef __PIPE_SELECT__
    int       r_poll;
    loff_t    r_pos;
#endif
	media_dev device;
	context ct[CONTEXT+1];
	int release, writers;
} pipe_file;

#ifdef KERNEL_PIPE  
#define A_INDEX 0
#define B_INDEX 1
#define END_INDEX 2

#define MEDIA_PATH_NUM 0
#define INDEX_PATH_NUM	1
#define END_PATH_NUM 	2

#define  THREAD_NUM	3

#define HTTP_MALLOC(x)	kmalloc(x,GFP_ATOMIC)
#define	HTTP_FREE(x)	kfree(x)


typedef struct http_thread {
	kpipe_setup	pipeSetup[END_PATH_NUM];
	int			pids[THREAD_NUM];
	int 		index;	//a.dma or b.dma.
	int			type;	//close or keep-alive or local file.
} http_thread;

typedef http_thread pipe_thread;

typedef struct http_manage {
	wait_queue_head_t wq;
	struct semaphore   semaphore;
	pipe_thread  	threads[END_INDEX];
	atomic_t		 nums;
	atomic_t		 starts[END_INDEX][END_PATH_NUM];
	atomic_t		 stops[END_INDEX];
	volatile char    change;
} http_manage;

typedef http_manage pipe_manage;
	
	
void dev_freeBuff(media_dev *device,struct block *buff);
struct block *dev_getBuff(media_dev *device);
int dev_insertBuff(media_dev *device,loff_t *pos,struct block *buff,size_t *left,context *ct);
	
extern int proc_released(int index);
extern context *proc_context(int index, int pathIndex);
extern int proc_tell(int index,int pathIndex,loff_t *seek,size_t *size,context *ct);
extern struct block *proc_getBuff(int index,int pathIndex);
extern int proc_freeBuff(int index,int pathIndex, struct block *buff);
extern int proc_insertBuff(int index,int pathIndex,struct block *buff,loff_t pos, size_t len,context *ct);

#define H_DEBUG

#ifdef H_DEBUG
#  define HDEBUG(fmt, args...) if(pipe_debug) printk( KERN_ERR fmt, ## args)
#else
#  define HDEBUG(fmt, args...) /* not debugging: nothing */
#endif

extern int pipe_debug;

extern pipe_manage pipeManage;

#ifdef NO_KERNEL_PIPE_THREAD

#define SOCK_POS_MAGIC		0xca7843ac

typedef struct sock_pos_s {
	int 		magic;
	loff_t 	pos;
	struct socket *sock;
	int 		leftLen;
	char 	*leftPos;
	char		*request;
} sock_pos_t;
#endif

#endif	      //end ifdef KERNEL_PIPE        

block* dev_search(media_dev* device, loff_t pos, block* hotp);
void dev_flush(media_dev* device);
int  dev_read (media_dev* device, loff_t* pos, char* data, size_t* left, context* ct);
int  dev_write(media_dev* device, loff_t* pos, const char* data, size_t* left, context* ct);


#endif
