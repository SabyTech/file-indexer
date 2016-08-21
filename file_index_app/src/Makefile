CC = g++
PROG = ssfi

CCFLAGS = -g -O2 -Wfatal-errors -Wshadow -Wall -std=c++0x -lstdc++ -L/usr/local/lib -I/usr/include/boost
LDFLAGS = -lboost_system -lboost_filesystem -lboost_program_options -lboost_thread

OBJECTDIR = ../obj
BINDIR = ../bin

all: $(PROG)

clean:
	rm -f $(PROG) $(OBJECTS)

OBJECTS = $(OBJECTDIR)/FileSource.o \
	  $(OBJECTDIR)/main_ssfi.o \
          $(OBJECTDIR)/FileIndexer.o \
	  $(OBJECTDIR)/FileParser.o

$(PROG): $(OBJECTS) 
	$(CC) $(CCFLAGS) $(OBJECTS) $(LDFLAGS) -o $(BINDIR)/$(PROG)

$(OBJECTDIR)/FileSource.o: FileSource.cpp
	$(CC) $(CCFLAGS) $(LDFLAGS) -c FileSource.cpp -o $(OBJECTDIR)/FileSource.o

$(OBJECTDIR)/FileIndexer.o: FileIndexer.cpp
	$(CC) $(CCFLAGS) $(LDFLAGS) -c FileIndexer.cpp -o $(OBJECTDIR)/FileIndexer.o

$(OBJECTDIR)/FileParser.o: FileParser.cpp
	$(CC) $(CCFLAGS) $(LDFLAGS) -c FileParser.cpp -o $(OBJECTDIR)/FileParser.o

$(OBJECTDIR)/main_ssfi.o: main_ssfi.cpp
	$(CC) $(CCFLAGS) $(LDFLAGS) -c main_ssfi.cpp -o $(OBJECTDIR)/main_ssfi.o
