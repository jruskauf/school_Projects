NAME = "fonts"

build:
	gcc -Wall --std=gnu99 -c $(NAME).c
	gcc -Wall --std=gnu99 -c sysprog.c
	gcc -Wall --std=gnu99 -o $(NAME) $(NAME).o sysprog.o sysprog.h -lSDL -lSDL_image -lTTF_font
