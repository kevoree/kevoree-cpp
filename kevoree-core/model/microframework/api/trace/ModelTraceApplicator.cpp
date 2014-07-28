
#include "ModelTraceApplicator.h"
#include "ModelTrace.h"
#include <string>
#include <microframework/api/utils/any.h>

ModelTraceApplicator::ModelTraceApplicator(KMFContainer* _targetModel, KMFFactory* _factory){
	 targetModel = _targetModel ;
	 factory = _factory ;
	 pendingObj = NULL;
	 pendingParent = NULL;
	 pendingParentRefName ="";
	 pendingObjPath ="" ;
	 fireEvents = true ;
}

ModelTraceApplicator::~ModelTraceApplicator(){

}


void ModelTraceApplicator::createOrAdd(string previousPath , KMFContainer* target, string refName, string potentialTypeName)
{
	KMFContainer* targetElm = NULL ;
	if(!previousPath.empty()){
		LOGGER_WRITE(Logger::DEBUG,"prev tpah");
		targetElm = target->findByPath(previousPath);
	}
	if(targetElm != NULL){
		target->reflexiveMutator(ADD,refName,targetElm, true, fireEvents) ;
	}else{
		if(potentialTypeName.compare("")){
			pendingObj = factory->create(potentialTypeName);
		}
		pendingObjPath = previousPath ;
		pendingParentRefName = refName ;
		pendingParent = target ;
	}
}


void ModelTraceApplicator::tryClosePending(string srcPath){
	if((pendingObj != NULL) && (pendingObjPath.compare(srcPath) !=0)){
		if(pendingParent != NULL){
			 pendingParent->reflexiveMutator(ADD, pendingParentRefName, pendingObj, true, fireEvents) ;
			 pendingObj = NULL;
			 pendingParent = NULL;
			 pendingParentRefName = "";
			 pendingObjPath = "";
		}
	}
}

void ModelTraceApplicator::applyTraceOnModel(TraceSequence *seq){

	for (std::list<ModelTrace*>::const_iterator iterator = seq->traces.begin(), end = seq->traces.end(); iterator != end; ++iterator)
	{

		KMFContainer* target = targetModel ;
		ModelTrace* mt = *iterator ;
		cout << mt->toString() << endl ;
		if(dynamic_cast<ModelAddTrace*>(mt) != 0){
			LOGGER_WRITE(Logger::DEBUG,"Add trace");
			tryClosePending("");
			cout << mt->srcPath << endl ;
            if(!mt->srcPath.empty()){

            	 if(targetModel->findByPath(mt->srcPath) != NULL)
            	{
            		 target = targetModel->findByPath(mt->srcPath)	;
            	}
            	 createOrAdd(((ModelAddTrace*)mt)->previousPath, target, mt->refName, ((ModelAddTrace*)mt)->typeName);
            }
		}

		if(dynamic_cast<ModelAddAllTrace*>(mt) != 0){
			LOGGER_WRITE(Logger::DEBUG,"Add All trace");
			tryClosePending("");
			int i = 0 ;
			if( !((ModelAddAllTrace*)mt)->previousPath.empty())
			{
				std::list<string> prevPath = ((ModelAddAllTrace*)mt)->previousPath  ;
				for(std::list<string>::const_iterator it = prevPath.begin() , end = prevPath.end(); it != end; ++it) {
					string path = *it ;
					std::list<string>::iterator it2 = ((ModelAddAllTrace*)mt)->typeName.begin() ;
					std::advance(it2,i) ;
					if(!(*it2).empty())
					{
						string type_name = *it2;
						createOrAdd(path,target, mt->refName, type_name);
					}
					++i ;
				}
			}
		}

		if(dynamic_cast<ModelRemoveTrace*>(mt) != 0){
			LOGGER_WRITE(Logger::DEBUG,"RM trace");
			tryClosePending(mt->srcPath);
			KMFContainer* tmpTarget = targetModel ;

			if(mt->srcPath.compare("") != 0){
				tmpTarget = targetModel->findByPath(mt->srcPath) ;
			}
			if(tmpTarget != NULL){
				tmpTarget->reflexiveMutator(REMOVE,mt->refName, targetModel->findByPath(((ModelRemoveTrace*)mt)->objPath), true, fireEvents);
			}
		}

		if(dynamic_cast<ModelRemoveAllTrace*>(mt) != 0){
			LOGGER_WRITE(Logger::DEBUG,"RM All trace");
				tryClosePending(mt->srcPath);
				KMFContainer* tmpTarget = targetModel ;

				if(mt->srcPath.compare("") != 0){
					tmpTarget = targetModel->findByPath(mt->srcPath) ;
				}
				if(tmpTarget != NULL){
					tmpTarget->reflexiveMutator(REMOVE_ALL,mt->refName,NULL, true, fireEvents);
				}
			}

		if(dynamic_cast<ModelSetTrace*> (mt) != 0){
			LOGGER_WRITE(Logger::DEBUG,"Set trace");
			tryClosePending(mt->srcPath);
			if(!mt->srcPath.empty() && mt->srcPath.empty() != 0){
				KMFContainer* target = targetModel->findByPath(mt->srcPath) ;
				if(target == NULL)
				{
					throw string("Set Trace source not found for path : " + mt->srcPath + " pending " + pendingObjPath + "\n" + mt->toString()) ;
				}
			}else {
				if(mt->srcPath.compare(pendingObjPath) == 0 && pendingObj != NULL){
					target = pendingObj ;
				}
			}
			if(!((ModelSetTrace*)mt)->content.empty()){
				target->reflexiveMutator(SET, mt->refName, ((ModelSetTrace*)mt)->content, true, fireEvents) ;
			}else
			{
				KMFContainer* targetContentPath ;
				if(!((ModelSetTrace*)mt)->objPath.empty()){
					targetContentPath = targetModel->findByPath(((ModelSetTrace*)mt)->objPath) ;
				}else
				{
					targetContentPath = NULL ;
				}
				if(targetContentPath != NULL){
					target->reflexiveMutator(SET, mt->refName, targetContentPath, true , fireEvents );
				}else {
					if(!((ModelSetTrace*)mt)->typeName.empty() && !((ModelSetTrace*)mt)->typeName.empty() ){
						createOrAdd(((ModelSetTrace*)mt)->objPath, target, ((ModelSetTrace*)mt)->refName, ((ModelSetTrace*)mt)->typeName) ;
					}else
					{
						target->reflexiveMutator(SET,((ModelSetTrace*)mt)->refName,targetContentPath, true, fireEvents );
					}
 				}

			}
		}
	}
}
