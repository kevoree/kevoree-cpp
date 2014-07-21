/*
 * ModelGenerator.cpp
 *
 *  Created on: 19 déc. 2013
 *      Author: jed
 */

#include "ModelGenerator.h"
#include <string>
#include <fstream>

 ModelGenerator *generator = new ModelGenerator();
extern "C"
{

void addNodeType(char *name){
	generator->addNodeType(name);
}
void addGroupType(char *name){
	generator->addGroupType(name);
}
void addComponentType(char *name){
	generator->addComponentType(name);
}

void addDictionnary(char *dico){
	generator->addDictionnary(dico);
}
void setVersion(char *version){
	generator->setVersion(version);
}
void setGroupName(char *GroupName){
	generator->setGroupName(GroupName);
}
}


extern "C"{  
void closelib()
{
	if(generator->model->typeDefinitions.size() > 0)
	{
		generator->close();
	}
	delete generator->model;
	delete generator;
}
}

ModelGenerator::ModelGenerator() {

	model = factory.createContainerRoot();
	du =factory.createDeployUnit();

	loader.setFactory(&factory);

	du->version ="SNAPSHOT";
}

ModelGenerator::~ModelGenerator() {

}


void ModelGenerator::close()
{	
	std::string result  =ser.serialize(model);
	ofstream myfile;
	myfile.open ("target/lib.json");
	myfile << result;
	myfile.close();
	/*
	ofstream pomfile;
	pomfile.open ("target/pom.xml");
	pomfile << "<project xmlns=\"http://maven.apache.org/POM/4.0.0\"\n";
	pomfile << "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n";
	pomfile << "xsi:schemaLocation=\"http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd\">\n";
	pomfile << "<modelVersion>4.0.0</modelVersion>\n";
	pomfile << "<groupId>"+du->groupName+"</groupId>\n";
	pomfile << "<artifactId>"+type->name+"</artifactId>\n";
	pomfile << "<version>"+type->version+"</version>\n";
	pomfile << "<packaging>so</packaging>\n";
	pomfile << "</project>\n";
	
	pomfile.close();*/
	
	 
	

}

void ModelGenerator::addNodeType(char *name){

	type = factory.createNodeType();
	type->name =string(name);


	du->name =string(name);
	du->groupName = "org.kevoree.library";

	du->type ="elf32-i386";

	type->adddeployUnit(du);
	model->addtypeDefinitions(type);
	model->adddeployUnits(du);

}

void ModelGenerator::addComponentType(char *name){
	DeployUnit *du;
	type = factory.createComponentType();
	type->name =string(name);
	type->abstract = false;

	du =factory.createDeployUnit();
	du->name =string(name);
	du->groupName = "org.kevoree.library";

	du->type ="elf32-i386";
	type->adddeployUnit(du);

	model->addtypeDefinitions(type);

	model->adddeployUnits(du);
}

void ModelGenerator::addDictionnary(char *dico){
	DictionaryType *typegroup= factory.createDictionaryType();
	DictionaryAttribute *attport = factory.createDictionaryAttribute();
	attport->optional = false;
	attport->datatype = "string";
	attport->fragmentDependant = true;
	attport->name =string(dico);
	attport->defaultValue = "9000";
	typegroup->addattributes(attport);
	type->adddictionaryType(typegroup);

}


void ModelGenerator::addGroupType(char *name)
{

	type = factory.createGroupType();
	type->name =string(name);
	du =factory.createDeployUnit();
	du->name =string(name);

	du->type ="elf32-i386";
	type->adddeployUnit(du);
	model->addtypeDefinitions(type);
	model->adddeployUnits(du);

}
void ModelGenerator::setGroupName(char *name){
	du->groupName = name;

}

void ModelGenerator::setVersion(char *name){
	du->version = string(name);
	type->version = string(name);
}

