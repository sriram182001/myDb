cmake_minimum_required(VERSION 3.16)
project(mydb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include all source files
add_executable(mydb 
    src/main.cpp
    src/storage/Pager.cpp
    src/storage/Table.cpp
    src/storage/Row.cpp
)

# Add include directories
include_directories(src)
