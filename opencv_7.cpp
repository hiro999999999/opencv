//Cで書いた３x３の移動平均オペレータ。OpenCVの答え合わせ付
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
    img_dst = img_gray.clone();
    double op[3][3] = { { 1.0/9.0, 1.0/9.0, 1.0/9.0 },
                        { 1.0/9.0, 1.0/9.0, 1.0/9.0 },
                        { 1.0/9.0, 1.0/9.0, 1.0/9.0 } };
    std::cout << "op "<< op << std::endl;
    for( int y = 0; y < img_gray.rows; y++){
        for( int x = 0; x < img_gray.cols; x++ ){
            int sum = 0;
            for( int i = -1; i <= 1; i++ ){
                if( y + i < 0 ) continue;
                if( y + i >= img_gray.rows ) break;
                for( int j = -1; j <= 1; j++ ){
                    if( x + j < 0 ) continue;
                    if( x + j >= img_gray.cols ) break;
                    sum += img_gray.data[ (y+i)*img_gray.step + (x + j)*img_gray.channels() ]*op[i+1][j+1];                    
                }
            }
            img_dst.data[ y*img_dst.step + x*img_dst.channels() ] = sum;
        }
    }
    blur( img_gray, img_gray, Size(3,3) );
    ////////////
    
    imshow( win_src, img_src );
    imshow( win_gray, img_gray );
    imshow( win_dst, img_dst );
    imwrite( file_gray, img_gray );
    imwrite( file_dst, img_dst );

    waitKey(0);
    return 0;
}