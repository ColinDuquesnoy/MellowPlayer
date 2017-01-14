function(QT5_QUERY_QMAKE VAR RESULT)
    get_target_property(QT_QMAKE_EXECUTABLE ${Qt5Core_QMAKE_EXECUTABLE} IMPORTED_LOCATION)
    execute_process(COMMAND "${QT_QMAKE_EXECUTABLE}" -query ${VAR}
            RESULT_VARIABLE return_code
            OUTPUT_VARIABLE output
            OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_STRIP_TRAILING_WHITESPACE)
    if(NOT return_code)
        file(TO_CMAKE_PATH "${output}" output)
        set(${RESULT} ${output} PARENT_SCOPE)
    endif()
endfunction()

set(QT_MIN_VERSION 5.7)
find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS Core Qml Quick Test QuickControls2)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
qt5_query_qmake(QT_INSTALL_QML QT_QML_DIR)
set(QML_INSTALL_DIR ${QT_QML_DIR}/HackEdit/Editor)
