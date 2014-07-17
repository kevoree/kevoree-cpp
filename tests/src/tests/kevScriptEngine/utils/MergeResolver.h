
#include <string>


#ifndef MERGERESOLVER_H_
#define MERGERESOLVER_H_


class MergeResolver {

public:
	MergeResolver();
	static void merge(ContainerRoot *model, std::string *type, std::string *url);
};

#endif /*MERGERESOLVER_H_*/
