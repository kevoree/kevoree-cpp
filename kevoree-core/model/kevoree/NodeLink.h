#ifndef __NodeLink_H
#define __NodeLink_H
#include <list>
#include <string>
#include <map>
#include <microframework/api/container/KMFContainerImpl.h>
#include <microframework/api/utils/Uuid.h>
class NetworkProperty;

class NodeLink : public KMFContainerImpl{ 
public:
std::string networkType;
int estimatedRate;
std::string lastCheck;
std::string zoneID;
std::string generated_KMF_ID;
std::map<string,NetworkProperty*> networkProperties; 
std::string internalGetKey();
NetworkProperty *findnetworkPropertiesByID(std::string id);
void addnetworkProperties(NetworkProperty *ptr);
void removenetworkProperties(NetworkProperty *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
NodeLink();

~NodeLink();

}; // END CLASS 
#endif
