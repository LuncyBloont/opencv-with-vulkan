cmake_minimum_required(VERSION 3.0.0)
project(ImageProcessing VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(DEBUG "Off")

include(CTest)
enable_testing()

if(DEBUG)
    set(CMAKE_BUILD_TYPE "Debug")
    add_definitions(-DDEBUG)
else()
    set(CMAKE_BUILD_TYPE "Release") # 加速编译
endif()

file(GLOB_RECURSE SRC "./src/**.cpp")
file(GLOB_RECURSE HDR "./include/**.hpp" "./include/**.h")
file(GLOB_RECURSE SDR "./shaderLib/**.glsl" "./shaders/**.frag" "./shaders/**.vert", "./defaultVS/**.vert")

file(GLOB_RECURSE mains ./examples/*/*/main.cpp)

include("./libconfig/includeDirs.cmake")
include("./libconfig/libraryDirs.cmake")
include("./libconfig/library.cmake")

foreach(file IN LISTS mains)
    string(REGEX REPLACE "(.*)\\/([^\\/]+)\\/([^\\/]+)\\/([^\\/]+\\.cpp)$" "example_\\2_\\3" build_item ${file})
    message(${build_item})
    add_executable(${build_item} ${file} ${SRC} ${HDR} ${SDR})

    target_include_directories(
        ${build_item}
        PRIVATE
        "./include/"
        "./include/vk"
        ${TPINCDIR}
    )
    
    target_link_directories(
        ${build_item}
        PRIVATE
        ${TPLIBDIR}
    )
    
    target_link_libraries(
        ${build_item}
        PRIVATE
        ${TPLIBS}
    )
    
    set_target_properties(
        ${build_item}
        PROPERTIES
        RESOURCE "shaderLib/templateEnd.frag.glsl"
    )
endforeach()

file(COPY ${DLLS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
