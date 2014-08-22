#ifndef __FakeConsole_H
#define __FakeConsole_H


#include <kevoree-core/api/AbstractComponent.h>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <sstream>
#include <iostream>
#include <chrono>
#include <stdio.h>


#pragma ComponentType "facialrecognation"
#pragma Input "Output"

using namespace std;
using namespace std::chrono;
using namespace cv;

class FacialRecognation :public AbstractComponent
{
public:
	FacialRecognation();
	~FacialRecognation();

	void start();
	void stop();
	void update();
	boost::thread *t;
	int started;
	long detectAndDisplay(Mat );


	CascadeClassifier face_cascade;
	CascadeClassifier eyes_cascade;

};

#endif /*__FakeConsole_H*/

