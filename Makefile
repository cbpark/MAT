PKGNAME  := MAT
SRCDIR 	 := src
LIBDIR 	 := lib
CXXFLAGS := -g -O2 -Wall -Wextra -std=c++14 -pedantic -I$(SRCDIR) $(CXXFLAGS)
LDFLAGS  := -O2
AR       := ar crs
MKDIR    := mkdir -p
RM       := rm -f

LIB    := $(LIBDIR)/lib$(PKGNAME).a
LIBSRC := $(wildcard $(SRCDIR)/*.cc)
LIBOBJ := $(LIBSRC:.cc=.o)

# GSL (https://www.gnu.org/software/gsl/)
CXXFLAGS += $(shell gsl-config --cflags)
LDFLAGS  += $(shell gsl-config --libs)

.PHONY: all build clean

all: $(LIB)

$(LIB): CXXFLAGS += -fPIC
$(LIB): $(LIBOBJ)
	$(MKDIR) $(LIBDIR)
	$(AR) $@ $^
	ranlib $@

clean::
	$(RM) $(LIBOBJ) $(LIB)
	$(RM) -r $(LIBDIR)
