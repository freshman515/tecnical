#include "cat.h"
#ifdef USE_CATTWO
#include "cat2.h"
#endif


std::string Cat::barking() {
#ifdef USE_CATTWO
    return cat2::two();
#else
    return "meow";
#endif 
}