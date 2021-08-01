
#include "Triangle.h"

float sign (Point p1, Point p2, Point p3)
{
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle (Point pt, Point v1, Point v2, Point v3)
{
    float d1, d2, d3;
    bool has_neg, has_pos;

    d1 = sign(pt, v1, v2);
    d2 = sign(pt, v2, v3);
    d3 = sign(pt, v3, v1);

    has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);
    return !(has_neg && has_pos);
}


Triangle::Triangle(Point p1,Point p2,Point p3,Scalar color){

    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    centerPoint = Point((p2.x+p3.x)/2, (p1.y- (2*(p1.y - p2.y)/3)));
    this->color = color;
};

bool Triangle::isColliding(Point point){
     return PointInTriangle(point,p1,p2,p3);
};

void Triangle::moveShape(Point point){


    p1 = Point(point.x,point.y-80);
    p2 = Point(point.x-69,point.y+40);
    p3 = Point(point.x+69,point.y+40);

    Shape::moveShape(point);
}
void Triangle::drawShape(Mat& img,Point higestPoint){

    vector<vector<Point>> triangleContour;
    vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);


    if(!carried){
        polylines(img,points,true,color,1);
        fillPoly(img,points,color);

    }
    else{
        polylines(img,points,true,Scalar(255,255,255),1);
        fillPoly(img,points,Scalar(255,255,255));
    }

    Shape::drawShape(img,higestPoint);
}
