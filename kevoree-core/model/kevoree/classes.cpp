#include "kevoree.h"
std::string ComponentInstance::internalGetKey(){
return name;
}
Port* ComponentInstance::findprovidedByID(std::string id){
return provided[id];
}
Port* ComponentInstance::findrequiredByID(std::string id){
return required[id];
}




void ComponentInstance::addprovided(Port *ptr)
{
    Port  *container = (Port *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Port cannot be added in ComponentInstance because the key is not defined");
    }else
    {
        if(provided.find(container->internalGetKey()) == provided.end())
        {
            provided[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"provided",ptr_any);
	container->setEContainer(this,cmd,"provided");

        }
    }
}






void ComponentInstance::addrequired(Port *ptr)
{
    Port  *container = (Port *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Port cannot be added in ComponentInstance because the key is not defined");
    }else
    {
        if(required.find(container->internalGetKey()) == required.end())
        {
            required[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"required",ptr_any);
	container->setEContainer(this,cmd,"required");

        }
    }
}


void ComponentInstance::add_namespace(_Namespace *ptr){
_namespace =ptr;

}





void ComponentInstance::removeprovided(Port *ptr)
{
    Port *container = (Port*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Port cannot be removed in ComponentInstance because the key is not defined");
    }
    else
    {
        provided.erase( provided.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}






void ComponentInstance::removerequired(Port *ptr)
{
    Port *container = (Port*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Port cannot be removed in ComponentInstance because the key is not defined");
    }
    else
    {
        required.erase( required.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}


void ComponentInstance::remove_namespace(_Namespace *ptr){
delete ptr;
}

string ComponentInstance::metaClassName() {
return "ComponentInstance";
}
void ComponentInstance::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("metaData")==0){
metaData= AnyCast<string>(___value);
} else if(___refName.compare("started")==0){
if(AnyCast<string>(___value).compare("true") == 0){
started= true;
}else { 
started= false;
}
}else {

if(___refName.compare("typeDefinition")==0){
if(___mutatorType ==ADD){
addtypeDefinition((TypeDefinition*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removetypeDefinition((TypeDefinition*)AnyCast<TypeDefinition*>(___value));
}
} else if(___refName.compare("dictionary")==0){
if(___mutatorType ==ADD){
adddictionary((Dictionary*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedictionary((Dictionary*)AnyCast<Dictionary*>(___value));
}
} else if(___refName.compare("fragmentDictionary")==0){
if(___mutatorType ==ADD){
addfragmentDictionary((FragmentDictionary*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removefragmentDictionary((FragmentDictionary*)AnyCast<FragmentDictionary*>(___value));
}
} else if(___refName.compare("provided")==0){
if(___mutatorType ==ADD){
addprovided((Port*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removeprovided((Port*)AnyCast<Port*>(___value));
}
} else if(___refName.compare("required")==0){
if(___mutatorType ==ADD){
addrequired((Port*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removerequired((Port*)AnyCast<Port*>(___value));
}
} else if(___refName.compare("_namespace")==0){
if(___mutatorType ==ADD){
add_namespace((_Namespace*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
remove_namespace((_Namespace*)AnyCast<_Namespace*>(___value));
}
}

}

}

KMFContainer* ComponentInstance::findByID(string relationName,string idP){
if(relationName.compare("typeDefinition")== 0){
return typeDefinition;
}

if(relationName.compare("dictionary")== 0){
return dictionary;
}

if(relationName.compare("fragmentDictionary")== 0){
return (KMFContainer*)findfragmentDictionaryByID(idP);
}

if(relationName.compare("provided")== 0){
return (KMFContainer*)findprovidedByID(idP);
}

if(relationName.compare("required")== 0){
return (KMFContainer*)findrequiredByID(idP);
}

if(relationName.compare("_namespace")== 0){
return _namespace;
}

return NULL;

}





void ComponentInstance::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        visitor->beginVisitRef("dictionary","org.kevoree.Dictionary");
internal_visit(visitor,dictionary,recursive,containedReference,nonContainedReference,"dictionary");
visitor->endVisitRef("dictionary");




visitor->beginVisitRef("fragmentDictionary","org.kevoree.FragmentDictionary");
for ( std::map<string,FragmentDictionary*>::iterator it = fragmentDictionary.begin();  it != fragmentDictionary.end(); ++it)
{
    FragmentDictionary * current =(FragmentDictionary*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"fragmentDictionary");
}
visitor->endVisitRef("fragmentDictionary");



visitor->beginVisitRef("provided","org.kevoree.Port");
for ( std::map<string,Port*>::iterator it = provided.begin();  it != provided.end(); ++it)
{
    Port * current =(Port*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"provided");
}
visitor->endVisitRef("provided");



visitor->beginVisitRef("required","org.kevoree.Port");
for ( std::map<string,Port*>::iterator it = required.begin();  it != required.end(); ++it)
{
    Port * current =(Port*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"required");
}
visitor->endVisitRef("required");
    }
    if(nonContainedReference)
    {
        visitor->beginVisitRef("typeDefinition","org.kevoree.TypeDefinition");
internal_visit(visitor,typeDefinition,recursive,containedReference,nonContainedReference,"typeDefinition");
visitor->endVisitRef("typeDefinition");
visitor->beginVisitRef("_namespace","org.kevoree._Namespace");
internal_visit(visitor,_namespace,recursive,containedReference,nonContainedReference,"_namespace");
visitor->endVisitRef("_namespace");

    }
    visitor->endVisitElem(this);
}


void ComponentInstance::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(metaData),"metaData",this);
visitor->visit(any(started),"started",this);
}
ComponentInstance::ComponentInstance(){

_namespace=NULL;

}

ComponentInstance::~ComponentInstance(){

if(dictionary != NULL){
delete dictionary;
dictionary= NULL;}





for ( std::map<string,FragmentDictionary*>::iterator it = fragmentDictionary.begin();  it != fragmentDictionary.end(); ++it)
{
FragmentDictionary * current = it->second;
if(current != NULL)
{
    delete current;
}

}

fragmentDictionary.clear();





for ( std::map<string,Port*>::iterator it = provided.begin();  it != provided.end(); ++it)
{
Port * current = it->second;
if(current != NULL)
{
    delete current;
}

}

provided.clear();





for ( std::map<string,Port*>::iterator it = required.begin();  it != required.end(); ++it)
{
Port * current = it->second;
if(current != NULL)
{
    delete current;
}

}

required.clear();


}

std::string ComponentType::internalGetKey(){
return name+"/"+version;
}
PortTypeRef* ComponentType::findrequiredByID(std::string id){
return required[id];
}
PortTypeRef* ComponentType::findprovidedByID(std::string id){
return provided[id];
}




void ComponentType::addrequired(PortTypeRef *ptr)
{
    PortTypeRef  *container = (PortTypeRef *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The PortTypeRef cannot be added in ComponentType because the key is not defined");
    }else
    {
        if(required.find(container->internalGetKey()) == required.end())
        {
            required[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"required",ptr_any);
	container->setEContainer(this,cmd,"required");

        }
    }
}






void ComponentType::addprovided(PortTypeRef *ptr)
{
    PortTypeRef  *container = (PortTypeRef *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The PortTypeRef cannot be added in ComponentType because the key is not defined");
    }else
    {
        if(provided.find(container->internalGetKey()) == provided.end())
        {
            provided[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"provided",ptr_any);
	container->setEContainer(this,cmd,"provided");

        }
    }
}






void ComponentType::removerequired(PortTypeRef *ptr)
{
    PortTypeRef *container = (PortTypeRef*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The PortTypeRef cannot be removed in ComponentType because the key is not defined");
    }
    else
    {
        required.erase( required.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}






void ComponentType::removeprovided(PortTypeRef *ptr)
{
    PortTypeRef *container = (PortTypeRef*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The PortTypeRef cannot be removed in ComponentType because the key is not defined");
    }
    else
    {
        provided.erase( provided.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}


string ComponentType::metaClassName() {
return "ComponentType";
}
void ComponentType::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("version")==0){
version= AnyCast<string>(___value);
} else if(___refName.compare("factoryBean")==0){
factoryBean= AnyCast<string>(___value);
} else if(___refName.compare("bean")==0){
bean= AnyCast<string>(___value);
} else if(___refName.compare("abstract")==0){
if(AnyCast<string>(___value).compare("true") == 0){
abstract= true;
}else { 
abstract= false;
}
}else {

if(___refName.compare("deployUnit")==0){
if(___mutatorType ==ADD){
adddeployUnit((DeployUnit*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedeployUnit((DeployUnit*)AnyCast<DeployUnit*>(___value));
}
} else if(___refName.compare("dictionaryType")==0){
if(___mutatorType ==ADD){
adddictionaryType((DictionaryType*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedictionaryType((DictionaryType*)AnyCast<DictionaryType*>(___value));
}
} else if(___refName.compare("superTypes")==0){
if(___mutatorType ==ADD){
addsuperTypes((TypeDefinition*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removesuperTypes((TypeDefinition*)AnyCast<TypeDefinition*>(___value));
}
} else if(___refName.compare("required")==0){
if(___mutatorType ==ADD){
addrequired((PortTypeRef*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removerequired((PortTypeRef*)AnyCast<PortTypeRef*>(___value));
}
} else if(___refName.compare("provided")==0){
if(___mutatorType ==ADD){
addprovided((PortTypeRef*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removeprovided((PortTypeRef*)AnyCast<PortTypeRef*>(___value));
}
}

}

}

KMFContainer* ComponentType::findByID(string relationName,string idP){
if(relationName.compare("deployUnit")== 0){
return (KMFContainer*)finddeployUnitByID(idP);
}

if(relationName.compare("dictionaryType")== 0){
return dictionaryType;
}

if(relationName.compare("superTypes")== 0){
return (KMFContainer*)findsuperTypesByID(idP);
}

if(relationName.compare("required")== 0){
return (KMFContainer*)findrequiredByID(idP);
}

if(relationName.compare("provided")== 0){
return (KMFContainer*)findprovidedByID(idP);
}

return NULL;

}





void ComponentType::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        visitor->beginVisitRef("dictionaryType","org.kevoree.DictionaryType");
internal_visit(visitor,dictionaryType,recursive,containedReference,nonContainedReference,"dictionaryType");
visitor->endVisitRef("dictionaryType");




visitor->beginVisitRef("required","org.kevoree.PortTypeRef");
for ( std::map<string,PortTypeRef*>::iterator it = required.begin();  it != required.end(); ++it)
{
    PortTypeRef * current =(PortTypeRef*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"required");
}
visitor->endVisitRef("required");



visitor->beginVisitRef("provided","org.kevoree.PortTypeRef");
for ( std::map<string,PortTypeRef*>::iterator it = provided.begin();  it != provided.end(); ++it)
{
    PortTypeRef * current =(PortTypeRef*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"provided");
}
visitor->endVisitRef("provided");
    }
    if(nonContainedReference)
    {
        



visitor->beginVisitRef("deployUnit","org.kevoree.DeployUnit");
for ( std::map<string,DeployUnit*>::iterator it = deployUnit.begin();  it != deployUnit.end(); ++it)
{
    DeployUnit * current =(DeployUnit*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"deployUnit");
}
visitor->endVisitRef("deployUnit");



visitor->beginVisitRef("superTypes","org.kevoree.TypeDefinition");
for ( std::map<string,TypeDefinition*>::iterator it = superTypes.begin();  it != superTypes.end(); ++it)
{
    TypeDefinition * current =(TypeDefinition*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"superTypes");
}
visitor->endVisitRef("superTypes");
    }
    visitor->endVisitElem(this);
}


void ComponentType::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(version),"version",this);
visitor->visit(any(factoryBean),"factoryBean",this);
visitor->visit(any(bean),"bean",this);
visitor->visit(any(abstract),"abstract",this);
}
ComponentType::ComponentType(){


}

ComponentType::~ComponentType(){

deployUnit.clear();
superTypes.clear();
if(dictionaryType != NULL){
delete dictionaryType;
dictionaryType= NULL;}





for ( std::map<string,PortTypeRef*>::iterator it = required.begin();  it != required.end(); ++it)
{
PortTypeRef * current = it->second;
if(current != NULL)
{
    delete current;
}

}

required.clear();





for ( std::map<string,PortTypeRef*>::iterator it = provided.begin();  it != provided.end(); ++it)
{
PortTypeRef * current = it->second;
if(current != NULL)
{
    delete current;
}

}

provided.clear();


}

std::string ContainerNode::internalGetKey(){
return name;
}
ComponentInstance* ContainerNode::findcomponentsByID(std::string id){
return components[id];
}
ContainerNode* ContainerNode::findhostsByID(std::string id){
return hosts[id];
}
Group* ContainerNode::findgroupsByID(std::string id){
return groups[id];
}
NetworkInfo* ContainerNode::findnetworkInformationByID(std::string id){
return networkInformation[id];
}




void ContainerNode::addcomponents(ComponentInstance *ptr)
{
    ComponentInstance  *container = (ComponentInstance *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The ComponentInstance cannot be added in ContainerNode because the key is not defined");
    }else
    {
        if(components.find(container->internalGetKey()) == components.end())
        {
            components[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"components",ptr_any);
	container->setEContainer(this,cmd,"components");

        }
    }
}






void ContainerNode::addhosts(ContainerNode *ptr)
{
    ContainerNode  *container = (ContainerNode *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The ContainerNode cannot be added in ContainerNode because the key is not defined");
    }else
    {
        if(hosts.find(container->internalGetKey()) == hosts.end())
        {
            hosts[container->internalGetKey()]=ptr;
            
        }
    }
}


void ContainerNode::addhost(ContainerNode *ptr){
host =ptr;

}





void ContainerNode::addgroups(Group *ptr)
{
    Group  *container = (Group *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Group cannot be added in ContainerNode because the key is not defined");
    }else
    {
        if(groups.find(container->internalGetKey()) == groups.end())
        {
            groups[container->internalGetKey()]=ptr;
            
        }
    }
}






void ContainerNode::addnetworkInformation(NetworkInfo *ptr)
{
    NetworkInfo  *container = (NetworkInfo *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The NetworkInfo cannot be added in ContainerNode because the key is not defined");
    }else
    {
        if(networkInformation.find(container->internalGetKey()) == networkInformation.end())
        {
            networkInformation[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"networkInformation",ptr_any);
	container->setEContainer(this,cmd,"networkInformation");

        }
    }
}






void ContainerNode::removecomponents(ComponentInstance *ptr)
{
    ComponentInstance *container = (ComponentInstance*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The ComponentInstance cannot be removed in ContainerNode because the key is not defined");
    }
    else
    {
        components.erase( components.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}






void ContainerNode::removehosts(ContainerNode *ptr)
{
    ContainerNode *container = (ContainerNode*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The ContainerNode cannot be removed in ContainerNode because the key is not defined");
    }
    else
    {
        hosts.erase( hosts.find(container->internalGetKey()));
        
        container->setEContainer(NULL,NULL,"");
    }
}


void ContainerNode::removehost(ContainerNode *ptr){
delete ptr;
}





void ContainerNode::removegroups(Group *ptr)
{
    Group *container = (Group*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Group cannot be removed in ContainerNode because the key is not defined");
    }
    else
    {
        groups.erase( groups.find(container->internalGetKey()));
        
        container->setEContainer(NULL,NULL,"");
    }
}






void ContainerNode::removenetworkInformation(NetworkInfo *ptr)
{
    NetworkInfo *container = (NetworkInfo*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The NetworkInfo cannot be removed in ContainerNode because the key is not defined");
    }
    else
    {
        networkInformation.erase( networkInformation.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}


string ContainerNode::metaClassName() {
return "ContainerNode";
}
void ContainerNode::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("metaData")==0){
metaData= AnyCast<string>(___value);
} else if(___refName.compare("started")==0){
if(AnyCast<string>(___value).compare("true") == 0){
started= true;
}else { 
started= false;
}
}else {

if(___refName.compare("typeDefinition")==0){
if(___mutatorType ==ADD){
addtypeDefinition((TypeDefinition*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removetypeDefinition((TypeDefinition*)AnyCast<TypeDefinition*>(___value));
}
} else if(___refName.compare("dictionary")==0){
if(___mutatorType ==ADD){
adddictionary((Dictionary*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedictionary((Dictionary*)AnyCast<Dictionary*>(___value));
}
} else if(___refName.compare("fragmentDictionary")==0){
if(___mutatorType ==ADD){
addfragmentDictionary((FragmentDictionary*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removefragmentDictionary((FragmentDictionary*)AnyCast<FragmentDictionary*>(___value));
}
} else if(___refName.compare("components")==0){
if(___mutatorType ==ADD){
addcomponents((ComponentInstance*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removecomponents((ComponentInstance*)AnyCast<ComponentInstance*>(___value));
}
} else if(___refName.compare("hosts")==0){
if(___mutatorType ==ADD){
addhosts((ContainerNode*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removehosts((ContainerNode*)AnyCast<ContainerNode*>(___value));
}
} else if(___refName.compare("host")==0){
if(___mutatorType ==ADD){
addhost((ContainerNode*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removehost((ContainerNode*)AnyCast<ContainerNode*>(___value));
}
} else if(___refName.compare("groups")==0){
if(___mutatorType ==ADD){
addgroups((Group*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removegroups((Group*)AnyCast<Group*>(___value));
}
} else if(___refName.compare("networkInformation")==0){
if(___mutatorType ==ADD){
addnetworkInformation((NetworkInfo*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removenetworkInformation((NetworkInfo*)AnyCast<NetworkInfo*>(___value));
}
}

}

}

KMFContainer* ContainerNode::findByID(string relationName,string idP){
if(relationName.compare("typeDefinition")== 0){
return typeDefinition;
}

if(relationName.compare("dictionary")== 0){
return dictionary;
}

if(relationName.compare("fragmentDictionary")== 0){
return (KMFContainer*)findfragmentDictionaryByID(idP);
}

if(relationName.compare("components")== 0){
return (KMFContainer*)findcomponentsByID(idP);
}

if(relationName.compare("hosts")== 0){
return (KMFContainer*)findhostsByID(idP);
}

if(relationName.compare("host")== 0){
return host;
}

if(relationName.compare("groups")== 0){
return (KMFContainer*)findgroupsByID(idP);
}

if(relationName.compare("networkInformation")== 0){
return (KMFContainer*)findnetworkInformationByID(idP);
}

return NULL;

}





void ContainerNode::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        visitor->beginVisitRef("dictionary","org.kevoree.Dictionary");
internal_visit(visitor,dictionary,recursive,containedReference,nonContainedReference,"dictionary");
visitor->endVisitRef("dictionary");




visitor->beginVisitRef("fragmentDictionary","org.kevoree.FragmentDictionary");
for ( std::map<string,FragmentDictionary*>::iterator it = fragmentDictionary.begin();  it != fragmentDictionary.end(); ++it)
{
    FragmentDictionary * current =(FragmentDictionary*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"fragmentDictionary");
}
visitor->endVisitRef("fragmentDictionary");



visitor->beginVisitRef("components","org.kevoree.ComponentInstance");
for ( std::map<string,ComponentInstance*>::iterator it = components.begin();  it != components.end(); ++it)
{
    ComponentInstance * current =(ComponentInstance*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"components");
}
visitor->endVisitRef("components");



visitor->beginVisitRef("networkInformation","org.kevoree.NetworkInfo");
for ( std::map<string,NetworkInfo*>::iterator it = networkInformation.begin();  it != networkInformation.end(); ++it)
{
    NetworkInfo * current =(NetworkInfo*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"networkInformation");
}
visitor->endVisitRef("networkInformation");
    }
    if(nonContainedReference)
    {
        visitor->beginVisitRef("typeDefinition","org.kevoree.TypeDefinition");
internal_visit(visitor,typeDefinition,recursive,containedReference,nonContainedReference,"typeDefinition");
visitor->endVisitRef("typeDefinition");




visitor->beginVisitRef("hosts","org.kevoree.ContainerNode");
for ( std::map<string,ContainerNode*>::iterator it = hosts.begin();  it != hosts.end(); ++it)
{
    ContainerNode * current =(ContainerNode*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"hosts");
}
visitor->endVisitRef("hosts");visitor->beginVisitRef("host","org.kevoree.ContainerNode");
internal_visit(visitor,host,recursive,containedReference,nonContainedReference,"host");
visitor->endVisitRef("host");




visitor->beginVisitRef("groups","org.kevoree.Group");
for ( std::map<string,Group*>::iterator it = groups.begin();  it != groups.end(); ++it)
{
    Group * current =(Group*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"groups");
}
visitor->endVisitRef("groups");
    }
    visitor->endVisitElem(this);
}


void ContainerNode::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(metaData),"metaData",this);
visitor->visit(any(started),"started",this);
}
ContainerNode::ContainerNode(){

host=NULL;

}

ContainerNode::~ContainerNode(){

hosts.clear();
groups.clear();
if(dictionary != NULL){
delete dictionary;
dictionary= NULL;}





for ( std::map<string,FragmentDictionary*>::iterator it = fragmentDictionary.begin();  it != fragmentDictionary.end(); ++it)
{
FragmentDictionary * current = it->second;
if(current != NULL)
{
    delete current;
}

}

fragmentDictionary.clear();





for ( std::map<string,ComponentInstance*>::iterator it = components.begin();  it != components.end(); ++it)
{
ComponentInstance * current = it->second;
if(current != NULL)
{
    delete current;
}

}

components.clear();





for ( std::map<string,NetworkInfo*>::iterator it = networkInformation.begin();  it != networkInformation.end(); ++it)
{
NetworkInfo * current = it->second;
if(current != NULL)
{
    delete current;
}

}

networkInformation.clear();


}

std::string ContainerRoot::internalGetKey(){
return generated_KMF_ID;
}
ContainerNode* ContainerRoot::findnodesByID(std::string id){
return nodes[id];
}
TypeDefinition* ContainerRoot::findtypeDefinitionsByID(std::string id){
return typeDefinitions[id];
}
Repository* ContainerRoot::findrepositoriesByID(std::string id){
return repositories[id];
}
TypedElement* ContainerRoot::finddataTypesByID(std::string id){
return dataTypes[id];
}
TypeLibrary* ContainerRoot::findlibrariesByID(std::string id){
return libraries[id];
}
Channel* ContainerRoot::findhubsByID(std::string id){
return hubs[id];
}
MBinding* ContainerRoot::findmBindingsByID(std::string id){
return mBindings[id];
}
DeployUnit* ContainerRoot::finddeployUnitsByID(std::string id){
return deployUnits[id];
}
NodeNetwork* ContainerRoot::findnodeNetworksByID(std::string id){
return nodeNetworks[id];
}
Group* ContainerRoot::findgroupsByID(std::string id){
return groups[id];
}




void ContainerRoot::addnodes(ContainerNode *ptr)
{
    ContainerNode  *container = (ContainerNode *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The ContainerNode cannot be added in ContainerRoot because the key is not defined");
    }else
    {
        if(nodes.find(container->internalGetKey()) == nodes.end())
        {
            nodes[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"nodes",ptr_any);
	container->setEContainer(this,cmd,"nodes");

        }
    }
}






void ContainerRoot::addtypeDefinitions(TypeDefinition *ptr)
{
    TypeDefinition  *container = (TypeDefinition *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The TypeDefinition cannot be added in ContainerRoot because the key is not defined");
    }else
    {
        if(typeDefinitions.find(container->internalGetKey()) == typeDefinitions.end())
        {
            typeDefinitions[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"typeDefinitions",ptr_any);
	container->setEContainer(this,cmd,"typeDefinitions");

        }
    }
}






void ContainerRoot::addrepositories(Repository *ptr)
{
    Repository  *container = (Repository *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Repository cannot be added in ContainerRoot because the key is not defined");
    }else
    {
        if(repositories.find(container->internalGetKey()) == repositories.end())
        {
            repositories[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"repositories",ptr_any);
	container->setEContainer(this,cmd,"repositories");

        }
    }
}






void ContainerRoot::adddataTypes(TypedElement *ptr)
{
    TypedElement  *container = (TypedElement *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The TypedElement cannot be added in ContainerRoot because the key is not defined");
    }else
    {
        if(dataTypes.find(container->internalGetKey()) == dataTypes.end())
        {
            dataTypes[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"dataTypes",ptr_any);
	container->setEContainer(this,cmd,"dataTypes");

        }
    }
}






void ContainerRoot::addlibraries(TypeLibrary *ptr)
{
    TypeLibrary  *container = (TypeLibrary *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The TypeLibrary cannot be added in ContainerRoot because the key is not defined");
    }else
    {
        if(libraries.find(container->internalGetKey()) == libraries.end())
        {
            libraries[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"libraries",ptr_any);
	container->setEContainer(this,cmd,"libraries");

        }
    }
}






void ContainerRoot::addhubs(Channel *ptr)
{
    Channel  *container = (Channel *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Channel cannot be added in ContainerRoot because the key is not defined");
    }else
    {
        if(hubs.find(container->internalGetKey()) == hubs.end())
        {
            hubs[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"hubs",ptr_any);
	container->setEContainer(this,cmd,"hubs");

        }
    }
}






void ContainerRoot::addmBindings(MBinding *ptr)
{
    MBinding  *container = (MBinding *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The MBinding cannot be added in ContainerRoot because the key is not defined");
    }else
    {
        if(mBindings.find(container->internalGetKey()) == mBindings.end())
        {
            mBindings[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"mBindings",ptr_any);
	container->setEContainer(this,cmd,"mBindings");

        }
    }
}






void ContainerRoot::adddeployUnits(DeployUnit *ptr)
{
    DeployUnit  *container = (DeployUnit *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The DeployUnit cannot be added in ContainerRoot because the key is not defined");
    }else
    {
        if(deployUnits.find(container->internalGetKey()) == deployUnits.end())
        {
            deployUnits[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"deployUnits",ptr_any);
	container->setEContainer(this,cmd,"deployUnits");

        }
    }
}






void ContainerRoot::addnodeNetworks(NodeNetwork *ptr)
{
    NodeNetwork  *container = (NodeNetwork *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The NodeNetwork cannot be added in ContainerRoot because the key is not defined");
    }else
    {
        if(nodeNetworks.find(container->internalGetKey()) == nodeNetworks.end())
        {
            nodeNetworks[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"nodeNetworks",ptr_any);
	container->setEContainer(this,cmd,"nodeNetworks");

        }
    }
}






void ContainerRoot::addgroups(Group *ptr)
{
    Group  *container = (Group *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Group cannot be added in ContainerRoot because the key is not defined");
    }else
    {
        if(groups.find(container->internalGetKey()) == groups.end())
        {
            groups[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"groups",ptr_any);
	container->setEContainer(this,cmd,"groups");

        }
    }
}






void ContainerRoot::removenodes(ContainerNode *ptr)
{
    ContainerNode *container = (ContainerNode*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The ContainerNode cannot be removed in ContainerRoot because the key is not defined");
    }
    else
    {
        nodes.erase( nodes.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}






void ContainerRoot::removetypeDefinitions(TypeDefinition *ptr)
{
    TypeDefinition *container = (TypeDefinition*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The TypeDefinition cannot be removed in ContainerRoot because the key is not defined");
    }
    else
    {
        typeDefinitions.erase( typeDefinitions.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}






void ContainerRoot::removerepositories(Repository *ptr)
{
    Repository *container = (Repository*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Repository cannot be removed in ContainerRoot because the key is not defined");
    }
    else
    {
        repositories.erase( repositories.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}






void ContainerRoot::removedataTypes(TypedElement *ptr)
{
    TypedElement *container = (TypedElement*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The TypedElement cannot be removed in ContainerRoot because the key is not defined");
    }
    else
    {
        dataTypes.erase( dataTypes.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}






void ContainerRoot::removelibraries(TypeLibrary *ptr)
{
    TypeLibrary *container = (TypeLibrary*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The TypeLibrary cannot be removed in ContainerRoot because the key is not defined");
    }
    else
    {
        libraries.erase( libraries.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}






void ContainerRoot::removehubs(Channel *ptr)
{
    Channel *container = (Channel*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Channel cannot be removed in ContainerRoot because the key is not defined");
    }
    else
    {
        hubs.erase( hubs.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}






void ContainerRoot::removemBindings(MBinding *ptr)
{
    MBinding *container = (MBinding*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The MBinding cannot be removed in ContainerRoot because the key is not defined");
    }
    else
    {
        mBindings.erase( mBindings.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}






void ContainerRoot::removedeployUnits(DeployUnit *ptr)
{
    DeployUnit *container = (DeployUnit*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The DeployUnit cannot be removed in ContainerRoot because the key is not defined");
    }
    else
    {
        deployUnits.erase( deployUnits.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}






void ContainerRoot::removenodeNetworks(NodeNetwork *ptr)
{
    NodeNetwork *container = (NodeNetwork*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The NodeNetwork cannot be removed in ContainerRoot because the key is not defined");
    }
    else
    {
        nodeNetworks.erase( nodeNetworks.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}






void ContainerRoot::removegroups(Group *ptr)
{
    Group *container = (Group*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Group cannot be removed in ContainerRoot because the key is not defined");
    }
    else
    {
        groups.erase( groups.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}


string ContainerRoot::metaClassName() {
return "ContainerRoot";
}
void ContainerRoot::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("generated_KMF_ID")==0){
generated_KMF_ID= AnyCast<string>(___value);
}else {

if(___refName.compare("nodes")==0){
if(___mutatorType ==ADD){
addnodes((ContainerNode*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removenodes((ContainerNode*)AnyCast<ContainerNode*>(___value));
}
} else if(___refName.compare("typeDefinitions")==0){
if(___mutatorType ==ADD){
addtypeDefinitions((TypeDefinition*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removetypeDefinitions((TypeDefinition*)AnyCast<TypeDefinition*>(___value));
}
} else if(___refName.compare("repositories")==0){
if(___mutatorType ==ADD){
addrepositories((Repository*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removerepositories((Repository*)AnyCast<Repository*>(___value));
}
} else if(___refName.compare("dataTypes")==0){
if(___mutatorType ==ADD){
adddataTypes((TypedElement*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedataTypes((TypedElement*)AnyCast<TypedElement*>(___value));
}
} else if(___refName.compare("libraries")==0){
if(___mutatorType ==ADD){
addlibraries((TypeLibrary*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removelibraries((TypeLibrary*)AnyCast<TypeLibrary*>(___value));
}
} else if(___refName.compare("hubs")==0){
if(___mutatorType ==ADD){
addhubs((Channel*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removehubs((Channel*)AnyCast<Channel*>(___value));
}
} else if(___refName.compare("mBindings")==0){
if(___mutatorType ==ADD){
addmBindings((MBinding*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removemBindings((MBinding*)AnyCast<MBinding*>(___value));
}
} else if(___refName.compare("deployUnits")==0){
if(___mutatorType ==ADD){
adddeployUnits((DeployUnit*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedeployUnits((DeployUnit*)AnyCast<DeployUnit*>(___value));
}
} else if(___refName.compare("nodeNetworks")==0){
if(___mutatorType ==ADD){
addnodeNetworks((NodeNetwork*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removenodeNetworks((NodeNetwork*)AnyCast<NodeNetwork*>(___value));
}
} else if(___refName.compare("groups")==0){
if(___mutatorType ==ADD){
addgroups((Group*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removegroups((Group*)AnyCast<Group*>(___value));
}
}

}

}

KMFContainer* ContainerRoot::findByID(string relationName,string idP){
if(relationName.compare("nodes")== 0){
return (KMFContainer*)findnodesByID(idP);
}

if(relationName.compare("typeDefinitions")== 0){
return (KMFContainer*)findtypeDefinitionsByID(idP);
}

if(relationName.compare("repositories")== 0){
return (KMFContainer*)findrepositoriesByID(idP);
}

if(relationName.compare("dataTypes")== 0){
return (KMFContainer*)finddataTypesByID(idP);
}

if(relationName.compare("libraries")== 0){
return (KMFContainer*)findlibrariesByID(idP);
}

if(relationName.compare("hubs")== 0){
return (KMFContainer*)findhubsByID(idP);
}

if(relationName.compare("mBindings")== 0){
return (KMFContainer*)findmBindingsByID(idP);
}

if(relationName.compare("deployUnits")== 0){
return (KMFContainer*)finddeployUnitsByID(idP);
}

if(relationName.compare("nodeNetworks")== 0){
return (KMFContainer*)findnodeNetworksByID(idP);
}

if(relationName.compare("groups")== 0){
return (KMFContainer*)findgroupsByID(idP);
}

return NULL;

}





void ContainerRoot::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        



visitor->beginVisitRef("nodes","org.kevoree.ContainerNode");
for ( std::map<string,ContainerNode*>::iterator it = nodes.begin();  it != nodes.end(); ++it)
{
    ContainerNode * current =(ContainerNode*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"nodes");
}
visitor->endVisitRef("nodes");



visitor->beginVisitRef("typeDefinitions","org.kevoree.TypeDefinition");
for ( std::map<string,TypeDefinition*>::iterator it = typeDefinitions.begin();  it != typeDefinitions.end(); ++it)
{
    TypeDefinition * current =(TypeDefinition*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"typeDefinitions");
}
visitor->endVisitRef("typeDefinitions");



visitor->beginVisitRef("repositories","org.kevoree.Repository");
for ( std::map<string,Repository*>::iterator it = repositories.begin();  it != repositories.end(); ++it)
{
    Repository * current =(Repository*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"repositories");
}
visitor->endVisitRef("repositories");



visitor->beginVisitRef("dataTypes","org.kevoree.TypedElement");
for ( std::map<string,TypedElement*>::iterator it = dataTypes.begin();  it != dataTypes.end(); ++it)
{
    TypedElement * current =(TypedElement*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"dataTypes");
}
visitor->endVisitRef("dataTypes");



visitor->beginVisitRef("libraries","org.kevoree.TypeLibrary");
for ( std::map<string,TypeLibrary*>::iterator it = libraries.begin();  it != libraries.end(); ++it)
{
    TypeLibrary * current =(TypeLibrary*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"libraries");
}
visitor->endVisitRef("libraries");



visitor->beginVisitRef("hubs","org.kevoree.Channel");
for ( std::map<string,Channel*>::iterator it = hubs.begin();  it != hubs.end(); ++it)
{
    Channel * current =(Channel*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"hubs");
}
visitor->endVisitRef("hubs");



visitor->beginVisitRef("mBindings","org.kevoree.MBinding");
for ( std::map<string,MBinding*>::iterator it = mBindings.begin();  it != mBindings.end(); ++it)
{
    MBinding * current =(MBinding*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"mBindings");
}
visitor->endVisitRef("mBindings");



visitor->beginVisitRef("deployUnits","org.kevoree.DeployUnit");
for ( std::map<string,DeployUnit*>::iterator it = deployUnits.begin();  it != deployUnits.end(); ++it)
{
    DeployUnit * current =(DeployUnit*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"deployUnits");
}
visitor->endVisitRef("deployUnits");



visitor->beginVisitRef("nodeNetworks","org.kevoree.NodeNetwork");
for ( std::map<string,NodeNetwork*>::iterator it = nodeNetworks.begin();  it != nodeNetworks.end(); ++it)
{
    NodeNetwork * current =(NodeNetwork*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"nodeNetworks");
}
visitor->endVisitRef("nodeNetworks");



visitor->beginVisitRef("groups","org.kevoree.Group");
for ( std::map<string,Group*>::iterator it = groups.begin();  it != groups.end(); ++it)
{
    Group * current =(Group*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"groups");
}
visitor->endVisitRef("groups");
    }
    if(nonContainedReference)
    {
        
    }
    visitor->endVisitElem(this);
}


void ContainerRoot::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(generated_KMF_ID),"generated_KMF_ID",this);
}
ContainerRoot::ContainerRoot(){

generated_KMF_ID= Uuid::getSingleton().generateUUID();

}

ContainerRoot::~ContainerRoot(){






for ( std::map<string,ContainerNode*>::iterator it = nodes.begin();  it != nodes.end(); ++it)
{
ContainerNode * current = it->second;
if(current != NULL)
{
    delete current;
}

}

nodes.clear();





for ( std::map<string,TypeDefinition*>::iterator it = typeDefinitions.begin();  it != typeDefinitions.end(); ++it)
{
TypeDefinition * current = it->second;
if(current != NULL)
{
    delete current;
}

}

typeDefinitions.clear();





for ( std::map<string,Repository*>::iterator it = repositories.begin();  it != repositories.end(); ++it)
{
Repository * current = it->second;
if(current != NULL)
{
    delete current;
}

}

repositories.clear();





for ( std::map<string,TypedElement*>::iterator it = dataTypes.begin();  it != dataTypes.end(); ++it)
{
TypedElement * current = it->second;
if(current != NULL)
{
    delete current;
}

}

dataTypes.clear();





for ( std::map<string,TypeLibrary*>::iterator it = libraries.begin();  it != libraries.end(); ++it)
{
TypeLibrary * current = it->second;
if(current != NULL)
{
    delete current;
}

}

libraries.clear();





for ( std::map<string,Channel*>::iterator it = hubs.begin();  it != hubs.end(); ++it)
{
Channel * current = it->second;
if(current != NULL)
{
    delete current;
}

}

hubs.clear();





for ( std::map<string,MBinding*>::iterator it = mBindings.begin();  it != mBindings.end(); ++it)
{
MBinding * current = it->second;
if(current != NULL)
{
    delete current;
}

}

mBindings.clear();





for ( std::map<string,DeployUnit*>::iterator it = deployUnits.begin();  it != deployUnits.end(); ++it)
{
DeployUnit * current = it->second;
if(current != NULL)
{
    delete current;
}

}

deployUnits.clear();





for ( std::map<string,NodeNetwork*>::iterator it = nodeNetworks.begin();  it != nodeNetworks.end(); ++it)
{
NodeNetwork * current = it->second;
if(current != NULL)
{
    delete current;
}

}

nodeNetworks.clear();





for ( std::map<string,Group*>::iterator it = groups.begin();  it != groups.end(); ++it)
{
Group * current = it->second;
if(current != NULL)
{
    delete current;
}

}

groups.clear();


}

std::string PortType::internalGetKey(){
return name+"/"+version;
}
string PortType::metaClassName() {
return "PortType";
}
void PortType::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("version")==0){
version= AnyCast<string>(___value);
} else if(___refName.compare("factoryBean")==0){
factoryBean= AnyCast<string>(___value);
} else if(___refName.compare("bean")==0){
bean= AnyCast<string>(___value);
} else if(___refName.compare("abstract")==0){
if(AnyCast<string>(___value).compare("true") == 0){
abstract= true;
}else { 
abstract= false;
}
} else if(___refName.compare("synchrone")==0){
if(AnyCast<string>(___value).compare("true") == 0){
synchrone= true;
}else { 
synchrone= false;
}
}else {

if(___refName.compare("deployUnit")==0){
if(___mutatorType ==ADD){
adddeployUnit((DeployUnit*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedeployUnit((DeployUnit*)AnyCast<DeployUnit*>(___value));
}
} else if(___refName.compare("dictionaryType")==0){
if(___mutatorType ==ADD){
adddictionaryType((DictionaryType*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedictionaryType((DictionaryType*)AnyCast<DictionaryType*>(___value));
}
} else if(___refName.compare("superTypes")==0){
if(___mutatorType ==ADD){
addsuperTypes((TypeDefinition*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removesuperTypes((TypeDefinition*)AnyCast<TypeDefinition*>(___value));
}
}

}

}

KMFContainer* PortType::findByID(string relationName,string idP){
if(relationName.compare("deployUnit")== 0){
return (KMFContainer*)finddeployUnitByID(idP);
}

if(relationName.compare("dictionaryType")== 0){
return dictionaryType;
}

if(relationName.compare("superTypes")== 0){
return (KMFContainer*)findsuperTypesByID(idP);
}

return NULL;

}





void PortType::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        visitor->beginVisitRef("dictionaryType","org.kevoree.DictionaryType");
internal_visit(visitor,dictionaryType,recursive,containedReference,nonContainedReference,"dictionaryType");
visitor->endVisitRef("dictionaryType");

    }
    if(nonContainedReference)
    {
        



visitor->beginVisitRef("deployUnit","org.kevoree.DeployUnit");
for ( std::map<string,DeployUnit*>::iterator it = deployUnit.begin();  it != deployUnit.end(); ++it)
{
    DeployUnit * current =(DeployUnit*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"deployUnit");
}
visitor->endVisitRef("deployUnit");



visitor->beginVisitRef("superTypes","org.kevoree.TypeDefinition");
for ( std::map<string,TypeDefinition*>::iterator it = superTypes.begin();  it != superTypes.end(); ++it)
{
    TypeDefinition * current =(TypeDefinition*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"superTypes");
}
visitor->endVisitRef("superTypes");
    }
    visitor->endVisitElem(this);
}


void PortType::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(version),"version",this);
visitor->visit(any(factoryBean),"factoryBean",this);
visitor->visit(any(bean),"bean",this);
visitor->visit(any(abstract),"abstract",this);
visitor->visit(any(synchrone),"synchrone",this);
}
PortType::PortType(){


}

PortType::~PortType(){

deployUnit.clear();
superTypes.clear();
if(dictionaryType != NULL){
delete dictionaryType;
dictionaryType= NULL;}


}

std::string Port::internalGetKey(){
return name;
}
MBinding* Port::findbindingsByID(std::string id){
return bindings[id];
}




void Port::addbindings(MBinding *ptr)
{
    MBinding  *container = (MBinding *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The MBinding cannot be added in Port because the key is not defined");
    }else
    {
        if(bindings.find(container->internalGetKey()) == bindings.end())
        {
            bindings[container->internalGetKey()]=ptr;
            
        }
    }
}


void Port::addportTypeRef(PortTypeRef *ptr){
portTypeRef =ptr;

}





void Port::removebindings(MBinding *ptr)
{
    MBinding *container = (MBinding*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The MBinding cannot be removed in Port because the key is not defined");
    }
    else
    {
        bindings.erase( bindings.find(container->internalGetKey()));
        
        container->setEContainer(NULL,NULL,"");
    }
}


void Port::removeportTypeRef(PortTypeRef *ptr){
delete ptr;
}

string Port::metaClassName() {
return "Port";
}
void Port::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
}else {

if(___refName.compare("bindings")==0){
if(___mutatorType ==ADD){
addbindings((MBinding*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removebindings((MBinding*)AnyCast<MBinding*>(___value));
}
} else if(___refName.compare("portTypeRef")==0){
if(___mutatorType ==ADD){
addportTypeRef((PortTypeRef*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removeportTypeRef((PortTypeRef*)AnyCast<PortTypeRef*>(___value));
}
}

}

}

KMFContainer* Port::findByID(string relationName,string idP){
if(relationName.compare("bindings")== 0){
return (KMFContainer*)findbindingsByID(idP);
}

if(relationName.compare("portTypeRef")== 0){
return portTypeRef;
}

return NULL;

}





void Port::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        
    }
    if(nonContainedReference)
    {
        



visitor->beginVisitRef("bindings","org.kevoree.MBinding");
for ( std::map<string,MBinding*>::iterator it = bindings.begin();  it != bindings.end(); ++it)
{
    MBinding * current =(MBinding*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"bindings");
}
visitor->endVisitRef("bindings");visitor->beginVisitRef("portTypeRef","org.kevoree.PortTypeRef");
internal_visit(visitor,portTypeRef,recursive,containedReference,nonContainedReference,"portTypeRef");
visitor->endVisitRef("portTypeRef");

    }
    visitor->endVisitElem(this);
}


void Port::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
}
Port::Port(){

portTypeRef=NULL;

}

Port::~Port(){

bindings.clear();


}

std::string _Namespace::internalGetKey(){
return name;
}
Instance* _Namespace::findelementsByID(std::string id){
return elements[id];
}




void _Namespace::addelements(Instance *ptr)
{
    Instance  *container = (Instance *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Instance cannot be added in _Namespace because the key is not defined");
    }else
    {
        if(elements.find(container->internalGetKey()) == elements.end())
        {
            elements[container->internalGetKey()]=ptr;
            
        }
    }
}






void _Namespace::removeelements(Instance *ptr)
{
    Instance *container = (Instance*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Instance cannot be removed in _Namespace because the key is not defined");
    }
    else
    {
        elements.erase( elements.find(container->internalGetKey()));
        
        container->setEContainer(NULL,NULL,"");
    }
}


string _Namespace::metaClassName() {
return "_Namespace";
}
void _Namespace::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
}else {

if(___refName.compare("elements")==0){
if(___mutatorType ==ADD){
addelements((Instance*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removeelements((Instance*)AnyCast<Instance*>(___value));
}
}

}

}

KMFContainer* _Namespace::findByID(string relationName,string idP){
if(relationName.compare("elements")== 0){
return (KMFContainer*)findelementsByID(idP);
}

return NULL;

}





void _Namespace::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        
    }
    if(nonContainedReference)
    {
        



visitor->beginVisitRef("elements","org.kevoree.Instance");
for ( std::map<string,Instance*>::iterator it = elements.begin();  it != elements.end(); ++it)
{
    Instance * current =(Instance*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"elements");
}
visitor->endVisitRef("elements");
    }
    visitor->endVisitElem(this);
}


void _Namespace::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
}
_Namespace::_Namespace(){


}

_Namespace::~_Namespace(){

elements.clear();


}

std::string Dictionary::internalGetKey(){
return generated_KMF_ID;
}
DictionaryValue* Dictionary::findvaluesByID(std::string id){
return values[id];
}




void Dictionary::addvalues(DictionaryValue *ptr)
{
    DictionaryValue  *container = (DictionaryValue *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The DictionaryValue cannot be added in Dictionary because the key is not defined");
    }else
    {
        if(values.find(container->internalGetKey()) == values.end())
        {
            values[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"values",ptr_any);
	container->setEContainer(this,cmd,"values");

        }
    }
}






void Dictionary::removevalues(DictionaryValue *ptr)
{
    DictionaryValue *container = (DictionaryValue*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The DictionaryValue cannot be removed in Dictionary because the key is not defined");
    }
    else
    {
        values.erase( values.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}


string Dictionary::metaClassName() {
return "Dictionary";
}
void Dictionary::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("generated_KMF_ID")==0){
generated_KMF_ID= AnyCast<string>(___value);
}else {

if(___refName.compare("values")==0){
if(___mutatorType ==ADD){
addvalues((DictionaryValue*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removevalues((DictionaryValue*)AnyCast<DictionaryValue*>(___value));
}
}

}

}

KMFContainer* Dictionary::findByID(string relationName,string idP){
if(relationName.compare("values")== 0){
return (KMFContainer*)findvaluesByID(idP);
}

return NULL;

}





void Dictionary::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        



visitor->beginVisitRef("values","org.kevoree.DictionaryValue");
for ( std::map<string,DictionaryValue*>::iterator it = values.begin();  it != values.end(); ++it)
{
    DictionaryValue * current =(DictionaryValue*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"values");
}
visitor->endVisitRef("values");
    }
    if(nonContainedReference)
    {
        
    }
    visitor->endVisitElem(this);
}


void Dictionary::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(generated_KMF_ID),"generated_KMF_ID",this);
}
Dictionary::Dictionary(){

generated_KMF_ID= Uuid::getSingleton().generateUUID();

}

Dictionary::~Dictionary(){






for ( std::map<string,DictionaryValue*>::iterator it = values.begin();  it != values.end(); ++it)
{
DictionaryValue * current = it->second;
if(current != NULL)
{
    delete current;
}

}

values.clear();


}

std::string FragmentDictionary::internalGetKey(){
return name;
}
string FragmentDictionary::metaClassName() {
return "FragmentDictionary";
}
void FragmentDictionary::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("generated_KMF_ID")==0){
generated_KMF_ID= AnyCast<string>(___value);
} else if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
}else {

if(___refName.compare("values")==0){
if(___mutatorType ==ADD){
addvalues((DictionaryValue*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removevalues((DictionaryValue*)AnyCast<DictionaryValue*>(___value));
}
}

}

}

KMFContainer* FragmentDictionary::findByID(string relationName,string idP){
if(relationName.compare("values")== 0){
return (KMFContainer*)findvaluesByID(idP);
}

return NULL;

}





void FragmentDictionary::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        



visitor->beginVisitRef("values","org.kevoree.DictionaryValue");
for ( std::map<string,DictionaryValue*>::iterator it = values.begin();  it != values.end(); ++it)
{
    DictionaryValue * current =(DictionaryValue*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"values");
}
visitor->endVisitRef("values");
    }
    if(nonContainedReference)
    {
        
    }
    visitor->endVisitElem(this);
}


void FragmentDictionary::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(generated_KMF_ID),"generated_KMF_ID",this);
visitor->visit(any(name),"name",this);
}
FragmentDictionary::FragmentDictionary(){


}

FragmentDictionary::~FragmentDictionary(){






for ( std::map<string,DictionaryValue*>::iterator it = values.begin();  it != values.end(); ++it)
{
DictionaryValue * current = it->second;
if(current != NULL)
{
    delete current;
}

}

values.clear();


}

std::string DictionaryType::internalGetKey(){
return generated_KMF_ID;
}
DictionaryAttribute* DictionaryType::findattributesByID(std::string id){
return attributes[id];
}




void DictionaryType::addattributes(DictionaryAttribute *ptr)
{
    DictionaryAttribute  *container = (DictionaryAttribute *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The DictionaryAttribute cannot be added in DictionaryType because the key is not defined");
    }else
    {
        if(attributes.find(container->internalGetKey()) == attributes.end())
        {
            attributes[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"attributes",ptr_any);
	container->setEContainer(this,cmd,"attributes");

        }
    }
}






void DictionaryType::removeattributes(DictionaryAttribute *ptr)
{
    DictionaryAttribute *container = (DictionaryAttribute*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The DictionaryAttribute cannot be removed in DictionaryType because the key is not defined");
    }
    else
    {
        attributes.erase( attributes.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}


string DictionaryType::metaClassName() {
return "DictionaryType";
}
void DictionaryType::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("generated_KMF_ID")==0){
generated_KMF_ID= AnyCast<string>(___value);
}else {

if(___refName.compare("attributes")==0){
if(___mutatorType ==ADD){
addattributes((DictionaryAttribute*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removeattributes((DictionaryAttribute*)AnyCast<DictionaryAttribute*>(___value));
}
}

}

}

KMFContainer* DictionaryType::findByID(string relationName,string idP){
if(relationName.compare("attributes")== 0){
return (KMFContainer*)findattributesByID(idP);
}

return NULL;

}





void DictionaryType::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        



visitor->beginVisitRef("attributes","org.kevoree.DictionaryAttribute");
for ( std::map<string,DictionaryAttribute*>::iterator it = attributes.begin();  it != attributes.end(); ++it)
{
    DictionaryAttribute * current =(DictionaryAttribute*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"attributes");
}
visitor->endVisitRef("attributes");
    }
    if(nonContainedReference)
    {
        
    }
    visitor->endVisitElem(this);
}


void DictionaryType::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(generated_KMF_ID),"generated_KMF_ID",this);
}
DictionaryType::DictionaryType(){

generated_KMF_ID= Uuid::getSingleton().generateUUID();

}

DictionaryType::~DictionaryType(){






for ( std::map<string,DictionaryAttribute*>::iterator it = attributes.begin();  it != attributes.end(); ++it)
{
DictionaryAttribute * current = it->second;
if(current != NULL)
{
    delete current;
}

}

attributes.clear();


}

std::string DictionaryAttribute::internalGetKey(){
return name;
}
string DictionaryAttribute::metaClassName() {
return "DictionaryAttribute";
}
void DictionaryAttribute::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("optional")==0){
if(AnyCast<string>(___value).compare("true") == 0){
optional= true;
}else { 
optional= false;
}
} else if(___refName.compare("state")==0){
if(AnyCast<string>(___value).compare("true") == 0){
state= true;
}else { 
state= false;
}
} else if(___refName.compare("datatype")==0){
datatype= AnyCast<string>(___value);
} else if(___refName.compare("fragmentDependant")==0){
if(AnyCast<string>(___value).compare("true") == 0){
fragmentDependant= true;
}else { 
fragmentDependant= false;
}
} else if(___refName.compare("defaultValue")==0){
defaultValue= AnyCast<string>(___value);
}else {

if(___refName.compare("genericTypes")==0){
if(___mutatorType ==ADD){
addgenericTypes((TypedElement*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removegenericTypes((TypedElement*)AnyCast<TypedElement*>(___value));
}
}

}

}

KMFContainer* DictionaryAttribute::findByID(string relationName,string idP){
if(relationName.compare("genericTypes")== 0){
return (KMFContainer*)findgenericTypesByID(idP);
}

return NULL;

}





void DictionaryAttribute::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        
    }
    if(nonContainedReference)
    {
        



visitor->beginVisitRef("genericTypes","org.kevoree.TypedElement");
for ( std::map<string,TypedElement*>::iterator it = genericTypes.begin();  it != genericTypes.end(); ++it)
{
    TypedElement * current =(TypedElement*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"genericTypes");
}
visitor->endVisitRef("genericTypes");
    }
    visitor->endVisitElem(this);
}


void DictionaryAttribute::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(optional),"optional",this);
visitor->visit(any(state),"state",this);
visitor->visit(any(datatype),"datatype",this);
visitor->visit(any(fragmentDependant),"fragmentDependant",this);
visitor->visit(any(defaultValue),"defaultValue",this);
}
DictionaryAttribute::DictionaryAttribute(){


}

DictionaryAttribute::~DictionaryAttribute(){

genericTypes.clear();


}

std::string DictionaryValue::internalGetKey(){
return name;
}
string DictionaryValue::metaClassName() {
return "DictionaryValue";
}
void DictionaryValue::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("value")==0){
value= AnyCast<string>(___value);
}else {

}

}





void DictionaryValue::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        
    }
    if(nonContainedReference)
    {
        
    }
    visitor->endVisitElem(this);
}


void DictionaryValue::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(value),"value",this);
}
DictionaryValue::DictionaryValue(){


}

DictionaryValue::~DictionaryValue(){



}

std::string PortTypeRef::internalGetKey(){
return name;
}
PortTypeMapping* PortTypeRef::findmappingsByID(std::string id){
return mappings[id];
}
void PortTypeRef::addref(PortType *ptr){
ref =ptr;

}





void PortTypeRef::addmappings(PortTypeMapping *ptr)
{
    PortTypeMapping  *container = (PortTypeMapping *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The PortTypeMapping cannot be added in PortTypeRef because the key is not defined");
    }else
    {
        if(mappings.find(container->internalGetKey()) == mappings.end())
        {
            mappings[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"mappings",ptr_any);
	container->setEContainer(this,cmd,"mappings");

        }
    }
}


void PortTypeRef::removeref(PortType *ptr){
delete ptr;
}





void PortTypeRef::removemappings(PortTypeMapping *ptr)
{
    PortTypeMapping *container = (PortTypeMapping*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The PortTypeMapping cannot be removed in PortTypeRef because the key is not defined");
    }
    else
    {
        mappings.erase( mappings.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}


string PortTypeRef::metaClassName() {
return "PortTypeRef";
}
void PortTypeRef::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("optional")==0){
short f;
Utils::from_string<short>(f, AnyCast<string>(___value), std::dec);
optional= f;
} else if(___refName.compare("noDependency")==0){
short f;
Utils::from_string<short>(f, AnyCast<string>(___value), std::dec);
noDependency= f;
}else {

if(___refName.compare("ref")==0){
if(___mutatorType ==ADD){
addref((PortType*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removeref((PortType*)AnyCast<PortType*>(___value));
}
} else if(___refName.compare("mappings")==0){
if(___mutatorType ==ADD){
addmappings((PortTypeMapping*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removemappings((PortTypeMapping*)AnyCast<PortTypeMapping*>(___value));
}
}

}

}

KMFContainer* PortTypeRef::findByID(string relationName,string idP){
if(relationName.compare("ref")== 0){
return ref;
}

if(relationName.compare("mappings")== 0){
return (KMFContainer*)findmappingsByID(idP);
}

return NULL;

}





void PortTypeRef::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        



visitor->beginVisitRef("mappings","org.kevoree.PortTypeMapping");
for ( std::map<string,PortTypeMapping*>::iterator it = mappings.begin();  it != mappings.end(); ++it)
{
    PortTypeMapping * current =(PortTypeMapping*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"mappings");
}
visitor->endVisitRef("mappings");
    }
    if(nonContainedReference)
    {
        visitor->beginVisitRef("ref","org.kevoree.PortType");
internal_visit(visitor,ref,recursive,containedReference,nonContainedReference,"ref");
visitor->endVisitRef("ref");

    }
    visitor->endVisitElem(this);
}


void PortTypeRef::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(optional),"optional",this);
visitor->visit(any(noDependency),"noDependency",this);
}
PortTypeRef::PortTypeRef(){

ref=NULL;

}

PortTypeRef::~PortTypeRef(){






for ( std::map<string,PortTypeMapping*>::iterator it = mappings.begin();  it != mappings.end(); ++it)
{
PortTypeMapping * current = it->second;
if(current != NULL)
{
    delete current;
}

}

mappings.clear();


}

std::string ServicePortType::internalGetKey(){
return name+"/"+version;
}
Operation* ServicePortType::findoperationsByID(std::string id){
return operations[id];
}




void ServicePortType::addoperations(Operation *ptr)
{
    Operation  *container = (Operation *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Operation cannot be added in ServicePortType because the key is not defined");
    }else
    {
        if(operations.find(container->internalGetKey()) == operations.end())
        {
            operations[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"operations",ptr_any);
	container->setEContainer(this,cmd,"operations");

        }
    }
}






void ServicePortType::removeoperations(Operation *ptr)
{
    Operation *container = (Operation*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Operation cannot be removed in ServicePortType because the key is not defined");
    }
    else
    {
        operations.erase( operations.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}


string ServicePortType::metaClassName() {
return "ServicePortType";
}
void ServicePortType::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("version")==0){
version= AnyCast<string>(___value);
} else if(___refName.compare("factoryBean")==0){
factoryBean= AnyCast<string>(___value);
} else if(___refName.compare("bean")==0){
bean= AnyCast<string>(___value);
} else if(___refName.compare("abstract")==0){
if(AnyCast<string>(___value).compare("true") == 0){
abstract= true;
}else { 
abstract= false;
}
} else if(___refName.compare("synchrone")==0){
if(AnyCast<string>(___value).compare("true") == 0){
synchrone= true;
}else { 
synchrone= false;
}
} else if(___refName.compare("interface")==0){
interface= AnyCast<string>(___value);
}else {

if(___refName.compare("deployUnit")==0){
if(___mutatorType ==ADD){
adddeployUnit((DeployUnit*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedeployUnit((DeployUnit*)AnyCast<DeployUnit*>(___value));
}
} else if(___refName.compare("dictionaryType")==0){
if(___mutatorType ==ADD){
adddictionaryType((DictionaryType*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedictionaryType((DictionaryType*)AnyCast<DictionaryType*>(___value));
}
} else if(___refName.compare("superTypes")==0){
if(___mutatorType ==ADD){
addsuperTypes((TypeDefinition*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removesuperTypes((TypeDefinition*)AnyCast<TypeDefinition*>(___value));
}
} else if(___refName.compare("operations")==0){
if(___mutatorType ==ADD){
addoperations((Operation*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removeoperations((Operation*)AnyCast<Operation*>(___value));
}
}

}

}

KMFContainer* ServicePortType::findByID(string relationName,string idP){
if(relationName.compare("deployUnit")== 0){
return (KMFContainer*)finddeployUnitByID(idP);
}

if(relationName.compare("dictionaryType")== 0){
return dictionaryType;
}

if(relationName.compare("superTypes")== 0){
return (KMFContainer*)findsuperTypesByID(idP);
}

if(relationName.compare("operations")== 0){
return (KMFContainer*)findoperationsByID(idP);
}

return NULL;

}





void ServicePortType::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        visitor->beginVisitRef("dictionaryType","org.kevoree.DictionaryType");
internal_visit(visitor,dictionaryType,recursive,containedReference,nonContainedReference,"dictionaryType");
visitor->endVisitRef("dictionaryType");




visitor->beginVisitRef("operations","org.kevoree.Operation");
for ( std::map<string,Operation*>::iterator it = operations.begin();  it != operations.end(); ++it)
{
    Operation * current =(Operation*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"operations");
}
visitor->endVisitRef("operations");
    }
    if(nonContainedReference)
    {
        



visitor->beginVisitRef("deployUnit","org.kevoree.DeployUnit");
for ( std::map<string,DeployUnit*>::iterator it = deployUnit.begin();  it != deployUnit.end(); ++it)
{
    DeployUnit * current =(DeployUnit*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"deployUnit");
}
visitor->endVisitRef("deployUnit");



visitor->beginVisitRef("superTypes","org.kevoree.TypeDefinition");
for ( std::map<string,TypeDefinition*>::iterator it = superTypes.begin();  it != superTypes.end(); ++it)
{
    TypeDefinition * current =(TypeDefinition*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"superTypes");
}
visitor->endVisitRef("superTypes");
    }
    visitor->endVisitElem(this);
}


void ServicePortType::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(version),"version",this);
visitor->visit(any(factoryBean),"factoryBean",this);
visitor->visit(any(bean),"bean",this);
visitor->visit(any(abstract),"abstract",this);
visitor->visit(any(synchrone),"synchrone",this);
visitor->visit(any(interface),"interface",this);
}
ServicePortType::ServicePortType(){


}

ServicePortType::~ServicePortType(){

deployUnit.clear();
superTypes.clear();
if(dictionaryType != NULL){
delete dictionaryType;
dictionaryType= NULL;}





for ( std::map<string,Operation*>::iterator it = operations.begin();  it != operations.end(); ++it)
{
Operation * current = it->second;
if(current != NULL)
{
    delete current;
}

}

operations.clear();


}

std::string Operation::internalGetKey(){
return name;
}
Parameter* Operation::findparametersByID(std::string id){
return parameters[id];
}




void Operation::addparameters(Parameter *ptr)
{
    Parameter  *container = (Parameter *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Parameter cannot be added in Operation because the key is not defined");
    }else
    {
        if(parameters.find(container->internalGetKey()) == parameters.end())
        {
            parameters[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"parameters",ptr_any);
	container->setEContainer(this,cmd,"parameters");

        }
    }
}


void Operation::addreturnType(TypedElement *ptr){
returnType =ptr;

}





void Operation::removeparameters(Parameter *ptr)
{
    Parameter *container = (Parameter*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The Parameter cannot be removed in Operation because the key is not defined");
    }
    else
    {
        parameters.erase( parameters.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}


void Operation::removereturnType(TypedElement *ptr){
delete ptr;
}

string Operation::metaClassName() {
return "Operation";
}
void Operation::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
}else {

if(___refName.compare("parameters")==0){
if(___mutatorType ==ADD){
addparameters((Parameter*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removeparameters((Parameter*)AnyCast<Parameter*>(___value));
}
} else if(___refName.compare("returnType")==0){
if(___mutatorType ==ADD){
addreturnType((TypedElement*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removereturnType((TypedElement*)AnyCast<TypedElement*>(___value));
}
}

}

}

KMFContainer* Operation::findByID(string relationName,string idP){
if(relationName.compare("parameters")== 0){
return (KMFContainer*)findparametersByID(idP);
}

if(relationName.compare("returnType")== 0){
return returnType;
}

return NULL;

}





void Operation::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        



visitor->beginVisitRef("parameters","org.kevoree.Parameter");
for ( std::map<string,Parameter*>::iterator it = parameters.begin();  it != parameters.end(); ++it)
{
    Parameter * current =(Parameter*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"parameters");
}
visitor->endVisitRef("parameters");
    }
    if(nonContainedReference)
    {
        visitor->beginVisitRef("returnType","org.kevoree.TypedElement");
internal_visit(visitor,returnType,recursive,containedReference,nonContainedReference,"returnType");
visitor->endVisitRef("returnType");

    }
    visitor->endVisitElem(this);
}


void Operation::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
}
Operation::Operation(){

returnType=NULL;

}

Operation::~Operation(){






for ( std::map<string,Parameter*>::iterator it = parameters.begin();  it != parameters.end(); ++it)
{
Parameter * current = it->second;
if(current != NULL)
{
    delete current;
}

}

parameters.clear();


}

std::string Parameter::internalGetKey(){
return name;
}
void Parameter::addtype(TypedElement *ptr){
type =ptr;

}

void Parameter::removetype(TypedElement *ptr){
delete ptr;
}

string Parameter::metaClassName() {
return "Parameter";
}
void Parameter::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("order")==0){
int f;
Utils::from_string<int>(f, AnyCast<string>(___value), std::dec);
order= f;
}else {

if(___refName.compare("type")==0){
if(___mutatorType ==ADD){
addtype((TypedElement*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removetype((TypedElement*)AnyCast<TypedElement*>(___value));
}
}

}

}

KMFContainer* Parameter::findByID(string relationName,string idP){
if(relationName.compare("type")== 0){
return type;
}

return NULL;

}





void Parameter::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        
    }
    if(nonContainedReference)
    {
        visitor->beginVisitRef("type","org.kevoree.TypedElement");
internal_visit(visitor,type,recursive,containedReference,nonContainedReference,"type");
visitor->endVisitRef("type");

    }
    visitor->endVisitElem(this);
}


void Parameter::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(order),"order",this);
}
Parameter::Parameter(){

type=NULL;

}

Parameter::~Parameter(){



}

std::string TypedElement::internalGetKey(){
return name;
}
TypedElement* TypedElement::findgenericTypesByID(std::string id){
return genericTypes[id];
}




void TypedElement::addgenericTypes(TypedElement *ptr)
{
    TypedElement  *container = (TypedElement *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The TypedElement cannot be added in TypedElement because the key is not defined");
    }else
    {
        if(genericTypes.find(container->internalGetKey()) == genericTypes.end())
        {
            genericTypes[container->internalGetKey()]=ptr;
            
        }
    }
}






void TypedElement::removegenericTypes(TypedElement *ptr)
{
    TypedElement *container = (TypedElement*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The TypedElement cannot be removed in TypedElement because the key is not defined");
    }
    else
    {
        genericTypes.erase( genericTypes.find(container->internalGetKey()));
        
        container->setEContainer(NULL,NULL,"");
    }
}


string TypedElement::metaClassName() {
return "TypedElement";
}
void TypedElement::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
}else {

if(___refName.compare("genericTypes")==0){
if(___mutatorType ==ADD){
addgenericTypes((TypedElement*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removegenericTypes((TypedElement*)AnyCast<TypedElement*>(___value));
}
}

}

}

KMFContainer* TypedElement::findByID(string relationName,string idP){
if(relationName.compare("genericTypes")== 0){
return (KMFContainer*)findgenericTypesByID(idP);
}

return NULL;

}





void TypedElement::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        
    }
    if(nonContainedReference)
    {
        



visitor->beginVisitRef("genericTypes","org.kevoree.TypedElement");
for ( std::map<string,TypedElement*>::iterator it = genericTypes.begin();  it != genericTypes.end(); ++it)
{
    TypedElement * current =(TypedElement*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"genericTypes");
}
visitor->endVisitRef("genericTypes");
    }
    visitor->endVisitElem(this);
}


void TypedElement::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
}
TypedElement::TypedElement(){


}

TypedElement::~TypedElement(){

genericTypes.clear();


}

std::string MessagePortType::internalGetKey(){
return name+"/"+version;
}
TypedElement* MessagePortType::findfiltersByID(std::string id){
return filters[id];
}




void MessagePortType::addfilters(TypedElement *ptr)
{
    TypedElement  *container = (TypedElement *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The TypedElement cannot be added in MessagePortType because the key is not defined");
    }else
    {
        if(filters.find(container->internalGetKey()) == filters.end())
        {
            filters[container->internalGetKey()]=ptr;
            
        }
    }
}






void MessagePortType::removefilters(TypedElement *ptr)
{
    TypedElement *container = (TypedElement*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The TypedElement cannot be removed in MessagePortType because the key is not defined");
    }
    else
    {
        filters.erase( filters.find(container->internalGetKey()));
        
        container->setEContainer(NULL,NULL,"");
    }
}


string MessagePortType::metaClassName() {
return "MessagePortType";
}
void MessagePortType::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("version")==0){
version= AnyCast<string>(___value);
} else if(___refName.compare("factoryBean")==0){
factoryBean= AnyCast<string>(___value);
} else if(___refName.compare("bean")==0){
bean= AnyCast<string>(___value);
} else if(___refName.compare("abstract")==0){
if(AnyCast<string>(___value).compare("true") == 0){
abstract= true;
}else { 
abstract= false;
}
} else if(___refName.compare("synchrone")==0){
if(AnyCast<string>(___value).compare("true") == 0){
synchrone= true;
}else { 
synchrone= false;
}
}else {

if(___refName.compare("deployUnit")==0){
if(___mutatorType ==ADD){
adddeployUnit((DeployUnit*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedeployUnit((DeployUnit*)AnyCast<DeployUnit*>(___value));
}
} else if(___refName.compare("dictionaryType")==0){
if(___mutatorType ==ADD){
adddictionaryType((DictionaryType*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedictionaryType((DictionaryType*)AnyCast<DictionaryType*>(___value));
}
} else if(___refName.compare("superTypes")==0){
if(___mutatorType ==ADD){
addsuperTypes((TypeDefinition*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removesuperTypes((TypeDefinition*)AnyCast<TypeDefinition*>(___value));
}
} else if(___refName.compare("filters")==0){
if(___mutatorType ==ADD){
addfilters((TypedElement*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removefilters((TypedElement*)AnyCast<TypedElement*>(___value));
}
}

}

}

KMFContainer* MessagePortType::findByID(string relationName,string idP){
if(relationName.compare("deployUnit")== 0){
return (KMFContainer*)finddeployUnitByID(idP);
}

if(relationName.compare("dictionaryType")== 0){
return dictionaryType;
}

if(relationName.compare("superTypes")== 0){
return (KMFContainer*)findsuperTypesByID(idP);
}

if(relationName.compare("filters")== 0){
return (KMFContainer*)findfiltersByID(idP);
}

return NULL;

}





void MessagePortType::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        visitor->beginVisitRef("dictionaryType","org.kevoree.DictionaryType");
internal_visit(visitor,dictionaryType,recursive,containedReference,nonContainedReference,"dictionaryType");
visitor->endVisitRef("dictionaryType");

    }
    if(nonContainedReference)
    {
        



visitor->beginVisitRef("deployUnit","org.kevoree.DeployUnit");
for ( std::map<string,DeployUnit*>::iterator it = deployUnit.begin();  it != deployUnit.end(); ++it)
{
    DeployUnit * current =(DeployUnit*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"deployUnit");
}
visitor->endVisitRef("deployUnit");



visitor->beginVisitRef("superTypes","org.kevoree.TypeDefinition");
for ( std::map<string,TypeDefinition*>::iterator it = superTypes.begin();  it != superTypes.end(); ++it)
{
    TypeDefinition * current =(TypeDefinition*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"superTypes");
}
visitor->endVisitRef("superTypes");



visitor->beginVisitRef("filters","org.kevoree.TypedElement");
for ( std::map<string,TypedElement*>::iterator it = filters.begin();  it != filters.end(); ++it)
{
    TypedElement * current =(TypedElement*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"filters");
}
visitor->endVisitRef("filters");
    }
    visitor->endVisitElem(this);
}


void MessagePortType::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(version),"version",this);
visitor->visit(any(factoryBean),"factoryBean",this);
visitor->visit(any(bean),"bean",this);
visitor->visit(any(abstract),"abstract",this);
visitor->visit(any(synchrone),"synchrone",this);
}
MessagePortType::MessagePortType(){


}

MessagePortType::~MessagePortType(){

deployUnit.clear();
superTypes.clear();
filters.clear();
if(dictionaryType != NULL){
delete dictionaryType;
dictionaryType= NULL;}


}

std::string Repository::internalGetKey(){
return url;
}
string Repository::metaClassName() {
return "Repository";
}
void Repository::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("url")==0){
url= AnyCast<string>(___value);
}else {

}

}





void Repository::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        
    }
    if(nonContainedReference)
    {
        
    }
    visitor->endVisitElem(this);
}


void Repository::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(url),"url",this);
}
Repository::Repository(){


}

Repository::~Repository(){



}

std::string DeployUnit::internalGetKey(){
return groupName+"/"+hashcode+"/"+name+"/"+version;
}
DeployUnit* DeployUnit::findrequiredLibsByID(std::string id){
return requiredLibs[id];
}




void DeployUnit::addrequiredLibs(DeployUnit *ptr)
{
    DeployUnit  *container = (DeployUnit *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The DeployUnit cannot be added in DeployUnit because the key is not defined");
    }else
    {
        if(requiredLibs.find(container->internalGetKey()) == requiredLibs.end())
        {
            requiredLibs[container->internalGetKey()]=ptr;
            
        }
    }
}






void DeployUnit::removerequiredLibs(DeployUnit *ptr)
{
    DeployUnit *container = (DeployUnit*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The DeployUnit cannot be removed in DeployUnit because the key is not defined");
    }
    else
    {
        requiredLibs.erase( requiredLibs.find(container->internalGetKey()));
        
        container->setEContainer(NULL,NULL,"");
    }
}


string DeployUnit::metaClassName() {
return "DeployUnit";
}
void DeployUnit::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("groupName")==0){
groupName= AnyCast<string>(___value);
} else if(___refName.compare("version")==0){
version= AnyCast<string>(___value);
} else if(___refName.compare("url")==0){
url= AnyCast<string>(___value);
} else if(___refName.compare("hashcode")==0){
hashcode= AnyCast<string>(___value);
} else if(___refName.compare("type")==0){
type= AnyCast<string>(___value);
}else {

if(___refName.compare("requiredLibs")==0){
if(___mutatorType ==ADD){
addrequiredLibs((DeployUnit*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removerequiredLibs((DeployUnit*)AnyCast<DeployUnit*>(___value));
}
}

}

}

KMFContainer* DeployUnit::findByID(string relationName,string idP){
if(relationName.compare("requiredLibs")== 0){
return (KMFContainer*)findrequiredLibsByID(idP);
}

return NULL;

}





void DeployUnit::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        
    }
    if(nonContainedReference)
    {
        



visitor->beginVisitRef("requiredLibs","org.kevoree.DeployUnit");
for ( std::map<string,DeployUnit*>::iterator it = requiredLibs.begin();  it != requiredLibs.end(); ++it)
{
    DeployUnit * current =(DeployUnit*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"requiredLibs");
}
visitor->endVisitRef("requiredLibs");
    }
    visitor->endVisitElem(this);
}


void DeployUnit::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(groupName),"groupName",this);
visitor->visit(any(version),"version",this);
visitor->visit(any(url),"url",this);
visitor->visit(any(hashcode),"hashcode",this);
visitor->visit(any(type),"type",this);
}
DeployUnit::DeployUnit(){


}

DeployUnit::~DeployUnit(){

requiredLibs.clear();


}

std::string TypeLibrary::internalGetKey(){
return name;
}
TypeDefinition* TypeLibrary::findsubTypesByID(std::string id){
return subTypes[id];
}




void TypeLibrary::addsubTypes(TypeDefinition *ptr)
{
    TypeDefinition  *container = (TypeDefinition *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The TypeDefinition cannot be added in TypeLibrary because the key is not defined");
    }else
    {
        if(subTypes.find(container->internalGetKey()) == subTypes.end())
        {
            subTypes[container->internalGetKey()]=ptr;
            
        }
    }
}






void TypeLibrary::removesubTypes(TypeDefinition *ptr)
{
    TypeDefinition *container = (TypeDefinition*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The TypeDefinition cannot be removed in TypeLibrary because the key is not defined");
    }
    else
    {
        subTypes.erase( subTypes.find(container->internalGetKey()));
        
        container->setEContainer(NULL,NULL,"");
    }
}


string TypeLibrary::metaClassName() {
return "TypeLibrary";
}
void TypeLibrary::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
}else {

if(___refName.compare("subTypes")==0){
if(___mutatorType ==ADD){
addsubTypes((TypeDefinition*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removesubTypes((TypeDefinition*)AnyCast<TypeDefinition*>(___value));
}
}

}

}

KMFContainer* TypeLibrary::findByID(string relationName,string idP){
if(relationName.compare("subTypes")== 0){
return (KMFContainer*)findsubTypesByID(idP);
}

return NULL;

}





void TypeLibrary::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        
    }
    if(nonContainedReference)
    {
        



visitor->beginVisitRef("subTypes","org.kevoree.TypeDefinition");
for ( std::map<string,TypeDefinition*>::iterator it = subTypes.begin();  it != subTypes.end(); ++it)
{
    TypeDefinition * current =(TypeDefinition*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"subTypes");
}
visitor->endVisitRef("subTypes");
    }
    visitor->endVisitElem(this);
}


void TypeLibrary::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
}
TypeLibrary::TypeLibrary(){


}

TypeLibrary::~TypeLibrary(){

subTypes.clear();


}

std::string NamedElement::internalGetKey(){
return name;
}
string NamedElement::metaClassName() {
return "NamedElement";
}
void NamedElement::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
}else {

}

}





void NamedElement::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        
    }
    if(nonContainedReference)
    {
        
    }
    visitor->endVisitElem(this);
}


void NamedElement::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
}
NamedElement::NamedElement(){


}

NamedElement::~NamedElement(){



}

std::string PortTypeMapping::internalGetKey(){
return generated_KMF_ID;
}
string PortTypeMapping::metaClassName() {
return "PortTypeMapping";
}
void PortTypeMapping::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("beanMethodName")==0){
beanMethodName= AnyCast<string>(___value);
} else if(___refName.compare("serviceMethodName")==0){
serviceMethodName= AnyCast<string>(___value);
} else if(___refName.compare("paramTypes")==0){
paramTypes= AnyCast<string>(___value);
} else if(___refName.compare("generated_KMF_ID")==0){
generated_KMF_ID= AnyCast<string>(___value);
}else {

}

}





void PortTypeMapping::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        
    }
    if(nonContainedReference)
    {
        
    }
    visitor->endVisitElem(this);
}


void PortTypeMapping::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(beanMethodName),"beanMethodName",this);
visitor->visit(any(serviceMethodName),"serviceMethodName",this);
visitor->visit(any(paramTypes),"paramTypes",this);
visitor->visit(any(generated_KMF_ID),"generated_KMF_ID",this);
}
PortTypeMapping::PortTypeMapping(){

generated_KMF_ID= Uuid::getSingleton().generateUUID();

}

PortTypeMapping::~PortTypeMapping(){



}

std::string Channel::internalGetKey(){
return name;
}
MBinding* Channel::findbindingsByID(std::string id){
return bindings[id];
}




void Channel::addbindings(MBinding *ptr)
{
    MBinding  *container = (MBinding *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The MBinding cannot be added in Channel because the key is not defined");
    }else
    {
        if(bindings.find(container->internalGetKey()) == bindings.end())
        {
            bindings[container->internalGetKey()]=ptr;
            
        }
    }
}






void Channel::removebindings(MBinding *ptr)
{
    MBinding *container = (MBinding*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The MBinding cannot be removed in Channel because the key is not defined");
    }
    else
    {
        bindings.erase( bindings.find(container->internalGetKey()));
        
        container->setEContainer(NULL,NULL,"");
    }
}


string Channel::metaClassName() {
return "Channel";
}
void Channel::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("metaData")==0){
metaData= AnyCast<string>(___value);
} else if(___refName.compare("started")==0){
if(AnyCast<string>(___value).compare("true") == 0){
started= true;
}else { 
started= false;
}
}else {

if(___refName.compare("typeDefinition")==0){
if(___mutatorType ==ADD){
addtypeDefinition((TypeDefinition*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removetypeDefinition((TypeDefinition*)AnyCast<TypeDefinition*>(___value));
}
} else if(___refName.compare("dictionary")==0){
if(___mutatorType ==ADD){
adddictionary((Dictionary*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedictionary((Dictionary*)AnyCast<Dictionary*>(___value));
}
} else if(___refName.compare("fragmentDictionary")==0){
if(___mutatorType ==ADD){
addfragmentDictionary((FragmentDictionary*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removefragmentDictionary((FragmentDictionary*)AnyCast<FragmentDictionary*>(___value));
}
} else if(___refName.compare("bindings")==0){
if(___mutatorType ==ADD){
addbindings((MBinding*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removebindings((MBinding*)AnyCast<MBinding*>(___value));
}
}

}

}

KMFContainer* Channel::findByID(string relationName,string idP){
if(relationName.compare("typeDefinition")== 0){
return typeDefinition;
}

if(relationName.compare("dictionary")== 0){
return dictionary;
}

if(relationName.compare("fragmentDictionary")== 0){
return (KMFContainer*)findfragmentDictionaryByID(idP);
}

if(relationName.compare("bindings")== 0){
return (KMFContainer*)findbindingsByID(idP);
}

return NULL;

}





void Channel::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        visitor->beginVisitRef("dictionary","org.kevoree.Dictionary");
internal_visit(visitor,dictionary,recursive,containedReference,nonContainedReference,"dictionary");
visitor->endVisitRef("dictionary");




visitor->beginVisitRef("fragmentDictionary","org.kevoree.FragmentDictionary");
for ( std::map<string,FragmentDictionary*>::iterator it = fragmentDictionary.begin();  it != fragmentDictionary.end(); ++it)
{
    FragmentDictionary * current =(FragmentDictionary*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"fragmentDictionary");
}
visitor->endVisitRef("fragmentDictionary");
    }
    if(nonContainedReference)
    {
        visitor->beginVisitRef("typeDefinition","org.kevoree.TypeDefinition");
internal_visit(visitor,typeDefinition,recursive,containedReference,nonContainedReference,"typeDefinition");
visitor->endVisitRef("typeDefinition");




visitor->beginVisitRef("bindings","org.kevoree.MBinding");
for ( std::map<string,MBinding*>::iterator it = bindings.begin();  it != bindings.end(); ++it)
{
    MBinding * current =(MBinding*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"bindings");
}
visitor->endVisitRef("bindings");
    }
    visitor->endVisitElem(this);
}


void Channel::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(metaData),"metaData",this);
visitor->visit(any(started),"started",this);
}
Channel::Channel(){


}

Channel::~Channel(){

bindings.clear();
if(dictionary != NULL){
delete dictionary;
dictionary= NULL;}





for ( std::map<string,FragmentDictionary*>::iterator it = fragmentDictionary.begin();  it != fragmentDictionary.end(); ++it)
{
FragmentDictionary * current = it->second;
if(current != NULL)
{
    delete current;
}

}

fragmentDictionary.clear();


}

std::string MBinding::internalGetKey(){
return generated_KMF_ID;
}
void MBinding::addport(Port *ptr){
port =ptr;

}

void MBinding::addhub(Channel *ptr){
hub =ptr;

}

void MBinding::removeport(Port *ptr){
delete ptr;
}

void MBinding::removehub(Channel *ptr){
delete ptr;
}

string MBinding::metaClassName() {
return "MBinding";
}
void MBinding::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("generated_KMF_ID")==0){
generated_KMF_ID= AnyCast<string>(___value);
}else {

if(___refName.compare("port")==0){
if(___mutatorType ==ADD){
addport((Port*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removeport((Port*)AnyCast<Port*>(___value));
}
} else if(___refName.compare("hub")==0){
if(___mutatorType ==ADD){
addhub((Channel*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removehub((Channel*)AnyCast<Channel*>(___value));
}
}

}

}

KMFContainer* MBinding::findByID(string relationName,string idP){
if(relationName.compare("port")== 0){
return port;
}

if(relationName.compare("hub")== 0){
return hub;
}

return NULL;

}





void MBinding::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        
    }
    if(nonContainedReference)
    {
        visitor->beginVisitRef("port","org.kevoree.Port");
internal_visit(visitor,port,recursive,containedReference,nonContainedReference,"port");
visitor->endVisitRef("port");
visitor->beginVisitRef("hub","org.kevoree.Channel");
internal_visit(visitor,hub,recursive,containedReference,nonContainedReference,"hub");
visitor->endVisitRef("hub");

    }
    visitor->endVisitElem(this);
}


void MBinding::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(generated_KMF_ID),"generated_KMF_ID",this);
}
MBinding::MBinding(){

generated_KMF_ID= Uuid::getSingleton().generateUUID();
port=NULL;
hub=NULL;

}

MBinding::~MBinding(){



}

std::string NodeNetwork::internalGetKey(){
return generated_KMF_ID;
}
NodeLink* NodeNetwork::findlinkByID(std::string id){
return link[id];
}




void NodeNetwork::addlink(NodeLink *ptr)
{
    NodeLink  *container = (NodeLink *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The NodeLink cannot be added in NodeNetwork because the key is not defined");
    }else
    {
        if(link.find(container->internalGetKey()) == link.end())
        {
            link[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"link",ptr_any);
	container->setEContainer(this,cmd,"link");

        }
    }
}


void NodeNetwork::addinitBy(ContainerNode *ptr){
initBy =ptr;

}

void NodeNetwork::addtarget(ContainerNode *ptr){
target =ptr;

}





void NodeNetwork::removelink(NodeLink *ptr)
{
    NodeLink *container = (NodeLink*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The NodeLink cannot be removed in NodeNetwork because the key is not defined");
    }
    else
    {
        link.erase( link.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}


void NodeNetwork::removeinitBy(ContainerNode *ptr){
delete ptr;
}

void NodeNetwork::removetarget(ContainerNode *ptr){
delete ptr;
}

string NodeNetwork::metaClassName() {
return "NodeNetwork";
}
void NodeNetwork::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("generated_KMF_ID")==0){
generated_KMF_ID= AnyCast<string>(___value);
}else {

if(___refName.compare("link")==0){
if(___mutatorType ==ADD){
addlink((NodeLink*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removelink((NodeLink*)AnyCast<NodeLink*>(___value));
}
} else if(___refName.compare("initBy")==0){
if(___mutatorType ==ADD){
addinitBy((ContainerNode*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removeinitBy((ContainerNode*)AnyCast<ContainerNode*>(___value));
}
} else if(___refName.compare("target")==0){
if(___mutatorType ==ADD){
addtarget((ContainerNode*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removetarget((ContainerNode*)AnyCast<ContainerNode*>(___value));
}
}

}

}

KMFContainer* NodeNetwork::findByID(string relationName,string idP){
if(relationName.compare("link")== 0){
return (KMFContainer*)findlinkByID(idP);
}

if(relationName.compare("initBy")== 0){
return initBy;
}

if(relationName.compare("target")== 0){
return target;
}

return NULL;

}





void NodeNetwork::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        



visitor->beginVisitRef("link","org.kevoree.NodeLink");
for ( std::map<string,NodeLink*>::iterator it = link.begin();  it != link.end(); ++it)
{
    NodeLink * current =(NodeLink*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"link");
}
visitor->endVisitRef("link");
    }
    if(nonContainedReference)
    {
        visitor->beginVisitRef("initBy","org.kevoree.ContainerNode");
internal_visit(visitor,initBy,recursive,containedReference,nonContainedReference,"initBy");
visitor->endVisitRef("initBy");
visitor->beginVisitRef("target","org.kevoree.ContainerNode");
internal_visit(visitor,target,recursive,containedReference,nonContainedReference,"target");
visitor->endVisitRef("target");

    }
    visitor->endVisitElem(this);
}


void NodeNetwork::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(generated_KMF_ID),"generated_KMF_ID",this);
}
NodeNetwork::NodeNetwork(){

generated_KMF_ID= Uuid::getSingleton().generateUUID();
initBy=NULL;
target=NULL;

}

NodeNetwork::~NodeNetwork(){






for ( std::map<string,NodeLink*>::iterator it = link.begin();  it != link.end(); ++it)
{
NodeLink * current = it->second;
if(current != NULL)
{
    delete current;
}

}

link.clear();


}

std::string NodeLink::internalGetKey(){
return generated_KMF_ID;
}
NetworkProperty* NodeLink::findnetworkPropertiesByID(std::string id){
return networkProperties[id];
}




void NodeLink::addnetworkProperties(NetworkProperty *ptr)
{
    NetworkProperty  *container = (NetworkProperty *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The NetworkProperty cannot be added in NodeLink because the key is not defined");
    }else
    {
        if(networkProperties.find(container->internalGetKey()) == networkProperties.end())
        {
            networkProperties[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"networkProperties",ptr_any);
	container->setEContainer(this,cmd,"networkProperties");

        }
    }
}






void NodeLink::removenetworkProperties(NetworkProperty *ptr)
{
    NetworkProperty *container = (NetworkProperty*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The NetworkProperty cannot be removed in NodeLink because the key is not defined");
    }
    else
    {
        networkProperties.erase( networkProperties.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}


string NodeLink::metaClassName() {
return "NodeLink";
}
void NodeLink::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("networkType")==0){
networkType= AnyCast<string>(___value);
} else if(___refName.compare("estimatedRate")==0){
int f;
Utils::from_string<int>(f, AnyCast<string>(___value), std::dec);
estimatedRate= f;
} else if(___refName.compare("lastCheck")==0){
lastCheck= AnyCast<string>(___value);
} else if(___refName.compare("zoneID")==0){
zoneID= AnyCast<string>(___value);
} else if(___refName.compare("generated_KMF_ID")==0){
generated_KMF_ID= AnyCast<string>(___value);
}else {

if(___refName.compare("networkProperties")==0){
if(___mutatorType ==ADD){
addnetworkProperties((NetworkProperty*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removenetworkProperties((NetworkProperty*)AnyCast<NetworkProperty*>(___value));
}
}

}

}

KMFContainer* NodeLink::findByID(string relationName,string idP){
if(relationName.compare("networkProperties")== 0){
return (KMFContainer*)findnetworkPropertiesByID(idP);
}

return NULL;

}





void NodeLink::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        



visitor->beginVisitRef("networkProperties","org.kevoree.NetworkProperty");
for ( std::map<string,NetworkProperty*>::iterator it = networkProperties.begin();  it != networkProperties.end(); ++it)
{
    NetworkProperty * current =(NetworkProperty*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"networkProperties");
}
visitor->endVisitRef("networkProperties");
    }
    if(nonContainedReference)
    {
        
    }
    visitor->endVisitElem(this);
}


void NodeLink::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(networkType),"networkType",this);
visitor->visit(any(estimatedRate),"estimatedRate",this);
visitor->visit(any(lastCheck),"lastCheck",this);
visitor->visit(any(zoneID),"zoneID",this);
visitor->visit(any(generated_KMF_ID),"generated_KMF_ID",this);
}
NodeLink::NodeLink(){

generated_KMF_ID= Uuid::getSingleton().generateUUID();

}

NodeLink::~NodeLink(){






for ( std::map<string,NetworkProperty*>::iterator it = networkProperties.begin();  it != networkProperties.end(); ++it)
{
NetworkProperty * current = it->second;
if(current != NULL)
{
    delete current;
}

}

networkProperties.clear();


}

std::string NetworkInfo::internalGetKey(){
return name;
}
NetworkProperty* NetworkInfo::findvaluesByID(std::string id){
return values[id];
}




void NetworkInfo::addvalues(NetworkProperty *ptr)
{
    NetworkProperty  *container = (NetworkProperty *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The NetworkProperty cannot be added in NetworkInfo because the key is not defined");
    }else
    {
        if(values.find(container->internalGetKey()) == values.end())
        {
            values[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"values",ptr_any);
	container->setEContainer(this,cmd,"values");

        }
    }
}






void NetworkInfo::removevalues(NetworkProperty *ptr)
{
    NetworkProperty *container = (NetworkProperty*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The NetworkProperty cannot be removed in NetworkInfo because the key is not defined");
    }
    else
    {
        values.erase( values.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}


string NetworkInfo::metaClassName() {
return "NetworkInfo";
}
void NetworkInfo::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
}else {

if(___refName.compare("values")==0){
if(___mutatorType ==ADD){
addvalues((NetworkProperty*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removevalues((NetworkProperty*)AnyCast<NetworkProperty*>(___value));
}
}

}

}

KMFContainer* NetworkInfo::findByID(string relationName,string idP){
if(relationName.compare("values")== 0){
return (KMFContainer*)findvaluesByID(idP);
}

return NULL;

}





void NetworkInfo::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        



visitor->beginVisitRef("values","org.kevoree.NetworkProperty");
for ( std::map<string,NetworkProperty*>::iterator it = values.begin();  it != values.end(); ++it)
{
    NetworkProperty * current =(NetworkProperty*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"values");
}
visitor->endVisitRef("values");
    }
    if(nonContainedReference)
    {
        
    }
    visitor->endVisitElem(this);
}


void NetworkInfo::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
}
NetworkInfo::NetworkInfo(){


}

NetworkInfo::~NetworkInfo(){






for ( std::map<string,NetworkProperty*>::iterator it = values.begin();  it != values.end(); ++it)
{
NetworkProperty * current = it->second;
if(current != NULL)
{
    delete current;
}

}

values.clear();


}

std::string NetworkProperty::internalGetKey(){
return name+"/"+name;
}
string NetworkProperty::metaClassName() {
return "NetworkProperty";
}
void NetworkProperty::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("value")==0){
value= AnyCast<string>(___value);
}else {

}

}





void NetworkProperty::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        
    }
    if(nonContainedReference)
    {
        
    }
    visitor->endVisitElem(this);
}


void NetworkProperty::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(name),"name",this);
visitor->visit(any(value),"value",this);
}
NetworkProperty::NetworkProperty(){


}

NetworkProperty::~NetworkProperty(){



}

std::string ChannelType::internalGetKey(){
return name+"/"+version;
}
string ChannelType::metaClassName() {
return "ChannelType";
}
void ChannelType::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("version")==0){
version= AnyCast<string>(___value);
} else if(___refName.compare("factoryBean")==0){
factoryBean= AnyCast<string>(___value);
} else if(___refName.compare("bean")==0){
bean= AnyCast<string>(___value);
} else if(___refName.compare("abstract")==0){
if(AnyCast<string>(___value).compare("true") == 0){
abstract= true;
}else { 
abstract= false;
}
} else if(___refName.compare("lowerBindings")==0){
int f;
Utils::from_string<int>(f, AnyCast<string>(___value), std::dec);
lowerBindings= f;
} else if(___refName.compare("upperBindings")==0){
int f;
Utils::from_string<int>(f, AnyCast<string>(___value), std::dec);
upperBindings= f;
} else if(___refName.compare("lowerFragments")==0){
int f;
Utils::from_string<int>(f, AnyCast<string>(___value), std::dec);
lowerFragments= f;
} else if(___refName.compare("upperFragments")==0){
int f;
Utils::from_string<int>(f, AnyCast<string>(___value), std::dec);
upperFragments= f;
}else {

if(___refName.compare("deployUnit")==0){
if(___mutatorType ==ADD){
adddeployUnit((DeployUnit*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedeployUnit((DeployUnit*)AnyCast<DeployUnit*>(___value));
}
} else if(___refName.compare("dictionaryType")==0){
if(___mutatorType ==ADD){
adddictionaryType((DictionaryType*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedictionaryType((DictionaryType*)AnyCast<DictionaryType*>(___value));
}
} else if(___refName.compare("superTypes")==0){
if(___mutatorType ==ADD){
addsuperTypes((TypeDefinition*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removesuperTypes((TypeDefinition*)AnyCast<TypeDefinition*>(___value));
}
}

}

}

KMFContainer* ChannelType::findByID(string relationName,string idP){
if(relationName.compare("deployUnit")== 0){
return (KMFContainer*)finddeployUnitByID(idP);
}

if(relationName.compare("dictionaryType")== 0){
return dictionaryType;
}

if(relationName.compare("superTypes")== 0){
return (KMFContainer*)findsuperTypesByID(idP);
}

return NULL;

}





void ChannelType::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        visitor->beginVisitRef("dictionaryType","org.kevoree.DictionaryType");
internal_visit(visitor,dictionaryType,recursive,containedReference,nonContainedReference,"dictionaryType");
visitor->endVisitRef("dictionaryType");

    }
    if(nonContainedReference)
    {
        



visitor->beginVisitRef("deployUnit","org.kevoree.DeployUnit");
for ( std::map<string,DeployUnit*>::iterator it = deployUnit.begin();  it != deployUnit.end(); ++it)
{
    DeployUnit * current =(DeployUnit*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"deployUnit");
}
visitor->endVisitRef("deployUnit");



visitor->beginVisitRef("superTypes","org.kevoree.TypeDefinition");
for ( std::map<string,TypeDefinition*>::iterator it = superTypes.begin();  it != superTypes.end(); ++it)
{
    TypeDefinition * current =(TypeDefinition*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"superTypes");
}
visitor->endVisitRef("superTypes");
    }
    visitor->endVisitElem(this);
}


void ChannelType::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(version),"version",this);
visitor->visit(any(factoryBean),"factoryBean",this);
visitor->visit(any(bean),"bean",this);
visitor->visit(any(abstract),"abstract",this);
visitor->visit(any(lowerBindings),"lowerBindings",this);
visitor->visit(any(upperBindings),"upperBindings",this);
visitor->visit(any(lowerFragments),"lowerFragments",this);
visitor->visit(any(upperFragments),"upperFragments",this);
}
ChannelType::ChannelType(){


}

ChannelType::~ChannelType(){

deployUnit.clear();
superTypes.clear();
if(dictionaryType != NULL){
delete dictionaryType;
dictionaryType= NULL;}


}

std::string TypeDefinition::internalGetKey(){
return name+"/"+version;
}
DeployUnit* TypeDefinition::finddeployUnitByID(std::string id){
return deployUnit[id];
}
TypeDefinition* TypeDefinition::findsuperTypesByID(std::string id){
return superTypes[id];
}




void TypeDefinition::adddeployUnit(DeployUnit *ptr)
{
    DeployUnit  *container = (DeployUnit *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The DeployUnit cannot be added in TypeDefinition because the key is not defined");
    }else
    {
        if(deployUnit.find(container->internalGetKey()) == deployUnit.end())
        {
            deployUnit[container->internalGetKey()]=ptr;
            
        }
    }
}


void TypeDefinition::adddictionaryType(DictionaryType *ptr){
if(dictionaryType != ptr ){
if(dictionaryType != NULL ){
dictionaryType->setEContainer(NULL,NULL,"");
}
if(ptr != NULL ){
ptr->setEContainer(this,NULL,"dictionaryType");
}
dictionaryType =ptr;
}

}





void TypeDefinition::addsuperTypes(TypeDefinition *ptr)
{
    TypeDefinition  *container = (TypeDefinition *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The TypeDefinition cannot be added in TypeDefinition because the key is not defined");
    }else
    {
        if(superTypes.find(container->internalGetKey()) == superTypes.end())
        {
            superTypes[container->internalGetKey()]=ptr;
            
        }
    }
}






void TypeDefinition::removedeployUnit(DeployUnit *ptr)
{
    DeployUnit *container = (DeployUnit*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The DeployUnit cannot be removed in TypeDefinition because the key is not defined");
    }
    else
    {
        deployUnit.erase( deployUnit.find(container->internalGetKey()));
        
        container->setEContainer(NULL,NULL,"");
    }
}


void TypeDefinition::removedictionaryType(DictionaryType *ptr){
delete ptr;
}





void TypeDefinition::removesuperTypes(TypeDefinition *ptr)
{
    TypeDefinition *container = (TypeDefinition*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The TypeDefinition cannot be removed in TypeDefinition because the key is not defined");
    }
    else
    {
        superTypes.erase( superTypes.find(container->internalGetKey()));
        
        container->setEContainer(NULL,NULL,"");
    }
}


string TypeDefinition::metaClassName() {
return "TypeDefinition";
}
void TypeDefinition::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("version")==0){
version= AnyCast<string>(___value);
} else if(___refName.compare("factoryBean")==0){
factoryBean= AnyCast<string>(___value);
} else if(___refName.compare("bean")==0){
bean= AnyCast<string>(___value);
} else if(___refName.compare("abstract")==0){
if(AnyCast<string>(___value).compare("true") == 0){
abstract= true;
}else { 
abstract= false;
}
}else {

if(___refName.compare("deployUnit")==0){
if(___mutatorType ==ADD){
adddeployUnit((DeployUnit*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedeployUnit((DeployUnit*)AnyCast<DeployUnit*>(___value));
}
} else if(___refName.compare("dictionaryType")==0){
if(___mutatorType ==ADD){
adddictionaryType((DictionaryType*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedictionaryType((DictionaryType*)AnyCast<DictionaryType*>(___value));
}
} else if(___refName.compare("superTypes")==0){
if(___mutatorType ==ADD){
addsuperTypes((TypeDefinition*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removesuperTypes((TypeDefinition*)AnyCast<TypeDefinition*>(___value));
}
}

}

}

KMFContainer* TypeDefinition::findByID(string relationName,string idP){
if(relationName.compare("deployUnit")== 0){
return (KMFContainer*)finddeployUnitByID(idP);
}

if(relationName.compare("dictionaryType")== 0){
return dictionaryType;
}

if(relationName.compare("superTypes")== 0){
return (KMFContainer*)findsuperTypesByID(idP);
}

return NULL;

}





void TypeDefinition::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        visitor->beginVisitRef("dictionaryType","org.kevoree.DictionaryType");
internal_visit(visitor,dictionaryType,recursive,containedReference,nonContainedReference,"dictionaryType");
visitor->endVisitRef("dictionaryType");

    }
    if(nonContainedReference)
    {
        



visitor->beginVisitRef("deployUnit","org.kevoree.DeployUnit");
for ( std::map<string,DeployUnit*>::iterator it = deployUnit.begin();  it != deployUnit.end(); ++it)
{
    DeployUnit * current =(DeployUnit*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"deployUnit");
}
visitor->endVisitRef("deployUnit");



visitor->beginVisitRef("superTypes","org.kevoree.TypeDefinition");
for ( std::map<string,TypeDefinition*>::iterator it = superTypes.begin();  it != superTypes.end(); ++it)
{
    TypeDefinition * current =(TypeDefinition*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"superTypes");
}
visitor->endVisitRef("superTypes");
    }
    visitor->endVisitElem(this);
}


void TypeDefinition::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(version),"version",this);
visitor->visit(any(factoryBean),"factoryBean",this);
visitor->visit(any(bean),"bean",this);
visitor->visit(any(abstract),"abstract",this);
}
TypeDefinition::TypeDefinition(){

dictionaryType=NULL;

}

TypeDefinition::~TypeDefinition(){

deployUnit.clear();
superTypes.clear();
if(dictionaryType != NULL){
delete dictionaryType;
dictionaryType= NULL;}


}

std::string Instance::internalGetKey(){
return name;
}
FragmentDictionary* Instance::findfragmentDictionaryByID(std::string id){
return fragmentDictionary[id];
}
void Instance::addtypeDefinition(TypeDefinition *ptr){
typeDefinition =ptr;

}

void Instance::adddictionary(Dictionary *ptr){
if(dictionary != ptr ){
if(dictionary != NULL ){
dictionary->setEContainer(NULL,NULL,"");
}
if(ptr != NULL ){
ptr->setEContainer(this,NULL,"dictionary");
}
dictionary =ptr;
}

}





void Instance::addfragmentDictionary(FragmentDictionary *ptr)
{
    FragmentDictionary  *container = (FragmentDictionary *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The FragmentDictionary cannot be added in Instance because the key is not defined");
    }else
    {
        if(fragmentDictionary.find(container->internalGetKey()) == fragmentDictionary.end())
        {
            fragmentDictionary[container->internalGetKey()]=ptr;
            	any ptr_any = container;
	RemoveFromContainerCommand  *cmd = new  RemoveFromContainerCommand(this,REMOVE,"fragmentDictionary",ptr_any);
	container->setEContainer(this,cmd,"fragmentDictionary");

        }
    }
}


void Instance::removetypeDefinition(TypeDefinition *ptr){
delete ptr;
}

void Instance::removedictionary(Dictionary *ptr){
delete ptr;
}





void Instance::removefragmentDictionary(FragmentDictionary *ptr)
{
    FragmentDictionary *container = (FragmentDictionary*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The FragmentDictionary cannot be removed in Instance because the key is not defined");
    }
    else
    {
        fragmentDictionary.erase( fragmentDictionary.find(container->internalGetKey()));
        delete container;
        container->setEContainer(NULL,NULL,"");
    }
}


string Instance::metaClassName() {
return "Instance";
}
void Instance::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("metaData")==0){
metaData= AnyCast<string>(___value);
} else if(___refName.compare("started")==0){
if(AnyCast<string>(___value).compare("true") == 0){
started= true;
}else { 
started= false;
}
}else {

if(___refName.compare("typeDefinition")==0){
if(___mutatorType ==ADD){
addtypeDefinition((TypeDefinition*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removetypeDefinition((TypeDefinition*)AnyCast<TypeDefinition*>(___value));
}
} else if(___refName.compare("dictionary")==0){
if(___mutatorType ==ADD){
adddictionary((Dictionary*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedictionary((Dictionary*)AnyCast<Dictionary*>(___value));
}
} else if(___refName.compare("fragmentDictionary")==0){
if(___mutatorType ==ADD){
addfragmentDictionary((FragmentDictionary*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removefragmentDictionary((FragmentDictionary*)AnyCast<FragmentDictionary*>(___value));
}
}

}

}

KMFContainer* Instance::findByID(string relationName,string idP){
if(relationName.compare("typeDefinition")== 0){
return typeDefinition;
}

if(relationName.compare("dictionary")== 0){
return dictionary;
}

if(relationName.compare("fragmentDictionary")== 0){
return (KMFContainer*)findfragmentDictionaryByID(idP);
}

return NULL;

}





void Instance::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        visitor->beginVisitRef("dictionary","org.kevoree.Dictionary");
internal_visit(visitor,dictionary,recursive,containedReference,nonContainedReference,"dictionary");
visitor->endVisitRef("dictionary");




visitor->beginVisitRef("fragmentDictionary","org.kevoree.FragmentDictionary");
for ( std::map<string,FragmentDictionary*>::iterator it = fragmentDictionary.begin();  it != fragmentDictionary.end(); ++it)
{
    FragmentDictionary * current =(FragmentDictionary*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"fragmentDictionary");
}
visitor->endVisitRef("fragmentDictionary");
    }
    if(nonContainedReference)
    {
        visitor->beginVisitRef("typeDefinition","org.kevoree.TypeDefinition");
internal_visit(visitor,typeDefinition,recursive,containedReference,nonContainedReference,"typeDefinition");
visitor->endVisitRef("typeDefinition");

    }
    visitor->endVisitElem(this);
}


void Instance::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(metaData),"metaData",this);
visitor->visit(any(started),"started",this);
}
Instance::Instance(){

typeDefinition=NULL;
dictionary=NULL;

}

Instance::~Instance(){

if(dictionary != NULL){
delete dictionary;
dictionary= NULL;}





for ( std::map<string,FragmentDictionary*>::iterator it = fragmentDictionary.begin();  it != fragmentDictionary.end(); ++it)
{
FragmentDictionary * current = it->second;
if(current != NULL)
{
    delete current;
}

}

fragmentDictionary.clear();


}

std::string Group::internalGetKey(){
return name;
}
ContainerNode* Group::findsubNodesByID(std::string id){
return subNodes[id];
}




void Group::addsubNodes(ContainerNode *ptr)
{
    ContainerNode  *container = (ContainerNode *)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The ContainerNode cannot be added in Group because the key is not defined");
    }else
    {
        if(subNodes.find(container->internalGetKey()) == subNodes.end())
        {
            subNodes[container->internalGetKey()]=ptr;
            
        }
    }
}






void Group::removesubNodes(ContainerNode *ptr)
{
    ContainerNode *container = (ContainerNode*)ptr;
    if(container->internalGetKey().empty())
    {
        LOGGER_WRITE(Logger::WARNING,"The ContainerNode cannot be removed in Group because the key is not defined");
    }
    else
    {
        subNodes.erase( subNodes.find(container->internalGetKey()));
        
        container->setEContainer(NULL,NULL,"");
    }
}


string Group::metaClassName() {
return "Group";
}
void Group::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("metaData")==0){
metaData= AnyCast<string>(___value);
} else if(___refName.compare("started")==0){
if(AnyCast<string>(___value).compare("true") == 0){
started= true;
}else { 
started= false;
}
}else {

if(___refName.compare("typeDefinition")==0){
if(___mutatorType ==ADD){
addtypeDefinition((TypeDefinition*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removetypeDefinition((TypeDefinition*)AnyCast<TypeDefinition*>(___value));
}
} else if(___refName.compare("dictionary")==0){
if(___mutatorType ==ADD){
adddictionary((Dictionary*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedictionary((Dictionary*)AnyCast<Dictionary*>(___value));
}
} else if(___refName.compare("fragmentDictionary")==0){
if(___mutatorType ==ADD){
addfragmentDictionary((FragmentDictionary*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removefragmentDictionary((FragmentDictionary*)AnyCast<FragmentDictionary*>(___value));
}
} else if(___refName.compare("subNodes")==0){
if(___mutatorType ==ADD){
addsubNodes((ContainerNode*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removesubNodes((ContainerNode*)AnyCast<ContainerNode*>(___value));
}
}

}

}

KMFContainer* Group::findByID(string relationName,string idP){
if(relationName.compare("typeDefinition")== 0){
return typeDefinition;
}

if(relationName.compare("dictionary")== 0){
return dictionary;
}

if(relationName.compare("fragmentDictionary")== 0){
return (KMFContainer*)findfragmentDictionaryByID(idP);
}

if(relationName.compare("subNodes")== 0){
return (KMFContainer*)findsubNodesByID(idP);
}

return NULL;

}





void Group::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        visitor->beginVisitRef("dictionary","org.kevoree.Dictionary");
internal_visit(visitor,dictionary,recursive,containedReference,nonContainedReference,"dictionary");
visitor->endVisitRef("dictionary");




visitor->beginVisitRef("fragmentDictionary","org.kevoree.FragmentDictionary");
for ( std::map<string,FragmentDictionary*>::iterator it = fragmentDictionary.begin();  it != fragmentDictionary.end(); ++it)
{
    FragmentDictionary * current =(FragmentDictionary*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"fragmentDictionary");
}
visitor->endVisitRef("fragmentDictionary");
    }
    if(nonContainedReference)
    {
        visitor->beginVisitRef("typeDefinition","org.kevoree.TypeDefinition");
internal_visit(visitor,typeDefinition,recursive,containedReference,nonContainedReference,"typeDefinition");
visitor->endVisitRef("typeDefinition");




visitor->beginVisitRef("subNodes","org.kevoree.ContainerNode");
for ( std::map<string,ContainerNode*>::iterator it = subNodes.begin();  it != subNodes.end(); ++it)
{
    ContainerNode * current =(ContainerNode*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"subNodes");
}
visitor->endVisitRef("subNodes");
    }
    visitor->endVisitElem(this);
}


void Group::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(metaData),"metaData",this);
visitor->visit(any(started),"started",this);
}
Group::Group(){


}

Group::~Group(){

subNodes.clear();
if(dictionary != NULL){
delete dictionary;
dictionary= NULL;}





for ( std::map<string,FragmentDictionary*>::iterator it = fragmentDictionary.begin();  it != fragmentDictionary.end(); ++it)
{
FragmentDictionary * current = it->second;
if(current != NULL)
{
    delete current;
}

}

fragmentDictionary.clear();


}

std::string GroupType::internalGetKey(){
return name+"/"+version;
}
string GroupType::metaClassName() {
return "GroupType";
}
void GroupType::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("version")==0){
version= AnyCast<string>(___value);
} else if(___refName.compare("factoryBean")==0){
factoryBean= AnyCast<string>(___value);
} else if(___refName.compare("bean")==0){
bean= AnyCast<string>(___value);
} else if(___refName.compare("abstract")==0){
if(AnyCast<string>(___value).compare("true") == 0){
abstract= true;
}else { 
abstract= false;
}
}else {

if(___refName.compare("deployUnit")==0){
if(___mutatorType ==ADD){
adddeployUnit((DeployUnit*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedeployUnit((DeployUnit*)AnyCast<DeployUnit*>(___value));
}
} else if(___refName.compare("dictionaryType")==0){
if(___mutatorType ==ADD){
adddictionaryType((DictionaryType*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedictionaryType((DictionaryType*)AnyCast<DictionaryType*>(___value));
}
} else if(___refName.compare("superTypes")==0){
if(___mutatorType ==ADD){
addsuperTypes((TypeDefinition*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removesuperTypes((TypeDefinition*)AnyCast<TypeDefinition*>(___value));
}
}

}

}

KMFContainer* GroupType::findByID(string relationName,string idP){
if(relationName.compare("deployUnit")== 0){
return (KMFContainer*)finddeployUnitByID(idP);
}

if(relationName.compare("dictionaryType")== 0){
return dictionaryType;
}

if(relationName.compare("superTypes")== 0){
return (KMFContainer*)findsuperTypesByID(idP);
}

return NULL;

}





void GroupType::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        visitor->beginVisitRef("dictionaryType","org.kevoree.DictionaryType");
internal_visit(visitor,dictionaryType,recursive,containedReference,nonContainedReference,"dictionaryType");
visitor->endVisitRef("dictionaryType");

    }
    if(nonContainedReference)
    {
        



visitor->beginVisitRef("deployUnit","org.kevoree.DeployUnit");
for ( std::map<string,DeployUnit*>::iterator it = deployUnit.begin();  it != deployUnit.end(); ++it)
{
    DeployUnit * current =(DeployUnit*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"deployUnit");
}
visitor->endVisitRef("deployUnit");



visitor->beginVisitRef("superTypes","org.kevoree.TypeDefinition");
for ( std::map<string,TypeDefinition*>::iterator it = superTypes.begin();  it != superTypes.end(); ++it)
{
    TypeDefinition * current =(TypeDefinition*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"superTypes");
}
visitor->endVisitRef("superTypes");
    }
    visitor->endVisitElem(this);
}


void GroupType::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(version),"version",this);
visitor->visit(any(factoryBean),"factoryBean",this);
visitor->visit(any(bean),"bean",this);
visitor->visit(any(abstract),"abstract",this);
}
GroupType::GroupType(){


}

GroupType::~GroupType(){

deployUnit.clear();
superTypes.clear();
if(dictionaryType != NULL){
delete dictionaryType;
dictionaryType= NULL;}


}

std::string NodeType::internalGetKey(){
return name+"/"+version;
}
string NodeType::metaClassName() {
return "NodeType";
}
void NodeType::reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent){
if(___refName.compare("name")==0){
name= AnyCast<string>(___value);
} else if(___refName.compare("version")==0){
version= AnyCast<string>(___value);
} else if(___refName.compare("factoryBean")==0){
factoryBean= AnyCast<string>(___value);
} else if(___refName.compare("bean")==0){
bean= AnyCast<string>(___value);
} else if(___refName.compare("abstract")==0){
if(AnyCast<string>(___value).compare("true") == 0){
abstract= true;
}else { 
abstract= false;
}
}else {

if(___refName.compare("deployUnit")==0){
if(___mutatorType ==ADD){
adddeployUnit((DeployUnit*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedeployUnit((DeployUnit*)AnyCast<DeployUnit*>(___value));
}
} else if(___refName.compare("dictionaryType")==0){
if(___mutatorType ==ADD){
adddictionaryType((DictionaryType*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removedictionaryType((DictionaryType*)AnyCast<DictionaryType*>(___value));
}
} else if(___refName.compare("superTypes")==0){
if(___mutatorType ==ADD){
addsuperTypes((TypeDefinition*)AnyCast<KMFContainer*>(___value));
}else if(___mutatorType == REMOVE){
removesuperTypes((TypeDefinition*)AnyCast<TypeDefinition*>(___value));
}
}

}

}

KMFContainer* NodeType::findByID(string relationName,string idP){
if(relationName.compare("deployUnit")== 0){
return (KMFContainer*)finddeployUnitByID(idP);
}

if(relationName.compare("dictionaryType")== 0){
return dictionaryType;
}

if(relationName.compare("superTypes")== 0){
return (KMFContainer*)findsuperTypesByID(idP);
}

return NULL;

}





void NodeType::visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference)
{
    
      visitor->beginVisitElem(this);
    if(containedReference)
    {
        visitor->beginVisitRef("dictionaryType","org.kevoree.DictionaryType");
internal_visit(visitor,dictionaryType,recursive,containedReference,nonContainedReference,"dictionaryType");
visitor->endVisitRef("dictionaryType");

    }
    if(nonContainedReference)
    {
        



visitor->beginVisitRef("deployUnit","org.kevoree.DeployUnit");
for ( std::map<string,DeployUnit*>::iterator it = deployUnit.begin();  it != deployUnit.end(); ++it)
{
    DeployUnit * current =(DeployUnit*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"deployUnit");
}
visitor->endVisitRef("deployUnit");



visitor->beginVisitRef("superTypes","org.kevoree.TypeDefinition");
for ( std::map<string,TypeDefinition*>::iterator it = superTypes.begin();  it != superTypes.end(); ++it)
{
    TypeDefinition * current =(TypeDefinition*) it->second;
    
    internal_visit(visitor,current,recursive,containedReference,nonContainedReference,"superTypes");
}
visitor->endVisitRef("superTypes");
    }
    visitor->endVisitElem(this);
}


void NodeType::visitAttributes(ModelAttributeVisitor *visitor){
visitor->visit(any(name),"name",this);
visitor->visit(any(version),"version",this);
visitor->visit(any(factoryBean),"factoryBean",this);
visitor->visit(any(bean),"bean",this);
visitor->visit(any(abstract),"abstract",this);
}
NodeType::NodeType(){


}

NodeType::~NodeType(){

deployUnit.clear();
superTypes.clear();
if(dictionaryType != NULL){
delete dictionaryType;
dictionaryType= NULL;}


}

