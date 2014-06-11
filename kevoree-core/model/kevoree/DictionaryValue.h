#ifndef __DictionaryValue_H
#define __DictionaryValue_H
#include <list>
#include <string>
#include <map>
#include <microframework/api/container/KMFContainerImpl.h>
class DictionaryValue : public KMFContainerImpl{ 
public:
std::string name;
std::string value;
std::string internalGetKey();
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
DictionaryValue();

~DictionaryValue();

}; // END CLASS 
#endif
