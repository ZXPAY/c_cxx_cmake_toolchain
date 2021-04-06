cmake_minimum_required(VERSION 3.16)

project(hello_world)

set(MAIN_FILE main.cpp)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(OPTIMIZATION_FLAGS O3)

set(CFLAGS
    -Wall
    -${OPTIMIZATION_FLAGS}
    -fdiagnostics-color=always   # high light the warning or error
    )
set(DEPEN_DIR
  inc
  )

add_compile_options(${CFLAGS})

# Assembly file
FILE(GLOB ASMSRC src/*.s)
# C file
FILE(GLOB CSRC src/*.c)
# C++ file
FILE(GLOB CXXSRC src/*.cpp)

# test file, excecuted file
FILE(GLOB TEST_FILES test/*.c test/*.cpp)


message(STATUS ${ASMSRC})
message(STATUS ${CSRC})
message(STATUS ${CXXSRC})
message(STATUS ${STARTUP_FILE})
message(STATUS ${LINKER_FILE})
message(STATUS ${CMAKE_OBJCOPY})

set_property(SOURCE ${ASMSRC} PROPERTY LANGUAGE C)

set(SOURCE_FILE
  ${CSRC}
  ${CXXSRC}
  ${ASMSRC} 
  )

# generate the main executable ifle
add_executable(${PROJECT_NAME} ${MAIN_FILE} ${SOURCE_FILE})

# generate the test executable file
foreach(file ${TEST_FILES})
  get_filename_component(barefile ${file} NAME_WE)
  message(STATUS testfile->${barefile})
  add_executable(${barefile} ${file} ${SOURCE_FILE})
  target_include_directories(${barefile} PUBLIC ${DEPEN_DIR})
endforeach()

# Include reference
target_include_directories(${PROJECT_NAME} PUBLIC ${DEPEN_DIR})


# library directory
add_subdirectory(divlib)
target_include_directories(${PROJECT_NAME} PUBLIC divlib)
target_link_libraries(${PROJECT_NAME} PUBLIC mylib)       # library name




