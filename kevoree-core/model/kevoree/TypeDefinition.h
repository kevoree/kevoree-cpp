#ifndef __TypeDefinition_H
#define __TypeDefinition_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class DeployUnit;

class DictionaryType;

class Value;

class TypeDefinition : public NamedElement{ 
public:
string version;
bool abstract;
std::map<string,DeployUnit*> deployUnits; 
std::map<string,TypeDefinition*> superTypes; 
DictionaryType *dictionaryType; 
std::map<string,Value*> metaData; 
std::string internalGetKey();
DeployUnit *finddeployUnitsByID(std::string id);
TypeDefinition *findsuperTypesByID(std::string id);
Value *findmetaDataByID(std::string id);
void adddeployUnits(DeployUnit *ptr);
void addsuperTypes(TypeDefinition *ptr);
void adddictionaryType(DictionaryType *ptr);
void addmetaData(Value *ptr);
void removedeployUnits(DeployUnit *ptr);
void removesuperTypes(TypeDefinition *ptr);
void removedictionaryType(DictionaryType *ptr);
void removemetaData(Value *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
TypeDefinition();

~TypeDefinition();

}; // END CLASS 
#endif
