file(GLOB_RECURSE SOURCE_FILES "*.qml" "*.js")

# Generate imports.qrc
macro(GENERATE_IMPORTS_QRC)
    message("updating imports.qrc")

    file(WRITE imports.qrc "<!DOCTYPE RCC>\n")
    file(APPEND imports.qrc "<RCC version=\"1.0\">\n")
    file(APPEND imports.qrc "    <qresource prefix=\"/MellowPlayer/imports\">\n")
    file(APPEND imports.qrc "        <file>MellowPlayer/qmldir</file>\n")
    foreach(FILE ${SOURCE_FILES})
        string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" RELATIVE_PATH ${FILE})
        file(APPEND imports.qrc "        <file>${RELATIVE_PATH}</file>\n")
        endif()
    endforeach()

    file(APPEND imports.qrc "    </qresource>\n")
    file(APPEND imports.qrc "</RCC>\n")
endmacro()

macro(GENERATE_QML_DIR)
    message("updating qmldir")
    file(WRITE MellowPlayer/qmldir "module MellowPlayer\n\n")
    file(APPEND MellowPlayer/qmldir "singleton MaterialIcons 3.0 MaterialIcons.qml\n\n")

    foreach(FILE ${SOURCE_FILES})
        if (${FILE} MATCHES "MaterialIcons")
            continue()
        endif()
        string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/MellowPlayer/" "" RELATIVE_PATH ${FILE})
        get_filename_component(BASE_NAME ${RELATIVE_PATH} NAME_WE)
        file(APPEND MellowPlayer/qmldir "${BASE_NAME} 3.0 ${RELATIVE_PATH}\n")
    endforeach()

endmacro()

GENERATE_QML_DIR()
GENERATE_IMPORTS_QRC()
