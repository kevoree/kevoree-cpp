#ifndef __ModelTraceApplicator_H
#define __ModelTraceApplicator_H


#include <microframework/api/trace/ModelTrace.h>
#include <microframework/api/trace/TraceSequence.h>

class ModelTraceApplicator
{
public:
	ModelTraceApplicator();
	~ModelTraceApplicator();
	void applyTraceOnModel(TraceSequence *seq);



};
#endif
