cmake_minimum_required(VERSION 3.0.0)
project(ImageProcessing VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(LAB_PATH "./lab5/1/main.cpp") # 选择实验代码目录

include(CTest)
enable_testing()
set(CMAKE_BUILD_TYPE "Debug") # 加速编译

aux_source_directory("./src/" SRC)
aux_source_directory("./src/vk" VK_HELP_SRC)

add_executable(ImageProcessing ${LAB_PATH} ${SRC} ${VK_HELP_SRC})

target_include_directories(
    ImageProcessing
    PRIVATE
    "C:/OpenCV/opencv/build/include/"
    "C:/VulkanSDK/1.3.224.1/Include"
    "./include/"
    "./include/vk"
)

target_link_directories(
    ImageProcessing
    PRIVATE
    "C:/OpenCV/opencv/build/x64/vc15/lib/"
    "C:/VulkanSDK/1.3.224.1/Lib"
)

target_link_libraries(
    ImageProcessing
    PRIVATE
    opencv_world460d.lib
    vulkan-1.lib
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
