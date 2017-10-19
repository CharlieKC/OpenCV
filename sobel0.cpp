// header inclusion
#include <stdio.h>
#include <include/opencv/cv.hpp>        //you may need to
#include <include/opencv/highgui.h>   //adjust import locations
#include <include/opencv/cxcore.hpp>    //depending on your machine setup


using namespace cv;

void GaussianBlur(

	cv::Mat &input,
	int size,
	cv::Mat &blurredOutput);

int main( int argc, char** argv )
{

 // LOADING THE IMAGE
 //char* imageName = argv[1];
 char* imageName = "car.png";

 Mat image;
 image = imread(imageName, 1);

 if( argc != 2 || !image.data )
 {
   printf( " No image data \n " );
   return -1;
 }

 // CONVERT to hsv
 Mat hsv_image;
 cvtColor(image, hsv_image, CV_BGR2HSV );
 sobel(hsv_image);

 return 0;
}

void sobel(Mat &input) {

			//x-gradient image and kernel
			Mat dX;
			dX.create(input.size(), input.type());

			float xKernelValues[9] = {-1,0,1,-2,0,2,-1,0,1}
			Mat xKernel =	cv.Mat(3,3, 8UC1, xKernelValues);

			//Y-gradient image and kernel
			Mat dY;
			dY.create(input.size(), input.type());

			Mat yKernel;
			//y-gradient kernel is transpose of x
			transpose(xKernel,yKernel);

			//gradient magnitude image
			Mat mag;
			mag.create(input.size(), input.type());

			// gradient direction image
			Mat dir;
			dir.create(input.size(), input.type());


			Vec3b intensity;

			//loop over image pixels
			for(int x=1, x<input.rows-1; x++){
				for(int y=1, y<input.cols-1; y++){

					float totalX = 0.0;
					float totalY = 0.0;

					//loop over kernel values
					for(int m=-1; m<2; m++){
						for(int n = -1 ; n<2; n++){

							//value of input image (maybe)
							intensityX = input.at<Vec3b>(x-m, y-n)[2];
							totalX += intensityX*xKernel[m+1][n+1];

							intensityY = input.at<Vec3b>(x-m, y-n)[2];
							totalY += intensityY*yKernel[m+1][n+1];

						}
					}

					dX.at<float>(x,y) = totalX;
					dY.at<float>(x,y) = totalY;
				}
			}

}

void GaussianBlur(cv::Mat &input, int size, cv::Mat &blurredOutput)
{
	// intialise the output using the input
	blurredOutput.create(input.size(), input.type());

	// create the Gaussian kernel in 1D
	cv::Mat kX = cv::getGaussianKernel(size, -1);
	cv::Mat kY = cv::getGaussianKernel(size, -1);

	// make it 2D multiply one by the transpose of the other
	cv::Mat kernel = kX * kY.t();

	//CREATING A DIFFERENT IMAGE kernel WILL BE NEEDED
	//TO PERFORM OPERATIONS OTHER THAN GUASSIAN BLUR!!!

	// we need to create a padded version of the input
	// or there will be border effects
	int kernelRadiusX = ( kernel.size[0] - 1 ) / 2;
	int kernelRadiusY = ( kernel.size[1] - 1 ) / 2;

	cv::Mat paddedInput;
	cv::copyMakeBorder( input, paddedInput,
		kernelRadiusX, kernelRadiusX, kernelRadiusY, kernelRadiusY,
		cv::BORDER_REPLICATE );

	// now we can do the convoltion
	for ( int i = 0; i < input.rows; i++ )
	{
		for( int j = 0; j < input.cols; j++ )
		{
			double sum = 0.0;
			for( int m = -kernelRadiusX; m <= kernelRadiusX; m++ )
			{
				for( int n = -kernelRadiusY; n <= kernelRadiusY; n++ )
				{
					// find the correct indices we are using
					int imagex = i + m + kernelRadiusX;
					int imagey = j + n + kernelRadiusY;
					int kernelx = m + kernelRadiusX;
					int kernely = n + kernelRadiusY;

					// get the values from the padded image and the kernel
					int imageval = ( int ) paddedInput.at<uchar>( imagex, imagey );
					double kernalval = kernel.at<double>( kernelx, kernely );

					// do the multiplication
					sum += imageval * kernalval;
				}
			}
			// set the output value as the sum of the convolution
			blurredOutput.at<uchar>(i, j) = (uchar) sum;
		}
	}

}
