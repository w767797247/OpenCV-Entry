// OpenCV入门36.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;

int main()
{
	Mat image(600, 600, CV_8UC3);
	RNG& rng = theRNG();

	while (1)
	{
		char key;
		int count = rng.uniform(3, 103);
		vector<Point>points;

		for (int i = 0; i < count; i++);
		{
			Point point;
			point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);

			points.push_back(point);
		}

		vector<int> hull;
		convexHull(Mat(points), hull, true);

		image = Scalar::all(0);
		for (int i = 0; i < count; i++)
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), CV_FILLED, CV_AA);

		int hullcount = (int)hull.size();
		Point point0 = points[hull[hullcount - 1]];

		for (int i = 0; i < hullcount; i++)
		{
			Point point = points[hull[i]];
			line(image, point0, point, Scalar(255, 255, 255), 2, CV_AA);
			point0 = point;
		}
		imshow("凸包", image);

		key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q')
			break;
	}
    return 0;
}

