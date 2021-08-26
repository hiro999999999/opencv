//
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
using namespace cv;
int main(){
    std::string win_src = "src";
    std::string win_dst = "dst";
    std::string file_src = "src.png";
    std::string file_dst = "dst.png";
    Mat img_src =  imread( file_src, 1 );
    Mat img_dst;

    namedWindow( win_src, WINDOW_AUTOSIZE );
    namedWindow( win_dst, WINDOW_AUTOSIZE );

    //ここに書く
    Mat img_gray;
    cvtColor( img_src, img_gray, COLOR_BGR2GRAY );
    GaussianBlur(img_gray,img_dst, Size(55, 55), 1);
    ////////////
    
    imshow( win_src, img_src );
    imshow( win_dst, img_gray );
    imwrite( file_dst, img_dst );

    waitKey(0);
    return 0;
}