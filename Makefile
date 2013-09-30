CC=gcc
CXX=g++-4.8
RM=rm -f
CPPFLAGS=-g -std=c++11
LDFLAGS=-g
LDLIBS=

SRCS=main.cpp simulator.cpp resend.cpp node.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: simulator

simulator: $(OBJS)
	$(CXX) $(LDFLAGS) -o simulator $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	rm -f ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .dependtool

include .depend