//画素単位で画像いじる
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

    //ここに書く
    img_dst = img_src.clone();
    std::cout << "channels" << img_dst.channels() << std::endl;
    for( int i = 0; i < img_dst.rows; i++ ){
        for( int j = 0; j < img_dst.cols; j++ ){
            img_dst.data[ j*img_dst.step + i*img_dst.channels() + 2] = 0;
            img_dst.data[ j*img_dst.step + i*img_dst.channels()] = 255;
        }
    }
    ////////////

    namedWindow( win_src, WINDOW_AUTOSIZE );
    namedWindow( win_dst, WINDOW_AUTOSIZE );    
    imshow( win_src, img_src );
    imshow( win_dst, img_dst );
    imwrite( file_dst, img_dst );

    waitKey(0);
    return 0;
}