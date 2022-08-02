#ifndef __MAIN_H__
#define __MAIN_H__

#include "opencv2/opencv.hpp"
#include <string>
#include <iostream>
using namespace std;

void flip_img(cv::Mat &img, cv::Mat &dst){
    cv::flip(img,dst,0);
};

#endif