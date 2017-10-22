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
# C++11 Required
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
if(MSVC_COMPILER)
add_compile_options("/std:c++latest")
else()
add_compile_options("-std=c++1z")
endif()
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# find common packages
find_package(Threads)


# add uninstall target
configure_file(
    "${CMAKE_SOURCE_DIR}/scripts/cmake/uninstall.cmake.in"
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
