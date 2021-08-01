
#include "Rectangle.h"


Rectangle::Rectangle(Point topLeft , Point bottomRight,Scalar color){

    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
    this->color = color;
    centerPoint = Point((topLeft.x+bottomRight.x)/2 , (topLeft.y+bottomRight.y)/2);
};

bool Rectangle::isColliding(Point point){
        if(topLeft.x < point.x && topLeft.y < point.y && bottomRight.x > point.x && bottomRight.y >point.y){
            return true;
        }

        return false;
};

void Rectangle::moveShape(Point point){

    topLeft = Point(point.x - 50 , point.y -50);
    bottomRight = Point(point.x +50 , point.y +50);
    Shape::moveShape(point);

}
void Rectangle::drawShape(Mat& img,Point higestPoint){
    if(!carried){
        rectangle(img,topLeft,bottomRight,color,FILLED);
    }
    else{
        rectangle(img,topLeft,bottomRight,Scalar(255,255,255),FILLED);
    }
    Shape::drawShape(img,higestPoint);

}
