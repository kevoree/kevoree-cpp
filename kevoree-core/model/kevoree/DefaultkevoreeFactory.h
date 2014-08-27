#ifndef __DefaultkevoreeFactory_H
#define __DefaultkevoreeFactory_H

#include "kevoree.h"

#include <microframework/api/KMFFactory.h>

class DefaultkevoreeFactory : public KMFFactory {
public:
ComponentInstance* createComponentInstance(){return new ComponentInstance();
};
Instance* createInstance(){return new Instance();
};
Port* createPort(){return new Port();
};
ComponentType* createComponentType(){return new ComponentType();
};
TypeDefinition* createTypeDefinition(){return new TypeDefinition();
};
PortTypeRef* createPortTypeRef(){return new PortTypeRef();
};
ContainerNode* createContainerNode(){return new ContainerNode();
};
Group* createGroup(){return new Group();
};
NetworkInfo* createNetworkInfo(){return new NetworkInfo();
};
ContainerRoot* createContainerRoot(){return new ContainerRoot();
};
Repository* createRepository(){return new Repository();
};
Channel* createChannel(){return new Channel();
};
MBinding* createMBinding(){return new MBinding();
};
Package* createPackage(){return new Package();
};
NamedElement* createNamedElement(){return new NamedElement();
};
DeployUnit* createDeployUnit(){return new DeployUnit();
};
PortType* createPortType(){return new PortType();
};
Dictionary* createDictionary(){return new Dictionary();
};
Value* createValue(){return new Value();
};
FragmentDictionary* createFragmentDictionary(){return new FragmentDictionary();
};
DictionaryType* createDictionaryType(){return new DictionaryType();
};
DictionaryAttribute* createDictionaryAttribute(){return new DictionaryAttribute();
};
TypedElement* createTypedElement(){return new TypedElement();
};
PortTypeMapping* createPortTypeMapping(){return new PortTypeMapping();
};
ServicePortType* createServicePortType(){return new ServicePortType();
};
Operation* createOperation(){return new Operation();
};
Parameter* createParameter(){return new Parameter();
};
MessagePortType* createMessagePortType(){return new MessagePortType();
};
ChannelType* createChannelType(){return new ChannelType();
};
GroupType* createGroupType(){return new GroupType();
};
NodeType* createNodeType(){return new NodeType();
};
KMFContainer* create(std::string metaClassName){
if(metaClassName.compare("org.kevoree.ComponentInstance")==0){
return (KMFContainer*) createComponentInstance();
}
if(metaClassName.compare("org.kevoree.Instance")==0){
return (KMFContainer*) createInstance();
}
if(metaClassName.compare("org.kevoree.Port")==0){
return (KMFContainer*) createPort();
}
if(metaClassName.compare("org.kevoree.ComponentType")==0){
return (KMFContainer*) createComponentType();
}
if(metaClassName.compare("org.kevoree.TypeDefinition")==0){
return (KMFContainer*) createTypeDefinition();
}
if(metaClassName.compare("org.kevoree.PortTypeRef")==0){
return (KMFContainer*) createPortTypeRef();
}
if(metaClassName.compare("org.kevoree.ContainerNode")==0){
return (KMFContainer*) createContainerNode();
}
if(metaClassName.compare("org.kevoree.Group")==0){
return (KMFContainer*) createGroup();
}
if(metaClassName.compare("org.kevoree.NetworkInfo")==0){
return (KMFContainer*) createNetworkInfo();
}
if(metaClassName.compare("org.kevoree.ContainerRoot")==0){
return (KMFContainer*) createContainerRoot();
}
if(metaClassName.compare("org.kevoree.Repository")==0){
return (KMFContainer*) createRepository();
}
if(metaClassName.compare("org.kevoree.Channel")==0){
return (KMFContainer*) createChannel();
}
if(metaClassName.compare("org.kevoree.MBinding")==0){
return (KMFContainer*) createMBinding();
}
if(metaClassName.compare("org.kevoree.Package")==0){
return (KMFContainer*) createPackage();
}
if(metaClassName.compare("org.kevoree.NamedElement")==0){
return (KMFContainer*) createNamedElement();
}
if(metaClassName.compare("org.kevoree.DeployUnit")==0){
return (KMFContainer*) createDeployUnit();
}
if(metaClassName.compare("org.kevoree.PortType")==0){
return (KMFContainer*) createPortType();
}
if(metaClassName.compare("org.kevoree.Dictionary")==0){
return (KMFContainer*) createDictionary();
}
if(metaClassName.compare("org.kevoree.Value")==0){
return (KMFContainer*) createValue();
}
if(metaClassName.compare("org.kevoree.FragmentDictionary")==0){
return (KMFContainer*) createFragmentDictionary();
}
if(metaClassName.compare("org.kevoree.DictionaryType")==0){
return (KMFContainer*) createDictionaryType();
}
if(metaClassName.compare("org.kevoree.DictionaryAttribute")==0){
return (KMFContainer*) createDictionaryAttribute();
}
if(metaClassName.compare("org.kevoree.TypedElement")==0){
return (KMFContainer*) createTypedElement();
}
if(metaClassName.compare("org.kevoree.PortTypeMapping")==0){
return (KMFContainer*) createPortTypeMapping();
}
if(metaClassName.compare("org.kevoree.ServicePortType")==0){
return (KMFContainer*) createServicePortType();
}
if(metaClassName.compare("org.kevoree.Operation")==0){
return (KMFContainer*) createOperation();
}
if(metaClassName.compare("org.kevoree.Parameter")==0){
return (KMFContainer*) createParameter();
}
if(metaClassName.compare("org.kevoree.MessagePortType")==0){
return (KMFContainer*) createMessagePortType();
}
if(metaClassName.compare("org.kevoree.ChannelType")==0){
return (KMFContainer*) createChannelType();
}
if(metaClassName.compare("org.kevoree.GroupType")==0){
return (KMFContainer*) createGroupType();
}
if(metaClassName.compare("org.kevoree.NodeType")==0){
return (KMFContainer*) createNodeType();
}
return NULL;
}
};
#endif
