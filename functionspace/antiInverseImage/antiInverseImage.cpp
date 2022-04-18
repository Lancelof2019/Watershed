
#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
using namespace cv;

Mat WatershedAlg::antiInverseImage(Mat image) {
        #pragma omp parallel for
        for(int i = 0; i < image.rows; i++) {
            #pragma omp parallel for
            for(int j = 0; j < image.cols; j++) {
                if( (int) image.at<uchar>(i,j) == ZERO ) {
                    image.at<uchar>(i,j) = ZERO;
                } else {
                    image.at<uchar>(i,j) = ONE;
                }
            }
        }

        return image;
    }
