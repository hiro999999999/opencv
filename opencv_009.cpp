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
                img_gray.data[ y*step_spiked + x*channels_spiked ] = 0;
            }
        }
    }
    img_dst = img_gray.clone();
    int values[9];
    for( int y = 0; y < img_gray.rows; y++){
        for( int x = 0; x < img_gray.cols; x++ ){
            int k = 0;
            for( int i = -1; i <= 1; i++ ){
                if( y + i < 0 ) continue;
                if( y + i >= img_gray.rows ) continue;
                for( int j = -1; j <= 1; j++ ){
                    if( x + j < 0 ) continue;
                    if( x + j >= img_gray.cols ) continue;
                    values[k++] =  img_gray.data[ (y+i)*img_gray.step + (x+j)*img_gray.channels() ];
                }
            }
            for(int i = 0; i < 9; i++ ) std::cout << values[i] << " ";
            for( int i = 0; i < 9; i++ ){
                for( int j = 8; j > i; j-- ){
                    if( values[j-1] > values[j] ){
                        int tmp = values[j];
                        values[j] = values[j-1];
                        values[j-1] = tmp;
                    }
                }
            }
            img_dst.data[ y*img_dst.step + x*img_dst.channels() ] = values[4];
            std::cout << std::endl<<std::endl;
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