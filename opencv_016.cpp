//輪郭追跡
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
using namespace cv;
int main(){
    std::string win_src = "src";
    std::string win_gray = "gray";
    std::string win_bi = "bi";
    std::string win_brd = "brd";
    std::string win_dst = "dst";
    std::string file_src = "src.png";
    std::string file_gray = "gray.png";
    std::string file_dst = "dst.png";
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
    Point starting_point, current_point;
    bool found_starting_point = false;
    for( int y = 0; y < height; y++ ){
        for( int x = 0; x < width; x++ ){
            if( img_bi.data[ y*step + x*channels ] == 255 && !found_starting_point ){ 
                starting_point = Point( x, y );
                found_starting_point = true;
            }
        }
    }

    //輪郭追従
    const double angle_rate    = M_PI/4;
    const int    circle_radius = 3;
    int x0 = starting_point.x,
        y0 = starting_point.y;
    bool tracked[width][height];
    for( int i = 0; i < height; i++ ) for( int j = 0; j < width; j++ ) tracked[j][i] = false;
    tracked[starting_point.x][starting_point.y] = true;
    Mat img_brd( height, width, CV_8U, Scalar( 0, 0, 0 ) );
    circle( img_brd, starting_point, circle_radius, 255, -1, 8 );
    int dir_id = -3;
    double d;
    bool contour_tracked = false;
    while( !contour_tracked ){
        int counter = 0;
        bool found_next_pixel = false;
        while( !found_next_pixel ){
             counter++;
            dir_id++;
            if( dir_id > 7 ) dir_id -= 8;
            else if( dir_id < 0 ) dir_id += 8;
            if( dir_id%2 == 0 ) d = 1;
            else                d = sqrt(2);
            float dx_float = - d*cos(angle_rate*dir_id),
                  dy_float =   d*sin(angle_rate*dir_id);
            int   dx = (int)dx_float,
                  dy = (int)dy_float;
            int x = x0 + dx,
                y = y0 + dy;
            if( img_bi.data[ y*step + x*channels ] == 255 ){
                x0 = x;
                y0 = y;
                dir_id += 4;
                current_point = Point( x,y );
                tracked[x][y] = true;
                circle( img_brd, current_point, circle_radius, 255, -1, 8 );
                found_next_pixel = true;
            }
            if( counter > 8 ) break;
        }
        if( current_point == starting_point && tracked[x0][y0] ) contour_tracked = true;
    }

    //ソース画像加工
    for( int y = 0; y < height; y++ ){ 
        for( int x = 0; x < width; x++ ){
            if( img_brd.data[ y*step + x*channels ] > 0 )  {
                for( int i = 0; i < img_dst.channels(); i++ ){
                    if( i == 0 )img_dst.data[ y*img_dst.step + x*img_dst.channels() + i ] = 255;
                    else img_dst.data[ y*img_dst.step + x*img_dst.channels() + i ] = 0;
                }
            }
        } 
    }
    ////////////
    
    imshow( win_src, img_src );
    imshow( win_gray, img_gray );
    imshow( win_bi, img_bi );
    imshow( win_brd, img_brd );
    imshow( win_dst, img_dst );
    imwrite( file_gray, img_gray );
    imwrite( file_dst, img_dst );

    waitKey(0);
    return 0;
}