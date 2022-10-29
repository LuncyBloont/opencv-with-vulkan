cmake_minimum_required(VERSION 3.0.0)
project(ImageProcessing VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(LAB_PATH "./lab6/3/main.cpp") # 选择实验代码目录

include(CTest)
enable_testing()
# set(CMAKE_BUILD_TYPE "Release") # 加速编译
add_definitions(-DDEBUG)

aux_source_directory("./src/" SRC)
aux_source_directory("./src/vk" VK_HELP_SRC)

add_executable(ImageProcessing ${LAB_PATH} ${SRC} ${VK_HELP_SRC})

include("./libconfig/includeDirs.cmake")
include("./libconfig/libraryDirs.cmake")
include("./libconfig/library.cmake")

target_include_directories(
    ImageProcessing
    PRIVATE
    "./include/"
    "./include/vk"
    ${TPINCDIR}
)

target_link_directories(
    ImageProcessing
    PRIVATE
    ${TPLIBDIR}
)

target_link_libraries(
    ImageProcessing
    PRIVATE
    ${TPLIBS}
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
