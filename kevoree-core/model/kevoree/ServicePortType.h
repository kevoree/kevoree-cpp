#ifndef __ServicePortType_H
#define __ServicePortType_H
#include <list>
#include <string>
#include <map>
#include "PortType.h"
class Operation;

class ServicePortType : public PortType{ 
public:
std::string interface;
std::map<string,Operation*> operations; 
std::string internalGetKey();
Operation *findoperationsByID(std::string id);
void addoperations(Operation *ptr);
void removeoperations(Operation *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
ServicePortType();

~ServicePortType();

}; // END CLASS 
#endif
