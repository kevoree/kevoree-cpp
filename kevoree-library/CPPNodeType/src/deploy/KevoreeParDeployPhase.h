#ifndef __KevoreeParDeployPhase_H
#define __KevoreeParDeployPhase_H
#include <kevoree-core/core/api/PrimitiveCommand.h>
#include <list>

class KevoreeParDeployPhase 
{
public:
KevoreeParDeployPhase();
~KevoreeParDeployPhase();
void setMaxTime(long mt);
long getMaxTime();
void populate(PrimitiveCommand *cmd);
void rollback();


long maxTimeout;
std::list<PrimitiveCommand*> primitives;
KevoreeParDeployPhase *sucessor;
};
#endif

