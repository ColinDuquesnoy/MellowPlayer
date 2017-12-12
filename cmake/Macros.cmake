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

# taken from https://github.com/hluk/qxtglobalshortcut
macro(add_framework fwname appname)
    find_library(FRAMEWORK_${fwname}
            NAMES ${fwname}
            PATHS ${CMAKE_OSX_SYSROOT}/System/Library
            PATH_SUFFIXES Frameworks
            NO_DEFAULT_PATH)
    if( ${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
        MESSAGE(ERROR ": Framework ${fwname} not found")
    else()
        TARGET_LINK_LIBRARIES(${appname} "${FRAMEWORK_${fwname}}/${fwname}")
        MESSAGE(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
    endif()
endmacro()


macro(glob_recurse_excl SOURCE_FILES FILE_EXT EXCLUDE_DIRS)
    file (GLOB_RECURSE SOURCE_FILES_LIST ${FILE_EXT})
    separate_arguments(EXCLUDE_DIRS)
    foreach (TMP_PATH ${SOURCE_FILES_LIST})
        foreach(EXCLUDE_DIR ${EXCLUDE_DIRS})
            string (FIND ${TMP_PATH} ${EXCLUDE_DIR} EXCLUDE_DIR_FOUND)
            if (NOT ${EXCLUDE_DIR_FOUND} EQUAL -1)
                list(REMOVE_ITEM SOURCE_FILES_LIST ${TMP_PATH})
            endif ()
        endforeach()
    endforeach(TMP_PATH)
    set(${SOURCE_FILES} ${SOURCE_FILES_LIST})
endmacro()


MACRO(SUBDIRLIST result curdir)
    FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
    SET(dirlist "")
    FOREACH(child ${children})
        IF(IS_DIRECTORY ${curdir}/${child})
            LIST(APPEND dirlist ${child})
        ENDIF()
    ENDFOREACH()
    SET(${result} ${dirlist})
ENDMACRO()
