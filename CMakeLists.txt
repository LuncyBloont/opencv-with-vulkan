cmake_minimum_required(VERSION 3.0.0)
project(ImageProcessing VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Release)

file(GLOB_RECURSE SRC "./src/**.cpp")
file(GLOB_RECURSE HDR "./include/**.hpp" "./include/**.h")
file(GLOB_RECURSE SDR "./shaderLib/**.glsl" "./shaders/**.frag" "./shaders/**.vert" "./defaultVS/**.vert")

file(GLOB_RECURSE mains ./examples/*/*/main.cpp)

file(STRINGS "./libconfig/includeDirs.txt" USER_INCLUDE_DIR)
file(STRINGS "./libconfig/libraryDirs.txt" USER_LIB_DIR)
file(STRINGS "./libconfig/dllCopy.txt" USER_DLL)

message(${USER_LIB_DIR})

link_directories(
    ${USER_LIB_DIR}
)

foreach(file IN LISTS mains)
    string(REGEX REPLACE "(.*)\\/([^\\/]+)\\/([^\\/]+)\\/([^\\/]+\\.cpp)$" "example_\\2_\\3" build_item ${file})
    message(${build_item})
    add_executable(${build_item} ${file} ${SRC} ${HDR})

    target_include_directories(
        ${build_item}
        ${USER_INCLUDE_DIR}
        PRIVATE
        "./include/"
        "./include/vk"
    )
    
    target_link_libraries(
        ${build_item}
        PRIVATE
        optimized opencv_world460
        debug opencv_world460d
        general vulkan-1
    )
endforeach()

file(COPY ${USER_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
