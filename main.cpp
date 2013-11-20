	
	#include <kevoree-platform/base/KevoreeBootStrap.h>
	#include <microframework/api/trace/DefaultTraceConverter.h>
	#include <microframework/api/json/JSONModelLoader.h>
	#include <microframework/api/compare/ModelCompare.h>
	
	#include <kevoree-core/model/kevoree/ContainerRoot.h>
	#include <iostream>
	#include <fstream>
	#include <stdio.h>
	#include <sys/time.h>
	
	int main(int argc,char **argv)
	{
	/*
		KevoreeBootStrap *kb = new KevoreeBootStrap(); 	
		ifstream filemodel;
		filemodel.open ("boostrapmodel.json");
		if(!filemodel)
		{
		    cout << "no boostrap model found" << endl;
		}else 
		{
			
			DefaultkevoreeFactory factory;
			JSONModelLoader loader;
			loader.setFactory(&factory);
			ContainerRoot *model = (ContainerRoot*)loader.loadModelFromStream(filemodel)->front();
			
			
			kb->setBootstrapModel(model); // boostrapmodel
			kb->start();
		}
		
		*/
		

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

	start = clock();
		ModelCompare *kompare = new ModelCompare();
		TraceSequence *seq = kompare->diff(model,model2);
	finish = clock();
	std::cout << "time delta (ms) = " << Utils::mstimer(start,finish) << std::endl;
		cout << seq->exportToString() << endl;
	}

	
	

	
