module;

#ifdef FATX_WITH_OPENCV
#include "FatOcv.hxx"
#endif

export module FatX.OpenCV.Contour;

#ifdef FATX_WITH_OPENCV

import std;

export namespace fatx::opencv
{
    auto FindLargestContour(const std::vector<std::vector<cv::Point>>& contours, const double& maxArea) -> std::ptrdiff_t
    {
        std::ptrdiff_t largestIdx{ -1 };

        {
            double currentMaxArea{};

            for (std::size_t i{}; i < contours.size(); ++i)
            {
                if (const auto& area = cv::contourArea(contours[i]); area > maxArea and area > currentMaxArea)
                {
                    currentMaxArea = area;
                    largestIdx     = static_cast<decltype(largestIdx)>(i);
                }
            }
        }

        return largestIdx;
    }
}

#endif

// module : private;
