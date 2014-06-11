#ifndef __ContainerNode_H
#define __ContainerNode_H
#include <list>
#include <string>
#include <map>
#include "Instance.h"
class ComponentInstance;

class Group;

class NetworkInfo;

class ContainerNode : public Instance{ 
public:
std::map<string,ComponentInstance*> components; 
std::map<string,ContainerNode*> hosts; 
ContainerNode *host; 
std::map<string,Group*> groups; 
std::map<string,NetworkInfo*> networkInformation; 
std::string internalGetKey();
ComponentInstance *findcomponentsByID(std::string id);
ContainerNode *findhostsByID(std::string id);
Group *findgroupsByID(std::string id);
NetworkInfo *findnetworkInformationByID(std::string id);
void addcomponents(ComponentInstance *ptr);
void addhosts(ContainerNode *ptr);
void addhost(ContainerNode *ptr);
void addgroups(Group *ptr);
void addnetworkInformation(NetworkInfo *ptr);
void removecomponents(ComponentInstance *ptr);
void removehosts(ContainerNode *ptr);
void removehost(ContainerNode *ptr);
void removegroups(Group *ptr);
void removenetworkInformation(NetworkInfo *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
ContainerNode();

~ContainerNode();

}; // END CLASS 
#endif
