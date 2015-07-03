/*
 * dhcpcd - DHCP client daemon -
 * Copyright (C) 2002 Red Hat, Inc.,
 * Copyright (C) 2002 Christopher Blizzard <blizzard@redhat.com>
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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <syslog.h>
#include <stdlib.h>
#include <signal.h>


#include "cache.h"
#include "client.h"
#include "pathnames.h"

extern char          *ConfigDir;
extern char          *IfNameExt;
extern dhcpInterface  DhcpIface;
extern dhcpOptions    DhcpOptions;
extern int            prev_ip_addr;

char                  cache_file[128];
dhcpOptions           DhcpOptionsCached;

static ssize_t
readn(int fd, void *vptr, size_t n);

static ssize_t
writen(int fd, const void *vptr, size_t n);

/*****************************************************************************/
int readDhcpCache()
{
  int fd;
  u_char option;
  int lastread = -1;
  u_char size;
  char *p;
  snprintf(cache_file,sizeof(cache_file),DHCP_CACHE_FILE,ConfigDir,IfNameExt);

  fd=open(cache_file,O_RDONLY);
  if (fd < 0)
    return -1;

  /* read in the dhcpIface struct */
  if (readn(fd,(char *)&DhcpIface,sizeof(dhcpInterface)) !=
      sizeof(dhcpInterface))
    goto loser;

  if (strncmp(DhcpIface.version,VERSION,sizeof(DhcpIface.version)))
    goto loser;

  prev_ip_addr = DhcpIface.ciaddr;

  /* read in the dhcpOptions struct */
  while (1) {
    lastread = readn(fd, &option, 1);

    /* error */
    if (lastread <= 0)
      goto loser;
    /* endOption */
    if (option == endOption)
      break;

    lastread = readn(fd, &size, 1);

    /* error */
    if (lastread <= 0)
      goto loser;
    
    if (size) {
      p = malloc(size);
      lastread = readn(fd, p, size);
      DhcpOptionsCached.num++;
      DhcpOptionsCached.len[option] = size;
      DhcpOptionsCached.val[option] = p;
    }
  }

  close(fd);
  return 0;

  loser:
  close(fd);
  return -1;
}

/*****************************************************************************/
void writeDhcpCache()
{
  int i, fd;
  char p;
  snprintf(cache_file,sizeof(cache_file),DHCP_CACHE_FILE,ConfigDir,IfNameExt);

  fd=open(cache_file,O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR+S_IWUSR);
  if (fd < 0) {
    syslog(LOG_ERR, "writeDhcpCache: failed to open cache file %m\n");
    return;
  }

  /* write out the dhcp interface information */

  if (writen(fd,(char *)&DhcpIface,sizeof(dhcpInterface)) != sizeof(dhcpInterface)) {
    syslog(LOG_ERR, "writeDhcpCache: failed to write to cache file %m\n");
    goto loser;
  }

  /* write out the dhcp options structure */
  for (i=0; i < 256; i++) {
    if (DhcpOptions.len[i]) {

      /* write out the option type */
      p = i;
      if (writen(fd, &p, 1) != 1) {
	syslog(LOG_ERR, "writeDhcpCache: failed to write type %m\n");
	goto loser;
      }

      /* write out the option length */
      p = DhcpOptions.len[i];
      if (writen(fd, &p, 1) != 1) {
	syslog(LOG_ERR, "writeDhcpCache: failed to write len %m\n");
	goto loser;
      }

      /* write out the option itself */
      if (writen(fd, DhcpOptions.val[i], DhcpOptions.len[i]) !=
	  DhcpOptions.len[i]) {
	syslog(LOG_ERR, "writeDhcpCache: failed to write data %m\n");
	goto loser;
      }
    }
  }

  /* write out an end marker */
  p = endOption;
  if (writen(fd, &p, 1) != 1) {
    syslog(LOG_ERR, "writeDhcpCache: failed to write endOption %m\n");
    goto loser;
  }

  close(fd);
  return;

 loser:
  /* if we failed to write something, don't leave a bad file hanging
     around */
  close(fd);
  deleteDhcpCache();
}

/*****************************************************************************/
void deleteDhcpCache()
{
  snprintf(cache_file,sizeof(cache_file),DHCP_CACHE_FILE,ConfigDir,IfNameExt);
  unlink(cache_file);
}

/*****************************************************************************/
void releaseDhcpOptionsCached(void)
{
  register int i;
  for (i=1;i<256;i++)
    if ( DhcpOptionsCached.val[i] ) free(DhcpOptionsCached.val[i]);
  memset(&DhcpOptionsCached,0,sizeof(dhcpOptions));
}

/*****************************************************************************/
void useDhcpOptionsCached(void)
{
  releaseDhcpOptions();
  memcpy(&DhcpOptions, &DhcpOptionsCached, sizeof(dhcpOptions));
  memset(&DhcpOptionsCached, 0, sizeof(dhcpOptions));
}

/* Straight out of APUE - blocking read and write */
ssize_t
readn(int fd, void *vptr, size_t n)
{
  size_t nleft;
  ssize_t nread;
  char *ptr;

  ptr = vptr;
  nleft = n;
  while (nleft > 0) {
    if ((nread = read(fd, ptr, nleft)) < 0)
      return (nread); /* error, return < 0 */
    else if (nread == 0)
      break; /* EOF */

    nleft -= nread;
    ptr += nread;
  }
  return (n - nleft); /* return >= 0 */
}

ssize_t
writen(int fd, const void *vptr, size_t n)
{
  size_t nleft;
  ssize_t nwritten;
  const char *ptr;

  ptr = vptr; /* can't do pointer arithmetic on void * */
  nleft  = n;
  while (nleft > 0) {
    if ((nwritten = write (fd, ptr, nleft)) <= 0)
      return (nwritten); /* error */

    nleft -= nwritten;
    ptr += nwritten;
  }

  return(n);
}

void touch(const char *name)
{
	int fd = open(name ,  O_RDWR | O_CREAT,S_IRUSR |
				  S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (fd < 0) {
		perror("open");
		fprintf(stderr,"Can not create file %s\n",name);
		return;
	}
	close(fd);
}

int kill_pidfile(char *file, int signal)
{
	int pid;
	FILE *fp = fopen(file,"r");

	if (fp == NULL) return 0;
	fscanf(fp,"%d",&pid);
	fclose(fp);
	kill(pid, signal);
	return 0;
}
