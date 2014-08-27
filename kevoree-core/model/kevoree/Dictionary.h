#ifndef __Dictionary_H
#define __Dictionary_H
#include <list>
#include <string>
#include <map>
#include <microframework/api/container/KMFContainerImpl.h>
#include <microframework/api/utils/Uuid.h>
class Value;

class Dictionary :  public  KMFContainerImpl{
public:
std::string generated_KMF_ID;
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
Dictionary();

~Dictionary();

}; // END CLASS 
#endif
