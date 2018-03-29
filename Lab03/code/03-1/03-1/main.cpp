//
//  main.cpp
//  03-1
//
//  Created by Fallingstar on 2018. 3. 29..
//  Copyright © 2018년 Fallingstar. All rights reserved.
//

// DIO : The WORLD!!!!!!!!!!!!!

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

void equalizeHistFunc(string imgName);
void smoothingFunc(string imgName);

int main(int argc, const char * argv[]) {
    equalizeHistFunc("TheWorld.jpg");
//    smoothingFunc("Gray_Lenna.png");
    
    return 0;
}

void equalizeHistFunc(string imgName) {
    // Variables for image show
    string imageName(imgName);
    Mat img, img_gray;
    Mat img_result;
    
    // Variables for Histogram
    int histSize = 256;
    float range[] = { 0, 256 } ;
    const float* histRange = { range };
    bool uniform = true;
    bool accumulate = false;
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w / histSize);
    Mat histImage1(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
    Mat histImage2(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
    Mat b_hist1, b_hist2;
    
    // Show images
    img = imread(imageName.c_str(), IMREAD_COLOR);
    
    cvtColor(img, img_gray, CV_BGR2GRAY);
    equalizeHist(img_gray, img_result);
    
    imshow("Original Gray", img_gray);
    imshow("Result", img_result);
//    waitKey(0);
    
    
    // Show Histogram - Original
    calcHist( &img_gray, 1, 0, Mat(), b_hist1, 1, &histSize, &histRange, uniform, accumulate );
    normalize(b_hist1, b_hist1, 0, histImage1.rows, NORM_MINMAX, -1, Mat());
    
    for (int i = 1; i < histSize; i++) {
        line( histImage1, Point( bin_w*(i-1), hist_h - cvRound(b_hist1.at<float>(i-1)) ) , Point( bin_w*(i), hist_h - cvRound(b_hist1.at<float>(i)) ), Scalar( 255, 0, 0), 2, 8, 0 );
    }
    
    // Show Histogram - Result
    calcHist( &img_result, 1, 0, Mat(), b_hist2, 1, &histSize, &histRange, uniform, accumulate );
    normalize(b_hist2, b_hist2, 0, histImage2.rows, NORM_MINMAX, -1, Mat());
    
    for (int i = 1; i < histSize; i++) {
        line( histImage2, Point( bin_w*(i-1), hist_h - cvRound(b_hist2.at<float>(i-1)) ) , Point( bin_w*(i), hist_h - cvRound(b_hist2.at<float>(i)) ), Scalar( 255, 0, 0), 2, 8, 0 );
    }
    
    namedWindow("Histogram Result", WINDOW_AUTOSIZE);
    namedWindow("Histogram Original", WINDOW_AUTOSIZE);
    imshow("Histogram Result", histImage2);
    imshow("Histogram Original", histImage1);
    waitKey(0);
    
}

void smoothingFunc(string imgName) {
    string imageName(imgName);
    Mat img;
    Mat img_result;
    int width, height;
    
    img = imread(imageName.c_str(), IMREAD_GRAYSCALE);
    
    
}
