

TOP ?= $(shell pwd)
CROSS_COMPILE =  
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
LD = $(CROSS_COMPILE)ld
AR = $(CROSS_COMPILE)ar

CFLAGS = -c -std=gnu99  -Wall -fPIC -fvisibility=hidden -rdynamic
CXXFLAGS = -std=c++11 -Wall -fPIC -fvisibility=hidden

ARFLAGS = -rc

# 编译过程文件路径
OBJ_DIR = $(TOP)/obj
# 生成库路径
LIB_DIR = $(TOP)/lib
# 可执行文件路径
BIN_DIR = $(TOP)/bin

LIB_SDK = $(LIB_DIR)/x_platform.so
LIB_NAME = x_platform_sdk

BIN_EXE = $(BIN_DIR)/x_platform
BIN_NAME = x_platform

# 子目录架构
SUBDIRS = ApplicationLayer
SUBDIRS += RuntimeEnvironment
SUBDIRS += ServicesLayer
# 测试调试路径
TESTDIRS = Debug


INC += -I$(TOP) 
# application layer
INC += -I$(TOP)/ApplicationLayer
INC += -I$(TOP)/ApplicationLayer/main

# rte
INC += -I$(TOP)/RuntimeEnvironment
INC += -I$(TOP)/RuntimeEnvironment/Appl_Interface
INC += -I$(TOP)/RuntimeEnvironment/Service_Interface
INC += -I$(TOP)/RuntimeEnvironment/Rte_Linux
INC += -I$(TOP)/RuntimeEnvironment/Env_Config

# service layer
INC += -I$(TOP)/ServicesLayer
INC += -I$(TOP)/ServicesLayer/Algor
INC += -I$(TOP)/ServicesLayer/DataStructOpt
INC += -I$(TOP)/ServicesLayer/DataStructOpt/inc
INC += -I$(TOP)/ServicesLayer/DataStructOpt/src
INC += -I$(TOP)/ServicesLayer/Lib
INC += -I$(TOP)/ServicesLayer/Memory

 
LDFLAGS += -pthread  -Wl,--no-as-needed,-rpath,/usr/lib:./,--defsym, -fPIC -ldl
CFLAGS += $(INC)
CXXFLAGS += $(INC)

export CFLAGS 
export CXXFLAGS 
export TOP
export CC
export LD 
export CXX
export AR
export ARFLAGS
export LDFLAGS
export OBJ_DIR
export LIB_DIR
export LIB_SDK
export LIB_NAME
export BIN_DIR

.PHONY: $(SUBDIRS)
.PHONY: $(TESTDIRS)

all: $(BIN_EXE) $(TESTDIRS)

$(BIN_EXE): $(SUBDIRS) 
	$(CXX)  $(LDFLAGS)  $(OBJ_DIR)/*.o  -o  $@
#	$(CXX)  $(LDFLAGS) -shared  $(OBJ_DIR)/*.o  -o  $@

$(SUBDIRS):
	@$(MAKE) -C $@


$(TESTDIRS):
	@$(MAKE) -C $@

clean:
	rm -f $(LIB_SDK) 
	for d in $(SUBDIRS) ; do $(MAKE) -C $$d clean ; done
	for d in $(TESTDIRS) ; do $(MAKE) -C $$d clean ; done
	rm -f $(OBJ_DIR)/*.o
