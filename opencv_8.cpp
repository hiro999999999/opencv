//組織的ディザリング
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

    //ディザ行列
    img_dst = img_gray.clone();
    int diz[4][4] = { {  0,  8,  2, 10 },
                      { 12,  4, 14,  6 },
                      {  3, 11,  1,  9 },
                      { 15,  7, 13,  5 } };
    int coefficient = 1;
    for( int y = 0; y < img_gray.rows; y++ ){
        for( int x = 0; x < img_gray.cols; x++ ){
            if( img_gray.data[ y*img_gray.step + x*img_gray.channels() ] < diz[y%4][x%4]*16 ) coefficient = 0;
            else coefficient = 1;
            img_dst.data[ y*img_dst.step + x*img_dst.channels() ] = coefficient*255;
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