CFLAGS = -Wall -g
CXX = gcc
BINDIR = ./bin

all: $(BINDIR) myls

$(BINDIR):
	mkdir -p $(BINDIR)

myls: myls.c
	$(CXX) $(CFLAGS) $^ -o $(BINDIR)/$@
