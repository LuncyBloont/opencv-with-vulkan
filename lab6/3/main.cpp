#include "glm/fwd.hpp"
#include "gpuMat.h"
#include "helper.h"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "shader.h"
#include "stage.h"
#include "vkenv.h"

int main()
{
    initializeVulkan();

    {

        cv::Mat voronoi = imreadRGB("../voronoi.png");
        GPUMat voronoiTex(&voronoi);
        voronoiTex.apply();

        cv::Mat scene = imreadRGB("../bb.png");
        GPUMat sceneTex(&scene);
        sceneTex.apply();

        cv::Mat black = imreadRGB("../black.bmp");
        GPUMat blackTex(&black);
        blackTex.apply();

        StageProperties assets {
            {}, { &voronoiTex, &sceneTex, &blackTex },
            {}, {},
            "../shaders/ghostHead/mainImage.spv"
        };

        Stage frame(800, 600, &assets);

        uint32_t age = 1;

        while (true) {
            frame.render(age);
            frame.show("Output");

            if (cv::waitKey(1) == 'q')
            {
                break;
            }

            age += 1;
        }

    }

    cleanupVulkan();
    return 0;
}