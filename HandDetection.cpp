#include "HandDetection.h"

//This function finds all the contours in an image and puts the biggest one to the given list.
void getContour(vector<vector<Point>> &biggestContour,Mat combined){

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(combined, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE);
    //Mat image_copy = Mat::zeros(img_gray.size(),CV_8UC3);

        double biggestContourArea = 0;
        int biggestIndex = -1;
        for(int i = 0 ;i<contours.size();i++){
            if(biggestContourArea < contourArea(contours[i])){
                biggestContourArea = contourArea(contours[i]);
                biggestIndex = i;
            }
        }
        if(biggestIndex != -1){
            biggestContour.push_back(contours[biggestIndex]);
        }
}

void fillConvexityDefects(vector<Vec4i>& convexityDefectsVector,vector<vector<Point>> biggestContour){

    if(biggestContour.size() == 0){
        return;
    }

    vector<Point> hull;
    vector<int> indexHull;
    convexHull(biggestContour[0], hull);
    convexHull(biggestContour[0],indexHull);
    convexityDefects(biggestContour[0],indexHull,convexityDefectsVector);
}

void fillFingerAndDefectLocations(vector<Point>& fingerLocations,vector<Point>& defects,vector<Vec4i> convexityDefectsVector,vector<vector<Point>> biggestContour){
    double smallestXValue = DBL_MAX;
    Point smallestXPoint;
    Point emptyPoint;
    for(const Vec4i& v : convexityDefectsVector){
        float depth = v[3] / 256;
        if (depth > contourArea(biggestContour[0])/500){
            int startidx = v[0]; Point ptStart(biggestContour[0][startidx]);
            int endidx = v[1]; Point ptEnd(biggestContour[0][endidx]);
            int faridx = v[2]; Point ptFar(biggestContour[0][faridx]);
            if(ptStart.x < smallestXValue){
                smallestXValue = ptStart.x;
                smallestXPoint = ptEnd;
            }
            fingerLocations.push_back(ptStart);
            defects.push_back(ptFar);
            }
        }
     if(smallestXPoint != emptyPoint){
         fingerLocations.push_back(smallestXPoint);
    }

}

void getHighestPointFromContour(Point& point,vector<vector<Point>> biggestContour){

    auto val = std::minmax_element(biggestContour[0].begin(), biggestContour[0].end(), [](Point const& a, Point const& b){
        return a.y < b.y;
    });

    point = *val.first;



}

void getCenterColorFromCamera (Vec3b &color, VideoCapture cap){
    Mat3b im;
    for (;;)
    {
        cap >> im;
        Point centerPoint(im.cols/2, im.rows/2);
        circle(im, centerPoint, 3, Scalar(0, 0, 255), 3);
        string outputText = "Please put your fingertip on the red circle";
        putText(im, outputText, Point(5, 30), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
        putText(im, "Press Enter", Point(5, 60), FONT_HERSHEY_SIMPLEX, 0.7, Scalar(0, 255, 0), 2);
        imshow("Window", im);

        // Wait until ENTER is pressed
        if (waitKey(10) == 13)
        {
            color.operator=((im.at<Vec3b>(im.rows/2, im.cols/2)));
            break;
        }
    }
}


Point lastArrowPoint = Point(0,0);
Point currentFingerPoint = Point(0,0);
vector<Shape*> shapes;
vector<Point> drawnPoints;
bool drawing = false;
RNG rng(12345);
bool fingerCounting = true;
Vec3b color;
Mat img;
int fps =20;

void fingerCountMode(Mat image_copy,vector<vector<Point>> biggestContour){
    drawContours(image_copy,biggestContour,0,Scalar(0,255,0),2);
    vector<Vec4i> convexityDefectsVector;
    fillConvexityDefects(convexityDefectsVector,biggestContour);

    vector<Point> fingerLocations;
    vector<Point> defects;
    fillFingerAndDefectLocations(fingerLocations,defects,convexityDefectsVector,biggestContour);
    for(int i = 0 ; i<fingerLocations.size();i++){
        circle(image_copy, fingerLocations[i], 4, Scalar(0, 0, 255), 2);
    }
    for(int i = 0 ; i<defects.size();i++){
        circle(image_copy, defects[i], 4, Scalar(255, 0, 0), 2);
    }
    putText(image_copy,"Finger Count: "+to_string(fingerLocations.size()), cv::Point(20, 30),cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(118, 185, 0), 2);
    putText(image_copy,"Press '.' to retake color", cv::Point(20, 60),cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(118, 185, 0), 2);
    putText(image_copy,"Press 'S' to switch modes", cv::Point(20, 90),cv::FONT_HERSHEY_DUPLEX,1.0,CV_RGB(118, 185, 0), 2);

}

void drawingMode(Mat image_copy,vector<vector<Point>> biggestContour){


    Point highestPoint = Point(-1,-1);
    if(biggestContour.size() != 0){
        getHighestPointFromContour(highestPoint,biggestContour);
        currentFingerPoint = highestPoint;
        circle(image_copy, highestPoint, 4, Scalar(255, 0, 0), 2);
    }

    putText(image_copy,"Press 'R' to spawn a rectangle", cv::Point(20, 30),cv::FONT_HERSHEY_DUPLEX,0.5,CV_RGB(0, 0, 0), 1);
    putText(image_copy,"Press 'C' to spawn a circle", cv::Point(20, 60),cv::FONT_HERSHEY_DUPLEX,0.5,CV_RGB(0, 0, 0),1);
    putText(image_copy,"Press 'T' to spawn a triangle", cv::Point(20, 90),cv::FONT_HERSHEY_DUPLEX,0.5,CV_RGB(0, 0, 0), 1);
    putText(image_copy,"Press 'A' twice to select 2 points for a line", cv::Point(20, 120),cv::FONT_HERSHEY_DUPLEX,0.5,CV_RGB(0, 0, 0), 1);
    putText(image_copy,"Press 'D' to start/stop drawing", cv::Point(20, 150),cv::FONT_HERSHEY_DUPLEX,0.5,CV_RGB(0, 0, 0), 1);
    putText(image_copy,"Press 'Q' to clear", cv::Point(20, 180),cv::FONT_HERSHEY_DUPLEX,0.5,CV_RGB(0, 0, 0), 1);
    putText(image_copy,"Press 'S' to switch modes", cv::Point(20, 210),cv::FONT_HERSHEY_DUPLEX,0.5,CV_RGB(0, 0, 0), 1);


    if(highestPoint.x != -1){
        if(lastArrowPoint.x != 0 && lastArrowPoint.y != 0){
            Line* line = new Line(lastArrowPoint,currentFingerPoint,Scalar(255,255,255));
            line->drawShape(image_copy,highestPoint);
            delete line;

        }
        if(drawing){
            drawnPoints.push_back(highestPoint);
        }
    }

    for(int i = 0 ; i<shapes.size();i++){
        shapes[i]->drawShape(image_copy,highestPoint);
    }
    for(int i = 1 ; i<drawnPoints.size();i++){
        cv::line(image_copy,drawnPoints[i-1],drawnPoints[i],Scalar(255,0,0),5);
    }
}

void runApplication(){

    VideoCapture vid(0);


    if(!vid.isOpened()){
        return;
    }
    getCenterColorFromCamera(color,vid);
    destroyAllWindows();

    while(vid.read(img)){

        char key = waitKey(1000/fps) & 0xFF;
        if(key == 27){
            break;
        }
        else if(key == '.'){
            destroyAllWindows();
            getCenterColorFromCamera(color,vid);
            destroyAllWindows();
        }
        else if(key == 's') {
            if(!fingerCounting){
                drawing = false;
                lastArrowPoint = Point(0,0);
            }
            fingerCounting = !fingerCounting;
        }
        else if(!fingerCounting){
            if(key == 'r'){
                Rectangle* rectangle = new Rectangle(Point(400,200),Point(500,300),Scalar(rng.uniform(0,256) , rng.uniform(0,256),rng.uniform(0,256)));
                shapes.push_back(rectangle);
            }
            else if(key == 'c'){
                Circle* circle = new Circle(Point(300,250),Scalar(rng.uniform(0,256) , rng.uniform(0,256),rng.uniform(0,256)));
                shapes.push_back(circle);
            }
            else if(key =='t'){
                Triangle* triangle = new Triangle(Point(160,180),Point(91,300),Point(229,300),Scalar(rng.uniform(0,256) , rng.uniform(0,256),rng.uniform(0,256)));
                shapes.push_back(triangle);
            }
            else if(key =='a'){

                if((lastArrowPoint.x != 0 && lastArrowPoint.y != 0) && !(lastArrowPoint.x == currentFingerPoint.x && lastArrowPoint.y == currentFingerPoint.y)){

                    Line* line = new Line(lastArrowPoint,currentFingerPoint,Scalar(rng.uniform(0,256) , rng.uniform(0,256),rng.uniform(0,256)));
                    shapes.push_back(line);
                    lastArrowPoint = Point(0,0);
                }
                else{

                    lastArrowPoint = currentFingerPoint;
                }

            }
            else if(key =='d'){
                drawing = !drawing;
            }
            else if(key == 'q'){
                shapes.clear();
                shapes.shrink_to_fit();
                drawnPoints.clear();
                drawnPoints.shrink_to_fit();
            }
        }

        Mat combined = getCombinedMask(color,img);

        Mat image_copy = img.clone();
        vector<vector<Point>> biggestContour;
        getContour(biggestContour,combined);

        if(fingerCounting){
            fingerCountMode(image_copy,biggestContour);
        }
        else{
           drawingMode(image_copy,biggestContour);
        }

        imshow("Hand Detection", image_copy);

    }

}
