#ifndef __GroupType_H
#define __GroupType_H
#include <list>
#include <string>
#include <map>
#include "TypeDefinition.h"
class GroupType : public TypeDefinition{ 
public:
std::string internalGetKey();
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
GroupType();

~GroupType();

}; // END CLASS 
#endif
