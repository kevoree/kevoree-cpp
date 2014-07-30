
#include <string>


#ifndef MERGERESOLVER_H_
#define MERGERESOLVER_H_

#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <microframework/api/utils/Utils.h>

class MergeResolver {

public:
	MergeResolver();
	static void merge(ContainerRoot *model, std::string type, std::string url);
};

#endif /*MERGERESOLVER_H_*/
