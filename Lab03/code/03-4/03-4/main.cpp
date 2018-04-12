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

void getGradientMagnitudeMap();
Mat getG(Mat img_origin, int x, int y);
int getGx(Mat img_origin, int x, int y);
int getGy(Mat img_origin, int x, int y);

int main(int argc, const char * argv[]) {
    getGradientMagnitudeMap();
    return 0;
}

void getGradientMagnitudeMap(){
    string imageName("./Lena_color.png");
    Mat image, image_gray, image_resize, image_result;
    int width=0, height=0;
    
    image = imread(imageName.c_str(), IMREAD_COLOR);
    
    if (image.empty()) {
        cout << "Could not open or find image : " << imageName << std::endl;
        return;
    }else{
        cvtColor(image, image_gray, CV_BGR2GRAY);
        
        width = image_gray.size().width;
        height = image_gray.size().height;
        
        image_result = getG(image_gray, width, height);
        
        namedWindow("Result", CV_WINDOW_AUTOSIZE);
        namedWindow("Origin", CV_WINDOW_AUTOSIZE);
        
        imshow("Result", image_result);
        imshow("Origin", image_gray);
        
        waitKey(0);
    }
}

Mat getG(Mat img_origin, int width, int height){
    float Gx, Gy;
    Mat G;
    int pix;
    
    G = Mat::zeros(width+1, height+1, img_origin.type());
    
    // Get G
    for (int x = 1; x < width; x++) {
        for (int y = 1; y < height; y++) {
            Gx = getGx(img_origin, x, y);
            Gy = getGy(img_origin, x, y);
            pix = sqrt(pow(Gx, 2)+pow(Gy, 2));
            G.at<uchar>(x, y) = saturate_cast<uchar>(pix);
        }
    }
    
    return G;
}

int getGx(Mat img_origin, int x, int y){
    Mat maskX = (Mat_<double>(3, 3) << 1, 0, -1, 2, 0, -2, 1, 0, -1);
    int sum = 0;
    
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            sum += img_origin.at<uchar>(x+i, y+j) * maskX.at<double>(1+i, 1+j);
        }
    }
    
    return sum;
}

int getGy(Mat img_origin, int x, int y){
    Mat maskY = (Mat_<double>(3, 3) << 1, 2, 1, 0, 0, 0, -1, -2, -1);
    int sum = 0;
    
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            sum += img_origin.at<uchar>(x+i, y+j) * maskY.at<double>(1+i, 1+j);
        }
    }
    return sum;
}

