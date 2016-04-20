CC = g++
CFLAGS = -D_JUDGE_ -ansi -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++0x -D_GLIBCXX_DEBUG
SOURCES = *.cc
OBJECTS = $(SOURCES: .cc = .o)
EXECUTABLE = program.exe

all: $(EXECUTABLE)

# Configuration for main program compilation
$(EXECUTABLE):
	$(CC) $(FLAGS) -c $(SOURCES)
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(OBJECTS)

# Configuration to build final tar
jutge: documentation
	tar -cvf jutge.tar *.hh *.cc Makefile Doxyfile documentation.tar jp_*.txt

# Configuration to build Documentation tar
documentation:
	tar -cvf documentation.tar DOC/

# Configuration for make clean
clean:
	rm *.o
	rm *.exe