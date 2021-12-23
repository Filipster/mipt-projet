#pragma once
#include <iostream>
#include "libraries_opencv.h"

using namespace cv;
class faceDetector {
public:
    CascadeClassifier faceCascade;
    Mat frame;

    void face_detector(Mat frame) {
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
};
