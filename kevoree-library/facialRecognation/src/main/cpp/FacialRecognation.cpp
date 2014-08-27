
#include "FacialRecognation.h"

// todo generate
extern "C"{
AbstractComponent* create(){

	LOGGER_WRITE(Logger::DEBUG, "Creating FacialRecognation  Component" );
	return new FacialRecognation();
}
}
extern "C" {
void destroy_object(FacialRecognation  * object )
{
	delete object;
}
}




using namespace std;

void ThreadFunction(FacialRecognation *ptr,VideoCapture *capture, Mat *frame)
{



	if(!capture->isOpened()){
		LOGGER_WRITE(Logger::DEBUG, "Unable to open Video Stream" );
	}else{
		LOGGER_WRITE(Logger::DEBUG, " Video Stream  Open"   );
	}




	long curr = 0 ;
	long potentialVal = 0;


	LOGGER_WRITE(Logger::DEBUG, " Video Stream  Open"   );
	milliseconds timestamp = duration_cast< milliseconds >(high_resolution_clock::now().time_since_epoch());
	LOGGER_WRITE(Logger::DEBUG, " Video Stream  Open"   );
	duration<double> threshold = duration<double>(0.3);
	LOGGER_WRITE(Logger::DEBUG, " Video Stream  Open"   );
	for(;;)
	{
		LOGGER_WRITE(Logger::DEBUG, " Video Stream  Open"   );
		(*capture) >> (*frame);
		LOGGER_WRITE(Logger::DEBUG, " Video Stream  Open"   );
		//-- 3. Apply the classifier to the frame
		if( !frame->empty() )
		{ long curr2 = ptr->detectAndDisplay(*frame );
		milliseconds timestamp1 = duration_cast< milliseconds >(high_resolution_clock::now().time_since_epoch());
		duration<double> time_span = duration_cast<duration<double> > (timestamp1 - timestamp) ;

		if( curr2 == potentialVal && time_span > threshold)
		{
			curr = potentialVal ;
			std::ostringstream ss;
			ss << curr;
			ptr->send("output",ss.str());
			timestamp = timestamp1 ;
		}else if(curr2 == curr){
			timestamp = timestamp1 ;
		}else if(curr2 != curr && time_span <= threshold){
			if(potentialVal != curr2){
				potentialVal = curr2 ;
				timestamp = timestamp1 ;
			}
		}
		}
		else
		{
			LOGGER_WRITE(Logger::INFO," --(!) No captured frame -- Break!" );

		break;
		}

		int c = waitKey(10);
		if( (char)c == 'c' ) { break; }
	}


}




FacialRecognation::FacialRecognation()
{
	face_cascade =  CascadeClassifier() ;
	eyes_cascade = CascadeClassifier() ;

}
FacialRecognation::~FacialRecognation()
{


}

void FacialRecognation::start()
{

		this->started = 1 ;
		cout << "Start"<< endl ;
		face_cascade.load("/Users/Aymeric/Documents/dev_Kevoree/kevoree-cpp/kevoree-library/FacialRecognation/ressources/lbpcascade_frontalface.xml" );
		cout << "Start"<< endl ;
		VideoCapture* capture = new VideoCapture() ;
		cout << "Start"<< endl ;
	    Mat  *frame = new Mat();
		cout << "Start"<< endl ;
		capture->open(-1);
		cout << "Start"<< endl ;
		(*capture) >> (*frame);
		cout << "Start"<< endl ;
		t= new boost::thread (&ThreadFunction,this,capture,frame );

}

void FacialRecognation::stop(){
	//chat->close();
	this->started = 0;
	t->interrupt();
	t->join();

}


void FacialRecognation::update()
{

}


/**
 * @function detectAndDisplay
 */
long FacialRecognation::detectAndDisplay( Mat frame )
{

	std::vector<Rect> faces;
	Mat frame_gray;

	cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
	equalizeHist( frame_gray, frame_gray );

	//-- Detect faces
	face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0, Size(80, 80) );
	long res =faces.size() ;

	for( size_t i = 0; i < faces.size(); i++ )
	{
		Mat faceROI = frame_gray( faces[i] );
		std::vector<Rect> eyes;

		//-- In each face, detect eyes
		eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CV_HAAR_SCALE_IMAGE, Size(30, 30) );
		//-- Draw the face
		Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
		ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar( 255, 0, 0 ), 2, 8, 0 );

	}
	//-- Show what you got
//	imshow( "Capture - Face detection", frame );
	return res ;

}

