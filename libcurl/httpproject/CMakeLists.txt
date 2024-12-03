cmake_minimum_required(VERSION 3.20)

project(HttpClientProject)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#源文件
set(SOURCE HttpClient.cpp main.cpp)
#头文件路径
include_directories(${PROJECT_SOURCE_DIR})
add_executable(HttpClientTest ${SOURCE})
#查找依赖库
find_package(CURL REQUIRED)

# 如果 log4cpp 没有 CMake 配置文件，手动指定路径
set(LOG4CPP_LIB "/usr/lib/x86_64-linux-gnu/liblog4cpp.so")
set(LOG4CPP_INCLUDE "/usr/include/log4cpp")



target_link_libraries(HttpClientTest PRIVATE
     CURL::libcurl 
     log4cpp
 )

