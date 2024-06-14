#include <opencv2/highgui.hpp>

int main()
{
	cv::Mat img = cv::imread("/path/image.png");
	cv::imshow("Image", img);
	
	cv::waitKey(0);

	cv::destroyAllWindows();


	return 0;
}
