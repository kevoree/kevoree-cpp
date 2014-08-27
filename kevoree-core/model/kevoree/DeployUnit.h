#ifndef __DeployUnit_H
#define __DeployUnit_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class Value;

class DeployUnit : public NamedElement{ 
public:
string version;
string hashcode;
string url;
std::map<string,Value*> filters; 
std::map<string,DeployUnit*> requiredLibs; 
std::string internalGetKey();
Value *findfiltersByID(std::string id);
DeployUnit *findrequiredLibsByID(std::string id);
void addfilters(Value *ptr);
void addrequiredLibs(DeployUnit *ptr);
void removefilters(Value *ptr);
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
