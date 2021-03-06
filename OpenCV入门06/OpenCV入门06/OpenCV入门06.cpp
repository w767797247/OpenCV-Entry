// OpenCV入门06.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace cv;

int main()
{
	Mat cat = imread("cat.jpeg");
	namedWindow("[1]动物图",WINDOW_NORMAL);
	imshow("[1]动物图", cat);
	
	Mat image = imread("01.jpg", 199);
	Mat image1 = imread("02.png");
	
	namedWindow("[2]景物图", WINDOW_NORMAL);
	imshow("[2]景物图", image);

	namedWindow("[3]猫咪老师", WINDOW_NORMAL);
	imshow("[3]猫咪老师", image1);

	Mat imageROI;
	imageROI = image(Rect(400, 350, image1.cols, image1.rows));

	addWeighted(imageROI, 0.9, image1, 0.4, 0., imageROI);

	namedWindow("[4]组合图", WINDOW_NORMAL);
	imshow("[4]组合图", image);

	imwrite("由imwrite生成的图片.jpg", image);

	waitKey();

	return 0;
}

