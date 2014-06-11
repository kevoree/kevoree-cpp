#ifndef __NetworkInfo_H
#define __NetworkInfo_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class NetworkProperty;

class NetworkInfo : public NamedElement{ 
public:
std::map<string,NetworkProperty*> values; 
std::string internalGetKey();
NetworkProperty *findvaluesByID(std::string id);
void addvalues(NetworkProperty *ptr);
void removevalues(NetworkProperty *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
NetworkInfo();

~NetworkInfo();

}; // END CLASS 
#endif
