
#include "Circle.h"


Circle::Circle(Point center,Scalar color){

    centerPoint = center;
    this->color = color;
};

bool Circle::isColliding(Point point){
        if(distanceBetweenPoints(centerPoint,point) <= 50){
            return true;
        }

        return false;
};

void Circle::moveShape(Point point){

    Shape::moveShape(point);
}
void Circle::drawShape(Mat& img,Point higestPoint){
    if(!carried){
        circle(img,centerPoint,50,color,FILLED);
    }
    else{
        circle(img,centerPoint,50,Scalar(255,255,255),FILLED);
    }
    Shape::drawShape(img,higestPoint);

}
