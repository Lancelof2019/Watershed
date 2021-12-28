#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
using namespace cv;

Mat WatershedAlg::thresholdOtsu(Mat image) {
    

        //threshold(image, image,ZERO,ONE, CV_THRESH_BINARY |         CV_THRESH_OTSU);

        cv::adaptiveThreshold(image,image,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY,  23,2);
        //if pixel <254 ,then 0 is given 
       
        string filename9="/opt/test9.txt";
        ofstream fout9(filename9); 


        for(int i = 0; i < image.rows; i++) {
            for(int j = 0; j < image.cols; j++) {

             fout9<<((int)image.at<uchar>(i,j))<<",";
             

         }
          fout9<<endl;
     }
     fout9.close();
        return image;
    }
