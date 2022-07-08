//#include "main.h"
//#include "MorphologicalImages/Lab7.h"
//#include "MorphologicalImages/Lab7.cpp"
//#include "StatisticalPropertiesGrayscaleImages/Lab8.h"
//#include "StatisticalPropertiesGrayscaleImages/Lab8.cpp"
//#include <fstream>
//
//using namespace std;
//using namespace cv;
//
//namespace lab {
//
//    void testOpenImage() {
//        const string fileName = FileUtil::getFileNameWithFullPath();
//        const Mat src = imread(fileName);
//        if (!src.empty()) {
//            imshow("inputImage", src);
//        }
//        waitKey();
//    }
//
//    void testOpenImagesFld() {
//        vector<string> files = FileUtil::getAllFilesInDirWithFullPath();
//        for_each(files.begin(), files.end(), [&](const auto &item) {
//            const Mat src = imread(item);
//            if (!src.empty()) {
//                imshow(item, src);
//            }
//        });
//        waitKey();
//    }
//
//    void testParcurgereSimplaDiblookStyle() {
//        const string fname = FileUtil::getFileNameWithFullPath();
//        const Mat src = imread(fname, IMREAD_GRAYSCALE);
//
//        if (src.empty()) {
//            cout << "File not selected, returning to main menu" << endl;
//            return;
//        }
//
//        const int height = src.rows;
//        const int width = src.cols;
//        Mat dst = src.clone();
//
//        auto t = (double) getTickCount(); // Get the current time [s]
//
//        // the fastest approach using the "diblook style"
//        const uchar *lpSrc = src.data;
//        uchar *lpDst = dst.data;
//        int w = (int) src.step; // no dword alignment is done !!!
//        for (int i = 0; i < height; i++)
//            for (int j = 0; j < width; j++) {
//                const uchar val = lpSrc[i * w + j];
//                lpDst[i * w + j] = 255 - val;
//            }
//
//        // Get the current time again and compute the time difference [s]
//        t = ((double) getTickCount() - t) / getTickFrequency();
//        // Print (in the console window) the processing time in [ms]
//        printf("Time = %.3f [ms]\n", t * 1000);
//
//        imshow("input inputImage", src);
//        imshow("negative inputImage", dst);
//        waitKey();
//    }
//
//    void testColor2Gray() {
//        const string fname = FileUtil::getFileNameWithFullPath();
//        Mat src = imread(fname);
//
//        if (src.empty()) {
//            cout << "File not selected, returning to main menu" << endl;
//            return;
//        }
//
//        int height = src.rows;
//        int width = src.cols;
//
//        Mat dst = Mat(height, width, CV_8UC1);
//
//        // Asa se acceseaaza pixelii individuali pt. o imagine RGB 24 biti/pixel
//        // Varianta ineficienta (lenta)
//        for (int i = 0; i < height; i++) {
//            for (int j = 0; j < width; j++) {
//                Vec3b v3 = src.at<Vec3b>(i, j);
//                uchar b = v3[0];
//                uchar g = v3[1];
//                uchar r = v3[2];
//                dst.at<uchar>(i, j) = (r + g + b) / 3;
//            }
//        }
//
//        imshow("input inputImage", src);
//        imshow("gray inputImage", dst);
//        waitKey();
//
//    }
//
//    void testBGR2HSV() {
//
//        const string fname = FileUtil::getFileNameWithFullPath();
//        const Mat src = imread(fname);
//
//        if (src.empty()) {
//            cout << "File not selected, returning to main menu" << endl;
//            return;
//        }
//
//        const int height = src.rows;
//        const int width = src.cols;
//
//        // Componentele d eculoare ale modelului HSV
//        Mat H = Mat(height, width, CV_8UC1);
//        Mat S = Mat(height, width, CV_8UC1);
//        Mat V = Mat(height, width, CV_8UC1);
//
//        // definire pointeri la matricele (8 biti/pixeli) folosite la afisarea componentelor individuale H,S,V
//        uchar *lpH = H.data;
//        uchar *lpS = S.data;
//        uchar *lpV = V.data;
//
//        Mat hsvImg;
//        cvtColor(src, hsvImg, COLOR_BGR2HSV);
//
//        // definire pointer la matricea (24 biti/pixeli) a imaginii HSV
//        uchar *hsvDataPtr = hsvImg.data;
//
//        for (int i = 0; i < height; i++) {
//            for (int j = 0; j < width; j++) {
//                int hi = i * width * 3 + j * 3;
//                int gi = i * width + j;
//
//                lpH[gi] = hsvDataPtr[hi] * 510 / 360;        // lpH = 0 .. 255
//                lpS[gi] = hsvDataPtr[hi + 1];            // lpS = 0 .. 255
//                lpV[gi] = hsvDataPtr[hi + 2];            // lpV = 0 .. 255
//            }
//        }
//
//        imshow("input inputImage", src);
//        imshow("H", H);
//        imshow("S", S);
//        imshow("V", V);
//
//        waitKey();
//
//    }
//
//    void testResize() {
//
//        const string fname = FileUtil::getFileNameWithFullPath();
//        const Mat src = imread(fname);
//
//        if (src.empty()) {
//            cout << "File not selected, returning to main menu" << endl;
//            return;
//        }
//
//        Mat dst1, dst2;
//        //without interpolation
//        FileUtil::resizeImg(const_cast<Mat &>(src), dst1, 320, false);
//        //with interpolation
//        FileUtil::resizeImg(const_cast<Mat &>(src), dst2, 320, true);
//        imshow("input inputImage", src);
//        imshow("resized inputImage (without interpolation)", dst1);
//        imshow("resized inputImage (with interpolation)", dst2);
//        waitKey();
//
//    }
//
//    void testCanny() {
//
//        const string fname = FileUtil::getFileNameWithFullPath();
//        Mat src, dst, gauss;
//        src = imread(fname, IMREAD_GRAYSCALE);
//
//        if (src.empty()) {
//            cout << "File not selected, returning to main menu" << endl;
//            return;
//        }
//
//        double k = 0.4;
//        int pH = 50;
//        int pL = (int) k * pH;
//        GaussianBlur(src, gauss, Size(5, 5), 0.8, 0.8);
//        Canny(gauss, dst, pL, pH, 3);
//        imshow("input inputImage", src);
//        imshow("canny", dst);
//        waitKey();
//
//    }
//
//    void testVideoSequence() {
//        const string videoPath = "assets/vids/lab/rubic.avi";
//        VideoCapture cap(videoPath); // off-line video from file
//        //VideoCapture cap(0);	// live video from web cam
//        if (!cap.isOpened()) {
//            printf("Cannot open video capture device.\n");
//            waitKey(0);
//            return;
//        }
//
//        Mat edges;
//        Mat frame;
//        int c;
//
//        while (cap.read(frame)) {
//            Mat grayFrame;
//            cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
//            Canny(grayFrame, edges, 40, 100, 3);
//            imshow("source", frame);
//            imshow("gray", grayFrame);
//            imshow("edges", edges);
//            c = waitKey(0);  // waits a key press to advance to the next frame
//            if (c == 27) {
//                // press ESC to exit
//                printf("ESC pressed - capture finished\n");
//                break;  //ESC pressed
//            }
//        }
//    }
//
//    void testSnap() {
//        VideoCapture cap(0); // open the deafult camera (i.e. the built in web cam)
//        if (!cap.isOpened()) // openenig the video device failed
//        {
//            printf("Cannot open video capture device.\n");
//            return;
//        }
//
//        Mat frame;
//        char numberStr[256];
//        char fileName[256];
//
//        // video resolution
//        Size capS = Size((int) cap.get(CAP_PROP_FRAME_WIDTH),
//                         (int) cap.get(CAP_PROP_FRAME_HEIGHT));
//
//        // Display window
//        const char *WIN_SRC = "Src"; //window for the source frame
//        namedWindow(WIN_SRC, WINDOW_AUTOSIZE);
//        moveWindow(WIN_SRC, 0, 0);
//
//        const char *WIN_DST = "Snapped"; //window for showing the snapped frame
//        namedWindow(WIN_DST, WINDOW_AUTOSIZE);
//        moveWindow(WIN_DST, capS.width + 10, 0);
//
//        int c;
//        int frameNum = -1;
//        int frameCount = 0;
//
//        for (;;) {
//            cap >> frame; // get a new frame from camera
//            if (frame.empty()) {
//                printf("End of the video file\n");
//                break;
//            }
//
//            ++frameNum;
//
//            imshow(WIN_SRC, frame);
//
//            c = waitKey(10);  // waits a key press to advance to the next frame
//            if (c == 27) {
//                // press ESC to exit
//                printf("ESC pressed - capture finished");
//                break;  //ESC pressed
//            }
//            if (c == 115) { //'s' pressed - snapp the inputImage to a file
//                frameCount++;
//                fileName[0] = '\0';
//                sprintf(numberStr, "%d", frameCount);
//                strcat(fileName, "Images/A");
//                strcat(fileName, numberStr);
//                strcat(fileName, ".bmp");
//                bool bSuccess = imwrite(fileName, frame);
//                if (!bSuccess) {
//                    printf("Error writing the snapped inputImage\n");
//                } else
//                    imshow(WIN_DST, frame);
//            }
//        }
//
//    }
//
//    void MyCallBackFunc(int event, int x, int y, int flags, void *param) {
//        //More examples: http://opencvexamples.blogspot.com/2014/01/detect-mouse-clicks-and-moves-on-image.html
//        Mat *src = (Mat *) param;
//        if (event == EVENT_LBUTTONDOWN) {
//            printf("Pos(x,y): %d,%d  Color(RGB): %d,%d,%d\n",
//                   x, y,
//                   (int) (*src).at<Vec3b>(y, x)[2],
//                   (int) (*src).at<Vec3b>(y, x)[1],
//                   (int) (*src).at<Vec3b>(y, x)[0]);
//        }
//    }
//
//    void testMouseClick() {
//        const string fname = FileUtil::getFileNameWithFullPath();
//        const Mat src = imread(fname);
//
//        if (src.empty()) {
//            cout << "File not selected, returning to main menu" << endl;
//            return;
//        }
//
//        //Create a window
//        namedWindow("My Window", 1);
//
//        //set the callback function for any mouse event
//        setMouseCallback("My Window", MyCallBackFunc, (void *) &src);
//
//        //show the inputImage
//        imshow("My Window", src);
//
//        // Wait until user press some key
//        waitKey(0);
//
//    }
//
//    void printChainCodeAndDerivative(const vector<int> &chainCode);
//
//    void borderTracing() {
//
//        // read the inputImage
//        Mat_<uchar> src = imread(FileUtil::getFileNameWithFullPath(), IMREAD_GRAYSCALE);
//
//        // display the original inputImage
//        imshow("OriginalImage", src);
//
//        bool foundBlackPixel = false;
//
//        int inputImageHeight = src.rows;
//        int inputImageWidth = src.cols;
//
//        int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
//        int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
//
//        Point2i borderPoints[99999];
//
//        Point2i point;
//        int borderPointsCounter = 0;
//
//        for (int i = 0; i < inputImageHeight; i++) {
//
//            for (int j = 0; j < inputImageWidth; j++) {
//
//                if (src(i, j) == 0) {
//
//                    point = Point2i(j, i);
//                    borderPoints[borderPointsCounter++] = point;
//                    foundBlackPixel = true;
//                    break;
//                }
//            }
//
//            if (foundBlackPixel) {
//                break;
//            }
//        }
//
//        vector<int> chainCode;
//
//        int direction = 7;
//
//        while (borderPoints[0] != borderPoints[borderPointsCounter - 2] ||
//               borderPoints[1] != borderPoints[borderPointsCounter - 1] ||
//               (borderPointsCounter <= 2)) {
//
//            if (direction % 2 == 0) {
//                direction = (direction + 7) % 8;
//            } else {
//                direction = (direction + 6) % 8;
//            }
//
//            for (int i = direction; i < direction + 8; i++) {
//
//                int neighbourY = point.y + dx[i % 8];
//                int neighbourX = point.x + dy[i % 8];
//                uchar neighbor = src(neighbourY, neighbourX);
//
//                if (neighbor == 0) {
//
//                    borderPoints[borderPointsCounter++] = Point2i(neighbourX, neighbourY);
//                    point = Point2i(neighbourX, neighbourY);
//                    chainCode.push_back(direction);
//                    direction = i % 8;
//                    break;
//                }
//            }
//        }
//
//        Mat_<uchar> dst(inputImageHeight, inputImageWidth);
//
//        // init inputImage in black
//        for (int i = 0; i < inputImageHeight; i++) {
//            for (int j = 0; j < inputImageWidth; j++) {
//                dst(i, j) = 0;
//            }
//        }
//
//        // all border points shall be white
//        for (int i = 0; i < borderPointsCounter; i++) {
//            dst(borderPoints[i].y, borderPoints[i].x) = 255;
//        }
//
//        imshow("BorderedImage", dst);
//        waitKey();
//        printChainCodeAndDerivative(chainCode);
//    }
//
//    void printChainCodeAndDerivative(const vector<int> &chainCode) {
//
//        int chainCodeSize = chainCode.size();
//
//        cout << "Chain code" << endl;
//        for (int i = 0; i < chainCodeSize; i++) {
//            cout << chainCode[i] << " ";
//        }
//
//        cout << endl << "Derivative chain code" << endl;
//        for (int i = 1; i < chainCodeSize; i++) {
//            cout << (chainCode[i] - chainCode[i - 1] + 8) % 8 << " ";
//        }
//    }
//
//    void chainCodeToText() {
//
//        int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
//        int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
//
//        int inputImageHeight = 1000;
//        int inputImageWidth = 1000;
//        Mat_<uchar> dst(inputImageHeight, inputImageWidth);
//
//        // init inputImage in black
//        for (int i = 0; i < inputImageHeight; i++) {
//            for (int j = 0; j < inputImageWidth; j++) {
//                dst(i, j) = 0;
//            }
//        }
//
//        ifstream file;
//        file.open(FileUtil::getFileNameWithFullPath());
//
//        int startRow, startColumn;
//        file >> startRow;
//        file >> startColumn;
//
//        int chainCodeSize;
//        file >> chainCodeSize;
//
//        vector<int> chainCode;
//        int currentChainCode;
//
//        int currentRow = startRow;
//        int currentColumn = startColumn;
//
//        dst(currentRow, currentColumn) = 255;
//
//        for (int i = 0; i < chainCodeSize; i++) {
//
//            file >> currentChainCode;
//            chainCode.push_back(currentChainCode);
//
//            currentRow = currentRow + dx[currentChainCode];
//            currentColumn = currentColumn + dy[currentChainCode];
//            dst(currentRow, currentColumn) = 255;
//        }
//
//        file.close();
//        imshow("result", dst);
//        waitKey();
//    }
//}
//
//int main(int argc, char *argv[]) {
//
//    int op;
//
//    do {
//        destroyAllWindows();
//        cout << "Menu:\n";
//        cout << " 1 - Open inputImage\n";
//        cout << " 2 - Open BMP images from folder\n";
//        cout << " 3 - Image negative - diblook style\n";
//        cout << " 4 - BGR->HSV\n";
//        cout << " 5 - Resize inputImage\n";
//        cout << " 6 - Canny edge detection\n";
//        cout << " 7 - Edges in a video sequence\n";
//        cout << " 8 - Snap frame from live video\n";
//        cout << " 9 - Mouse callback demo\n";
//        cout << " 10 - Bordered inputImage\n";
//        cout << " 11 - chainCodeToText\n";
//        cout << " 12 - Lab7Demo (deprecated)\n";
//        cout << " 13 - Lab8Demo\n";
//        cout << " 0 - Exit\n\n";
//        cout << "Option: ";
//
//        cin >> op;
//
//        switch (op) {
//            case 1:
//                lab::testOpenImage();
//                break;
//            case 2:
//                lab::testOpenImagesFld();
//                break;
//            case 3:
//                lab::testParcurgereSimplaDiblookStyle(); //diblook style
//                break;
//            case 4:
//                // lab::testColor2Gray();
//                lab::testBGR2HSV();
//                break;
//            case 5:
//                lab::testResize();
//                break;
//            case 6:
//                lab::testCanny();
//                break;
//            case 7:
//                lab::testVideoSequence();
//                break;
//            case 8:
//                lab::testSnap();
//                break;
//            case 9:
//                lab::testMouseClick();
//                break;
//            case 10:
//                lab::borderTracing();
//                break;
//            case 11:
//                lab::chainCodeToText();
//                break;
//            case 13:
//                Lab8Work::Lab8 lab8;
//                lab8.demo();
//                break;
//        }
//    } while (op != 0);
//    return EXIT_SUCCESS;
//}

#include "main.h"

#include "LaneDetection/LaneDetection.h"
#include "LaneDetection/LaneDetection.cpp"

#include <fstream>

using namespace std;
using namespace cv;

namespace Menu {

    int main(int argc, char *argv[]) {

        const string fileName = FileUtil::getFileNameWithFullPath();
        const Mat inputImage = imread(fileName);

        LaneDetection laneDetection = LaneDetection();
        laneDetection
                .setImage(inputImage)
                .applyGaussianBlur()
                .applyCannyEdgeDetection()
                .printOutputLines()
                .displayImage();
    }
}