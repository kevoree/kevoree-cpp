#ifndef __Parameter_H
#define __Parameter_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class TypedElement;

class Parameter : public NamedElement{ 
public:
int order;
TypedElement *type; 
std::string internalGetKey();
void addtype(TypedElement *ptr);
void removetype(TypedElement *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
Parameter();

~Parameter();

}; // END CLASS 
#endif
