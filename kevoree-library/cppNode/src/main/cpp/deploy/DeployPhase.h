#ifndef __KevoreeParDeployPhase_H
#define __KevoreeParDeployPhase_H

#include <microframework/api/utils/Logger.h>
#include <kevoree-core/api/PrimitiveCommand.h>
#include <list>

class DeployPhase
{
public:
	DeployPhase();
	~DeployPhase();
	void setMaxTime(long mt);
	long getMaxTime();
	void populate(PrimitiveCommand *cmd);
	void rollback();


	long maxTimeout;
	std::list<PrimitiveCommand*> primitives;
	DeployPhase *sucessor;
};
#endif

