LIBS =
INC = -I ../inc
CFLAGS = -Wall --std=c99 $(LIBS)
CC = gcc
PROJ = unittools
USERPWD = $(USERPATH)
BINPATH = bin
DEBUG = 
all: clean bins

debug: CFLAGS += -DDEBUG -g
debug: DEBUG = debug
debug: clean bins

bins:
	@make -C src $(DEBUG)

save: clean
	@echo
	@echo    "Project backup process commencing"
	@echo
	@if [ "$(USER)" = "wedge" ]; then /bin/mv -f inc/unittools.h inc/unittools.h.bak; /bin/cat inc/unittools.h.bak | /bin/grep -v 'VERSION' | /bin/grep -v 'endif' > inc/unittools.h; echo -n "#define VERSION \"" >> inc/unittools.h; echo "`/bin/date +%Y%m%d-%H`\"" >> inc/unittools.h; echo "#endif" >> inc/unittools.h; /bin/rm -f inc/unittools.h.bak; fi
	@echo -n "Taking snapshot of current project ($(PROJ))      ... "
	@(cd ..; tar cf $(PROJ)-`date +%Y%m%d-%H`.tar $(PROJ) && echo "OK" || echo "error")
	@echo -n "Compressing snapshot of $(PROJ) project archive   ... "
	@gzip -f -9 ../$(PROJ)-*.tar && echo "OK" || echo "error"
	@echo -n "Setting secure permissions on $(PROJ) archive     ... "
	@chmod 600 ../$(PROJ)-*.gz && echo "OK" || echo "error"
	@echo
	@echo    "Project backup process complete"
	@echo

install:
	@/bin/mkdir -p ~/bin/
	@/bin/chmod 0700 ~/bin/
	@/bin/cp -vf $(BINPATH)/* ~/bin/
	@/bin/ln -sf /home/$(USER)/$(BINPATH)/hm2dcm /home/$(USER)/$(BINPATH)/hm2Dm

help:
	@echo "************************************************************************"
	@echo "***                        unittools Makefile                        ***"
	@echo "************************************************************************"
	@echo "*** make                   - build everything                        ***"
	@echo "*** make debug             - build everything (with debug symbols)   ***"
	@echo "*** make clean             - clean; remove all compiled code         ***"
	@echo "*** make install           - install binaries into ~/bin directory   ***"
	@echo "************************************************************************"

clean:
	@/bin/rm -vf .*.sw[op] *.save* *~ $(BINPATH)/* core errors
