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
    Point starting_point, current_point;
    int area;
    double x_total = 0,
           y_total = 0;
    int x_max = 0,
        x_min = 1000000,
        y_max = 0,
        y_min = 1000000;
    Point G;
    bool found_starting_point = false;
    for( int y = 0; y < height; y++ ){
        for( int x = 0; x < width; x++ ){
            if( img_bi.data[ y*step + x*channels ] == 255 ){ 
                x_total += x;
                y_total += y; 
                area++;
                if( x > x_max ) x_max = x;
                if( x < x_min ) x_min = x;
                if( y > y_max ) y_max = y;
                if( y < y_min ) y_min = y;
                if( !found_starting_point ){
                    cout << "x: " << x << " y: " << y << endl;
                    starting_point = Point( x, y );
                    found_starting_point = true;
                }
            }
        }
    }
    double x_g = x_total/area,
           y_g = y_total/area;
    G = Point( x_g, y_g );
    cout << "area: " << area << endl;
    cout << "G: ( " << x_g << ", " << y_g << " )" << endl;

   double  x_d = 0,
            y_d = 0,
           xy_d = 0;
    for( int y = 0; y < height; y++ ){
            for( int x = 0; x < width; x++ ){
                if(  img_bi.data[ y*step + x*channels ] == 255  ){
                    x_d += pow(( x - x_g ),2);
                    y_d += pow(( y - y_g ),2);//*( y- y_g );
                    xy_d += ( x - x_g )*( y- y_g );
                }
            }
    }
    cout << "x_d: " << x_d/area << " y_d: " << y_d/area <<  " xy_d: " << xy_d/area << endl;
    double theta = atan2( (2*xy_d),( x_d - y_d ) )/2;

    cout << "theta: " << theta*180/M_PI << endl;
    //輪郭追従
    const double angle_rate    = M_PI/4;
    const int    circle_radius = 3;
    ////画素ごとの追跡記録用の配列とその初期化
    bool tracked[width][height];
    for( int i = 0; i < height; i++ ) for( int j = 0; j < width; j++ ) tracked[j][i] = false;
    tracked[starting_point.x][starting_point.y] = true;
    ////処理済み画素の座標リスト
    std::vector<Point> tracked_pixel_list;
    int x0 = starting_point.x,
        y0 = starting_point.y;
    int dir_id = 0; //処理する画素の方向を示す変数
    double d;
    bool contour_tracked = false;
    Mat img_brd( height, width, CV_8U, Scalar( 0, 0, 0 ) );
    circle( img_brd, starting_point,   circle_radius, 255, -1, 8 );
    circle( img_brd,              G, circle_radius, 128, -1, 8 );
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
                if( current_point == starting_point && tracked[x][y] ) contour_tracked = true;
                tracked[x][y] = true;
                current_point = Point( x,y );
                tracked_pixel_list.push_back( current_point );
                x0 = x;
                y0 = y;
                dir_id += 4;
                circle( img_brd, current_point, circle_radius, 255, -1, 8 );
                found_next_pixel = true;
            }
            if( counter > 8 ) break;
        }
    }
    double perimeter = 0; 
    for( int i = 0; i < tracked_pixel_list.size() - 1; i++ ) {
        perimeter += sqrt( pow( tracked_pixel_list[i+1].x - tracked_pixel_list[i].x, 2 ) +  pow( tracked_pixel_list[i+1].y - tracked_pixel_list[i].y, 2 ) );
    }
    cout << "perimeter: " << perimeter << std::endl;
    double circularity = 4*M_PI*area/(perimeter*perimeter);
    cout << "circularity: " << circularity << std::endl;
    //ソース画像加工
    for( int y = 0; y < height; y++ ){ 
        for( int x = 0; x < width; x++ ){
            if( img_bi.data[ y*step + x*channels ] == 255 )  {  
                img_dst.data[ y*img_dst.step + x*img_dst.channels() ] = 0;
            }
            if( img_brd.data[ y*step + x*channels ] == 255 )  {
                for( int i = 0; i < img_dst.channels(); i++ ){
                    if( i == 0 )img_dst.data[ y*img_dst.step + x*img_dst.channels() + i ] = 255;
                    else img_dst.data[ y*img_dst.step + x*img_dst.channels() + i ] = 0;
                }
            }else if( img_brd.data[ y*step + x*channels ] == 128 ){
                for( int i = 0; i < img_dst.channels(); i++ ){
                    img_dst.data[ y*img_dst.step + x*img_dst.channels() + i ] = 255;
                }              
            }
        } 
    }
    rectangle( img_dst, Point(x_min, y_min), Point(x_max, y_max), Scalar( 0, 255, 0), 3 );
    line( img_dst, Point( x_min, y_g + (x_min - x_g)*tan(theta) ), Point( x_max, y_g + ( x_max - x_g )*tan(theta) ), Scalar( 0, 0, 255 ) );
    line( img_dst, Point( x_g + (y_min - y_g)*tan(-theta) , y_min ), Point( x_g + (y_max - y_g)*tan(-theta) , y_max ), Scalar( 0, 0, 255 ) );

    Moments m = moments( img_bi, true );
    double area_cv = m.m00;
    cout << "area " << area_cv << endl;
    double x_g_cv = m.m10/m.m00;
    double y_g_cv =  m.m01/m.m00;
    cout << "G: ( " << x_g_cv << ", " << y_g_cv << " )" << endl;
    double ang = 0.5*atan2(2.0*m.mu11,m.mu20-m.mu02);
    cout << "theta " << ang*180/M_PI << endl;
    ////////////

    imshow( win_brd, img_brd );
    imshow( win_bi, img_bi );
    imshow( win_gray, img_gray );
    imshow( win_src, img_src );    
    imshow( win_dst, img_dst );
    imwrite( file_gray, img_gray );
    imwrite( file_bi, img_bi );
    imwrite( file_brd, img_brd );
    imwrite( file_dst, img_dst );

    waitKey(0);
    return 0;
}