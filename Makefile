SRCS		:=
OBJS		:=
DEPS		:=
TMPS		:=
LIBS		:= -lrt -lpthread -lboost_system
PROGRAMS	:=
#======================================================================
# MODULES
MODULES		:= src/InterProcess src/PayLoad src/DeviceManager
# LIBS
MODULES		+= lib/
# APP
MODULES 	+= 

INCLUDE_DIRS	:= include
INCLUDE_DIRS	+= unitTest
vpath %.h $(INCLUDE_DIRS)
#======================================================================
# select which tools to use as compiler, 
# librarian and linker
#======================================================================
CXXFLAGS	+= -std=c++11 -Wall -O2
CXXFLAGS	+= $(addprefix -I , $(INCLUDE_DIRS))
#======================================================================
# select which tools to use as compiler, librarian and linker
#======================================================================
AR = ar
ARFLAGS = rv
#======================================================================
# Enviroment
#======================================================================
MKDIR		:= mkdir -p
RM		:= rm -f
MV		:= mf -f
#======================================================================
# Unit test
include ./unitTest/TEST_PAYLOAD/xmodule.mk
# Common modules
include $(patsubst %, ./%/xmodule.mk, $(MODULES))
# Current program
include ./Process/Reciever/xmodule.mk
include ./Process/Sender/xmodule.mk

#======================================================================
.PHONY: default build run all clean

default: all

all: $(OBJS) $(PROGRAMS)

run: $(PROGRAMS) run_sender run_reciever

run_sender:
	@echo "*****PARENT*****"
	@./Process/Sender/Sender
run_reciever:
	@echo "*****CHILD*****"
	@./Process/Reciever/Reciever
clean:
	$(RM) $(OBJS) $(DEPS) $(TMPS)
	$(RM) $(PROGRAMS) 
	

