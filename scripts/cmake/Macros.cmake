macro(set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

macro (create_test target libs)
    configure_file(${CMAKE_SOURCE_DIR}/cmake/test_main.cpp.in test_main.cpp)
    STRING(REPLACE "-Werror" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    STRING(REPLACE "-Weverything" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
    add_executable(${PROJECT_NAME} ${SOURCE_FILES} test_main.cpp)
    target_link_libraries(${PROJECT_NAME}
            ${libs}
            gtest
            ${CMAKE_THREAD_LIBS_INIT})
    add_test (NAME ${target} COMMAND $<TARGET_FILE:${target}>)
endmacro (create_test)

macro(COPY_FILES TARGET_NAME FILES DESTINATION)
    add_custom_target(${TARGET_NAME} ALL COMMENT "Copying files...")
    foreach(PATH ${FILES})
        add_custom_command(TARGET ${TARGET_NAME}
                COMMAND ${CMAKE_COMMAND} -E copy ${PATH} ${DESTINATION})
    endforeach()
endmacro()
