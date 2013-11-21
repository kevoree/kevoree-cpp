	
	#include <kevoree-platform/base/KevoreeBootStrap.h>
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
	
	
	class VisitorTester :public ModelVisitor
{
public:
    void visit(KMFContainer *elem,string refNameInParent, KMFContainer* parent)
    {
  cout << elem->path() << endl;
    }

};


class VisitorAttTester:public ModelAttributeVisitor
{

  public:
    void  visit(any val,string name,KMFContainer *parent)
    {
         if(!val.empty())
         {

         if(val.type() == typeid(string)){
                    cout << "visiting ATTRIBUTE NAME --> " << name << "  VALUE "<<AnyCast <string>(val)  << endl;
         }

         }


    }

};

	
	int main(int argc,char **argv)
	{
/*
AdaptationModel e;
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
	}*/
		
	

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
		
		
	   for (std::list<ModelTrace*>::iterator iterator = seq->traces.begin(), end = seq->traces.end(); iterator != end; ++iterator)
        {
			ModelTrace *trace = *iterator;
			KMFContainer *modelElement = model2->findByPath(trace->srcPath);
		
			if(trace->refName.compare("started") ==0)
			{
				cout << modelElement->path() << endl;
					 if((typeid(*modelElement) == typeid(Instance)) && typeid(*trace) == typeid(ModelSetTrace)){
						 
						 	cout << trace->refName << endl;
					 }
			}
			 
		}	
		
	}

	
	

	
