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
    Mat img_gray;
    cvtColor( img_src, img_gray, COLOR_BGR2GRAY );

    namedWindow( win_src, WINDOW_AUTOSIZE );
    namedWindow( win_gray, WINDOW_AUTOSIZE );
    namedWindow( win_dst, WINDOW_AUTOSIZE );

    //ここに書く
    int height   = img_gray.rows,
        width    = img_gray.cols,
        step     = img_gray.step,
        channels = img_gray.channels(),
        src_channels = img_src.channels();
    int left_right_extention = 70,
        top_bottom_extention = 70;
    int value = 255;
    Mat img_dst( height + 2*top_bottom_extention, width+2*left_right_extention, img_src.type(), Scalar( 255, 255, 255) );

    for( int y = 0; y < height; y++ ){
        for( int x = 0; x < width; x++ ){
            for(int i = 0; i < src_channels; i++ ){
                img_dst.data[ ( y + top_bottom_extention )*img_dst.step + ( x + left_right_extention )*img_dst.channels() + i ] = img_src.data[ y*img_src.step + x*img_src.channels() + i ];
            }
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