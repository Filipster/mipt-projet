#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "libraries_opencv.h"
#include <iostream>
#include<conio.h>

void main(int argc, char** argv)
{
	cv::Mat src = cv::imread("C:\\Users\\Lipster\\Desktop\\test_pic.jpeg"); 
	cv::namedWindow("Object Detection", cv::WINDOW_GUI_NORMAL);
	cv::Mat _copy = ResizeImage(src);
	imshow("Object Detection", _copy);
	
	std::vector<std::vector<cv::Point2f>> contours = FindAnchors(_copy);
	std::vector<cv::Point2f> lstPointIntersection = ListPointIntersection(contours);
	
	lstPointIntersection = ClusterPoints(lstPointIntersection, 3);
	std::vector<cv::Point2f> anchors;
	anchors = SortAnchors(lstPointIntersection);
	anchors = TranformPoints(anchors, cv::Point2f(), src.size().height / 800.0);
	std::vector<cv::Point2f> indentityRegion = { anchors[1],anchors[3] };
	std::vector<cv::Point2f> answerRegion = { anchors[3],anchors[5] };
	cv::Mat subIdImage = SubRectangleImage(src, indentityRegion);
	subIdImage = ResizeImage(subIdImage);
	cv::Mat subAnswerImage = SubRectangleImage(src, answerRegion);
	
	subAnswerImage = ResizeImage(subAnswerImage);
	
	cv::namedWindow("SubImage", cv::WINDOW_GUI_NORMAL);
	cv::namedWindow("SubImage Resized", cv::WINDOW_GUI_NORMAL);
	std::vector<std::vector<cv::Point2f>> IdRects = FindRectangles(subIdImage, 200, 250, 0.05);
	IdRects = SortRectangles(IdRects, 1);
	std::vector<std::vector<cv::Point2f>> answerRects = FindRectangles(subAnswerImage, 200, 250, 0.05);
	answerRects = SortRectangles(answerRects, 1);
	
	imshow("SubImage resized 2x", subIdImage);
	imshow("SubImagem resized 2x", subAnswerImage);

	std::vector<cv::Mat> IdMats = SeriImage(subIdImage, IdRects);
	std::vector<cv::Mat> AnswerMats = SeriImage(subAnswerImage, answerRects);
	for (int i = 0; i < AnswerMats.size(); i++) {
		cv::imshow("jpeg." + std::to_string(i) + ".jpg", AnswerMats[i]);
		
	}
	
	std::vector<std::string> id = IdentityHeader(IdMats);
	std::vector<std::vector<std::string>> allAnswers = AllAnswers(AnswerMats);
	std::cout << "Console output :" << id[0] << std::endl;
	std::cout << "Console Output :" << id[1] << std::endl;
	int k = 1;
	for (int i = 0; i < allAnswers.size(); i++)
	{
		for (int j = 0; j < allAnswers[i].size(); j++)
		{
			std::cout << k << "." << allAnswers[i][j] << "     ";
			k++;
		}
	}
	cv::waitKey();
}
