SHELL = /bin/bash -e
INC = -I inc/
CCFLAGS = -Wall 
OPTS =
CC = gcc $(CCFLAGS) $(OPTS) $(INC)
OBJ = 
AR = ar
DEBUG = 
DESIG = datacomm
SEMESTER = fall2014
PROJ = pong-$(SEMESTER)
PARTS = src
ALL = $(PARTS) $(BIN)
BIN = pong
default: $(ALL)
debug: clean $(BIN)-debug

$(BIN)-debug: CC += -DDEBUG -g
$(BIN)-debug: DEBUG = debug
$(BIN)-debug: $(BIN)

$(BIN):
	@for i in $(PARTS); do make -C $$i $(DEBUG); done

clean:
	@for i in $(PARTS); do make -C $$i clean; done
	@rm -f bin/* lib/*

save: clean
	@echo "Archiving the project ..."
	@(cd ..; tar cf $(PROJ)-`date +%Y%m%d-%H`.tar $(PROJ))
	@echo "Compressing the archive ..."
	@gzip -f -9 ../$(PROJ)-*.tar
	@echo "Setting Permissions ..."
	@chmod 600 ../$(PROJ)-*.gz

help:
	@echo
	@echo "**************[ Data Communications Pong Implementation ]***************"
	@echo "** make                     - build everything                        **"
	@echo "** make debug               - build everything with debug symbols     **"
	@echo "**                                                                    **"
	@echo "** make save                - create a backup archive                 **"
	@echo "**                                                                    **"
	@echo "** make clean               - clean; remove all objects/compiled code **"
	@echo "** make help                - this information                        **"
	@echo "************************************************************************"
