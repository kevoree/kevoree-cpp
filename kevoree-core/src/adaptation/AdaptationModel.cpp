#include <kevoree-core/api/adaptation/AdaptationModel.h>


AdaptationModel::AdaptationModel(){


}

AdaptationModel::~AdaptationModel(){
	adaptations.clear();
}



void AdaptationModel::add(AdaptationPrimitive *ptr)
{
	adaptations.push_back(ptr);
}



