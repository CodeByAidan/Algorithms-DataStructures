cmake_minimum_required(VERSION 3.26)
project(Algorithms_DataStructures)

set(CMAKE_CXX_STANDARD 14)

# Source files for your project
set(SOURCE_FILES
#        Project/src/Chapter2-Arithmetic/2-7_Multi-precision-Arithmetic/lapp.cpp
        Project/src/Chapter2-Arithmetic/2-7_Multi-precision-Arithmetic/large.h
        Project/src/Chapter2-Arithmetic/2-7_Multi-precision-Arithmetic/large.cpp
        Project/src/Chapter2-Arithmetic/2-8_Binomial-Coefficients/binom.cpp
        #        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-1_Introduction/roman1.cpp
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-2_References-and-Reference-Counting/ints.cpp
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-2_References-and-Reference-Counting/ints.h
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-2_References-and-Reference-Counting/ints0.cpp
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-2_References-and-Reference-Counting/ints0.h
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-2_References-and-Reference-Counting/intsapp.cpp
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-3_Function-Templates/swap.cpp
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-4_Recursive-Functions/roman2.cpp
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-5_Dynamic-Arrays-Chunks-and-Class-Templates/chunk.cpp
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-5_Dynamic-Arrays-Chunks-and-Class-Templates/tplchunk.cpp
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-6_Exception-Handling/except.cpp
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/Exercises/1.1/charstring.cpp
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/Exercises/1.1/charstring.h
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/Exercises/1.2/main.cpp
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/Exercises/1.2/ReversePrint.cpp
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/Exercises/1.2/ReversePrint.h
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/Exercises/1.3/roman3.cpp
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/Exercises/1.4/main.cpp
#        Project/src/Chapter2-Arithmetic/2-4_Radix-Conversion-for-Output-Operations/num2char.cpp
#        Project/src/Chapter2-Arithmetic/2-6_Double-precision-Unsigned-Integers/dblulong.cpp
)

# Include directories for your project
include_directories(
            Project/src/Chapter2-Arithmetic/2-7_Multi-precision-Arithmetic
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-1_Introduction
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-2_References-and-Reference-Counting
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-3_Function-Templates
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-4_Recursive-Functions
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-5_Dynamic-Arrays-Chunks-and-Class-Templates
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-6_Exception-Handling
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/Exercises/1.1
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/Exercises/1.2
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/Exercises/1.3
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/Exercises/1.4
#        Project/src/Chapter2-Arithmetic/2-4_Radix-Conversion-for-Output-Operations
#        Project/src/Chapter2-Arithmetic/2-6_Double-precision-Unsigned-Integers
)

# Create an executable target
add_executable(Algorithms_DataStructures ${SOURCE_FILES})
