//
//  main.cpp
//  Lab01-LoadImage
//
//  Created by Fallingstar on 2018. 3. 15..
//  Copyright © 2018년 Fallingstar. All rights reserved.
//

// Headers for OpenCV
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>

// Headers for default
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

void showWithsaturate();
void showWithLinearBlending();

int main(int argc, const char * argv[]) {
    showWithsaturate();
    showWithLinearBlending();
    
    return 0;
}


void showWithsaturate(){
    string imageName("./kawaii.jpg");
    Mat image, new_image;
    int width=0, height=0;
    float alpha=2.2, beta=10;
    
    image = imread(imageName.c_str(), IMREAD_COLOR);
    
    if (image.empty()) {
        cout << "Could not open or find image : " << imageName << std::endl;
        return ;
    }else{
        width = image.size().width;
        height = image.size().height;
        
        cout << "Enter the alpha value : ";
        cin >> alpha;
        cout << "Enter the beta value : ";
        cin >> beta;
        
        new_image = Mat::zeros(height, width, image.type());
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                for (int i = 0; i < 3; i++) {
                    new_image.at<Vec3b>(y, x)[i] = saturate_cast<uchar>( alpha * (image.at<Vec3b>(y, x)[i] + beta));
                }
            }
        }
        
        namedWindow("YYS1", WINDOW_AUTOSIZE);
        namedWindow("YYS2", WINDOW_AUTOSIZE);
        imshow("YYS1", image);
        imshow("YYS2", new_image);
        waitKey(0);
        destroyWindow("YYS1");
        destroyWindow("YYS2");
    }
}

void showWithLinearBlending() {
    string imageName1("./kawaii.jpg"), imageName2("./Torr.jpg");
    Mat image1, image2, fin_image;
    float alpha = 0.2;
    
    image1 = imread(imageName1.c_str(), IMREAD_COLOR);
    image2 = imread(imageName2.c_str(), IMREAD_COLOR);
    
    fin_image = Mat::zeros(720, 1280, image1.type());
    for (int x = 0; x < 1280; x++) {
        for (int y = 0; y < 720; y++) {
            for (int i = 0; i < 3; i++) {
                fin_image.at<Vec3b>(y, x)[i] = saturate_cast<uchar>(
                                                                    (alpha * image1.at<Vec3b>(y, x)[i]) +
                                                                    ((1-alpha) * image2.at<Vec3b>(y, x)[i]) );
            }
        }
    }
    namedWindow("YYS", WINDOW_AUTOSIZE);
    imshow("YYS", fin_image);
    waitKey(0);
}
