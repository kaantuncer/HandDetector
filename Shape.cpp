
#include "Shape.h"

using namespace std;

bool Shape::isColliding(Point point){
    std::cout<<"Shape Is Colliding"<<std::endl;
    return false;
}

void Shape::drawShape(Mat& img, Point highestPoint){

    bool isCollided = this->isColliding(highestPoint);


    if(!isCollided){
        this->lastEntry = chrono::system_clock::now();
        this->carried = false;
    }
    else{
        auto currentTime = chrono::system_clock::now();
        auto difference = chrono::duration_cast<chrono::seconds>(currentTime - this->lastEntry).count();
        if(difference >= 2){
            if(difference==2){
                this->stationaryTime = chrono::system_clock::now();
            }
            this->carried = true;
            if(!(distanceBetweenPoints(highestPoint,this->centerPoint) <= 18)){
                this->stationaryTime = chrono::system_clock::now();
            }
            difference = chrono::duration_cast<chrono::seconds>(currentTime - this->stationaryTime).count();
            if(difference >= 2){
                this->carried = false;
                this->lastEntry = chrono::system_clock::now();
            }
            this->moveShape(highestPoint);
        }
    }
}

void Shape::moveShape(Point point){
    centerPoint = point;
}

 long Shape::distanceBetweenPoints(Point& point1,Point& point2){
    return sqrt(pow(point1.x-point2.x,2)+pow(point1.y-point2.y,2));
}

