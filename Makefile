PKGNAME  := MAT
SRCDIR 	 := src
LIBDIR 	 := lib
CXXFLAGS := -g -O2 -Wall -Wextra -std=c++14 -pedantic -I$(SRCDIR) $(CXXFLAGS)
AR       := ar crs
MKDIR    := mkdir -p
RM       := rm -f

LIB    := $(LIBDIR)/lib$(PKGNAME).a
LIBSRC := $(wildcard $(SRCDIR)/*.cc)
LIBOBJ := $(LIBSRC:.cc=.o)
EXE    := examples/mat

DESTDIR ?= /usr/local
HEADERS := $(wildcard $(SRCDIR)/*.h)

# GSL (https://www.gnu.org/software/gsl/)
CXXFLAGS += $(shell gsl-config --cflags)
LIBS     += $(shell gsl-config --libs)

.PHONY: all install clean

all: $(LIB)

$(LIB): CXXFLAGS += -fPIC
$(LIB): $(LIBOBJ)
	$(MKDIR) $(LIBDIR)
	$(AR) $@ $^
	ranlib $@

install: $(LIB) $(HEADERS)
	$(MKDIR) $(DESTDIR)/lib
	cp -a $(LIB) $(DESTDIR)/lib
	$(MKDIR) $(DESTDIR)/include/$(PKGNAME)
	cp -a $(HEADERS) $(DESTDIR)/include/$(PKGNAME)

examples/%: examples/%.o $(LIB)
	$(CXX) $(LDFLAGS) -o $@ $< -L$(LIBDIR) -l$(PKGNAME) $(LIBS)

clean::
	$(RM) $(EXE) $(LIBOBJ) $(LIB)
	$(RM) -r $(LIBDIR)
