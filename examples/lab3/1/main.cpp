#include <iostream>
#include "glm/glm.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "shader.h"
#include "opencv2/core.hpp"

#define VIDEO_PATH "../images/0.webm"

using namespace glm;

using namespace mltsg;

int main()
{
    Log("running...\n");
    cv::VideoCapture video(VIDEO_PATH);
    cv::Mat frame, surface;

    float avgFPS = 0;
    clock_t preTime = clock();
    while (true) {
        video >> frame;

        if (frame.size().width <= 0 || frame.size().height <= 0)
        {
            video.open(VIDEO_PATH);
            continue;
        }

        if (surface.empty() || surface.size() != frame.size())
        {
            surface.create(frame.size(), frame.type());
            continue;
        }
        
        clock_t now = clock();
        avgFPS = mix(avgFPS, 1.0f / (float(now - preTime) / CLOCKS_PER_SEC), 0.1f);
        preTime = now;

        multiProcess<MLTSG_U8, 32>(surface, [&](vec2 uv) {
            vec2 pos = uv * 2.0f - 1.0f;
            vec2 scalePos = pos * 0.1f;
            float len = length(pos);
            float x = clamp(len, 0.0f, 1.0f);
            vec2 smpUV = mix(scalePos, pos, 0.5f - 0.5f * cos(x * 3.1415926f)) * 0.5f + 0.5f;
            vec4 col = sample<MLTSG_U8>(frame, smpUV, SampleUV::Repeat, SamplePoint::Linear);
            return col;
        });
        
        cv::imshow("Input", frame);
        cv::imshow("Output", surface);

        int key = cv::pollKey();
        if (key == 27 || key == 'q')
        {
            break;
        }
    }
    
    Log("AVG FPS: %f\n", avgFPS);

    return 0;
}