#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
int	fd;
int	files = 0;
int	magic;
int	type;
int	size;
int	offset;
int	ofd;
int	target_type;
int	global_offset = 0;

	if (argc < 3) {
		printf("Usage: %s source id target [offset]\n", argv[0]);
		return -1;
	}

	fd = open(argv[1], O_RDONLY );
	if (fd < 0) {
		printf("Unable to open %s\n", argv[1]);
		return -1;
	}
	ofd = open(argv[3], O_RDWR | O_CREAT | O_TRUNC, 0644 );
	if (ofd < 0) {
		printf("Unable to open %s\n", argv[3]);
		return -1;
	}

	target_type = atoi( argv[2] );

	if (argc == 5) {
		global_offset = atoi( argv[4] );
		printf("global offset = %d\n", global_offset );
	}

	do {
		lseek( fd, -1*(files+1)*16 , SEEK_END );
		read( fd, &magic, 4);
		read( fd, &type, 4);
		read( fd, &size, 4);
		read( fd, &offset, 4);

		if (magic != 0xbabeface)
			break;
		files++;

		printf("%d: type: %d, size: %d, offset: %d\n", files, type, size, offset );

		if (type == target_type) {
			lseek( fd, offset + global_offset, SEEK_SET );
			while(size) {
				char	buf[BUFSIZ];
				int	chunk;
				chunk = (size > BUFSIZ) ? BUFSIZ : size;
				read( fd, buf, chunk );
				write( ofd, buf, chunk );
				size -= chunk;
			}
			close(ofd );
			break;
		}

	} while(1);
	close(fd);
	return 0;
}


