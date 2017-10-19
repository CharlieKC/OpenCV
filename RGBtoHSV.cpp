/////////////////////////////////////////////////////////////////////////////
//
// COMS30121 - RGBtoHSV.cpp
//
// University of Bristol
//
/////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup

using namespace cv;

int main( int argc, char** argv )
{

 // LOADING THE IMAGE
 //char* imageName = argv[1];

 Mat image;
 image = imread( "mandrill0.jpg", 1 );
/*
 if( argc != 2 || !image.data )
 {
   printf( " No image data \n " );
   return -1;
 }*/

 // CONVERT AND SAVE THE IMAGE
 cvtColor( image, image, CV_BGR2HSV );

 for(int y=0; y<imageOut.rows; y++) {
  for(int x=0; x<imageOut.cols; x++) {
    uchar pixelHue = imageOut.at<Vec3b>(y,x)[0];
    // uchar pixelSaturation = image.at<Vec3b>(y,x)[1];
    //uchar pixelValue = image.at<Vec3b>(y,x)[2];

    int i_pixel = (int)pixelHue;

    i_pixel += 60;
    i_pixel = i_pixel % 180;
    pixelHue = (uchar)i_pixel;
    imageOut.at<Vec3b>(y,x)[0]= pixelHue; //value
    // imageOut.at<Vec3b>(y,x)[1]= 0.4;
    // //print(image.at<Vec3b>(y,x)[0]);
    // imageOut.at<Vec3b>(y,x)[2]= 255;
    // //need to adjust hue values

 cvtColor( image, image, CV_HSV2BGR );
 imwrite( "hsv.jpg", image );

 return 0;
}
