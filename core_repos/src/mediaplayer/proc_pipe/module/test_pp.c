#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

#include "proc_pipe.h"

int          rfd=0;
int          wfd=0;
char        *proc_file=NULL;
char        *local_file=NULL;

void* thread_write(void *data)
{
    int  fd;
    int  ret;
    char buf[4096];

    printf("enter write thread\n");
    wfd = open(proc_file, O_WRONLY);
    
    fd = open(local_file, O_RDONLY);
    while(1){
        sleep(5);
        ret = read(fd, buf, 4096);
        if(ret == 0){
            printf("local file end\n");
            break;
        }
        write(wfd, buf, ret);
    }
    sleep(5);
    ioctl(wfd, P_IOCRELS);
    close(wfd);
    return NULL;
}

int main(int argc, char **argv)
{
    int            fd, val, ret;
    size_inf       inf;
    off_t          size;
    struct stat    st;
    struct timeval tv;
    fd_set         rset;
    char           buf[256];
    pthread_t      pid;

    if(argc != 3){
        printf("usage: %s <proc file> <local file>\n", argv[0]);
        exit(0);
    }
    proc_file = strdup(argv[1]);
    local_file = strdup(argv[2]);
    fd = open(argv[1], O_RDONLY);
    if(fd<0){
        printf("wrong proc file:%s\n", argv[1]);
        exit(0);
    }
    if(stat(argv[2], &st)<0){
        printf("wrong local file:%s\n", argv[2]);
        exit(0);
    }

    if(ioctl(fd, P_IOCRESET) != 0){
        printf("ioctl reset error\n");
        exit(0);
    }

    size = st.st_size;
    inf.dats = size;
    inf.idxs = 0;
    inf.mdas = size;
    if(ioctl(fd, P_IOCSIZE, &inf) !=0){
        printf("ioctl set size error\n");
        exit(0);
    }
    close(fd);

    pthread_create(&pid, NULL, thread_write, NULL);
    rfd=open(proc_file, O_RDONLY);
    /* set non-block */
    val = fcntl(rfd, F_GETFL, 0);
    fcntl(rfd, F_SETFL, val|O_NONBLOCK);

    while(1){
        FD_ZERO(&rset);
        FD_SET(rfd, &rset);

        tv.tv_sec=2;
        tv.tv_usec=0;
//        printf("%d)before select\n", (int)time(NULL));
        ret = select(rfd+1, &rset, NULL, NULL, &tv);
//        printf("%d)end select\n", (int)time(NULL));
        if(FD_ISSET(rfd, &rset)){
            ret = read(rfd, buf, 256);
            if(ret<0){
                if(errno == EAGAIN){
                    printf("%d)read eagain\n", (int)time(NULL));
                    continue;
                }
                printf("%d)read error:%s\n", (int)time(NULL), strerror(errno));
                exit(0);
             }
            if(ret == 0){
                printf("%d)read eof\n", (int)time(NULL));
                exit(0);
            }else{
                printf("%d)read buf len:%d\n", (int)time(NULL), ret);
            }
        }
    }
    return 0;
}
