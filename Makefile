ifeq ($(CXX),)
 CXX=/usr/bin/g++
endif

CXX_FLAGS = -std=c++23

BASE	:= $(CURDIR)
INCLUDE := $(BASE)/include
SRC		:= $(BASE)/src
BUILD	:= $(BASE)/build

ifeq ($(wildcard $(BUILD)),)
 $(shell mkdir $(BUILD))
endif

objs = avl_main.o

.PHONY: all $(objs) clean

all: $(objs)
	$(CXX) -I$(INCLUDE) $(CXX_FLAGS) -o $(BUILD)/avl_main $(addprefix $(BUILD)/, $(objs))

$(objs):
	$(CXX) -I$(INCLUDE) $(CXX_FLAGS) -c -o $(addprefix $(BUILD)/, $(objs)) $(addprefix $(SRC)/,$(patsubst %.o,%.cpp,$(objs)))

clean:
	rm -rf $(BUILD)/*