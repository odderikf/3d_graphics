cmake_minimum_required(VERSION 3.12)
project(exercise1)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
add_executable(a a.cpp)
add_executable(b b.cpp)

target_link_libraries(a ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(b ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})