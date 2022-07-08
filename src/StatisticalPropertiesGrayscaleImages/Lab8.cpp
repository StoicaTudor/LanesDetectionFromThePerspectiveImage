//
// Created by citadin on 04.04.2022.
//

#include "Lab8.h"

namespace Lab8Work {
    class Lab8 {

    private:
        // Calc histogram
        static int *getHistogram(cv::Mat_<uchar> image) {

            int *histogram = new int(256);

            // init histogram
            for (int i = 0; i < 256; i++)
                histogram[i] = 0;

            for (int i = 0; i < image.rows; i++)
                for (int j = 0; j < image.cols; j++)
                    histogram[image(i, j)]++;

            return histogram;
        }

        static void showHistogram(const int *histogram, int height, int nrBins) {

            cv::Mat histogramImage(height, nrBins, CV_8UC3, CV_RGB(255, 255, 255));

            int histogramMax = 0;

            for (int i = 0; i < nrBins; i++)
                if (histogram[i] > histogramMax)
                    histogramMax = histogram[i];

            double scale;
            scale = (double) height / histogramMax;
            int baseline = height - 1;

            for (int i = 0; i < nrBins; i++)
                for (int j = baseline; j > baseline - histogram[i] * scale; --j)
                    histogramImage.at<cv::Vec3b>(j, i) = {0, 255, 0};

            imshow("Histogram", histogramImage);
            cv::waitKey(0);
        }

        static float meanValue(const cv::Mat_<uchar> &image, const int histogram[256]) {

            int totalNrPixels = image.rows * image.cols;
            float weight = 0;

            for (int i = 0; i < 256; i++)
                weight += (float) i * (float) histogram[i];

            return (float) weight / (float) totalNrPixels;
        }

        static float standardDeviation(const cv::Mat_<uchar> &image, float meanValue, const int histogram[256]) {

            float weight = 0;
            int height = image.rows;
            int width = image.cols;
            int totalNrPixels = height * width;

            for (int i = 0; i < 256; i++)
                weight += (float) ((float) i - meanValue) * ((float) i - meanValue) * (float) histogram[i];

            return sqrt((float) weight / (float) totalNrPixels);
        }


        static cv::Mat_<uchar> adjustImageToThreshold(cv::Mat_<uchar> inputImage, int threshold) {

            int height = inputImage.rows;
            int width = inputImage.cols;

            cv::Mat_<uchar> resultingImage(height, width);

            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (inputImage(i, j) >= threshold)
                        resultingImage(i, j) = 255;
                    else if (inputImage(i, j) < threshold)
                        resultingImage(i, j) = 0;
                }
            }

            imshow("Initial Image", inputImage);
            imshow("Black&White Image", resultingImage);
            cv::waitKey(0);

            return resultingImage;
        }

        static void globalThresholding(const cv::Mat_<uchar> &inputImage, const int histogram[256]) {

            int height = inputImage.rows;
            int width = inputImage.cols;

            int minIntensity = 256;
            int maxIntensity = -1;

            cv::Mat_<uchar> resultingImage(height, width);

            for (int i = 0; i < 256; i++) {
                if (histogram[i] != 0 && i < minIntensity) {
                    minIntensity = i;
                }
                if (histogram[i] != 0 && i > maxIntensity) {
                    maxIntensity = i;
                }
            }

            float referenceThresholdValue = (float) (minIntensity + maxIntensity) / 2;
            float previousReferenceValue;

            do {
                float meanG1 = 0;
                float meanG2 = 0;

                float N1 = 0;
                float N2 = 0;

                for (int i = minIntensity; i <= (int) referenceThresholdValue; i++) {
                    meanG1 += (float) i * (float) histogram[i];
                    N1 += (float) histogram[i];
                }

                meanG1 = meanG1 / N1;

                for (int i = (int) referenceThresholdValue + 1; i <= maxIntensity; i++) {
                    meanG2 += (float) i * (float) histogram[i];
                    N2 += (float) histogram[i];
                }
                meanG2 = meanG2 / N2;

                previousReferenceValue = referenceThresholdValue;
                referenceThresholdValue = (float) (meanG1 + meanG2) / 2;

            } while (abs(referenceThresholdValue - previousReferenceValue) > 0);

            resultingImage = adjustImageToThreshold(inputImage, (int) referenceThresholdValue);

            imshow("Initial Image", inputImage);
            imshow("Resulting inputImage", resultingImage);
            cv::waitKey(0);
        }

        static void stretchingShrinking(cv::Mat_<uchar> initialImage, int gOutMin, int gOutMax) {

            int height = initialImage.rows;
            int width = initialImage.cols;

            cv::Mat_<uchar> resultingImage(height, width);

            int gInMax = -1;
            int gInMin = 256;

            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++) {

                    if (initialImage(i, j) > gInMax)
                        gInMax = initialImage(i, j);

                    if (initialImage(i, j) < gInMin)
                        gInMin = initialImage(i, j);
                }

            float report = (float) (gOutMax - gOutMin) / (float) (gInMax - gInMin);

            for (int i = 0; i < height; i++)
                for (int j = 0; j < width; j++) {

                    int gIn = initialImage(i, j);
                    int gOut = gOutMin + (gIn - gInMin) * (int) report;

                    if (gOut <= 0)
                        resultingImage(i, j) = 0;
                    else if (gOut >= 255)
                        resultingImage(i, j) = 255;
                    else
                        resultingImage(i, j) = gOut;
                }

            imshow("Initial initialImage", initialImage);
            imshow("stretchingShrinking", resultingImage);
            cv::waitKey(0);
        }

        /*
         * gama < 1 => compression
         * gama > 1 => decompression
         */
        static void gammaCorrection(cv::Mat_<uchar> image, float gamma) {

            int height = image.rows;
            int width = image.cols;
            cv::Mat_<uchar> resultingImage(height, width);

            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {

                    float value = 255 * (pow(((float) image(i, j) / 255), gamma));

                    if (value >= 255)
                        resultingImage(i, j) = 255;
                    else if (value <= 0)
                        resultingImage(i, j) = 0;
                    else resultingImage(i, j) = value;
                }
            }

            imshow("Initial", image);
            imshow("Compression", resultingImage);
            cv::waitKey(0);
        }

    public:
        static void demo() {
            cv::Mat_<uchar> img = imread("/home/citadin/Documents/Facultate/A3S2/IP/Lab/Lab8/PI-L8/balloons.bmp",
                                         cv::IMREAD_GRAYSCALE);

            int *histogram = getHistogram(img);
            showHistogram(histogram, 256, 256);

            float mean = meanValue(img, histogram);

            std::cout << "Mean value: " << mean << std::endl;
            std::cout << "Standard deviation: " << standardDeviation(img, mean, histogram) << std::endl;

            globalThresholding(img, histogram);
            stretchingShrinking(img, 10, 150);
            cv::Mat_<uchar> inputImage = imread(
                    "/home/citadin/Documents/Facultate/A3S2/IP/Lab/Lab8/PI-L8/wilderness.bmp", cv::IMREAD_GRAYSCALE);
            gammaCorrection(inputImage, 0.2);
            gammaCorrection(inputImage, 1.5);
        }
    };
}
