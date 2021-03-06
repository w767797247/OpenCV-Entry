// OpenCV入门28.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat src = imread("04.png");
	Mat mid, dst;

	Canny(src, mid, 50, 200, 3);
	cvtColor(mid, dst, CV_GRAY2BGR);

	vector<Vec2f>lines;
	HoughLines(mid, lines, 1, CV_PI / 180, 250, 0, 0);

	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt1.y = cvRound(y0 - 1000 * (a));

		line(dst, pt1, pt2, Scalar(55, 100, 195), 1, CV_AA);
	}
	imshow("原始图", src);

	imshow("效果图", dst);

	waitKey(0);
	return 0;
}

