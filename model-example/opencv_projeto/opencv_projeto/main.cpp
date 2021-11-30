#include <iostream>
#include "libraries_opencv.h"

using namespace cv;

CascadeClassifier faceCascade;

void faceDetection(Mat frame) {
    double scale = 1.0;

    Mat grayscale;
    cvtColor(frame, grayscale, COLOR_BGR2GRAY);
    resize(grayscale, grayscale, Size(grayscale.size().width / scale, grayscale.size().height / scale));

    //face detection setup 
    std::vector<Rect> faces;
    faceCascade.detectMultiScale(grayscale, faces, 1.1, 3, 0, Size(30, 30));

    for (Rect area : faces) {
        Scalar drawColor = Scalar(255, 0, 0); 
        //geometric-scalar recognizer setup
        rectangle(frame, Point(cvRound(area.x * scale), cvRound(area.y * scale)),
            Point(cvRound((area.x + area.width - 1) * scale), cvRound((area.y + area.height - 1) * scale)), drawColor);
    }
    imshow("detection", frame);
}

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
    while (cap.read(frame)) {
        if (frame.empty()) {
            std::cout << "No Frame";
            break;
        }
        faceDetection(frame);
        if (waitKey(15) >= 0) {
            break;
        }
    }
    return 0;
}



