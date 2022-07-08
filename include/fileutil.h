#ifndef OPENCVAPP_CMAKE_UTIL_H
#define OPENCVAPP_CMAKE_UTIL_H

#include <iostream>
#include <opencv2/opencv.hpp>

class FileUtil {
private:
    static inline std::string DEFAULT_PATH_ASSETS = "assets/pics/*";
public:
    static std::string getFileNameWithFullPath();
    static std::vector<std::string> getAllFilesInDirWithFullPath();
    static void resizeImg(cv::Mat& src, cv::Mat& dst, int maxSize, bool interpolate);
};

#endif //OPENCVAPP_CMAKE_UTIL_H
