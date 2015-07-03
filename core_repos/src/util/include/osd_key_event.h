#ifndef __OSD_KEY_EVENT_H__
#define __OSD_KEY_EVENT_H__

typedef enum _enum_osd_event{
	osd_event_network_link_down,
	osd_event_network_link_up,
	osd_event_unknown
	
}enum_osd_event;



struct osd_key_event_map_st{
       enum_osd_event event;
       const char     key;
};

#define EPDEVICES2P       "devices2pfifo"
#define EPDEVICEP2S       "devicep2sfifo"
#endif
