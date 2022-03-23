SRCS = myhead.c
CFLAGS = -Wall -g
CXX = gcc
BINDIR = ./bin

all: $(BINDIR) myhead

$(BINDIR):
	mkdir -p $(BINDIR)

myhead: myhead.c
	$(CXX) $(CFLAGS) $^ -o $(BINDIR)/$@

