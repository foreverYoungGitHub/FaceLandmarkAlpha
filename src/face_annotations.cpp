//
// Created by 刘阳 on 2016/12/29.
//

#include "face_annotations.h"

void FaceAnnotations::read(std::string muct)
{
    //get connection index from file
    std::ifstream connection_file;
    connection_file.open("./connection.txt");

    while(!connection_file.eof())
    {
        std::string line;
        getline(connection_file, line);
        if(line == "")
            continue;

        char *ptr = new char[line.length() + 1];
        strcpy(ptr, line.c_str());
        char *p = strtok(ptr, " ");
        int x = atoi(p);
        p = strtok(NULL, " ");
        int y = atoi(p);
        connection_.push_back(cv::Vec2i(x, y));
    }

    //get symmetry index from file
    std::ifstream symmetry_file;
    symmetry_file.open("./symmetry.txt");

    while(!symmetry_file.eof())
    {
        std::string line;
        getline(symmetry_file, line);
        if(line == "")
            continue;

        char *ptr = new char[line.length() + 1];
        strcpy(ptr, line.c_str());
        symmetry_.push_back(atoi(ptr));
    }

    //get points from file
    std::ifstream point_file;
    point_file.open(muct + "muct-landmarks/muct76-opencv.csv");

    //get the labels from the first line
    std::string labels;
    getline(point_file, labels);

    //get the data from the flowing lines
    //while(!point_file.eof())
    {
        std::string line;
        getline(point_file, line);
//        if(line == "")
//            continue;

        //get image name from the first col
        char *ptr = new char[line.length() + 1];
        strcpy(ptr, line.c_str());
        char *p = strtok(ptr, ",");

        std::string img_name(p);
        img_name_.push_back(muct + "jpg/" + img_name + ".jpg");

        //generate mirror img
//        cv::Mat img = cv::imread(muct + "jpg/" + img_name + ".jpg");
//        cv::Mat img_mirror;
//        cv::flip(img, img_mirror, 1);
//        cv::imwrite(muct + "jpg/" + img_name + "_mirror.jpg", img_mirror);
//        img_name_.push_back(muct + "jpg/" + img_name + "_mirror.jpg");

        //get tag from second col
        p = strtok(NULL, ",");
        std::string tag(p);

        //get data from the rest of the cols
        p = strtok(NULL, "\n");
        std::string points_str(p);
        std::vector<cv::Point2f> points = get_data(points_str);
        points_.push_back(points);

        //generate mirror landmarks
//        std::vector<cv::Point2f> points_mirror = get_data(points_str, img.cols);
//        points_.push_back(points_mirror);
    }
}

std::vector<cv::Point2f> FaceAnnotations::get_data(std::string points_str)
{
    //get the landmarks of the face
    std::vector<cv::Point2f> points;

    char *ptr = new char[points_str.length() + 1];
    strcpy(ptr, points_str.c_str());
    char *p = strtok(ptr, ",");

    int x , y;
    for(int index = 0; p != 0; index++)
    {
        if(index % 2 == 0)
        {
            x = atoi(p);
        }
        else
        {
            y = atoi(p);
            points.push_back(cv::Point2f(x, y));
        }
        p = strtok(NULL, ",");
    }

    return points;
}

std::vector<cv::Point2f> FaceAnnotations::get_data(std::vector<cv::Point2f> points_org, int img_width)
{
    //get the landmarks of the face
    std::vector<cv::Point2f> points = points_org;

    for(int index = 0; index < points.size(); index++)
    {
        //mirror the points through (img_width - point.x)
        points[index].x = img_width - points_org[symmetry_[index]].x;
        points[index].y = points_org[symmetry_[index]].y;
    }

    return points;
}

void FaceAnnotations::write(cv::FileStorage)
{
    std::ofstream file("./connection-test.txt");

    for(int i = 0; i < connection_.size(); i++)
    {
        file << connection_[i][0] << " " << connection_[i][1] << std::endl;
    }

}

void FaceAnnotations::show(int index)
{
    index = 0;

    cv::Mat img = cv::imread(img_name_[index]);

    //show the points and its relative index
//    for(int i = 0; i < points_[index].size(); i++)
//    {
//        cv::circle(img, points_[index][i], 1, cv::Scalar(0, 255, 0));
//        cv::putText(img, std::to_string(i), points_[index][i], cv::FONT_HERSHEY_TRIPLEX, 0.4, cv::Scalar(0, 0, 255));
//    }

    //show the connection between points
//    for(int i = 0; i < connection_.size(); i++)
//    {
//        cv::line(img, points_[index][connection_[i][0]], points_[index][connection_[i][1]],  cv::Scalar(0, 255, 0));
//    }

    //show the symmetry connection for each point
//    for(int i = 0; i < symmetry_.size(); i++)
//    {
//        cv::Mat img_copy;
//        img.copyTo(img_copy);
//        cv::line(img_copy, points_[index][i], points_[index][symmetry_[i]],  cv::Scalar(0, 255, 0));
//        cv::imshow("test", img_copy);
//        cv::waitKey(0);
//    }

    cv::imshow("test", img);
    cv::waitKey(0);
}