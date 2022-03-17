
#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
using namespace cv;

void WatershedAlg::removeholesopt(Mat& src,int pnumThrshold, int handlingType, int neighbourType,int pixelThreshold)  {
   
    Mat Pointlabel(src.rows,src.cols, CV_8UC1,Scalar::all(255) );  
    for(int i = 0; i < src.rows; ++i) {    
           // uchar* iData = src.ptr<uchar>(i);  
           // uchar* iLabel = Pointlabel.ptr<uchar>(i);  
            for(int j = 0; j < src.cols; ++j) {    
                 if(src.at<uchar>(i,j)>pixelThreshold){
                 Pointlabel.at<uchar>(i,j)=0;
                 }
            }    
     }  

    vector<vector<Point>> contours;  
    vector<cv::Vec4i> hierarchy; 
    findContours(Pointlabel,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point()); 
    Mat imageContours=Mat::zeros(Pointlabel.size(),CV_8UC1);  
    Mat contouroutput=Mat::zeros(Pointlabel.size(),CV_8UC1);   
    Point p=Point(0,0);



   if (!contours.empty() && !hierarchy.empty()) {
		vector<vector<Point> >::const_iterator couit = contours.begin();
		
		while (itc != contours.end()) {
		
			cv::Rect countourposition = cv::boundingRect(Mat(*couit));
			
			double area = contourArea(*couit);
			
			if (area < pnumThrshold) {
				
				for (int i = countourposition.y; i < countourposition.y + countourposition.height; i++) {
					
					for (int j = countourposition.x; j < countourposition.x + countourposition.width; j++){
						
						if ((int)Pointlabel.at<uchar>(i,j) == 255) {
							Pointlabel.at<uchar>(i,j) = 2;
                            src.at<uchar>(i,j)=pixelThreshold;

						}
					}
				}
			}
			couit++;
		}
	}
 }
