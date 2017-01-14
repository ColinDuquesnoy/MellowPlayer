set(LIB_NAME "${PROJECT_NAME}_entities")

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.hpp)

add_library(${LIB_NAME} SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${LIB_NAME} PUBLIC .)
qt5_use_modules(${LIB_NAME} Core)
install(TARGETS ${LIB_NAME} LIBRARY DESTINATION lib/static)
