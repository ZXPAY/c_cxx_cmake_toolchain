set(ALGO_LIBNAME algo_lib)

FILE(GLOB STRUCT_CSRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)

message(STATUS "=====${STRUCT_CSRC}")

add_library(${ALGO_LIBNAME} ${STRUCT_CSRC})
target_include_directories(${ALGO_LIBNAME} PUBLIC inc)

