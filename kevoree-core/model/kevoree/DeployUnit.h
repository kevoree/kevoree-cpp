#ifndef __DeployUnit_H
#define __DeployUnit_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class DeployUnit : public NamedElement{ 
public:
std::string groupName;
std::string version;
std::string url;
std::string hashcode;
std::string type;
std::map<string,DeployUnit*> requiredLibs; 
std::string internalGetKey();
DeployUnit *findrequiredLibsByID(std::string id);
void addrequiredLibs(DeployUnit *ptr);
void removerequiredLibs(DeployUnit *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
DeployUnit();

~DeployUnit();

}; // END CLASS 
#endif
