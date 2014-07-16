
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




FakeConsole::FakeConsole()
{

}
FakeConsole::~FakeConsole()
{


}

void FakeConsole::start()
{


}

void FakeConsole::stop(){

}


void FakeConsole::update()
{

}
