#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{

	Mat img = imread(argv[1], 1); // Load the color image
	if (!img.data) // check image is available
	{
		cout << "Could not load image file" << endl;
		return -1;
	}

	int height = img.rows;
	int width = img.cols;
	int widthstep = img.step;
	int ch = img.channels();
	printf("height: %d, widht: %d, width step: %d, chanels: %d\n", height, width, widthstep, ch);

	Mat gray(height, width, CV_8UC1, Scalar(0)); // create new image, CV_8UC1 means gray(one chanel),  Scalar(0) = default black color
	cvtColor(img, gray, COLOR_BGR2GRAY); // convert RGB image to Gray

	Mat enhance_image = gray.clone(); //get the copy of the gray image

	int input_x;
	int out_x;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			input_x = (int)gray.at<uchar>(y, x);
			if ((input_x >= 0) and (input_x <= 105) ){
				out_x = int((5 / 105) * input_x);
			}else if ((input_x > 105) and (input_x <= 240)){
				out_x = int((245 / 135) * (input_x - 105) + 5);
			}else if((input_x > 240) and (input_x <= 255)) {
				out_x = int((5 / 15) * (input_x - 240) + 250);
			}
			enhance_image.at<uchar>(y, x) = (uchar)out_x;
		}
	}

	//gray image
	namedWindow("Gray"); // Create the window
	imshow("Gray", gray); // load and show image

	//enhance gray image
	namedWindow("EnGray"); // Create the window
	imshow("EnGray", enhance_image); // load and show image

	waitKey(0); // wait to close

	return 0;

}