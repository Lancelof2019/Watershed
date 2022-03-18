
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

     cv::imshow("Laplacian",absdst);

     cv::waitKey(0);



    cv::split(absdst,channelArr);

    /*cv::imshow("R",channelArr[0]);
    cv::waitKey(0);
    cv::imshow("G",channelArr[1]);
    cv::waitKey(0);
    cv::imshow("B",channelArr[2]);
    cv::waitKey(0);
    */
    combImg=channelArr[0]+channelArr[1]+channelArr[2];

    //cv2::convertScaleAbs(combImg,grayImg);
    //grayImg=cv::cvtColor(combImg,cv::COLOR;
    cv::imshow("seed Lap",combImg);
    cv::waitKey(0);

         for(int i = 0; i < combImg.rows; i++) {

            for(int j = 0; j < combImg.cols; j++) {
                if( (int) combImg.at<uchar>(i,j) > THVALUE) {
                    combImg.at<uchar>(i,j) = 255;
                    imgPos.push_back(Point(i,j));

                    
                } else {
                    combImg.at<uchar>(i,j) = 0;
                }
            }
        }
    cv::imshow("seed Lap compare",combImg);
    cv::waitKey(0);
    //int imgposnum=imgPos.size();
    cout<<"The number of  imgPos is :"<<imgPos.size()<<endl;
    //(ratio*imgposnum);
     cout<<"The number of Pcounter is:"<<ratio*imgPos.size()<<endl;
    srand(unsigned(time(0)));

    //vector<Point> posVector;
    vector<int> vnum;

    for(int u=0;u<imgPos.size();u++){


     vnum.push_back(u);


    }

    Mat zerosImg=cv::Mat::zeros(combImg.rows,combImg.cols,CV_8UC1);
    std::random_shuffle(vnum.begin(),vnum.end());
    
    Pcounter=(int)(ratio*imgPos.size());
    cout<<"The number of Pcounter"<<Pcounter<<endl;

     for(int count=0;count<=Pcounter;count++){
     
        //cout<<"The pos is x :"<<imgPos.at(count).x<<endl;
        //cout<<"The pos is y :"<<imgPos.at(count).y<<endl;
        zerosImg.at<uchar>(imgPos.at(vnum.at(count)).x,imgPos.at(vnum.at(count)).y)=255;



     }


      cv::imshow("randomly chosen",zerosImg);
       cv::waitKey(0);

}
