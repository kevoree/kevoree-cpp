#ifndef __FragmentDictionary_H
#define __FragmentDictionary_H
#include <list>
#include <string>
#include <map>
#include "Dictionary.h"
#include "NamedElement.h"
class FragmentDictionary : public Dictionary{
public:
string name;
std::string internalGetKey();
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
FragmentDictionary();

~FragmentDictionary();

}; // END CLASS 
#endif
