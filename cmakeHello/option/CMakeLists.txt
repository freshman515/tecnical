cmake_minimum_required(VERSION 3.20)
project(Animal CXX)

#设置C++版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(config.h.in config.h)
add_subdirectory(animal)

add_executable(Animal main.cpp )

target_link_libraries(Animal PUBLIC libanimal)

target_include_directories(Animal PUBLIC ${CMAKE_BINARY_DIR} ${PROJECT_SOURCE_DIR}/animal)