PREFIX=/usr/local
BINDIR=$(PREFIX)/bin
CC=cc

txt2owo: txt2owo.c
	$(CC) $< -o $@

.PHONY: all install uninstall
all: txt2owo

install: txt2owo
	mkdir -p $(BINDIR)
	cp $< $(BINDIR)/$<
	chmod 755 $(BINDIR)/$<

uninstall: $(BINDIR)/txt2owo
	rm $<
