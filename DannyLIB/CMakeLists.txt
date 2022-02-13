set(LIBNAME DannyLIB)

FILE(GLOB CSRC src/*.c)
FILE(GLOB CXXSRC src/*.cpp)

add_library(${LIBNAME} ${CSRC})
target_include_directories(${LIBNAME} PUBLIC inc)

