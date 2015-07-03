#ifndef _FIFO_QUEUE_SEARCH_H_
#define _FIFO_QUEUE_SEARCH_H_

typedef enum _FIFO_QUEUE_SEARCH_RETURN {
	FIFO_QUEUE_SEARCH_RETURN_OK = 0,
	FIFO_QUEUE_SEARCH_RETURN_ERRPR = -1,	
	FIFO_QUEUE_SEARCH_RETURN_MEMORY = -2, // allocate memory error
} FIFO_QUEUE_SEARCH_RETURN;

typedef int (*FIFO_QS_User_Relase_Value) (void *value);  //TWO_WAY_INDEX_TABLE relase value function prototype

/*
	purpose : to create a instance for first in first out queue search 
	remarks:
		1) the func is used for free the value from the fifo_queue_search_add function
*/
void *fifo_queue_search_create(int max_queue_number,FIFO_QS_User_Relase_Value func);
/*
	purpose : to destroy the fifo queue instance
*/
void fifo_queue_search_destroy(void *_pdata);

/*
	purpose : add a target into fifo_queue
	remarks:
*/
FIFO_QUEUE_SEARCH_RETURN fifo_queue_search_add(void *_pdata,char *target,void *value);

/*
	purpose : delete target node from fifo_queue
*/
FIFO_QUEUE_SEARCH_RETURN fifo_queue_search_del(void *_pdata,char *target);
/*
	purpose : get the value from fifo queue when the same target
	remarks:
		we ill organize the fifo queue. the target will become to the latest node
*/
void *fifo_queue_search_get(void *_pdata,char *target);

/*
	purpose : delete all node that begin with header_string in the fifo_queue
	remarks:
		1)  return how many node be deleted
*/
int fifo_queue_search_del_header_string(void *_pdata,char *header_string);

/*
	purpose : printf all target in the fifo queue
*/
int fifo_queue_search_dump(void *_pdata);

#endif
