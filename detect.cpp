#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

VideoCapture videonih("vid/bola.mp4");
Mat vid, vidKecil, vid_hsv, mask, thresh;

int main(){

    int low_hue   = 0;
    int upper_hue = 21;
    int low_sat   = 0;
    int upper_sat = 255;
    int low_v     = 0;
    int upper_v   = 255;

    namedWindow("Trackbar", WINDOW_AUTOSIZE);
    createTrackbar("low_hue",   "Trackbar", &low_hue, 180);
    createTrackbar("upper_hue", "Trackbar", &upper_hue, 180);
    createTrackbar("low_sat",   "Trackbar", &low_sat, 255);
    createTrackbar("upper_sat", "Trackbar", &upper_sat, 255);
    createTrackbar("low_v",     "Trackbar", &low_v, 255);
    createTrackbar("upper_v",   "Trackbar", &upper_v, 255);

    while(1){

        videonih >> vid;

        resize(vid, vidKecil, Size(), 0.3, 0.3, INTER_LINEAR);
        cvtColor(vidKecil, vid_hsv, COLOR_BGR2HSV);

        inRange(vid_hsv, Scalar(20, 70, 0), Scalar(120, 240, 255), thresh);
       
        vector<vector<Point>> contours;
        findContours(thresh, contours, RETR_TREE, CHAIN_APPROX_NONE);

        for(int i = 0; i < contours.size(); i++){
            vector<Point>contours_new;
            Point2f center;
            float radius;
            contours_new = contours[i];
            minEnclosingCircle(contours_new, center, radius);

            if (radius > 30 && radius < 78){
                circle(vidKecil, center, radius, Scalar(255, 0, 0), 3);
                printf("x: %2f y: %2f rad %f\n\n", center.x, center.y, radius);
            }
        }
    
        imshow("test kecil", vidKecil);
        //imshow("test hsv", vid_hsv);
        //imshow("test mask", thresh);

    char c = waitKey(100);
    if (c == 'q'){
        break;
        }
    }

    videonih.release();

}

