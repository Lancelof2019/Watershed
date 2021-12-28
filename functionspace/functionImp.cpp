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





Mat WatershedAlg::thresholdOtsu(Mat image) {
    

        //threshold(image, image,ZERO,ONE, CV_THRESH_BINARY |         CV_THRESH_OTSU);

        cv::adaptiveThreshold(image,image,255,cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY,  45,2);
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





Mat WatershedAlg::inverseImage(Mat image) {
        for(int i = 0; i < image.rows; i++) {

            for(int j = 0; j < image.cols; j++) {
                if( (int) image.at<uchar>(i,j) == ZERO ) {
                    image.at<uchar>(i,j) = ONE;
                } else {
                    image.at<uchar>(i,j) = ZERO;
                }
            }
        }

        return image;
    }



Mat WatershedAlg::antiInverseImage(Mat image) {
        for(int i = 0; i < image.rows; i++) {

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



Mat WatershedAlg::erosion(Mat image, vector< vector <int> > kernel) {
        int n = kernel.size();
        int m = kernel[0].size();

        vector< vector < bool> > shouldBeZeroImage(image.rows, vector<bool>(image.cols, false));
        for(int i = n / 2; i < image.rows - n / 2; i++) {
            for(int j = m / 2; j < image.cols - m / 2; j++) {

                // Loop the kernel
                if( (int) image.at<uchar>(i, j) == ONE) {
                    bool shouldBeZero = false;
                    for(int crtX = i - n / 2, x = 0; crtX <= i + n / 2; crtX++, x++) {
                        for(int crtY = j - m / 2, y = 0; crtY <= j + m / 2; crtY++, y++) {
                            if((int) image.at<uchar>(crtX, crtY) == ZERO && kernel[x][y] == 1) {
                                shouldBeZero = true;
                                break;
                            }
                        }
                    }

                    if(shouldBeZero) {
                        shouldBeZeroImage[i][j] = true;
                    }
                }
            }
        }

        for(int i = 0; i < image.rows; i++) {
            for(int j = 0; j < image.cols; j++) {
                if(shouldBeZeroImage[i][j]) {
                    image.at<uchar>(i, j) = ZERO;
                }
            }
        }

        string filename11="/opt/test11.txt";
 
        ofstream fout11(filename11);
        for(int i = 0; i < image.rows; i++) {
         for(int j = 0; j < image.cols; j++) {

          fout11<<image.at<Vec3b>(i,j)<<",";
             

         }
         fout11<<endl;
       }
        
        fout11.close();


        return image;
    }



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

Mat WatershedAlg::watershed(Mat image, vector<Point> const &markers,Mat duplImage) {
 
        string filename5="/opt/test5.txt";
        ofstream fout5(filename5);
        priority_queue<Pixel,vector<Pixel>,Compare> prioq;//compare the value of image.at<uchar>(i,j)
        Mat markerImage(image.rows, image.cols, CV_8UC3, Scalar::all(0));
            vector<cv::Vec3b> colors{ {0, 0, 0} };
            for(int i = 1; i <= markers.size()+1; i++) {
            Vec3b vecColor;
            vecColor[0] = rand()%255+0;
            vecColor[1] = rand()%255+1;
            vecColor[2] = rand()%255+2;
            //vecColor[3] = 0.5;
            
            colors.push_back(vecColor);
        }
  
        
        vector<vector<int>> markerMap(image.rows, vector<int>(image.cols, 0));
        vector<vector<bool>> inprioq(image.rows, vector<bool>(image.cols, false));
        vector<int> dx{-1, 1, 0, 0, -1, -1, 1, 1};
        vector<int> dy{0, 0, -1, 1, -1,  1, 1, -1};

        // Put markers in priority queue
        int id = 1;
        Mat testDuplicate=duplImage;
        Mat dstImage;
  

        for(auto marker: markers) {
     
            markerMap[marker.x][marker.y] = id;
            
            for(int i = 0; i < 4; i++) {

                int newX = marker.x + dx[i];
                int newY = marker.y + dy[i];
                if(newX < 0 || newY < 0 || newX >= image.rows || newY >= image.cols) {
                    continue;
                }
                cout<<"The current marker point:"<<marker<<endl;
                cout<<(int)image.at<uchar>(marker.x, marker.y)<<endl;
                cout<<"----------------"<<endl;
                cout<<"next position:"<<"["<<newX<<","<<newY<<"]"<<endl;
                cout<<(int)image.at<uchar>(newX, newY)<<endl;

                prioq.push( Pixel( (int) image.at<uchar>(newX, newY), newX, newY) );//start from the neighuobors who got bigger value
                
            }

            id++;
        }



              cout<<"The first time when the next points,the size is: "<<prioq.size()<<endl;

              priority_queue<Pixel,vector<Pixel>,Compare> tmp_prioq;

              tmp_prioq=prioq;

     
         string filename7="/opt/test7.txt";
         ofstream fout7(filename7);
         for(int i = 0; i < image.rows; i++) {
           for(int j = 0; j < image.cols; j++) {

             fout7<<markerMap[i][j]<<",";
             

         }
           fout7<<endl;
     }
          fout7.close();

          //each marker got its position and its neighbour<--> ^ and V
      
        cv::imshow("test2.jpg",image);
        cv::waitKey(0);
        for(int i = 0; i < image.rows; i++) {
            for(int j = 0; j < image.cols; j++) {

             fout5<<((int)markerMap[i][j])<<",";
             

        }
         fout5<<endl;
     }
     fout5.close();
     
        while(!prioq.empty()) {
            Pixel curpoint = prioq.top(); prioq.pop();//store the neighbours near ctrx and ctry

            bool canLabel = true;
            int neighboursLabel = 0;
            for(int i = 0; i < 4; i++) {
                int nextX = curpoint.x + dx[i];
                int nextY = curpoint.y + dy[i];
                if(nextX < 0 || nextY < 0 || nextX >= image.rows || nextY >= image.cols) {
                    continue;
                }
                Pixel next = Pixel( (int) image.at<uchar>(nextX, nextY), nextX, nextY);

                // Must check if all surrounding marked have the same color
                if(markerMap[next.x][next.y] != 0 && next.val != 0) {
                    if(neighboursLabel == 0) {
                        neighboursLabel = markerMap[next.x][next.y];
                    } else {
                        if(markerMap[next.x][next.y] != neighboursLabel ) {
                            canLabel = false;
                        }
                    }
                } else {
                    if(inprioq[nextX][nextY] == false) {
                        inprioq[next.x][next.y] = true;//aviod duplicate point is chosen
                        prioq.push(next);
                        //the most important expending step,//only the point whose pixel value is 0 in Markermap
                    }
                }
            }

            if(canLabel&&(int)image.at<uchar>(curpoint.x,curpoint.y)!=0) {
                
                markerMap[curpoint.x][curpoint.y] = neighboursLabel;
               duplImage.at<Vec3b>(curpoint.x,curpoint.y)=colors[ markerMap[curpoint.x][curpoint.y] ];
         
                
            }
         
        }
        cv::addWeighted(duplImage,1.5,testDuplicate,0.3,0,dstImage);
    
        return dstImage;
    }

void WatershedAlg::processImage(Mat image,Mat duplImage)  {
        // Make image grayscale
       image = makeImageGrayScale(image);

        cv::imshow("makeImageGrayScale",image);
        cv::waitKey(0);

        // Apply threshold
        image = thresholdOtsu(image);
        cv::imshow("thresholdOtsu",image);
        cv::waitKey(0);
       
     
        // Inverse pixels
    
       // image = inverseImage(image);
        //cv::imshow("inverseImage",image);
       // cv::waitKey(0);

       image=antiInverseImage(image);
       cv::imshow("antiInverseImage",image);
       cv::waitKey(0);
        // Erode foreground
        vector< vector<int> > erosionTargetThree{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, };
       image = erosion(image, erosionTargetThree);
        //image=testErosion(image, erosionTargetThree);
        Mat tempImage= image;
        cv::imshow("erosion",image);
        cv::waitKey(0);
        // Apply distance transform
        vector<Point> markers;
        image = distanceTransform(image, markers);
        //image=testDistanceTransform(image, markers);
        Mat distanceImage = image;
        cv::imshow("distance transformation",distanceImage);
        cv::waitKey(0);
        cout << "Detected " << markers.size() << " markers \n";

        // Watershed
       if(markers.size() == 0) {
            for(int i = 0; i < image.rows; i++) {
                for(int j = 0; j < image.cols; j++) {
                    if((int) distanceImage.at<uchar>(i,j) != 0) {
                        markers.push_back(Point(i, j));
                        image.at<uchar>(i, j) = 25;
                        cv::imshow("watershed result",image);
                        cv::waitKey(0);
                        //return watershed(image, markers);
                    }
                }
            }
        }


        image = watershed(image, markers,duplImage);
        cv::imshow("watershed result",image);
        cv::waitKey(0);

    }
