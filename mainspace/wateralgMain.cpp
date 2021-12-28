 #include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
 #include<iostream>
 using namespace std;
 using namespace cv;
 int main(){
     cout<<"---Image will be read into memory-----"<<endl;
     cv::Mat srcImg=cv::imread("/opt/project_space/test_mnist/HPC_comb_code/watershed_demo/energy/12_energy_map.png");
     
     //opt/project_space/test_mnist/HPC_comb_code/watershed_demo/energy/12_energy_map.png");
     
     
     ///opt/project_space/test_mnist/HPC_comb_code/watershed_demo/energy/32_energy_map.png");
  
     cv::Mat duplImage=srcImg;
     ///opt/project_space/test_mnist/HPC_comb_code/watershed_demo/energy/12_energy_map.png");

         
         //"Copyright-Norfolk-Castle-Museum.jpg");  
    
     //opt/project_space/te st_mnist/HPC_comb_code/watershed_demo/energy/2_energy_map.png");
     cv::imshow("test1",srcImg);
     cv::waitKey();
     WatershedAlg *walg=new WatershedAlg();
     walg->processImage(srcImg,duplImage);
   }
