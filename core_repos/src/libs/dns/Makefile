PROG=	dns
SRCS=	dns.c
#---------------
OBJS	+= ${SRCS:.c=.o}
#---------------
compile:	${PROG}
#---------------
${PROG}: ${OBJS}
	$(CC)  -o ${PROG} $(OBJS) $(CFLAGS) $(CLFLAGS) $(LDFLAGS)
#---------------
clean:
	rm -f *.o ${PROG} ${PROG}.elf ${PROG}.gdb
#---------------
#install: ${PROG}
#	mkdir -p $(ROOT_FS_DIR)/usr/sbin
#	cp -f $(PROG) $(ROOT_FS_DIR)/usr/sbin
#---------------
# End of Makefile
