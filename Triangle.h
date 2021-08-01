#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"
#include <vector>

using namespace std;


class Triangle: public Shape {
  public:
    Point p1,p2,p3;
    Triangle(Point p1,Point p2,Point p3, Scalar color);
     bool isColliding(Point point);
     void moveShape(Point point);
     void drawShape(Mat& img,Point higestPoint);
 };


#endif // TRIANGLE_H
