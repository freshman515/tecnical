cmake_minimum_required(VERSION 3.20)
project(download)
add_executable(download http_download.cpp)

find_package(CURL REQUIRED)
target_link_libraries(download PRIVATE CURL::libcurl)
