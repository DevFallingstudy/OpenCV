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
#include <stdlib.h>

#define    ABS(x)            ( ((x)<0)?-(x):(x) )    // 절대 값

using namespace cv;
using namespace std;

void medianFilter();

void smoothingImage();
int getMedian(int pix[], int size);
int* bubbleSort(int pix[], int size);

int main(int argc, const char * argv[]) {
    smoothingImage();
    return 0;
}

void smoothingImage(){
    string imageName("./lena_noise.png");
    Mat image, image_gray, image_resize, image_result;
    int width=0, height=0;
    int size_frame, padding;
    int pix;
    int idx = 0;
    int min, max, median;
    int* pix_array;
    
    image = imread(imageName.c_str(), IMREAD_COLOR);
    
    if (image.empty()) {
        cout << "Could not open or find image : " << imageName << std::endl;
        return;
    }else{
        cout << "Enter the size of frame : ";
        cin >> size_frame;
        
        padding = size_frame-3+1;
        
        cvtColor(image, image_gray, CV_BGR2GRAY);
        width = image_gray.size().width;
        height = image_gray.size().height;
        
        cv::resize(image_gray, image_resize, cv::Size(width+padding, height+padding), 0, 0, CV_INTER_NN);
        
        image_result = Mat::zeros(width, height, image_gray.type());
        
        min = -(size_frame/2);
        max = -min;
        
        pix_array = (int*)malloc(sizeof(int)*size_frame);
        
        for (int i = 0; i < size_frame; i++) {
            pix_array[i] = 0;
        }
        
        for (int x = 1; x < width; x++) {
            for (int y = 1; y < height; y++) {
                idx = 0;
                for (int i = min; i < max; i++) {
                    for (int j = min; j < max; j++) {
                        pix = image_gray.at<uchar>(x+i, y+j);
                        pix_array[idx] = image_gray.at<uchar>(x+i, y+j);
                        idx++;
                    }
                }
                median = getMedian(pix_array, size_frame);
                image_result.at<uchar>(x, y) = saturate_cast<uchar>(median);
            }
        }
        
        namedWindow("Result", CV_WINDOW_AUTOSIZE);
        namedWindow("Origin", CV_WINDOW_AUTOSIZE);
        
        imshow("Result", image_result);
        imshow("Origin", image_gray);
    }
    
    waitKey(0);
}

int getMedian(int pix[], int size) {
    int *srt_pix = bubbleSort(pix, size);
    int median = srt_pix[4];
    
    return median;
}

int* bubbleSort(int pix[], int size){
    for (int i = 0; i < (size*size)-1; i++) {
        for (int j = 1; j < size*size; j++) {
            if (i == j) {
                continue;
            }else if (pix[i] < pix[j]){
                int tmp;
                tmp = pix[i];
                pix[i] = pix[j];
                pix[j] = tmp;
            }
        }
    }
    
    return pix;
}
