# CMakeLists.txt

cmake_minimum_required(VERSION 3.12)
project(mathlib VERSION 1.0)

# Create a shared library
add_library(mathlib SHARED mathlib.cpp)

# Set the library version and compatibility version
set_target_properties(mathlib PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

# Specify the installation path for the library
install(TARGETS mathlib
    LIBRARY DESTINATION lib
    PUBLIC_HEADER DESTINATION include
)

# Specify the header files to be installed
install(FILES mathlib.h DESTINATION include)
