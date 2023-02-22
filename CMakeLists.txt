############################
###### Cmake template ######
############################

# author: sami dhiab
# email: sami@theion.de



cmake_minimum_required(VERSION 3.5.0)

# project name, exec and lib
set(project_name KeyenceServer)
set(library_name KeyenceServerLib)
set(executable_name KeyenceServerBin)
set(VCPKG_ROOT C:/vcpkg CACHE FILEPATH "${VCPKG_ROOT}")

project(${project_name} VERSION "1.0")

# set the C++ standard: 20 is set
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
#This is necessary for MSVC to create a symbol file, .lib, besides a shared library, .dll
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()
# add child cmake
add_subdirectory(dependencies)
# includes
include_directories(${PROJECT_SOURCE_DIR}/includes/)
include_directories(${PROJECT_SOURCE_DIR}/dependencies/lib_keyence_sdk/includes/)

########################## add subdirectory##################
set(CMAKE_PREFIX_PATH "${VCPKG_ROOT}/installed/x64-windows/share")
message(" child: vcpkg root folder: ${VCPKG_ROOT}") 
find_package(sockpp CONFIG REQUIRED)
# add dependencies cmake
add_definitions(-D_SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING)  
add_definitions(-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)  

# add all source *.cpp : change repo name
file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    )

# make the exec: change project name
add_executable(${executable_name} ${all_SRCS})
#set_target_properties()

# link againt library
target_link_libraries(${executable_name}
# keyence interface lib
PUBLIC keyenceLib
PUBLIC wsock32 
PUBLIC ws2_32
# sockpp lib
PUBLIC ${SOCKPP_LIBRARIES}
)
target_include_directories(${executable_name} 
PUBLIC ${SOCKPP_INCLUDE_DIRS}
)
# copy lib/ dlls to exe folder
add_custom_command(TARGET ${executable_name} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${executable_name}> $<TARGET_FILE_DIR:${executable_name}>
  COMMAND_EXPAND_LISTS
  )




