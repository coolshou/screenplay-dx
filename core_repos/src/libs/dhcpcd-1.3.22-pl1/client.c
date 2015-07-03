/*
 * dhcpcd - DHCP client daemon -
 * Copyright (C) 1996 - 1997 Yoichi Hariguchi <yoichi@fore.com>
 * Copyright (C) January, 1998 Sergei Viznyuk <sv@phystech.com>
 * 
 * dhcpcd is an RFC2131 and RFC1541 compliant DHCP client daemon.
 *
 * This is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdarg.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/utsname.h>
#include <net/if.h>
#include <net/if_arp.h>
#ifdef __GLIBC__
#include <net/if_packet.h>
#else
#include <linux/if_packet.h>
#endif
#include <net/route.h>
#include <netdb.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <syslog.h>
#include <errno.h>
#include <setjmp.h>
#include <resolv.h>
#include <time.h>
#include <signal.h>
#include "client.h"
#include "cache.h"
#include "buildmsg.h"
#include "udpipgen.h"
#include "pathnames.h"

#include <linux/version.h>

#ifndef LINUX_VERSION_CODE
#error Unknown Linux kernel version
#endif

#ifndef KERNEL_VERSION
#define KERNEL_VERSION(a,b,c) (((a) << 16) + ((b) << 8) + (c))
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,1,1)
#define OLD_LINUX_VERSION 1
#endif

extern	char		*ProgramName,**ProgramEnviron,*Cfilename;
extern	char		*IfName,*IfNameExt;
extern	int		IfName_len,IfNameExt_len;
extern	char		*HostName;
extern	unsigned char	*ClassID;
extern	int		ClassID_len;
extern  unsigned char	*ClientID;
extern  int		ClientID_len;
extern	int		DebugFlag;
extern	int		BeRFC1541;
extern	unsigned	LeaseTime;
extern	int		ReplResolvConf;
extern	int		ReplNISConf;
extern	int		ReplNTPConf;
extern	int		SetDomainName;
extern	int		SetHostName;
extern	unsigned short	ip_id;
extern  void		*(*currState)();
extern  time_t          TimeOut;
extern  unsigned        nleaseTime;
extern  struct in_addr  inform_ipaddr;
extern	int		DoCheckSum;
extern	int		TestCase;
extern  int		Window;
extern	char		*ConfigDir;
extern  dhcpOptions     DhcpOptionsCached;
#if 0
extern	unsigned char	ClientMACaddr[ETH_ALEN];
extern	int		ClientMACaddr_ind;
#endif

#ifdef ARPCHECK
int arpCheck();
#endif
int arpRelease();
int arpInform();

int		dhcpSocket;
int		udpFooSocket;
int             prev_ip_addr;
time_t		ReqSentTime;
dhcpOptions	DhcpOptions;
dhcpInterface   DhcpIface;
udpipMessage	UdpIpMsgSend,UdpIpMsgRecv;
jmp_buf		env;
unsigned char	ClientHwAddr[ETH_ALEN];
char		hostinfo_file[128];

const struct ip *ipSend=(struct ip *)((struct udpiphdr *)UdpIpMsgSend.udpipmsg)->ip;
const struct ip *ipRecv=(struct ip *)((struct udpiphdr *)UdpIpMsgRecv.udpipmsg)->ip;
const dhcpMessage *DhcpMsgSend = (dhcpMessage *)&UdpIpMsgSend.udpipmsg[sizeof(udpiphdr)];
      dhcpMessage *DhcpMsgRecv = (dhcpMessage *)&UdpIpMsgRecv.udpipmsg[sizeof(udpiphdr)];

int resolv_renamed=0;
int yp_renamed=0;
int ntp_renamed=0;

/* Note: Legths initialised to negative to allow us to distinguish between "empty" and "not set" */
char InitialHostName[HOSTNAME_MAX_LEN];
int InitialHostName_len=-1;
char InitialDomainName[HOSTNAME_MAX_LEN];
int InitialDomainName_len=-1;
static short int saved_if_flags = 0;
void do_cmd_bg(char *fmt, ...);
/*****************************************************************************/
int parseDhcpMsgRecv() /* this routine parses dhcp message received */
{
#ifdef DEBUG
  int i,j;
#endif
  register u_char *p = DhcpMsgRecv->options+4;
  unsigned char *end = DhcpMsgRecv->options+sizeof(DhcpMsgRecv->options);
  while ( p < end )
    switch ( *p )
      {
        case endOption: goto swend;
       	case padOption: p++; break;
       	default:
	  if ( p[1] )
	    {
	      if ( DhcpOptions.len[*p] == p[1] )
	        memcpy(DhcpOptions.val[*p],p+2,p[1]);
	      else
	        {
		  DhcpOptions.len[*p] = p[1];
	          if ( DhcpOptions.val[*p] )
	            free(DhcpOptions.val[*p]);
	      	  else
		    DhcpOptions.num++;
	      	  DhcpOptions.val[*p] = malloc(p[1]+1);
		  memset(DhcpOptions.val[*p],0,p[1]+1);
	  	  memcpy(DhcpOptions.val[*p],p+2,p[1]);
	        }
	    }
	  p+=p[1]+2;
      }
swend:
#ifdef DEBUG
  fprintf(stderr,"parseDhcpMsgRecv: %d options received:\n",DhcpOptions.num);
  for (i=1;i<255;i++)
    if ( DhcpOptions.val[i] )
      switch ( i )
        {
	  case 1: /* subnet mask */
	  case 3: /* routers on subnet */
	  case 4: /* time servers */
	  case 5: /* name servers */
	  case 6: /* dns servers */
	  case 28:/* broadcast addr */
	  case 33:/* staticRoute */
	  case 41:/* NIS servers */
	  case 42:/* NTP servers */
	  case 50:/* dhcpRequestdIPaddr */
	  case 54:/* dhcpServerIdentifier */
	    for (j=0;j<DhcpOptions.len[i];j+=4)
	      fprintf(stderr,"i=%-2d  len=%-2d  option = %u.%u.%u.%u\n",
		i,DhcpOptions.len[i],
		((unsigned char *)DhcpOptions.val[i])[0+j],
		((unsigned char *)DhcpOptions.val[i])[1+j],
		((unsigned char *)DhcpOptions.val[i])[2+j],
		((unsigned char *)DhcpOptions.val[i])[3+j]);
	    break;
	  case 2: /* time offset */
	  case 51:/* dhcpAddrLeaseTime */
	  case 57:/* dhcpMaxMsgSize */
	  case 58:/* dhcpT1value */
	  case 59:/* dhcpT2value */
	    fprintf(stderr,"i=%-2d  len=%-2d  option = %d\n",
		i,DhcpOptions.len[i],
		    ntohl(*(int *)DhcpOptions.val[i]));
	    break;
	  case 23:/* defaultIPTTL */
	  case 29:/* performMaskdiscovery */
	  case 31:/* performRouterdiscovery */
	  case 53:/* dhcpMessageType */
	    fprintf(stderr,"i=%-2d  len=%-2d  option = %u\n",
		i,DhcpOptions.len[i],*(unsigned char *)DhcpOptions.val[i]);
	    break;
	  default:
	    fprintf(stderr,"i=%-2d  len=%-2d  option = \"%s\"\n",
		i,DhcpOptions.len[i],(char *)DhcpOptions.val[i]);
	}
fprintf(stderr,"\
DhcpMsgRecv->yiaddr  = %u.%u.%u.%u\n\
DhcpMsgRecv->siaddr  = %u.%u.%u.%u\n\
DhcpMsgRecv->giaddr  = %u.%u.%u.%u\n\
DhcpMsgRecv->sname   = \"%s\"\n\
ServerHardwareAddr   = %02X.%02X.%02X.%02X.%02X.%02X\n",
((unsigned char *)&DhcpMsgRecv->yiaddr)[0],
((unsigned char *)&DhcpMsgRecv->yiaddr)[1],
((unsigned char *)&DhcpMsgRecv->yiaddr)[2],
((unsigned char *)&DhcpMsgRecv->yiaddr)[3],
((unsigned char *)&DhcpMsgRecv->siaddr)[0],
((unsigned char *)&DhcpMsgRecv->siaddr)[1],
((unsigned char *)&DhcpMsgRecv->siaddr)[2],
((unsigned char *)&DhcpMsgRecv->siaddr)[3],
((unsigned char *)&DhcpMsgRecv->giaddr)[0],
((unsigned char *)&DhcpMsgRecv->giaddr)[1],
((unsigned char *)&DhcpMsgRecv->giaddr)[2],
((unsigned char *)&DhcpMsgRecv->giaddr)[3],
DhcpMsgRecv->sname,
UdpIpMsgRecv.ethhdr.ether_shost[0],
UdpIpMsgRecv.ethhdr.ether_shost[1],
UdpIpMsgRecv.ethhdr.ether_shost[2],
UdpIpMsgRecv.ethhdr.ether_shost[3],
UdpIpMsgRecv.ethhdr.ether_shost[4],
UdpIpMsgRecv.ethhdr.ether_shost[5]);
#endif
  if ( ! DhcpMsgRecv->yiaddr ) DhcpMsgRecv->yiaddr=DhcpMsgSend->ciaddr;
  if ( ! DhcpOptions.val[dhcpServerIdentifier] ) /* did not get dhcpServerIdentifier */
    {	/* make it the same as IP address of the sender */
      DhcpOptions.val[dhcpServerIdentifier] = malloc(4);
      memcpy(DhcpOptions.val[dhcpServerIdentifier],&ipRecv->ip_src.s_addr,4);
      DhcpOptions.len[dhcpServerIdentifier] = 4;
      DhcpOptions.num++;
      if ( DebugFlag )
	syslog(LOG_DEBUG,
	"dhcpServerIdentifier option is missing in DHCP server response. Assuming %u.%u.%u.%u\n",
	((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[0],
	((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[1],
	((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[2],
	((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[3]);
    }
  if ( ! DhcpOptions.val[dns] ) /* did not get DNS */
    {	/* make it the same as dhcpServerIdentifier */
      DhcpOptions.val[dns] = malloc(4);
      memcpy(DhcpOptions.val[dns],DhcpOptions.val[dhcpServerIdentifier],4);
      DhcpOptions.len[dns] = 4;
      DhcpOptions.num++;
      if ( DebugFlag )
	syslog(LOG_DEBUG,
	"dns option is missing in DHCP server response. Assuming %u.%u.%u.%u\n",
	((unsigned char *)DhcpOptions.val[dns])[0],
	((unsigned char *)DhcpOptions.val[dns])[1],
	((unsigned char *)DhcpOptions.val[dns])[2],
	((unsigned char *)DhcpOptions.val[dns])[3]);
    }
  if ( ! DhcpOptions.val[subnetMask] ) /* did not get subnetMask */
    {
      DhcpOptions.val[subnetMask] = malloc(4);
      ((unsigned char *)DhcpOptions.val[subnetMask])[0] = 255;
      if ( ((unsigned char *)&DhcpMsgRecv->yiaddr)[0] < 128 )
	{
          ((unsigned char *)DhcpOptions.val[subnetMask])[1] = 0; /* class A */
          ((unsigned char *)DhcpOptions.val[subnetMask])[2] = 0;
	}
      else
	{
          ((unsigned char *)DhcpOptions.val[subnetMask])[1] = 255;
	  if ( ((unsigned char *)&DhcpMsgRecv->yiaddr)[0] < 192 )
	    ((unsigned char *)DhcpOptions.val[subnetMask])[2] = 0;/* class B */
	  else
	    ((unsigned char *)DhcpOptions.val[subnetMask])[2] = 255;/* class C */
	}
      ((unsigned char *)DhcpOptions.val[subnetMask])[3] = 0;
      DhcpOptions.len[subnetMask] = 4;
      DhcpOptions.num++;
      if ( DebugFlag )
	syslog(LOG_DEBUG,
	"subnetMask option is missing in DHCP server response. Assuming %u.%u.%u.%u\n",
	((unsigned char *)DhcpOptions.val[subnetMask])[0],
	((unsigned char *)DhcpOptions.val[subnetMask])[1],
	((unsigned char *)DhcpOptions.val[subnetMask])[2],
	((unsigned char *)DhcpOptions.val[subnetMask])[3]);
    }
  if ( ! DhcpOptions.val[broadcastAddr] ) /* did not get broadcastAddr */
    {
      int br = DhcpMsgRecv->yiaddr | ~*((int *)DhcpOptions.val[subnetMask]);
      DhcpOptions.val[broadcastAddr] = malloc(4);
      memcpy(DhcpOptions.val[broadcastAddr],&br,4);
      DhcpOptions.len[broadcastAddr] = 4;
      DhcpOptions.num++;
      if ( DebugFlag )
	syslog(LOG_DEBUG,
	"broadcastAddr option is missing in DHCP server response. Assuming %u.%u.%u.%u\n",
	((unsigned char *)DhcpOptions.val[broadcastAddr])[0],
	((unsigned char *)DhcpOptions.val[broadcastAddr])[1],
	((unsigned char *)DhcpOptions.val[broadcastAddr])[2],
	((unsigned char *)DhcpOptions.val[broadcastAddr])[3]);
    }
#if 0
  if ( ! DhcpOptions.val[routersOnSubnet] )
    {
      DhcpOptions.val[routersOnSubnet] = malloc(4);
      if ( DhcpMsgRecv->giaddr )
      	memcpy(DhcpOptions.val[routersOnSubnet],&DhcpMsgRecv->giaddr,4);
      else
	memcpy(DhcpOptions.val[routersOnSubnet],DhcpOptions.val[dhcpServerIdentifier],4);
      DhcpOptions.len[routersOnSubnet] = 4;
      DhcpOptions.num++;
      if ( DebugFlag )
	syslog(LOG_DEBUG,
	"routersOnSubnet option is missing in DHCP server response. Assuming %u.%u.%u.%u\n",
	((unsigned char *)DhcpOptions.val[routersOnSubnet])[0],
	((unsigned char *)DhcpOptions.val[routersOnSubnet])[1],
	((unsigned char *)DhcpOptions.val[routersOnSubnet])[2],
	((unsigned char *)DhcpOptions.val[routersOnSubnet])[3]);
    }
#endif
  if ( DhcpOptions.val[dhcpIPaddrLeaseTime] && DhcpOptions.len[dhcpIPaddrLeaseTime] == 4 )
    {
      if ( *(unsigned int *)DhcpOptions.val[dhcpIPaddrLeaseTime] == 0 )
	{
          memcpy(DhcpOptions.val[dhcpIPaddrLeaseTime],&nleaseTime,4);
	  if ( DebugFlag )
	    syslog(LOG_DEBUG,"dhcpIPaddrLeaseTime=0 in DHCP server response. Assuming %u sec\n",LeaseTime);
	}
    }
  else /* did not get dhcpIPaddrLeaseTime */
    {
      DhcpOptions.val[dhcpIPaddrLeaseTime] = malloc(4);
      memcpy(DhcpOptions.val[dhcpIPaddrLeaseTime],&nleaseTime,4);
      DhcpOptions.len[dhcpIPaddrLeaseTime] = 4;
      DhcpOptions.num++;
      if ( DebugFlag )
	syslog(LOG_DEBUG,"dhcpIPaddrLeaseTime option is missing in DHCP server response. Assuming %u sec\n",LeaseTime);
    }
  if ( DhcpOptions.val[dhcpT1value] && DhcpOptions.len[dhcpT1value] == 4 )
    {
      if ( *(unsigned int *)DhcpOptions.val[dhcpT1value] == 0 )
	{
	  unsigned t2 = 0.5*ntohl(*(unsigned int *)DhcpOptions.val[dhcpIPaddrLeaseTime]);
	  int t1 = htonl(t2);
	  memcpy(DhcpOptions.val[dhcpT1value],&t1,4);
	  DhcpOptions.len[dhcpT1value] = 4;
	  if ( DebugFlag )
	    syslog(LOG_DEBUG,"dhcpT1value=0 in DHCP server response. Assuming %u sec\n",t2);
	}
    }
  else		/* did not get T1 */
    {
      unsigned t2 = 0.5*ntohl(*(unsigned int *)DhcpOptions.val[dhcpIPaddrLeaseTime]);
      int t1 = htonl(t2);
      DhcpOptions.val[dhcpT1value] = malloc(4);
      memcpy(DhcpOptions.val[dhcpT1value],&t1,4);
      DhcpOptions.len[dhcpT1value] = 4;
      DhcpOptions.num++;
      if ( DebugFlag )
	syslog(LOG_DEBUG,"dhcpT1value option is missing in DHCP server response. Assuming %u sec\n",t2);
    }
  if ( DhcpOptions.val[dhcpT2value] && DhcpOptions.len[dhcpT2value] == 4 )
    {
      if ( *(unsigned int *)DhcpOptions.val[dhcpT2value] == 0 )
	{
	  unsigned t2 = 0.875*ntohl(*(unsigned int *)DhcpOptions.val[dhcpIPaddrLeaseTime]);
	  int t1 = htonl(t2);
	  memcpy(DhcpOptions.val[dhcpT2value],&t1,4);
	  DhcpOptions.len[dhcpT2value] = 4;
	  if ( DebugFlag )
	    syslog(LOG_DEBUG,"dhcpT2value=0 in DHCP server response. Assuming %u sec\n",t2);
	}
    }
  else		/* did not get T2 */
    {
      unsigned t2 = 0.875*ntohl(*(unsigned int *)DhcpOptions.val[dhcpIPaddrLeaseTime]);
      int t1 = htonl(t2);
      DhcpOptions.val[dhcpT2value] = malloc(4);
      memcpy(DhcpOptions.val[dhcpT2value],&t1,4);
      DhcpOptions.len[dhcpT2value] = 4;
      DhcpOptions.num++;
      if ( DebugFlag )
	syslog(LOG_DEBUG,"dhcpT2value option is missing in DHCP server response. Assuming %u sec\n",t2);
    }
  if ( DhcpOptions.val[dhcpMessageType] )
    return *(unsigned char *)DhcpOptions.val[dhcpMessageType];
  return 0;
}
/*****************************************************************************/
void classIDsetup()
{
  struct utsname sname;
  if ( uname(&sname) ) syslog(LOG_ERR,"classIDsetup: uname: %m\n");
  DhcpIface.class_len=snprintf(DhcpIface.class_id,CLASS_ID_MAX_LEN,
  "%s %s %s",sname.sysname,sname.release,sname.machine);
}
/*****************************************************************************/
void clientIDsetup()
{
  unsigned char *c = DhcpIface.client_id;
  *c++ = dhcpClientIdentifier;
  if ( ClientID )
    {
      *c++ = ClientID_len + 1;	/* 1 for the field below */
      *c++ = 0;			/* type: string */
      memcpy(c,ClientID,ClientID_len);
      DhcpIface.client_len = ClientID_len + 3;
      return;
    }
  *c++ = ETH_ALEN + 1;	        /* length: 6 (MAC Addr) + 1 (# field) */
  *c++ = ARPHRD_ETHER;		/* type: Ethernet address */
#if 0
  memcpy(c,DhcpIface.chaddr,ETH_ALEN);
#else
  memcpy(c,ClientHwAddr,ETH_ALEN);
#endif
  DhcpIface.client_len = ETH_ALEN + 3;
}
/*****************************************************************************/
void releaseDhcpOptions()
{
  register int i;
  for (i=1;i<256;i++)
    if ( DhcpOptions.val[i] ) free(DhcpOptions.val[i]);
  memset(&DhcpOptions,0,sizeof(dhcpOptions));
}
/*****************************************************************************/
/* Subtract the `struct timeval' values X and Y,
   storing the result in RESULT.
   Return 1 if the difference is negative, otherwise 0.  */
static int
timeval_subtract (result, x, y)
     struct timeval *result, *x, *y;
{
  /* Perform the carry for the later subtraction by updating Y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }

  /* Compute the time remaining to wait.
     `tv_usec' is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;

  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}
/*****************************************************************************/
int dhcpSendAndRecv(xid,msg,buildUdpIpMsg)
unsigned xid,msg;
void (*buildUdpIpMsg)(unsigned);
{
  struct sockaddr addr;
  struct timeval begin, current, diff;
  int i,len;
  int j=DHCP_INITIAL_RTO/2;
  int timeout;
  const struct udphdr *udpRecv=(struct udphdr *)((char *)(((struct udpiphdr *)UdpIpMsgRecv.udpipmsg)->ip)+sizeof(struct ip));
  char foobuf[512];
  do
    {
      do
    	{
	  j+=j;
	  if (j > DHCP_MAX_RTO) j = DHCP_MAX_RTO;
      	  memset(&addr,0,sizeof(struct sockaddr));
      	  memcpy(addr.sa_data,IfName,IfName_len);
	  buildUdpIpMsg(xid);
      	  if ( sendto(dhcpSocket,&UdpIpMsgSend,
		      sizeof(struct packed_ether_header)+
		      sizeof(udpiphdr)+sizeof(dhcpMessage),0,
		      &addr,sizeof(struct sockaddr)) == -1 )
	    {
	      syslog(LOG_ERR,"sendto: %m\n");
	      return -1;
	    }
	  gettimeofday(&begin, NULL);
      	  i=random();
    	}
      while ( peekfd(dhcpSocket,j+i%200000) );
      do
	{
	  struct ip ipRecv_local;
	  memset(&UdpIpMsgRecv,0,sizeof(udpipMessage));
      	  i=sizeof(struct sockaddr);
      	  len=recvfrom(dhcpSocket,&UdpIpMsgRecv,sizeof(udpipMessage),0,
		     (struct sockaddr *)&addr,&i);
	  if ( len == -1 )
    	    {
      	      syslog(LOG_ERR,"recvfrom: %m\n");
      	      return -1;
    	    }
	  gettimeofday(&current, NULL);
	  timeval_subtract(&diff, &current, &begin);
	  timeout = j - diff.tv_sec*1000000 - diff.tv_usec + random()%200000;
	  if ( UdpIpMsgRecv.ethhdr.ether_type != htons(ETHERTYPE_IP) )
	    continue;
	  /* Use local copy because ipRecv is not aligned.  */
	  memcpy(&ipRecv_local, ((struct udpiphdr *)UdpIpMsgRecv.udpipmsg)->ip,
		 sizeof(struct ip));
	  if ( ipRecv_local.ip_p != IPPROTO_UDP ) continue;
	  len-=sizeof(struct packed_ether_header);
	  i=(int )ntohs(ipRecv_local.ip_len);
	  if ( len < i )
	    {
	      if ( DebugFlag ) syslog(LOG_DEBUG,
		"corrupted IP packet of size=%d and ip_len=%d discarded\n",
		len,i);
	      continue;
	    }
	  len=i-(ipRecv_local.ip_hl<<2);
	  i=(int )ntohs(udpRecv->uh_ulen);
	  if ( len < i )
	    {
	      if ( DebugFlag ) syslog(LOG_DEBUG,
		"corrupted UDP msg of size=%d and uh_ulen=%d discarded\n",
		len,i);
	      continue;
	    }
	  if ( DoCheckSum )
	    {
	      len=udpipchk((udpiphdr *)UdpIpMsgRecv.udpipmsg);
	      if ( len )
		{
		  if ( DebugFlag )
		    switch ( len )
		      {
			case -1: syslog(LOG_DEBUG,
			  "corrupted IP packet with ip_len=%d discarded\n",
			  (int )ntohs(ipRecv_local.ip_len));
			  break;
			case -2: syslog(LOG_DEBUG,
			  "corrupted UDP msg with uh_ulen=%d discarded\n",
			  (int )ntohs(udpRecv->uh_ulen));
			break;
		      }
		  continue;
		}
	    }
	  DhcpMsgRecv = (dhcpMessage *)&UdpIpMsgRecv.udpipmsg[(ipRecv_local.ip_hl<<2)+sizeof(struct udphdr)];
	  if ( DhcpMsgRecv->htype != ARPHRD_ETHER ) continue;
	  if ( DhcpMsgRecv->xid != xid ) continue;
	  if ( DhcpMsgRecv->op != DHCP_BOOTREPLY ) continue;
	  while ( udpFooSocket > 0 && recvfrom(udpFooSocket,(void *)foobuf,sizeof(foobuf),0,NULL,NULL) != -1 );
	  if ( parseDhcpMsgRecv() == msg ) return 0;
	  if ( *(unsigned char *)DhcpOptions.val[dhcpMessageType] == DHCP_NAK )
	    {
	      if ( DhcpOptions.val[dhcpMsg] )
		syslog(LOG_ERR,
		"DHCP_NAK server response received: %s\n",
		(char *)DhcpOptions.val[dhcpMsg]);
	      else
		syslog(LOG_ERR,
		"DHCP_NAK server response received\n");
	      return 1;
	    }
    	}
      while ( timeout > 0 && peekfd(dhcpSocket, timeout) == 0 );
    }
  while ( 1 );
  return 1;
}

/*****************************************************************************/
void execute_on_change(prm)
char *prm;
{
#ifndef __EM86XX__
	syslog(LOG_ERR,"xxx:F:%s, (%s)\n", __FUNCTION__, prm);
	if (strcmp(prm, "down") == 0)
		return;

	/* killall zcip process */
	kill_pidfile("/var/run/zcip.pid", 9);

	/* touch flag file to notify user the IP is gotted*/
	touch("/tmp/get_dhcpip");
#else

	printf("xxx:F:%s, (%s)\n", __FUNCTION__, prm);
	if ( !strcmp(prm, "down") ) {
		/* send signal to dhcp-client to invoke zcip */
		touch("/tmp/dhcpcd_timeout");
		kill_pidfile("/var/run/dhcp-client.pid", SIGUSR1);
	} else {
		/* send signal to dhcp-client to kill zcip */
		touch("/tmp/get_dhcpip");
		kill_pidfile("/var/run/dhcp-client.pid", SIGUSR2);
	}
#endif
	return;
}

/*****************************************************************************/
int dhcpConfig()
{
  int i;
  FILE *f;
  char hostinfo_file_old[128];
  struct ifreq		ifr;
  struct rtentry	rtent;
#ifdef OLD_LINUX_VERSION
  struct sockaddr_pkt	sap;
#endif
  struct sockaddr_in	*p = (struct sockaddr_in *)&(ifr.ifr_addr);
  struct hostent *hp=NULL;
  char *dname=NULL;
  int dname_len=0;

  if ( TestCase ) goto tsc;
  memset(&ifr,0,sizeof(struct ifreq));
#ifdef OLD_LINUX_VERSION
  memcpy(ifr.ifr_name,IfName,IfName_len);
#else
  memcpy(ifr.ifr_name,IfNameExt,IfNameExt_len);
#endif
  p->sin_family = AF_INET;
  p->sin_addr.s_addr = DhcpIface.ciaddr;
  if ( ioctl(dhcpSocket,SIOCSIFADDR,&ifr) == -1 )  /* setting IP address */
    {
      syslog(LOG_ERR,"dhcpConfig: ioctl SIOCSIFADDR: %m\n");
      return -1;
    }
  memcpy(&p->sin_addr.s_addr,DhcpOptions.val[subnetMask],4);
  if ( ioctl(dhcpSocket,SIOCSIFNETMASK,&ifr) == -1 )  /* setting netmask */
    {
      p->sin_addr.s_addr = 0xffffffff; /* try 255.255.255.255 */
      if ( ioctl(dhcpSocket,SIOCSIFNETMASK,&ifr) == -1 )
	{
	  syslog(LOG_ERR,"dhcpConfig: ioctl SIOCSIFNETMASK: %m\n");
	  return -1;
	}
    }
  memcpy(&p->sin_addr.s_addr,DhcpOptions.val[broadcastAddr],4);
  if ( ioctl(dhcpSocket,SIOCSIFBRDADDR,&ifr) == -1 ) /* setting broadcast address */
    syslog(LOG_ERR,"dhcpConfig: ioctl SIOCSIFBRDADDR: %m\n");

  /* setting local route - not needed on later kernels  */
#ifdef OLD_LINUX_VERSION
  memset(&rtent,0,sizeof(struct rtentry));
  p			=	(struct sockaddr_in *)&rtent.rt_dst;
  p->sin_family		=	AF_INET;
  memcpy(&p->sin_addr.s_addr,DhcpOptions.val[subnetMask],4);
  p->sin_addr.s_addr	&=	DhcpIface.ciaddr;
  p			=	(struct sockaddr_in *)&rtent.rt_gateway;
  p->sin_family		=	AF_INET;
  p->sin_addr.s_addr	=	0;
  p			=	(struct sockaddr_in *)&rtent.rt_genmask;
  p->sin_family		=	AF_INET;
  memcpy(&p->sin_addr.s_addr, DhcpOptions.val[subnetMask], 4);
  rtent.rt_dev		=	IfName;
  rtent.rt_metric     	=	1;
  rtent.rt_flags      	=	RTF_UP;
  if ( ioctl(dhcpSocket,SIOCADDRT,&rtent) )
    syslog(LOG_ERR,"dhcpConfig: ioctl SIOCADDRT: %m\n");
#endif

  for (i=0;i<DhcpOptions.len[staticRoute];i+=8)
    {  /* setting static routes */
      memset(&rtent,0,sizeof(struct rtentry));
      p                   =   (struct sockaddr_in *)&rtent.rt_dst;
      p->sin_family	  =	  AF_INET;
      memcpy(&p->sin_addr.s_addr,
      ((char *)DhcpOptions.val[staticRoute])+i,4);
      p		          =	  (struct sockaddr_in *)&rtent.rt_gateway;
      p->sin_family	  =	  AF_INET;
      memcpy(&p->sin_addr.s_addr,
      ((char *)DhcpOptions.val[staticRoute])+i+4,4);
      p		          =	  (struct sockaddr_in *)&rtent.rt_genmask;
      p->sin_family	  =       AF_INET;
      p->sin_addr.s_addr  =	  0xffffffff;
#ifdef OLD_LINUX_VERSION
      rtent.rt_dev	      =	  IfName;
#else
      rtent.rt_dev	      =	  IfNameExt;
#endif
      rtent.rt_metric     =	  1;
      rtent.rt_flags      =	  RTF_UP|RTF_HOST|RTF_GATEWAY;
      if ( ioctl(dhcpSocket,SIOCADDRT,&rtent) )
	syslog(LOG_ERR,"dhcpConfig: ioctl SIOCADDRT: %m\n");
    }
  if ( DhcpOptions.len[routersOnSubnet] > 3 )
  for (i=0;i<DhcpOptions.len[routersOnSubnet];i+=4)
    {  /* setting default routes */
      memset(&rtent,0,sizeof(struct rtentry));
      p			=	(struct sockaddr_in *)&rtent.rt_dst;
      p->sin_family		=	AF_INET;
      p->sin_addr.s_addr	=	0;
      p			=	(struct sockaddr_in *)&rtent.rt_gateway;
      p->sin_family		=	AF_INET;
      memcpy(&p->sin_addr.s_addr,
      ((char *)DhcpOptions.val[routersOnSubnet])+i,4);
      p			=	(struct sockaddr_in *)&rtent.rt_genmask;
      p->sin_family		=	AF_INET;
      p->sin_addr.s_addr	=	0;
#ifdef OLD_LINUX_VERSION
      rtent.rt_dev		=	IfName;
#else
      rtent.rt_dev		=	IfNameExt;
#endif
      rtent.rt_metric	        =	1;
      rtent.rt_window		=	Window;
      rtent.rt_flags	        =	RTF_UP|RTF_GATEWAY|(Window ? RTF_WINDOW : 0);
      if ( ioctl(dhcpSocket,SIOCADDRT,&rtent) == -1 )
	{
	  if ( errno == ENETUNREACH )    /* possibly gateway is over the bridge */
	    {                            /* try adding a route to gateway first */
	      memset(&rtent,0,sizeof(struct rtentry));
	      p                   =   (struct sockaddr_in *)&rtent.rt_dst;
	      p->sin_family	      =	  AF_INET;
	      memcpy(&p->sin_addr.s_addr,
	      ((char *)DhcpOptions.val[routersOnSubnet])+i,4);
	      p		      =	  (struct sockaddr_in *)&rtent.rt_gateway;
	      p->sin_family	      =	  AF_INET;
	      p->sin_addr.s_addr  =   0;
	      p		      =	  (struct sockaddr_in *)&rtent.rt_genmask;
	      p->sin_family	      =   AF_INET;
	      p->sin_addr.s_addr  =	  0xffffffff;
#ifdef OLD_LINUX_VERSION
	      rtent.rt_dev	      =	  IfName;
#else
	      rtent.rt_dev	      =	  IfNameExt;
#endif
	      rtent.rt_metric     =	  0;
	      rtent.rt_flags      =	  RTF_UP|RTF_HOST;
	      if ( ioctl(dhcpSocket,SIOCADDRT,&rtent) == 0 )
		{
		  memset(&rtent,0,sizeof(struct rtentry));
		  p    	             =	(struct sockaddr_in *)&rtent.rt_dst;
		  p->sin_family	     =	AF_INET;
		  p->sin_addr.s_addr =	0;
		  p		     =	(struct sockaddr_in *)&rtent.rt_gateway;
		  p->sin_family	     =	AF_INET;
		  memcpy(&p->sin_addr.s_addr,
		  ((char *)DhcpOptions.val[routersOnSubnet])+i,4);
		  p		     =	(struct sockaddr_in *)&rtent.rt_genmask;
		  p->sin_family	     =	AF_INET;
		  p->sin_addr.s_addr =	0;
#ifdef OLD_LINUX_VERSION
		  rtent.rt_dev	     =	IfName;
#else
		  rtent.rt_dev	     =	IfNameExt;
#endif
		  rtent.rt_metric    =	1;
		  rtent.rt_window    =  Window;
	          rtent.rt_flags     =	RTF_UP|RTF_GATEWAY|(Window ? RTF_WINDOW : 0);
	          if ( ioctl(dhcpSocket,SIOCADDRT,&rtent) == -1 )
		    syslog(LOG_ERR,"dhcpConfig: ioctl SIOCADDRT: %m\n");
		}
	    }
	  else
	    syslog(LOG_ERR,"dhcpConfig: ioctl SIOCADDRT: %m\n");
	}
    }

  /* rebind dhcpSocket after changing ip address to avoid problems with 2.0 kernels */
#ifdef OLD_LINUX_VERSION
  memset(&sap,0,sizeof(sap));
  sap.spkt_family = AF_INET;
  sap.spkt_protocol = htons(ETH_P_ALL);
  memcpy(sap.spkt_device,IfName,IfName_len);
  if ( bind(dhcpSocket,(void*)&sap,sizeof(struct sockaddr)) == -1 )
    syslog(LOG_ERR,"dhcpConfig: bind: %m\n");
#endif  

  arpInform();
  if ( DebugFlag )
    fprintf(stdout,"dhcpcd: your IP address = %u.%u.%u.%u\n",
    ((unsigned char *)&DhcpIface.ciaddr)[0],
    ((unsigned char *)&DhcpIface.ciaddr)[1],
    ((unsigned char *)&DhcpIface.ciaddr)[2],
    ((unsigned char *)&DhcpIface.ciaddr)[3]);
  if ( ReplResolvConf && DhcpOptions.len[dns])
    {
      resolv_renamed=1+rename(RESOLV_CONF,""RESOLV_CONF".sv");
      f=fopen(RESOLV_CONF,"w");
      if ( f )
	{
	  int i;
#if 0
	  if ( DhcpOptions.len[nisDomainName] )
	    fprintf(f,"domain %s\n",(char *)DhcpOptions.val[nisDomainName]);
	  else
	    if ( DhcpOptions.len[domainName] )
	      fprintf(f,"domain %s\n",(char *)DhcpOptions.val[domainName]);
#endif
	  for (i=0;i<DhcpOptions.len[dns];i+=4)
	    fprintf(f,"nameserver %u.%u.%u.%u\n",
	    ((unsigned char *)DhcpOptions.val[dns])[i],
	    ((unsigned char *)DhcpOptions.val[dns])[i+1],
	    ((unsigned char *)DhcpOptions.val[dns])[i+2],
	    ((unsigned char *)DhcpOptions.val[dns])[i+3]);
#if 0
	  if ( DhcpOptions.len[nisDomainName] + DhcpOptions.len[domainName] )
	    {
	      fprintf(f,"search");
	      if ( DhcpOptions.len[nisDomainName] )
	        fprintf(f," %s",(char *)DhcpOptions.val[nisDomainName]);
	      if ( DhcpOptions.len[domainName] )
	        fprintf(f," %s",(char *)DhcpOptions.val[domainName]);
	      fprintf(f,"\n");
	    }
#else
	  if ( DhcpOptions.len[domainName] )
	    fprintf(f,"search %s\n",(char *)DhcpOptions.val[domainName]);
#endif
	  fclose(f);
	}
      else
	syslog(LOG_ERR,"dhcpConfig: fopen: %m\n");

   /* moved the next section of code from before to after we've created
    * resolv.conf. See below for explanation. <poeml@suse.de>
    * res_init() is normally called from within the first function of the
    * resolver which is called. Here, we want resolv.conf to be
    * reread. Otherwise, we won't be able to find out about our hostname,
    * because the resolver won't notice the change in resolv.conf */
      (void)res_init();
    }
  if ( ReplNISConf && DhcpOptions.len[nisDomainName] )
    {
      yp_renamed=1+rename(NIS_CONF,""NIS_CONF".sv");
      f=fopen(NIS_CONF,"w");
      if ( f )
	{
	  int i;
	  char *domain=(char *)DhcpOptions.val[nisDomainName]; setdomainname(domain, strlen(domain)+1);
	  for (i=0;i<DhcpOptions.len[nisServers];i+=4)
	    fprintf(f,"domain %s server %u.%u.%u.%u\n",(domain?domain:"localdomain"),
	    ((unsigned char *)DhcpOptions.val[nisServers])[i],
	    ((unsigned char *)DhcpOptions.val[nisServers])[i+1],
	    ((unsigned char *)DhcpOptions.val[nisServers])[i+2],
	    ((unsigned char *)DhcpOptions.val[nisServers])[i+3]);
	  if ( !DhcpOptions.len[nisServers] )
	    fprintf(f,"domain %s broadcast\n", (domain?domain:"localdomain"));
	  fclose(f);
	}
      else
	syslog(LOG_ERR,"dhcpConfig: fopen: %m\n");
    }
  if ( ReplNTPConf && DhcpOptions.len[ntpServers] >= 4)
    {
      ntp_renamed=1+rename(NTP_CONF,""NTP_CONF".sv");
      f=fopen(NTP_CONF,"w");
      if ( f )
 	{
 	  int net, mask;
 	  memcpy(&mask,DhcpOptions.val[subnetMask],4);
 	  net = DhcpIface.ciaddr & mask;

 	  /* Note: Revise drift/log file names and stratum for local clock */
 	  fprintf(f,"restrict default noquery notrust nomodify\n");
 	  fprintf(f,"restrict 127.0.0.1\n");
 	  fprintf(f,"restrict %u.%u.%u.%u mask %u.%u.%u.%u\n",
 		  ((unsigned char *)&net)[0],
 		  ((unsigned char *)&net)[1],
 		  ((unsigned char *)&net)[2],
 		  ((unsigned char *)&net)[3],
 		  ((unsigned char *)&mask)[0],
 		  ((unsigned char *)&mask)[1],
 		  ((unsigned char *)&mask)[2],
 		  ((unsigned char *)&mask)[3]);
 	  if ( DhcpOptions.len[ntpServers]>=4 )
	    {
	      int i;
	      char addr[4*3+3*1+1];
	      for (i=0;i<DhcpOptions.len[ntpServers];i+=4)
		{
		  snprintf(addr,sizeof(addr),"%u.%u.%u.%u",
		  ((unsigned char *)DhcpOptions.val[ntpServers])[i],
		  ((unsigned char *)DhcpOptions.val[ntpServers])[i+1],
		  ((unsigned char *)DhcpOptions.val[ntpServers])[i+2],
		  ((unsigned char *)DhcpOptions.val[ntpServers])[i+3]);
		  fprintf(f,"restrict %s\nserver %s\n",addr,addr);
		}
 	    }
	  else
	    {		/* No servers found, use local clock */
	      fprintf(f, "fudge 127.127.1.0 stratum 3\n");
 	      fprintf(f, "server 127.127.1.0\n");
	    }
 	  fprintf(f, "driftfile /etc/ntp.drift\n");
 	  fprintf(f, "logfile /var/log/ntp.log\n");
 	  fclose(f);
 	}
       else
 	syslog(LOG_ERR,"dhcpConfig: fopen: %m\n");
     }
  if ( SetHostName )
    {
      if ( ! DhcpOptions.len[hostName] )
	{
	  hp=gethostbyaddr((char *)&DhcpIface.ciaddr,
	  sizeof(DhcpIface.ciaddr),AF_INET);
	  if ( hp )
	    {
	      dname=hp->h_name;
	      while ( *dname > 32 )
#if 0
		if ( *dname == '.' )
		  break;
		else
#endif
		  dname++;
	      dname_len=dname-hp->h_name;
	      DhcpOptions.val[hostName]=(char *)malloc(dname_len+1);
	      DhcpOptions.len[hostName]=dname_len;
	      memcpy((char *)DhcpOptions.val[hostName],
	      hp->h_name,dname_len);
	      ((char *)DhcpOptions.val[hostName])[dname_len]=0;
	      DhcpOptions.num++;
	    }
	}
      if ( InitialHostName_len<0 && gethostname(InitialHostName,sizeof(InitialHostName))==0 )
	{
	  InitialHostName_len=strlen(InitialHostName);
	  if ( DebugFlag )
	    fprintf(stdout,"dhcpcd: orig hostname = %s\n",InitialHostName);
	}
      if ( DhcpOptions.len[hostName] )
        {
          sethostname(DhcpOptions.val[hostName],DhcpOptions.len[hostName]);
	  if ( DebugFlag )
	    fprintf(stdout,"dhcpcd: your hostname = %s\n",
	    (char *)DhcpOptions.val[hostName]);
	}
    }
  if ( SetDomainName )
    {
      if ( InitialDomainName_len<0 && getdomainname(InitialDomainName,sizeof(InitialDomainName))==0 )
	{
	  InitialDomainName_len=strlen(InitialDomainName);
	  if ( DebugFlag )
	    fprintf(stdout,"dhcpcd: orig domainname = %s\n",InitialDomainName);
	}
#if 0
      if ( DhcpOptions.len[nisDomainName] )
        {
          setdomainname(DhcpOptions.val[nisDomainName],
		      DhcpOptions.len[nisDomainName]);
	  if ( DebugFlag )
	    fprintf(stdout,"dhcpcd: your domainname = %s\n",
		(char *)DhcpOptions.val[nisDomainName]);
        }
      else
        {
#endif
	  if ( ! DhcpOptions.len[domainName] )
	    {
	      if ( ! hp )
		hp=gethostbyaddr((char *)&DhcpIface.ciaddr,
		sizeof(DhcpIface.ciaddr),AF_INET);
	      if ( hp )
		{
		  dname=hp->h_name;
		  while ( *dname > 32 )
		    if ( *dname == '.' )
		      {
			dname++;
		        break;
		      }
		    else
		      dname++;
		  dname_len=strlen(dname);
		  if ( dname_len )
		    {
		      DhcpOptions.val[domainName]=(char *)malloc(dname_len+1);
		      DhcpOptions.len[domainName]=dname_len;
		      memcpy((char *)DhcpOptions.val[domainName],
		      dname,dname_len);
		      ((char *)DhcpOptions.val[domainName])[dname_len]=0;
		      DhcpOptions.num++;
		    }
		}
	    }
          if ( DhcpOptions.len[domainName] )
            {
	      setdomainname(DhcpOptions.val[domainName],
		DhcpOptions.len[domainName]);
	      if ( DebugFlag )
		fprintf(stdout,"dhcpcd: your domainname = %s\n",
		(char *)DhcpOptions.val[domainName]);
	    }
#if 0
	}
#endif
    }
tsc:
  memset(DhcpIface.version,0,sizeof(DhcpIface.version));
  strncpy(DhcpIface.version,VERSION,sizeof(DhcpIface.version));

  writeDhcpCache();

  snprintf(hostinfo_file,sizeof(hostinfo_file),DHCP_HOSTINFO,ConfigDir,IfNameExt);
  snprintf(hostinfo_file_old,sizeof(hostinfo_file_old),""DHCP_HOSTINFO".old",ConfigDir,IfNameExt);
  rename(hostinfo_file,hostinfo_file_old);
  f=fopen(hostinfo_file,"w");
  if ( f )
    {
      int b,c;
      memcpy(&b,DhcpOptions.val[subnetMask],4);
      c = DhcpIface.ciaddr & b;
      fprintf(f,"\
IPADDR=%u.%u.%u.%u\n\
NETMASK=%u.%u.%u.%u\n\
NETWORK=%u.%u.%u.%u\n\
BROADCAST=%u.%u.%u.%u\n",
((unsigned char *)&DhcpIface.ciaddr)[0],
((unsigned char *)&DhcpIface.ciaddr)[1],
((unsigned char *)&DhcpIface.ciaddr)[2],
((unsigned char *)&DhcpIface.ciaddr)[3],
((unsigned char *)DhcpOptions.val[subnetMask])[0],
((unsigned char *)DhcpOptions.val[subnetMask])[1],
((unsigned char *)DhcpOptions.val[subnetMask])[2],
((unsigned char *)DhcpOptions.val[subnetMask])[3],
((unsigned char *)&c)[0],
((unsigned char *)&c)[1],
((unsigned char *)&c)[2],
((unsigned char *)&c)[3],
((unsigned char *)DhcpOptions.val[broadcastAddr])[0],
((unsigned char *)DhcpOptions.val[broadcastAddr])[1],
((unsigned char *)DhcpOptions.val[broadcastAddr])[2],
((unsigned char *)DhcpOptions.val[broadcastAddr])[3]);
      if ( DhcpOptions.len[routersOnSubnet] > 3 )
	{
	  fprintf(f,"\
GATEWAY=%u.%u.%u.%u",
((unsigned char *)DhcpOptions.val[routersOnSubnet])[0],
((unsigned char *)DhcpOptions.val[routersOnSubnet])[1],
((unsigned char *)DhcpOptions.val[routersOnSubnet])[2],
((unsigned char *)DhcpOptions.val[routersOnSubnet])[3]);
	  for (i=4;i<DhcpOptions.len[routersOnSubnet];i+=4)
  	    fprintf(f,",%u.%u.%u.%u",
	    ((unsigned char *)DhcpOptions.val[routersOnSubnet])[i],
	    ((unsigned char *)DhcpOptions.val[routersOnSubnet])[1+i],
	    ((unsigned char *)DhcpOptions.val[routersOnSubnet])[2+i],
	    ((unsigned char *)DhcpOptions.val[routersOnSubnet])[3+i]);
	}
if ( DhcpOptions.len[staticRoute] )
  {
    fprintf(f,"\nROUTE=%u.%u.%u.%u,%u.%u.%u.%u",
    ((unsigned char *)DhcpOptions.val[staticRoute])[0],
    ((unsigned char *)DhcpOptions.val[staticRoute])[1],
    ((unsigned char *)DhcpOptions.val[staticRoute])[2],
    ((unsigned char *)DhcpOptions.val[staticRoute])[3],
    ((unsigned char *)DhcpOptions.val[staticRoute])[4],
    ((unsigned char *)DhcpOptions.val[staticRoute])[5],
    ((unsigned char *)DhcpOptions.val[staticRoute])[6],
    ((unsigned char *)DhcpOptions.val[staticRoute])[7]);
    for (i=8;i<DhcpOptions.len[staticRoute];i+=8)
    fprintf(f,",%u.%u.%u.%u,%u.%u.%u.%u",
    ((unsigned char *)DhcpOptions.val[staticRoute])[i],
    ((unsigned char *)DhcpOptions.val[staticRoute])[1+i],
    ((unsigned char *)DhcpOptions.val[staticRoute])[2+i],
    ((unsigned char *)DhcpOptions.val[staticRoute])[3+i],
    ((unsigned char *)DhcpOptions.val[staticRoute])[4+i],
    ((unsigned char *)DhcpOptions.val[staticRoute])[5+i],
    ((unsigned char *)DhcpOptions.val[staticRoute])[6+i],
    ((unsigned char *)DhcpOptions.val[staticRoute])[7+i]);
  }
if ( DhcpOptions.len[hostName] )
  fprintf(f,"\nHOSTNAME=%s",(char *)DhcpOptions.val[hostName]);
if ( DhcpOptions.len[domainName] )
  fprintf(f,"\nDOMAIN=%s",(char *)DhcpOptions.val[domainName]);
if ( DhcpOptions.len[nisDomainName] )
  fprintf(f,"\nNISDOMAIN=%s",(char *)DhcpOptions.val[nisDomainName]);
if ( DhcpOptions.len[rootPath] )
  fprintf(f,"\nROOTPATH=%s",(char *)DhcpOptions.val[rootPath]);
fprintf(f,"\n\
DNS=%u.%u.%u.%u",
((unsigned char *)DhcpOptions.val[dns])[0],
((unsigned char *)DhcpOptions.val[dns])[1],
((unsigned char *)DhcpOptions.val[dns])[2],
((unsigned char *)DhcpOptions.val[dns])[3]);
for (i=4;i<DhcpOptions.len[dns];i+=4)
  fprintf(f,",%u.%u.%u.%u",
  ((unsigned char *)DhcpOptions.val[dns])[i],
  ((unsigned char *)DhcpOptions.val[dns])[1+i],
  ((unsigned char *)DhcpOptions.val[dns])[2+i],
  ((unsigned char *)DhcpOptions.val[dns])[3+i]);
if ( DhcpOptions.len[ntpServers]>=4 )
  {
    fprintf(f,"\nNTPSERVERS=%u.%u.%u.%u",
    ((unsigned char *)DhcpOptions.val[ntpServers])[0],
    ((unsigned char *)DhcpOptions.val[ntpServers])[1],
    ((unsigned char *)DhcpOptions.val[ntpServers])[2],
    ((unsigned char *)DhcpOptions.val[ntpServers])[3]);
    for (i=4;i<DhcpOptions.len[ntpServers];i+=4)
      fprintf(f,",%u.%u.%u.%u",
      ((unsigned char *)DhcpOptions.val[ntpServers])[i],
      ((unsigned char *)DhcpOptions.val[ntpServers])[1+i],
      ((unsigned char *)DhcpOptions.val[ntpServers])[2+i],
      ((unsigned char *)DhcpOptions.val[ntpServers])[3+i]);
  }
if ( DhcpOptions.len[nisServers]>=4 )
  {
    fprintf(f,"\nNISSERVERS=%u.%u.%u.%u",
    ((unsigned char *)DhcpOptions.val[nisServers])[0],
    ((unsigned char *)DhcpOptions.val[nisServers])[1],
    ((unsigned char *)DhcpOptions.val[nisServers])[2],
    ((unsigned char *)DhcpOptions.val[nisServers])[3]);
    for (i=4;i<DhcpOptions.len[nisServers];i+=4)
      fprintf(f,",%u.%u.%u.%u",
      ((unsigned char *)DhcpOptions.val[nisServers])[i],
      ((unsigned char *)DhcpOptions.val[nisServers])[1+i],
      ((unsigned char *)DhcpOptions.val[nisServers])[2+i],
      ((unsigned char *)DhcpOptions.val[nisServers])[3+i]);
  }
fprintf(f,"\n\
DHCPSID=%u.%u.%u.%u\n\
DHCPGIADDR=%u.%u.%u.%u\n\
DHCPSIADDR=%u.%u.%u.%u\n\
DHCPCHADDR=%02X:%02X:%02X:%02X:%02X:%02X\n\
DHCPSHADDR=%02X:%02X:%02X:%02X:%02X:%02X\n\
DHCPSNAME=%s\n\
LEASETIME=%u\n\
RENEWALTIME=%u\n\
REBINDTIME=%u\n\
INTERFACE=%s\n\
CLASSID=\"%s\"\n",
((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[0],
((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[1],
((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[2],
((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[3],
((unsigned char *)&DhcpMsgRecv->giaddr)[0],
((unsigned char *)&DhcpMsgRecv->giaddr)[1],
((unsigned char *)&DhcpMsgRecv->giaddr)[2],
((unsigned char *)&DhcpMsgRecv->giaddr)[3],
((unsigned char *)&DhcpMsgRecv->siaddr)[0],
((unsigned char *)&DhcpMsgRecv->siaddr)[1],
((unsigned char *)&DhcpMsgRecv->siaddr)[2],
((unsigned char *)&DhcpMsgRecv->siaddr)[3],
ClientHwAddr[0],
ClientHwAddr[1],
ClientHwAddr[2],
ClientHwAddr[3],
ClientHwAddr[4],
ClientHwAddr[5],
DhcpIface.shaddr[0],
DhcpIface.shaddr[1],
DhcpIface.shaddr[2],
DhcpIface.shaddr[3],
DhcpIface.shaddr[4],
DhcpIface.shaddr[5],
DhcpMsgRecv->sname,
ntohl(*(unsigned int *)DhcpOptions.val[dhcpIPaddrLeaseTime]),
ntohl(*(unsigned int *)DhcpOptions.val[dhcpT1value]),
ntohl(*(unsigned int *)DhcpOptions.val[dhcpT2value]),
IfNameExt,
DhcpIface.class_id);
      if ( ClientID )
	fprintf(f,"CLIENTID=\"%s\"\n",ClientID);
      else
	fprintf(f,"CLIENTID=%02X:%02X:%02X:%02X:%02X:%02X\n",
DhcpIface.client_id[3],DhcpIface.client_id[4],DhcpIface.client_id[5],
DhcpIface.client_id[6],DhcpIface.client_id[7],DhcpIface.client_id[8]);
      fclose(f);
    }
  else
    syslog(LOG_ERR,"dhcpConfig: fopen: %m\n");
#if 0
  if ( Cfilename )
    if ( fork() == 0 )
      {
	char *argc[2];
	argc[0]=Cfilename;
	argc[1]=NULL;
	if ( execve(Cfilename,argc,ProgramEnviron) )
	  syslog(LOG_ERR,"error executing \"%s\": %m\n",
	  Cfilename);
	exit(0);
      }
#endif
  if ( DhcpIface.ciaddr == prev_ip_addr )
    execute_on_change("up");
  else					/* IP address has changed */
    {
      execute_on_change("new");
      prev_ip_addr=DhcpIface.ciaddr;
    }
  if ( *(unsigned int *)DhcpOptions.val[dhcpIPaddrLeaseTime] == 0xffffffff )
    {
      syslog(LOG_INFO,"infinite IP address lease time. Exiting\n");
      exit(0);
    }
  return 0;
}

/*****************************************************************************/
void *dhcpStart()
{
  int o = 1, i=0;
  struct ifreq	ifr;
  struct sockaddr_pkt sap;
  struct sockaddr_in clientAddr;
  memset(&ifr,0,sizeof(struct ifreq));
  memcpy(ifr.ifr_name,IfName,IfName_len);
#ifdef OLD_LINUX_VERSION
  dhcpSocket = socket(AF_INET,SOCK_PACKET,htons(ETH_P_ALL));
#else
  dhcpSocket = socket(AF_PACKET,SOCK_PACKET,htons(ETH_P_ALL));
#endif
  if ( dhcpSocket == -1 )
    {
      syslog(LOG_ERR,"dhcpStart: socket: %m\n");
      exit(1);
    }

  if ( ioctl(dhcpSocket,SIOCGIFHWADDR,&ifr) )
    {
      syslog(LOG_ERR,"dhcpStart: ioctl SIOCGIFHWADDR: %m\n");
      exit(1);
    }
  if ( ifr.ifr_hwaddr.sa_family != ARPHRD_ETHER && ifr.ifr_hwaddr.sa_family != ARPHRD_IEEE802 )
    {
      syslog(LOG_ERR,"dhcpStart: interface %s is not Ethernet or 802.2 Token Ring\n",ifr.ifr_name);
      exit(1);
    }
  if ( setsockopt(dhcpSocket,SOL_SOCKET,SO_BROADCAST,&o,sizeof(o)) == -1 )
    {
      syslog(LOG_ERR,"dhcpStart: setsockopt: %m\n");
      exit(1);
    }
  if ( ioctl(dhcpSocket,SIOCGIFFLAGS,&ifr) )  
    {  
      syslog(LOG_ERR,"dhcpStart: ioctl SIOCGIFFLAGS: %m\n");  
      exit(1);  
    }  
  saved_if_flags = ifr.ifr_flags;  
  ifr.ifr_flags = saved_if_flags | IFF_UP | IFF_BROADCAST | IFF_NOTRAILERS | IFF_RUNNING;
  if ( ioctl(dhcpSocket,SIOCSIFFLAGS,&ifr) )
    {
      syslog(LOG_ERR,"dhcpStart: ioctl SIOCSIFFLAGS: %m\n");
      exit(1);
    }
  memset(&sap,0,sizeof(sap));

  do
    {
      i++;
      if ( i>1 )
	syslog(LOG_WARNING,"dhcpStart: retrying MAC address request "
	"(returned %02x:%02x:%02x:%02x:%02x:%02x)",
	ClientHwAddr[0],ClientHwAddr[1],ClientHwAddr[2],
	ClientHwAddr[3],ClientHwAddr[4],ClientHwAddr[5]);
      if ( ioctl(dhcpSocket,SIOCGIFHWADDR,&ifr) )
        {
	  syslog(LOG_ERR,"dhcpStart: ioctl SIOCGIFHWADDR: %m\n");
	  exit(1);
	}
      if ( ifr.ifr_hwaddr.sa_family != ARPHRD_ETHER && ifr.ifr_hwaddr.sa_family != ARPHRD_IEEE802 )
	{
	  syslog(LOG_ERR,"dhcpStart: interface %s is not Ethernet or 802.2 Token Ring\n",ifr.ifr_name);
	  exit(1);
	}
      if ( setsockopt(dhcpSocket,SOL_SOCKET,SO_BROADCAST,&o,sizeof(o)) == -1 )
	{
	  syslog(LOG_ERR,"dhcpStart: setsockopt: %m\n");
	  exit(1);
	}
      ifr.ifr_flags = saved_if_flags | IFF_UP | IFF_BROADCAST | IFF_NOTRAILERS | IFF_RUNNING;
      if ( ioctl(dhcpSocket,SIOCSIFFLAGS,&ifr) )
	{
	  syslog(LOG_ERR,"dhcpStart: ioctl SIOCSIFFLAGS: %m\n");
	  exit(1);
	}
      memset(&sap,0,sizeof(sap));
      sap.spkt_protocol = htons(ETH_P_ALL);
      memcpy(sap.spkt_device,IfName,IfName_len);
#ifdef OLD_LINUX_VERSION
      sap.spkt_family = AF_INET;
#else
      sap.spkt_family = AF_PACKET;
#endif
      if ( bind(dhcpSocket,(void*)&sap,sizeof(struct sockaddr)) == -1 )
        syslog(LOG_ERR,"dhcpStart: bind: %m\n");

      memcpy(ClientHwAddr,ifr.ifr_hwaddr.sa_data,ETH_ALEN);
      if ( DebugFlag )
	fprintf(stdout,"dhcpcd: MAC address = %02x:%02x:%02x:%02x:%02x:%02x\n",
	ClientHwAddr[0], ClientHwAddr[1], ClientHwAddr[2],
	ClientHwAddr[3], ClientHwAddr[4], ClientHwAddr[5]);
    }
  while ( !ClientHwAddr[0] &&
	  !ClientHwAddr[1] &&
	  !ClientHwAddr[2] &&
	  !ClientHwAddr[3] &&
	  !ClientHwAddr[4] &&
	  !ClientHwAddr[5] &&
	   i<HWADDR_TRIES );

  ip_id=time(NULL)&0xffff;
  srandom(ip_id);

  udpFooSocket = socket(AF_INET,SOCK_DGRAM,0);
  if ( udpFooSocket == -1 )
    {
      syslog(LOG_ERR,"dhcpStart: socket: %m\n");
      exit(1);
    }
  if ( setsockopt(udpFooSocket,SOL_SOCKET,SO_BROADCAST,&o,sizeof(o)) )
    syslog(LOG_ERR,"dhcpStart: setsockopt: %m\n");
  memset(&clientAddr.sin_addr,0,sizeof(&clientAddr.sin_addr));
  clientAddr.sin_family = AF_INET;
  clientAddr.sin_port = htons(DHCP_CLIENT_PORT);
  if ( bind(udpFooSocket,(struct sockaddr *)&clientAddr,sizeof(clientAddr)) )
    {
      if ( errno != EADDRINUSE )
	syslog(LOG_ERR,"dhcpStart: bind: %m\n");
      close(udpFooSocket);
      udpFooSocket = -1;
    }
  else
    if ( fcntl(udpFooSocket,F_SETFL,O_NONBLOCK) == -1 )
      {
	syslog(LOG_ERR,"dhcpStart: fcntl: %m\n");
	exit(1);
      }

  return &dhcpInit;
}
/*****************************************************************************/
void *dhcpReboot()
{
  dhcpStart();
  memset(&DhcpOptions,0,sizeof(DhcpOptions));
  memset(&DhcpIface,0,sizeof(dhcpInterface));
  if ( readDhcpCache() < 0 )
    {
      struct ifreq	ifr;
      struct sockaddr_in *p = (struct sockaddr_in *)&(ifr.ifr_addr);
      memset(&DhcpIface,0,sizeof(dhcpInterface));
      memset(&ifr,0,sizeof(struct ifreq));
#ifdef OLD_LINUX_VERSION
      memcpy(ifr.ifr_name,IfName,IfName_len);
#else
      memcpy(ifr.ifr_name,IfNameExt,IfNameExt_len);
#endif
      p->sin_family = AF_INET;
      if ( ioctl(dhcpSocket,SIOCGIFADDR,&ifr) == 0 )
        DhcpIface.ciaddr=p->sin_addr.s_addr;
#if 0
      if ( ClientMACaddr_ind )
        memcpy(DhcpIface.chaddr,ClientMACaddr,ETH_ALEN);
      else
        memcpy(DhcpIface.chaddr,ClientHwAddr,ETH_ALEN);
#endif
      if ( ClassID )
	{
    	  memcpy(DhcpIface.class_id,ClassID,ClassID_len);
	  DhcpIface.class_len=ClassID_len;
	}
      else
	classIDsetup();
      clientIDsetup();
      return &dhcpInit;
    }
#if 0
  if ( ClientMACaddr_ind )
    memcpy(DhcpIface.chaddr,ClientMACaddr,ETH_ALEN);
  else
    memcpy(DhcpIface.chaddr,ClientHwAddr,ETH_ALEN);
#endif
  if ( sigsetjmp(env,0xffff) )
    {
      /* If we got here it means that the dhcp server wasn't available
         in a reboot state but we have a cache file in place.  Use the
         cached information if the timeout was infinite. */
      if ( DhcpOptionsCached.val[dhcpIPaddrLeaseTime] &&
	   *(unsigned int *)DhcpOptionsCached.val[dhcpIPaddrLeaseTime] == 0xffffffff) {
	syslog(LOG_INFO, "Infinite IP address lease time in cache.  Using old settings.\n");

	/* use the cached dhcp options */
	useDhcpOptionsCached();

	/* configure our interface */
	if (dhcpConfig()) {
	  dhcpStop();
	  return 0;
	}
      }

      if ( DebugFlag )
	syslog(LOG_DEBUG,"timed out waiting for DHCP_ACK response\n");
      alarm(TimeOut);
      return &dhcpInit;
    }
  return dhcpRequest(random(),&buildDhcpReboot);
}
/*****************************************************************************/
void *dhcpInit()
{
  releaseDhcpOptions();
  releaseDhcpOptionsCached();

#ifdef DEBUG
fprintf(stderr,"ClassID  = \"%s\"\n\
ClientID = \"%u.%u.%u.%02X.%02X.%02X.%02X.%02X.%02X\"\n",
DhcpIface.class_id,
DhcpIface.client_id[0],DhcpIface.client_id[1],DhcpIface.client_id[2],
DhcpIface.client_id[3],DhcpIface.client_id[4],DhcpIface.client_id[5],
DhcpIface.client_id[6],DhcpIface.client_id[7],DhcpIface.client_id[8]);
#endif

#ifdef __EM86XX__
  if ( sigsetjmp(env,0xffff) )
    {
      if ( DebugFlag )
	syslog(LOG_DEBUG,"timed out waiting for DHCP_ACK response\n");
      alarm(TimeOut);
    }
#endif

  if ( DebugFlag ) syslog(LOG_DEBUG,"broadcasting DHCP_DISCOVER\n");
  if ( dhcpSendAndRecv(random(),DHCP_OFFER,&buildDhcpDiscover) )
    {
      dhcpStop();
      return 0;
    }
  if ( DebugFlag ) syslog(LOG_DEBUG,"broadcasting second DHCP_DISCOVER\n");
  dhcpSendAndRecv(DhcpMsgRecv->xid,DHCP_OFFER,&buildDhcpDiscover);
  prev_ip_addr = DhcpIface.ciaddr;
  DhcpIface.ciaddr = DhcpMsgRecv->yiaddr;
  memcpy(&DhcpIface.siaddr,DhcpOptions.val[dhcpServerIdentifier],4);
  memcpy(DhcpIface.shaddr,UdpIpMsgRecv.ethhdr.ether_shost,ETH_ALEN);
  DhcpIface.xid = DhcpMsgRecv->xid;
/* DHCP_OFFER received */
  if ( DebugFlag )
    syslog(LOG_DEBUG,"DHCP_OFFER received from %s (%u.%u.%u.%u)\n",
    DhcpMsgRecv->sname,
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[0],
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[1],
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[2],
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[3]);

  return dhcpRequest(DhcpIface.xid,&buildDhcpRequest);
}
/*****************************************************************************/
void *dhcpRequest(xid,buildDhcpMsg)
unsigned xid;
void (*buildDhcpMsg)(unsigned);
{

/* send the message and read and parse replies into DhcpOptions */
  if ( DebugFlag )
    syslog(LOG_DEBUG,"broadcasting DHCP_REQUEST for %u.%u.%u.%u\n",
	   ((unsigned char *)&DhcpIface.ciaddr)[0],
	   ((unsigned char *)&DhcpIface.ciaddr)[1],
	   ((unsigned char *)&DhcpIface.ciaddr)[2],
	   ((unsigned char *)&DhcpIface.ciaddr)[3]);
  if ( dhcpSendAndRecv(xid,DHCP_ACK,buildDhcpMsg) ) return &dhcpInit;
  ReqSentTime=time(NULL);
  if ( DebugFlag ) syslog(LOG_DEBUG,
    "DHCP_ACK received from %s (%u.%u.%u.%u)\n",DhcpMsgRecv->sname,
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[0],
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[1],
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[2],
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[3]);
#ifdef ARPCHECK
/* check if the offered IP address already in use */
  if ( arpCheck() )
    {
      if ( DebugFlag ) syslog(LOG_DEBUG,
	"requested %u.%u.%u.%u address is in use\n",
	((unsigned char *)&DhcpIface.ciaddr)[0],
	((unsigned char *)&DhcpIface.ciaddr)[1],
	((unsigned char *)&DhcpIface.ciaddr)[2],
	((unsigned char *)&DhcpIface.ciaddr)[3]);
      dhcpDecline();
      DhcpIface.ciaddr = 0;
      return &dhcpInit;
    }
  if ( DebugFlag ) syslog(LOG_DEBUG,
    "verified %u.%u.%u.%u address is not in use\n",
    ((unsigned char *)&DhcpIface.ciaddr)[0],
    ((unsigned char *)&DhcpIface.ciaddr)[1],
    ((unsigned char *)&DhcpIface.ciaddr)[2],
    ((unsigned char *)&DhcpIface.ciaddr)[3]);
#endif
  if ( dhcpConfig() )
    {
      dhcpStop();
      return 0;
    }

  /* Successfull ACK: Use the fields obtained for future requests */
  memcpy(&DhcpIface.siaddr,DhcpOptions.val[dhcpServerIdentifier],4);
  memcpy(DhcpIface.shaddr,UdpIpMsgRecv.ethhdr.ether_shost,ETH_ALEN);

  return &dhcpBound;
}
/*****************************************************************************/
void *dhcpBound()
{
  int i;
  if ( sigsetjmp(env,0xffff) ) return &dhcpRenew;
  i=ReqSentTime+ntohl(*(unsigned int *)DhcpOptions.val[dhcpT1value])-time(NULL);
  if ( i > 0 )
    alarm(i);
  else
    return &dhcpRenew;

  sleep(ntohl(*(u_int *)DhcpOptions.val[dhcpT1value]));
  return &dhcpRenew;
}
/*****************************************************************************/
void *dhcpRenew()
{
  int i;
  if ( sigsetjmp(env,0xffff) ) return &dhcpRebind;
  i = ReqSentTime+ntohl(*(unsigned int *)DhcpOptions.val[dhcpT2value])-time(NULL);
  if ( i > 0 )
    alarm(i);
  else
    return &dhcpRebind;

  if ( DebugFlag )
    syslog(LOG_DEBUG,"sending DHCP_REQUEST for %u.%u.%u.%u to %u.%u.%u.%u\n",
	   ((unsigned char *)&DhcpIface.ciaddr)[0],
	   ((unsigned char *)&DhcpIface.ciaddr)[1],
	   ((unsigned char *)&DhcpIface.ciaddr)[2],
	   ((unsigned char *)&DhcpIface.ciaddr)[3],
	   ((unsigned char *)&DhcpIface.siaddr)[0],
	   ((unsigned char *)&DhcpIface.siaddr)[1],
	   ((unsigned char *)&DhcpIface.siaddr)[2],
	   ((unsigned char *)&DhcpIface.siaddr)[3]);
  if ( dhcpSendAndRecv(random(),DHCP_ACK,&buildDhcpRenew) ) return &dhcpRebind;
  ReqSentTime=time(NULL);
  if ( DebugFlag ) syslog(LOG_DEBUG,
    "DHCP_ACK received from %s (%u.%u.%u.%u)\n",DhcpMsgRecv->sname,
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[0],
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[1],
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[2],
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[3]);
  return &dhcpBound;
}
/*****************************************************************************/
void *dhcpRebind()
{
  int i;
  if ( sigsetjmp(env,0xffff) ) return &dhcpStop;
  i = ReqSentTime+ntohl(*(unsigned int *)DhcpOptions.val[dhcpIPaddrLeaseTime])-time(NULL);
  if ( i > 0 )
    alarm(i);
  else
    return &dhcpStop;

  if ( DebugFlag )
    syslog(LOG_DEBUG,"broadcasting DHCP_REQUEST for %u.%u.%u.%u\n",
	   ((unsigned char *)&DhcpIface.ciaddr)[0],
	   ((unsigned char *)&DhcpIface.ciaddr)[1],
	   ((unsigned char *)&DhcpIface.ciaddr)[2],
	   ((unsigned char *)&DhcpIface.ciaddr)[3]);
  if ( dhcpSendAndRecv(random(),DHCP_ACK,&buildDhcpRebind) ) return &dhcpStop;
  ReqSentTime=time(NULL);
  if ( DebugFlag ) syslog(LOG_DEBUG,
    "DHCP_ACK received from %s (%u.%u.%u.%u)\n",DhcpMsgRecv->sname,
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[0],
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[1],
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[2],
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[3]);

  /* Successfull ACK: Use the fields obtained for future requests */
  memcpy(&DhcpIface.siaddr,DhcpOptions.val[dhcpServerIdentifier],4);
  memcpy(DhcpIface.shaddr,UdpIpMsgRecv.ethhdr.ether_shost,ETH_ALEN);

  return &dhcpBound;
}
/*****************************************************************************/
void *dhcpRelease()
{
  struct sockaddr addr;
  deleteDhcpCache();
  if ( DhcpIface.ciaddr == 0 ) return &dhcpInit;

  buildDhcpRelease(random());

  memset(&addr,0,sizeof(struct sockaddr));
  memcpy(addr.sa_data,IfName,IfName_len);
  if ( DebugFlag )
    syslog(LOG_DEBUG,"sending DHCP_RELEASE for %u.%u.%u.%u to %u.%u.%u.%u\n",
	   ((unsigned char *)&DhcpIface.ciaddr)[0],
	   ((unsigned char *)&DhcpIface.ciaddr)[1],
	   ((unsigned char *)&DhcpIface.ciaddr)[2],
	   ((unsigned char *)&DhcpIface.ciaddr)[3],
	   ((unsigned char *)&DhcpIface.siaddr)[0],
	   ((unsigned char *)&DhcpIface.siaddr)[1],
	   ((unsigned char *)&DhcpIface.siaddr)[2],
	   ((unsigned char *)&DhcpIface.siaddr)[3]);
  if ( sendto(dhcpSocket,&UdpIpMsgSend,sizeof(struct packed_ether_header)+
	      sizeof(udpiphdr)+sizeof(dhcpMessage),0,
	      &addr,sizeof(struct sockaddr)) == -1 )
    syslog(LOG_ERR,"dhcpRelease: sendto: %m\n");
  arpRelease(); /* clear ARP cache entries for client IP addr */
  if ( SetHostName )
    {
      sethostname(InitialHostName,InitialHostName_len);
      if ( DebugFlag )
	fprintf(stdout,"dhcpcd: your hostname = %s\n",InitialHostName);
    }
  if ( SetDomainName )
    {
      setdomainname(InitialDomainName,InitialDomainName_len);
      if ( DebugFlag )
	fprintf(stdout,"dhcpcd: your domainname = %s\n",InitialDomainName);
    }
  DhcpIface.ciaddr=0;
  return &dhcpInit;
}
/*****************************************************************************/
void *dhcpStop()
{
  releaseDhcpOptions();
  releaseDhcpOptionsCached();
  if ( TestCase ) goto tsc;
/* not setup the interface
  memset(&ifr,0,sizeof(struct ifreq));
#ifdef OLD_LINUX_VERSION
  memcpy(ifr.ifr_name,IfName,IfName_len);
#else
  memcpy(ifr.ifr_name,IfNameExt,IfNameExt_len);
#endif
  p->sin_family = AF_INET;
  p->sin_addr.s_addr = 0;
#ifndef OLD_LINUX_VERSION
  if ( ioctl(dhcpSocket,SIOCSIFADDR,&ifr) == -1 )
    syslog(LOG_ERR,"dhcpStop: ioctl SIOCSIFADDR: %m\n");
#endif
  ifr.ifr_flags = saved_if_flags & ~IFF_UP;
  if ( (IfName_len==IfNameExt_len) && ioctl(dhcpSocket,SIOCSIFFLAGS,&ifr) )
    syslog(LOG_ERR,"dhcpStop: ioctl SIOCSIFFLAGS: %m\n");
*/
tsc:
  close(dhcpSocket);
  if ( resolv_renamed )
    rename(""RESOLV_CONF".sv",RESOLV_CONF);
  if ( yp_renamed )
    rename(""NIS_CONF".sv",NIS_CONF);
  if ( ntp_renamed )
    rename(""NTP_CONF".sv",NTP_CONF);

#ifndef __EM86XX__ 
  execute_on_change("down");
  exit(1);
#endif

  return &dhcpStart;
}
/*****************************************************************************/
#ifdef ARPCHECK
void *dhcpDecline()
{
  struct sockaddr addr;
  memset(&UdpIpMsgSend,0,sizeof(udpipMessage));
  memcpy(UdpIpMsgSend.ethhdr.ether_dhost,MAC_BCAST_ADDR,ETH_ALEN);
  memcpy(UdpIpMsgSend.ethhdr.ether_shost,ClientHwAddr,ETH_ALEN);
  UdpIpMsgSend.ethhdr.ether_type = htons(ETHERTYPE_IP);
  buildDhcpDecline(random());
  udpipgen((udpiphdr *)&UdpIpMsgSend.udpipmsg,0,INADDR_BROADCAST,
  htons(DHCP_CLIENT_PORT),htons(DHCP_SERVER_PORT),sizeof(dhcpMessage));
  memset(&addr,0,sizeof(struct sockaddr));
  memcpy(addr.sa_data,IfName,IfName_len);
  if ( DebugFlag ) syslog(LOG_DEBUG,"broadcasting DHCP_DECLINE\n");
  if ( sendto(dhcpSocket,&UdpIpMsgSend,sizeof(struct packed_ether_header)+
	      sizeof(udpiphdr)+sizeof(dhcpMessage),0,
	      &addr,sizeof(struct sockaddr)) == -1 )
    syslog(LOG_ERR,"dhcpDecline: sendto: %m\n");
  return &dhcpInit;
}
#endif
/*****************************************************************************/
void checkIfAlreadyRunning()
{
  int pid;
  FILE *fp;
  char pidfile[64];
  snprintf(pidfile,sizeof(pidfile),PID_FILE_PATH,ConfigDir,IfNameExt);
  if ((fp = fopen(pidfile,"r"))==NULL)
	  return;
  fscanf(fp, "%d", &pid);
  fclose(fp);
  if (kill(pid,0))
	  return;
  fprintf(stderr,"\
****  %s: already running\n\
****  %s: if not then delete %s file\n",ProgramName,ProgramName,pidfile);
  exit(1);
}
/*****************************************************************************/
void *dhcpInform()
{
  dhcpStart();
  memset(&DhcpOptions,0,sizeof(DhcpOptions));
  memset(&DhcpIface,0,sizeof(dhcpInterface));
  if ( ! inform_ipaddr.s_addr )
    {
      struct ifreq ifr;
      struct sockaddr_in *p = (struct sockaddr_in *)&(ifr.ifr_addr);
      memset(&ifr,0,sizeof(struct ifreq));
#ifdef OLD_LINUX_VERSION
      memcpy(ifr.ifr_name,IfName,IfName_len);
#else
      memcpy(ifr.ifr_name,IfNameExt,IfNameExt_len);
#endif
      p->sin_family = AF_INET;
      if ( ioctl(dhcpSocket,SIOCGIFADDR,&ifr) == 0 )
        inform_ipaddr.s_addr=p->sin_addr.s_addr;
      if ( ! inform_ipaddr.s_addr )
	{
	  if ( readDhcpCache() < 0)
	    {
	      syslog(LOG_ERR,"dhcpInform: no IP address given\n");
	      return NULL;
	    }
          else
	    inform_ipaddr.s_addr=DhcpIface.ciaddr;
	}
    }
#if 0
  if ( ! DhcpIface.ciaddr )
    {
      if ( ClientMACaddr_ind )
	memcpy(DhcpIface.chaddr,ClientMACaddr,ETH_ALEN);
      else
	memcpy(DhcpIface.chaddr,ClientHwAddr,ETH_ALEN);
    }
#endif
  DhcpIface.ciaddr=inform_ipaddr.s_addr;
  if ( ! DhcpIface.class_len )
    { 
      if ( ClassID )
        {
    	  memcpy(DhcpIface.class_id,ClassID,ClassID_len);
	  DhcpIface.class_len=ClassID_len;
        }
      else
        classIDsetup();
    }
  if ( ! DhcpIface.client_len ) clientIDsetup();
  if ( sigsetjmp(env,0xffff) )
    {
      if ( DebugFlag )
	syslog(LOG_DEBUG,"timed out waiting for DHCP_ACK response\n");
      return 0;
    }
  if ( DebugFlag )
    syslog(LOG_DEBUG,"broadcasting DHCP_INFORM for %u.%u.%u.%u\n",
	   ((unsigned char *)&DhcpIface.ciaddr)[0],
	   ((unsigned char *)&DhcpIface.ciaddr)[1],
	   ((unsigned char *)&DhcpIface.ciaddr)[2],
	   ((unsigned char *)&DhcpIface.ciaddr)[3]);
  if ( dhcpSendAndRecv(random(),DHCP_ACK,buildDhcpInform) ) return 0;
  if ( DebugFlag ) syslog(LOG_DEBUG,
    "DHCP_ACK received from %s (%u.%u.%u.%u)\n",DhcpMsgRecv->sname,
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[0],
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[1],
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[2],
    ((unsigned char *)DhcpOptions.val[dhcpServerIdentifier])[3]);
#ifdef ARPCHECK
/* check if the offered IP address already in use */
  if ( arpCheck() )
    {
      if ( DebugFlag ) syslog(LOG_DEBUG,
	"requested %u.%u.%u.%u address is in use\n",
	((unsigned char *)&DhcpIface.ciaddr)[0],
	((unsigned char *)&DhcpIface.ciaddr)[1],
	((unsigned char *)&DhcpIface.ciaddr)[2],
	((unsigned char *)&DhcpIface.ciaddr)[3]);
      dhcpDecline();
      return 0;
    }
  if ( DebugFlag ) syslog(LOG_DEBUG,
    "verified %u.%u.%u.%u address is not in use\n",
    ((unsigned char *)&DhcpIface.ciaddr)[0],
    ((unsigned char *)&DhcpIface.ciaddr)[1],
    ((unsigned char *)&DhcpIface.ciaddr)[2],
    ((unsigned char *)&DhcpIface.ciaddr)[3]);
#endif
  if ( dhcpConfig() ) return 0;
  exit(0);
}

void do_cmd_bg(char *fmt, ...)
{
    va_list ap;
    char *argv[10];
    int argc = 0, flag;
                                                                                                                             
    va_start(ap, fmt);
    argv[argc++] = fmt;
    do {
        argv[argc] = va_arg(ap, char *);
    } while (argv[argc++] != 0);
    va_end(ap);
    argc--;
                                                                                                                             
    if (1){
        flag = 0;
        fprintf(stderr, "command: ");
        while (argv[flag]) {
            fprintf(stderr, "%s ", argv[flag]);
            flag++;
        }
        printf("\n");
    }
	flag = 0;
	if (vfork() == 0) {
		//setsid();
		if (vfork() == 0) {
			execv(argv[0], argv);
			perror(argv[0]);
			_exit(0);
		}
		_exit(0);
	}
	wait(&flag);
	return;
}
