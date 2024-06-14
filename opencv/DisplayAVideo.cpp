/*
 * Write a program in both C++
 * to open and display the video stream from your webcam in a window.
 * Reading: OpenCV Documentation on VideoCapture
 *
*/


#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <stdio.h>


int main()
{
	cv::Mat frame;
	cv::VideoCapture cap(0);
 
	if (!cap.isOpened()) {
		std::cerr << "ERROR! Unable to open camera" << std::endl;
		return -1;
 	}

	std::cout << "Press any key to terminate" << std::endl;
	
	while (true) {
		cap.read(frame);
		
		cv::imshow("Video", frame);
 		if (cv::waitKey(30) >= 0) {
 			break;
		}
 	}
	
	return 0;
}


