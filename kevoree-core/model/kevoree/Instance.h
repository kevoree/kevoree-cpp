#ifndef __Instance_H
#define __Instance_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class TypeDefinition;

class Dictionary;

class FragmentDictionary;

class Value;

class Instance : public NamedElement{ 
public:
bool started;
TypeDefinition *typeDefinition; 
Dictionary *dictionary; 
std::map<string,FragmentDictionary*> fragmentDictionary; 
std::map<string,Value*> metaData; 
std::string internalGetKey();
FragmentDictionary *findfragmentDictionaryByID(std::string id);
Value *findmetaDataByID(std::string id);
void addtypeDefinition(TypeDefinition *ptr);
void adddictionary(Dictionary *ptr);
void addfragmentDictionary(FragmentDictionary *ptr);
void addmetaData(Value *ptr);
void removetypeDefinition(TypeDefinition *ptr);
void removedictionary(Dictionary *ptr);
void removefragmentDictionary(FragmentDictionary *ptr);
void removemetaData(Value *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
Instance();

~Instance();

}; // END CLASS 
#endif
