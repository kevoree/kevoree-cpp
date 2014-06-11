#ifndef __ContainerRoot_H
#define __ContainerRoot_H
#include <list>
#include <string>
#include <map>
#include <microframework/api/container/KMFContainerImpl.h>
#include <microframework/api/utils/Uuid.h>
class ContainerNode;

class TypeDefinition;

class Repository;

class TypedElement;

class TypeLibrary;

class Channel;

class MBinding;

class DeployUnit;

class NodeNetwork;

class Group;

class ContainerRoot : public KMFContainerImpl{ 
public:
std::string generated_KMF_ID;
std::map<string,ContainerNode*> nodes; 
std::map<string,TypeDefinition*> typeDefinitions; 
std::map<string,Repository*> repositories; 
std::map<string,TypedElement*> dataTypes; 
std::map<string,TypeLibrary*> libraries; 
std::map<string,Channel*> hubs; 
std::map<string,MBinding*> mBindings; 
std::map<string,DeployUnit*> deployUnits; 
std::map<string,NodeNetwork*> nodeNetworks; 
std::map<string,Group*> groups; 
std::string internalGetKey();
ContainerNode *findnodesByID(std::string id);
TypeDefinition *findtypeDefinitionsByID(std::string id);
Repository *findrepositoriesByID(std::string id);
TypedElement *finddataTypesByID(std::string id);
TypeLibrary *findlibrariesByID(std::string id);
Channel *findhubsByID(std::string id);
MBinding *findmBindingsByID(std::string id);
DeployUnit *finddeployUnitsByID(std::string id);
NodeNetwork *findnodeNetworksByID(std::string id);
Group *findgroupsByID(std::string id);
void addnodes(ContainerNode *ptr);
void addtypeDefinitions(TypeDefinition *ptr);
void addrepositories(Repository *ptr);
void adddataTypes(TypedElement *ptr);
void addlibraries(TypeLibrary *ptr);
void addhubs(Channel *ptr);
void addmBindings(MBinding *ptr);
void adddeployUnits(DeployUnit *ptr);
void addnodeNetworks(NodeNetwork *ptr);
void addgroups(Group *ptr);
void removenodes(ContainerNode *ptr);
void removetypeDefinitions(TypeDefinition *ptr);
void removerepositories(Repository *ptr);
void removedataTypes(TypedElement *ptr);
void removelibraries(TypeLibrary *ptr);
void removehubs(Channel *ptr);
void removemBindings(MBinding *ptr);
void removedeployUnits(DeployUnit *ptr);
void removenodeNetworks(NodeNetwork *ptr);
void removegroups(Group *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
ContainerRoot();

~ContainerRoot();

}; // END CLASS 
#endif
