#ifndef __REDSONIC_NET_UTIL_H__
#define __REDSONIC_NET_UTIL_H__

extern int redsonic_net_util_nic_list(void);
extern int redsonic_net_util_nic_is_link(char * dev_name);
extern int redsonic_net_util_nic_is_running(char * dev_name);
extern int redsonic_net_util_nic_up_down(char * dev_name, int enable);
extern int redsonic_net_util_is_dhcp_on(char * dev_name);
extern int redsonic_net_util_set_dhcp_on_off(char * dev_name, int on);
extern int redsonic_net_util_set_ip(char * dev_name, char * ipaddr);
extern int redsonic_net_util_get_ip(char * dev_name, char * ipaddr);
extern int redsonic_net_util_set_netmask(char * dev_name, char * ipaddr);
extern int redsonic_net_util_get_netmask(char * dev_name, char * ipaddr);
extern int redsonic_net_util_get_gateway(char * dev_name, char * ipaddr);
extern int redsonic_net_util_set_gateway(char * dev_name, char * ipaddr);
extern int redsonic_net_util_get_dns(int order, char * dns_name);
extern int redsonic_net_util_set_dns(int order, char * dns_name);
extern int redsonic_net_util_wireless_get_ssid(char * dev_name, char * ssid);
extern int redsonic_net_util_wireless_set_ssid(char * dev_name, char * ssid);
extern int redsonic_net_util_wireless_get_channel(char * dev_name, int * channel);
extern int redsonic_net_util_wireless_set_channel(char * dev_name, int channel);
extern int redsonic_net_util_wireless_get_txpower(char * dev_name, int * tx_power);
extern int redsonic_net_util_wireless_set_txpower_on_off(char * dev_name, int is_on);
extern int redsonic_net_util_wireless_get_wep_key(char * dev_name, char * key, int * key_len);
extern int redsonic_net_util_wireless_set_wep_key(char * dev_name, char * key_string);
extern int redsonic_net_util_wireless_get_wep_key_index(char * dev_name, int * channel);
extern int redsonic_net_util_wireless_set_wep_key_index(char * dev_name, int channel);
extern int redsonic_net_util_wireless_get_secure_method(char * dev_name, char * method);
extern int redsonic_net_util_wireless_set_secure_method(char * dev_name, char * method);
extern int redsonic_net_util_wireless_get_encryption_level(char * dev_name, int * n_bits);
extern int redsonic_net_util_wireless_get_signal_dbm(char * dev_name, int * dbm);
extern int redsonic_net_util_wireless_get_normalized_strength(char * dev_name, int * percentage);
extern int redsonic_net_util_wireless_get_ap_mac_addr(char * dev_name, char * mac_addr);
extern int redsonic_net_util_wireless_is_associated(char * dev_name);

#endif //__REDSONIC_NET_UTIL_H__

