SYSTEMC_DIR = /usr/local/systemc-2.3.2
PROJECT     = DMA
BUILDFLAGS  = -g3
CXX         = g++

INCFLAGS    = -I. -I${SYSTEMC_DIR}/include
LDFLAGS     = -L${SYSTEMC_DIR}/lib-linux64 -lsystemc -lm
SRC_CPPHEAD = MEM1_TLM MEM2_TLM DMA_TLM DMA
SRC_CPP     = $(SRC_CPPHEAD:=.cpp}
MAIN        = main.cpp
OBJECTS     = $(SRC_CPPHEAD:=.o)

EXE = $(PROJECT)

all: $(EXE)

$(EXE): $(MAIN) $(OBJECTS) $(HEADERS)
	@echo "$@ building..."
	$(CXX) $(INCFLAGS) $(MAIN) $(OBJECTS) $(LDFLAGS) -o $@
	@echo ""
	@echo "$@ build done successfully..."
	@echo ""

%.o:%.cpp %.h
	@echo "Compiling $< ..."
	$(CXX) -c $< $(INCFLAGS)

clean:
	rm -f $(EXE) \
	rm -f *.o
	rm -f *.vcd
