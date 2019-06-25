LIBS = -lm
INC = -I .
CFLAGS = -g -Wall --std=c99 $(LIBS)
CC = gcc
DESIG = unix
PROJ = eoce
SEMESTER = spring2018
USERPWD = $(USERPATH)
PROJPWD = /var/public/$(SEMESTER)/$(DESIG)/$(PROJ)
BINPATH = .
all: clean

copy:
	@/bin/cp -av $(PROJPWD)/* $(USERPWD)/

submit: save
	@submit $(DESIG) $(PROJ) `/bin/ls -1 ../$(PROJ)*gz | tail -1`

save: clean
	@echo
	@echo    "Project backup process commencing"
	@echo
	@echo -n "Taking snapshot of current project ($(PROJ))      ... "
	@(cd ..; /bin/tar cf $(PROJ)-`/bin/date +%Y%m%d-%H`.tar $(PROJ) && echo "OK" || echo "error")
	@echo -n "Compressing snapshot of $(PROJ) project archive   ... "
	@/bin/gzip -f -9 ../$(PROJ)-*.tar && echo "OK" || echo "error"
	@echo -n "Setting secure permissions on $(PROJ) archive     ... "
	@/bin/chmod 600 ../$(PROJ)-*.gz && echo "OK" || echo "error"
	@echo
	@echo    "Project backup process complete"
	@echo

update:
	@/bin/cp -f $(PROJPWD)/Makefile .

clean:
	@/bin/rm -vf .*.sw[op] *.save* *~ core errors
