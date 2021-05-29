cmake_minimum_required(VERSION 3.16)

project(main)

set(MAIN_FILE main.cpp)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(OPTIMIZATION_FLAGS O3)
option(BUILD_DannyLIB OFF)

set(DannyLIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/DannyLIB)


set(CFLAGS
    -Wall
    -${OPTIMIZATION_FLAGS}
    -fdiagnostics-color=always   # high light the warning or error
    )
set(LDFLAGS

    )
set(DEPEN_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/smlib
    )

add_compile_options(${CFLAGS})
add_link_options(${LDFLAGS})

if(BUILD_DannyLIB)
    add_subdirectory(DannyLIB)
    set(DEPEN_DIR
        ${DEPEN_DIR}
        ${DannyLIB_PATH}/inc
    )
endif()

# Assembly file
FILE(GLOB ASMSRC src/*.s)
# C file
FILE(GLOB CSRC src/*.c)
# C++ file
FILE(GLOB CXXSRC src/*.cpp)

# test file, excecuted file
FILE(GLOB TEST_FILES test/*.c test/*.cpp)

set_property(SOURCE ${ASMSRC} PROPERTY LANGUAGE C)

set(SOURCE_FILE
  ${CSRC}
  ${CXXSRC}
  ${ASMSRC} 
  )

# generate the main executable ifle
add_executable(${PROJECT_NAME} ${MAIN_FILE} ${SOURCE_FILE})

# Include reference
target_include_directories(${PROJECT_NAME} PUBLIC ${DEPEN_DIR})


# library directory
add_subdirectory(divlib)
target_include_directories(${PROJECT_NAME} PUBLIC divlib)
target_link_libraries(${PROJECT_NAME} PUBLIC 
    mylib
    DannyLIB
    m
    )

# generate the test executable file
add_subdirectory(test)
