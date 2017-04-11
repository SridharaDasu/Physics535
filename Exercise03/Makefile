CXX           = g++
CXXFLAGS      = $(OPT2) -pipe -Wall -W -Woverloaded-virtual -g -std=c++11
LD            = g++
LDFLAGS       = $(OPT2)
SOFLAGS       = -dynamiclib -single_module -undefined $(UNDEFOPT)

PYINCLUDES = -I$(PYTHIA8DATA)/../../../include
PYLDLIBS = -L$(PYTHIA8DATA)/../../../lib -lpythia8 -lpythia8lhapdf6

FASTJET=$(PYTHIA8DATA)/../../../../../fastjet/3.1.0/
FASTJETINCLUDES = `$(FASTJET)/bin/fastjet-config --cxxflags`
FASTJETLDLIBS   = `$(FASTJET)/bin/fastjet-config --libs`

ROOTINCLUDES = -I$(ROOTSYS)/include
ROOTLDLIBS = `$(ROOTSYS)/bin/root-config --cflags --glibs` -lEG

INCLUDES = -I. $(PYINCLUDES) $(FASTJETINCLUDES) $(ROOTINCLUDES)
LDLIBS = -L. $(PYLDLIBS) $(FASTJETLDLIBS) $(ROOTLDLIBS)

all : generateData
	@echo Built $@

clean :
	rm -rf generateData *.a *.o

generateData : generateData.cc libPhysics535.a
	$(LD) $(CXXFLAGS) $(INCLUDES) $(LDFLAGS) $^ $(LDLIBS) -o $@
	@echo Built $@

libPhysics535.a : libPhysics535.a(EventAnalysis.o) libPhysics535.a(UltraFastSim.o)
	@echo Built $@

EventAnalysis.cc : EventAnalysis.h

UltraFastSim.cc : UltraFastSim.h EventData.h

.cc.a :
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $^
	ar rv $@ $*.o
	rm -f $*.o
	@echo Compiled $@
