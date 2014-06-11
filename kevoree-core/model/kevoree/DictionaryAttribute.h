#ifndef __DictionaryAttribute_H
#define __DictionaryAttribute_H
#include <list>
#include <string>
#include <map>
#include "TypedElement.h"
class DictionaryAttribute : public TypedElement{ 
public:
bool optional;
bool state;
std::string datatype;
bool fragmentDependant;
std::string defaultValue;
std::string internalGetKey();
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
DictionaryAttribute();

~DictionaryAttribute();

}; // END CLASS 
#endif
