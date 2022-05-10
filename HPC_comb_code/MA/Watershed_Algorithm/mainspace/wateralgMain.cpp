 #include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
 #include<iostream>
 #include <time.h>
 using namespace std;
 using namespace cv;
 int main(){
  
     clock_t start,end;
     start=clock();
     cv::Mat srcImg=cv::imread("/opt/testimages/istockphoto-1150481340-612x612.jpg");
     if(!srcImg.data){
      
      cout<<"The file is not loaded or does not exist"<<endl;
      return -1;
     }
     cv::imshow("Test image",srcImg);
     cv::waitKey(0);
     cv::Mat duplImage(srcImg.rows,srcImg.cols,CV_8UC3,Scalar::all(0));
     srcImg.copyTo(duplImage);
     WatershedAlg *walg=new WatershedAlg();
     walg->processImage(srcImg,duplImage);
     end=clock();
     delete walg;
   
     cout<<"The total time the algorithm used is :"<<(double)(end - start)/CLOCKS_PER_SEC<<endl;
  
     return 0;
   }
