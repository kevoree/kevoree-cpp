#ifndef __ChannelType_H
#define __ChannelType_H
#include <list>
#include <string>
#include <map>
#include "TypeDefinition.h"
class ChannelType : public TypeDefinition{ 
public:
int lowerBindings;
int upperBindings;
int lowerFragments;
int upperFragments;
std::string internalGetKey();
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
ChannelType();

~ChannelType();

}; // END CLASS 
#endif
