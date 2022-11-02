#include <iostream>
#include "glm/common.hpp"
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "opencv2/core/mat.hpp"
#include "opencv2/core/types.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "shader.h"
#include "glm/glm.hpp"

using namespace mltsg;

int main()
{
    struct Tmp 
    {
        cv::Mat input;
        cv::Mat output;
        cv::Point2f moveable[4];
        cv::Point2f stick[4];
        bool mouseDown = false;
        int moveID = 0;
        int offsetX;
        int offsetY;
    } data;

    data.input = cv::imread("../images/bb.png");
    data.output.create(data.input.size(), CV_8UC3);

    data.stick[0] = { 0.0f, 0.0f };
    data.stick[1] = { 1.0f * data.input.cols, 0.0f };
    data.stick[2] = { 1.0f * data.input.cols, 1.0f * data.input.rows };
    data.stick[3] = { 0.0f, 1.0f * data.input.rows };

    data.moveable[0] = data.stick[0];
    data.moveable[1] = data.stick[1];
    data.moveable[2] = data.stick[2];
    data.moveable[3] = data.stick[3];

    cv::namedWindow("view");

    cv::setMouseCallback("view", [](int type, int x, int y, int flags, void* rawdata) {
        Tmp* data = reinterpret_cast<Tmp*>(rawdata);

        if (type == cv::EVENT_LBUTTONDOWN)
        {
            for (int i = 0; i < 4; ++i)
            {
                if (glm::distance(glm::vec2(x, y), glm::vec2(data->moveable[i].x, data->moveable[i].y)) < 10)
                {
                    data->moveID = i;
                    data->mouseDown = true;
                    data->offsetX = int(x - data->moveable[i].x);
                    data->offsetY = int(y - data->moveable[i].y);
                    break;
                }
            }
        }

        if (type == cv::EVENT_LBUTTONUP)
        {
            data->mouseDown = false;
        }

        if (data->mouseDown)
        {
            data->moveable[data->moveID].x = float(x - data->offsetX);
            data->moveable[data->moveID].y = float(y - data->offsetY);
        }

        static cv::Mat wrapTransfer{ 3, 3, CV_32FC1 };

        wrapTransfer = cv::getPerspectiveTransform(data->stick, data->moveable);
        cv::warpPerspective(data->input, data->output, wrapTransfer, data->input.size());

        multiProcess<MLTSG_U8, 16>(data->output, [&](glm::vec2 uv) {
            glm::vec2 uvp{ uv.x * data->output.cols, uv.y * data->output.rows };
            glm::vec3 fg = glm::vec4(1.0f);
            float alpha = 0.0f;
            for (int i = 0; i < 4; ++i)
            {
                if (glm::distance(uvp, glm::vec2(data->moveable[i].x, data->moveable[i].y)) < 10.0f)
                {
                    fg = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
                    alpha = 0.5f;
                }
            }
            return glm::vec4(glm::mix(_rgb(texelFetch<MLTSG_U8>(data->output, uv)), fg, alpha), 1.0f);
        });

        cv::imshow("view", data->output);

    }, &data);

    cv::waitKey();
    
    return 0;
}
