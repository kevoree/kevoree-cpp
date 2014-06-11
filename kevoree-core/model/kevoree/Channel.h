#ifndef __Channel_H
#define __Channel_H
#include <list>
#include <string>
#include <map>
#include "Instance.h"
class MBinding;

class Channel : public Instance{ 
public:
std::map<string,MBinding*> bindings; 
std::string internalGetKey();
MBinding *findbindingsByID(std::string id);
void addbindings(MBinding *ptr);
void removebindings(MBinding *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
Channel();

~Channel();

}; // END CLASS 
#endif
