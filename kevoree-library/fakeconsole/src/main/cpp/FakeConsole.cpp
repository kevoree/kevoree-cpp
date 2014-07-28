
#include "FakeConsole.h"

// todo generate
extern "C"{
AbstractComponent* create(){
	return new FakeConsole();
}
}
extern "C" {
void destroy_object( FakeConsole * object )
{
	delete object;
}
}




using namespace std;

void ThreadFunction(FakeConsole *ptr)
{
	/*int argc=0;
	char **argv=NULL;
	QApplication a(argc, argv);
	ptr->chat =new ChatDialog();
	ptr->chat->setFakeConsole(ptr);
	ptr->chat->show();
	a.exec();*/

	while(ptr->started == 1)
		{
			ptr->send("Output","tick");

			sleep(1);
		}


}




FakeConsole::FakeConsole()
{

}
FakeConsole::~FakeConsole()
{


}

void FakeConsole::start()
{

	this->started = 1;
	t= new boost::thread(&ThreadFunction,this);

}

void FakeConsole::stop(){
	//chat->close();
	this->started = 0;
	t->interrupt();
	t->join();

}


void FakeConsole::update()
{

}

void FakeConsole::receive(std::string msg){

	std::cout << "FakeConsole receive "<< msg << std::endl;
	//chat->appendMessage("todo",msg.c_str());
}
