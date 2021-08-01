#ifndef HANDDETECTION_H
#define HANDDETECTION_H

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Line.h"
#include "MaskManager.h"

using namespace cv;
using namespace std;

void getContour(vector<vector<Point>> &biggestContour,Mat combined);
void fillConvexityDefects(vector<Vec4i>& convexityDefectsVector,vector<vector<Point>> biggestContour);
void fillFingerAndDefectLocations(vector<Point>& fingerLocations,vector<Point>& defects,vector<Vec4i> convexityDefectsVector,vector<vector<Point>> biggestContour);
void getCenterColorFromCamera (Vec3b &color, VideoCapture cap);
void getHighestPointFromContour(Point& point,vector<vector<Point>> biggestContour);
bool checkCollisionWithRectangle(Point topLeft,Point bottomRight,Point point);
void runApplication();

#endif // HANDDETECTION_H
