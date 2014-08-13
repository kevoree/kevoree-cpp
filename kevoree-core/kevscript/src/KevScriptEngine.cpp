

#include <kevoree-core/kevscript/api/KevScriptEngine.h>
#include "utils/MergeResolver.h"
#include "utils/PortResolver.h"
#include "utils/TypeDefinitionResolver.h"
#include <iostream>
#include <string>
#include <kevoree-core/api/KevScriptService.h>
#include <kevoree-core/model/kevoree/Instance.h>
#include <microframework/api/utils/KevoreeException.h>
#include <kevoree-core/model/kevoree/DefaultkevoreeFactory.h>
#include <kevoree-core/model/kevoree/Instance.h>
#include <kevoree-core/model/kevoree/Channel.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <kevoree-core/kevscript/src/utils/InstanceResolver.h>


extern "C" {
#include <kevoree-core/kevscript/api/waxeyeParser.h>
}

KevScriptEngine::KevScriptEngine()
{

}

KevScriptEngine::~KevScriptEngine()
{

}


/*
 *
 *
 *
 *

    		std::map<string, ContainerNode*> m =model->nodes ;
    		cout << "maps" << endl;
    		for(auto it = m.begin(); it != m.end(); ++it){
    			cout << it->first <<endl ;
    		}
    		cout << "maps" << endl;

 */

void KevScriptEngine:: printCP(ContainerRoot *model){
	std::map<string, ContainerNode*> m =model->nodes ;
	LOGGER_WRITE(Logger::DEBUG,"Print CP MAp");
    		for(auto it = m.begin(); it != m.end(); ++it){
    			ContainerNode* cn = it->second  ;
    		 	LOGGER_WRITE(Logger::DEBUG,"Node name " + cn->name);
    		 	LOGGER_WRITE(Logger::DEBUG,"cp size " );
    		 	std::map<string, ComponentInstance*> cmap =	cn->components ;
    		 	for(std::map<string, ComponentInstance*>::iterator it2 = cmap.begin(); it2 != cmap.end(); it2++){
    		 		ComponentInstance* cio = it2->second ;
    		 		LOGGER_WRITE(Logger::DEBUG,"ComponentInstance " + cio->name);
    		 	}
    		 	}

    		cout << "maps" << endl;

}

void KevScriptEngine::execute(std::string &script,ContainerRoot *model){
	struct ast_t *ast = parseKevscript(script.c_str());
	//interpret
	interpret(ast,model);
	// destructor
	freeKevScriptAst(ast);
}
void KevScriptEngine::executeFromStream(istream	&inputstream,ContainerRoot *model){
	if(inputstream)
	{
		// read file
		std::string script;
		std::ostringstream os;
		inputstream >>os.rdbuf();
		script=os.str();
		LOGGER_WRITE(Logger::DEBUG,"KevScript "+script);
		// interpret
		this->execute(script,model);
	}else
	{
		throw KevoreeException("KevScriptEngine executeFromStream inputstream is null");
	}
}

void KevScriptEngine::interpret(struct ast_t *ast, ContainerRoot *model){

	struct ast_tree_t *tree = ast->data.tree;
    struct vector_t *child = ast->data.tree->children;
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
	list<Instance*>* target_node;
	list<Port*>* ports ;

	list<Instance*> *tochangeDico;
	string propName;
	vector_t* children_lst2;
	int val ;
	vector_t* children_lst;
	ast_t* portName;
	ast_t* leftHnodes ;
	string propToSet ;



    switch (tree->type) {



    case TYPE_KEVSCRIPT:
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_KEVSCRIPT");
    	if(child != NULL)
    	{
    	num_child = child->size;
    	for (i = 0; i < num_child; i +=1) {
    		interpret((struct ast_t*) vector_get(child, i), model);
    		}
    	}


    	break ;
    case TYPE_STATEMENT:
       	LOGGER_WRITE(Logger::DEBUG,"TYPE_STATEMENT");
        	if(child != NULL)
        	{
        	num_child = child->size;
        	for (i = 0; i < num_child; i +=1) {
        		interpret((struct ast_t*) vector_get(child, i), model);
        		}
        	}

        	break ;
    case TYPE_ADDREPO:
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_ADDREPO ");
      	rep = factory.createRepository();
      	rep->url = ast_children_as_string((struct ast_t*) vector_get(child,0)) ;
      	model->addrepositories(rep);

    	break ;

    case TYPE_ADD:
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_ADD");
     	try
     	{
    	    td = TypeDefinitionResolver::resolve((struct ast_t*) vector_get(child,1),model) ;
     	}catch (string s)
     	{
     		{ cout << "exception"+s; }
     	}
    	if(td == NULL)
    	{
    		throw KevoreeException("TypeDefinition not found : " + string(ast_children_as_string((struct ast_t*) vector_get(child,1))))	;
    	}else
    	{
    		struct ast_t *instance_name =  (struct ast_t*)  vector_get(child, 0) ;
    		if(instance_name->data.tree->type == TYPE_NAMELIST)
    		{
    			struct vector_t *chil_inst =instance_name->data.tree->children;
    			size_t num_inst = chil_inst->size;
				for (i = 0; i < num_inst; i +=1) {
					struct ast_t *name =  (struct ast_t*)  vector_get(chil_inst, i) ;
					applyAdd(td,name,model);
				}

    		}
    	}

    	break ;
    case TYPE_INCLUDE:
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_INCLUDE");
    	type = string(ast_children_as_string((struct ast_t*) vector_get(child,0))) ;
    	url = string(ast_children_as_string((struct ast_t*) vector_get(child,1)));
    	MergeResolver::merge(model, type, url) ;
     	break ;

    case TYPE_REMOVE:
     	LOGGER_WRITE(Logger::DEBUG,"TYPE_REMOVE");
     	display_ast(ast, type_strings);

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
    		Instance * leftinst = *itLeft ;
    		for(auto itRight = rightHands->begin(); itRight != rightHands->end() ; ++ itRight){
    	   		Instance * rightinst = *itRight ;
    	   		  applyAttach(leftinst,rightinst,model,false) ;


    		}
    	}

    	LOGGER_WRITE(Logger::DEBUG,"TYPE_ATTACH END");

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
      	throw KevoreeException("Pause statement is not implemented yet.") ;
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
    		throw KevoreeException("Network must be : network nodeName.propertyType.interfaceName IP") ;
    	}else{
    		string nodename = string(ast_children_as_string((struct ast_t*) vector_get(left_hand_children,0)));
    		string proptype = string(ast_children_as_string((struct ast_t*) vector_get(left_hand_children,1)));
    		string interfacename = string(ast_children_as_string((struct ast_t*) vector_get(left_hand_children,2)));
    		ContainerNode* networkTargetNode = model->findnodesByID(nodename);
    		if(networkTargetNode == NULL){
    	  		throw KevoreeException("Node not found for name " + nodename) ;
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
      		Channel* channel = (Channel *)*it ;
      		ports = PortResolver::resolve( (struct ast_t*)  vector_get(child, 0) , model) ;
      		for(auto itp = ports->begin(); itp != ports->end(); ++itp){
      			MBinding* mb = factory.createMBinding();
      			Port* p = (Port*)*itp ;
      			p->addbindings(mb);
      			mb->port = *itp ;
      			mb->hub= channel;
      			channel->addbindings(mb);
      			mb->addport(p);
      			model->addmBindings(mb);
      		}
      	}
    	break ;
    case TYPE_DELBINDING:
      	LOGGER_WRITE(Logger::DEBUG,"TYPE_DELBINDING");
      	channel_instances = InstanceResolver::resolve( (struct ast_t*)  vector_get(child, 1) , model) ;
      	ports = PortResolver::resolve( (struct ast_t*)  vector_get(child, 0) , model) ;
      	for(auto it = channel_instances->begin(); it != channel_instances->end(); ++it){
      		Channel* channel = (Channel *)*it ;
      		MBinding* toDrop = NULL ;
      		for(auto itb = channel->bindings.begin(); itb != channel->bindings.end(); ++itb){
      			for(auto itp = ports->begin(); itp != ports->end() ; ++ itp){
      				MBinding* mb = 	itb ->second;
      				Port* p = *itp ;
      				p->removebindings(mb);
      				if(mb->port->internalGetKey().compare(p->internalGetKey())){
      					toDrop = mb ;
      				}
      			}

      		}
      		if(toDrop != NULL){
      			//Todo à verifier
      			toDrop->deleteContainer() ;
      		}
      	}

    	break ;
    case TYPE_SET:
    	LOGGER_WRITE(Logger::DEBUG,"TYPE_SET");
    	propToSet = "";
        display_ast(ast, type_strings);

    	child = ast->data.tree->children;


    	if(child->size == 3){


    		vector_t* children = ((struct ast_t*)vector_get(child, 2))->data.tree->children ;
    		size_t num_child = children->size ;
    		for (i = 0 ; i < num_child ; i++){
    			propToSet.append(ast_children_as_string(((struct ast_t*)vector_get(children,i))));
    		}

    		target_node = InstanceResolver::resolve((struct ast_t*) vector_get(child,1) , model) ;

    	}else{
    		vector_t* children = ((struct ast_t*) vector_get(child, 2))->data.tree->children ;
    		size_t num_child = children->size ;

    		for (i = 0 ; i < num_child ; i++){
    			ast_t* curr_child =	((struct ast_t*)vector_get(children,i));
    			switch(curr_child->data.tree->type){
    			case TYPE_SINGLEQUOTELINE:
    				break ;

    			case TYPE_DOUBLEQUOTELINE:
    				propToSet.append(ast_children_as_string(curr_child));
    				break ;

    			case TYPE_NEWLINE:
    				propToSet.append("\n");
    				break ;

    			default:
    				break ;
    			}
    		}
    	}

    	leftHnodes = (struct ast_t*)vector_get(child, 0) ;
    	if(leftHnodes->data.tree->children->size <2)
    	{
    		throw KevoreeException("Bad dictionary value description ") ;
    	}
    	portName =(struct ast_t*)vector_get(leftHnodes->data.tree->children, leftHnodes->data.tree->children->size -1)   ;
    	children_lst = leftHnodes->data.tree->children ;
    	val =leftHnodes->data.tree->children->size -1 ;
    	children_lst2 = vector_new(val) ;
    	propName = ast_children_as_string(portName);
    	// removing from the ast portname

    	for(int i = 0 ; i < children_lst->size ; i++)
    	{
    		string curr_elm =string(ast_children_as_string(((struct ast_t*)vector_get(children_lst,i)))) ;
    		if(curr_elm.compare(propName) != 0)
    		{
    			vector_push(children_lst2,vector_get(children_lst,i));
    		}
    	}

    	leftHnodes->data.tree->children = children_lst2 ;
    	tochangeDico = InstanceResolver::resolve(leftHnodes,model);

    	for(auto itDico = tochangeDico->begin() ; itDico != tochangeDico->end() ; ++itDico){

    		Instance* target = *itDico ;

    		if(target_node == NULL){
    			LOGGER_WRITE(Logger::DEBUG,"IF");
    			if(target->dictionary == NULL){
    				target->dictionary = factory.createDictionary();
    			}

    			DictionaryValue* dicVal = target->dictionary->findvaluesByID(propName);
    			if(dicVal == NULL){
    				dicVal = factory.createDictionaryValue();
    				if(target->typeDefinition->dictionaryType != NULL){
    					DictionaryAttribute* dicAtt = target->typeDefinition->dictionaryType->findattributesByID(propName);
    					if(dicAtt == NULL){
    						throw KevoreeException("Param does not existe in type " + target->name + " -> " + propName) ;
    					}else{
    						dicVal->name = dicAtt->name;
    					}
    				}

    				target->dictionary->addvalues(dicVal);

    			}

    			target->dictionary->addvalues(dicVal);
    		}else{
    			for(auto it2 = target_node->begin(); it2 != target_node->end(); ++it2){

    				Instance * tg_n = *it2 ;
    				cout << tg_n->name << endl ;
    				if(target->findfragmentDictionaryByID(tg_n->name) == NULL)
    				{
    					FragmentDictionary* newDic = factory.createFragmentDictionary();
    					newDic->name = tg_n->name ;
    					target->addfragmentDictionary(newDic);

    				}

    				DictionaryValue* dicVal = target->findfragmentDictionaryByID(tg_n->name)->findvaluesByID(propName);
    				if(dicVal == NULL){
    					dicVal = factory.createDictionaryValue();
    					cout << "nul" << endl ;
    					if(target->typeDefinition->dictionaryType != NULL){

    						DictionaryAttribute* dicAttr = target->typeDefinition->dictionaryType->findattributesByID(propName);
    						if(dicAttr == NULL){
    							throw KevoreeException("Param does not existe in type " + target->name + " -> " + propName) ;
    						}else{
    							if(!dicAttr->fragmentDependant)
    							{
    								throw  KevoreeException("Dictionary Attribute is not fragment dependent " + dicAttr->name);
    							}
    							dicVal->name = dicAttr->name ;

    						}

    					}
    					target->findfragmentDictionaryByID(tg_n->name)->addvalues(dicVal);
    				}

    				dicVal->value = propToSet ;
    			}
    		}
    	}
    	break ;

    default:
    	LOGGER_WRITE(Logger::DEBUG,"default");
    	break ;




    }
	}
void KevScriptEngine::applyAttach(Instance *leftH, Instance *rightH, ContainerRoot *model, bool reverse) {
	ContainerNode* cnL = dynamic_cast<ContainerNode*>(leftH);
	Group* gR = dynamic_cast<Group*>(rightH);
cout << "container" + cnL->name << endl ;
cout << "gR" + gR->name << endl ;
	if(cnL == 0)
	{
		throw KevoreeException(leftH->name + " is not a ContainerNode") ;
	}if(gR == 0)
	{
		throw KevoreeException(rightH->name + " is not a Group") ;
	}

	if(!reverse)
	{
		gR->addsubNodes(cnL);
		cnL->addgroups(gR);

	}else
	{
		gR->removesubNodes(cnL);
		cnL->removegroups(gR);
	}

}
void KevScriptEngine::applyMove(Instance *leftH, Instance *rightH, ContainerRoot *model) {

	ContainerNode* cn = dynamic_cast<ContainerNode*>(rightH);
	if(cn == 0)
	{
		throw KevoreeException(rightH -> name + " is not a ContainerNode") ;
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
				throw KevoreeException(rightH ->name + " is not a ContainerNode or component") ;
			}
		}
	}

}

bool KevScriptEngine::applyAdd(TypeDefinition *td, struct ast_t *ast, ContainerRoot *model) {
	Instance* process = NULL;
	DefaultkevoreeFactory factory;
	struct vector_t *child = ast->data.tree->children;
	string newNodeName = ast_children_as_string((struct ast_t*) vector_get(child,0)) ;
	if(dynamic_cast<NodeType*>(td) != 0)
	{

		NodeType* nt = dynamic_cast<NodeType*>(td) ;

		ContainerNode* instance = factory.createContainerNode() ;
		instance->started = true ;
		instance->typeDefinition = nt ;
		if((ast->data.tree->type == TYPE_INSTANCEPATH) && child->size == 1)
		{
			string newNodeName = ast_children_as_string((struct ast_t*) vector_get(child,0)) ;
			instance->name = newNodeName ;
			if(model->findnodesByID(newNodeName) != NULL)
			{
				throw KevoreeException("Node already exists with name: " + newNodeName) ;
			}
			model->addnodes(instance);
			process = instance ;

		}else
		{
			string parentNodeName = ast_children_as_string((struct ast_t*) vector_get(child,0)) ;
			string newNodeName = ast_children_as_string((struct ast_t*) vector_get(child,1)) ;
			instance->name = newNodeName ;
			instance->started = true ;
			ContainerNode *parentNode = model->findnodesByID(parentNodeName) ;
			if(parentNode == NULL){
				throw KevoreeException("Node" +parentNodeName +"doesn't exist");
			}
			model->addnodes(instance);
			parentNode->addhost(instance);
			process = instance ;
		}
	}

	else if(dynamic_cast<ComponentType*>(td) != 0){
		cout << "ComponentType" << endl ;
		ComponentType* ct = dynamic_cast<ComponentType*>(td);
		ComponentInstance* instance = factory.createComponentInstance();
		instance->typeDefinition = ct ;
		instance->started = true ;
		if((ast->data.tree->type == TYPE_INSTANCEPATH) && child->size == 2)
		{

			string newNodeName = ast_children_as_string((struct ast_t*) vector_get(child,1)) ;
			instance->name = newNodeName ;
			map<string,PortTypeRef*> reqPortMap = ct->required ;
			map<string,PortTypeRef*> provPortMap = ct->provided ;
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

			ContainerNode *parentNode = model->findnodesByID(parentNodeName);
			if(parentNode == NULL){
				throw KevoreeException("Node" +parentNodeName +"doesn't exist");
			}
			else{
				parentNode->addcomponents(instance);
				process = instance ;
			}


		}

	}

		else if(dynamic_cast<ChannelType*>(td) != 0){
			cout << "ChannelType" << endl ;
			ChannelType* cht = dynamic_cast<ChannelType*>(td);
			Channel *instance = factory.createChannel() ;
			instance->started = true ;
			instance->typeDefinition = cht ;
			if((ast->data.tree->type== TYPE_INSTANCEPATH) && child->size == 1)
			{
				string channelname = ast_children_as_string((struct ast_t*) vector_get(child,0)) ;
				instance->name = channelname ;
				model->addhubs(instance) ;
				process = instance ;
			}else{
				throw KevoreeException("wrong channel name : ") ;
			}
		}

		else if(dynamic_cast<GroupType*>(td) != 0){
			cout << "GroupType" << endl ;
			GroupType* gt = dynamic_cast<GroupType*>(td);
			Group *instance = factory.createGroup() ;
			instance->typeDefinition = gt ;
			instance->started = true ;
			if((ast->data.tree->type == TYPE_INSTANCEPATH) && child->size == 1)
			{
				string groupname = ast_children_as_string((struct ast_t*) vector_get(child,0)) ;
				instance->name = groupname ;
				model->addgroups(instance) ;
				process = instance ;
			}else{
				throw KevoreeException("Bad group name : " ) ;
			}
		}

	return process != NULL;

}
