#ifndef WATERSHEDALG_H
#define WATERSHEDALG_H

#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/structPixel/structPixel.cpp"
#include<iostream>
#include <fstream>
#include <opencv2/opencv.hpp>
#include<queue>
#include <vector>
#include<random>
#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <queue>
#include<string>
#include <cstdlib>
using namespace cv;
using namespace std;
#define ZERO 0
#define ONE 254
#define STEP 1
using namespace std;
using namespace cv;

class WatershedAlg{

public:
Mat makeImageGrayScale(Mat image);

Mat thresholdMeasure(Mat image);

Mat inverseImage(Mat image);

Mat antiInverseImage(Mat image);

Mat erosion(Mat image, vector< vector <int> > kernel);

Mat distanceTransform(Mat image, vector<Point> &markers);

Mat watershed(Mat image, vector<Point> const &markers,Mat duplImage);

Mat contourFun(Mat image);
//bool comp(Point a,Point b);
void removeholesopt(Mat& src, int pnumlThrshold, int handlingType, int neighbourType,int pixelThreshhold);

void processImage(Mat image,Mat duplImage) ;
void lapseedFunc(Mat &Img);

};
#endif
