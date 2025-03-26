# See LICENSE file for copyright and license details
# slstatus - suckless status monitor
.POSIX:

include config.mk

REQ = util
COM =\
	components/battery\
	components/cpu\
	components/datetime\
	components/kanji\
	components/ram\
	components/run_command\
	components/temperature\
	components/wifi

all: wlstat

$(COM:=.o): config.mk $(REQ:=.h) slstatus.h
slstatus.o: slstatus.c slstatus.h arg.h config.h config.mk $(REQ:=.h)

.c.o:
	$(CC) -o $@ -c $(CPPFLAGS) $(CFLAGS) $<

config.h:
	cp config.def.h $@

wlstat: slstatus.o $(COM:=.o) $(REQ:=.o)
	$(CC) -o $@ $(LDFLAGS) $(COM:=.o) $(REQ:=.o) slstatus.o $(LDLIBS)

clean:
	rm -f wlstat slstatus.o $(COM:=.o) $(REQ:=.o) wlstat-${VERSION}.tar.gz

dist:
	rm -rf wlstat"-$(VERSION)"
	mkdir -p wlstat"-$(VERSION)/components"
	cp -R LICENSE Makefile README config.mk config.def.h \
	      arg.h slstatus.h slstatus.c $(REQ:=.c) $(REQ:=.h) \
	      wlstat"-$(VERSION)"
	cp -R $(COM:=.c) wlstat"-$(VERSION)/components"
	tar -cf - wlstat"-$(VERSION)" | gzip -c > wlstat"-$(VERSION).tar.gz"
	rm -rf wlstat"-$(VERSION)"

install: all
	mkdir -p "$(DESTDIR)$(PREFIX)/bin"
	cp -f wlstat "$(DESTDIR)$(PREFIX)/bin"
	chmod 755 "$(DESTDIR)$(PREFIX)/bin/wlstat"

uninstall:
	rm -f "$(DESTDIR)$(PREFIX)/bin/wlstat"
