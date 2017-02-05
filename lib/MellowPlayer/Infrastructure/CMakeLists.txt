set(LIB_NAME "${PROJECT_NAME}.Infrastructure")

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.hpp)
include_directories(${CMAKE_SOURCE_DIR}/3rdparty/spdlog-0.11.0/include/)
if(WIN32)
    add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
else()
    add_library(${LIB_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})

    install(TARGETS ${LIB_NAME}
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static)
endif()
target_link_libraries(${LIB_NAME} ${PROJECT_NAME}.Entities ${PROJECT_NAME}.UseCases)
qt5_use_modules(${LIB_NAME} Core)
