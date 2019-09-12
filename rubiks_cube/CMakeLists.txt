cmake_minimum_required(VERSION 3.12)
project(rubik)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(glm REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
add_executable(rubik main.cpp)

target_link_libraries(rubik ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${GLM_LIBRARY})