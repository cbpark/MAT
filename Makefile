PKGNAME  := MAT
SRCDIR 	 := src
LIBDIR 	 := lib
CXXFLAGS := -g -O2 -Wall -Wextra -std=c++14 -pedantic -I$(SRCDIR) $(CXXFLAGS)
AR       := ar crs
MKDIR    := mkdir -p
RM       := rm -f
UNAME    := $(shell uname -s)

LIB    := $(LIBDIR)/lib$(PKGNAME).a
LIBSRC := $(wildcard $(SRCDIR)/*.cc)
LIBOBJ := $(LIBSRC:.cc=.o)
EXE    := examples/mat
ifeq ($(UNAME), Darwin)
SHAREDLIB  := $(LIBDIR)/lib$(PKGNAME).dylib
else
SHAREDLIB  := $(LIBDIR)/lib$(PKGNAME).so
endif

DESTDIR ?= /usr/local
HEADERS := $(wildcard $(SRCDIR)/*.h)

# GSL (https://www.gnu.org/software/gsl/)
CXXFLAGS += $(shell gsl-config --cflags)
LIBS     += $(shell gsl-config --libs)

.PHONY: all lib install clean

all: $(LIB)

$(LIB): CXXFLAGS += -fPIC
$(LIB): $(LIBOBJ)
	$(MKDIR) $(LIBDIR)
	$(AR) $@ $^
	ranlib $@

ifeq ($(UNAME), Darwin)
lib: LDFLAGS += -dynamiclib -undefined suppress
else
lib: LDFLAGS += -shared
endif
lib: CXXFLAGS += -fPIC
lib: $(LIBOBJ)
	$(MKDIR) $(LIBDIR)
	$(CXX) $(LDFLAGS) -o $(SHAREDLIB) $^

install: $(LIB) lib $(HEADERS)
	$(MKDIR) $(DESTDIR)/lib
	cp -a $(LIB) $(SHAREDLIB) $(DESTDIR)/lib
	$(MKDIR) $(DESTDIR)/include/$(PKGNAME)
	cp -a $(HEADERS) $(DESTDIR)/include/$(PKGNAME)

examples/%: examples/%.o $(LIB)
	$(CXX) $(LDFLAGS) -o $@ $< $(LIB) $(LIBS)

clean::
	$(RM) $(EXE) $(LIBOBJ) $(LIB) $(SHAREDLIB)
	$(RM) -r $(LIBDIR)
