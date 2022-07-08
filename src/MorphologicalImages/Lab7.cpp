//
// Created by citadin on 28.03.2022.
//

#include "Lab7.h"

#include <utility>

namespace Lab7Work {

    class Lab7 {

    public:

        Lab7() {
            inputImage = imread(FileUtil::getFileNameWithFullPath(), cv::IMREAD_GRAYSCALE);
            myStructElem = generateStructuringElement(5);
        }

        void runDemoDilation() {
            cv::Mat_ outputMatrix = dilation(inputImage, myStructElem);
            imshow("Input inputImage", inputImage);
            imshow("Dilation", outputMatrix);
            cv::waitKey(0);
        }

        void runDemoErosion() {
            cv::Mat_ outputMatrix = erosion(inputImage, myStructElem);
            imshow("Input inputImage", inputImage);
            imshow("Erosion", outputMatrix);
            cv::waitKey(0);
        }

        void runDemoOpening() {
            cv::Mat_ outputMatrix = opening(inputImage, myStructElem);
            imshow("Input inputImage", inputImage);
            imshow("Opening", outputMatrix);
            cv::waitKey(0);
        }

        void runDemoClosing() {
            cv::Mat_ outputMatrix = closing(inputImage, myStructElem);
            imshow("Input inputImage", inputImage);
            imshow("Opening", outputMatrix);
            cv::waitKey(0);
        }

        void runDemoBoundaryExtraction() {
            cv::Mat_ outputMatrix = boundaryExtraction(inputImage, myStructElem);
            imshow("Input inputImage", inputImage);
            imshow("Boundary", outputMatrix);
            cv::waitKey(0);
        }

        void runDemoRegionFilling() {
            cv::Mat_ outputMatrix = regionFilling(inputImage, myStructElem);
            imshow("Input inputImage", inputImage);
            imshow("Region Filling", outputMatrix);
            cv::waitKey(0);
        }

    private:

        cv::Mat_<uchar> inputImage;
        cv::Mat_<uchar> myStructElem;

        static cv::Mat_<uchar> dilation(cv::Mat_<uchar> inputMatrix, cv::Mat_<uchar> structuringElement) {

            int height = inputMatrix.rows;
            int width = inputMatrix.cols;

            cv::Mat_<uchar> outputMatrix(height, width);

            int structuringElementMidY = structuringElement.rows / 2;
            int structuringElementMidX = structuringElement.cols / 2;

            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++)
                    if (inputMatrix(i, j) == 0) {

                        outputMatrix(i, j) = 0;

                        for (int k = 0; k < structuringElement.rows; k++)
                            for (int l = 0; l < structuringElement.cols; l++)
                                if (structuringElement(k, l) == 0) {

                                    int y = i + k - structuringElementMidY;
                                    int x = j + l - structuringElementMidX;

                                    if (coordinateInsideImage(inputMatrix, y, x))
                                        outputMatrix(y, x) = 0;
                                }
                    } else
                        outputMatrix(i, j) = 255;

            return outputMatrix;
        }

        static cv::Mat_<uchar> erosion(cv::Mat_<uchar> src, cv::Mat_<uchar> structuringElement) {

            int height = src.rows;
            int width = src.cols;
            cv::Mat_<uchar> dst = src.clone();

            int structuringElementMidY = structuringElement.rows / 2;
            int structuringElementMidX = structuringElement.cols / 2;

            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++)
                    if (src(i, j) == 0)
                        for (int a = 0; a < structuringElement.rows; a++)
                            for (int b = 0; b < structuringElement.cols; b++)
                                if (structuringElement(a, b) == 0) {

                                    int y = i + a - structuringElementMidY;
                                    int x = j + b - structuringElementMidX;

                                    if (coordinateInsideImage(src, y, x))
                                        if (src(y, x) == 255)
                                            dst(i, j) = 255;
                                }
            return dst;
        }

        static cv::Mat_<uchar> opening(const cv::Mat_<uchar> &src, const cv::Mat_<uchar> &elem) {

            int height = src.rows;
            int width = src.cols;

            cv::Mat_<uchar> dst(height, width);

            dst = dilation(erosion(src, elem), elem);

            return dst;
        }

        static cv::Mat_<uchar> closing(const cv::Mat_<uchar> &src, const cv::Mat_<uchar> &elem) {

            int height = src.rows;
            int width = src.cols;

            cv::Mat_<uchar> dst(height, width);

            dst = erosion(dilation(src, elem), elem);

            return dst;
        }

        static cv::Mat_<uchar> boundaryExtraction(cv::Mat_<uchar> inputImage, cv::Mat_<uchar> elem) {

            int height = inputImage.rows;
            int width = inputImage.cols;

            cv::Mat_<uchar> outputImage = inputImage.clone();

            cv::Mat_<uchar> erodedImage = erosion(inputImage, std::move(elem));

            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++)
                    if (inputImage(i, j) == erodedImage(i, j))
                        outputImage(i, j) = 255;
                    else
                        outputImage(i, j) = 0;

            return outputImage;
        }

        static cv::Mat_<uchar> regionFilling(cv::Mat_<uchar> inputImage, const cv::Mat_<uchar> &structElem) {

            bool stop = false;
            std::pair<int, int> point;

            for (int i = 0; i < inputImage.rows; i++) {

                int flag = 0;

                for (int j = 0; j < inputImage.cols; j++) {

                    if (flag == 0 && inputImage(i, j) == 0)
                        flag = 1;

                    if (flag == 1 && inputImage(i, j) == 255) {
                        point = {i, j};
                        flag = 2;
                    }

                    if (flag == 2 && inputImage(i, j) == 0)
                        flag = 3;

                    if (flag == 3 && inputImage(i, j) == 255) {
                        stop = true;
                        break;
                    }
                }
                if (stop)
                    break;
            }

            cv::Mat_<uchar> inverse(inputImage.rows, inputImage.cols);
            for (int i = 0; i < inputImage.rows; i++)
                for (int j = 0; j < inputImage.cols; j++)
                    if (inputImage(i, j) == 0)
                        inverse(i, j) = 255;
                    else
                        inverse(i, j) = 0;

            cv::Mat_<uchar> outputMatrix(inputImage.rows, inputImage.cols, 255);
            outputMatrix(point.first, point.second) = 0;

            cv::Mat_<uchar> mat(inputImage.rows, inputImage.cols, 255);

            while (true) {

                cv::Mat_<uchar> dilationMatrix = dilation(outputMatrix, structElem);

                for (int i = 0; i < inputImage.rows; i++)
                    for (int j = 0; j < inputImage.cols; j++)
                        if (dilationMatrix(i, j) == 0 && inverse(i, j) == 0)
                            mat(i, j) = 0;
                        else
                            mat(i, j) = 255;

                if (matricesAreDistinct(outputMatrix, mat)) {
                    break;
                }
                outputMatrix = mat.clone();
            }
            return outputMatrix;
        }

        static bool coordinateInsideImage(const cv::Mat &img, int y, int x) {

            int height = img.rows;
            int width = img.cols;

            return (y >= 0 && y < height) && (x >= 0 && x < width);
        }

        static bool matricesAreDistinct(cv::Mat_<uchar> firstMatrix, cv::Mat_<uchar> secondMatrix) {

            for (int i = 0; i < firstMatrix.rows; i++)
                for (int j = 0; j < firstMatrix.cols; j++)
                    if (firstMatrix(i, j) != secondMatrix(i, j))
                        return true;

            return false;
        }

        static cv::Mat_<uchar> generateStructuringElement(int matSize) {

            cv::Mat_<uchar> structuringElement(matSize, matSize, 255);

            int mid = matSize / 2;

            for (int i = 0; i < matSize; i++) {
                structuringElement(i, mid) = 0;
                structuringElement(mid, i) = 0;
            }

            return structuringElement;
        }
    };
}
