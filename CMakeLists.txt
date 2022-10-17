cmake_minimum_required(VERSION 3.0.0)
project(ImageProcessing VERSION 0.1.0)

set(LAB_PATH "./lab3/2/main.cpp") # 选择实验代码目录

include(CTest)
enable_testing()
set(CMAKE_BUILD_TYPE "Debug") # 加速编译

include_directories(
    "C:/OpenCV/opencv/build/include/"
    "./include/"
    "./include/vk"
    "C:/VulkanSDK/1.3.216.0/Include"
)

aux_source_directory(
    "./src/" SRC
)

aux_source_directory(
    "./src/vk" VK_HELP_SRC
)

link_directories(
    "C:/OpenCV/opencv/build/x64/vc15/lib/"
    "C:/VulkanSDK/1.3_validation/Lib"
)

link_libraries(
    opencv_world460d.lib
    vulkan-1.lib
)

add_executable(ImageProcessing ${LAB_PATH} ${SRC} ${VK_HELP_SRC})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
