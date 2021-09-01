//オープニング処理とクロージング処理
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
using namespace cv;
int main(){
    std::string win_src = "src";
    std::string win_gray   = "gray",
                win_gray_1 = "gray_1",
                win_gray_2 = "gray_2",
                win_gray_3 = "gray_3",
                win_gray_4 = "gray_4";
    std::string win_tmp = "tmp";
    std::string win_dst = "dst";
    std::string file_src = "src.png";
    std::string file_gray = "gray.png";
    std::string file_dst = "dst.png";
    Mat img_src =  imread( file_src, 1 );
    Mat img_gray;
    cvtColor( img_src, img_gray, COLOR_BGR2GRAY );
    Mat img_dst = img_gray.clone();

    //namedWindow( win_src, WINDOW_AUTOSIZE );
    //namedWindow( win_dst, WINDOW_AUTOSIZE );

    //ここに書く
    int thresh = 220;
    int height   = img_gray.rows,
        width    = img_gray.cols,
        step     = img_gray.step,
        channels = img_gray.channels();
    Mat img_gray_1 = img_gray.clone();
    for( int y = 0; y < height; y++ ){
        for( int x = 0; x < width; x++ ){
            if( img_gray.data[ y*img_gray.step + x*img_gray.channels() ] < thresh  ) img_gray_1.data[ y*img_gray.step + x*img_gray.channels() ] = 255;
            else img_gray_1.data[ y*img_gray.step + x*img_gray.channels() ] = 0; 
        }
    }
    //クロージング処理
    std::cout << "クロージング処理" << std::endl;
    Mat img_gray_2 = img_gray_1.clone();
    ////膨張処理
    std::cout << "  膨張処理" << std::endl;
    for( int y = 1; y < height; y++ ){
        for( int x = 0; x < width; x++ ){
            if( img_gray_1.data[ y*img_gray.step + (x-1)*img_gray.channels() ]     == 255 ||
                img_gray_1.data[ y*img_gray.step + (x+1)*img_gray.channels() ]     == 255 ||  
                img_gray_1.data[ (y-1)*img_gray.step + x*img_gray.channels() ]     == 255 || 
                img_gray_1.data[ (y-1)*img_gray.step + (x-1)*img_gray.channels() ] == 255 || 
                img_gray_1.data[ (y-1)*img_gray.step + (x+1)*img_gray.channels() ] == 255 || 
                img_gray_1.data[ (y+1)*img_gray.step + x*img_gray.channels() ]     == 255 || 
                img_gray_1.data[ (y+1)*img_gray.step + (x+1)*img_gray.channels() ] == 255 ||  
                img_gray_1.data[ (y+1)*img_gray.step + (x-1)*img_gray.channels() ] == 255 || 
                img_gray_1.data[ y*img_gray.step + x*img_gray.channels() ]         == 255   
              ) img_gray_2.data[ y*img_gray.step + x*img_gray.channels() ] = 255;
            else img_gray_2.data[ y*img_gray.step + x*img_gray.channels() ] = img_gray_1.data[ y*img_gray.step + x*img_gray.channels() ]; 
        }
    }
    ////収縮処理
    std::cout << "  収縮処理" << std::endl;
    Mat img_gray_3 = img_gray_2.clone();
    for( int y = 0; y < height; y++ ){
        for( int x = 0; x < width; x++ ){
            if(img_gray_2.data[ y*img_gray.step + (x-1)*img_gray.channels() ]      == 0 ||
                img_gray_2.data[ y*img_gray.step + (x+1)*img_gray.channels() ]     == 0 ||  
                img_gray_2.data[ (y-1)*img_gray.step + x*img_gray.channels() ]     == 0 || 
                img_gray_2.data[ (y-1)*img_gray.step + (x-1)*img_gray.channels() ] == 0 || 
                img_gray_2.data[ (y-1)*img_gray.step + (x+1)*img_gray.channels() ] == 0 || 
                img_gray_2.data[ (y+1)*img_gray.step + x*img_gray.channels() ]     == 0 || 
                img_gray_2.data[ (y+1)*img_gray.step + (x+1)*img_gray.channels() ] == 0 ||  
                img_gray_2.data[ (y+1)*img_gray.step + (x-1)*img_gray.channels() ] == 0 ||  
                img_gray_2.data[ y*img_gray.step + x*img_gray.channels() ]         == 0
              ) img_gray_3.data[ y*img_gray.step + x*img_gray.channels() ] = 0;
            else img_gray_3.data[ y*img_gray.step + x*img_gray.channels() ] = img_gray_2.data[ (y+1)*img_gray.step + x*img_gray.channels() ] ; 
        }
    }
    Mat img_gray_4  = img_gray_3.clone();
    std::cout << "オープニング処理" << std::endl;
    //オープニング処理
    ////収縮処理
    std::cout << "  収縮処理" << std::endl;
    for( int y = 0; y < height; y++ ){
        for( int x = 0; x < width; x++ ){
            if( 
                img_gray_3.data[ y*img_gray.step + (x-1)*img_gray.channels() ]     == 0 ||
                img_gray_3.data[ y*img_gray.step + (x+1)*img_gray.channels() ]     == 0 ||  
                img_gray_3.data[ (y-1)*img_gray.step + x*img_gray.channels() ]     == 0 || 
                img_gray_3.data[ (y-1)*img_gray.step + (x-1)*img_gray.channels() ] == 0 || 
                img_gray_3.data[ (y-1)*img_gray.step + (x+1)*img_gray.channels() ] == 0 || 
                img_gray_3.data[ (y+1)*img_gray.step + x*img_gray.channels() ]     == 0 || 
                img_gray_3.data[ (y+1)*img_gray.step + (x+1)*img_gray.channels() ] == 0 ||  
                img_gray_3.data[ (y+1)*img_gray.step + (x-1)*img_gray.channels() ] == 0 ||
                img_gray_3.data[ y*img_gray.step + x*img_gray.channels() ]         == 0
              ) img_gray_4.data[ y*img_gray.step + x*img_gray.channels() ] = 0;
            else img_gray_4.data[ y*img_gray.step + x*img_gray.channels() ] = img_gray_3.data[ (y+1)*img_gray.step + x*img_gray.channels() ]; 
        }
    }
    img_gray = img_gray_4.clone();
    ////膨張処理
    std::cout << "  膨張処理" << std::endl;
    for( int y = 1; y < height; y++ ){
        for( int x = 0; x < width; x++ ){
            std::cout << "y: " << y << " " << "x: " << x <<std::endl;
            if( img_gray_4.data[ y*img_gray.step + (x-1)*img_gray.channels() ]     == 255 ||
                img_gray_4.data[ y*img_gray.step + (x+1)*img_gray.channels() ]     == 255 ||  
                img_gray_4.data[ (y-1)*img_gray.step + x*img_gray.channels() ]     == 255 || 
                img_gray_4.data[ (y-1)*img_gray.step + (x-1)*img_gray.channels() ] == 255 || 
                img_gray_4.data[ (y-1)*img_gray.step + (x+1)*img_gray.channels() ] == 255 || 
                img_gray_4.data[ (y+1)*img_gray.step + x*img_gray.channels() ]     == 255 || 
                img_gray_4.data[ (y+1)*img_gray.step + (x+1)*img_gray.channels() ] == 255 ||  
                img_gray_4.data[ (y+1)*img_gray.step + (x-1)*img_gray.channels() ] == 255 ||  
                img_gray_4.data[ y*img_gray.step + x*img_gray.channels() ]         == 255
              ) img_gray.data[ y*img_gray.step + x*img_gray.channels() ] = 255;
            else img_gray.data[ y*img_gray.step + x*img_gray.channels() ] = img_gray_4.data[ y*img_gray.step + x*img_gray.channels() ]; 
        }
    }
    std::cout << "完了" << std::endl;
    Mat img_tmp;
    Mat elements = ( Mat_<uchar>(3,3) << 1,1,1,1,1,1,1,1,1 );
    morphologyEx( img_gray_1, img_tmp, MORPH_CLOSE, elements, Point( -1, -1 ), 1 );
    morphologyEx( img_tmp, img_dst, MORPH_OPEN, elements, Point( -1, -1 ), 1 );
    ////////////

    imshow( win_dst, img_dst );
    imshow( win_tmp, img_tmp );
    imshow( win_gray, img_gray );
    imshow( win_gray_4, img_gray_4 );
    imshow( win_gray_3, img_gray_3 );
    imshow( win_gray_2, img_gray_2 );
    imshow( win_gray_1, img_gray_1 );    
    imshow( win_src, img_src );
    imwrite( file_dst, img_dst );
    imwrite( file_gray, img_gray );
    waitKey(0);
    return 0;
}