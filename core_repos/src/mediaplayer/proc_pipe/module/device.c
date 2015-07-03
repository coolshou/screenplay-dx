#include "proc_pipe.h"
#include "device.h"

#define HEAD	(device->head)
#define TAIL	(device->tail)
#define FREE	(device->free)
#define PRED	(device->pred)
#define POS(a)	((a)->position)
#define END(a)	((a)->position+(a)->a_size)
#define PREV(a)	((a)->prev)
#define NEXT(a)	((a)->next)

#define my_min(a,b) (((a)<(b))?(a):(b))
/**
 * Search the @pos from the block list @hotp. For each block
 * POS(bp) is the beginning of the block and the END(bp) is
 * the end of the block. 
 * In this function, it will try to search the block which contains
 * the @pos. If it is not found, it will return NULL.
 */
block* dev_search(media_dev* device, loff_t pos, block* hotp)
{
	block *bp;

	if(!hotp || !HEAD || (pos<POS(HEAD)) || (pos>=END(TAIL))) return NULL;

	if(pos >= END(hotp)) {
		for(bp=NEXT(hotp); pos>=END(bp); bp=NEXT(bp));
		if(pos >= POS(bp)) return bp;
	}
	else if(pos < POS(hotp)) {
		for(bp=PREV(hotp); pos<POS(bp); bp=PREV(bp));
		if(pos <  END(bp)) return bp;
	}else {
		return hotp;
	}
	return NULL;
}

/**
 *  Release blocks from @delh to @delt and put them into the free list.
 *  This function looks wired because it cut several items in the list at
 *  one time.
 */
static inline void dev_free(media_dev* device, block* delh, block* delt)
{
	block *bp;

	if(!delh || !delt || POS(delh)>POS(delt)) return;

	for(bp=delh; bp && POS(bp)<=POS(delt); bp=NEXT(bp)) bp->a_size = 0;

	if(PREV(delh)) NEXT(PREV(delh)) = NEXT(delt); else {if((HEAD = NEXT(delt))) PREV(HEAD) = NULL;}
	if(NEXT(delt)) PREV(NEXT(delt)) = PREV(delh); else {if((TAIL = PREV(delh))) NEXT(TAIL) = NULL;}

	NEXT(delt) = FREE; FREE = delh;
}
static inline void dev_reap(media_dev* device)
{
	block *tmph = NULL, *tmpt = NULL;
	int i;

	PDEBUG("device reap\n");

	for(i=0; i<=CONTEXT; i++) {
		block *bp = HOTP(device->ctp+i), *h, *t, *cur;

		if(bp && (!tmph || POS(bp)<POS(tmph) || END(bp)>END(tmpt))) {
			for(h=bp; PREV(h)&&(END(PREV(h))>=POS(h)); h=PREV(h));
			for(t=bp; NEXT(t)&&(POS(NEXT(t))<=END(t)); t=NEXT(t));
			if(PREV(h)) NEXT(PREV(h)) = NEXT(t); else {if((HEAD = NEXT(t))) PREV(HEAD) = NULL;}
			if(NEXT(t)) PREV(NEXT(t)) = PREV(h); else {if((TAIL = PREV(h))) NEXT(TAIL) = NULL;}
			for(cur=tmph; cur && POS(cur)<POS(h); cur=NEXT(cur));
			if(!tmph) {			//add at head
				tmph = h; tmpt = t;
				PREV(h) = NULL;
				NEXT(t) = NULL;
			}
			else if(!cur) {			//add at tail
				NEXT(tmpt) = h;
				PREV(h) = tmpt;
				NEXT(t) = NULL;
				tmpt = t;
			}
			else{				//add before cur
				if(PREV(cur)) NEXT(PREV(cur)) = h; else tmph = h;
				PREV(h) = PREV(cur);
				NEXT(t) = cur;
				PREV(cur) = t;
			}
		}
	}
	FREE = HEAD; HEAD = tmph; TAIL = tmpt;

	if(!FREE) {
		FREE = HEAD;		HEAD = NEXT(HEAD);
		NEXT(FREE) = NULL;	PREV(HEAD) = NULL;
		FREE->a_size = 0;
	}
}

inline void dev_flush(media_dev* device)
{
	int i = 0;

	PDEBUG("device flush\n");

	HEAD = NULL; TAIL = NULL;
	FREE = &((device->block_pool)[0]);

	do {
		if(i < BLOCK_NUM-1) {
			((device->block_pool)[i]).next = &((device->block_pool)[i+1]);
			i++;
		}
		else {
			((device->block_pool)[i]).next = NULL;
			break;
		}
	} while(1);
}

inline int dev_read(media_dev* device, loff_t* pos, char* data, size_t* left, context* ct)
{
	block *bp;
	size_t len;

	PDEBUG("<%d>: read at %d size %d\n", current->pid, (int)*pos, (int)*left);

	if(*left == 0) return 0;

	if(HOTP(ct) && HOTP(ct)->a_size == 0) HOTP(ct) = NULL;

	if((bp=dev_search(device, *pos, HOTP(ct)))) {
		block *pre, *delh = bp;

		do {
			len = my_min((size_t)((loff_t)END(bp)-(*pos)), *left);
			if(copy_to_user(data, bp->buff+(*pos-POS(bp)), len)) return DEV_FAULT;
			*left -= len; *pos += len; data += len; pre = bp;
		} while(*left && (bp=NEXT(bp)) && (POS(bp)<=END(pre)));

		if(REVS(ct)) {
			HOTP(ct) = delh;
			delh = (*pos<END(pre))?(NEXT(delh)):(NULL);
		}
		else {
			if(*pos < END(pre)) {
				HOTP(ct) = (*pos<EPOS(ct))?(pre):(NULL);
				pre = PREV(pre);
			}
			else if(*left==0 && NEXT(pre) && POS(NEXT(pre))<=*pos) {
				HOTP(ct) = (*pos<EPOS(ct))?(NEXT(pre)):(NULL);
			}
			else {
				HOTP(ct) = NULL;
			}
		}
		dev_free(device, delh, pre);
	}
	else {
		HOTP(ct) = NULL;
	}
	SEEK(ct) = *pos; SIZE(ct) = *left;

	return 0;
}

#ifdef KERNEL_PIPE
block *dev_getBuff(media_dev *device)
{
	block *bp;
	if(!FREE) dev_reap(device);
	bp=FREE;
	FREE=NEXT(FREE);
	
	return bp;
	
}

// how to record file position.
int dev_insertBuff(media_dev *device,loff_t *pos, struct block *buff,size_t *left,context *ct)
{
	block *bp = buff, *bpp = NULL, *cur;
	size_t len = my_min(BUFF_SIZE, *left);
	size_t pre_read = 0;
//	char flag=0,rec1=0,rec2=0;
//	loff_t dummy, *pos;
	
//	pos=&dummy;
	if(HOTP(ct) && HOTP(ct)->a_size == 0) HOTP(ct) = NULL;

	if(len > 0) *left -= len; else goto my_seek;
	
	bpp=bp;

	POS(bp) = *pos; bp->a_size = len;
/*
	if(*pos==147456) {
	//	HDEBUG("interrupted\n");
		flag=1;
	}
	
	{
		block *tmp;
		int num1,num2,num;
		num1=num2=0;
		num=30;
		for(tmp=FREE;tmp;tmp=NEXT(tmp))
			num1++;
		for(tmp=HEAD;tmp;tmp=NEXT(tmp))
			num2++;
		if(num1+num2 < num) {
			HDEBUG("error, block list\n");
		}
	}
*/	
	for(cur=(HOTP(ct)&&POS(bp)>=POS(HOTP(ct)))?(HOTP(ct)):(HEAD); cur; cur=NEXT(cur)) {
		if((POS(bp)>=POS(cur)) && (END(bp)<=END(cur))) {
			NEXT(bp) = FREE; FREE = bp; bp->a_size=0;
			bp = NULL; bpp = cur;
		//	rec1=1;
			break;
		}
		if(POS(bp)<=POS(cur)) {
			block *delh = cur;
			while(cur && (END(bp)>=END(cur))) cur = NEXT(cur);
			dev_free(device, delh, cur?PREV(cur):TAIL);
		//	rec1=2;
			break;
		}
	}
	if(bp) {
		if(!HEAD) {			//add at head
			HEAD = bp; TAIL = bp;
			PREV(bp) = NULL;
			NEXT(bp) = NULL;
		//	rec2=3;
		}
		else if(!cur) {			//add at tail
			NEXT(TAIL) = bp;
			PREV(bp) = TAIL;
			NEXT(bp) = NULL;
			TAIL = bp;
		//	rec2=4;
		}
		else{				//add before cur
			if(PREV(cur)) NEXT(PREV(cur)) = bp; else HEAD = bp;
			PREV(bp) = PREV(cur);
			NEXT(bp) = cur;
			PREV(cur) = bp;
		//	rec2=5;
		}
	//	if(copy_from_user(bp->buff, data, len)) return DEV_FAULT;
	}

	/*	if(flag) {
		if(buff->prev==NULL) {
			HDEBUG(" prev is NULL,self:%p,next:%p,hotp:%p\n,head:%p,free:%p,tail:%p,rec1:%d,rec2:%d\n",
					buff,buff->next,HOTP(ct),HEAD,FREE,TAIL,rec1,rec2);
		}
		flag=0;
		rec1=0;
		rec2=0;
	}
	*/
	
my_seek:
	if(bpp && POS(bpp)<=SEEK(ct) && SEEK(ct)<END(bpp)) HOTP(ct) = bpp;

	if(HOTP(ct)) {
		if(REVS(ct)) {
			for(bp=HOTP(ct); PREV(bp)&&(END(PREV(bp))>=POS(bp)); bp=PREV(bp)) {
				pre_read = END(HOTP(ct)) - POS(PREV(bp));
				if(pre_read > PRE_READ) break;
			}
			if((pre_read>PRE_READ) || (POS(bp)<=BPOS(ct))) {
				*pos += len;
				return DEV_FULL;
			}
			*pos = (POS(bp)<BPOS(ct)+BUFF_SIZE)?(BPOS(ct)):(POS(bp)-BUFF_SIZE);
			SIZE(ct) = POS(bp) - (*pos);
		}
		else {
			for(bp=HOTP(ct); NEXT(bp)&&(POS(NEXT(bp))<=END(bp)); bp=NEXT(bp)) {
				pre_read = END(NEXT(bp)) - POS(HOTP(ct));
				if(pre_read > PRE_READ) break;
			}
			if((pre_read>PRE_READ) || (END(bp)>=EPOS(ct))) {
				*pos += len;
				return DEV_FULL;
			}
			if((*pos+len) == END(bp)) {
				*pos = END(bp);
				return 0;
			}
			*pos = END(bp);
		}
	}
	else if(SEEK(ct) >= EPOS(ct)) {
		*pos += len;
		return DEV_FULL;
	}
	else if((*pos+len) == SEEK(ct)) {
		*pos = SEEK(ct);
		return 0;
	}
	else {
		if(REVS(ct)) {
			*pos = (SEEK(ct)+SIZE(ct)>BPOS(ct)+BUFF_SIZE)?(SEEK(ct)+SIZE(ct)-BUFF_SIZE):(BPOS(ct));
		}
		else	*pos = SEEK(ct);
	}
	PDEBUG("<%d>: return seek %lld\n", current->pid, *pos);
	return DEV_SEEK;
}

void dev_freeBuff(media_dev *device, block *buff)
{
	//blokc *bp=FREE;
	
	NEXT(buff)=FREE;
	FREE=buff;
}

#endif

inline int dev_write(media_dev* device, loff_t* pos, const char* data, size_t* left, context* ct)
{
	block *bp = NULL, *bpp = NULL, *cur;
	size_t len = my_min(BUFF_SIZE, *left);
	size_t pre_read = 0;

	PDEBUG("<%d>: write at %lld/%lld size %d\n", current->pid, *pos, EPOS(ct), len);

	if(HOTP(ct) && HOTP(ct)->a_size == 0) HOTP(ct) = NULL;

	if(len > 0) *left -= len; else goto my_seek;

	if(!FREE) dev_reap(device);

	bp = FREE; bpp = FREE; FREE = NEXT(FREE);

	POS(bp) = *pos; bp->a_size = len;

	for(cur=(HOTP(ct)&&POS(bp)>=POS(HOTP(ct)))?(HOTP(ct)):(HEAD); cur; cur=NEXT(cur)) {
		if((POS(bp)>=POS(cur)) && (END(bp)<=END(cur))) {
			NEXT(bp) = FREE; FREE = bp;bp->a_size=0;
			bp = NULL; bpp = cur;
			break;
		}
		if(POS(bp)<=POS(cur)) {
			block *delh = cur;
			while(cur && (END(bp)>=END(cur))) cur = NEXT(cur);
			dev_free(device, delh, cur?PREV(cur):TAIL);
			break;
		}
	}
	if(bp) {
		if(!HEAD) {			//add at head
			HEAD = bp; TAIL = bp;
			PREV(bp) = NULL;
			NEXT(bp) = NULL;
		}
		else if(!cur) {			//add at tail
			NEXT(TAIL) = bp;
			PREV(bp) = TAIL;
			NEXT(bp) = NULL;
			TAIL = bp;
		}
		else{				//add before cur
			if(PREV(cur)) NEXT(PREV(cur)) = bp; else HEAD = bp;
			PREV(bp) = PREV(cur);
			NEXT(bp) = cur;
			PREV(cur) = bp;
		}
		if(copy_from_user(bp->buff, data, len)) return DEV_FAULT;
	}
my_seek:
	if(bpp && POS(bpp)<=SEEK(ct) && SEEK(ct)<END(bpp)) HOTP(ct) = bpp;

	if(HOTP(ct)) {
		if(REVS(ct)) {
			for(bp=HOTP(ct); PREV(bp)&&(END(PREV(bp))>=POS(bp)); bp=PREV(bp)) {
				pre_read = END(HOTP(ct)) - POS(PREV(bp));
				if(pre_read > PRED) break;
			}
			if((pre_read>PRED) || (POS(bp)<=BPOS(ct))) {
				*pos += len;
				return DEV_FULL;
			}
			*pos = (POS(bp)<BPOS(ct)+BUFF_SIZE)?(BPOS(ct)):(POS(bp)-BUFF_SIZE);
			SIZE(ct) = POS(bp) - (*pos);
		}
		else {
			for(bp=HOTP(ct); NEXT(bp)&&(POS(NEXT(bp))<=END(bp)); bp=NEXT(bp)) {
				pre_read = END(NEXT(bp)) - POS(HOTP(ct));
				if(pre_read > PRED) break;
			}
			if((pre_read>PRED) || (END(bp)>=EPOS(ct))) {
				*pos += len;
				return DEV_FULL;
			}
			if((*pos+len) == END(bp)) {
				*pos = END(bp);
				return 0;
			}
			*pos = END(bp);
		}
	}
	else if(SEEK(ct) >= EPOS(ct)) {
		*pos += len;
		return DEV_FULL;
	}
	else if((*pos+len) == SEEK(ct)) {
		*pos = SEEK(ct);
		return 0;
	}
	else {
		if(REVS(ct)) {
			*pos = (SEEK(ct)+SIZE(ct)>BPOS(ct)+BUFF_SIZE)?(SEEK(ct)+SIZE(ct)-BUFF_SIZE):(BPOS(ct));
		}
		else	*pos = SEEK(ct);
	}
	PDEBUG("<%d>: return seek %lld\n", current->pid, *pos);
	return DEV_SEEK;
}
