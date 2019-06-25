LIBS = -lm
CFLAGS = -Wall $(LIBS)
INC = 
CC = gcc
SRC = $(shell /bin/ls -1 *.c 2>/dev/null)
BIN = $(SRC:.c=)
DESIG = discrete
PROJ = bdt0
SEMESTER = fall2018
USERPWD = $(USERPATH)
PROJPWD = /var/public/$(SEMESTER)/$(DESIG)/$(PROJ)
BINPATH = .
all: clean $(SRC) $(BIN) 

debug: CFLAGS += -DDEBUG -g
debug: DEBUG = debug
debug: clean $(SRC) $(BIN) 

.c:
ifneq ($(MAKECMDGOALS),debug)
	@printf "[\033[0;33mCC\033[0m]   %-20s ... " "$<"
	@$(CC) $(INC) -o $@ $< $(CFLAGS) 2>> errors && echo "\033[0;32mOK\033[0m" || echo "\033[0;31mFAIL\033[0m"
else
	$(CC)  $(INC) -o $@ $< $(CFLAGS)
endif

copy:
	@/bin/cp    -av $(PROJPWD)/*        $(USERPWD)/

getdata:
	@/bin/cp    -av $(PROJPWD)/in/*     in/
	@/bin/mkdir -p  out

geteval:
	@/bin/cp    -av $(PROJPWD)/eval     .

update:
	@/bin/cp    -av $(PROJPWD)/Makefile .

refresh: update getdata geteval

check:
	@$(PWD)/eval

checksummary:
	@$(PWD)/eval summary

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

submit: save
	@/usr/local/bin/submit $(DESIG) $(PROJ) `/bin/ls -1 ../$(PROJ)*gz | /usr/bin/tail -1`

clean:
	@/bin/rm -vf .*.sw[op] *.save* *~ $(BIN) $(BINPATH)/$(BIN) core errors
	@/bin/rm -rf m?/ o?/ out/* 
