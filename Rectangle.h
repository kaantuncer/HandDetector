#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"


class Rectangle: public Shape {
    Point topLeft;
    Point bottomRight;
  public:
    Rectangle(Point topLeft , Point bottomRight,Scalar color);
     bool isColliding(Point point);
     void moveShape(Point point);
     void drawShape(Mat& img,Point higestPoint);
 };


#endif // RECTANGLE_H
