#ifndef MASKMANAGER_H
#define MASKMANAGER_H

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;


void HSVCallback(int,void*);
void LABCallback(int,void*);
void YCB_Cb_Callback(int,void*);
void YCB_Cr_Callback(int,void*);


void HSVMask(Mat &mask,Mat image, Vec3b bgrPixel ,int threshold);
void LABMask(Mat &mask,Mat image, Vec3b bgrPixel ,int threshold);
void YCB_Cb_Mask(Mat &mask,Mat image, Vec3b bgrPixel ,int threshold);
void YCB_Cr_Mask(Mat &mask,Mat image, Vec3b bgrPixel ,int threshold);
void applyMasks(Mat& result , Mat image,Vec3b bgrPixel);
Mat getCombinedMask(Vec3b& bgrPixel, Mat& image);

#endif // MASKMANAGER_H
