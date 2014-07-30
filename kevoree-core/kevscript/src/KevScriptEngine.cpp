
#include <iostream>
#include <string>
#include <kevoree-core/kevscript/api/KevScriptEngine.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <kevoree-core/model/kevoree/Instance.h>
#include <kevoree-core/model/kevoree/Channel.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/kevscript/src/utils/InstanceResolver.h>
#include "utils/MergeResolver.h"
#include "utils/TypeDefinitionResolver.h"

extern "C" {
#include <kevoree-core/kevscript/api/Waxeye.h>
}


KevScriptEngine::KevScriptEngine()
{

}

KevScriptEngine::~KevScriptEngine()
{

}


void KevScriptEngine::execute(std::string nodeName,ContainerRoot *model){

}
void KevScriptEngine::executeFromStream(istream	&inputstream,ContainerRoot *model){


}


void KevScriptEngine::interpret(struct ast_t *ast, ContainerRoot *model){

	struct ast_tree_t *tree = ast->data.tree;
    struct vector_t *child ;
    struct vector_t *left_hand_children;
	struct ast_t *left_hand_Network	 ;
    size_t num_child ;
    size_t i;
    TypeDefinition *td  ;
    DefaultkevoreeFactory factory;
    Repository *rep ;
    string type ;
    string url ;
    list<Instance*>* leftHands;
	list<Instance*>* rightHands;
	list<Instance*>* instances ;
	list<Instance*>* channel_instances;



    switch (tree->type) {

    case TYPE_KEVSCRIPT:

    	child = ast->data.tree->children;
    	if(child != NULL)
    	{
    	num_child = child->size;
    	for (i = 0; i < num_child; i +=1) {
    		interpret((struct ast_t*) vector_get(child, i), model);
    		}
    	}
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_KEVSCRIPT");

    	break ;
    case TYPE_STATEMENT:
       	child = ast->data.tree->children;
        	if(child != NULL)
        	{
        	num_child = child->size;
        	for (i = 0; i < num_child; i +=1) {
        		interpret((struct ast_t*) vector_get(child, i), model);
        		}
        	}
        	LOGGER_WRITE(Logger::DEBUG,"TYPE_STATEMENT");
        	break ;
    case TYPE_ADDREPO:
    	child = ast->data.tree->children;
      	rep = factory.createRepository();
      	rep->url = ast_children_as_string((struct ast_t*) vector_get(child,0)) ;
      	model->addrepositories(rep);
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_ADDREPO " + rep->url);
    	break ;

    case TYPE_ADD:
     	LOGGER_WRITE(Logger::DEBUG,"TYPE_ADD");
      	child = ast->data.tree->children;
     	try
     	{
    	    td = TypeDefinitionResolver::resolve((struct ast_t*) vector_get(child,1),model) ;
     	}catch (string s)
     	{
     		{ cout << "exception"+s; }
     	}


    	if(td == NULL)
    	{
    		throw string("TypeDefinition not found : " + string(ast_children_as_string((struct ast_t*) vector_get(child,1))))	;
    	}else
    	{
    		struct ast_t *instance_name =  (struct ast_t*)  vector_get(child, 1) ;
    		if(instance_name->data.tree->type == TYPE_NAMELIST)
    		{
    			struct vector_t *chil_inst =instance_name->data.tree->children;
    			size_t num_inst = chil_inst->size;

				for (i = 0; i < num_inst; i +=1) {
					LOGGER_WRITE(Logger::DEBUG,"Todo : ApplyAdd");
									}
    		}
    	}

    	break ;
    case TYPE_INCLUDE:
     	LOGGER_WRITE(Logger::DEBUG,"TYPE_INCLUDE");
    	child = ast->data.tree->children;
    	type = string(ast_children_as_string((struct ast_t*) vector_get(child,0))) ;
    	url = string(ast_children_as_string((struct ast_t*) vector_get(child,1)));
    	MergeResolver::merge(model, type, url) ;

    	break ;

    case TYPE_REMOVE:
     	display_ast(ast, type_strings);
       	LOGGER_WRITE(Logger::DEBUG,"TYPE_REMOVE");
    	break ;
    case TYPE_MOVE:
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_MOVE");
    	leftHands = InstanceResolver::resolve( (struct ast_t*)  vector_get(child, 0) , model) ;
     rightHands = InstanceResolver::resolve( (struct ast_t*)  vector_get(child, 1) , model) ;
    	for(auto itLeft = leftHands->begin() ; itLeft != leftHands->end() ; ++itLeft){
    		for(auto itRight = rightHands->begin(); itRight != rightHands->end() ; ++ itRight){
    			applyMove(*itLeft,*itRight,model) ;
    		}
    	}
    	break ;
    case TYPE_ATTACH:
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_ATTACH");
    	leftHands = InstanceResolver::resolve( (struct ast_t*)  vector_get(child, 0) , model) ;
    	rightHands = InstanceResolver::resolve( (struct ast_t*)  vector_get(child, 1) , model) ;
    	for(auto itLeft = leftHands->begin() ; itLeft != leftHands->end() ; ++itLeft){
    		for(auto itRight = rightHands->begin(); itRight != rightHands->end() ; ++ itRight){
    			applyAttach(*itLeft,*itRight,model,true) ;
    		}
    	}
    	break ;
    case TYPE_DETACH:
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_DETACH");
    	leftHands = InstanceResolver::resolve( (struct ast_t*)  vector_get(child, 0) , model) ;
    	rightHands = InstanceResolver::resolve( (struct ast_t*)  vector_get(child, 1) , model) ;
    	for(auto itLeft = leftHands->begin() ; itLeft != leftHands->end() ; ++itLeft){
    		for(auto itRight = rightHands->begin(); itRight != rightHands->end() ; ++ itRight){
    			applyAttach(*itLeft,*itRight,model,true) ;
    		}
    	}
    	break ;
    case TYPE_START:
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_START");
    	instances = InstanceResolver::resolve( (struct ast_t*)  vector_get(child, 0) , model) ;
    	for(auto it = instances->begin() ; it != instances->end(); ++it)
    	{
    		Instance * ist = *it ;
    		ist->started = true ;
    	}
    	break ;
    case TYPE_PAUSE:
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_PAUSE");
      	throw string("Pause statement is not implemented yet.") ;
    	break ;
    case TYPE_STOP:
       	LOGGER_WRITE(Logger::DEBUG,"TYPE_STOP");
    	instances = InstanceResolver::resolve( (struct ast_t*)  vector_get(child, 0) , model) ;
    	for(auto it = instances->begin() ; it != instances->end(); ++it)
    	{
    		Instance * ist =* it ;
    		ist->started = false ;
    	}
    	break ;
    case TYPE_NETWORK:
     	LOGGER_WRITE(Logger::DEBUG,"TYPE_NETWORK");
    	left_hand_Network	= (struct ast_t*)  vector_get(child, 0);
    	left_hand_children = left_hand_Network->data.tree->children ;
    	if(left_hand_children->size != 3)
    	{
    		throw string("Network must be : network nodeName.propertyType.interfaceName IP") ;
    	}else{
    		string nodename = string(ast_children_as_string((struct ast_t*) vector_get(left_hand_children,0)));
    		string proptype = string(ast_children_as_string((struct ast_t*) vector_get(left_hand_children,1)));
    		string interfacename = string(ast_children_as_string((struct ast_t*) vector_get(left_hand_children,2)));
    		ContainerNode* networkTargetNode = model->findnodesByID(nodename);
    		if(networkTargetNode == NULL){
    	  		throw string("Node not found for name " + nodename) ;
    		}
    		NetworkInfo * info = networkTargetNode->findnetworkInformationByID(proptype) ;
    		if(info == NULL){
    			info = factory.createNetworkInfo();
    			info->name = proptype ;
    			networkTargetNode->addnetworkInformation(info);
    		}
    		NetworkProperty * netprop = info->findvaluesByID(interfacename) ;
    		if(netprop == NULL){
    			netprop = factory.createNetworkProperty() ;
    			netprop->name = interfacename ;
    			info->addvalues(netprop) ;
    		}
    		netprop->value =  string(ast_children_as_string((struct ast_t*) vector_get(child, 1)));
    	}

    	break ;
    case TYPE_ADDBINDING:
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_ADDBINDING");
      	channel_instances = InstanceResolver::resolve( (struct ast_t*)  vector_get(child, 1) , model) ;
      	for(auto it = channel_instances->begin(); it != channel_instances->end(); ++it){
      	//	Channel * channel = (Channel *)it ;
      		//list<Port> ports = Port;
      	}
    	break ;
    case TYPE_DELBINDING:
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_DELBINDING");
    	break ;


    default:
    	LOGGER_WRITE(Logger::DEBUG,"default");
    	break ;
    }

   delete tree ;


	}
void KevScriptEngine::applyAttach(Instance *leftH, Instance *rightH, ContainerRoot *model, bool reverse) {

	ContainerNode* cnL = dynamic_cast<ContainerNode*>(leftH);
	Group* gR = dynamic_cast<Group*>(rightH);
	if(cnL == 0)
	{
		throw string(leftH->name + " is not a ContainerNode") ;
	}if(gR == 0)
	{
		throw string(rightH->name + " is not a Group") ;
	}
	if(!reverse)
	{
		gR->addsubNodes(cnL);
	}else
	{
		gR->removesubNodes(cnL);
	}
	delete cnL ;
	delete gR ;
}
void KevScriptEngine::applyMove(Instance *leftH, Instance *rightH, ContainerRoot *model) {

	ContainerNode* cn = dynamic_cast<ContainerNode*>(rightH);
	if(cn == 0)
	{
		throw string(rightH -> name + " is not a ContainerNode") ;
	}else
	{
		ComponentInstance* ci = dynamic_cast<ComponentInstance*>(leftH);
		if(ci != 0){
			cn->addcomponents(ci) ;
		}else
		{
			ContainerNode* cn2 = dynamic_cast<ContainerNode*>(leftH);
			if(cn2 != 0)
			{
				cn->addhost(cn2) ;
			}else
			{
				throw string(rightH -> name + " is not a ContainerNode or component") ;
			}
		}
	}
	delete cn ;
}

bool KevScriptEngine::applyAdd(TypeDefinition *td, struct ast_t *ast, ContainerRoot *model) {
	Instance* process ;
	DefaultkevoreeFactory factory;
	struct vector_t *child = ast->data.tree->children;

	if(dynamic_cast<NodeType*>(td) != 0)
	{
		NodeType* nt = dynamic_cast<NodeType*>(td) ;
		ContainerNode* instance = factory.createContainerNode() ;
		instance->typeDefinition = td ;
		if((ast->data.tree->type == TYPE_INSTANCEPATH) && child->size == 1)
		{
			string newNodeName = ast_children_as_string((struct ast_t*) vector_get(child,0)) ;
			instance->name = newNodeName ;
			if(model->findnodesByID(newNodeName) != NULL)
			{
				throw string("Node already exists with name: " + newNodeName) ;
			}
			model->addnodes(instance);
			process = instance ;

		}else
		{
			string parentNodeName = ast_children_as_string((struct ast_t*) vector_get(child,0)) ;
			string newNodeName = ast_children_as_string((struct ast_t*) vector_get(child,1)) ;
			instance->name = newNodeName ;
			ContainerNode *parentNode = model->findnodesByID(parentNodeName) ;
			if(parentNode == NULL){
				throw string("Node" +parentNodeName +"doesn't exist");
			}
			model->addnodes(instance);
			parentNode->addhost(instance);
			process = instance ;
		}
	}

	if(dynamic_cast<ComponentType*>(td) != 0){
		ComponentType* ct = dynamic_cast<ComponentType*>(td);
		ComponentInstance* instance = factory.createComponentInstance();
		instance->typeDefinition = td ;
		if((ast->data.tree->type == TYPE_INSTANCEPATH) && child->size == 2)
			{
			string newNodeName = ast_children_as_string((struct ast_t*) vector_get(child,1)) ;
			instance->name = newNodeName ;
			map<string,PortTypeRef*> reqPortMap = ct->required ;
			map<string,PortTypeRef*> provPortMap = ct->required ;
			for(std::map<string,PortTypeRef*>::iterator it = reqPortMap.begin(); it != reqPortMap.end() ; ++it)
			{
				PortTypeRef *curr = it->second ;
				Port *newPort = factory.createPort() ;
				newPort->portTypeRef = curr ;
				newPort->name = curr->name ;
				instance->addrequired(newPort) ;
			}
			for(std::map<string,PortTypeRef*>::iterator it = provPortMap.begin(); it != provPortMap.end() ; ++it)
			{
				PortTypeRef *curr = it->second ;
				Port *newPort = factory.createPort() ;
				newPort->portTypeRef = curr ;
				newPort->name = curr->name ;
				instance->addprovided(newPort) ;
			}
			string parentNodeName = ast_children_as_string((struct ast_t*) vector_get(child,0)) ;
			ContainerNode *parentNode = model->findnodesByID(parentNodeName) ;
			if(parentNode == NULL){
						throw string("Node" +parentNodeName +"doesn't exist");
					}
			else{
				parentNode->addcomponents(instance);
				process = instance ;
			}

			}

		if(dynamic_cast<ChannelType*>(td) != 0){
			ChannelType* cht = dynamic_cast<ChannelType*>(td);
			Channel *instance = factory.createChannel() ;
			instance->typeDefinition = td ;
			if((ast->data.tree->type== TYPE_INSTANCEPATH) && child->size == 1)
						{
				string channelname = ast_children_as_string((struct ast_t*) vector_get(child,0)) ;
				instance->name = channelname ;
				model->addhubs(instance) ;
				process = instance ;
						}else{
							throw string("wrong channel name : ") ;
						}
		}

		if(dynamic_cast<GroupType*>(td) != 0){
			GroupType* gt = dynamic_cast<GroupType*>(td);
			Group *instance = factory.createGroup() ;
				instance->typeDefinition = td ;
				if((ast->data.tree->type == TYPE_INSTANCEPATH) && child->size == 1)
							{
					string channelname = ast_children_as_string((struct ast_t*) vector_get(child,0)) ;
					instance->name = channelname ;
					model->addgroups(instance) ;
					process = instance ;
							}else{
								throw string("wrong channel name : " ) ;
							}
			}
	}
	return process != NULL;

}
