#ifndef __Dictionary_H
#define __Dictionary_H
#include <list>
#include <string>
#include <map>
#include <microframework/api/container/KMFContainerImpl.h>
#include <microframework/api/utils/Uuid.h>
class DictionaryValue;

class Dictionary : public KMFContainerImpl{ 
public:
std::string generated_KMF_ID;
std::map<string,DictionaryValue*> values; 
std::string internalGetKey();
DictionaryValue *findvaluesByID(std::string id);
void addvalues(DictionaryValue *ptr);
void removevalues(DictionaryValue *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
Dictionary();

~Dictionary();

}; // END CLASS 
#endif
