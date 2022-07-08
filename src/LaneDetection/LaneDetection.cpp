//
// Created by citadin on 10.04.2022.
//

#include "LaneDetection.h"

class LaneDetection {

private:
    const int KERNEL_SIZE = 3;
    const int LOW_THRESHOLD = 100;
    const int RATIO = 3;

    cv::Mat workingImage;
    int inputImageWidth;
    int inputImageHeight;

    std::vector<cv::Vec4i> linesP;
    const int RHO = 2; // distance resolution in pixels of the Hough grid
    const int THETA = CV_PI / 180; // angular resolution in radians of the Hough grid
    const int THRESHOLD = 15; // minimum number of votes (intersections in Hough grid cell)
    const int MIN_LINE_LENGTH = 40;// minimum number of pixels making up a line
    const int MAX_LINE_GAP_SEGMENTS = 30; // maximum gap in pixels between connectable line segments

public:

    LaneDetection setImage(const cv::Mat &image) {
        this->inputImageWidth = image.cols;
        this->inputImageHeight = image.rows;
        cv::cvtColor(image, this->workingImage, cv::COLOR_BGR2GRAY);

        return *this;
    }

    LaneDetection applyGaussianBlur() {
        cv::GaussianBlur(this->workingImage,
                         this->workingImage,
                         cv::Size(KERNEL_SIZE, KERNEL_SIZE),
                         0);

        return *this;
    }

    LaneDetection applyCannyEdgeDetection() {
        cv::Canny(this->workingImage,
                  this->workingImage,
                  LOW_THRESHOLD,
                  LOW_THRESHOLD * RATIO,
                  KERNEL_SIZE);

        return *this;
    }

    LaneDetection applyHoughLineTransformation() {
        cv::HoughLinesP(this->workingImage,
                        this->linesP,
                        RHO,
                        THETA,
                        THRESHOLD,
                        MIN_LINE_LENGTH,
                        MAX_LINE_GAP_SEGMENTS);


        return *this;
    }

    LaneDetection printOutputLines() {

        for (auto currentLine: this->linesP) {

        }

        return *this;
    }

    LaneDetection displayImage() {

        cv::imshow("current image", this->workingImage);
        cv::waitKey();

        return *this;
    }
};
