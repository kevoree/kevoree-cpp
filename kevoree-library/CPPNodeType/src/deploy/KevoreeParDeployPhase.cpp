#include "KevoreeParDeployPhase.h"



KevoreeParDeployPhase::KevoreeParDeployPhase(){
	maxTimeout=30000;
}


void KevoreeParDeployPhase::setMaxTime(long mt)
{
		maxTimeout=mt;
}
