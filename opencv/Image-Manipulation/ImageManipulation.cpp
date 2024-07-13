/*
 * Learn and implement various image manipulations such as 
 * resizing, flipping, cropping, rotating, and validating image loading.
*/


#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

class ImageManipulation
{
public:
	ImageManipulation(const std::string& imagePath) 
		: m_imagePath(imagePath) {}
	
	
	bool img_load() {
		m_image = cv::imread(m_imagePath);
		
		if (m_image.empty()) {
            		std::cerr << "ERROR! Unable to load image" << std::endl;
            		return false;
        	}

        	std::cout << "Image loaded successfully" << std::endl;
        	return true;
    	}

    
   	void img_resize(int width, int height) {
        	if (!m_image.empty()) {
            		cv::resize(m_image, m_image, cv::Size(width, height));
		} else {
            		std::cerr << "ERROR! No image loaded to resize" << std::endl;
        	}
    	}


	void img_flip(int flip) {
		cv::flip(m_image, m_image, flip);
	}


	void img_crop(int x, int y, int w, int h) {
		if (!m_image.empty()) {
			cv::Rect reg(x, y, w, h);
			m_image = m_image(reg);
		}
	}

	void img_rotate(double degrees) {
		if (!m_image.empty()) {

			cv::Point2f center((m_image.cols-1)/2.0, (m_image.rows-1)/2.0);
			cv::Mat rot = cv::getRotationMatrix2D(center, degrees, 1.0);

    			cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), m_image.size(), degrees).boundingRect2f();

			rot.at<double>(0,2) += bbox.width/2.0 - m_image.cols/2.0;
			rot.at<double>(1,2) += bbox.height/2.0 - m_image.rows/2.0;

			cv::Mat dst;

			cv::warpAffine(m_image, m_image, rot, bbox.size());
		}
	}

 
    	void img_display(const std::string& windowName) const {
        	if (!m_image.empty()) {
            		cv::imshow(windowName, m_image);
        	} else {
            		std::cerr << "ERROR! No image to display" << std::endl;
        	}
    	}


	 void img_save(const std::string& savePath) const {
        	if (!m_image.empty()) {
            		cv::imwrite(savePath, m_image);
		} else {
            		std::cerr << "ERROR! No image to save" << std::endl;
        	}
    	}
	

	void waitForKeyPress() const {
        	cv::waitKey(0);
    	}

private:
    std::string m_imagePath;
    cv::Mat m_image;
};



int main()
{
  
     ImageManipulation img("/home/shushan/Downloads/the-image-cicada.png");

    
    if (!img.img_load()) {
        return -1;
    }
    img.img_crop(200, 200, 200, 200);
    img.img_resize(200, 200);
    img.img_rotate(-45);
    img.img_flip(-1);
    img.img_display("Resized Image");
    img.img_save("/home/shushan/Downloads/rotated_image.png");

    img.waitForKeyPress();

    return 0;
}

