#include <iostream>
#include <opencv2/opencv.hpp>
#include "../inc/face_annotations.h"

int main(int argc, char *argv[]) {

    FaceAnnotations face_annotations;

    face_annotations.read("/Users/Young/projects/muct/");
    face_annotations.show(0);
//    face_annotations.write(0);

    return 0;
}
