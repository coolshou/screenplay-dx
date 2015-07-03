#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
int	i;
int	ofd;
int	offset[argc];
int	size[argc];
int	type[argc];
int	files = 0;
struct	stat	st;
char	cmdbuf[BUFSIZ];
int	magic = 0xbabeface;

	if (argc < 2) {
		printf("Usage: %s target type1 file1 [type2] [file2] [type3] [file3]...\n", argv[0]);
		return 0;
	}

	ofd = open( argv[1], O_RDWR | O_CREAT | O_TRUNC, 0644 );
	if (ofd < 0) {
		printf("Unable to open %s\n", argv[1]);
		return 0;
	}

	close( ofd );

	for(i=2; i<argc; i+=2) {
		type[files] = atoi( argv[i] );

		if (stat( argv[i+1], &st)) {
			printf("Unable to open %s\n", argv[i+1]);
			break;
		}

		size[files] = st.st_size;

		if (!files)
			offset[files] = 0;
		else
			offset[files] = offset[files-1] + size[files-1];
		files++;

		sprintf( cmdbuf, "cat %s >> %s", argv[i+1], argv[1] );   
		system( cmdbuf );

	}

#if 1
	ofd = open( argv[1], O_RDWR | O_APPEND, 0644 );
	lseek( ofd, 0, SEEK_END );

	for(i=0;i<files;i++) {
		printf("%d: type: %d, size: %d, offset: %d\n", i, type[i], size[i], offset[i]);
		write( ofd, &magic, 4 );
		write( ofd, &type[i], 4 );
		write( ofd, &size[i], 4 );
		write( ofd, &offset[i], 4 );
	}
#endif

	close(ofd);

	return 0;
}


