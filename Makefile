ROOTCFLAGS := $(shell root-config --cflags)
ROOTLIBS   := $(shell root-config --glibs)

CC = g++
LD = g++

CXXFLAGS = -g -std=c++17 -fPIC $(ROOTCFLAGS)
LDFLAGS  = -shared
LDLIBS   = $(ROOTLIBS)

INCLUDES = -I. -I$(shell root-config --incdir)

OBJDIR = obj
OUTDIR = lib

DICT = DMDict
LIBNAME = libDMAnalysis

DICTRoo = DMDictRoo
LIBNAMERoo = libDMAnalysisRoo

objects    := $(patsubst %.cc,$(OBJDIR)/%.o,$(wildcard *.cc))
objectsRoo := $(patsubst %.cxx,$(OBJDIR)/%.o,$(wildcard *.cxx))

all: dirs lib libRoo

dirs:
	mkdir -p $(OBJDIR) $(OUTDIR)

lib: $(objects) $(OBJDIR)/$(DICT).o
	@echo "Linking $@..."
	$(LD) $(LDFLAGS) -o $(OUTDIR)/$(LIBNAME).so $^ $(LDLIBS)

libRoo: $(objectsRoo) $(OBJDIR)/$(DICTRoo).o
	@echo "Linking $@..."
	$(LD) $(LDFLAGS) -o $(OUTDIR)/$(LIBNAMERoo).so $^ $(LDLIBS)

$(DICT).cc: DM*.hh LinkDef.hh | dirs
	@echo "Generating dictionary $@..."
	rootcling -f $@ -c $(INCLUDES) $^

$(DICTRoo).cxx: RooAnnModPdf.h RooDMPdf.h RooDMInteg.h LinkDef.h | dirs
	@echo "Generating dictionary $@..."
	rootcling -f $@ -c $(INCLUDES) $^

$(OBJDIR)/%.o: %.cc | dirs
	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: %.C | dirs
	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJDIR)/%.o: %.cxx | dirs
	$(CC) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(DICT).cc $(DICT).h
	rm -f $(DICTRoo).cxx $(DICTRoo).h
	rm -f $(OUTDIR)/$(LIBNAME).so $(OUTDIR)/$(LIBNAMERoo).so
	rm -f $(OUTDIR)/*.pcm $(OUTDIR)/*.rootmap
	rm -f $(OBJDIR)/*.o
