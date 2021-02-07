
# if


# 条件判断的关键字主要有  ifeq ifneq ifdef ifndef

# 调用 make DEBUG=1 / make COVER=1 / make

CXXFLAGS :=

ifdef DEBUG
	CXXFLAGS += -g -O0 -W -Wall
else ifdef COVER
	CXXFLAGS += -g -O0 -fprofile-arcs -ftest-coverage
else
	CXXFLAGS += -O2
endif

all:
	@echo $(CXXFLAGS)
