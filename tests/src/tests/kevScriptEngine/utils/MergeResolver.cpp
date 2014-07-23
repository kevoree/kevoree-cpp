/*
 * MergeResolver.cpp
 *
 *  Created on: 17 juil. 2014
 *      Author: Aymeric
 */


#include "MergeResolver.h"
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <maven-resolver/api/MavenResolver.h>

#include <microframework/api/json/JSONModelLoader.h>
#include <microframework/api/compare/ModelCompare.h>

void MergeResolver::merge(ContainerRoot *model, std::string type, std::string url){

	if(type.compare("mvn") == 0)
	{
		std::list<std::string> urls;

		std::map<std::string, Repository*> map =  model->repositories ;
		for(std::map<std::string, Repository*>::iterator it = model->repositories.begin(); it != model->repositories.end(); ++it) {
			urls.push_back(it->second->url) ;
		}

		maven::resolver::MavenResolver mvnResol;
		mvnResol.setBasePath("/tmp");
		std::vector<string> splitted_chain;
		Utils::split(splitted_chain , url  ,":") ;
		JSONModelLoader loader;
		string file  = mvnResol.resolve(splitted_chain.at(0),splitted_chain.at(1),splitted_chain.at(2),"json",urls) ;
		ifstream target;
			target.open (file);
			if(!target){
				cout << "no file trace" << endl;
			}

		DefaultkevoreeFactory factory;
		loader.setFactory(&factory) ;
		ContainerRoot *remote = (ContainerRoot*) loader.loadModelFromStream(target)->front();
		ModelCompare *compare= new ModelCompare();
		compare->merge(model,remote);
		delete remote ;
		delete compare ;
	}else
	{
		LOGGER_WRITE(Logger::WARNING,"Not resolved typeDef" + url);
	}

}
