
#include <kevoree-platform/KevoreeBootStrap/KevoreeBootStrap.h>
#include <microframework/api/trace/DefaultTraceConverter.h>
#include <microframework/api/json/JSONModelLoader.h>
#include <microframework/api/json/JSONModelSerializer.h>
#include <microframework/api/compare/ModelCompare.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/model/kevoree/Instance.h>
#include <microframework/api/KMFContainer.h>
#include <kevoree-logger/api/Logger.h>
#include <kevoree-core/kevscript/api/KevScriptEngine.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>

#include <kevoree-tools/DynamicLoader/DynamicLoader.h>

#include <string>
#include <boost/filesystem.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
/*
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

*/
namespace po = boost::program_options;

DefaultkevoreeFactory factory;
JSONModelLoader loader;
ContainerRoot *model=NULL;
KevoreeBootStrap *kb=NULL;

/* configuration */
const string log_file ="kevoree.log";
const std::string name = "Kevoree Platform";
const std::string version = "1.0.1-SNAPSHOT";
std::string path_bootstrap_model = "";
std::string nodename = "node0";

void sig_handler(int s);

void defaultbootstrapmodel(std::string nodename);

bool hasEnding (std::string const &fullString, std::string const &ending)
{
    if (fullString.length() >= ending.length()) {
        return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
    } else {
        return false;
    }
}


int main (int argc, char *argv[])
{


	 /*struct sigaction sigIntHandler;

	   sigIntHandler.sa_handler = sig_handler;
	   sigemptyset(&sigIntHandler.sa_mask);
	   sigIntHandler.sa_flags = 0;

	   sigaction(SIGINT, &sigIntHandler, NULL);*/

	Logger::Start(Logger::INFO, log_file);

	po::options_description description(name+" "+version+"Usage");

	description.add_options()
			("help,h", "Display this help message")
			("nodeName,n",po::value<std::string>(&nodename), "Allows to associate a node name with the runtime")
			("version,v", "Display the version number")
			("model,m", po::value<std::string>(),"Allows to give an initial bootstrap model (.json,.kev.kevs accepted)")
			("level,l", po::value<int>(),"debug level");


	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, description), vm);
	po::notify(vm);

	if(vm.count("help")){
		std::cout << description;

		return 0;
	}

	if(vm.count("version")){
		std::cout << name+" "+version << std::endl;

		return 0;
	}
	if(vm.count("level")){

		int level = vm["level"].as<int>();
		switch(level){
		case 0:
			Logger::Start(Logger::DEBUG, log_file);
			break;

		case 1:
			Logger::Start(Logger::INFO, log_file);
			break;

		case 2:
			Logger::Start(Logger::ERROR, log_file);
			break;
		}

	}

	if(vm.count("nodeName")){
		nodename = vm["nodeName"].as<std::string>();
	}

	if(vm.count("model")){

		path_bootstrap_model = vm["model"].as<std::string>();
		Logger::Write(Logger::DEBUG, "Reading model");
		ifstream modelfile;
		modelfile.open(path_bootstrap_model);
		DefaultkevoreeFactory factory;

		if(hasEnding(path_bootstrap_model,"json"))
		{
			JSONModelLoader loader;
			loader.setFactory(&factory);
			model=  (ContainerRoot*)loader.loadModelFromStream(modelfile)->front();

		}else if(hasEnding(path_bootstrap_model,"kevs") || hasEnding(path_bootstrap_model,"kev")  ){
			model = factory.createContainerRoot();
			KevScriptEngine kse;
			kse.executeFromStream(modelfile,model);
		}else{
			Logger::Write(Logger::INFO, "Unsupported model format use json, kevs or kev, loading default model") ;
		//	model = NULL ;
		}

	}


	if(model == NULL)
	{
		Logger::Write(Logger::DEBUG, "loading default model");
		defaultbootstrapmodel(nodename);
	}


	signal (SIGINT,sig_handler);
	signal(SIGABRT, sig_handler);
	signal(SIGTERM, sig_handler);
	int exit=0;
	clock_t start = clock();

	kb = new KevoreeBootStrap();

	kb->setNodeName(nodename);

	boost::filesystem::path temp = boost::filesystem::temp_directory_path();
	const std::string tempstr    = temp.native()+"/.m2";
	kb->setBasePath(tempstr);

	loader.setFactory(&factory);



	kb->setBootstrapModel(model); // boostrapmodel
	kb->start();



	clock_t finish = clock();
	std::cin >> exit;
}



void sig_handler(int s)
{
	Logger::Write(Logger::INFO, "Stopping signal captured");
	if(kb !=NULL){
		//kb->stop();
		delete kb;
	}
	if(model != NULL)
		delete model;

	exit(1);
}



void defaultbootstrapmodel(std::string nodename){


	model = factory.createContainerRoot();


	DeployUnit *d =factory.createDeployUnit();
	d->name = "cppnode";
	d->groupName = "org.kevoree.library.cpp";
	d->version = version;
	d->type ="so";


	TypeDefinition *nodetype = factory.createNodeType();
	nodetype->name = "cppnode";
	nodetype->abstract= false;
	nodetype->adddeployUnit(d);


	DeployUnit *dg =factory.createDeployUnit();
	dg->name = "webSocketGroup";
	dg->groupName = "org.kevoree.library.cpp";
	dg->version = version;
	dg->type ="so";

	TypeDefinition *grouptype = factory.createGroupType();
	grouptype->abstract= false;
	grouptype->name ="webSocketGroupt";
	grouptype->version = version;

	DictionaryType *typegroup= factory.createDictionaryType();
	DictionaryAttribute *attport = factory.createDictionaryAttribute();
	attport->optional = false;
	attport->datatype = "int";
	attport->fragmentDependant = true;
	attport->name ="port";
	attport->defaultValue = "9000";
	typegroup->addattributes(attport);

	grouptype->adddictionaryType(typegroup);

	grouptype->adddeployUnit(dg);



	ContainerNode *node0 = factory.createContainerNode();
	node0->name = nodename;
	node0->started= true;


	Group *group = factory.createGroup();
	group->name ="group0";
	group->started = true;
	group->addtypeDefinition(grouptype);

	FragmentDictionary *dico =factory.createFragmentDictionary();

	dico->name ="node0";
	DictionaryValue *valport = factory.createDictionaryValue();
	valport->name ="port";
	valport->value ="9000";

	dico->addvalues(valport);


	group->addfragmentDictionary(dico);




	DeployUnit *dc =factory.createDeployUnit();
	dc->name = "HelloWorldComponent";
	dc->groupName = "org.kevoree.library.cpp";
	dc->version = version;
	dc->type ="so";


	node0->addtypeDefinition(nodetype);
	model->addtypeDefinitions(grouptype);
	model->addtypeDefinitions(nodetype);


	model->adddeployUnits(d);
	model->adddeployUnits(dg);
	model->adddeployUnits(dc);


	model->addnodes(node0);

	model->addgroups(group);
	group->addsubNodes(node0);
	node0->addgroups(group);


	Repository *repo_release = factory.createRepository();
	repo_release->url = "http://maven.reacloud.com/nexus/content/repositories/releases";
	Repository *repo_snap = factory.createRepository();
	repo_snap->url = "http://maven.reacloud.com/nexus/content/repositories/snapshots";

	model->addrepositories(repo_release);
	model->addrepositories(repo_snap);
}



