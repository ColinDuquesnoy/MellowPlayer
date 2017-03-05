set(LIB_NAME "${PROJECT_NAME}.UseCases")

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.hpp)

if(WIN32)
    add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
else()
    add_library(${LIB_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES} ISystemTrayIcon.hpp IApplicationSettings.hpp)
    target_link_libraries(${LIB_NAME} ${PROJECT_NAME}.Entities)
    install(TARGETS ${LIB_NAME}
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static)
endif()
qt5_use_modules(${LIB_NAME} Core)
