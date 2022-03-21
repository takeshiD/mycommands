SRCS = mywc.c
CFLAGS = -Wall
CXX = gcc
BINDIR = ./bin

all: $(BINDIR) mywc

mywc: mywc.c
	$(CXX) $(CFLAGS) $^ -o $(BINDIR)/$@

$(BINDIR):
	mkdir -p $(BINDIR)
