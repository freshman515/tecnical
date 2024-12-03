
 add_library(libcat OBJECT cat.cpp)
 target_include_directories(libcat PUBLIC .)
 
 add_library(libdog OBJECT dog.cpp)
 target_include_directories(libdog PUBLIC .)