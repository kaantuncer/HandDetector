#include "MaskManager.h"

Mat maskHSV,maskLAB,maskYCB_Cb,maskYCB_Cr;
int HSVThreshold = 8,LABThreshold =20,YCB_Cb_Threshold = 20 , YCB_Cr_Threshold = 7;

Mat image;
Vec3b bgrPixel;


void HSVMask(Mat &maskHSV,Mat image, Vec3b bgrPixel ,int thresh){

    Mat HSV,hsv;
    cvtColor(image, HSV, cv::COLOR_BGR2HSV);
    Mat3b bgr (bgrPixel);
    cvtColor(bgr, hsv, COLOR_BGR2HSV);
    Vec3b hsvPixel(hsv.at<Vec3b>(0,0));

    cv::Scalar minHSV = cv::Scalar(hsvPixel.val[0] - thresh);
    cv::Scalar maxHSV = cv::Scalar(hsvPixel.val[0] + thresh);

    Mat1b hsv_chs[3];
    split(HSV,hsv_chs);

    cv::inRange(hsv_chs[0], minHSV, maxHSV, maskHSV);

}

void LABMask(Mat &mask,Mat image, Vec3b bgrPixel ,int thresh){

    Mat LAB,lab;
    cvtColor(image, LAB, COLOR_BGR2Lab);
    Mat3b bgr (bgrPixel);
    cvtColor(bgr, lab, COLOR_BGR2Lab);
    Vec3b labPixel(lab.at<Vec3b>(0,0));

    Mat1b lab_chs[3];
    split(LAB,lab_chs);

    cv::Scalar minLAB = cv::Scalar(labPixel.val[1] - thresh);
    cv::Scalar maxLAB = cv::Scalar(labPixel.val[1] + thresh);
    cv::inRange(lab_chs[1], minLAB, maxLAB, mask);


}

void YCB_Cb_Mask(Mat &mask,Mat image, Vec3b bgrPixel ,int thresh){

    Mat YCB,ycb;
    cvtColor(image, YCB, cv::COLOR_BGR2YCrCb);
    Mat3b bgr (bgrPixel);
    cvtColor(bgr, ycb, COLOR_BGR2YCrCb);
    Vec3b ycbPixel(ycb.at<Vec3b>(0,0));

    Mat1b ycb_chs[3];
    split(YCB,ycb_chs);

    cv::Scalar minYCB = cv::Scalar(ycbPixel.val[1] - thresh);
    cv::Scalar maxYCB = cv::Scalar(ycbPixel.val[1] + thresh);

    cv::inRange(ycb_chs[1], minYCB, maxYCB, mask);

}

void YCB_Cr_Mask(Mat &mask,Mat image, Vec3b bgrPixel ,int thresh){

    Mat YCB,ycb;
    cvtColor(image, YCB, cv::COLOR_BGR2YCrCb);
    Mat3b bgr (bgrPixel);
    cvtColor(bgr, ycb, COLOR_BGR2YCrCb);
    Vec3b ycbPixel(ycb.at<Vec3b>(0,0));

    Mat1b ycb_chs[3];
    split(YCB,ycb_chs);

    cv::Scalar minYCB = cv::Scalar(ycbPixel.val[2] - thresh);
    cv::Scalar maxYCB = cv::Scalar(ycbPixel.val[2] + thresh);

    cv::inRange(ycb_chs[2], minYCB, maxYCB, mask);

}

Mat getCombinedMask(Vec3b& currentBgrPixel, Mat& currentImage){

    image = currentImage;
    bgrPixel = currentBgrPixel;


    namedWindow("Mask HSV/H",WINDOW_AUTOSIZE);
    createTrackbar("Threshold:","Mask HSV/H",&HSVThreshold,40,HSVCallback);
    HSVCallback(0,0);

    namedWindow("Mask LAB/A",WINDOW_AUTOSIZE);
    createTrackbar("Threshold:","Mask LAB/A",&LABThreshold,40,LABCallback);
    LABCallback(0,0);

    namedWindow("Mask YCbCr/Cb",WINDOW_AUTOSIZE);
    createTrackbar("Threshold:","Mask YCbCr/Cb",&YCB_Cb_Threshold,40,YCB_Cb_Callback);
    YCB_Cb_Callback(0,0);

    namedWindow("Mask YCbCr/Cr",WINDOW_AUTOSIZE);
    createTrackbar("Threshold:","Mask YCbCr/Cr",&YCB_Cr_Threshold,40,YCB_Cr_Callback);
    YCB_Cr_Callback(0,0);

    Mat combined;

    Mat maskX,maskY,maskZ,maskQ,maskW,maskE;

    bitwise_and(maskHSV,maskLAB,maskX);
    bitwise_and(maskHSV,maskYCB_Cb,maskY);
    bitwise_and(maskLAB,maskYCB_Cb,maskZ);


    bitwise_and(maskYCB_Cr,maskHSV,maskQ);
    bitwise_and(maskYCB_Cr,maskYCB_Cb,maskW);
    bitwise_and(maskYCB_Cr,maskLAB,maskE);

    bitwise_or(maskX,maskY,combined);
    bitwise_or(combined,maskZ,combined);
    bitwise_or(combined,maskW,combined);
    bitwise_or(combined,maskE,combined);
    bitwise_or(combined,maskQ,combined);

    /*
    bitwise_and(maskYCB_Cb,maskYCB_Cr,combined);
    bitwise_and(maskLAB,combined,combined);
    bitwise_and(maskHSV,combined,combined);

    */


    Mat element = getStructuringElement(0,
                         Size(5,5),
                         Point(3, 3));

    morphologyEx(combined,combined,MORPH_OPEN,element);

    morphologyEx(combined, combined,3,element);

    imshow("Combined",combined);

    //GaussianBlur(combined,combined,Size(3,3),0);
    medianBlur(combined,combined,3);

    return combined;
}

void HSVCallback(int,void*){
    HSVMask(maskHSV,image,bgrPixel,HSVThreshold);
    imshow("Mask HSV/H",maskHSV);
}
void LABCallback(int,void*){
    LABMask(maskLAB,image,bgrPixel,LABThreshold);
    imshow("Mask LAB/A",maskLAB);
}
void YCB_Cb_Callback(int,void*){
    YCB_Cb_Mask(maskYCB_Cb,image,bgrPixel,YCB_Cb_Threshold);
    imshow("Mask YCbCr/Cb",maskYCB_Cb);
}
void YCB_Cr_Callback(int,void*){
    YCB_Cr_Mask(maskYCB_Cr,image,bgrPixel,YCB_Cr_Threshold);
    imshow("Mask YCbCr/Cr",maskYCB_Cr);
}
