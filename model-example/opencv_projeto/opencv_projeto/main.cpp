#include <iostream>
#include <vector>
#include <string>
#include "libraries_opencv.h"
#include "class.h"

using namespace cv;
CascadeClassifier faceCascade;


int main(int argc, const char** argv) {
    //file upload
    std::string faceClassifier = "C:\\Users\\Lipster\\Desktop\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_alt.xml";

    if (!faceCascade.load(faceClassifier)) {
        std::cout << "ERROR in load";
        return -1;
    };
    std::cout << "Classifier Loaded" << std::endl;
    //video display capture
    VideoCapture cap(0);
    if (!cap.isOpened())
        return -1;
    //frame settings
    Mat frame;
    faceDetector facedetector;
    while (cap.read(frame)) {
        if (frame.empty()) {
            std::cout << "No Frame";
            break;
        }
        facedetector.face_detector(frame);
        if (waitKey(15) >= 0) {
            break;
        }
    }
    return 0;
}
