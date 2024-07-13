import cv2

img = cv2.imread('/home/shushan/Downloads/the-image-cicada.png')
cv2.imshow('Image', img)

cv2.waitKey(0)

cv2.destroyAllWindows()
