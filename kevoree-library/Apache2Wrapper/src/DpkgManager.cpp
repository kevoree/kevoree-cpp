#include "DpkgManager.h"
#include <cstdlib>

// todo generate
extern "C"{  
    AbstractComponent* create(){
    return new Apache2Wrapper();
   }                        
}
extern "C" {
	void destroy_object( Apache2Wrapper * object )
	{
	  delete object;
	}
}


Apache2Wrapper::Apache2Wrapper()
{
	

}
Apache2Wrapper::~Apache2Wrapper()
{


}

void Apache2Wrapper::start()
{
	system("/etc/init.d/apache2 start");	 
}

void Apache2Wrapper::stop(){
	system("/etc/init.d/apache2 stop");	
}


void Apache2Wrapper::update()
{	
	
}

