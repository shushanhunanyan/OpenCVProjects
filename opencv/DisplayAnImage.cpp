#include <opencv2/highgui.hpp>

int main()
{
	cv::Mat img = cv::imread("/home/shushan/Downloads/the-image-cicada.png");
	cv::imshow("Image", img);
	
	cv::waitKey(0);

	cv::destroyAllWindows();


	return 0;
}
