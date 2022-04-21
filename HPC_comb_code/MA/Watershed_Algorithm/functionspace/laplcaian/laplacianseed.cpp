#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
#include <cmath> 
#include <stdlib.h>
#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vector>
#define  THVALUE 117
using namespace cv;
void WatershedAlg::lapseedFunc(Mat &Img){
    double ratio=0.085;
    double Pcounter=0;
    Mat dst,absdst,grayImg,combImg;
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int ddepth = CV_16S;
    vector<Point> imgPos;
    Mat channelArr[3];
    cv::Laplacian( Img, dst, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );
    cv::convertScaleAbs(dst,absdst);
    cv::split(absdst,channelArr);
    combImg=channelArr[0]+channelArr[1]+channelArr[2];
    #pragma o,p parallel for
    for(int i = 0; i < combImg.rows; i++) {
        #pragma o,p parallel for
         for(int j = 0; j < combImg.cols; j++) {
             if( (int) combImg.at<uchar>(i,j) > THVALUE) {
                 combImg.at<uchar>(i,j) = 255;
                 imgPos.push_back(Point(i,j));
                } else {
                    combImg.at<uchar>(i,j) = 0;
                }
            }
        }
/
    srand(unsigned(time(0)));
    vector<int> vnum;
    #pragma o,p parallel for
    for(int u=0;u<imgPos.size();u++){
     vnum.push_back(u);
    }
    Mat zerosImg=cv::Mat::zeros(combImg.rows,combImg.cols,CV_8UC1);
    std::random_shuffle(vnum.begin(),vnum.end());
    Pcounter=(int)(ratio*imgPos.size());
    cout<<"The number of Pcounter"<<Pcounter<<endl;
    #pragma o,p parallel for
    for(int count=0;count<=Pcounter;count++){
      zerosImg.at<uchar>(imgPos.at(vnum.at(count)).x,imgPos.at(vnum.at(count)).y)=255;
     }
      cv::imshow("randomly chosen",zerosImg);
      cv::waitKey(0);

}
