#ifndef __Package_H
#define __Package_H
#include <list>
#include <string>
#include <map>
#include "NamedElement.h"
class TypeDefinition;

class DeployUnit;

class Package : public NamedElement{ 
public:
std::map<string,Package*> packages; 
std::map<string,TypeDefinition*> typeDefinitions; 
std::map<string,DeployUnit*> deployUnits; 
std::string internalGetKey();
Package *findpackagesByID(std::string id);
TypeDefinition *findtypeDefinitionsByID(std::string id);
DeployUnit *finddeployUnitsByID(std::string id);
void addpackages(Package *ptr);
void addtypeDefinitions(TypeDefinition *ptr);
void adddeployUnits(DeployUnit *ptr);
void removepackages(Package *ptr);
void removetypeDefinitions(TypeDefinition *ptr);
void removedeployUnits(DeployUnit *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
Package();

~Package();

}; // END CLASS 
#endif
