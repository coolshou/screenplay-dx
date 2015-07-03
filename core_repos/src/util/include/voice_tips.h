#ifndef __VOICE_TIPS_H__
#define __VOICE_TIPS_H__

#include "event_proxy.h"

#define VOICE_TIPS_LOGIN	(0x1)
#define VOICE_TIPS_CLICKED	(0x2)

#define VOICE_TIPS_STOP_IT	(~0x0)

#define VOICE_TIPS_LOGIN_URL	"file:///osd/voice/login.mp3"
#define VOICE_TIPS_CLICKED_URL	"file:///osd/voice/clicked.wav"

int voice_tips_receiver_create(void);

int voice_tips_sender_create(void);

int voice_tips_send_event(unsigned int cmd);

int voice_tips_receive_event(unsigned int **cmd);

void voice_tips_sender_enable();
void voice_tips_sender_disable();
void voice_tips_receiver_enable();
void voice_tips_receiver_disable();

#endif
