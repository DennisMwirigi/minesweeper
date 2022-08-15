# Facilitates the building and installation of the software via CMake. 
# Note that this CMakeLists file must support the installation of the software, not just the building of it.

# Specify minimum required version of CMake.
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

# Specify project and languages used.
project(cpp_project LANGUAGES CXX)

# Add program target
add_executable(minesweeper app/main.cpp app/draw.cpp app/game.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include" "/usr/include/GL")

# Install the hello and goodbye programs.
install(TARGETS minesweeper DESTINATION bin)

# Install the demo script.
# install(PROGRAMS demo DESTINATION bin)

# Currently compiling with g++ -framework OpenGL -framework GLUT -o main main.cpp draw.cpp game.cpp -std=c++20