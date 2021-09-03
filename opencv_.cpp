//輪郭追跡
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
int main(){
    std::string win_src = "src";
    std::string win_gray = "gray";
    std::string win_bi = "bi";
    std::string win_brd = "brd";
    std::string win_dst = "dst";
    std::string file_src  = "src.png";
    std::string file_gray = "gray.png";
    std::string file_bi   = "bi.png";
    std::string file_brd  = "brd.png";
    std::string file_dst  = "dst.png";
    Mat img_src =  imread( file_src, 1 );
    Mat img_gray;
    cvtColor( img_src, img_gray, COLOR_BGR2GRAY );

    //ここに書く
    const int height   = img_gray.rows,
              width    = img_gray.cols,
              step     = img_gray.step,
              channels = img_gray.channels();
    int operator_results[step*height];
    Mat img_dst = img_src.clone();

    //2値化　→　クロージング処理　→　オープニング処理
    Mat img_bi = img_gray.clone(); 
    Mat img_tmp_0, img_tmp_1;
    Mat element8 = (Mat_<uchar>(3, 3) << 1, 1, 1, 1, 1, 1, 1, 1, 1 );
    threshold( img_gray, img_tmp_0, 220, 255, THRESH_BINARY_INV );
    morphologyEx( img_tmp_0, img_tmp_1, MORPH_CLOSE, element8, Point(-1, -1), 1 );
    morphologyEx( img_tmp_1, img_bi, MORPH_OPEN, element8, Point(-1, -1), 1 );

    //ラスタスキャン
    bool found_starting_point = false;
    for( int y = 0; y < height; y++ ){
        for( int x = 0; x < width; x++ ){
            
        }
    }
    ////////////
    imshow( win_src, img_src ); 
    imshow( win_bi, img_bi );
    imshow( win_gray, img_gray );   
    imshow( win_dst, img_dst );
    imwrite( file_gray, img_gray );
    imwrite( file_bi, img_bi );
    imwrite( file_dst, img_dst );

    waitKey(0);
    return 0;
}