#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
#include <cmath> 
#include <stdlib.h>


#include <cv.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;

Mat WatershedAlg::thresholdMeasure(Mat image) {
        
	cv::adaptiveThreshold(image,image,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY,  11,2);
      //if pixel <254 ,then 0 is given 
    return image;
    }
