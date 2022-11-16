# opencv-with-vulkan

A digital image process lab with these silutions:
* glsl like CPU shader
* multi threads glsl lick CPU shader
* GPU shader on Vulkan (Soon)

# library config

Create these files:
* ./libconfig/includeDirs.cmake
* ./libconfig/libraryDirs.cmake
* ./libconfig/library.cmake

## e.g.
./libconfig/includeDirs.cmake
```
set(
    TPINCDIR
    "C:/VulkanSDK/1.3.224.1/Include/"
    "C:/OpenCV/opencv/build/include/"
)
```

./libconfig/libraryDirs.cmake
```
set(
    TPLIBDIR
    "C:/VulkanSDK/1.3.224.1/Lib/"
    "C:/OpenCV/opencv/build/x64/vc15/lib/"
)

set(
    DLLS
    "C:/OpenCV/opencv/build/x64/vc15/bin/opencv_world460.dll"
    "C:/OpenCV/opencv/build/x64/vc15/bin/opencv_world460d.dll"
)
```

./libconfig/library.cmake
```
if(DEBUG)
    set(
        TPLIBS
        opencv_world460d.lib
        vulkan-1.lib
    )
else()
    set(
        TPLIBS
        opencv_world460.lib
        vulkan-1.lib
    )
endif()
```

