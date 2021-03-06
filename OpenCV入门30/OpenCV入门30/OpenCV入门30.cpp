// OpenCV入门30.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

Mat src, dst, mid;
vector<Vec4i> g_lines;

int g_nthreshold = 100;
static void on_HoughLines(int, void *);

int main()
{
	system("color 3F");

	Mat src = imread("p6sb.jpg");
	imshow("原始图", src);

	namedWindow("效果图", 1);
	createTrackbar("值", "效果图", &g_nthreshold, 200, on_HoughLines);
    
	Canny(src, mid, 50, 250, 3);
	cvtColor(mid, dst, COLOR_GRAY2BGR);

	on_HoughLines(g_nthreshold, 0);
	HoughLinesP(mid, g_lines, 1, CV_PI / 180, 80, 50, 10);

	imshow("效果图", dst);

	waitKey(0);

	return 0;
}

static void on_HoughLines(int, void *)
{
	Mat dstImage = dst.clone();
	Mat midImage = mid.clone();

	vector<Vec4i>mylines;
	HoughLinesP(midImage, mylines, 1, CV_PI / 180, g_nthreshold + 1, 50, 10);

	for (size_t i = 0; i < mylines.size(); i++)
	{
		Vec4i l = mylines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23, 180, 55), 1, CV_AA);
		imshow("效果图", dstImage);
	}
}