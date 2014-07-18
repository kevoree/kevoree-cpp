#include "KevScriptEngine.h"
#include <iostream>
#include <string>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <kevoree-core/model/kevoree/Instance.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include "utils/MergeResolver.h"
#include "utils/TypeDefinitionResolver.h"

extern "C" {
#include <tests/src/tests/Waxeye.h>
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
    struct vector_t *chil ;
    size_t num_chil ;
    size_t i;
    TypeDefinition *td  ;
    DefaultkevoreeFactory factory;
    Repository *rep ;
    string type ;
    string url ;

    switch (tree->type) {

    case TYPE_KEVSCRIPT:

    	chil = ast->data.tree->children;
    	if(chil != NULL)
    	{
    	num_chil = chil->size;
    	for (i = 0; i < num_chil; i +=1) {
    		interpret((struct ast_t*) vector_get(chil, i), model);
    		}
    	}
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_KEVSCRIPT");

    	break ;
    case TYPE_STATEMENT:
       	chil = ast->data.tree->children;
        	if(chil != NULL)
        	{
        	num_chil = chil->size;
        	for (i = 0; i < num_chil; i +=1) {
        		interpret((struct ast_t*) vector_get(chil, i), model);
        		}
        	}
        	LOGGER_WRITE(Logger::DEBUG,"TYPE_STATEMENT");
        	break ;
    case TYPE_ADDREPO:
    	chil = ast->data.tree->children;
      	rep = factory.createRepository();
      	rep->url = ast_children_as_string((struct ast_t*) vector_get(chil,0)) ;
      	model->addrepositories(rep);
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_ADDREPO");
    	break ;

    case TYPE_ADD:
			td = TypeDefinitionResolver::resolve((struct ast_t*) vector_get(chil, 0),model) ;

    	if(td == NULL)
    	{
    		throw string("TypeDefinition not found : " + string(ast_children_as_string((struct ast_t*) vector_get(chil,1))))	;
    	}else
    	{
    		struct ast_t *instance_name =  (struct ast_t*)  vector_get(chil, 1) ;
    		if(instance_name->type == TYPE_NAMELIST)
    		{
    			struct vector_t *chil_inst =instance_name->data.tree->children;
    			size_t num_inst = chil_inst->size;

				for (i = 0; i < num_inst; i +=1) {
					LOGGER_WRITE(Logger::DEBUG,"Todo : ApplyAdd");
									}
    		}
    	}
       	LOGGER_WRITE(Logger::DEBUG,"TYPE_ADD");
    	break ;
    case TYPE_INCLUDE:
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_INCLUDE");
    	chil = ast->data.tree->children;
    	type = string(ast_children_as_string((struct ast_t*) vector_get(chil,0))) ;
    	url = string(ast_children_as_string((struct ast_t*) vector_get(chil,1)));
    	MergeResolver::merge(model, &type, &url) ;
    	break ;

    case TYPE_REMOVE:
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_REMOVE");
    	break ;
    case TYPE_MOVE:
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_MOVE");
    	break ;
    case TYPE_ATTACH:
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_ATTACH");
    	break ;
    case TYPE_DETACH:
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_DETACH");
    	break ;
    case TYPE_START:
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_START");
    	break ;
    case TYPE_PAUSE:
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_PAUSE");
    	break ;
    case TYPE_STOP:
       	LOGGER_WRITE(Logger::DEBUG,"TYPE_STOP");
    	break ;
    case TYPE_NETWORK:
     	LOGGER_WRITE(Logger::DEBUG,"TYPE_NETWORK");
    	break ;
    case TYPE_ADDBINDING:
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_ADDBINDING");
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
		throw string(leftH -> name + " is not a ContainerNode") ;
	}if(gR == 0)
	{
		throw string(rightH -> name + " is not a Group") ;
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
		if((ast->type == TYPE_INSTANCEPATH) && child->size == 1)
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
		if((ast->type == TYPE_INSTANCEPATH) && child->size == 2)
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
			if((ast->type == TYPE_INSTANCEPATH) && child->size == 1)
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
				if((ast->type == TYPE_INSTANCEPATH) && child->size == 1)
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
