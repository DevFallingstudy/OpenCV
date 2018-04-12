//
//  main.cpp
//  03-2
//
//  Created by Fallingstar on 2018. 4. 5..
//  Copyright © 2018년 Fallingstar. All rights reserved.
//

// Headers for OpenCV
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

// Headers for default
#include <iostream>
#include <string>
#include <math.h>

using namespace cv;
using namespace std;

Mat smoothingImage(string imageName);
int getAverage(Mat img_origin, int x, int y, int size);

void getSharpnessImage();
Mat getLap(Mat img_origin, int x, int y);
int getLapPix1(Mat img_origin, int x, int y);
int getLapPix2(Mat img_origin, int x, int y);
int getLapPix3(Mat img_origin, int x, int y);
int getLapPix4(Mat img_origin, int x, int y);

int main(int argc, const char * argv[]) {
    getSharpnessImage();
    return 0;
}

void getSharpnessImage(){
    string imageName("./Lena_color.png");
    Mat image, image_gray, image_resize, image_result, image_Lap;
    int width=0, height=0;
    
    image_gray = smoothingImage("./Lena_color.png");
    
    if (image_gray.empty()) {
        cout << "Could not open or find image : " << imageName << std::endl;
        return;
    }else{        
        width = image_gray.size().width;
        height = image_gray.size().height;
        
        image_Lap = getLap(image_gray, width, height);
        image_result = Mat::zeros(width, height, image_gray.type());
        
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                image_result.at<uchar>(x, y) = saturate_cast<uchar>(image_Lap.at<uchar>(x, y) + image_gray.at<uchar>(x, y));
            }
        }
        
        namedWindow("Result", CV_WINDOW_AUTOSIZE);
        namedWindow("Lap", CV_WINDOW_AUTOSIZE);
        namedWindow("Origin", CV_WINDOW_AUTOSIZE);
        
        imshow("Result", image_result);
        imshow("Lap", image_Lap);
        imshow("Origin", image_gray);
        
        waitKey(0);
    }
}


Mat smoothingImage(string imageName){
    Mat image, image_gray, image_resize, image_result;
    int width=0, height=0;
    int size_frame, padding;
    int code = 0;
    
    image = imread(imageName.c_str(), IMREAD_COLOR);
    
    if (image.empty()) {
        cout << "Could not open or find image : " << imageName << std::endl;
    }else{
        code = 1;
        size_frame = 3;
        
        padding = size_frame-3+1;
        
        cvtColor(image, image_gray, CV_BGR2GRAY);
        width = image_gray.size().width;
        height = image_gray.size().height;
        
        cv::resize(image_gray, image_resize, cv::Size(width+padding, height+padding), 0, 0, CV_INTER_NN);
        
        image_result = Mat::zeros(width, height, image_gray.type());
        
        for (int x = 1; x < width; x++) {
            for (int y = 1; y < height; y++) {
                image_result.at<uchar>(x, y) = saturate_cast<uchar>(getAverage(image_gray, x, y, size_frame));
            }
        }
    }
    
    return image_result;
}

int getAverage(Mat img_origin, int x, int y, int size) {
    int sum = 0;
    int avg = 0;
    int max, min;
    
    max = size/2;
    min = -(size/2);
    
    for (int i = min; i <= max; i++) {
        for (int j = min; j <= max; j++) {
            sum += img_origin.at<uchar>(x+i, y+j);
        }
    }
    avg = sum/(size*size);
    
    return avg;
}

Mat getLap(Mat img_origin, int width, int height){
    Mat Laplacian;
    int pix1, pix2, pix3, pix4, pix;
    
    Laplacian = Mat::zeros(width+1, height+1, img_origin.type());
    
    // Get G
    for (int x = 1; x < width-1; x++) {
        for (int y = 1; y < height-1; y++) {
            pix = getLapPix4(img_origin, x, y);
            Laplacian.at<uchar>(x, y) = saturate_cast<uchar>(pix);
        }
    }
    
    return Laplacian;
}

int getLapPix1(Mat img_origin, int x, int y){
    Mat maskX = (Mat_<double>(3, 3) << 0, 1, 0,
                 1, -4, 1,
                 0, 1, 0);
    int sum = 0;
    
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            sum += img_origin.at<uchar>(x+i, y+j) * maskX.at<double>(1+i, 1+j);
        }
    }
    
    return sum;
}
int getLapPix2(Mat img_origin, int x, int y){
    Mat maskX = (Mat_<double>(3, 3) << 1, 1, 1,
                 1, -8, 1,
                 1, 1, 1);
    int sum = 0;
    
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            sum += img_origin.at<uchar>(x+i, y+j) * maskX.at<double>(1+i, 1+j);
        }
    }
    
    return sum;
}
int getLapPix3(Mat img_origin, int x, int y){
    Mat maskX = (Mat_<double>(3, 3) << 0, -1, 0,
                 -1, 4, -1,
                 0, -1, 0);
    int sum = 0;
    
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            sum += img_origin.at<uchar>(x+i, y+j) * maskX.at<double>(1+i, 1+j);
        }
    }
    
    return sum;
}
int getLapPix4(Mat img_origin, int x, int y){
    Mat maskX = (Mat_<double>(3, 3) << -1, -1, -1,
                 -1, 8, -1,
                 -1, -1, -1);
    int sum = 0;
    
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            sum += img_origin.at<uchar>(x+i, y+j) * maskX.at<double>(1+i, 1+j);
        }
    }
    
    return sum;
}

