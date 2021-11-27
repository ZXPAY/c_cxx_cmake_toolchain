FILE(GLOB TEST_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
)

message(STATUS "${TEST_FILES}")

if(UNIX)
foreach(file ${TEST_FILES})
    get_filename_component(barefile ${file} NAME_WE)
    message(STATUS testfile->${barefile})
    add_executable(${barefile} ${file} ${SOURCE_FILE})
    target_include_directories(${barefile} PUBLIC ${DEPEN_DIR})
    target_link_libraries(${barefile} PUBLIC 
        pthread
        mylib
        DannyLIB
        m
        rt
    )
endforeach()
endif()
