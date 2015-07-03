#include <linux/slab.h>
#include "proc_pipe.h"
#include "device.h"
#ifdef KRSA
#include "rsa.h"
#endif

#define RQ(i)           ((pipes[i]).r_queue)
#define WQ(i)           ((pipes[i]).w_queue)
#define SEMAPHO(i)      ((pipes[i]).semapho)
#define RELEASE(i)      ((pipes[i]).release)
#define WRITERS(i)      ((pipes[i]).writers)

#define Wait_Event(a, b) do{if(wait_event_interruptible(a,b)) return -ERESTARTSYS;}while(0)
#define Down(i)          do{if(down_interruptible(&(SEMAPHO(i)))) return -ERESTARTSYS;}while(0)
#define Up(i)            do{up(&(SEMAPHO(i)));}while(0)

#ifdef DOUBLE_DEV
static pipe_file pipes[2];
#else
static pipe_file pipes[1];
#endif

#ifdef 	KERNEL_PIPE
#include <linux/sched.h>
pipe_manage 	pipeManage;

int pipeType[2]={PIPE_TYPE_KERNEL_THREAD,PIPE_TYPE_KERNEL_THREAD};
extern int defaultPipeType;

#ifdef NO_KERNEL_PIPE_THREAD
int p_close_createAndRead(sock_pos_t *sp,kpipe_setup *param,char *buf,size_t count, loff_t *f_pos);
ssize_t p_sock_read(int index, struct file *filp, char *buf, size_t count, loff_t *f_pos);


#endif

#endif

static inline context* getct(int index, loff_t pos)
{
	pipe_file *pp = &(pipes[index]);
	int i, oldest = 0;
	unsigned long life = 0xFFFFFFFF;

	if(pos >= ((pp->ct)[CONTEXT]).bpos) return &((pp->ct)[CONTEXT]);

	for(i=0; (i<WRITERS(index))&&(((pp->ct)[i]).pid!=current->pid); i++) {
		if(((pp->ct)[i]).life < life) {
			oldest = i;
			life = ((pp->ct)[i]).life;
		}
	}
	if(i == WRITERS(index)) {
		i = oldest;
		((pp->ct)[i]).pid = current->pid;
	}
	((pp->ct)[i]).life = jiffies;

	return &((pp->ct)[i]);
}
static ssize_t p_read(int index, struct file* filp, char* buf, size_t count, loff_t* f_pos)
{
	context *ct = NULL;
	size_t left;
	int ret;

	if(RELEASE(index)) return -ENXIO;

	Down(index);

	ct = getct(index, *f_pos);
	if(*f_pos >= EPOS(ct)) {Up(index); return 0;}

	count = (*f_pos+count>EPOS(ct))?(EPOS(ct)-(*f_pos)):(count); left = count;

	#ifdef KERNEL_PIPE
	#ifdef NO_KERNEL_PIPE_THREAD
		if(pipeType[index] == PIPE_TYPE_KERNEL_DIRECT) {
	 		Up(index);
			return p_sock_read(index,filp,buf,count,f_pos);
		}
	#endif
	#endif
	
	while(1) {
		ret = dev_read(&((pipes[index]).device), f_pos, buf+(count-left), &left, ct);

#ifdef __PIPE_SELECT__
        pipes[index].r_pos = *f_pos+(count-left);
#endif
		if(ret == DEV_FAULT) {Up(index); return -EFAULT;}

		if(!W_ABLE(ct)) {
			W_ABLE(ct) = 1;
			wake_up_interruptible(&(WQ(index)));
		}
		if(left>0) {
			if(filp->f_flags & O_NONBLOCK) {
#ifdef __PIPE_SELECT__
                pipes[index].r_poll = 0;
#endif
				Up(index);
				if(count == left) return -EAGAIN;
				break;
			}
			R_ABLE(ct) = 0; Up(index);
			PDEBUG("<%d>: need more data, sleep\n", current->pid);
			Wait_Event(RQ(index), RELEASE(index)||R_ABLE(ct));
#ifdef	CONFIG_PROC_PIPE_64_BITS_SUPPORT
			if (*f_pos >= pipes[index].mda_size )
#else	// CONFIG_PROC_PIPE_64_BITS_SUPPORT
			if (*f_pos >= pipes[index].mda->size)
#endif	// CONFIG_PROC_PIPE_64_BITS_SUPPORT
				return (count - left);
			if(RELEASE(index)) return -ENXIO;
			Down(index);
		}
		else {Up(index); break;}
	}
	return (count - left);
}
static ssize_t p_write(int index, struct file* filp, const char* buf, size_t count, loff_t* f_pos)
{
	context *ct = filp->private_data;
	size_t left = count, wrt;
	int ret;

	if(RELEASE(index)) return count;

	while(1) {
		Down(index);
		wrt = left;
		ret = dev_write(&((pipes[index]).device), f_pos, buf+(count-left), &left, ct);

		if(ret == DEV_FAULT) {Up(index); return -EFAULT;}

#ifdef __PIPE_SELECT
        pipes[index].r_poll = 1;
#endif
		if(wrt) {
			R_ABLE(ct) = 1;
			if(ret == DEV_SEEK) {
				wake_up_interruptible_sync(&(RQ(index)));
			}
			else {
				wake_up_interruptible(&(RQ(index)));
			}
		}
		if(ret == DEV_SEEK) {Up(index); return -P_ESEEK;}

		if(ret == DEV_FULL) {
			W_ABLE(ct) = 0; Up(index);
			PDEBUG("<%d>: device full, sleep, left %d\n", current->pid, (int)left);
			Wait_Event(WQ(index), RELEASE(index)||W_ABLE(ct));
			if(RELEASE(index)) return count;
			continue;
		}
		Up(index);

		if(left <= 0) break;
	}
	return count;
}

static int rcount=0;
static int p_open(int index, struct inode* inode, struct file* filp)
{
	int ret = 0;

	Down(index);
	rcount++;
//	printk("Proc pipe open %d times.\n",rcount);
	if(!(filp->f_mode & FMODE_READ) && (filp->f_mode & FMODE_WRITE)) {
		if(WRITERS(index) < CONTEXT) {
			filp->private_data = &((pipes[index].ct)[WRITERS(index)]);
			(WRITERS(index))++;
		}
		else if(((pipes[index].ct)[CONTEXT]).pid == 0) {
			filp->private_data = &((pipes[index].ct)[CONTEXT]);
			((pipes[index].ct)[CONTEXT]).pid = current->pid;
		}
		else ret = (-EFAULT);
	}
	Up(index);

	return ret;
}

static int p_release(int index, struct inode* inode, struct file* filp)
{
#ifdef __PIPE_SELECT__
    pipe_file *pp = &(pipes[index]);
#endif
#ifdef KERNEL_PIPE
#ifdef NO_KERNEL_PIPE_THREAD
	if (pipeType[index] == PIPE_TYPE_KERNEL_DIRECT) {
		sock_pos_t *sp=(sock_pos_t *)filp->private_data;
		if(sp && sp->magic==SOCK_POS_MAGIC) {
			if(sp->sock) {
				sock_release(sp->sock);
				sp->sock = NULL;
			}
			if(sp->request) {
				kfree(sp->request);
				sp->request = NULL;
				sp->leftLen = 0;
				sp->leftPos = NULL;
			}
			kfree(sp);
			filp->private_data=NULL;
		}
	}
#endif
#endif
	wake_up_interruptible(&(RQ(index)));
	wake_up_interruptible(&(WQ(index)));
#ifdef __PIPE_SELECT__
    pp->r_poll = 1;
    pp->r_pos = 0;
#endif
	rcount--;
	
	return 0;
}

static int p_ioctl(int index, struct inode* inode, struct file* filp, unsigned int cmd, unsigned long arg)
{
	context *ct = filp->private_data;
	pipe_file *pp = &(pipes[index]);
	tell_inf t_inf;
	size_inf s_inf;
#ifdef KRSA
	krsa_arg rsa;
	unsigned char *input = NULL, output[MAX_RSA_MODULUS_LEN];
	unsigned int inputlen = 0, outputlen = 0;
#endif
	int err = 0, ret = 0, i;

	if(!capable(CAP_SYS_ADMIN)) return -EPERM;

	if(_IOC_TYPE(cmd) != P_IOCMAGIC) return -ENOTTY;

	if(_IOC_DIR(cmd) & _IOC_READ) {
		err = !access_ok(VERIFY_WRITE, (void *)arg, _IOC_SIZE(cmd));
	}
	else if(_IOC_DIR(cmd) & _IOC_WRITE) {
		err = !access_ok(VERIFY_READ, (void *)arg, _IOC_SIZE(cmd));
	}
	if(err) return -EFAULT;

	Down(index);

	switch(cmd) {
	case P_IOCCLEAR:
		dev_flush(&(pp->device));
		for(i=0; i<=CONTEXT; i++) {
			((pp->ct)[i]).hotp = NULL;	
		}
		break;
	case P_IOCRESET:
		memset(pp->ct, 0, sizeof(context)*(CONTEXT+1));
#ifdef __PIPE_SELECT__
        pp->r_poll = 1;
        pp->r_pos = 0;
#endif
		for(i=0; i<=CONTEXT; i++) {
			((pp->ct)[i]).r_able = 1;
			((pp->ct)[i]).w_able = 1;
		}
		RELEASE(index) = 0; WRITERS(index) = 0;
		dev_flush(&(pp->device));
		(pp->device).ctp = pp->ct;
		(pp->device).pred = 2*BUFF_SIZE;
	#ifdef KERNEL_PIPE
		pipeType[index]=PIPE_TYPE_USER_THREAD;
	#endif
	
		break;
	case P_IOCSIZE:
		if(copy_from_user((char*)&s_inf, (char*)arg, sizeof(size_inf))) {
			ret = (-EFAULT); goto my_error;
		}
#ifndef	CONFIG_PROC_PIPE_64_BITS_SUPPORT
#ifndef CONFIG_PROC_PIPE_KERNEL_SUPPORT_64_BITS
		if(s_inf.mdas > 0xFFFFFFFFF || s_inf.idxs > 0xFFFFFFFF) {
			ret = (-EFAULT); goto my_error;
		}
#endif
		(pp->mda)->size = s_inf.mdas;
		(pp->idx)->size = s_inf.idxs;
#else	// !CONFIG_PROC_PIPE_64_BITS_SUPPORT
#if 0
		(pp->mda)->size = s_inf.mdas;
		(pp->idx)->size = s_inf.idxs;
#else
		(pp->mda)->size = 0; 
		(pp->idx)->size = 0;
#endif
		pp->mda_size = s_inf.mdas;
		pp->idx_size = s_inf.idxs;
#endif	// !CONFIG_PROC_PIPE_64_BITS_SUPPORT
		for(i=0; i<CONTEXT; i++) {
			((pp->ct)[i]).epos = s_inf.mdas;
		}
		((pp->ct)[CONTEXT]).bpos = s_inf.dats;
		((pp->ct)[CONTEXT]).epos = s_inf.dats + s_inf.idxs;
		((pp->ct)[CONTEXT]).seek = s_inf.dats;
		break;
	case P_IOCREVS:
		((pp->ct)[CONTEXT]).reverse = *((int*)arg);
		break;
	case P_IOCTELL:
		t_inf.seek = filp->f_pos;
		t_inf.size = (BPOS(ct))?(BUFF_SIZE):(SIZE(ct));
		if(copy_to_user((char*)arg, (char*)&t_inf, sizeof(tell_inf))) {
			ret = (-EFAULT); goto my_error;
		}
		break;
	case P_IOCRELS:
		RELEASE(index) = 1;
		wake_up_interruptible(&(RQ(index)));
		wake_up_interruptible(&(WQ(index)));
		break;
	case P_IOCPRED:
		(pp->device).pred = *((size_t*)arg);
		break;
#ifdef KRSA
	case P_IOCKRSA:
		if(copy_from_user((char*)&rsa, (char*)arg, sizeof(krsa_arg))) {
			ret = (-EFAULT); goto my_error;
		}
		if(!access_ok(VERIFY_READ, (void *)(rsa.len), sizeof(unsigned int))) {
			ret = (-EFAULT); goto my_error;
		}
		if(copy_from_user((char*)&inputlen, (char*)(rsa.len), sizeof(unsigned int))) {
			ret = (-EFAULT); goto my_error;
		}
		if(!(input = kmalloc(inputlen, GFP_KERNEL))) {
			ret = (-EFAULT); goto my_error;
		}
		if(!access_ok(VERIFY_READ, (void *)(rsa.buf), inputlen)) {
			ret = (-EFAULT); goto my_error;
		}
		if(copy_from_user((char*)input, (char*)(rsa.buf), inputlen)) {
			ret = (-EFAULT); goto my_error;
		}
		if(RSAPrivateBlock(output, &outputlen, input, inputlen, &(rsa.key))) {
			ret = (-EFAULT); goto my_error;
		}
		if(!access_ok(VERIFY_WRITE, (void *)(rsa.buf), outputlen)) {
			ret = (-EFAULT); goto my_error;
		}
		if(copy_to_user((char*)(rsa.buf), (char*)output, outputlen)) {
			ret = (-EFAULT); goto my_error;
		}
		if(!access_ok(VERIFY_WRITE, (void *)(rsa.len), sizeof(unsigned int))) {
			ret = (-EFAULT); goto my_error;
		}
		if(copy_to_user((char*)(rsa.len), (char*)&outputlen, sizeof(unsigned int))) {
			ret = (-EFAULT); goto my_error;
		}
		break;
#endif


	#ifdef KERNEL_PIPE
	case P_IOCPIPETYPE:
			{
				int val;

				get_user(val,(int *)arg);

				if(val<0) {
					ret= -EFAULT;
					break;
				}
				
				#ifdef NO_KERNEL_PIPE_THREAD
					if(val<=PIPE_TYPE_KERNEL_DIRECT)
				#else
					if(val<=PIPE_TYPE_KERNEL_THREAD)
				#endif
					pipeType[index]=val;
				 else
				 	ret= -EFAULT;
			}
		break;
	case P_IOCPIPESTART:
		{
		//	int len;
			kpipe_setup userPath;
			kpipe_setup *pipeSetup;
			pipe_thread *pipeThread;
			DECLARE_WAIT_QUEUE_HEAD(WQ);

			copy_from_user(&userPath,(kpipe_setup *)arg,sizeof(kpipe_setup));
			
			
			pipeSetup=pipeManage.threads[index].pipeSetup;
			pipeThread=&(pipeManage.threads[index]);

//select a default pipe type.
			if(pipeType[index]==PIPE_TYPE_USER_THREAD)
				pipeType[index]=defaultPipeType;
			if(pipeType[index]!=PIPE_TYPE_KERNEL_THREAD && pipeType[index]!=PIPE_TYPE_KERNEL_DIRECT)
				pipeType[index]=PIPE_TYPE_KERNEL_DIRECT;

	//pipe_type_kernel_direct doesn't support local file.
	#ifdef NO_KERNEL_PIPE_THREAD
			if(pipeType[index]==PIPE_TYPE_KERNEL_DIRECT) {
				if(userPath.type>PIPE_KP) {
					ret = -EFAULT;
					break;
					}
			}
		#endif
			
			if(*(pipeSetup->host)) //if it has used already? a.dma or a.index.
				pipeSetup++;
			if(*(pipeSetup->host)) {
				HDEBUG("no pipeSetup\n");
				ret = -EFAULT;
				break;
			}
				

			
			pipeThread->index = index;	//a or b.
			pipeSetup->index = index;
		//	copy_from_user(&pipeSetup->nums,&userPath.nums,1);
			pipeSetup->nums = userPath.nums;
			
		//	copy_from_user(&pipeSetup->size,&((kpipe_setup *)arg)->size,sizeof(int));
			 pipeSetup->size = userPath.size;
			 
		//	copy_from_user(&httpThread->type,&((kpipe_setup *)arg)->type,1);
			pipeThread->type = userPath.type;	//close or keep alive.
			
			memcpy(pipeSetup->host,userPath.host,16);

			memcpy(pipeSetup->procfile,userPath.procfile,16);
			
			if(!strcmp(pipeSetup->procfile+strlen("/proc/a."),"mda")) {
				
				pipeSetup->pathIndex = MEDIA_PATH_NUM;	//dma or index.
			} else {
				pipeSetup->pathIndex  = INDEX_PATH_NUM;
			}
			
		
		//	pipeSetup->host=HTTP_MALLOC(strlen(userPath->host)+1);
			pipeSetup->path=HTTP_MALLOC(userPath.pathSize);
		//	pipeSetup->sessionid=HTTP_MALLOC(((kpipe_setup *)arg)->sessionidSize);
			
			if(!pipeSetup->path) {
			// no memroy.
			}
			
			copy_from_user(pipeSetup->path,userPath.path,userPath.pathSize);
		
			if(userPath.sessionid){
				pipeSetup->sessionid=HTTP_MALLOC(userPath.sessionidSize);

				copy_from_user(pipeSetup->sessionid,userPath.sessionid,userPath.sessionidSize);
			}
			
		//	copy_from_user(&(pipeSetup->port),&userPath.port),sizeof(short));
			pipeSetup->port = userPath.port;
			
		//	copy_from_user(&(pipeSetup->protection),&(((kpipe_setup *)arg)->protection),sizeof(int));			
			pipeSetup->protection = userPath.protection;

			HDEBUG("ioctl:%s %d:%s\n",pipeSetup->host,pipeSetup->port,pipeSetup->path);
			
			//pipeManage.starts[index][pipeSetup->index].start=1;
		
			if(pipeType[index]==PIPE_TYPE_KERNEL_THREAD) {
				down_interruptible(&(pipeManage.semaphore));
				atomic_set(&(pipeManage.starts[index][pipeSetup->pathIndex]),1); //start kernel_thread.
			//to wakeup manage thread.
		
				while(pipeManage.change) {
					interruptible_sleep_on_timeout(&WQ,5);
				}
				pipeManage.change=1;
				up(&(pipeManage.semaphore));
				wake_up_interruptible(&(pipeManage.wq));
				
			}
		
	
		}
		
	
		break;
	case P_IOCPIPESTOP:
		{
		
			pipe_thread *thread=&(pipeManage.threads[index]);
			int i;
			DECLARE_WAIT_QUEUE_HEAD(WQ);	

			RELEASE(index) = 1;

		if(pipeType[index]==PIPE_TYPE_KERNEL_THREAD) {
			wake_up_interruptible(&(RQ(index)));
			wake_up_interruptible(&(WQ(index)));



			down_interruptible(&(pipeManage.semaphore));
			atomic_set(&(pipeManage.stops[index]),1);
				//to wakeup manage thread.
			while(pipeManage.change) {
					interruptible_sleep_on_timeout(&WQ,5);
			}
			pipeManage.change = 1;
			up(&(pipeManage.semaphore));
			wake_up_interruptible(&(pipeManage.wq));
			
		} 
		else {
			 	for(i=0;i<END_PATH_NUM;i++) {
				if(thread->pipeSetup[i].path) {
					HTTP_FREE(thread->pipeSetup[i].path);
					if(thread->pipeSetup[i].sessionid)
						HTTP_FREE(thread->pipeSetup[i].sessionid);
					memset(&(thread->pipeSetup[i]),0,sizeof(kpipe_setup));
				}
			}
		}	
	
			
		}
		break;
	#endif
	default:
		ret = (-ENOTTY);
	}
	
my_error:
#ifdef KRSA
	if(input) kfree(input);
#endif
	Up(index);
	return ret;
}

#ifdef KERNEL_PIPE

int proc_released(int index)
{
	return(RELEASE(index));
}
//touch a context.
context *proc_context(int index, int pathIndex)
{
	context *ct=NULL;

//	Down(index);
	do{if(down_interruptible(&(SEMAPHO(index)))) return NULL;}while(0);

	if(pathIndex==INDEX_PATH_NUM) {
		if(((pipes[index].ct)[CONTEXT]).pid == 0) {
			ct = &((pipes[index].ct)[CONTEXT]);
			((pipes[index].ct)[CONTEXT]).pid = current->pid;
		}
	}
	else if(WRITERS(index) < CONTEXT) {
	    ct = &((pipes[index].ct)[WRITERS(index)]);
		(WRITERS(index))++;
	}
	else ct = NULL;

	Up(index);

	return ct;
}

#define 	POS(ct)		(ct->pos)
int proc_tell(int index,int pathIndex,loff_t *seek,size_t *size,context *ct)
{
	Down(index);
	*size = (BPOS(ct))?(BUFF_SIZE):(SIZE(ct));
	*seek=POS(ct);
	Up(index);
	
	return(0);
}

//get a free block.
struct block *proc_getBuff(int index,int pathIndex)
{
	struct block *blk=NULL;
//	Down(index);
	do{if(down_interruptible(&(SEMAPHO(index)))) return NULL;}while(0);

	blk=dev_getBuff(&(pipes[index].device));
	Up(index);
	
	return blk;
}


//return a free block.
int proc_freeBuff(int index,int pathIndex, struct block *buff)
{
	Down(index);
	dev_freeBuff(&(pipes[index].device),buff);
	Up(index);
	
	return 0;
}

// insert a written block.
int proc_insertBuff(int index,int pathIndex,struct block *buff,loff_t pos, size_t count,context *ct)
{
	loff_t* f_pos,spos;
	size_t left = count, wrt;
	int ret;

	if(RELEASE(index)) return count;

	if(pathIndex==INDEX_PATH_NUM) {
		spos = ((pipes[index].ct)[CONTEXT]).bpos + pos;
	} else {
		spos=pos;
	}
	
			
	f_pos=(loff_t *)&spos;
	
	
	while(1) {
		Down(index);
		wrt = left;
		ret = dev_insertBuff(&((pipes[index]).device), f_pos,buff, &left, ct);
		if(pathIndex==INDEX_PATH_NUM)
			POS(ct)=*f_pos-((pipes[index].ct)[CONTEXT]).bpos;
		else
			POS(ct)=*f_pos;
			
		if(ret == DEV_FAULT) {Up(index); return -EFAULT;}

		if(wrt && !R_ABLE(ct)) {
			R_ABLE(ct) = 1;
			if(ret == DEV_SEEK) {
				wake_up_interruptible_sync(&(RQ(index)));
			}
			else {
				wake_up_interruptible(&(RQ(index)));
			}
		}
		if(ret == DEV_SEEK) {Up(index); return -P_ESEEK;}

		if(ret == DEV_FULL) {
			W_ABLE(ct) = 0; Up(index);
			PDEBUG("<%d>: device full, sleep, left %d\n", current->pid, (int)left);
			Wait_Event(WQ(index), RELEASE(index)||W_ABLE(ct));
			if(RELEASE(index)) return count;
			continue;
		}
		Up(index);

		if(left <= 0) break;
	}
	return count;

}

int  kpipe_init(void);
void kpipe_cleanup(void);

#ifdef NO_KERNEL_PIPE_THREAD
ssize_t p_sock_read(int index, struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
//	context *ct=getct(index,*f_pos);
	pipe_file *pp=&(pipes[index]);
	kpipe_setup *pipeSetup=&(pipeManage.threads[index].pipeSetup[0]);
	size_t   len;
	int type;
	loff_t tmp_pos=*f_pos;
	sock_pos_t	*sockPos=filp->private_data;
	
	if(!filp->private_data) {
		HDEBUG("first read,malloc sock_pos_t\n");
		sockPos=kmalloc(sizeof(sock_pos_t),GFP_KERNEL);
		memset(sockPos,0,sizeof(sock_pos_t));
		sockPos->magic = SOCK_POS_MAGIC;
		filp->private_data = sockPos;
	}

	Down(index);
	if(tmp_pos >= ((pp->ct)[CONTEXT]).bpos)  {
		HDEBUG("read idx\n");
		if(pipeSetup->pathIndex!=INDEX_PATH_NUM)
			pipeSetup++;
		tmp_pos -=((pp->ct)[CONTEXT]).bpos;
	}
	type=pipeSetup->type;
	Up(index);
	len = p_close_createAndRead(sockPos,pipeSetup,buf,count,&tmp_pos);
	if(len>=0) {
		*f_pos +=len;
		sockPos->pos = tmp_pos+len;
	}
	return len;
}
#endif

#endif   //end #ifdef KERNEL_PIPE


static int p_opena(struct inode* inode, struct file* filp)
{
	return p_open(0, inode, filp);
}
static int p_releasea(struct inode* inode, struct file* filp)
{
	return p_release(0, inode, filp);
}
static int p_ioctla(struct inode* inode, struct file* filp, unsigned int cmd, unsigned long arg)
{
	return p_ioctl(0, inode, filp, cmd, arg);
}
static ssize_t p_read_mdaa(struct file* filp, char* buf, size_t count, loff_t* f_pos)
{
#ifdef	CONFIG_PROC_PIPE_64_BITS_SUPPORT
	if (*f_pos >= pipes[0].mda_size )
#else	// CONFIG_PROC_PIPE_64_BITS_SUPPORT
	if (*f_pos >= pipes[0].mda->size)
#endif	// CONFIG_PROC_PIPE_64_BITS_SUPPORT
		return 0;
	return p_read(0, filp, buf, count, f_pos);
}
static ssize_t p_write_mdaa(struct file* filp, const char* buf, size_t count, loff_t* f_pos)
{
#ifdef	CONFIG_PROC_PIPE_64_BITS_SUPPORT
	if(*f_pos >= pipes[0].mda_size)
#else	// CONFIG_PROC_PIPE_64_BITS_SUPPORT
	if(*f_pos >= pipes[0].mda->size)
#endif	// CONFIG_PROC_PIPE_64_BITS_SUPPORT
		return 0;
	return p_write(0, filp, buf, count, f_pos);

}
static ssize_t p_read_idxa(struct file* filp, char* buf, size_t count, loff_t* f_pos)
{
	loff_t pos = ((pipes[0].ct)[CONTEXT]).bpos + (*f_pos);
	ssize_t ret = p_read(0, filp, buf, count, &pos);

	*f_pos = pos - ((pipes[0].ct)[CONTEXT]).bpos;

	return ret;
}
static ssize_t p_write_idxa(struct file* filp, const char* buf, size_t count, loff_t* f_pos)
{
	loff_t pos = ((pipes[0].ct)[CONTEXT]).bpos + (*f_pos);
	ssize_t ret = p_write(0, filp, buf, count, &pos);

	*f_pos = pos - ((pipes[0].ct)[CONTEXT]).bpos;

	return ret;
}
#ifdef DOUBLE_DEV
static int p_openb(struct inode* inode, struct file* filp)
{
	return p_open(1, inode, filp);
}
static int p_releaseb(struct inode* inode, struct file* filp)
{
	return p_release(1, inode, filp);
}
static int p_ioctlb(struct inode* inode, struct file* filp, unsigned int cmd, unsigned long arg)
{
	return p_ioctl(1, inode, filp, cmd, arg);
}
static ssize_t p_read_mdab(struct file* filp, char* buf, size_t count, loff_t* f_pos)
{
#ifdef	CONFIG_PROC_PIPE_64_BITS_SUPPORT
	if(*f_pos >= pipes[1].mda_size)
#else	// CONFIG_PROC_PIPE_64_BITS_SUPPORT
	if(*f_pos >= pipes[1].mda->size)
#endif	// CONFIG_PROC_PIPE_64_BITS_SUPPORT
		return 0;
	return p_read(1, filp, buf, count, f_pos);
}
static ssize_t p_write_mdab(struct file* filp, const char* buf, size_t count, loff_t* f_pos)
{
#ifdef	CONFIG_PROC_PIPE_64_BITS_SUPPORT
	if(*f_pos >= pipes[1].mda_size)
#else	// CONFIG_PROC_PIPE_64_BITS_SUPPORT
	if(*f_pos >= pipes[1].mda->size)
#endif	// CONFIG_PROC_PIPE_64_BITS_SUPPORT
		return 0;
	return p_write(1, filp, buf, count, f_pos);
}
static ssize_t p_read_idxb(struct file* filp, char* buf, size_t count, loff_t* f_pos)
{
	loff_t pos = ((pipes[1].ct)[CONTEXT]).bpos + (*f_pos);
	ssize_t ret = p_read(1, filp, buf, count, &pos);

	*f_pos = pos - ((pipes[1].ct)[CONTEXT]).bpos;

	return ret;
}

static ssize_t p_write_idxb(struct file* filp, const char* buf, size_t count, loff_t* f_pos)
{
	loff_t pos = ((pipes[1].ct)[CONTEXT]).bpos + (*f_pos);
	ssize_t ret = p_write(1, filp, buf, count, &pos);

	*f_pos = pos - ((pipes[1].ct)[CONTEXT]).bpos;

	return ret;
}
#endif
#ifdef __PIPE_SELECT__
static unsigned int p_poll(int index, struct file *filp, poll_table *wait)
{
    unsigned int mask = 0;
    pipe_file *pp = &(pipes[index]);

#ifdef KERNEL_PIPE
	if(pipeType[index]>=PIPE_TYPE_KERNEL_THREAD)
		return (POLLIN|POLLRDNORM);
#endif

    poll_wait(filp, &(RQ(index)), wait);
    if(pp->r_poll || dev_search(&(pp->device), pp->r_pos, (pp->device).head)){
        if(pp->r_poll) pp->r_poll = 0;
        mask |= POLLIN | POLLRDNORM;  /* readable */
    }
    return mask;
}

static unsigned int p_polla(struct file *filp, poll_table *wait)
{
    return p_poll(0, filp, wait);
}

#ifdef DOUBLE_DEV
static unsigned int p_pollb(struct file *filp, poll_table *wait)
{
    return p_poll(1, filp, wait);
}
#endif

#endif

#ifdef	CONFIG_PROC_PIPE_64_BITS_SUPPORT
static	loff_t p_llseek_mdaa(struct file *file, loff_t offset, int origin)
{
long long	retval;
	switch( origin ) {
		case 2:
			offset += pipes[0].mda_size;
			break;
		case 1:
			offset += file->f_pos;
	}
	retval = -EINVAL;
	if (offset >= 0) {
		if (offset != file->f_pos) {
			file->f_pos = offset;
			file->f_version = 0;
		}
		retval = offset;
	}
	return retval;
}
#endif	// CONFIG_PROC_PIPE_64_BITS_SUPPORT

static struct file_operations p_fops_mdaa = {
	open	: p_opena,
	release	: p_releasea,
#ifdef __PIPE_SELECT__
    poll    : p_polla,
#endif
	ioctl	: p_ioctla,
	read	: p_read_mdaa,
	write	: p_write_mdaa,
#ifdef	CONFIG_PROC_PIPE_64_BITS_SUPPORT
	llseek:	p_llseek_mdaa,	
#endif	// CONFIG_PROC_PIPE_64_BITS_SUPPORT
};
static struct file_operations p_fops_idxa = {
	open	: p_opena,
	release	: p_releasea,
#ifdef __PIPE_SELECT__
    poll    : p_polla,
#endif
	ioctl	: p_ioctla,
	read	: p_read_idxa,
	write	: p_write_idxa,
};

#ifdef DOUBLE_DEV
static struct file_operations p_fops_mdab = {
	open	: p_openb,
	release	: p_releaseb,
#ifdef __PIPE_SELECT__
    poll    : p_pollb,
#endif
	ioctl	: p_ioctlb,
	read	: p_read_mdab,
	write	: p_write_mdab,
};
static struct file_operations p_fops_idxb = {
	open	: p_openb,
	release	: p_releaseb,
#ifdef __PIPE_SELECT__
    poll    : p_pollb,
#endif
	ioctl	: p_ioctlb,
	read	: p_read_idxb,
	write	: p_write_idxb,
};
#endif

int __init p_init(void)
{
#ifdef MODULE
//	SET_MODULE_OWNER(&p_fops_mdaa);
#endif
	memset(pipes, 0, sizeof(pipes));

	(pipes[0].mda) = create_proc_entry("a.mda", 0, NULL);
	(pipes[0].mda)->proc_fops = &p_fops_mdaa;
	(pipes[0].idx) = create_proc_entry("a.idx", 0, NULL);
	(pipes[0].idx)->proc_fops = &p_fops_idxa;
	sema_init(&(SEMAPHO(0)), 1);
	init_waitqueue_head(&(RQ(0)));
	init_waitqueue_head(&(WQ(0)));
#ifdef DOUBLE_DEV
	(pipes[1].mda) = create_proc_entry("b.mda", 0, NULL);
	(pipes[1].mda)->proc_fops = &p_fops_mdab;
	(pipes[1].idx) = create_proc_entry("b.idx", 0, NULL);
	(pipes[1].idx)->proc_fops = &p_fops_idxb;
	sema_init(&(SEMAPHO(1)), 1);
	init_waitqueue_head(&(RQ(1)));
	init_waitqueue_head(&(WQ(1)));
#endif
	// init khttp --carl.
	#ifdef KERNEL_PIPE
	printk("\033[1;33mNew kernel pipe 0717_2007................\033[0m\n");
	kpipe_init();
	#endif

	return 0;
}
void __exit p_cleanup(void)
{
	remove_proc_entry("a.mda", 0);
	remove_proc_entry("a.idx", 0);
#ifdef DOUBLE_DEV
	remove_proc_entry("b.mda", 0);
	remove_proc_entry("b.idx", 0);
#endif
	//cleanup khttp --carl.
	#ifdef KERNEL_PIPE
	kpipe_cleanup();
	#endif
	return;
}
module_init(p_init);
module_exit(p_cleanup);
MODULE_LICENSE("GPL");
