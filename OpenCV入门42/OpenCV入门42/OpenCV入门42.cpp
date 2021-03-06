// OpenCV入门42.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/photo/photo.hpp>
#include<iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "原始图"
#define WINDOW_NAME2 "效果图"

Mat srcImage, inpaintMask;
Point previousPoint(-1, -1);

static void on_Mouse(int event, int x, int y, int flags, void *)
{
	if (event == EVENT_LBUTTONUP || !(flags&EVENT_FLAG_LBUTTON))
		previousPoint = Point(-1, -1);
	else if (event == EVENT_LBUTTONDOWN)
		previousPoint = Point(x, y);

	else if (event == EVENT_MOUSEMOVE && (flags&EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (previousPoint.x < 0)
			previousPoint = pt;
		line(inpaintMask, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		line(srcImage, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		previousPoint = pt;
		imshow(WINDOW_NAME1, srcImage);
	}
}

int main(int argc, char** argv)
{
	Mat srcImage1 = imread("15.jpg", 1);
	srcImage = srcImage1.clone();
	inpaintMask = Mat::zeros(srcImage.size(),CV_8U);

	imshow(WINDOW_NAME1, srcImage);
	setMouseCallback(WINDOW_NAME1, on_Mouse, 0);
	while (1)
	{
		int c = waitKey(0);

		if ((char)c == 27)
			break;

		if ((char)c == '2')
		{
			inpaintMask = Scalar::all(0);
			srcImage1.copyTo(srcImage);
			imshow(WINDOW_NAME1, srcImage);
		}

		if ((char)c == '1' || (char)c == ' ')
		{
			Mat inpaintedImage;
			inpaint(srcImage, inpaintMask, inpaintedImage, 10, INPAINT_TELEA);
			imshow(WINDOW_NAME2, inpaintedImage);
		}
	}
    return 0;
}

