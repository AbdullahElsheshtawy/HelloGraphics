# CMakeList.txt : CMake project for HelloGraphics, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.29)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

project (HelloGraphics)

# Add source to this project's executable.
add_executable (HelloGraphics  WIN32 src/main.cpp src/Window.cpp  src/DeviceResources.cpp)
target_link_libraries(HelloGraphics d3d11)
include_directories("include/")