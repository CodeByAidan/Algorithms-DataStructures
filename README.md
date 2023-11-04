# Algorithms and Data Structures in C++
###### Leendert Ammeraal, 1996

link: https://www.amazon.com/Algorithms-Data-Structures-Leen-Ammeraal/dp/0471963550


## wtf how do i run?

Super simple, using the `CMakeLists.txt` file, say you want to run `roman1.cpp` in the 
Chapter1-Some-Aspects-of-Programming-in-C++ folder in the `1-1_Introduction` folder.

All you would have to do, is simply uncomment the following lines
```cmake
set(SOURCE_FILES
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-1_Introduction/roman1.cpp
...
)
```
and
```cmake
include_directories(
#        Project/src/Chapter1-Some-Aspects-of-Programming-in-C++/1-1_Introduction
...
)
```
and then run the following commands in the root directory of the project
```bash
mkdir build
path/to/cmake --build build --target Algorithms_DataStructures -j 14
```
and then run the executable in the `build` folder
```bash
./build/Algorithms_DataStructures
```