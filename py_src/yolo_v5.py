# https://github.com/ultralytics/yolov5

import torch
import cv2
import copy
import numpy as np

class YoloV5Detector(object):
    def __init__(self):
        self.__model = torch.hub.load('ultralytics/yolov5', 'yolov5s')  # or yolov5m, yolov5l, yolov5x, custom

    def inference(self, image):
        results = self.__model(image)
        results.print()

        detections_img = copy.deepcopy(image)
        self.__print_result(results.pandas().xyxy[0], detections_img)

        return detections_img
    
    def __print_result(self, detection_df, img):
        for index, det in detection_df.iterrows():
            bb_start = (int(det["xmin"]), int(det["ymin"]))
            bb_end   = (int(det["xmax"]), int(det["ymax"]))
            cv2.rectangle(img, bb_start, bb_end, (0, 0, 255), 2)

            bb_text = "{}({})-{:.2g}".format(det["class"], det["name"], det["confidence"])
            cv2.putText(img, bb_text, (bb_start[0], bb_start[1] - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 0, 255), 2)

        return img
