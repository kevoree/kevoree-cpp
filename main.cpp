	
	#include <kevoree-platform/KevoreeBootStrap/KevoreeBootStrap.h>
	#include <microframework/api/trace/DefaultTraceConverter.h>
	#include <microframework/api/json/JSONModelLoader.h>
	#include <microframework/api/compare/ModelCompare.h>
	#include <kevoree-core/model/kevoreeadaptation/kevoreeadaptation.h>
	#include <kevoree-core/model/kevoree/ContainerRoot.h>
	#include <kevoree-core/model/kevoree/Instance.h>
	#include <iostream>
	#include <fstream>
	#include <stdio.h>
	#include <sys/time.h>
	#include <microframework/api/KMFContainer.h>
	#include <microframework/api/utils/Logger.h>


	
	int main(int argc,char **argv)
	{
		AdaptationModel model;
		
		LOGGER_START(Logger::DEBUG, "kevoree.log");

	

		KevoreeBootStrap *kb = new KevoreeBootStrap(); 	
		kb->setNodeName("node0");
		
		ifstream filemodel;
		filemodel.open ("boostrapmodel.json");
		if(!filemodel)
		{
		    LOGGER_WRITE(Logger::ERROR, "no boostrap model found ");
		}else 
		{
			
			DefaultkevoreeFactory factory;
			JSONModelLoader loader;
			loader.setFactory(&factory);
			ContainerRoot *model = (ContainerRoot*)loader.loadModelFromStream(filemodel)->front();
			
			
			kb->setBootstrapModel(model); // boostrapmodel
			kb->start();
		}
			clock_t finish = clock();
	

		kb->join();
		pause();
	}
		
	/*

		DefaultkevoreeFactory factory;
	
		 JSONModelLoader loader;
	
		 loader.setFactory(&factory);
		ifstream myfile;
		 myfile.open ("jedModel.json");
		 if(!myfile){
		     cout << "no file trace" << endl;
		 }
	
		ifstream myfile2;
		 myfile2.open ("jedModel2.json");
		 if(!myfile2){
		     cout << "no file trace" << endl;
		 }
	
	clock_t start = clock();
		ContainerRoot *model = (ContainerRoot*)loader.loadModelFromStream(myfile)->front();
		ContainerRoot *model2 = (ContainerRoot*)loader.loadModelFromStream(myfile2)->front();
	clock_t finish = clock();
	
	std::cout << "time delta (ms) = " << Utils::mstimer(start,finish) << std::endl;

	//ContainerNode *n = (ContainerNode*)model2->findByPath("nodes[childNodePowet]");



	start = clock();
		ModelCompare *kompare = new ModelCompare();
		TraceSequence *seq = kompare->merge(model,model2);
	finish = clock();
	std::cout << "time delta (ms) = " << Utils::mstimer(start,finish) << std::endl;
		cout << seq->exportToString() << endl;
		}
		*/

		
	

	
	

	
