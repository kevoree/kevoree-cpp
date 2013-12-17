#ifndef __Planner_H
#define __Planner_H

#include <kevoree-core/model/kevoreeadaptation/kevoreeadaptation.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/ContainerNode.h>
#include <microframework/api/trace/TraceSequence.h>
#include <kevoree-core/model/kevoreeadaptation/AdaptationModel.h>
#include <kevoree-core/model/kevoreeadaptation/DefaultkevoreeadaptationFactory.h>	
#include <kevoree-core/model/kevoree/kevoree.h>
#include <set>
#include "Primitives.h"

class Planner 
{
	public:
	AdaptationModel* compareModels(ContainerRoot *actualModel,ContainerRoot *targetModel,string nodeName,TraceSequence *traces);
	AdaptationModel* schedule(AdaptationModel *adaptationModel,std::string nodeName);	
	private:
	AdaptationPrimitive* adapt(Primitives p,KMFContainer *elem);
	DefaultkevoreeadaptationFactory factory;	
};




class TupleObjPrim 
{
	public:
	TupleObjPrim(KMFContainer *_obj,Primitives _p){
		this->obj = _obj;
		this->p =_p;
	}
	bool equals(TupleObjPrim t){
		if((this->obj->internalGetKey().compare(t.obj->internalGetKey()) == 0) && this->p == t.p)
		{
			return true;
		}else {
			return false;
		}
	}
	bool equals(std::string path,std::unordered_map<string,std::list<TupleObjPrim> > elementAlreadyProcessed)
	{
		if(elementAlreadyProcessed.find(path) == elementAlreadyProcessed.end()){
			return false;
		}
		std::list<TupleObjPrim> tuples= elementAlreadyProcessed.find(path)->second;
	
		for (std::list<TupleObjPrim>::iterator iterator = tuples.begin(), end = tuples.end(); iterator != end; ++iterator)
		{
			if(this->equals(*iterator))
			{
				return true;
			}
		}
		return false;
		
	}
	
	void add(std::unordered_map<string,std::list<TupleObjPrim> > elementAlreadyProcessed)
	{
		std::list<TupleObjPrim> tuples;
		if(elementAlreadyProcessed.find(obj->path()) == elementAlreadyProcessed.end())
		{
			elementAlreadyProcessed[obj->path()] = tuples;
		}else
		{
			tuples= elementAlreadyProcessed.find(obj->path())->second;
		}
		tuples.push_back(*this);
		
	}
KMFContainer *obj;
Primitives p;		
};


#endif
