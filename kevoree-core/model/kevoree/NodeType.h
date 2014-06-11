#ifndef __NodeType_H
#define __NodeType_H
#include <list>
#include <string>
#include <map>
#include "TypeDefinition.h"
class NodeType : public TypeDefinition{ 
public:
std::string internalGetKey();
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
NodeType();

~NodeType();

}; // END CLASS 
#endif
