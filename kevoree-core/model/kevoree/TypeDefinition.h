#ifndef __TypeDefinition_H
#define __TypeDefinition_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class DeployUnit;

class DictionaryType;

class TypeDefinition : public NamedElement{ 
public:
std::string version;
std::string factoryBean;
std::string bean;
bool abstract;
std::map<string,DeployUnit*> deployUnit; 
DictionaryType *dictionaryType; 
std::map<string,TypeDefinition*> superTypes; 
std::string internalGetKey();
DeployUnit *finddeployUnitByID(std::string id);
TypeDefinition *findsuperTypesByID(std::string id);
void adddeployUnit(DeployUnit *ptr);
void adddictionaryType(DictionaryType *ptr);
void addsuperTypes(TypeDefinition *ptr);
void removedeployUnit(DeployUnit *ptr);
void removedictionaryType(DictionaryType *ptr);
void removesuperTypes(TypeDefinition *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
TypeDefinition();

~TypeDefinition();

}; // END CLASS 
#endif
