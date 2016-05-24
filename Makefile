# Compiler: default to g++
CC = g++

# Compiler flags: PRO2 standards with an appropriate use of "-D_GLIBCXX_DEBUG"
CFLAGS = -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++0x

# Main program source file
MAIN = program.cc

# Source files
SOURCES = Author.cc Book.cc Library.cc Quote.cc Utils.cc

# Header files: One per each source file (.cc)
HEADERS = $(SOURCES:.cc=.hh)

# Object files: One per each source file (.cc)
OBJECTS = $(MAIN:.cc=.o) $(SOURCES:.cc=.o)

# Executable name: defaults to "program.exe"
EXECUTABLE = $(MAIN:.cc=.exe)

# Final TAR name: defaults to "practica"
FINAL_TAR = practica

# Handle the default make command with the program generation
all: $(EXECUTABLE)

# Configuration for main program compilation
# We have a "clean" dependency to ensure no bad objects are in the current build
$(EXECUTABLE): clean
	$(CC) $(FLAGS) -c $(MAIN) $(SOURCES)
	$(CC) $(FLAGS) -o $(EXECUTABLE) $(OBJECTS)

# [DELETE] Configuration to build a quick judge tar
jutge:
	tar -cvf jutge.tar $(HEADERS) $(MAIN) $(SOURCES) Makefile Doxyfile jp_*.txt equip.pdf

# Configuration to build final judge tar
$(FINAL_TAR): docs
	tar -cvf $(FINAL_TAR).tar $(HEADERS) $(MAIN) $(SOURCES) Makefile Doxyfile jp_*.txt html.zip equip.pdf

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
