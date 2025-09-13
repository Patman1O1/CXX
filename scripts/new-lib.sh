#!/bin/bash

# Parameter for the library name
LIB="$1"

# Parameter for boolean value that determines if the library should be 
# build like a STL (Standard Template Library).
STL="${2:-"f"}" # Defaults to "f" for false
STL="${STL:0:1}" # Strips all characters except for the first
STL="${STL,,}" # Converts the remaining character to lowercase

# Exit the bash script if an invalid argument has been passed to "STL"
if [[ "$STL" != "f" && "$STL" != "t" && "$STL" != "0" && "$STL" != "1" ]]; then
    echo "Error: invalid argument \"$STL\" passed to STL";
    echo "Valid arguments are \"t\", \"f\", \"1\", and \"0\"";
    exit 1;
fi

# Create the library directory
mkdir -p "$LIB";

# Go to the library
cd "$LIB";


# ----------------------------------------------Header File------------------------------------------------ #
# Create the library's header file
touch "$LIB.hpp";

echo "//" >> "$LIB.hpp";
echo "// Created by Patrick Thomas on $(date "+%m/%d/%Y")" >> "$LIB.hpp";
echo "//" >> "$LIB.hpp";
echo "" >> "$LIB.hpp";

echo "#ifndef ${LIB^^}_HPP" >> "$LIB.hpp";
echo "#define ${LIB^^}_HPP" >> "$LIB.hpp";

echo "" >> "$LIB.hpp";
echo "" >> "$LIB.hpp";
echo "" >> "$LIB.hpp";

echo "#endif // ${LIB^^}_HPP" >> "$LIB.hpp";
echo "" >> "$LIB.hpp";


# ----------------------------------------------Source File------------------------------------------------ #
# If the "STL" argument has been set to false...
if [[ "$STL" == "f" || "$STL" == "0" ]]; then
    # Create the library's source file
    touch "$LIB.cpp";

    echo "//" >> "$LIB.cpp";
    echo "// Created by Patrick Thomas on $(date "+%m/%d/%Y")" >> "$LIB.cpp";
    echo "//" >> "$LIB.cpp";
    echo "" >> "$LIB.cpp";

    echo "#include \"$LIB.hpp\"" >> "$LIB.cpp";

    echo "" >> "$LIB.cpp";
    echo "" >> "$LIB.cpp";
    echo "" >> "$LIB.cpp";
fi


# ----------------------------------------------Test Suite------------------------------------------------- #
# Create the test suite
touch "${LIB}_tests.cpp";

echo "#include <gmock/gmock.h>" >> "${LIB}_tests.cpp";
echo "#include <gtest/gtest.h>" >> "${LIB}_tests.cpp";

echo "" >> "${LIB}_tests.cpp";

echo "#include \"${LIB}.hpp\"" >> "${LIB}_tests.cpp";

echo "" >> "${LIB}_tests.cpp";

echo "TEST($LIB, dummy_test) {" >> "${LIB}_tests.cpp";
echo "	EXPECT_THAT(0, testing::Eq(0));" >> "${LIB}_tests.cpp";
echo "}" >> "${LIB}_tests.cpp"; 
    
echo "" >> "${LIB}_tests.cpp";


# -------------------------------------------------Main---------------------------------------------------- #
# Create main
touch "${LIB}_main.cpp";

echo "#include \"$LIB.hpp\"" >> "${LIB}_main.cpp";

echo "" >> "${LIB}_main.cpp";
echo "" >> "${LIB}_main.cpp";

echo "int main() {" >> "${LIB}_main.cpp";

echo "" >> "${LIB}_main.cpp";
echo "" >> "${LIB}_main.cpp";

echo "	return 0;" >> "${LIB}_main.cpp";
echo "}" >> "${LIB}_main.cpp";
echo "" >> "${LIB}_main.cpp";


# -----------------------------------------------.gdbinit-------------------------------------------------- #
# Create .gdbinit
touch .gdbinit;


# ------------------------------------------------Makefile------------------------------------------------- #
# Create the Makefile
touch "Makefile";

echo "# Compiler" >> "Makefile";
echo "CXX = clang++" >> "Makefile";

echo "" >> "Makefile";

echo "# Included C++ Files" >> "Makefile";
echo "INCLUDE = -Iinclude \\
          -I/usr/local/include/c++ \\
          -I/usr/include" >> "Makefile";

echo "" >> "Makefile";

echo "# Included C++ Libraries" >> "Makefile";
echo "LIBS = -L/usr/local/lib/c++ \\
       -L/usr/lib \\
       -lgtest \\
       -lgtest_main \\
       -lgmock \\
       -lgmock_main \\
       -lpthread \\
    " >> "Makefile";

echo "" >> "Makefile";

echo "# Flags" >> "Makefile";
echo "CXXFLAGS = -Wall -g -std=c++23 -fPIC" >> "Makefile";
echo "LDFLAGS = -shared" >> "Makefile";
echo "VALGRIND_FLAGS = -s --tool=memcheck --leak-check=yes --track-origins=yes" >> "Makefile";

echo "" >> "Makefile";

echo "# Library Files" >> "Makefile";
echo "LIB_HDR = $LIB.hpp" >> "Makefile";

# Only create the source, object, and assembly, and shared object files
# if the library is not a template library
if [[ "$STL" == "f"  || "$STL" == "0" ]]; then
    echo "LIB_SRC = $LIB.cpp" >> "Makefile";
    echo "LIB_ASM = $LIB.s" >> "Makefile";
    echo "LIB_OBJ = $LIB.o" >> "Makefile";
    echo "LIB_SHARED_OBJ = lib$LIB.so" >> "Makefile";
fi

echo "" >> "Makefile";

echo "# Test Files" >> "Makefile";
echo "TEST_SRC = ${LIB}_tests.cpp" >> "Makefile";
echo "TEST_ASM = ${LIB}_tests.s" >> "Makefile";
echo "TEST_OBJ = ${LIB}_tests.o" >> "Makefile";
echo "TEST_EXE = ${LIB}_tests.out" >> "Makefile";

echo "" >> "Makefile";

echo "# Main Files" >> "Makefile";
echo "MAIN_SRC = ${LIB}_main.cpp" >> "Makefile";
echo "MAIN_ASM = ${LIB}_main.s" >> "Makefile";
echo "MAIN_OBJ = ${LIB}_main.o" >> "Makefile";
echo "MAIN_EXE = ${LIB}_main.out" >> "Makefile";

echo "" >> "Makefile";

echo "# Compile the source files into assembly files" >> "Makefile";
echo "%.s: %.cpp \$(LIB_HDR)" >> "Makefile";
echo "	\$(CXX) -S \$(CXXFLAGS) \$(INCLUDE) -c \$< -o \$@" >> "Makefile";

echo "" >> "Makefile";

echo "# Compile the source files into relocatable object files" >> "Makefile";
echo "%.o: %.cpp \$(LIB_HDR)" >> "Makefile";
echo "	\$(CXX) \$(CXXFLAGS) \$(INCLUDE) -c $< -o \$@" >> "Makefile";
    
echo "" >> "Makefile";

echo "# Compile the source files into executable object files" >> "Makefile";
echo "%.out: %.o %.so" >> "Makefile";
echo "	\$(CXX) \$(CXXFLAGS) \$(INCLUDE) $< -o \$@" >> "Makefile";
    
echo "" >> "Makefile";

# If "STL" is set to false...
if [[ "$STL" == "f" || "$STL" == "0" ]]; then
    echo "# Create the shared library" >> "Makefile";
    echo "\$(LIB_SHARED_OBJ): \$(LIB_OBJ)" >> "Makefile";
    echo "	\$(CXX) \$(LDFLAGS) \$(LIB_OBJ) -o \$(LIB_SHARED_OBJ)" >> "Makefile";

    echo "" >> "Makefile";

    echo "# Create the test suite" >> "Makefile";
    echo "\$(TEST_EXE): \$(LIB_OBJ) \$(TEST_OBJ)" >> "Makefile";
    echo "	\$(CXX) \$(CXXFLAGS) -Wl,-rpath,/usr/local/lib/c++ -o \$(TEST_EXE) \$(TEST_OBJ) \$(LIB_OBJ) \$(LIBS)" >> "Makefile";

    echo "" >> "Makefile";

    echo "# Create the main suite" >> "Makefile";
    echo "\$(MAIN_EXE): \$(LIB_OBJ) \$(MAIN_OBJ)" >> "Makefile";
    echo "	\$(CXX) \$(CXXFLAGS) -Wl,-rpath,/usr/local/lib/c++ -o \$(MAIN_EXE) \$(MAIN_OBJ) \$(LIB_OBJ) \$(LIBS)" >> "Makefile";

    echo "" >> "Makefile";

    echo "# Install rule" >> "Makefile";
    echo "install: \$(LIB_SHARED_OBJ)" >> "Makefile";
    echo "	sudo cp \$(LIB_SHARED_OBJ) /usr/local/lib/c++" >> "Makefile";
    echo "	sudo cp \$(LIB_HDR) /usr/local/include/c++" >> "Makefile";

    echo "" >> "Makefile";

    echo "# Uninstall rule" >> "Makefile";
    echo "uninstall:" >> "Makefile";
    echo "	sudo rm -f /usr/local/lib/c++/\$(LIB_SHARED_OBJ)" >> "Makefile";
    echo "	sudo rm -f /usr/local/include/c++/\$(LIB_HDR)" >> "Makefile";

    echo "" >> "Makefile";

    echo "# Assembly rule" >> "Makefile";
    echo "assembly: \$(LIB_ASM) \$(MAIN_ASM) \$(TEST_ASM)" >> "Makefile";
else
    echo "# Create the test suite" >> "Makefile";
    echo "\$(TEST_EXE): \$(TEST_OBJ)" >> "Makefile";
    echo "	\$(CXX) \$(CXXFLAGS) -Wl,-rpath,/usr/local/lib/c++ -o \$(TEST_EXE) \$(TEST_OBJ) \$(LIBS)" >> "Makefile";

    echo "" >> "Makefile";

    echo "# Create the main suite" >> "Makefile";
    echo "\$(MAIN_EXE): \$(MAIN_OBJ)" >> "Makefile";
    echo "	\$(CXX) \$(CXXFLAGS) -Wl,-rpath,/usr/local/lib/c++ -o \$(MAIN_EXE) \$(MAIN_OBJ) \$(LIBS)" >> "Makefile";

    echo "" >> "Makefile";

    echo "# Install rule" >> "Makefile";
    echo "install:" >> "Makefile";
    echo "	sudo cp \$(LIB_HDR) /usr/local/include/c++" >> "Makefile";

    echo "" >> "Makefile";

    echo "# Uninstall rule" >> "Makefile";
    echo "uninstall:" >> "Makefile";
    echo "	sudo rm -f /usr/local/include/c++/\$(LIB_HDR)" >> "Makefile";

    echo "" >> "Makefile";

    echo "# Assembly rule" >> "Makefile";
    echo "assembly: \$(MAIN_ASM) \$(TEST_ASM)" >> "Makefile";
fi

echo "" >> "Makefile";

echo "# Test suite rules" >> "Makefile";
echo "build_tests: \$(TEST_EXE)" >> "Makefile";

echo "" >> "Makefile";

echo "run_tests: \$(TEST_EXE)" >> "Makefile";
echo "	./\$(TEST_EXE)" >> "Makefile";

echo "" >> "Makefile";

echo "valgrind_tests: \$(TEST_EXE)" >> "Makefile";
echo "	valgrind \$(VALGRIND_FLAGS) ./\$(TEST_EXE)" >> "Makefile";

echo "" >> "Makefile";

echo "# Main rules" >> "Makefile";
echo "build_main: \$(MAIN_EXE)" >> "Makefile";

echo "" >> "Makefile";

echo "run_main: \$(MAIN_EXE)" >> "Makefile";
echo "	./\$(MAIN_EXE) \$(ARGS)" >> "Makefile";

echo "" >> "Makefile";

echo "gdb_main: \$(MAIN_EXE)" >> "Makefile";
echo "	gdb \$(MAIN_EXE)" >> "Makefile";

echo "" >> "Makefile";

echo "valgrind_main: \$(MAIN_EXE)" >> "Makefile";
echo "	valgrind \$(VALGRIND_FLAGS) ./\$(MAIN_EXE)" >> "Makefile";

echo "" >> "Makefile";

if [[ "$STL" == "f" || "$STL" == "0" ]]; then
    echo "# Rule to clean up build files" >> "Makefile";
    echo "clean: rm -f *.o *.so *exe *.s" >> "Makefile";
else
    echo "# Rule to clean up build files" >> "Makefile";
    echo "clean: rm -f *.o *.exe *.s" >> "Makefile";
fi
