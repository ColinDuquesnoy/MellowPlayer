set(LIB_NAME "${PROJECT_NAME}.Entities")

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.hpp)

add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES})
qt5_use_modules(${LIB_NAME} Core Gui)
