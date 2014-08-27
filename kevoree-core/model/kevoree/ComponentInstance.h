#ifndef __ComponentInstance_H
#define __ComponentInstance_H
#include <list>
#include <string>
#include <map>
#include "Instance.h"
class Port;

class Port;

class ComponentInstance : public Instance{ 
public:
std::map<string,Port*> provided; 
std::map<string,Port*> required; 
std::string internalGetKey();
Port *findprovidedByID(std::string id);
Port *findrequiredByID(std::string id);
void addprovided(Port *ptr);
void addrequired(Port *ptr);
void removeprovided(Port *ptr);
void removerequired(Port *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
ComponentInstance();

~ComponentInstance();

}; // END CLASS 
#endif
