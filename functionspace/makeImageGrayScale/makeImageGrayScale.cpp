#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
using namespace cv;

Mat WatershedAlg::makeImageGrayScale(Mat image) {
        Mat grayScale(image.rows, image.cols, CV_8UC1, Scalar(70));
        
    



        for(int i = 0; i < image.rows; i++) {

            for(int j = 0; j < image.cols; j++) {
                double gray = 0.21 * image.at<cv::Vec3b>(i,j)[0] +
                              0.72 * image.at<cv::Vec3b>(i,j)[1] +
                              0.07 * image.at<cv::Vec3b>(i,j)[2];
                grayScale.at<uchar>(i,j) = (uchar) gray;
            }
        }
       cv::GaussianBlur(grayScale, grayScale, Size(5,5), 1);
        string filename8="/opt/test8.txt";
        ofstream fout8(filename8);

        for(int i = 0; i < image.rows; i++) {
            for(int j = 0; j < image.cols; j++) {

             fout8<<((int)grayScale.at<uchar>(i,j))<<",";
             

         }
          fout8<<endl;
     }
     fout8.close();


        return grayScale;
    }

