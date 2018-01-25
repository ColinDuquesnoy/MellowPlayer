set(LIB_NAME "${PROJECT_NAME}.QmlImports")

file(GLOB_RECURSE SOURCE_FILES "*.qml" "*.js")
file(GLOB_RECURSE OTHER_FILES  "*.qrc" ".cmake" "qmldir")

# automatically update imports.qrc and MellowPlayer/qmldir
add_custom_target(update_imports COMMAND ${CMAKE_COMMAND} -P UpdateImports.cmake
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DEPENDS ${SOURCE_FILES})

# automatically check for syntax errors in qml and js files
find_program(QMLLINT qmllint)
if (CHECK_QML_SYNTAX AND QMLLINT)
    message(STATUS "Found qmllint: ${QMLLINT}")
    add_custom_target(check_qml_syntax COMMAND ${QMLLINT} ${SOURCE_FILES})
    add_dependencies(update_imports check_qml_syntax)
endif()
add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${OTHER_FILES})
target_link_libraries(${LIB_NAME} Qt5::Core)
