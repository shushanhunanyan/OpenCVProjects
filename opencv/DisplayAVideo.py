"""
  Write a program in both Python
  to open and display the video stream from your webcam in a window.
  Reading: OpenCV Documentation on VideoCapture
 
"""


import cv2

cap = cv2.VideoCapture(0);

if not cap.isOpened():
    print("ERROR")
    exit()

print("Press any key to terminate")

while True:
        ret, frame = cap.read()

        cv2.imshow('Video', frame)
        
        if cv2.waitKey(1) >= 0:
            break




