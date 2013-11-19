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
cout << "Constructor" << endl;
}

CPPNodeType::~CPPNodeType()
{
cout << "Destructor " << endl;
}



void CPPNodeType::startNode(){
	cout << "startNode" << endl;	
}
void CPPNodeType::stopNode(){
	
}
AdaptationModel CPPNodeType::plan(ContainerRoot *actualModel,ContainerRoot *targetModel){

cout << "PLAN" << endl;	
}


PrimitiveCommand CPPNodeType::getPrimitive(PrimitiveCommand primitive){
	
}
