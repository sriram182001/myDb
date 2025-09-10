cmake_minimum_required(VERSION 3.16)
project(mydb LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include all source files
add_executable(mydb 
    src/main.cpp
    src/pager/Pager.cpp
    src/table/Table.cpp
    src/row/Row.cpp
)

# Add include directories
include_directories(src)
