set(LIB_NAME "${PROJECT_NAME}.Domain")

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.hpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Settings/schema.json.in ${CMAKE_CURRENT_SOURCE_DIR}/Settings/schema.json)

add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES} domain.qrc ${BUILD_CONFIG_SOURCE})
target_link_libraries(${LIB_NAME} Qt5::Core Qt5::Gui)
if (USE_PRECOMPILED_HEADER)
    set_target_properties(${LIB_NAME} PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "stdafx.hpp")
    set_target_properties(${LIB_NAME} PROPERTIES COTIRE_ADD_UNITY_BUILD FALSE)
    cotire(${LIB_NAME})
endif()