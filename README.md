# opencv-with-vulkan

A digital image process lab with these silutions:
* glsl like CPU shader
* multi threads glsl lick CPU shader
* GPU shader on Vulkan (Soon)

# library config

Create these files:
* ./libconfig/includeDirs.txt
* ./libconfig/libraryDirs.txt
* ./libconfig/dllCopy.txt

## e.g.
./libconfig/includeDirs.txt
```
PRIVATE
C:/VulkanSDK/1.3.224.1/Include/
C:/OpenCV/opencv/build/include/
```

./libconfig/libraryDirs.txt
```
C:/VulkanSDK/1.3.224.1/Lib/
C:/OpenCV/opencv/build/x64/vc15/lib/
```

./libconfig/dllCopy.txt
```
C:/OpenCV/opencv/build/x64/vc15/bin/opencv_world460.dll
C:/OpenCV/opencv/build/x64/vc15/bin/opencv_world460d.dll
C:/OpenCV/opencv/build/x64/vc15/bin/opencv_videoio_ffmpeg460_64.dll
```
