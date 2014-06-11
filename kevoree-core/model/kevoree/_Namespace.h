#ifndef ___Namespace_H
#define ___Namespace_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class Instance;

class _Namespace : public NamedElement{ 
public:
std::map<string,Instance*> elements; 
std::string internalGetKey();
Instance *findelementsByID(std::string id);
void addelements(Instance *ptr);
void removeelements(Instance *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
_Namespace();

~_Namespace();

}; // END CLASS 
#endif
