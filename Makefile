# Compiler: default to g++
CC = g++

# Compiler flags: PRO2 standards with an appropriate use of "-D_GLIBCXX_DEBUG"
CFLAGS = -D_JUDGE_ -ansi -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++0x -D_GLIBCXX_DEBUG

# Source files
SOURCES = program.cc Author.cc Book.cc Library.cc Quote.cc Utils.cc

# Object files: One per each source file (.cc)
OBJECTS = $(SOURCES: .cc = .o)

# Executable name: defaults to "program.exe"
EXECUTABLE = program.exe

# Final TAR name: defaults to "practica"
FINAL_TAR = practica

# Handle the default make command with the program generation
all: $(EXECUTABLE)

# Configuration for main program compilation
# We have a "clean" dependency to ensure no bad objects are in the current build
$(EXECUTABLE): clean
	$(CC) $(FLAGS) -c $(SOURCES)
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(OBJECTS)

# Configuration to build final judge tar
$(FINAL_TAR): docs
	tar -cvf $(FINAL_TAR).tar *.hh *.cc Makefile Doxyfile jp_*.txt html.zip

# Configuration to build Documentation tar
docs: clean
	rm -rf DOC/
	doxygen Doxyfile
	zip -r html.zip DOC/html/

# Configuration for make clean
# We use "rm -rf" to recursively delete the files and not prompting the user if they don't exist
clean:
	rm -rf *.o
	rm -rf *.exe
	rm -rf *.tar
	rm -rf *.zip
