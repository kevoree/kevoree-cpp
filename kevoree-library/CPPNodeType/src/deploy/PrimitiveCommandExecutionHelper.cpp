#include "PrimitiveCommandExecutionHelper.h"
#include "KevoreeParDeployPhase.h"
#include "../Primitives.h"
#include <stdexcept>

bool PrimitiveCommandExecutionHelper::execute(ContainerNode *rootNode,AdaptationModel *adaptionModel,AbstractNodeType *nodeInstance)
{
	bool res;
	KevoreeParDeployPhase *phase=NULL;
	ParallelStep *orderedPrimitiveSet = adaptionModel->orderedPrimitiveSet;
	if(orderedPrimitiveSet == NULL)
	{
		LOGGER_WRITE(Logger::ERROR,"orderedPrimitiveSet is NULL");
		return false;
	}
	phase = new KevoreeParDeployPhase();
	res = executeStep(rootNode,orderedPrimitiveSet,nodeInstance,phase);
	
	LOGGER_WRITE(Logger::DEBUG,"Clean ParallelStep");
	cleanParallelStep(orderedPrimitiveSet);
	adaptionModel->orderedPrimitiveSet = NULL;
	  
	if(phase != NULL)
	{
		delete phase;
	}
	return res;
}

bool PrimitiveCommandExecutionHelper::cleanParallelStep(ParallelStep *step)
{
	  if (step == NULL)
	  {
          return true;
      }	
      ParallelStep *next = step->nextStep;  
      /*
      for ( std::unordered_map<string,AdaptationPrimitive*>::iterator it = step->adaptations.begin();  it != step->adaptations.end(); ++it)
		{
			AdaptationPrimitive *p  = it->second;
	
				cout << p << " " << p->primitiveType << p->ref->path() << endl;
					delete p;	
					it->second=NULL;
					//p->ref=NULL;
		
		
		}*/
      delete step;   
      return  cleanParallelStep(next);
}

bool PrimitiveCommandExecutionHelper::executeStep(ContainerNode *rootNode,ParallelStep *step,AbstractNodeType *nodeInstance,KevoreeParDeployPhase *phase){
	     if (step == NULL)
	     {
            return true;
         }
		try 
		{
				for (std::unordered_map<string,AdaptationPrimitive*>::const_iterator it = step->adaptations.begin();  it != step->adaptations.end(); ++it) 
				{
					AdaptationPrimitive *adaptation = it->second;
					PrimitiveCommand *primitive = nodeInstance->getPrimitive(adaptation);
					if(primitive != NULL)
					{
						if(!primitive->execute())
						{
							LOGGER_WRITE(Logger::ERROR,"The Primitive "+it->first+" "+adaptation->primitiveType);
							return false;
						}
						delete primitive;
					}
					else
					{
							LOGGER_WRITE(Logger::ERROR,"PrimitiveCommand is NULL");
					}
					
				}
				return executeStep(rootNode,step->nextStep,nodeInstance,phase);
	       }
    catch ( const std::exception & e )
    {
        std::cerr << e.what() << endl;
    }
}
