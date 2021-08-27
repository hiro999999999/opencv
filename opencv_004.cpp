//Look Up Table
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
    double gamma = 0.5;
    Mat lut( 256, 1, CV_8U );
    for(int i = 0; i < 256; i++ ){
        lut.data[i] = ( unsigned char )( 255.0*std::pow( i/255.0, 1.0/gamma ) );
    }
    //LUT( img_gray, lut, img_dst );
    img_gray.convertTo( img_dst, img_gray.type(), -1.0, 255.0 );

    ////////////
    
    imshow( win_src, img_src );
    imshow( win_dst, img_dst );
    imwrite( file_dst, img_dst );

    waitKey(0);
    return 0;
}