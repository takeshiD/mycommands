CFLAGS = -Wall -g
CXX = gcc
BINDIR = ./bin

all: $(BINDIR) spawn mysh

$(BINDIR):
	mkdir -p $(BINDIR)

spawn: spawn.c
	$(CXX) $(CFLAGS) $^ -o $(BINDIR)/$@

mysh: mysh.c
	$(CXX) $(CFLAGS) $^ -o $(BINDIR)/$@

