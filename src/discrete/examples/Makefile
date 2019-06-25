LIBS = `sdl-config --cflags --libs` -lSDL_image
CFLAGS = -Wall --std=gnu99 -L../lib $(LIBS)
INC = -I .
CC = gcc $(INC)
SRC = $(shell /bin/ls -1 *.c 2>/dev/null)
OBJ = $(SRC:.c=.o)
BIN = breakout
BINPATH = .
all: $(SRC) $(OBJ) $(BIN)

debug: CC += -DDEBUG -g
debug: DEBUG = debug
debug: $(SRC) $(OBJ) $(BIN)

.c.o:
ifneq ($(MAKECMDGOALS),debug)
	@printf "[CC]   %-20s ... " "$<"
	@$(CC) -c $< && echo "OK" || echo "FAIL"
else
	$(CC)  -c $<
endif

$(BIN):
ifneq ($(MAKECMDGOALS),debug)
	@printf "[LD]   %-20s ... " "pong"
	@$(CC) -o $(BINPATH)/$(BIN) $(OBJ) $(CFLAGS) && echo "OK" || echo "FAIL"
else
	$(CC)  -o $(BINPATH)/$(BIN) $(OBJ) $(CFLAGS)
endif

clean:
	rm -f *.swp *.o core $(BINPATH)/$(BIN)
