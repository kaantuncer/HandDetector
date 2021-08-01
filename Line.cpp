
#include "Line.h"


Line::Line(Point p1,Point p2,Scalar color){

    this->p1 = p1;
    this->p2 = p2;
    centerPoint = Point((p1.x+p2.x)/2, (p1.y+p2.y)/2);
    this->color = color;
};

bool Line::isColliding(Point point){

    if(distanceBetweenPoints(point,centerPoint) <=30){
        return true;
    }

    return false;
};

void Line::moveShape(Point point){

    int difX = centerPoint.x - p1.x;
    int difY = centerPoint.y - p1.y;

    p1.x = point.x - difX;
    p2.x = point.x + difX;

    p1.y = point.y - difY;
    p2.y = point.y + difY;

    Shape::moveShape(point);
}
void Line::drawShape(Mat& img,Point higestPoint){
    if(!carried){
        arrowedLine(img,p1,p2,color,10);
    }
    else{
        arrowedLine(img,p1,p2,Scalar(255,255,255),10);
    }
    Shape::drawShape(img,higestPoint);

}
