CFLAGS = -Wall -g
CXX = gcc
BINDIR = ./bin

all: $(BINDIR) mygrep

$(BINDIR):
	mkdir -p $(BINDIR)

mygrep: mygrep.c
	$(CXX) $(CFLAGS) $^ -o $(BINDIR)/$@
