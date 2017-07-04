set(LIB_NAME "${PROJECT_NAME}.Application")

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.hpp)

add_library(${LIB_NAME} STATIC ${SOURCE_FILES} ${HEADER_FILES} application.qrc)
qt5_use_modules(${LIB_NAME} Core Gui)
