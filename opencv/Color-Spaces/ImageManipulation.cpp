/*
 * Explore different color spaces and apply specific image filters
 * such as Gaussian blur and sharpening.
 *
*/

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>

class ImageManipulation {
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

    void convert_to_color_space(const std::string& colorSpace) {
        if (!m_image.empty()) {
            if (colorSpace == "RGB") {
                cv::cvtColor(m_image, m_convertedImage, cv::COLOR_BGR2RGB);
            } else if (colorSpace == "HSV") {
                cv::cvtColor(m_image, m_convertedImage, cv::COLOR_BGR2HSV);
            } else if (colorSpace == "LAB") {
                cv::cvtColor(m_image, m_convertedImage, cv::COLOR_BGR2Lab);
            } else if (colorSpace == "Grayscale") {
                cv::cvtColor(m_image, m_convertedImage, cv::COLOR_BGR2GRAY);
            } else {
                std::cerr << "ERROR! Unknown color space" << std::endl;
                return;
            }
            
	    img_display(colorSpace + " Image", m_convertedImage);
            img_save(m_imagePath.substr(0, m_imagePath.find_last_of('.')) + "_" + colorSpace + ".jpg", m_convertedImage);
        } else {
            std::cerr << "ERROR! No image loaded to convert" << std::endl;
        }
    }

    void apply_gaussian_blur(int ksize) {
        if (!m_image.empty()) {
            cv::GaussianBlur(m_image, m_filteredImage, cv::Size(ksize, ksize), 0);
            img_display("Gaussian Blur", m_filteredImage);
            img_save(m_imagePath.substr(0, m_imagePath.find_last_of('.')) + "_gaussian_blur.jpg", m_filteredImage);
        } else {
            std::cerr << "ERROR! No image loaded to apply Gaussian Blur" << std::endl;
        }
    }

    void apply_sharpening() {
        if (!m_image.empty()) {
            cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
                0, -1, 0,
                -1, 5, -1,
                0, -1, 0);
            cv::filter2D(m_image, m_filteredImage, -1, kernel);
            std::cout << "Applied sharpening filter" << std::endl;
            img_display("Sharpened Image", m_filteredImage);
            img_save(m_imagePath.substr(0, m_imagePath.find_last_of('.')) + "_sharpened.jpg", m_filteredImage);
        } else {
            std::cerr << "ERROR! No image loaded to apply sharpening" << std::endl;
        }
    }

    void apply_median_filter(int ksize) {
        if (!m_image.empty()) {
            cv::medianBlur(m_image, m_filteredImage, ksize);
            std::cout << "Applied Median Filter with kernel size " << ksize << std::endl;
            img_display("Median Filter", m_filteredImage);
            img_save(m_imagePath.substr(0, m_imagePath.find_last_of('.')) + "_median_filter.jpg", m_filteredImage);
        } else {
            std::cerr << "ERROR! No image loaded to apply Median Filter" << std::endl;
        }
    }

    void img_display(const std::string& windowName, const cv::Mat& image) const {
        if (!image.empty()) {
            cv::imshow(windowName, image);
        } else {
            std::cerr << "ERROR! No image to display" << std::endl;
        }
    }

    void img_save(const std::string& savePath, const cv::Mat& image) const {
        if (!image.empty()) {
            cv::imwrite(savePath, image);
            std::cout << "Image saved to " << savePath << std::endl;
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
    cv::Mat m_convertedImage;
    cv::Mat m_filteredImage;
};

int main() {
    ImageManipulation img("/home/shushan/Downloads/the-image-cicada.png");

    if (!img.img_load()) {
        return -1;
    }

    img.convert_to_color_space("RGB");
    img.convert_to_color_space("HSV");
    img.convert_to_color_space("LAB");
    img.convert_to_color_space("Grayscale");

    img.apply_gaussian_blur(15); 
    img.apply_sharpening();
    img.apply_median_filter(5); 

    img.waitForKeyPress();

    return 0;
}

