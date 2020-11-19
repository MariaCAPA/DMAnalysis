ROOTINC= -I$(shell root-config --incdir)

CC=g++
LD=g++
CXXFLAGS= -g -std=c++11 -fPIC 
#CXXFLAGS= -g -fPIC 
#-std=gnu++11
# -std=c++11 
SOFLAGS = -shared
CCFLAGS = -g `root-config --glibs --cflags --libs` -fPIC -lCore

INCLUDES=-I. ${ROOTINC}

#LIBDIR= -L 
LDLIBS= -lgsl -lgslcblas 
#LDLIBS= -lgsl -lgslcblas -lRooFit -lRooFitCore 

OBJDIR=obj
OUTDIR=lib

DICT=DMDict
LIBNAME=libDMAnalysis

DICTRoo=DMDictRoo
LIBNAMERoo=libDMAnalysisRoo


all: lib libRoo

objects := $(patsubst %.cc,$(OBJDIR)/%.o,$(wildcard *.cc))
objectsRoo := $(patsubst %.cc,$(OBJDIR)/%.o,$(wildcard *.cxx))

lib: $(objects) $(OBJDIR)/$(DICT).o 
	@echo "Linking ... "
	$(LD) $(SOFLAGS)  $(CCFLAGS) ${LIBDIR} ${LDLIBS}  $^  -o $(OUTDIR)/$(LIBNAME).so

libRoo: $(objectsRoo) $(OBJDIR)/$(DICTRoo).o
	@echo "Linking ... "
	$(LD) $(SOFLAGS)  $(CCFLAGS) ${LIBDIR} ${LDLIBS}  $^ -o $(OUTDIR)/$(LIBNAMERoo).so

$(OBJDIR)/$(DICT).o:$(DICT).cc
$(OBJDIR)/$(DICTROO).o:$(DICTROO).cxx

$(DICT).cc: DM*.hh 
	@echo "Generating dictionary $@..."
	rootcint -f $@  -c $(ROOTINC) $^ LinkDef.hh
	#mv DMDict_rdict.pcm lib/. 

$(DICTRoo).cc: RooAnnModPdf.h RooDMPdf.h RooDMInteg.h LinkDef.h
	@echo "Generating dictionary $@..."
	rootcint -f $@  -c $(ROOTINC) $^
	#mv DMDictRoo_rdict.pcm lib/. 

$(OBJDIR)/%.o : %.cc
	$(CC) $(CXXFLAGS) $(INCLUDES) -c  $< -o $@

$(OBJDIR)/%.o : %.C
	$(CC) $(CXXFLAGS) $(INCLUDES) -c  $< -o $@

$(OBJDIR)/%.o : %.cxx
	$(CC) $(CXXFLAGS) $(INCLUDES) -c  $< -o $@



clean:
	rm -f ${DICT}.cc ${DICT}.h $(OUTDIR)/${LIBNAME}.so ${OBJDIR}/*.o
	rm -f ${DICTRoo}.cc ${DICTRoo}.h $(OUTDIR)/${LIBNAMERoo}.so
