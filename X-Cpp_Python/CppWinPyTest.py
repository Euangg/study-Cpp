import cv2
import numpy as np

cvImage = np.ndarray((512, 512, 3))
for x in range(512):
    for y in range(512):
        if x == y:
            cvImage[y, x] = [0, 0, 255]
        else:
            cvImage[y, x] = [255, 255, 255]
cv2.imwrite("out.png",cvImage)