#include "/opt/project_space/test_mnist/HPC_comb_code/MA/Watershed_Algorithm/headerspace/WatershedAlg.h"
using namespace cv;

Mat WatershedAlg::distanceTransform(Mat image, vector<Point> &markers) {
        vector< vector<double> > distanceMap(image.rows, vector<double>(image.cols, 0));
        Mat markerImage(image.rows, image.cols, CV_8UC3, Scalar::all(0));
        queue<int> qx, qy;
        vector<int> dx{-1, 1, 0, 0, -1, -1, 1, 1};
        vector<int> dy{0, 0, -1, 1, -1,  1, 1, -1};

        string filename1="/opt/test1.txt";
        string filename2="/opt/test2.txt";
        string filename3="/opt/test3.txt";
        string filename4="/opt/test4.txt";
        string filename5="/opt/test5.txt";
        ofstream fout1(filename1);
        ofstream fout2(filename2);
        ofstream fout3(filename3);
        ofstream fout4(filename4);
        ofstream fout5(filename5);
        vector< vector<bool> > visited(image.rows, vector<bool>(image.cols, false));


        


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
                        image.at<uchar>(nextX, nextY) = 50;
                        qx.push(nextX);
                        qy.push(nextY);
                       // fout1<<(image.at<uchar>(nextX, nextY))<<",";
                       //the neighuours are all points who have 75 or 0 
                       //they are the points who are edges

                    }
                }

                  //if(j==image.cols-1){


                  // fout1<<endl;

                //  }

            }
        }

      
//
     for(int i = 0; i < image.rows; i++) {
         for(int j = 0; j < image.cols; j++) {

          fout1<<((int)image.at<uchar>(i,j))<<",";
             

        }
         fout1<<endl;
     }
        
        fout1.close();
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
                    //cout<<"The image at crtx:"<<crtX<<"and crty:"<<crtY<<" "<<(int)image.at<uchar>(crtX, crtY)<<endl;
                    //cout<<"The image at nextX:"<<nextX <<"and nextY:"<<nextY<<" "<<(int)image.at<uchar>(nextX, nextY)<<endl;
                    qx.push(nextX);
                    qy.push(nextY);
                    fout4<<"the postion of push point: "<<Point(nextX,nextY)<<"The value of image: "<<((int)image.at<uchar>(nextX,nextY))<<",";

                    

                }
                fout4<<endl;
            }
           //find the max value in local area
            if(isBigger) {
                markers.push_back(Point(crtX, crtY));
                cout<<"******************Potion and values******************"<<endl;
                cout<<Point(crtX, crtY)<<endl;


                cout<<(int)image.at<uchar>(crtX,crtY)<<endl;
                //cout<<(int)image.at<uchar>(crtX,crtY)
                cout<<"The other parts of the value in position ctrx and ctry "<<endl;
                for(int h = 0; h < 8; h++) {
                  int temp_nextX = crtX + dx[h];
                  int temp_nextY = crtY + dy[h];
                   if( temp_nextX < 0 || temp_nextY < 0 || temp_nextX >= image.rows || temp_nextY >= image.cols || (int) image.at<uchar>(temp_nextX, temp_nextY) == ZERO ) {
                    continue;
                }
                  cout<<"The value of "<<"["<<temp_nextX<<","<<temp_nextY<<"]:"<<(int)image.at<uchar>(temp_nextX,temp_nextY)<<endl;
                }
                markerImage.at<Vec3b>(crtX, crtY) = {0, 255, 0};

                //mark these compared points from last for loop
                cout<<"******************Potion and values******************"<<endl;
              //there will be 4 points

            }
        
        }
/*
        for(vector<Point>::iterator it=markers.begin();it!=markers.end();it++){
         cout<<"-----The value in Point----"<<endl;
         cout<<*it<<endl;
         cout<<(*it).x<<endl;
         cout<<(*it).y<<endl;
         cout<<"--------------------------"<<endl;

        }
         
*/

     for(int i = 0; i < image.rows; i++) {
         for(int j = 0; j < image.cols; j++) {

          fout3<<markerImage.at<Vec3b>(i,j)<<",";
             

        }
         fout3<<endl;
     }
        
        fout3.close();

        
////
     for(int i = 0; i < image.rows; i++) {
         for(int j = 0; j < image.cols; j++) {

          fout2<<((int)image.at<uchar>(i,j))<<",";
             

        }
         fout2<<endl;
     }
///////
         fout2.close();
        //imshow("Distance: ", image);
        return image;
    }
