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
Mat getHistogramImage(Mat* img);
void smoothingFunc(string imgName);

int main(int argc, const char * argv[]) {
    equalizeHistFunc("Lenna.png");
//    smoothingFunc("Gray_Lenna.png");
    
    return 0;
}

void equalizeHistFunc(string imgName) {
    // Variables for image show
    string imageName(imgName);
    Mat img, img_gray;
    Mat img_result;
    
    // Variables for Histogram
    Mat histImg1, histImg2;
    
    // Show images
    img = imread(imageName.c_str(), IMREAD_COLOR);
    
    cvtColor(img, img_gray, CV_BGR2GRAY);
    equalizeHist(img_gray, img_result);
    
    imshow("Original Gray", img_gray);
    imshow("Result", img_result);
    
    histImg1 = getHistogramImage(&img_gray);
    histImg2 = getHistogramImage(&img_result);
    
    namedWindow("Histogram Result", WINDOW_AUTOSIZE);
    namedWindow("Histogram Original", WINDOW_AUTOSIZE);
    imshow("Histogram Result", histImg2);
    imshow("Histogram Original", histImg1);
    waitKey(0);
    
}

Mat getHistogramImage(Mat* img) {
    int histSize = 256;
    float range[] = { 0, 256 } ;
    const float* histRange = { range };
    bool uniform = true, accumulate = false;
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double) hist_w / histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));
    Mat b_hist;
    
    calcHist( img, 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );
    normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
    
    for (int i = 1; i < histSize; i++) {
        line( histImage, Point( bin_w*(i-1), hist_h - cvRound(b_hist.at<float>(i-1)) ) , Point( bin_w*(i), hist_h - cvRound(b_hist.at<float>(i)) ), Scalar( 255, 0, 0), 2, 8, 0 );
    }
    
    return histImage;
}

void smoothingFunc(string imgName) {
    string imageName(imgName);
    Mat img;
    Mat img_result;
    int width, height;
    
    img = imread(imageName.c_str(), IMREAD_GRAYSCALE);
    
    
}
