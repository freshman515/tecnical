cmake_minimum_required(VERSION 3.20)
project(Animal CXX)

add_subdirectory(animal)

add_executable(Animal main.cpp )

target_link_libraries(Animal PUBLIC libanimal)

target_include_directories(Animal PUBLIC  ${CMAKE_SOURCE_DIR}/animal)