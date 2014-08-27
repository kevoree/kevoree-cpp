#ifndef __ContainerRoot_H
#define __ContainerRoot_H
#include <list>
#include <string>
#include <map>
#include <microframework/api/container/KMFContainerImpl.h>
#include <microframework/api/utils/Uuid.h>
class ContainerNode;

class Repository;

class Channel;

class MBinding;

class Group;

class Package;

class ContainerRoot : public KMFContainerImpl{ 
public:
std::string generated_KMF_ID;
std::map<string,ContainerNode*> nodes; 
std::map<string,Repository*> repositories; 
std::map<string,Channel*> hubs; 
std::map<string,MBinding*> mBindings; 
std::map<string,Group*> groups; 
std::map<string,Package*> packages; 
std::string internalGetKey();
ContainerNode *findnodesByID(std::string id);
Repository *findrepositoriesByID(std::string id);
Channel *findhubsByID(std::string id);
MBinding *findmBindingsByID(std::string id);
Group *findgroupsByID(std::string id);
Package *findpackagesByID(std::string id);
void addnodes(ContainerNode *ptr);
void addrepositories(Repository *ptr);
void addhubs(Channel *ptr);
void addmBindings(MBinding *ptr);
void addgroups(Group *ptr);
void addpackages(Package *ptr);
void removenodes(ContainerNode *ptr);
void removerepositories(Repository *ptr);
void removehubs(Channel *ptr);
void removemBindings(MBinding *ptr);
void removegroups(Group *ptr);
void removepackages(Package *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
ContainerRoot();

~ContainerRoot();

}; // END CLASS 
#endif
