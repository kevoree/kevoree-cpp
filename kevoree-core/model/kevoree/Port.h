#ifndef __Port_H
#define __Port_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class MBinding;

class PortTypeRef;

class Port : public NamedElement{ 
public:
std::map<string,MBinding*> bindings; 
PortTypeRef *portTypeRef; 
std::string internalGetKey();
MBinding *findbindingsByID(std::string id);
void addbindings(MBinding *ptr);
void addportTypeRef(PortTypeRef *ptr);
void removebindings(MBinding *ptr);
void removeportTypeRef(PortTypeRef *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
Port();

~Port();

}; // END CLASS 
#endif
