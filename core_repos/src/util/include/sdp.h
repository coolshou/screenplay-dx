/* Copyright (C) 2005, REDSonic, inc.
 * Author:  Wills Yin <wills_yin@redsonic.com>
 */
#ifndef  __SDP_H__
#define  __SDP_H__
#include <time.h>
#include <stdlib.h>

typedef struct sdp_desc_s  sdp_desc_t;

#define SAFE_FREE( p ) \
        do {                         \
                if( p ) {            \
                        free( p );   \
                        (p) = NULL;  \
                }                    \
        } while(0)


#define DESTROY_LIST(_list_, _type_, _function_)            \
        do {                                                \
                _type_ *object = _list_;                    \
                while (object) {                            \
                        _type_ *object_to_destroy = object; \
                        object = object->next;              \
                        _function_(object_to_destroy);      \
                }                                           \
        } while (0)


#define LINK_INTO_LIST(_list_, _new_object_, _type_)        \
        do {                                                \
                _type_ *p, *q;                              \
                if (_list_ == NULL) {                       \
                        _list_ = _new_object_;              \
                        break;                              \
                }                                           \
                p = q =  _list_;                            \
                while (p) {                                 \
                        q = p;                              \
                        p = p->next;                        \
                }                                           \
                q->next = _new_object_;                     \
        } while (0) 


sdp_desc_t* sdp_parse(const char* payload, int payload_len);
void        sdp_destroy(sdp_desc_t* sdp);

const char* sdp_get_sessionName(sdp_desc_t* sdp);
time_t      sdp_get_startTime(sdp_desc_t* sdp);
time_t      sdp_get_endTime(sdp_desc_t* sdp);
int         sdp_get_mediaNum(sdp_desc_t* sdp);
/*
 * A sdp may have a set of media, so we should specify the index of media 
 */
const char* sdp_get_mediaDesc(sdp_desc_t* sdp, int index);
const char* sdp_get_mediaAddr(sdp_desc_t* sdp, int index);
const char* sdp_get_mediaProt(sdp_desc_t* sdp, int index);
const char* sdp_get_mediaType(sdp_desc_t* sdp, int index);
int         sdp_get_mediaPort(sdp_desc_t* sdp, int index);
int         sdp_get_mediaCodec(sdp_desc_t* sdp, int index);

const char* sdp_get_attr(sdp_desc_t* sdp, const char* key, int index);
const char* sdp_get_mediaMimetype(sdp_desc_t* sdp, int index);

#endif
