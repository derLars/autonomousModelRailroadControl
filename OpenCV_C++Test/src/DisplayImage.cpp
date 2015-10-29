#include <cv.h>
#include <highgui.h>
#include <iostream>

#include <math.h>
using namespace cv;

enum Color { B=0, G=1, R=2 };

vector<Point> detectCalibrationPaper(Mat frame);
double calculateAngle(Point p1, Point p2);

Mat filterEdges(Mat frame);
Mat rotateFrame(Mat frame, double angle);

vector<Point> calculateSection(Mat& frame);
void detectTrain(Mat& frame, Mat& frame2);
int main( int argc, char** argv )
{
	VideoCapture capture(-1);
  	if(!capture.isOpened())
  	{
  		std::cout << "No camera detected" << std::endl;
  	}
  	else
  	{
  		namedWindow("frame", CV_WINDOW_NORMAL);
  		namedWindow("section", CV_WINDOW_NORMAL);

  		Mat frame, image, prevImage, change;

  		capture.set(CV_CAP_PROP_FRAME_WIDTH,1024);
  		capture.set(CV_CAP_PROP_FRAME_HEIGHT,1024);

  		vector<Point> section,paper;

  		capture >> frame;

  		Point p1;
  		p1.x = 906;
  		p1.y = 348;

  		Point p2;
  		p2.x = 756;
  		p2.y = 367;

  		while(!paper.size())
  		{
  			capture >> frame;
  			paper = detectCalibrationPaper(frame);
  			waitKey(100);
  		}
		capture >> frame;

		frame = rotateFrame(frame,calculateAngle(paper[2], paper[3]));
		section = calculateSection(frame);

  		while(1)
  		{
  			capture >> frame;

  			frame = rotateFrame(frame,calculateAngle(paper[2], paper[3]));

  			frame = image = Mat(frame,Rect(section[0].x,section[0].y,section[1].x,section[1].y));

  			image = filterEdges(image);

  			if(!prevImage.empty())
  		  	{
  				absdiff(image, prevImage, change);
  				threshold(change, change, 40, 255, CV_THRESH_BINARY);
  				blur(change,change,Size(3,3));
  				imshow("prev",change);
  				detectTrain(change,frame);
  		  	}

  			imshow("frame", frame);
  			imshow("section", image);

  			waitKey(100);

  			prevImage = image.clone();
  		}
  	}

	return 0;
}

vector<Point> calculateSection(Mat& frame)
{
	vector<Point>vec;
	vec = detectCalibrationPaper(frame);

	Point offset, p1;

	offset.x = vec[0].x -730;
	offset.y = vec[0].y -175;

	p1.x = 990;
	p1.y = 310;

	vec.clear();
	vec.push_back(offset);
	vec.push_back(p1);

	return vec;
}

Mat filterEdges(Mat frame)
{
	namedWindow("x", CV_WINDOW_NORMAL);
	namedWindow("y", CV_WINDOW_NORMAL);

	Mat gradientX, gradientY;
	Mat gradientX_ABS, gradientY_ABS;

	cvtColor(frame,frame,CV_RGB2GRAY); //make colored frame grey

	Sobel(frame,gradientX,CV_16S,1,0,3,1,0,BORDER_DEFAULT); //sobel filter in x-direction
	Sobel(frame,gradientY,CV_16S,0,1,3,1,0,BORDER_DEFAULT); //sobel filter in y-direction

    convertScaleAbs( gradientX, gradientX_ABS );
	convertScaleAbs( gradientY, gradientY_ABS );

	addWeighted(gradientX_ABS,0.5,gradientY_ABS,0.5,0,frame); //join filtered frames

	imshow("x", gradientX_ABS);
	imshow("y", gradientY_ABS);

	return frame;
}

vector<Point> calculateVectorEdges(vector<Point> inputVec)
{
	vector<Point> outputVec;

	Point xMin_yMin; //
	xMin_yMin.x = 9999;
	xMin_yMin.y = 9999;

	Point yMax_xMin; //
	yMax_xMin.x = 9999;
	yMax_xMin.y = 0;

	Point yMin_xMax; //
	yMin_xMax.x = 0;
	yMin_xMax.y = 9999;

	Point xMax_yMax; //
	xMax_yMax.x = 0;
	xMax_yMax.y = 0;

	for(int i = 0; i <inputVec.size(); i++)
	{
		xMin_yMin = inputVec[i].x < xMin_yMin.x ? inputVec[i] : xMin_yMin;
		xMax_yMax = inputVec[i].x > xMax_yMax.x ? inputVec[i] : xMax_yMax;

		yMin_xMax = inputVec[i].y < yMin_xMax.y ? inputVec[i] : yMin_xMax;
		yMax_xMin = inputVec[i].y > yMax_xMin.y ? inputVec[i] : yMax_xMin;

		if(inputVec[i].x <= xMin_yMin.x)
		{
			xMin_yMin = inputVec[i].y < xMin_yMin.y ? inputVec[i] : xMin_yMin;
		}

		if(inputVec[i].x >= xMax_yMax.x)
		{
			xMax_yMax = inputVec[i].y > xMax_yMax.y ? inputVec[i] : xMax_yMax;
		}

		if(inputVec[i].y <= yMin_xMax.y)
		{
			yMin_xMax = inputVec[i].x > yMin_xMax.x ? inputVec[i] : yMin_xMax;
		}

		if(inputVec[i].y >= yMax_xMin.y)
		{
			yMax_xMin = inputVec[i].x < yMax_xMin.x ? inputVec[i] : yMax_xMin;
		}
	}
	outputVec.push_back(xMin_yMin);
	outputVec.push_back(yMin_xMax);
	outputVec.push_back(xMax_yMax);
	outputVec.push_back(yMax_xMin);

	return outputVec;
}

vector<Point> detectCalibrationPaper(Mat frame)
{
	Mat frameGray, thr;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//Canny edge detection
	cvtColor(frame,frameGray,CV_RGB2GRAY); //make colored frame grey
	Canny( frame, frameGray, 255, 1, 3 );

	threshold( frameGray, thr, 50, 255, THRESH_BINARY );
	findContours( thr, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	vector<vector<Point> > contours_poly( contours.size() );
	Mat drawing = Mat::zeros(thr.size(), CV_8UC3);
	Scalar color = Scalar(0, 0, 255);
	int i=0;
	for(i = 0; i < contours.size(); i++ )
	{
		if(contourArea( contours[i],false) > 12000)
		{
			approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
			drawContours( drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point() );

			break;
		}
	}

	return calculateVectorEdges(contours[i]);
}

void detectTrain(Mat& frame, Mat& frame2)
{
	Mat frameGray, thr;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//Canny edge detection
	//threshold( frameGray, thr, 50, 255, THRESH_BINARY );
	findContours( frame, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );

	Mat drawing = Mat::zeros(frame.size(), CV_8UC3);
	Scalar color = Scalar(0, 0, 255);
	int i=0;
	int indx = 0;
	for(i = 0; i < contours.size(); i++ )
	{
		if(contourArea( contours[i],false) > contourArea( contours[indx],false))
		{
			indx = i;
		}


		//boundRect[i] = boundingRect( Mat(contours_poly[i]) );
			//drawContours( drawing, boundRect, i, color, 1, 8, vector<Vec4i>(), 0, Point() );

		//break;
	}
	if(contours.size())
	{
		approxPolyDP( Mat(contours[indx]), contours_poly[indx], 3, true );
		boundRect[indx] = boundingRect( Mat(contours_poly[indx]) );
		rectangle( frame2, boundRect[indx].tl(), boundRect[indx].br(), color, 2, 8, 0 );
	}
	//imshow("Train", drawing);
}



double calculateAngle(Point p1, Point p2)
{
	return atan((p2.y - p1.y)/(double)(p2.x - p1.x)) * 180 / CV_PI;
}

Mat rotateFrame(Mat frame,double angle)
{
	Point2f center(frame.cols/2, frame.rows/2);
	Mat rot_mat = getRotationMatrix2D(center, angle, 1.0);
	Mat dst;
	warpAffine(frame, dst, rot_mat, frame.size());

	return dst;
}

void blurr(Mat& frame)
{
	vector<Vec4i> lines;
	HoughLinesP(frame, lines, 1, CV_PI/180, 80, 100, 10);
}

int index(int x, int y, Mat& image, Color color)
{
	return (y * image.rows * image.channels()) + (x * image.channels()) + color;
}

int pixel(int x, int y, Mat& image, Color color)
{
	return (int)image.data[index(x, y, image, color)];
}

