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
AdaptationModel *CPPNodeType::plan(ContainerRoot *actualModel,ContainerRoot *targetModel){

cout << "PLAN" << endl;	


return NULL;
}


PrimitiveCommand CPPNodeType::getPrimitive(PrimitiveCommand primitive){
	
}
