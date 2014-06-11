#ifndef __NetworkProperty_H
#define __NetworkProperty_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class NetworkProperty : public NamedElement{ 
public:
std::string name;
std::string value;
std::string internalGetKey();
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
NetworkProperty();

~NetworkProperty();

}; // END CLASS 
#endif
