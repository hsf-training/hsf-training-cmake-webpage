#include <string>

#ifndef MYLIB_PUBLIC
#error "Must have MYLIB_PUBLIC defined"
#endif

#ifndef MYLIB_PRIVATE
#error "Must have MYLIB_PRIVATE defined"
#endif

std::string simple_lib_function() {
    return "Compiled in library";

}
