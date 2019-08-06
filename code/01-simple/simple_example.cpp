// This is an example file as part of Modern-CMake

#include "simple_lib.hpp"

#ifndef MYLIB_PUBLIC
#error "Must have MYLIB_PUBLIC defined"
#endif

#ifdef MYLIB_PRIVATE
#error "Must not have MYLIB_PRIVATE defined"
#endif

#include <iostream>

int main() {

    std::cout << "Simple example C++ compiled correctly and ran." << std::endl;
    std::cout << simple_lib_function() << std::endl;

    return 0;
}
