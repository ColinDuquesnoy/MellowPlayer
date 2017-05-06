file(GLOB_RECURSE HEADER_FILES ${CMAKE_SOURCE_DIR}/lib/*.hpp)

# plugins files (include them as source to be able to see them in QtCreator)
set(CMAKE_AUTOMOC OFF)

add_executable(${PROJECT_NAME} main.cpp DI.hpp)
include_directories(../3rdparty)
target_link_libraries(${PROJECT_NAME}
        ${PROJECT_NAME}.Entities
        ${PROJECT_NAME}.UseCases
        ${PROJECT_NAME}.Presentation
        ${PROJECT_NAME}.Infrastructure)
qt5_use_modules(${PROJECT_NAME} Core Gui Quick QuickControls2 WebEngine Widgets)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)
