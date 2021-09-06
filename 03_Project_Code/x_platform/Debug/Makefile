TOP_PWD ?= $(shell pwd)
CROSS_COMPILE =  
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
AR = $(CROSS_COMPILE)ar

INC += -I$(TOP_PWD) 

CDEBUG_FLAGS += $(INC)

CSRCS = $(wildcard *.c)

COBJS = $(patsubst %.c, %.o, $(CSRCS)) 
TAGS = $(basename $(CSRCS))

TEST_BIN = DebugSend

all: $(TEST_BIN)

$(TEST_BIN): $(COBJS)
	$(CC) $(CDEBUG_FLAGS) -g $^ -o $@

$(COBJS): 
	$(foreach n,$(TAGS),$(CC) $(CDEBUG_FLAGS) -g -c $(n).c -o $(n).o) 

clean:
	rm -f $(TOP_PWD)/*.o