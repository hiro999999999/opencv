//ヒストグラム
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

    //koko
    Mat img_hst;
    img_hst = Mat::zeros( 100, 256, CV_8UC1 );
    const int hdims[] = {255};
    const float hranges[] = {0, 255};
    const float* ranges[] = {hranges};
    Mat hist;
    cvtColor( img_src, img_dst, COLOR_BGR2GRAY );
    calcHist( &img_dst, 1, 0, Mat(), hist, 1, hdims, ranges );

    double hist_min, hist_max;
    minMaxLoc( hist, &hist_min, &hist_max );

    for( int i = 0; i <= 255; i++ ){
        int v = saturate_cast<int>( hist.at<float>(i) );
        std::cout << i << " " << v << std::endl;
        line( img_hst, Point( i, img_hst.rows ), Point( i, img_hst.rows - img_hst.rows*( v/hist_max ) ), Scalar( 255, 255, 255 ) ); 
    }
    namedWindow( "hist", WINDOW_AUTOSIZE );
    imshow( "hist", img_hst );

    imshow( win_src, img_src );
    imshow( win_dst, img_dst );
    imwrite( file_dst, img_dst );

    waitKey(0);
    return 0;
}