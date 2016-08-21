PROG = ssfi

C = g++
CCFLAGS = -g -O2 -Wfatal-errors -Wshadow -Wall -std=c++0x -lstdc++ -L/usr/local/lib -I/usr/include/boost
LDFLAGS = -lboost_system -lboost_filesystem -lboost_program_options -lboost_thread

all:
	$(MAKE) -C src

clean:
	$(MAKE) clean -C src
