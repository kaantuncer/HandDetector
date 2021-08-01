#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"


class Circle: public Shape {
  public:
    Circle(Point center, Scalar color);
     bool isColliding(Point point);
     void moveShape(Point point);
     void drawShape(Mat& img,Point higestPoint);
 };


#endif // CIRCLE_H
