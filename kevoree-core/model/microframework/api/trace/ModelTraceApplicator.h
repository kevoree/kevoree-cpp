#ifndef __ModelTraceApplicator_H
#define __ModelTraceApplicator_H

#include<string>

#include <microframework/api/trace/ModelTrace.h>
#include <microframework/api/trace/TraceSequence.h>
#include <microframework/api/KMFContainer.h>
#include <microframework/api/KMFFactory.h>

class ModelTraceApplicator
{
public:
	ModelTraceApplicator(KMFContainer* _targetModel, KMFFactory* _factory);
	~ModelTraceApplicator();
	void applyTraceOnModel(TraceSequence *seq);
	void tryClosePending(string srcPath) ;
	void createOrAdd(string previousPath , KMFContainer* target, string refName, string potentialTypeName);


	KMFContainer* targetModel ;
	KMFFactory* factory ;


	KMFContainer* pendingObj ;
	KMFContainer* pendingParent ;
	string pendingParentRefName ;
	string pendingObjPath ;
	bool fireEvents ;

};
#endif
