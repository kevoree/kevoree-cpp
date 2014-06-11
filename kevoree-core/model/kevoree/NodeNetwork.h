#ifndef __NodeNetwork_H
#define __NodeNetwork_H
#include <list>
#include <string>
#include <map>
#include <microframework/api/container/KMFContainerImpl.h>
#include <microframework/api/utils/Uuid.h>
class NodeLink;

class ContainerNode;

class ContainerNode;

class NodeNetwork : public KMFContainerImpl{ 
public:
std::string generated_KMF_ID;
std::map<string,NodeLink*> link; 
ContainerNode *initBy; 
ContainerNode *target; 
std::string internalGetKey();
NodeLink *findlinkByID(std::string id);
void addlink(NodeLink *ptr);
void addinitBy(ContainerNode *ptr);
void addtarget(ContainerNode *ptr);
void removelink(NodeLink *ptr);
void removeinitBy(ContainerNode *ptr);
void removetarget(ContainerNode *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
NodeNetwork();

~NodeNetwork();

}; // END CLASS 
#endif
