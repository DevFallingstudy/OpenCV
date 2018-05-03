//
//  main.cpp
//  04-1
//
//  Created by Fallingstar on 2018. 5. 3..
//  Copyright © 2018년 Fallingstar. All rights reserved.
//

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

Mat getImageWithName(string name);
Mat RGBtoYCrCb(Mat img_rgb);
Mat getYFromRGB(Mat img_RGB);
Mat getCbFromRGB(Mat img_RGB);
Mat getCrFromRGB(Mat img_RGB);

float arr1[3][3] = {
    {65.48, 128.55, 24.96},
    {-37.79, -74.20, 122},
    {112, -93.78, -18.21}
};

float arr2[3] = {16, 128, 128};

int main(int argc, const char * argv[]) {
    Mat img_origin;
    Mat img_Y, img_Cb, img_Cr;
    
    img_origin = getImageWithName("Lena_color.png");
    
    img_Y = getYFromRGB(img_origin);
    img_Cb = getCbFromRGB(img_origin);
    img_Cr = getCrFromRGB(img_origin);
    
    imshow("Y img", img_Y);
    imshow("Cb img", img_Cb);
    imshow("Cr img", img_Cr);
    waitKey(0);
    
    return 0;
}

Mat getImageWithName(string name) {
    string imageName(name);
    Mat img;
    
    // Show images
    img = imread(imageName.c_str(), IMREAD_COLOR);
    
    namedWindow("Result", WINDOW_AUTOSIZE);
    imshow("Result", img);
    waitKey(0);
    
    return img;
}

Mat RGBtoYCrCb(Mat img_rgb) {
    Mat img_YCrCb;
    
    cvtColor(img_rgb, img_YCrCb, CV_BGR2YCrCb);
    
    return img_YCrCb;
}

Mat getYFromRGB(Mat img_RGB) {
    Mat img_Y;
    int height, width;
    
    height = img_RGB.size().height;
    width = img_RGB.size().width;
    
    img_Y = Mat::zeros(img_RGB.size(), CV_8UC1);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            
            img_Y.at<uchar>(i, j) =
            arr1[0][0] * img_RGB.at<Vec3b>(i, j)[2]/255.0 +
            arr1[0][1] * img_RGB.at<Vec3b>(i, j)[1]/255.0 +
            arr1[0][2] * img_RGB.at<Vec3b>(i, j)[0]/255.0 + arr2[0];
        }
    }
    
    return img_Y;
}

Mat getCbFromRGB(Mat img_RGB) {
    Mat img_Cb;
    int height, width;
    
    height = img_RGB.size().height;
    width = img_RGB.size().width;
    
    img_Cb = Mat::zeros(img_RGB.size(), CV_8UC1);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            
            img_Cb.at<uchar>(i, j) =
            arr1[1][0] * img_RGB.at<Vec3b>(i, j)[2]/255.0 +
            arr1[1][1] * img_RGB.at<Vec3b>(i, j)[1]/255.0 +
            arr1[1][2] * img_RGB.at<Vec3b>(i, j)[0]/255.0 + arr2[1];
        }
    }
    
    return img_Cb;
}

Mat getCrFromRGB(Mat img_RGB) {
    Mat img_Cr;
    int height, width;
    
    height = img_RGB.size().height;
    width = img_RGB.size().width;
    
    img_Cr = Mat::zeros(img_RGB.size(), CV_8UC1);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            
            img_Cr.at<uchar>(i, j) =
            arr1[2][0] * img_RGB.at<Vec3b>(i, j)[2]/255.0 +
            arr1[2][1] * img_RGB.at<Vec3b>(i, j)[1]/255.0 +
            arr1[2][2] * img_RGB.at<Vec3b>(i, j)[0]/255.0 + arr2[2];
        }
    }
    
    return img_Cr;
}
