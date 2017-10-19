/////////////////////////////////////////////////////////////////////////////
//
// COMS30121 - thr.cpp
// TOPIC: RGB explicit thresholding
//
// Getting-Started-File for OpenCV
// University of Bristol
//
/////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <opencv/cv.h>        //you may need to
#include <opencv/highgui.h>   //adjust import locations
#include <opencv/cxcore.h>    //depending on your machine setup

using namespace cv;

int main() {

  // Read image from file
  Mat image = imread("mandrill0.jpg", 1);
  Mat imageOut;
  cvtColor(image, imageOut, CV_BGR2HSV);
  // Threshold by looping through all pixels
  for(int y=0; y<imageOut.rows; y++) {
   for(int x=0; x<imageOut.cols; x++) {
     uchar pixelHue = imageOut.at<Vec3b>(y,x)[0];
     // uchar pixelSaturation = image.at<Vec3b>(y,x)[1];
     //uchar pixelValue = image.at<Vec3b>(y,x)[2];

     int i_pixel = (int)pixelHue;

    // i_pixel += x;
     //i_pixel = i_pixel % 180;
     //pixelHue = (uchar)i_pixel;
     imageOut.at<Vec3b>(y,x)[0]= 0.2; //value
     imageOut.at<Vec3b>(y,x)[1]= 0.4;
     //print(image.at<Vec3b>(y,x)[0]);
     imageOut.at<Vec3b>(y,x)[2]= 255;
     //need to adjust hue values

 } }

  //Save thresholded image
  imwrite("colourthr.jpg", imageOut);

  return 0;
}
