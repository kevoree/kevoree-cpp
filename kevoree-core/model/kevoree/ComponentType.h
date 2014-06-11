#ifndef __ComponentType_H
#define __ComponentType_H
#include <list>
#include <string>
#include <map>
#include "TypeDefinition.h"
class PortTypeRef;

class PortTypeRef;

class ComponentType : public TypeDefinition{ 
public:
std::map<string,PortTypeRef*> required; 
std::map<string,PortTypeRef*> provided; 
std::string internalGetKey();
PortTypeRef *findrequiredByID(std::string id);
PortTypeRef *findprovidedByID(std::string id);
void addrequired(PortTypeRef *ptr);
void addprovided(PortTypeRef *ptr);
void removerequired(PortTypeRef *ptr);
void removeprovided(PortTypeRef *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
ComponentType();

~ComponentType();

}; // END CLASS 
#endif
