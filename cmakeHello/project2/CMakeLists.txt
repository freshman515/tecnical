cmake_minimum_required(VERSION 3.20)
project(Animal CXX)
include(animal/animal.cmake)
add_executable(animal main.cpp ${animal_source})