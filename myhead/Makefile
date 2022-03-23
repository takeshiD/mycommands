CFLAGS = -Wall -g
CXX = gcc
BINDIR = ./bin

all: $(BINDIR) myhead mytail mytail2

$(BINDIR):
	mkdir -p $(BINDIR)

myhead: myhead.c
	$(CXX) $(CFLAGS) $^ -o $(BINDIR)/$@

mytail: mytail.c
	$(CXX) $(CFLAGS) $^ -o $(BINDIR)/$@

mytail2: mytail2.c
	$(CXX) $(CFLAGS) $^ -o $(BINDIR)/$@
