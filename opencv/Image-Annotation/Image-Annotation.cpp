/* Develop a program that performs various image annotation tasks such as
 *  adding text labels
 *  drawing geometric shapes.
*/

#include <iostream>
#include <opencv2/opencv.hpp>

class ImageAnnotation
{
public:
	ImageAnnotation(const std::string& path)
	       	: m_img_path{path} {}

	bool img_load() {
		m_image = cv::imread(m_img_path);

		if (m_img_path.empty()) {
			std::cerr << "ERROR! Unable to load image" << std::endl;
			return false;
		}

		std::cout << "Image loaded Successfully" << std::endl;
		return true;
	}

	void img_add_text(const std::string& txt, cv::Point org, int font = cv::FONT_HERSHEY_SIMPLEX, double fontScale = 1.0, cv::Scalar color = cv::Scalar(255, 0, 0)) {
		putText(m_image, txt, org, font, fontScale, color);
	}

	void img_add_line(cv::Point start_point, cv::Point end_point, cv::Scalar color = cv::Scalar(0, 0, 0), int thickness = 1) {
		cv::line(m_image, start_point, end_point, color, thickness);
	}

        void img_add_rectangle(cv::Point start_point, cv::Point end_point, cv::Scalar color = cv::Scalar(0, 0, 0), int thickness = 1) {
                cv::rectangle(m_image, start_point, end_point, color, thickness);
        }


	void img_add_circle(cv::Point center, int radius, cv::Scalar color = cv::Scalar(0, 0, 0), int thickness = 1) {
                cv::circle(m_image, center, radius, color, thickness);
        }


	void img_show(const std::string& window_name) {
		if (!m_image.empty()) {
			cv::imshow(window_name, m_image);
            		cv::waitKey(0);
		}
        	else {
            		std::cerr << "ERROR! No image to display" << std::endl;
        	}
	}

private:
	std::string m_img_path;
	cv::Mat m_image;
};

int main()
{
	std::string imagePath = "/home/shushan/Downloads/the-image-cicada.png";
	ImageAnnotation annotator(imagePath);
	
	if (!annotator.img_load()) {
        	return -1; // Exit if image loading failed
    	}

	    std::string text = "Hello, OpenCV!";
	     cv::Point org(50, 100);
	         annotator.img_add_text(text, org);

		cv::Point circleCenter(300, 300); // Center of the circle
    int radius = 50; // Radius of the circle
    cv::Scalar circleColor(0, 255, 0); // Green color
    annotator.img_add_circle(circleCenter, radius, circleColor, 2);

        annotator.img_show("Image with Text, Line, and Circle");


		 return 0;
}
