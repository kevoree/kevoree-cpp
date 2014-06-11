#ifndef __MBinding_H
#define __MBinding_H
#include <list>
#include <string>
#include <map>
#include <microframework/api/container/KMFContainerImpl.h>
#include <microframework/api/utils/Uuid.h>
class Port;

class Channel;

class MBinding : public KMFContainerImpl{ 
public:
std::string generated_KMF_ID;
Port *port; 
Channel *hub; 
std::string internalGetKey();
void addport(Port *ptr);
void addhub(Channel *ptr);
void removeport(Port *ptr);
void removehub(Channel *ptr);
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
KMFContainer* findByID(string relationName,string idP);
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
MBinding();

~MBinding();

}; // END CLASS 
#endif
