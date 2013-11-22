#include "CPPNodeType.h"


extern "C"{  
    AbstractNodeType* create(){
    return new CPPNodeType();
   }                        
}
extern "C" void destroy_object( AbstractNodeType* object )
{
  delete object;
}


CPPNodeType::CPPNodeType()
{

}

CPPNodeType::~CPPNodeType()
{

}



void CPPNodeType::startNode()
{

}
void CPPNodeType::stopNode(){
	
}

AdaptationModel *CPPNodeType::plan(ContainerRoot *currentModel,ContainerRoot *targetModel,TraceSequence *traces)
{

AdaptationModel *adaptationmodel = planner.compareModels(currentModel,targetModel,node->name,traces);
// todo schedule jgraph
       

return adaptationmodel;
}


PrimitiveCommand CPPNodeType::getPrimitive(PrimitiveCommand primitive){
	
}
