#
# Makefile
#
#

CXX		= g++
CXXFLAGS= -O2 -c

MKBOBJS	= Des.o mkbing.o
UNBOBJS = Des.o unbing.o

all		: mkbing unbing

%.cpp	: %.o
		$(CXX) $(CXXFLAGS) $< -o $@

mkbing	: $(MKBOBJS)
		$(CXX) $(MKBOBJS) -o mkbing

unbing	: $(UNBOBJS)
		$(CXX) $(UNBOBJS) -o unbing

clean	:
		rm -f $(OBJS)
		rm -f mkbing
		rm -f unbing

