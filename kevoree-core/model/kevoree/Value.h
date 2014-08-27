#ifndef __Value_H
#define __Value_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class Value : public NamedElement{ 
public:
string value;
std::string internalGetKey();
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
Value();

~Value();

}; // END CLASS 
#endif
