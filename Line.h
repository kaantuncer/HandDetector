#ifndef LINE_H
#define LINE_H

#include "Shape.h"

class Line: public Shape {
  public:
    Point p1;
    Point p2;
    Line(Point p1,Point p2, Scalar color);
     bool isColliding(Point point);
     void moveShape(Point point);
     void drawShape(Mat& img,Point higestPoint);
 };


#endif // LINE_H
