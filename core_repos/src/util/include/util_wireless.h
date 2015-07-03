#include <asm/types.h>
#include <sys/socket.h>
#include <linux/rtnetlink.h>

#define MAX_SCAN_RESULT 48

struct rtnl_handle
{
	int			fd;
	struct sockaddr_nl      local;
	struct sockaddr_nl      peer;
	__u32                   seq;
	__u32                   dump;
};

struct scan_result {
	WIRELESS_MODE mode;
	char ssid[32];
	int ssid_len;
	char bssid[18];
	unsigned char wpa_ie[80];
	int wpa_ie_len;
	unsigned char rsn_ie[80];
	int rsn_ie_len;
	int crypt;
	int freq; /* MHz */
	int signal_dbm; /* signal quality */
	int signal_percentage;
	int wireless_type; //1 for 11bg, 2 for 11a, 4 for 11n
};

void handle_netlink_events(struct rtnl_handle *rth);
void rtnl_close(struct rtnl_handle *rth);
int rtnl_open(struct rtnl_handle *rth, unsigned subscriptions);
void parse_wpa_ie(unsigned char *ie, int *ret);
void parse_rsn_ie(unsigned char *ie, int *ret);
void set_crypt_type(int *crypt, int wpa);
unsigned char *get_gArWlan_buffer();
char *get_gArScan_result();
int *get_giCount();
int set_wlan_ifname(int cnt1, char *ifnamelist1, struct wireless_driver_ops *tmp);
int set_wlan_ifname_ifnamelist(int cnt1, int cnt2, char *ifnamelist1, char *ifnamelist2, char *name);
void set_cur_essid(char *essid);
char *get_cur_essid();
void strrm_carriage_return(char *str[], int len);
