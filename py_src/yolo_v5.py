# https://github.com/ultralytics/yolov5

import torch
import cv2
import numpy as np

class YoloV5Detector(object):
    def __init__(self):
        self.__model = torch.hub.load('ultralytics/yolov5', 'yolov5s')  # or yolov5m, yolov5l, yolov5x, custom
        self.data = "me:)"

    def inference(self, image):
        results = self.__model(image)
        # Results
        results.print()  
        # results.show()  # or .show(), .save(), .crop(), .pandas(), etc.

        # print(results.imgs)  # img1 predictions (tensor)
        
        return results.imgs

    def get_image(self):
        return cv2.imread("https://ultralytics.com/images/zidane.jpg")
