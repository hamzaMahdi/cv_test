#include "opencv2/opencv.hpp"
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/videoio.hpp>
#include "opencv2/imgcodecs.hpp"
#include <stdlib.h>
#include <stdio.h>
using namespace cv;
int main(int argc, char** argv)
{
    std::vector<cv::Vec3f> vecCircles;
    VideoCapture cap;
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(0))
        return 0;
    for(;;)
    {
       Mat frame;
	     Mat matProcessed;
       cap >> frame;
       if( frame.empty() ) break; // end of video stream
       	     inRange(frame,cv::Scalar(0,0,175),cv::Scalar(100,100,256),matProcessed);
       GaussianBlur(matProcessed,matProcessed,cv::Size(9,9),1.5);
       HoughCircles(matProcessed,vecCircles,CV_HOUGH_GRADIENT,2,matProcessed.rows/4,100,50,10,400);
        /// Draw the circles detected
        for( size_t i = 0; i < vecCircles.size(); i++ )
        {
            Point center(cvRound(vecCircles[i][0]), cvRound(vecCircles[i][1]));
            int radius = cvRound(vecCircles[i][2]);
            // circle center
            circle( frame, center, 3, Scalar(0,255,0), -1, 8, 0 );
            // circle outline
            circle( frame, center, radius, Scalar(0,0,255), 3, 8, 0 );
        }
        imshow("this is you, smile! :)", frame);
           
       //imshow("circle",matProcessed);
       if( waitKey(10) == 27 ) break; // stop capturing by pressing ESC 
    }
    // the camera will be closed automatically upon exit
    // cap.close();
    return 0;
}
