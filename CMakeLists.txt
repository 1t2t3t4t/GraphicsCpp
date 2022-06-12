cmake_minimum_required(VERSION 3.21)
project(GraphicsCpp)

set(CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(Src)

file(GLOB SRC Src/*.h Src/*.cpp)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Shaders/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Shaders/)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Assets/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Assets/)

add_executable(GraphicsCpp ${SRC})
target_link_libraries(GraphicsCpp ${CONAN_LIBS})