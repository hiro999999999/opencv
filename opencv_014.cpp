//ブロブのバウンディングボックス 入力は２値化済み画像
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
    
    int height   = img_gray.rows,
        width    = img_gray.cols,
        step     = img_gray.step,
        channels = img_gray.channels();
    int operator_results[step*height];
    int xmin =  1e8,
        xmax = -1e8,
        ymin = xmin,
        ymax = xmax;
    for( int y = 0; y < height; y++ ){
        for( int x = 0; x < width; x++ ){
            if( img_gray.data[ y*step + x*channels ] == 255 ){
                if( x < xmin ) xmin = x;
                if( x > xmax ) xmax = x;
                if( y < ymin ) ymin = y;
                if( y > ymax ) ymax = y;
            }
        }
    }
    double ashi = ( ( double )( ymax - ymin ) )/( xmax - xmin );
    for( int y = 0; y < height; y++ ){
        for( int x = 0; x < width; x++ ){
            if( ( ( y == ymin || y == ymax ) && ( x >= xmin && x <= xmax ) ) || 
                ( ( x == xmin || x == xmax ) && ( y >  ymin && y <  ymax ) )   ){
                     img_gray.data[ y*step + x*channels ] = 255;
                    //std::cout << "( " << x << ", " << y << " )" << std::endl;
                }
        }
    }
    std::cout << "( " << xmin << ", " << ymin << " )" << " -> " << "( " << xmax << ", " << ymax << " )" << std::endl;
    cvtColor( img_src, img_dst, COLOR_BGR2GRAY );
    Rect rect = boundingRect( img_dst );
    double ashi_cv = ( double )( rect.height )/rect.width;
    rectangle( img_dst, rect, 255 );
    std::cout << "aspect ratio" << std::endl << "yours: " << ashi << std::endl << "correct: " << ashi_cv << std::endl;
    ////////////
    
    imshow( win_src, img_src );
    imshow( win_gray, img_gray );
    imshow( win_dst, img_dst );
    imwrite( file_gray, img_gray );
    imwrite( file_dst, img_dst );

    waitKey(0);
    return 0;
}