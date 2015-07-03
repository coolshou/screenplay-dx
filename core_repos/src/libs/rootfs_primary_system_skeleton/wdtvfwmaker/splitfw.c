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
char	ofile[BUFSIZ];

	fd = open(argv[1], O_RDONLY );

	if (fd < 0) {
		printf("Unable to open %s\n", argv[1]);
		return 0;
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

		sprintf( ofile, "%d", type );
		ofd = open( ofile, O_RDWR | O_CREAT, 0644 );
		if (ofd < 0) {
			printf("Unable to open %s\n", ofile );
			continue;
		}

		lseek( fd, offset, SEEK_SET );

		while(size) {
			char	buf[BUFSIZ];
			int	chunk;
			chunk = (size > BUFSIZ) ? BUFSIZ : size;

			read( fd, buf, chunk );
			write( ofd, buf, chunk );

			size -= chunk;
		}
		close(ofd );

	} while(1);
	return 0;
}


