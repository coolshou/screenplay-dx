CFLAGS	+= -DCURSES_LOC="<ncurses.h>" -DLOCALE

OBJECTS = checklist.o inputbox.o lxdialog.o menubox.o msgbox.o textbox.o util.o yesno.o

lxdialog: $(OBJECTS) 
	$(CC) -o $@ $(OBJECTS) -lncurses 

clean:
	rm -f *.o lxdialog
