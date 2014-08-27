#ifndef __PortTypeRef_H
#define __PortTypeRef_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class PortType;

class PortTypeMapping;

class PortTypeRef : public NamedElement{ 
public:
bool optional;
bool noDependency;
PortType *ref; 
std::map<string,PortTypeMapping*> mappings; 
std::string internalGetKey();
PortTypeMapping *findmappingsByID(std::string id);
void addref(PortType *ptr);
void addmappings(PortTypeMapping *ptr);
void removeref(PortType *ptr);
void removemappings(PortTypeMapping *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
PortTypeRef();

~PortTypeRef();

}; // END CLASS 
#endif
