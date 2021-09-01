//外枠生成するやつ
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
    Mat img_dst;
    Mat img_gray;
    cvtColor( img_src, img_gray, COLOR_BGR2GRAY );

    namedWindow( win_src, WINDOW_AUTOSIZE );
    namedWindow( win_gray, WINDOW_AUTOSIZE );
    namedWindow( win_dst, WINDOW_AUTOSIZE );

    //ここに書く
    int height   = img_gray.rows,
        width    = img_gray.cols,
        step     = img_gray.step,
        channels = img_gray.channels();
    int left_right_extention = 70,
        top_bottom_extention = 70;
    int value = 0;
    img_dst = Mat::ones( Size( width+2*left_right_extention, height + 2*top_bottom_extention ), CV_8U )*value;
    for( int y = 0; y < height; y++ ){
        for( int x = 0; x < width; x++ ){
            img_dst.data[ ( y + top_bottom_extention )*img_dst.step + ( x + left_right_extention )*img_dst.channels() ] = img_gray.data[ y*step + x*channels ];
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