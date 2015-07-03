CFLAGS	+= -DCURSES_LOC="<ncurses.h>" -DLOCALE

default: mconf conf

mconf: mconf.o zconf.tab.o 
	$(CC) -o $@ mconf.o zconf.tab.o -lncurses

conf: conf.o zconf.tab.o
	$(CC) -o $@ conf.o zconf.tab.o -lncurses

clean:
	rm -f *.o mconf conf
