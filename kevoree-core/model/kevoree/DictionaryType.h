#ifndef __DictionaryType_H
#define __DictionaryType_H
#include <list>
#include <string>
#include <map>
#include <microframework/api/container/KMFContainerImpl.h>
#include <microframework/api/utils/Uuid.h>
class DictionaryAttribute;

class DictionaryType : public KMFContainerImpl{ 
public:
std::string generated_KMF_ID;
std::map<string,DictionaryAttribute*> attributes; 
std::string internalGetKey();
DictionaryAttribute *findattributesByID(std::string id);
void addattributes(DictionaryAttribute *ptr);
void removeattributes(DictionaryAttribute *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
DictionaryType();

~DictionaryType();

}; // END CLASS 
#endif
