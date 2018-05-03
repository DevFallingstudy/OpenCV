//
//  main.cpp
//  04-2
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

Mat RGBtoYCrCb(Mat img_RGB);
Mat RGBtoCMY(Mat img_RGB);
Mat CMYtoRGB(Mat img_CMY);
Mat RGBtoHSV(Mat img_RGB);

Mat IntensityToRGB(Mat src, float k);
Mat IntensityToYCrCb(Mat src, float k);
Mat IntensityToCMY(Mat src, float k);
Mat IntensityToHSV(Mat src, float k);

float arr1[3][3] = {
    {65.48, 128.55, 24.96},
    {-37.79, -74.20, 122},
    {112, -93.78, -18.21}
};

float arr2[3] = {16, 128, 128};

int main(int argc, const char * argv[]) {
    float k = 0.7;
    Mat img_origin;
    Mat img_Y, img_Cb, img_Cr;
    Mat img_YCbCr, img_CMY, img_HSV;
    Mat img_RGBIntensity, img_YCbCrIntensity, img_CMYIntensity, img_HSVIntensity;
    Mat img_RGBResult, img_YCbCrResult, img_CMYResult, img_HSVResult;
    
    img_origin = getImageWithName("Lena_color.png");
    
    img_YCbCr = RGBtoYCrCb(img_origin);
    img_CMY = RGBtoCMY(img_origin);
    img_HSV = RGBtoHSV(img_origin);

    img_RGBResult = IntensityToRGB(img_origin, k);
    img_YCbCrIntensity = IntensityToYCrCb(img_YCbCr, k);
    img_HSVIntensity = IntensityToHSV(img_HSV, k);
    img_CMYIntensity = IntensityToCMY(img_CMY, k);

    cvtColor(img_HSVIntensity, img_HSVResult, CV_HSV2BGR);
    cvtColor(img_YCbCrIntensity, img_YCbCrResult, CV_YCrCb2BGR);
    img_CMYResult = CMYtoRGB(img_CMYIntensity);

    imshow("origin", img_origin);

    imshow("RGB Int", img_RGBResult);
    imshow("YCbCr Int", img_YCbCrResult);
    imshow("CMY Int", img_CMYResult);
    imshow("HSV Int", img_HSVResult);
    
//    imshow("RGB", img_origin);
//    imshow("CMY", RGBtoCMY(img_origin));
//    imshow("RGB<-CMY", CMYtoRGB(RGBtoCMY(img_origin)));
    
    waitKey(0);
    
    return 0;
}

Mat getImageWithName(string name) {
    string imageName(name);
    Mat img;
    
    // Show images
    img = imread(imageName.c_str(), IMREAD_COLOR);
    
//    namedWindow("Result", WINDOW_AUTOSIZE);
//    imshow("Result", img);
//    waitKey(0);
    
    return img;
}

Mat RGBtoYCrCb(Mat img_RGB) {
    Mat img_YCrCb;
    
    cvtColor(img_RGB, img_YCrCb, CV_BGR2YCrCb);
    
    return img_YCrCb;
}

Mat RGBtoCMY(Mat img_RGB) {
    Mat img_CMY;
    int height, width;
    
    height = img_RGB.size().height;
    width = img_RGB.size().width;
    
    img_CMY = Mat::zeros(img_RGB.size(), CV_8UC3);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float R = (int)img_RGB.at<Vec3b>(i, j)[2];
            float G = (int)img_RGB.at<Vec3b>(i, j)[1];
            float B = (int)img_RGB.at<Vec3b>(i, j)[0];
            
            img_CMY.at<Vec3b>(i, j)[0] = 255 - R;
            img_CMY.at<Vec3b>(i, j)[1] = 255 - G;
            img_CMY.at<Vec3b>(i, j)[2] = 255 - B;
        }
    }
    
    return img_CMY;
}

Mat CMYtoRGB(Mat img_CMY) {
    Mat img_RGB;
    int height, width;
    
    height = img_CMY.size().height;
    width = img_CMY.size().width;
    
    img_RGB = Mat::zeros(img_CMY.size(), CV_8UC3);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            float C = (int)img_CMY.at<Vec3b>(i, j)[0];
            float M = (int)img_CMY.at<Vec3b>(i, j)[1];
            float Y = (int)img_CMY.at<Vec3b>(i, j)[2];
            
            img_RGB.at<Vec3b>(i, j)[2] = 255 - C;
            img_RGB.at<Vec3b>(i, j)[1] = 255 - M;
            img_RGB.at<Vec3b>(i, j)[0] = 255 - Y;
        }
    }
    
    return img_RGB;
}

Mat RGBtoHSV(Mat img_RGB) {
    Mat img_HSV;
    
    cvtColor(img_RGB, img_HSV, CV_BGR2HSV);
    
    return img_HSV;
}

Mat IntensityToRGB(Mat src, float k) {
    Mat img_result;
    int height, width;
    
    height = src.size().height;
    width = src.size().width;
    
    img_result = Mat::zeros(src.size(), CV_8UC3);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            
            img_result.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i, j)[0] * k;
            img_result.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i, j)[1] * k;
            img_result.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i, j)[2] * k;
        }
    }
    
    return img_result;
}

Mat IntensityToYCrCb(Mat src, float k) {
    Mat img_result;
    int height, width;
    
    height = src.size().height;
    width = src.size().width;
    
    img_result = Mat::zeros(src.size(), CV_8UC3);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            img_result.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i, j)[0] * k;
            img_result.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i, j)[1];
            img_result.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i, j)[2];
        }
    }
    
    return img_result;
}

Mat IntensityToCMY(Mat src, float k) {
    Mat img_result;
    int height, width;
    
    height = src.size().height;
    width = src.size().width;
    
    img_result = Mat::zeros(src.size(), CV_8UC3);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            img_result.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i, j)[0] * k + (1 - 255*k);
            img_result.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i, j)[1] * k + (1 - 255*k);
            img_result.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i, j)[2] * k + (1 - 255*k);
        }
    }
    
    return img_result;
}

Mat IntensityToHSV(Mat src, float k) {
    Mat img_result;
    int height, width;
    
    height = src.size().height;
    width = src.size().width;
    
    
    img_result = Mat::zeros(src.size(), CV_8UC3);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            img_result.at<Vec3b>(i, j)[0] = src.at<Vec3b>(i, j)[0];
            img_result.at<Vec3b>(i, j)[1] = src.at<Vec3b>(i, j)[1];
            img_result.at<Vec3b>(i, j)[2] = src.at<Vec3b>(i, j)[2] * k;
        }
    }
    
    return img_result;
}

