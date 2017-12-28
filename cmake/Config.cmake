# detect compilers
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CLANG_COMPILER TRUE)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(GCC_COMPILER TRUE)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    set(INTEL_COMPILER TRUE)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(MSVC_COMPILER TRUE)
endif()

# Treat warnings as errors
if(MSVC_COMPILER)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(TESTS_CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
    add_definitions("/wd4251")
    add_definitions("/wd4127")
    add_definitions("/wd4515")
    add_definitions("/wd4714")
    add_definitions("/wd4100")
    add_definitions("/wd4718")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
    set(TESTS_CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wno-unused-private-field -Wno-c++1z-extensions -Winvalid-pch")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -W -Wall -Wextra -Wno-unused-private-field -Wno-c++1z-extensions -Winvalid-pch -Wnon-virtual-dtor -Wdelete-non-virtual-dtor")
endif()

# Setup compiler settings
# C++17 Required
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_STANDARD 17)
if(MSVC_COMPILER)
    add_compile_options("/std:c++latest")
endif()
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# find common packages
find_package(Threads)


# add uninstall target
configure_file(
    "${CMAKE_SOURCE_DIR}/cmake/uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/uninstall.cmake)
    
if(UNIX AND NOT APPLE)
    EXECUTE_PROCESS(COMMAND "date" "+%Y-%m-%d" OUTPUT_VARIABLE BUILD_DATE)
    string(REGEX REPLACE "\n$" "" BUILD_DATE "${BUILD_DATE}")
else()
    string(TIMESTAMP BUILD_DATE_TIME_STR UTC)
    string(REPLACE "T" ";" BUILD_DATE_TIME_LIST ${BUILD_DATE_TIME_STR})
    list(GET BUILD_DATE_TIME_LIST 0 BUILD_DATE)
endif()

# Use ld.gold if it is available and isn't disabled explicitly
if (USE_LD_GOLD)
    execute_process(COMMAND ${CMAKE_C_COMPILER} -fuse-ld=gold -Wl,--version ERROR_QUIET OUTPUT_VARIABLE LD_VERSION)
    if("${LD_VERSION}" MATCHES "GNU gold" AND GCC_COMPILER)
        message(STATUS "Using GNU gold linker")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold -Wl,--disable-new-dtags")
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold -Wl,--disable-new-dtags")
    else()
        message(WARNING "GNU gold linker isn't available, using the default system linker.")
        set(USE_LD_GOLD OFF)
    endif()
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DQT_QML_DEBUG ")

IF(CMAKE_BUILD_TYPE MATCHES Debug)
    message(STATUS "qml import path: from source directory")
    set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/src/imports CACHE string "" FORCE)
else()
    message(STATUS "qml import path: from imports.qrc")
    set(USE_QML_IMPORT_LIB TRUE)
    add_definitions(-DUSE_IMPORTS_QRC=1)
ENDIF()
