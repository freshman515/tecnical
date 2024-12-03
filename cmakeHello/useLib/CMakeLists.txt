cmake_minimum_required(VERSION 3.20)
project(Animal CXX)

# include_directories(${PROJECT_SOURCE_DIR}/include)
# link_directories(${PROJECT_SOURCE_DIR}/a)
# link_libraries(animal)
# add_executable(app main.cpp)

#动态库
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/so)
add_executable(app main.cpp)
target_link_libraries(app PUBLIC animal)


