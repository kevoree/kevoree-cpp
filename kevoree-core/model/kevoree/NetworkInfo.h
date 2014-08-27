#ifndef __NetworkInfo_H
#define __NetworkInfo_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class Value;

class NetworkInfo : public NamedElement{ 
public:
std::map<string,Value*> values; 
std::string internalGetKey();
Value *findvaluesByID(std::string id);
void addvalues(Value *ptr);
void removevalues(Value *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
NetworkInfo();

~NetworkInfo();

}; // END CLASS 
#endif
