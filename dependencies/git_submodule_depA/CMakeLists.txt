############################
###### Cmake template ######
############################

# author: sami dhiab
# email: sami@theion.de



cmake_minimum_required(VERSION 3.5.0)

# project name and version: change project name
project(ClassLib VERSION "1.0")
#This is necessary for MSVC to create a symbol file, .lib, besides a shared library, .dll
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()
# set the C++ standard: 20 is set
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)



# make the exec: change project name
add_library(ClassLib SHARED 
class.h 
class.cpp)

