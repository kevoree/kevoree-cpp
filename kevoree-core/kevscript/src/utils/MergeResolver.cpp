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
#include <microframework/api/trace/TraceSequence.h>
#include <microframework/api/trace/ModelTraceApplicator.h>
#include <boost/filesystem.hpp>

void MergeResolver::merge(ContainerRoot *model, std::string type, std::string url){
	if(type.compare("mvn") == 0)
	{
		std::list<std::string> urls;
		std::map<std::string, Repository*> map =  model->repositories ;

		for(std::map<std::string, Repository*>::iterator it = model->repositories.begin(); it != model->repositories.end(); ++it) {
			string url = it->first ;
			urls.push_back(url) ;
		}
		// FIX ME USAGE THE GLOBAL
		maven::resolver::MavenResolver mvnResol;
		boost::filesystem::path temp = boost::filesystem::temp_directory_path();
		const std::string tempstr    = temp.native()+"/.m2";
		mvnResol.setBasePath(tempstr); // FIX ME
		std::vector<string> splitted_chain;
		Utils::split(splitted_chain , url  ,":") ;
		JSONModelLoader loader;
		string file  = mvnResol.resolve(splitted_chain.at(0),splitted_chain.at(1),splitted_chain.at(2),"json",urls) ;
		ifstream target;
		target.open (file);
		if(!target){
			throw KevoreeException("\nTypedefinition <"+splitted_chain.at(1)+"> not found in repositories");
		}
		LOGGER_WRITE(Logger::DEBUG,"TypeDefintion found " + splitted_chain.at(1));
		DefaultkevoreeFactory factory;
		loader.setFactory(&factory) ;

		ContainerRoot *remote = (ContainerRoot*) loader.loadModelFromStream(target)->front();
		ModelCompare *compare= new ModelCompare();
		TraceSequence* trace = compare->merge(model,remote);
		//LOGGER_WRITE(Logger::DEBUG,"Merge trace  " + trace->exportToString());


		ModelTraceApplicator* MTA = new ModelTraceApplicator(model,&factory) ;
		MTA->applyTraceOnModel(trace);
		delete MTA ;
		delete remote ;
		delete compare ;


	}else
	{
		LOGGER_WRITE(Logger::WARNING,"Not resolved typeDef" + url);
	}

}
