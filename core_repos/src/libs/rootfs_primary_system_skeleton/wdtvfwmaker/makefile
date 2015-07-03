
CFLAGS	+= -Wall

default: mkfw splitfw fwextract

fwextract: fwextract.c
	$(CC) -o $@ $< --static

mkfw: mkfw.c
	gcc -o $@ $<

splitfw: splitfw.c
	gcc -o $@ $<

clean:
	rm -f splitfw mkfw fwextract *.o
