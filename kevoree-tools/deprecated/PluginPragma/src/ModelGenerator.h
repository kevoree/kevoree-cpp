/*
 * ModelGenerator.h
 *
 *  Created on: 19 déc. 2013
 *      Author: jed
 */


#ifndef MODELGENERATOR_H_
#define MODELGENERATOR_H_

#include <microframework/api/json/JSONModelSerializer.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <microframework/api/json/JSONModelLoader.h>


class ModelGenerator {
public:
	ModelGenerator();
	virtual ~ModelGenerator();
	
	void addNodeType(char *name);
	void addGroupType(char *name);
	void addComponentType(char *name);

	void addDictionnary(char *dico);
	void setVersion(char *version);
	void setGroupName(char *GroupName);
	void close();
	

ContainerRoot *model;
DeployUnit *du;
TypeDefinition *type;
DefaultkevoreeFactory factory;
JSONModelLoader loader;	 
JSONModelSerializer ser;
};

#endif /* MODELGENERATOR_H_ */
