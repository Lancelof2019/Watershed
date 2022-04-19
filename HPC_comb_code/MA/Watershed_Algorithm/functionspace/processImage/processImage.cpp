#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
using namespace cv;
void WatershedAlg::processImage(Mat image,Mat duplImage)  {
       image = makeImageGrayScale(image);

       // Erode foreground
       vector< vector<int> > erosionTargetThree{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, };
       image = erosion(image, erosionTargetThree);
       // Apply threshold
       image = thresholdMeasure(image);
       image=antiInverseImage(image);

       // Apply distance transform
       vector<Point> markers;
       image = distanceTransform(image,markers);
        //image=testDistanceTransform(image, markers);
       Mat distanceImage = image;
        // Watershed
       if(markers.size() == 0) {
            for(int i = 0; i < image.rows; i++) {
                for(int j = 0; j < image.cols; j++) {
                    if((int) distanceImage.at<uchar>(i,j) != 0) {
                        markers.push_back(Point(i, j));
                        image.at<uchar>(i, j) = 25;
                         //return watershed(image, markers);
                    }
                }
            }
        }
        image = watershed(image, markers,duplImage);

    }
