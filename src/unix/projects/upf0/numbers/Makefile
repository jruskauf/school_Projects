LIBS =
INC = -I ../inc
CFLAGS = -g -Wall --std=c99 $(LIBS)
CC = gcc
PROJ = numbers
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

help:
	@echo "************************************************************************"
	@echo "***                         numbers Makefile                         ***"
	@echo "************************************************************************"
	@echo "*** make                   - build everything                        ***"
	@echo "*** make debug             - build everything (with debug symbols)   ***"
	@echo "*** make clean             - clean; remove all compiled code         ***"
	@echo "*** make install           - install binaries into ~/bin directory   ***"
	@echo "************************************************************************"

clean:
	@/bin/rm -vf .*.sw[op] *.save* *~ $(BINPATH)/* core errors
