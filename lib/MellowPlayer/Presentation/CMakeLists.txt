set(LIB_NAME "${PROJECT_NAME}.Presentation")

file(GLOB_RECURSE HEADER_FILES *.hpp)
file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE QML_FILES resources/qml/*.qml)
file(GLOB_RECURSE QRC_FILES *.qrc)

SET(CMAKE_DEBUG_POSTFIX "")
if(WIN32)
    add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES} ${QRC_FILES} ${QML_FILES})
else()
    add_library(${LIB_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES} ${QRC_FILES} ${QML_FILES})
    target_link_libraries(${LIB_NAME} ${PROJECT_NAME}.UseCases)
    install(TARGETS ${LIB_NAME}
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static)
endif()
if (USE_SNORENOTIFY AND LibsnoreQt5_FOUND)
    target_link_libraries(${LIB_NAME} Snore::Libsnore)
endif()
qt5_use_modules(${LIB_NAME} Core Qml Quick WebEngine Widgets)
