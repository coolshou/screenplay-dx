/* Copyright (C) 2006, Alphanetworks, inc.
 * Author: wills_yin@alphanetworks.com 
 * vim:cindent:ts=8:sw=8
 */
#ifndef __SECURESOHO_NETWORK_H__
#define __SECURESOHO_NETWORK_H__

typedef enum {
	NETWORK_STATE_INIT = 0,
	NETWORK_STATE_WIRELESS_CONNECTING,
	NETWORK_STATE_WIRELESS_TIMEOUT,
	NETWORK_STATE_REQUESTING_IP,
	NETWORK_STATE_DONE
} NETWORK_STATE;


/*
 * Netowrk API 
 */
/* * Restart the whole network, and apply the new settings. */
int  network_restart(int timeout);
/*
 * In static mode, it will do nothing but return 1; in DHCP mode, 
 * detect system whether get the DHCP IP or Auto IP, and save the
 * the dhcp zcip info to config file and apply the new settings. 
 */
NETWORK_STATE network_check_set_dhcp(void);

/* get network state */
NETWORK_STATE network_get_state( void );

/* * System will hang util all the network sconfigure etting is done. */
int  network_sync_restart(void);

/* * Check whether we should exit the wireless set thread or not. */
int is_exit_thread( void );

/* * Wireless thread use it update state info. */
int network_update_wireless_state(int success);
/*
 * Misc
 */
int GetIfHwAddr(const char* ifname, int namelen, char* hwaddr); 
int WaitInterfaceReady(const char *devname, int timeout);
int WaitInterfaceUp(const char *devname, int timeout);
/* wait for 'virint_dev' network nic ready */
int WaitHostInterfaceReady(int timeout);
#endif	// __SECURESOHO_NETWORK_H__
