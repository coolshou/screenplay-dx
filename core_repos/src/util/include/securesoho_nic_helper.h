#ifndef __SECURESOHO_NIC_HELPER_H
#define __SECURESOHO_NIC_HELPER_H

typedef enum _ENUM_NIC_TYPE{
	NIC_TYPE_UNKNOWN,
	NIC_TYPE_WIRED,
	NIC_TYPE_WIRELESS,
}ENUM_NIC_TYPE;

typedef struct {
		char name[16];
		int ipaddress;
}network_interface_t;

/* Desc: This functions used to get the nic's hardware address
 * Args:
 *      ifname             (IN): NIC interface name
 *      namelen            (IN): NIC interface name length
 *      hwaddr             (OUT): the hardware address
 * Return:
 *      None
 */
int securesoho_nic_get_ifc_hwaddr(const char* ifname,int namelen, unsigned char* hwaddr);


/* Desc: This functions used to wait the NIC active status
 * Args:
 *      ifname             (IN): NIC interface name
 *      namelen            (IN): NIC interface name length
 *      timeout            (OUT): the waiting timeout
 * Return:
 *      None
 */
int securesoho_nic_wait_ifc_up(const char *devname, int timeout);

/* Desc: This functions used to turn on NIC. If fail, try again until to timeout.
 * Args:
 *      ifname             (IN): NIC interface name
 *      timeout            (OUT): the waiting timeout
 * Return:
 *      None
 */
int securesoho_nic_ifc_up(const char *devname, int timeout);

/* Desc: This functions used to wait the NIC ready(IP gotted) at the specified timeout period.
 * Args:
 *      ifname             (IN): NIC interface name
 *      namelen            (IN): NIC interface name length
 *      timeout            (OUT): the waiting timeout
 * Return:
 *      None
 */
int securesoho_nic_wait_ifc_ready(const char *devname, int timeout);

/* Desc: This functions used to wait the host NIC ready(IP gotted) at the specified timeout period.
 * Args:
 *      timeout            (OUT): the waiting timeout
 * Return:
 *      None
 */
int securesoho_nic_wait_host_ready(int timeout);

/* Desc: This functions to check the NIC inteface status
 * Args:
 *      devname             (IN): NIC interface name
 * Return:
 *      0  -> ready
 *      1  -> interface down
 *      2  -> invalid ip (0.0.0.0)
 *      3  -> unknown
 */
int securesoho_nic_ifc_status(const char *devname);

/* Desc: This functions to check the NIC link connection status
 * Args:
 *      ifname             (IN): NIC interface name
 *      namelen            (IN): NIC interface name length
 * Return:
 *      0  -> link down
 *      1  -> link up
 */
int securesoho_nic_check_ifc_link(const char* ifname,int namelen);

/* Desc: This functions to get current link NIC type
 * Args:
 *      NULL
 * Return:
 *    NIC type
 */
ENUM_NIC_TYPE securesoho_nic_get_type(void);

/* Desc: This functions to get current link NIC Max BitRate
 * Args:
 *      NULL
 * Return:
 *      Max BitRate Kbps
 */
int securesoho_nic_max_bit_rate(void);

/* Desc: This functions to get local IP address list
 * Args:
 * 		addresslist			(IN): IP address list pointer
 * Return:
 * 		number of network interfaces which are up
 */
int securesoho_nic_get_ipaddress_list(network_interface_t** addresslist);

#endif
