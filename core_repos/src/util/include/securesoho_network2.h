#ifndef __SECURESOHO_NETWORK_H
#define __SECURESOHO_NETWORK_H

#include <semaphore.h>
#define NETWORK_COMMAND_RESTART     's'
#define NETWORK_COMMAND_CANCEL      'c'
#define NETWORK_COMMAND_STATE       'g'

#define NETWORK_COMMAND_DAEMON_INACTIVE  'd'
#define NETWORK_COMMAND_DAEMON_ACTIVE    'a'

#define NETWORK_DAEMON_HOST         "127.0.0.1"
#define NETWORK_DAEMON_PORT         4455

typedef enum {
	NETWORK_STATE_INIT = 0,
	NETWORK_STATE_WIRELESS_CONNECTING,
	NETWORK_STATE_WIRELESS_TIMEOUT,
	NETWORK_STATE_REQUESTING_IP,
	NETWORK_STATE_DONE,
	NETWORK_STATE_INVALID_IP,
	NETWORK_STATE_INTEFACE_DOWN,
	NETWORK_STATE_CABLE_PLUGOFF,
	NETWORK_STATE_UNKNOWN
} NETWORK_STATE;

int securesoho_network_init(void);
int securesoho_network_init_host(char *host);
/* use the extend wireless profile */
int network_restart(int timeout);
/* use the inline wireless profile */
int network_restart2(int timeout);
int network_sync_restart(void);

/* inactive network daemon */
int network_daemon_inactive(void);
int network_daemon_active(void);

NETWORK_STATE network_get_state(void);
int iw_sockets_open(void);
int get_ifnamelist_proc(char **ifnamelist);
char *get_if_hwaddr(char *ifname);
#endif
