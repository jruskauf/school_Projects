SHELL = /bin/bash -e
INC = -I inc/
CCFLAGS = -Wall --std=gnu99
OPTS =
CC = gcc $(CCFLAGS) $(OPTS) $(INC)
OBJ = 
AR = ar
DEBUG = 
DESIG = data
PROJ = $(shell /bin/pwd | /bin/grep -o '[sd][lk][anlsqt][0-9]' | /usr/bin/sort -u)
SEMESTER = fall2018
USERPWD = $(shell pwd)
DATAPATH = /var/public/$(SEMESTER)/$(DESIG)
PROJPATH = $(DATAPATH)/$(PROJ)
NEXTPROJ = $(shell /bin/cat $(DATAPATH)/projlist | /bin/grep "^$(PROJ):" | /usr/bin/cut -d':' -f2)
OTHER = $(shell /bin/cat $(DATAPATH)/projlist | /bin/grep "^$(PROJ):" | /usr/bin/cut -d':' -f3)
NEXTPATH = $(DATAPATH)/$(NEXTPROJ)
OTHERPATH = $(DATAPATH)/$(OTHER)
LIBS = src
UNIT = unit
APP = app
ALL = $(LIBS) $(UNIT) $(APP)
BIN = 
default: status-begin libs units status-end
debug: status-begin libs-debug units-debug status-end

libs-debug: CC += -DDEBUG -g
libs-debug: DEBUG = debug
libs-debug: libs

libs:
ifneq ($(MAKECMDGOALS),debug)
	@for i in $(LIBS); do make -sC $$i $(DEBUG); done
else
	@for i in $(LIBS); do make -C $$i $(DEBUG); done
endif

status-begin:
	@if [ -e "$(PROJPATH)/.updates/latest" ]; then if [ `cat .updates/current` -lt `cat $(PROJPATH)/.updates/latest` ]; then echo "*********************************************************"; echo "*** NEW UPDATE AVAILABLE: Type 'make update' to apply ***"; echo "*********************************************************"; fi; fi

status-end:
	@if [ -e "errors" ]; then if [ `cat errors | wc -l` -gt 0 ]; then echo " *** There were warnings or errors during compile! Type: 'cat errors' at the prompt to view."; fi; fi
	@if [ -e "$(PROJPATH)/.updates/latest" ]; then if [ `cat .updates/current` -lt `cat $(PROJPATH)/.updates/latest` ]; then echo "*********************************************************"; echo "*** NEW UPDATE AVAILABLE: Type 'make update' to apply ***"; echo "*********************************************************"; fi; fi

status-quit:
	@if [ -e "$(PROJPATH)/.updates/latest" ]; then if [ `cat .updates/current` -lt `cat $(PROJPATH)/.updates/latest` ]; then echo "*********************************************************"; echo "*** NEW UPDATE AVAILABLE: Type 'make update' to apply ***"; echo "*********************************************************"; /bin/false; fi; fi

units-debug: CC += -DDEBUG -g
units-debug: DEBUG = debug
units-debug: units

units:
ifneq ($(MAKECMDGOALS),debug)
	@for i in $(UNIT); do make -sC $$i $(DEBUG); done
else
	@for i in $(UNIT); do make -C $$i $(DEBUG); done
endif

apps-debug: CC += -DDEBUG -g
apps-debug: DEBUG = debug
apps-debug: apps

apps:
ifneq ($(MAKECMDGOALS),debug)
	@for i in $(APP); do make -sC $$i $(DEBUG); done
else
	@for i in $(APP); do make -C $$i $(DEBUG); done
endif

check: status-begin
	@${DATAPATH}/.eval/verify.sh $(PROJ)

clean: status-begin
	@printf  "Cleaning out object code    ... "
	@for i in $(ALL); do make -sC $$i clean; done
	@rm -f errors bin/* lib/*
	@printf  "OK\n\n"

copy:
	@echo      "Commencing copy process for $(SEMESTER) $(DESIG) project $(PROJ)"
	@echo  -n  " -> Creating project $(PROJ) directory tree           ... "
	@mkdir -p  $(USERPWD)/.updates 2> /dev/null && echo "OK" || echo "error"
	@echo  -n  " -> Copying $(PROJ) project files                     ... "
	@cp    -a  $(PROJPATH)/* $(USERPWD)/ 2>/dev/null && echo "OK" || echo "error"
	@echo  -n  " -> Synchronizing $(PROJ) project revision level      ... "
	@cp    -f  $(PROJPATH)/.updates/current $(USERPWD)/.updates/ 2> /dev/null && echo "OK" || echo "error"
	@echo  -n  " -> Establishing sane file permissions for $(PROJ)    ... "
	@chmod -R  u=rwX,go= $(USERPWD) && echo "OK" || echo "error"
	@echo
	@echo      "*** Copy Complete! You may now switch to the '$(USERPWD)' directory"
	@echo
	@echo      "[${USER}] obtaining project '$(PROJ)' (revision `cat $(PROJPATH)/.updates/latest`) in $(USERPWD) (`date +\"%Y%m%d%H%M\"`)" >> $(PROJPATH)/.updates/log 2>/dev/null

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

submit: save
	@submit $(DESIG) $(PROJ) `/bin/ls -1 ../$(PROJ)*gz | tail -1`
	@echo "[${USER}] submitting project '$(PROJ)' in `pwd` (`date +\"%Y%m%d%H%M\"`)" >> $(PROJPATH)/.updates/log

use-test-reference: clean
	@if [ -f "$(PROJPATH)/.datastore/refimp.sh" ]; then sh $(PROJPATH)/.datastore/refimp.sh `pwd` "$(SEMESTER)/$(DESIG)/$(PROJ)"; fi
	@echo "Test reference implementation in place, run 'make' to build everything."

use-your-own-code: clean
	@if [ -f "$(PROJPATH)/.datastore/locimp.sh" ]; then sh $(PROJPATH)/.datastore/locimp.sh `pwd` "$(SEMESTER)/$(DESIG)/$(PROJ)"; fi
	@echo "Local implementation restored, run 'make' to build everything."

update:
	@for((i=`cat .updates/current`+1; i<=`cat $(PROJPATH)/.updates/latest`; i++)); do sh $(PROJPATH)/.updates/$$i $(SEMESTER) $(DESIG) $(PROJ); echo "[${USER}] applying revision $$i of '$(PROJ)' in `pwd` (`date +\"%Y%m%d%H%M\"`)" >> $(PROJPATH)/.updates/log; done
	@chmod -R u=rwX,go= .
	@echo "Updated from revision `cat .updates/current` to revision `cat $(PROJPATH)/.updates/latest`"
	@cat $(PROJPATH)/.updates/latest > .updates/current

reupdate:
	@for((i=`cat .updates/current`; i<=`cat .updates/current`; i++)); do sh $(PROJPATH)/.updates/$$i $(SEMESTER) $(DESIG) $(PROJ); echo "[${USER}] re-applying revision $$i of '$(PROJ)' in `pwd` (`date +\"%Y%m%d%H%M\"`)" >> $(PROJPATH)/.updates/log; done
	@chmod -R u=rwX,go= .
	@echo "Re-applying revision `cat .updates/current`"

reupdate-all:
	@for((i=1; i<=`cat .updates/current`; i++)); do sh $(PROJPATH)/.updates/$$i $(SEMESTER) $(DESIG) $(PROJ); echo "[${USER}] re-applying revision $$i of '$(PROJ)' in `pwd` (`date +\"%Y%m%d%H%M\"`)" >> $(PROJPATH)/.updates/log; done
	@chmod -R u=rwX,go= .
	@echo "Re-applied updates from revision 1 to revision `cat .updates/current`"

upgrade-$(NEXTPROJ): use-your-own-code status-quit clean save
	@echo    "Commencing upgrade process from $(PROJ) to $(NEXTPROJ)"
	@echo
	@echo -n "Creating project $(NEXTPROJ) directory tree           ... "
	@mkdir -p ../$(NEXTPROJ) ../$(NEXTPROJ)/.updates && echo "OK" || echo "error"
	@echo -n "Copying your code to $(NEXTPROJ) project directory    ... "
	@cp -a * ../$(NEXTPROJ) && echo "OK" || echo "error"
	@echo -n "Copying new $(NEXTPROJ) files into project directory  ... "
	@cp -a $(DATAPATH)/$(NEXTPROJ)/* ../$(NEXTPROJ)/ && echo "OK" || echo "error"
	@echo -n "Synchronizing $(NEXTPROJ) project revision level      ... "
	@cp -f $(DATAPATH)/$(NEXTPROJ)/.updates/current ../$(NEXTPROJ)/.updates/ && echo "OK" || echo "error"
	@if [ -f "$(DATAPATH)/$(NEXTPROJ)/.updates/prune" ]; then echo -n "Pruning obsoleted files from $(NEXTPROJ) project tree ... "; sh $(DATAPATH)/$(NEXTPROJ)/.updates/prune ../$(NEXTPROJ) && echo "OK" || echo "error"; fi
	@echo -n "Establishing sane file permissions for $(NEXTPROJ)    ... "
	@chmod -R u=rwX,go= ../$(NEXTPROJ) && echo "OK" || echo "error"
	@echo
	@echo "Upgrade Complete! You may now switch to the ../$(NEXTPROJ) directory"
	@echo
	@echo "[${USER}] upgrading to project '$(NEXTPROJ)' (revision `cat $(DATAPATH)/$(NEXTPROJ)/.updates/latest`) in `pwd` (`date +\"%Y%m%d%H%M\"`)" >> $(DATAPATH)/$(NEXTPROJ)/.updates/log

get-$(OTHER): status-quit clean save
	@make -C $(DATAPATH)/$(OTHER) copy

help: status-begin
	@if [ "`echo $(PROJ) | cut -c3`" = "s" ]; then echo "****************[ Data Structures Stack Implementation ]****************"; elif [ "`echo $(PROJ) | cut -c2`" = "k" ]; then echo "****************[ Data Structures Knowledge Assessment ]****************"; elif [ "`echo $(PROJ) | cut -c3`" = "q" ]; then echo "****************[ Data Structures Queue Implementation ]****************"; elif [ "`echo $(PROJ) | cut -c3`" = "l" ]; then echo "****************[ Data Structures List Implementation ]*****************"; elif [ "`echo $(PROJ) | cut -c3`" = "n" ]; then echo "****************[ Data Structures Node Implementation ]*****************"; elif [ "`echo $(PROJ) | cut -c3`" = "t" ]; then echo "****************[ Data Structures Tree Implementation ]*****************"; else echo "****************[ Data Structures Code Implementation ]*****************"; fi
	@echo "** make                     - build everything (libs, units, apps)    **"
	@echo "** make debug               - build everything with debug symbols     **"
	@echo "** make check               - check implementation for validity       **"
	@echo "**                                                                    **"
	@echo "** make libs                - build all supporting libraries          **"
	@echo "** make libs-debug          - build all libraries with debug symbols  **"
	@if [ -d "app/" ]; then echo "** make apps                - build unit tests                        **"; echo "** make apps-debug          - build unit tests with debugging symbols **"; fi
	@echo "** make units               - build unit tests                        **"
	@echo "** make units-debug         - build unit tests with debugging symbols **"
	@if [ -f "$(PROJPATH)/.datastore/refimp.sh" ]; then echo "**                                                                    **"; echo "** make use-test-reference  - use working implementation object files **"; echo "** make use-your-own-code   - use your own implementation code        **"; fi
	@echo "**                                                                    **"
	@echo "** make save                - create a backup archive                 **"
	@echo "** make submit              - submit assignment (based on dirname)    **"
	@echo "**                                                                    **"
	@echo "** make update              - check for and apply updates             **"
	@echo "** make reupdate            - re-apply last revision                  **"
	@echo "** make reupdate-all        - re-apply all revisions                  **"
	@echo "**                                                                    **"
	@if [ -r $(NEXTPATH) ]; then /usr/bin/printf "** %-24s " "make upgrade-$(NEXTPROJ)"; /usr/bin/printf "- %-39s **\n" "upgrade to next project ($(NEXTPROJ))"; fi
	@if [ ! -z "$(OTHER)" ] && [ -r $(OTHERPATH) ]; then /usr/bin/printf "** %-24s " "make get-$(OTHER)"; /usr/bin/printf "- %-39s **\n" "obtain new project ($(OTHER))"; echo "**                                                                    **"; fi
	@echo "** make clean               - clean; remove all objects/compiled code **"
	@echo "** make help                - this information                        **"
	@echo "************************************************************************"
