#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
#include <queue>
#include <cstdlib> 
#include <vector>
using namespace cv;

bool comp(Point a,Point b){
      if(a.x!=b.x){
         return a.x<b.x;
      }
      return a.y<b.y;

}

Mat WatershedAlg::distanceTransform(Mat image, vector<Point> &markers) {
        vector< vector<double> > distanceMap(image.rows, vector<double>(image.cols, 0));
        Mat markerImage(image.rows, image.cols, CV_8UC3, Scalar::all(0));
        queue<int> qx, qy;
        vector<int> dx{-1, 1, 0, 0, -1, -1, 1, 1};
        vector<int> dy{0, 0, -1, 1, -1,  1, 1, -1};
        int pixelThreshold=120;
        vector<bool>checkVisted;
        vector<Point>zeroEdge;
        vector< vector<bool> > visited(image.rows, vector<bool>(image.cols, false));
//******It makes the nearest piexel along 0 point sohow up and become the edge pixel
        for(int i = 0; i < image.rows; i++) {
            for(int j = 0; j < image.cols; j++) {
                
                if(image.at<uchar>(i, j) != ZERO) {
                    continue;
                }
                //this is the part that sepreated from the edge
                
                for(int h = 0; h < 4; h++) {
                    int nextX = i + dx[h];
                    int nextY = j + dy[h];

                    if( nextX < 0 || nextY < 0 || nextX >= image.rows || nextY >= image.cols ) {
                        continue;
                    }

                    if( !visited[nextX][nextY] && (int) image.at<uchar>(nextX, nextY) == ONE ) {
                        visited[nextX][nextY] = true;
                        image.at<uchar>(nextX, nextY) = pixelThreshold;
                        qx.push(nextX);
                        qy.push(nextY);
                       //the neighuours are all points who have 75 or 0 
                       //they are the points who are edges
                       checkVisted.push_back(visited[nextX][nextY]);

                    }
                }
                if(checkVisted[0]||checkVisted[1]||checkVisted[2]||checkVisted[3]){


                  zeroEdge.push_back(Point(i,j));
                  checkVisted.clear();
                }

         
             

        }
        
     }
     //******It makes the nearest piexel along 0 point sohow up and become the edge pixel
    
     //edge is equal to 50

        while(!qx.empty()) {
            int crtX = qx.front(); qx.pop();
            int crtY = qy.front(); qy.pop();

            bool isBigger = true;//check
            for(int h = 0; h < 8; h++) {
                int nextX = crtX + dx[h];
                int nextY = crtY + dy[h];

                if( nextX < 0 || nextY < 0 || nextX >= image.rows || nextY >= image.cols || (int) image.at<uchar>(nextX, nextY) == ZERO ) {
                    continue;
                }

                if( (int) image.at<uchar>(crtX, crtY) <= (int) image.at<uchar>(nextX, nextY)) {
                    isBigger = false;
                    
                }
                //pick the max local value of some regions

                if( (int) image.at<uchar>(crtX, crtY) +1< (int) image.at<uchar>(nextX, nextY) ) {
                    visited[nextX][nextY] = true;
                    image.at<uchar>(nextX, nextY) = (uchar) min((image.at<uchar>(crtX, crtY)+1), 254);            
                    qx.push(nextX);
                    qy.push(nextY);
                  
                }
               
            }
         
            if(isBigger) {
                markers.push_back(Point(crtX, crtY));
              
            }
        
         
                            

        }
        


     pixelThreshold=pixelThreshold-1;
     int pnumThrshold=30;
     int handlingType=0;
     int neighbourType=0;
     removeholesopt(image,pnumThrshold,  handlingType, neighbourType, pixelThreshold);
	 
     return image;
    }
