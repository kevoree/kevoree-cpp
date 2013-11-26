#ifndef __KevoreeParDeployPhase_H
#define __KevoreeParDeployPhase_H
#include <kevoree-core/core/api/PrimitiveCommand.h>
#include <list>

class KevoreeParDeployPhase 
{
public:
KevoreeParDeployPhase();
void setMaxTime(long mt);

long maxTimeout;
std::list<PrimitiveCommand> primitives;
KevoreeParDeployPhase *sucessor;
};
#endif

