cmake_minimum_required(VERSION 3.12)
project(exercise2)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
add_executable(1a 1a.cpp)
add_executable(1b 1b.cpp)
add_executable(2 2.cpp)
add_executable(3 3.cpp)
add_executable(4 4.cpp)

target_link_libraries(1a ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(1b ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(2 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(3 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
target_link_libraries(4 ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})