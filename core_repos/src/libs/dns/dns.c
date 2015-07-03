#include <netdb.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
	struct	hostent	*he;
	char	*pip;
	int ret=0,a=-1,b=-1,c=-1,d=-1,e=-1;

	printf("%d\n",getpid());
	fflush(stdout);
	if (argc < 2) {
		printf("usage: %s domain\n", argv[0]);
		return 0;
	}
	ret = sscanf(argv[1],"%u.%u.%u.%u.%u",&a,&b,&c,&d,&e);
	if (ret==4){
			if (a<255 && b<255 && c<255 && d<255
					&& a>=0 && b>=0 && c>=0 && d>=0 ){
				printf("%s\n", argv[1]);
				return 0;
			}
	}
	he = gethostbyname( argv[1] );
	
	if (he && (pip = (char *)inet_ntoa(*((struct in_addr *)he->h_addr)))) {
		printf("%s\n", pip );
	} else
		printf("ERROR\n");
	fflush(stdout);
	return 0;
}
