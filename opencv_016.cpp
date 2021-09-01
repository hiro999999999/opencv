//輪郭追跡
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
using namespace cv;
int main(){
    std::string win_src = "src";
    std::string win_gray = "gray";
    std::string win_dst = "dst";
    std::string file_src = "src.png";
    std::string file_gray = "gray.png";
    std::string file_dst = "dst.png";
    Mat img_src =  imread( file_src, 1 );
    Mat img_gray;
    cvtColor( img_src, img_gray, COLOR_BGR2GRAY );
    Mat img_dst = img_gray.clone();

    namedWindow( win_src, WINDOW_AUTOSIZE );
    namedWindow( win_gray, WINDOW_AUTOSIZE );
    namedWindow( win_dst, WINDOW_AUTOSIZE );

    //ここに書く
    int height   = img_gray.rows,
        width    = img_gray.cols,
        step     = img_gray.step,
        channels = img_gray.channels();
    int operator_results[step*height];
    float d = sqrt(2);
    float a = (d*cos(M_PI/4));
    int a_int = (int)a;
    std::cout << "d = " << a_int << std::endl;
    for( int y = 0; y < height; y++ ){
        for( int x = 0; x < width; x++ ){
        }
    }
    ////////////
    
    imshow( win_src, img_src );
    imshow( win_gray, img_gray );
    imshow( win_dst, img_dst );
    imwrite( file_gray, img_gray );
    imwrite( file_dst, img_dst );

    waitKey(0);
    return 0;
}