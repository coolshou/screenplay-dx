/*
 *Copyright (C) 2003-2006, Alpha Networks Inc. All rights reserved.
 *
 *$Id: event_proxy.h,v 1.1.2.6 2007-03-06 04:26:51 divers_dai Exp $
 *vim:cindent:ts=8 sts=8 sw=8
 */
#ifndef __EVEMT_PROXY_H__

#define __EVEMT_PROXY_H__


#define EVENT_PROXY_SUCCESS	0
#define EVENT_PROXY_PARAERR	5
#define EVENT_PROXY_FAIL	2


typedef enum{
	EVENT_PROXY_FIFO=0,
	EVENT_PROXY_LIST
}event_proxy_instance_type;

typedef struct _event_proxy_ops_t* event_proxy_ops_fun;
typedef struct _event_proxy_t*  ptr_event_object_handler;

typedef unsigned char (*init_callback)(void * readfd,void * writefd);

typedef unsigned char (*list_free_data_callback)(void * data);

//event_proxy register function.
typedef unsigned char (*send_event_fun)(ptr_event_object_handler ep_handle,void *event,int event_len);
typedef unsigned char (*get_event_fun)(ptr_event_object_handler ep_handle, void **event,int *event_len);
typedef unsigned char (*clear_all_fun)(ptr_event_object_handler ep_handle);
//call this function to quire is there any data to read.
typedef  unsigned char (*poll_event_fun)(ptr_event_object_handler ep_handle,unsigned char *result);


typedef struct _event_proxy_ops_t{
	send_event_fun send_event;
	get_event_fun  get_event;
	poll_event_fun poll_event;
	clear_all_fun   clear_all;
}event_proxy_ops;



typedef struct _event_proxy_t{
	int instance_type;
	event_proxy_ops_fun ops_fun;
}event_proxy_t;


typedef struct _event_proxy_fifo_t{
	event_proxy_t parent;
	int readfd, writefd;
	int dummy_wrfd, dummy_rdfd;
	char *fifo_send;
	char *fifo_recv;
}event_proxy_fifo_t;


typedef struct _event_proxy_list_data_t{
	void *data;
	struct _event_proxy_list_data_t *next;
}event_proxy_list_data;



typedef struct _event_proxy_list_t{
	event_proxy_t parent;
	event_proxy_list_data  *head;//use it to mark the list's head.
	list_free_data_callback destory_event_cb;
}event_proxy_list_t;

//event_proxy abstract API
//use to create a new event proxy object default using fifo to transmit.
ptr_event_object_handler create_event_proxy(int  entity_type,char *rd_info,char *wr_info,init_callback cb);

//create a event proxy instance that using list to tansmit data info.
//when you use list ,you have to set the cb for the inner to call to free the event data,else create fail
ptr_event_object_handler create_list_event_proxy(int  entity_type, list_free_data_callback cb);

//when dont use the proxy object anymore.call this function to destory.
unsigned char destory_event_proxy(ptr_event_object_handler ep_handle);

//after init.when have some data to transfer to the other size of the communication channal.call this function to do it
unsigned char event_proxy_send_event(ptr_event_object_handler ep_handle,void *event,int event_len);

//when known that there are some event data to read ,call this function to get the data's address.after using this data,you have to free the data's space
unsigned char event_proxy_get_event(ptr_event_object_handler ep_handle, void **event,int *event_len);

//when to clear the communication channel's data.call it.
unsigned char event_proxy_clear_all(ptr_event_object_handler ep_handle);

//call this function to select if there are any event data to read.you can get the infor from the *result value.
unsigned char event_proxy_poll_event(ptr_event_object_handler ep_handle,unsigned char *result);


#endif

