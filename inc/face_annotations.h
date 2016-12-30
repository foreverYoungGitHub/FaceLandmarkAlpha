//
// Created by 刘阳 on 2016/12/29.
//

#ifndef LESSON1_FACE_ANNOTATIONS_H
#define LESSON1_FACE_ANNOTATIONS_H

#include <opencv2/opencv.hpp>

class FaceAnnotations {

public:
    std::vector<int> symmetry_;
    std::vector<cv::Vec2i> connection_;
    std::vector<std::string> img_name_;
    std::vector<std::vector<cv::Point2f> > points_;

    void read(std::string muct);
    void read(cv::FileNode);
    void write(cv::FileStorage);
    void show(int index);

private:
    std::vector<cv::Point2f> get_data(std::string points_str);
    std::vector<cv::Point2f> get_data(std::vector<cv::Point2f> points_org, int img_width);
};


#endif //LESSON1_FACE_ANNOTATIONS_H
