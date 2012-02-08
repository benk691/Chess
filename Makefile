CXX=g++
CXXFLAGS=-g -Wall
LD=g++

export CXX
export CXXFLAGS
export LD

EXE=chess
OBJS=bin/main.o
SUBDIRS=bin
CLEANDIRS=$(SUBDIRS:%=clean-%)

all: $(EXE)
	$(shell ln -s $(OBJS) $(EXE))

$(EXE): $(SUBDIRS)

$(SUBDIRS):
	@( cd $@ && $(MAKE) )

clean: $(CLEANDIRS)
	rm -rf *.o *~ $(EXE) #*

$(CLEANDIRS):
	$(MAKE) -C $(@:clean-%=%) clean

.PHONY: all clean $(EXE) $(OBJS) $(SUBDIRS) $(CLEANDIRS)

