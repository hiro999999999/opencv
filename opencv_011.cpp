//先鋭化処理
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
    int k = 1;
    double op[3][3] = { { -1.0*k,  -1.0*k, -1.0*k },
                        { -1.0*k, 1+8.0*k, -1.0*k },
                        { -1.0*k,  -1.0*k, -1.0*k } };
    int height   = img_gray.rows,
        width    = img_gray.cols,
        step     = img_gray.step,
        channels = img_gray.channels();
    int max = log(0),
        min = 100000000000;
    Mat img_gray_clone = img_gray.clone();
    int operator_results[step*height];
    for( int y = 0; y < height; y++ ){
        for( int x = 0; x < width; x++ ){
            int sum = 0;
            for( int i = -1; i <= 1; i++ ){
                if( y + i < -1 ) continue;
                if( y + i > height ) continue;
                for( int j = -1; j <= 1; j++ ){
                    if( x + j < 0 ) continue;
                    if( x + j > width ) continue;
                    sum += img_gray.data[ ( y + i )*step + ( x + j )*channels ]*op[i+1][j+1];
                }
            }
            sum = abs(sum);
            if( sum > 255 ) sum = 255;
            
            img_gray_clone.data[ y*step + x*channels ] = sum;
            if( sum < min ) min = sum;
            if( sum > max ) {max = sum;std::cout << "sum " << sum << std::endl;}
        }
    }
    std::cout << "max " << max << " min" << min << std::endl;
    Mat img_tmp = img_gray.clone();
    Mat op1 = Mat::ones( 3, 3, CV_32F )*(-k);
    op1.at<float>(1,1) = 1 + 8*k;
    filter2D( img_gray, img_tmp, CV_32F, op1 );
    convertScaleAbs( img_tmp, img_dst, 1, 0 );
    ////////////
    
    imshow( win_src, img_src );
    imshow( win_gray, img_gray_clone );
    imshow( win_dst, img_dst );
    imwrite( file_gray, img_gray_clone );
    imwrite( file_dst, img_dst );

    waitKey(0);
    return 0;
}