#include "CPPNodeType.h"


extern "C"{  
    INodeType* create(){
    return new CPPNodeType();
   }                        
}
extern "C" void destroy_object( INodeType* object )
{
  delete object;
}


CPPNodeType::CPPNodeType()
{

}

CPPNodeType::~CPPNodeType()
{

}



void CPPNodeType::startNode(){
	cout << "startNode" << endl;	
}
void CPPNodeType::stopNode(){
	
}
AdaptationModel CPPNodeType::compareModels(ContainerRoot *actualModel,ContainerRoot *targetModel,string nodename)
{
	
}

AdaptationModel *CPPNodeType::plan(ContainerRoot *currentModel,ContainerRoot *targetModel)
{

DefaultkevoreeadaptationFactory *factory  = new DefaultkevoreeadaptationFactory();
AdaptationModel  *adaptationModel =    factory->createAdaptationModel();


       

return NULL;
}


PrimitiveCommand CPPNodeType::getPrimitive(PrimitiveCommand primitive){
	
}
