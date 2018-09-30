
SYSTEMC      ?= /usr/local/systemc-2.3.2
TARGET_ARCH   = linux64

CXX          = g++
LD           = g++
CXXFLAGS     = -Wall  -I. -isystem $(SYSTEMC)/include  -Wno-deprecated -O2
LDFLAGS      =  -L$(SYSTEMC)/lib-$(TARGET_ARCH)

SOURCES      = $(wildcard *.cpp)
OBJS         = $(patsubst %.cpp,%.o,$(SOURCES))
EXE          = simulation.x

all: $(EXE)

$(EXE) : $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@  -lsystemc  2>&1 | c++filt

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.deps : $(SOURCES)
	$(CXX) $(CXXFLAGS) -MM $(SOURCES) > $@

ifneq ($(MAKECMDGOALS),clean)
-include .deps
endif

clean :
	-rm -f *.o *~ *_old $(EXE)
	-rm -f simulation.x
	-rm -f core
	-rm -f *.vcd
	-rm -f .deps

