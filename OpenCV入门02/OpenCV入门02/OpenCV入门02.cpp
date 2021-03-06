// OpenCV入门02.cpp: 定义控制台应用程序的入口点。

#include "stdafx.h"
#include<opencv2\opencv.hpp>
using namespace cv;

int main()
{
	VideoCapture capture("VID_20180621_133617.mp4");
	Mat edges;
	while (1)
	{
		Mat frame;
		capture >> frame;
		cvtColor(frame, edges, COLOR_BGR2GRAY);
		blur(edges, edges, Size(7, 7));
		if (frame.empty())
		{
			break;
		}
		imshow("读取视频", edges);
		waitKey(30);
	}
	return 0;
}
