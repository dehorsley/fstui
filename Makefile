include config.mk

CFLAGS += -g

SRC = dvtm.c vt.c
OBJ = ${SRC:.c=.o}

DESTDIR ?= /usr2/st

all: clean options fstui

options:
	@echo fstui build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

config.h:
	cp config.def.h config.h

.c.o:
	@echo CC $<
	@${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

fstui: ${OBJ}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

debug: clean
	@make CFLAGS='${DEBUG_CFLAGS}'

clean:
	@echo cleaning
	@rm -f fstui ${OBJ} fstui-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p dvtm-${VERSION}
	@cp -R LICENSE Makefile README.md testsuite.sh config.def.h config.mk \
		${SRC} vt.h forkpty-aix.c forkpty-sunos.c tile.c bstack.c \
		tstack.c vstack.c grid.c fullscreen.c fibonacci.c \
		dvtm-status dvtm.info dvtm.1 dvtm-${VERSION}
	@tar -cf dvtm-${VERSION}.tar dvtm-${VERSION}
	@gzip dvtm-${VERSION}.tar
	@rm -rf dvtm-${VERSION}

install: fstui
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f fstui ${DESTDIR}${PREFIX}/bin

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/fstui
	@rm -f ${DESTDIR}${PREFIX}/bin/fstui-status
	@echo removing manual page from ${DESTDIR}${MANPREFIX}/man1
	@rm -f ${DESTDIR}${MANPREFIX}/man1/dvtm.1

.PHONY: all options clean dist install uninstall debug
