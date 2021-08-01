#ifndef SHAPE_H
#define SHAPE_H

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;

class Shape{

    public:
        std::chrono::system_clock::time_point lastEntry = std::chrono::system_clock::now();
        std::chrono::system_clock::time_point stationaryTime = std::chrono::system_clock::now();
        Scalar color;
        Point centerPoint;
        bool carried;
        static long distanceBetweenPoints(Point& point1,Point& point2);
        virtual bool isColliding(Point point);
        virtual void moveShape(Point point);
        virtual void drawShape(Mat& img,Point highestPoint);

};




#endif // SHAPE_H
