//中央値フィルタ
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

    Mat img_dst;

    namedWindow( win_src, WINDOW_AUTOSIZE );
    namedWindow( win_gray, WINDOW_AUTOSIZE );
    namedWindow( win_dst, WINDOW_AUTOSIZE );

    //ここに書く
    Mat img_spiked;
    img_spiked = img_gray.clone();
    int height_spiked = img_spiked.rows,
        width_spiked = img_spiked.cols,
        step_spiked = img_spiked.step,
        channels_spiked = img_spiked.channels();
    for( int y = 0; y < height_spiked; y++ ){
        for( int x = 0; x < width_spiked; x++ ){
            if( ( y*step_spiked + x*channels_spiked )%500 == 0 ){
                img_spiked.data[ y*step_spiked + x*channels_spiked ] = 0;
            }
        }
    }

    img_dst = img_spiked.clone();
    ////////////
    
    imshow( win_src, img_src );
    imshow( win_gray, img_gray );
    imshow( win_dst, img_dst );
    imwrite( file_gray, img_gray );
    imwrite( file_dst, img_dst );

    waitKey(0);
    return 0;
}