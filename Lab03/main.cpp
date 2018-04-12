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

#define    ABS(x)            ( ((x)<0)?-(x):(x) )    // 절대 값

using namespace cv;
using namespace std;

void smoothingImage();
int getAverage(Mat img_origin, int x, int y, int size);
int getGaussian(Mat img_origin, int x, int y, int size, float sigma);

int main(int argc, const char * argv[]) {
    smoothingImage();
    return 0;
}

void smoothingImage(){
    string imageName("./Lena_color.png");
    Mat image, image_gray, image_resize, image_result;
    int width=0, height=0;
    int size_frame, padding;
    float sigma=0;
    int code = 0;
    
    image = imread(imageName.c_str(), IMREAD_COLOR);
    
    if (image.empty()) {
        cout << "Could not open or find image : " << imageName << std::endl;
        return;
    }else{
        
        do {
            cout << "Enter the mode(1:Avg, 2:Gaus) : ";
            cin >> code;
        } while (!(1 <= code && code <= 2));
        
        do {
            cout << "Enter the size of frame(odd number) : ";
            cin >> size_frame;
        } while ((size_frame%2 == 0) || (size_frame < 3));
        
        if (code == 2) {
            cout << "Enter the constant for multiply(Gaus) : ";
            cin >> sigma;
        }
        
        padding = size_frame-3+1;
        
        cvtColor(image, image_gray, CV_BGR2GRAY);
        width = image_gray.size().width;
        height = image_gray.size().height;
        
        cv::resize(image_gray, image_resize, cv::Size(width+padding, height+padding), 0, 0, CV_INTER_NN);
        
        image_result = Mat::zeros(width, height, image_gray.type());
        
        if (code == 1) {
            for (int x = 1; x < width; x++) {
                for (int y = 1; y < height; y++) {
                    image_result.at<uchar>(x, y) = getAverage(image_gray, x, y, size_frame);
                }
            }
        }else{
            for (int x = 1; x < width; x++) {
                for (int y = 1; y < height; y++) {
                    image_result.at<uchar>(x, y) = getGaussian(image_gray, x, y, size_frame, sigma);
                }
            }
        }
        
        namedWindow("Result", CV_WINDOW_AUTOSIZE);
        namedWindow("Origin", CV_WINDOW_AUTOSIZE);
        
        imshow("Result", image_result);
        imshow("Origin", image_gray);
    }
    
    waitKey(0);
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

int getGaussian(Mat img_origin, int x, int y, int size, float sigma) {
    int sum = 0;
    int avg = 0;
    int max, min;
    float coef;
    float coefSum = 0;
    int xMulti=0, yMulti=0;
    
    max = size/2;
    min = -(size/2);
    
    for (int i = min; i <= max; i++) {
        yMulti = ABS(i);
        for (int j = min; j <= max; j++) {
            xMulti = ABS(j);
            coef = 1.0/(3.14*2*pow(sigma, 2)) * (pow(2.71, (-((pow(xMulti, 2) + pow(yMulti, 2))))/(2*pow(sigma, 2))));
            coefSum += coef;
            
            sum += img_origin.at<uchar>(x+i, y+j) * coef;
        }
    }
    
    avg = sum/coefSum;
    
    return avg;
}
