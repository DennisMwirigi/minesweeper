# Facilitates the building and installation of the software via CMake. 
# Note that this CMakeLists file must support the installation of the software, not just the building of it.

# Specify minimum required version of CMake.
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lGL -lGLU -lm -lglut")

# Specify project and languages used.
project(cpp_project LANGUAGES CXX)

# Add program target
add_executable(minesweeper app/main.cpp app/draw.cpp app/game.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries(minesweeper ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

# Install the demo script.
install(PROGRAMS demo DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")