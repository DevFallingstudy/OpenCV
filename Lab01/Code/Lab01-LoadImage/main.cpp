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

int main(int argc, const char * argv[]) {
    string imageName("./kawaii.jpg");
    Mat image;
    
    if (argc > 1) {
        imageName = argv[1];
    }else{
        //Do nothing
    }
    
    image = imread(imageName.c_str(), IMREAD_COLOR);
    if (image.empty()) {
        cout << "Could not open or find image : " << imageName << std::endl;
        return -1;
    }else{
        namedWindow("YYS", WINDOW_AUTOSIZE);
        imshow("ABC", image);
        waitKey(0);
    }
    
    
    return 0;
}
