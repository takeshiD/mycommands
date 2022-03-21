SRCS = mycat.c
CXX = gcc
CFLAGS = -Wall
BINDIR = ./bin
all: $(BINDIR) mycat mycat2

$(BINDIR):
	mkdir -p $@

mycat: mycat.c
	$(CXX) $(CFLAGS) $^ -o $(BINDIR)/$@

mycat2: mycat2.c
	$(CXX) $(CFLAGS) $^ -o $(BINDIR)/$@
