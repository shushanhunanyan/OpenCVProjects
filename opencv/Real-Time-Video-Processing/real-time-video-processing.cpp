/*
 * Develop a program that captures video from your webcam
 * and applies various effects interactively using keyboard shortcuts.
 *
*/
/*
#include <opencv2/opencv.hpp>


class RealTimeVideoProcessing
{
public:
	RealTimeVideoProcessing(int index) 
		: m_cap{index} {}

	bool video_open() {
		if (!m_cap.isOpened()) {
			std::cerr << "Error while opening the camera" << std::endl;
			return false;
		}
		return true;
	}

	void video_load() {

		while (true) {
			m_cap.read(m_frame);

			cv::imshow("Video", m_frame);
			if (cv::waitKey(30) >= 'q') {
				break;
			} else if () {
				cv::imshow("Vertically Flipped Video", m_frame);
			}
		}
	}


private:
	cv::Mat m_frame;
	cv::VideoCapture m_cap;
};


int main() {
    RealTimeVideoProcessing videoProcessor(0);

    if (!videoProcessor.video_open()) {
        return -1;
    }

    videoProcessor.video_load();

    return 0;
}*/

#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <string>

class RealTimeVideoProcessing
{
public:
    RealTimeVideoProcessing(int index)
        : m_cap{index}
        , flipVertical{false}
        , flipHorizontal{false}
        , blur{false}
        , medianFilter{false}
        , drawShape{false}
        , rotate{false}
        , colorSpace{0} {}

    bool video_open() {
        if (!m_cap.isOpened()) {
            std::cerr << "Error while opening the camera" << std::endl;
            return false;
        }
        return true;
    }

    void video_load() {
        cv::namedWindow("Video", cv::WINDOW_AUTOSIZE);

        while (true) {
            m_cap.read(m_frame);

            if (m_frame.empty()) {
                std::cerr << "Error! Blank frame grabbed" << std::endl;
                break;
            }

            cv::Mat processed_frame = m_frame.clone();

            // Apply effects
            applyEffects(processed_frame);

            // Display current effect
            displayEffectText(processed_frame);

            // Display current time
            displayCurrentTime(processed_frame);

            // Show the processed frame
            cv::imshow("Video", processed_frame);

            // Check for user input to toggle effects or exit
            char key = static_cast<char>(cv::waitKey(30));
            if (key == 'q') {
                break;
            } else {
                handleKeyPress(key);
            }
        }
    }

private:
    cv::Mat m_frame;
    cv::VideoCapture m_cap;
    bool flipVertical;
    bool flipHorizontal;
    bool blur;
    bool medianFilter;
    bool drawShape;
    bool rotate;
    int colorSpace; // 0: BGR, 1: Grayscale, 2: HSV, 3: LAB
    std::string currentEffect;

    void applyEffects(cv::Mat &frame) {
        if (flipVertical) {
            cv::flip(frame, frame, 0);
        }
        if (flipHorizontal) {
            cv::flip(frame, frame, 1);
        }
        if (blur) {
            cv::GaussianBlur(frame, frame, cv::Size(15, 15), 0);
        }
        if (medianFilter) {
            cv::medianBlur(frame, frame, 15);
        }
        if (drawShape) {
            cv::rectangle(frame, cv::Point(50, 50), cv::Point(200, 200), cv::Scalar(0, 255, 0), 3);
        }
        if (rotate) {
            cv::Mat rot_mat = cv::getRotationMatrix2D(cv::Point(frame.cols / 2, frame.rows / 2), 45, 1);
            cv::warpAffine(frame, frame, rot_mat, frame.size());
        }
        switch (colorSpace) {
            case 1:
                cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
                cv::cvtColor(frame, frame, cv::COLOR_GRAY2BGR); // to keep the 3 channels
                break;
            case 2:
                cv::cvtColor(frame, frame, cv::COLOR_BGR2HSV);
                break;
            case 3:
                cv::cvtColor(frame, frame, cv::COLOR_BGR2Lab);
                break;
            default:
                break;
        }
    }

    void handleKeyPress(char key) {
        switch (key) {
            case 'v':
                flipVertical = !flipVertical;
                currentEffect = "Vertical Flip";
                break;
            case 'h':
                flipHorizontal = !flipHorizontal;
                currentEffect = "Horizontal Flip";
                break;
            case 'g':
                colorSpace = (colorSpace == 1) ? 0 : 1;
                currentEffect = "Grayscale";
                break;
            case 's':
                colorSpace = (colorSpace == 2) ? 0 : 2;
                currentEffect = "HSV";
                break;
            case 'l':
                colorSpace = (colorSpace == 3) ? 0 : 3;
                currentEffect = "LAB";
                break;
            case 'b':
                blur = !blur;
                currentEffect = "Blur";
                break;
            case 'm':
                medianFilter = !medianFilter;
                currentEffect = "Median Filter";
                break;
            case 'r':
                rotate = !rotate;
                currentEffect = "Rotate";
                break;
            case 'd':
                drawShape = !drawShape;
                currentEffect = "Draw Shape";
                break;
            default:
                break;
        }
    }

    void displayEffectText(cv::Mat &frame) {
        if (!currentEffect.empty()) {
            cv::putText(frame, "Effect: " + currentEffect, cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
        }
    }

    void displayCurrentTime(cv::Mat &frame) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::string time_str = std::ctime(&now_time);
        time_str.pop_back(); // Remove the newline character
        cv::putText(frame, time_str, cv::Point(10, frame.rows - 10), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 255, 255), 2);
    }
};

int main() {
    RealTimeVideoProcessing videoProcessor(0);

    if (!videoProcessor.video_open()) {
        return -1;
    }

    videoProcessor.video_load();

    return 0;
