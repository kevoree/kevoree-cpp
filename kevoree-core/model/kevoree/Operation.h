#ifndef __Operation_H
#define __Operation_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class Parameter;

class TypedElement;

class Operation : public NamedElement{ 
public:
std::map<string,Parameter*> parameters; 
TypedElement *returnType; 
std::string internalGetKey();
Parameter *findparametersByID(std::string id);
void addparameters(Parameter *ptr);
void addreturnType(TypedElement *ptr);
void removeparameters(Parameter *ptr);
void removereturnType(TypedElement *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
Operation();

~Operation();

}; // END CLASS 
#endif
