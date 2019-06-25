LIBS =
INC = -I ../inc
CFLAGS = -g -Wall --std=c99 $(LIBS)
CC = gcc
SRC = $(shell /bin/ls -1 *.c 2>/dev/null)
BIN = $(SRC:.c=)
PROJ = numbers
USERPWD = $(USERPATH)
BINPATH = ../bin
all: clean $(SRC) $(BIN)

debug: CFLAGS += -DDEBUG -g
debug: DEBUG = debug
debug: clean $(SRC) $(BIN) 

.c:
ifneq ($(MAKECMDGOALS),debug)
	@printf "[\033[0;33mCC\033[0m]   %-20s ... " "$<"
	@$(CC) $(CFLAGS) $(INC) -o $(BINPATH)/$@ $< 2>> errors && echo "\033[0;32mOK\033[0m" || echo "\033[0;31mFAIL\033[0m"
else
	$(CC)  $(CFLAGS) $(INC) -o $(BINPATH)/$@ $<
endif

clean:
	@/bin/rm -vf .*.sw[op] *.save* *~ core errors
