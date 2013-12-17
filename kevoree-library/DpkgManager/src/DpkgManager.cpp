#include "DpkgManager.h"
#include <cstdlib>

// todo generate
extern "C"{  
    AbstractComponent* create(){
    return new DpkgManager();
   }                        
}
extern "C" {
	void destroy_object( DpkgManager * object )
	{
	  delete object;
	}
}


DpkgManager::DpkgManager()
{
	

}
DpkgManager::~DpkgManager()
{


}

void DpkgManager::start()
{
		cout << "method START" << endl;
system("/etc/init.d/apache2 start");
		 
}

void DpkgManager::stop(){
	cout << "method STOP" << endl;
	system("/etc/init.d/apache2 stop");	
}


void DpkgManager::update()
{	
	
}

