#include <filesystem>
#include <numeric>
#include <vector>
#include "fileutil.h"
#include "portable-file-dialogs.h"

std::string FileUtil::getFileNameWithFullPath() {
    const std::vector<std::string> selectedFile = pfd::open_file("Select a file", DEFAULT_PATH_ASSETS).result();
    if (!selectedFile.empty()) {
        return std::accumulate(selectedFile.begin(), selectedFile.end(), std::string{});
    }
    return "";
}

std::vector<std::string> FileUtil::getAllFilesInDirWithFullPath() {
    std::vector<std::string> listOfFiles;
    const std::string folderPath = pfd::select_folder("Select a folder", DEFAULT_PATH_ASSETS).result();
    for (const auto &file: std::filesystem::directory_iterator(folderPath)) {
        listOfFiles.push_back(file.path());
    }
    return listOfFiles;
}

void FileUtil::resizeImg(cv::Mat &src, cv::Mat &dst, int maxSize, bool interpolate) {
    double ratio = 1;
    double w = src.cols;
    double h = src.rows;
    if (w > h)
        ratio = w / (double) maxSize;
    else
        ratio = h / (double) maxSize;
    int nw = (int) (w / ratio);
    int nh = (int) (h / ratio);
    cv::Size sz(nw, nh);
    if (interpolate)
        resize(src, dst, sz);
    else
        resize(src, dst, sz, 0, 0, cv::INTER_NEAREST);
}