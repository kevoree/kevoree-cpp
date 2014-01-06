#include <kevoree-core/api/adaptation/AdaptationModel.h>


AdaptationModel::AdaptationModel(){


}

AdaptationModel::~AdaptationModel(){

}
void AdaptationModel::addsteps(ParallelStep *ptr)
{
	if(ptr != NULL){
		steps.push(ptr);
	}else
	{
		Logger::Write(Logger::ERROR,"AdaptationModel cannot add null step");
	}
}


int AdaptationModel::size(){
	int count=0;
	int i=0;
	while ( i < steps.size() )
	{
		ParallelStep *step = steps.top();
		count += step->adaptations.size();
		i++;
	}
	return count;
}







