#ifndef __TypeLibrary_H
#define __TypeLibrary_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class TypeDefinition;

class TypeLibrary : public NamedElement{ 
public:
std::map<string,TypeDefinition*> subTypes; 
std::string internalGetKey();
TypeDefinition *findsubTypesByID(std::string id);
void addsubTypes(TypeDefinition *ptr);
void removesubTypes(TypeDefinition *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
TypeLibrary();

~TypeLibrary();

}; // END CLASS 
#endif
