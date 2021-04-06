set(LIBNAME mylib)

FILE(GLOB CSRC src/*.c)
FILE(GLOB CXXSRC src/*.cpp)
 
message(STATUS ${CSRC} ${CXXSRC})

add_library(${LIBNAME} ${CSRC})
target_include_directories(${LIBNAME} PUBLIC inc)




