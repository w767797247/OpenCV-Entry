// OpenCV入门12.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

bool ROI_AddImage();
bool LinearBlending();
bool ROI_LinearBlending();

int main()
{
	system("color 5E");

	if (ROI_AddImage() && LinearBlending() && ROI_LinearBlending())
	{
		cout << endl << "运行成功，得出了你需要的图像~! : )";
	}

	waitKey(0);
	return 0;
}

bool ROI_AddImage()
{
	Mat srcImage1 = imread("psb0IIOYVXT.png");
	Mat logoImage = imread("logo.jpg");
	if (!srcImage1.data) { printf("读取srcImage1 错误~！ \n"); return false; }
	if (!logoImage.data) { printf("读取logoImage 错误~！ \n"); return false; }

	Mat imageROI = srcImage1(Rect(200, 250, logoImage.cols, logoImage.rows));

	Mat mask = imread("logo.jpg", 0);
	
	logoImage.copyTo(imageROI, mask);

	namedWindow("<1>利用ROI实现图像叠加示例窗口");
	imshow("<1>利用ROI实现图像叠加示例窗口", srcImage1);

	return true;
}

bool LinearBlending()
{
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage2, srcImage3, dstImage;

	srcImage2 = imread("psb0IIOYVXT.png");
	srcImage3 = imread("psbLOWW3Y7R.png");

	if (!srcImage2.data) { printf("读取srcImage2错误~! \n"); return false; }
	if (!srcImage3.data) { printf("读取srcImage3错误~! \n"); return false; }

	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage2, alphaValue, srcImage3, betaValue, 0.0, dstImage,-1);

	namedWindow("<2>线性混合示例窗口[原图]",1);
	imshow("<2>线性混合示例窗口[原图]", srcImage2);

	namedWindow("<3>线性混合示例窗口[效果图]", 1);
	imshow("<3>线性混合示例窗口[效果图]", dstImage);

	return true;
}

bool ROI_LinearBlending()
{
	Mat srcImage4 = imread("psb0IIOYVXT.png");
	Mat logoImage = imread("logo.jpg");

	if (!srcImage4.data) { printf("读取srcImage4错误~! \n"); return false; }
	if (!logoImage.data) { printf("读取logoImage错误~! \n"); return false; }

	Mat imageROI;
	imageROI = srcImage4(Rect(200, 250, logoImage.cols, logoImage.rows));
	//imageROI = srcImage4(Range(250, 250+logoImage.rows), Range(200, 200+logoImage.cols);

	addWeighted(imageROI, 0.5, logoImage, 0.3, 0., imageROI,-1);

	namedWindow("<4>区域线性图像混合示例窗口");
	imshow("<4>区域线性图像混合示例窗口", srcImage4);

	return true;
}
