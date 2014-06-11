#ifndef __PortTypeMapping_H
#define __PortTypeMapping_H
#include <list>
#include <string>
#include <map>
#include <microframework/api/container/KMFContainerImpl.h>
#include <microframework/api/utils/Uuid.h>
class PortTypeMapping : public KMFContainerImpl{ 
public:
std::string beanMethodName;
std::string serviceMethodName;
std::string paramTypes;
std::string generated_KMF_ID;
std::string internalGetKey();
string metaClassName();
void reflexiveMutator(int ___mutatorType,string ___refName, any ___value, bool ___setOpposite,bool ___fireEvent );
void visit(ModelVisitor *visitor,bool recursive,bool containedReference ,bool nonContainedReference);
void visitAttributes(ModelAttributeVisitor *visitor);
PortTypeMapping();

~PortTypeMapping();

}; // END CLASS 
#endif
