#ifndef __Repository_H
#define __Repository_H
#include <list>
#include <string>
#include <map>
#include <microframework/api/container/KMFContainerImpl.h>
class Repository : public KMFContainerImpl{ 
public:
std::string url;
std::string internalGetKey();
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
Repository();

~Repository();

}; // END CLASS 
#endif
