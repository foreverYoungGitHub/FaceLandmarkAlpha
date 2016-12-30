//
// Created by 刘阳 on 2016/12/29.
//

#ifndef LESSON1_SHAPE_MODEL_H
#define LESSON1_SHAPE_MODEL_H

#include <opencv2/opencv.hpp>

class ShapeModel {

    cv::Mat subspace_; // linear subspace (2nxk) CV_32F
    cv::Mat var_vec_; // parameter variance (kx1) CV_32F
    cv::Mat shape_vec_; // parameter vector (kx1) CV_32F
    cv::Mat connectivity_; // connectivity (cx2) CV_32S


};


#endif //LESSON1_SHAPE_MODEL_H
