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
system("/etc/init.d/apache2 start");
		 
}

void DpkgManager::stop(){
	system("/etc/init.d/apache2 stop");	
}


void DpkgManager::update()
{	
	
}

