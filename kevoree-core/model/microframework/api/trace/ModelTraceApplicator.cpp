
#include "ModelTraceApplicator.h"




ModelTraceApplicator::ModelTraceApplicator(){

}

ModelTraceApplicator::~ModelTraceApplicator(){

}




void ModelTraceApplicator::applyTraceOnModel(TraceSequence *seq){

	for (std::list<ModelTrace*>::const_iterator iterator = seq->traces.begin(), end = seq->traces.end(); iterator != end; ++iterator)
	{

	}

}
