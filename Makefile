
all: vrms


vrms: vrms.c
	$(CC) -o vrms $(CFLAGS) vrms.c $(LDFLAGS) -lxbps


vrms.1: vrms.1.md
	pandoc -s -t man -o vrms.1 vrms.1.md

clean:
	rm -f vrms
