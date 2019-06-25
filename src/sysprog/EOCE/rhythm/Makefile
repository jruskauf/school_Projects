LIBS = `sdl-config --cflags --libs` -lSDL_image -lSDL_ttf
CFLAGS = -Wall --std=gnu99 $(LIBS)
INC = -I .
CC = gcc $(INC)
SRC = $(shell /bin/ls -1 *.c 2>/dev/null)
OBJ = $(SRC:.c=.o)
BIN = $(shell /usr/bin/basename `/bin/pwd`)
BINPATH = .
all: $(SRC) $(OBJ) $(BIN)

debug: CC += -DDEBUG -g
debug: DEBUG = debug
debug: $(SRC) $(OBJ) $(BIN)

.c.o:
ifneq ($(MAKECMDGOALS),debug)
	@printf "[\033[0;33mCC\033[0m]   %-20s ... " "$<"
	@$(CC) -c $< 2>> errors && echo "\033[0;32mOK\033[0m" || echo "\033[0;31mFAIL\033[0m"
else
	$(CC)  -c $<
endif

copy:
	@/bin/cp -av $(PROJPWD)/* $(USERPWD)/

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

$(BIN):
ifneq ($(MAKECMDGOALS),debug)
	@printf "[\033[0;33mLD\033[0m]   %-20s ... " "$(BIN)"
	@$(CC) -o $(BINPATH)/$(BIN) $(OBJ) $(CFLAGS) && echo "\033[0;32mOK\033[0m" || echo "\033[0;31mFAIL\033[0m"
else
	$(CC)  -o $(BINPATH)/$(BIN) $(OBJ) $(CFLAGS)
endif

clean:
	rm -f *.swp *.o core $(BINPATH)/$(BIN) errors
