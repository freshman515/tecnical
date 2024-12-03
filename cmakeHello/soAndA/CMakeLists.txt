cmake_minimum_required(VERSION 3.20)
project(Animal CXX)

# Add your source files here
file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

#静态
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/a)
# add_library(animal STATIC ${SRC})

#动态库
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/so)
add_library(animal SHARED ${SRC})



