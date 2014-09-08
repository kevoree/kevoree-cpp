/*
 * ModelCloner.cpp


 *
 *  Created on: 5 sept. 2014
 *      Author: Aymeric
 */

#include <string>
#include <map>


#include <microframework/api/utils/ModelCloner.h>
#include <microframework/api/utils/ModelAttributeVisitor.h>
#include <microframework/api/utils/KevoreeException.h>



ModelCloner::ModelCloner(KMFFactory* factory) {
	mainFactory = factory ;
}

ModelCloner::~ModelCloner() {
	// TODO Auto-generated destructor stub
}

std::map<KMFContainer*, KMFContainer*>* ModelCloner::createContext()
{
	std::map<KMFContainer*, KMFContainer*>* map = new std::map<KMFContainer*, KMFContainer*>();
	return map ;
}



KMFContainer* ModelCloner::cloneModelElm(KMFContainer* src) {
	if(src != NULL)
	{
		string metaClassname = src->metaClassName() ;
		if(!metaClassname.empty()){
			KMFContainer* clonedSrc = mainFactory->create(src->metaClassName()) ;
			ModelAttributeVisitor* mav = new AttributeCloner(clonedSrc) ;
			src->visitAttributes(mav);
			return clonedSrc ;
		}
		else throw  KevoreeException("KMF Container metaClass Name is empty in cloneModelElm");

	}else throw  KevoreeException("KMF Container in cloneModelElm is Null");


}


void ModelCloner::resolveModelElem(KMFContainer* src, KMFContainer* target,std::map<KMFContainer*, KMFContainer*>* context,bool mutableOnlyIn){
	ReferenceResolver* rf = new ReferenceResolver(target,mutableOnlyIn,context);
	src->visit(rf,false,true,true);
}





/* ------------ Internal Class Attribute Cloner ------------ */

ModelCloner::AttributeCloner::AttributeCloner(KMFContainer* clonedSrcIn){
	clonedSrc = clonedSrcIn;
}

void ModelCloner::AttributeCloner::visit(KMFContainer *elem,string name,KMFContainer *parent){

}

/* ------------ Internal Class ReferenceResolver ------------ */

 ModelCloner::ReferenceResolver::ReferenceResolver(KMFContainer* targetIn, bool mutableOnlyIn,std::map<KMFContainer*, KMFContainer*>* contextIn)
 {
	 target = targetIn ;
	 mutableOnly = mutableOnlyIn;
	 context = contextIn ;
}

 void ModelCloner::ReferenceResolver::visit(KMFContainer *elem,string refNameInParent,KMFContainer *parent){

 	if(elem != NULL){
 	if(mutableOnly && elem->isRecursiveReadOnly() ){
 		target->reflexiveMutator(ADD,refNameInParent,elem,false,false);
 	}else{
 		KMFContainer * elemResolved =  context->find(elem)->second ;
 		if(elemResolved == NULL){
 			throw KevoreeException("Cloner error, not self-contain model, the element " + elem->path() + " is contained in the root element") ;
 		}
 		target->reflexiveMutator(ADD,refNameInParent,elemResolved,false,false);
 	}
 	}else throw  KevoreeException("KMFContainer is Null");
}

 /* ------------ Internal Class CloneGraphVisitor ------------ */

 ModelCloner::CloneGraphVisitor::CloneGraphVisitor(std::map<KMFContainer*, KMFContainer*>* contextIn, bool mutableOnlyIn, ModelCloner* obj){
	 context = contextIn;
	 mutableOnly = mutableOnlyIn ;
	 modelclone = obj ;
 }

void ModelCloner::CloneGraphVisitor::visit(KMFContainer *elem,string name, KMFContainer *parent){

	if(elem != NULL){
	if(mutableOnly && elem->isRecursiveReadOnly() ){
		noChildrenVisit();
	}else{

		context->insert(std::make_pair(elem,modelclone->cloneModelElm(elem))) ;
	}
 	}else throw  KevoreeException("KMFContainer is Null");

}

/* ------------ Internal Class ResolveGraphVisitor ------------ */

ModelCloner::ResolveGraphVisitor::ResolveGraphVisitor(std::map<KMFContainer*, KMFContainer*>* contextIn, bool mutableOnlyIn, bool readOnlyIn,ModelCloner* obj){
	 context = contextIn;
	 mutableOnly = mutableOnlyIn ;
	 readOnly = readOnlyIn ;
	 modelclone = obj ;
		}

void ModelCloner::ResolveGraphVisitor::visit(KMFContainer *elem,string name,KMFContainer *parent){

		if(elem != NULL){
		if(mutableOnly && elem->isRecursiveReadOnly() ){

		}else{
			KMFContainer * clonedObj =  context->find(elem)->second ;
		if(clonedObj != 0){
			modelclone->resolveModelElem(elem,clonedObj, context,mutableOnly);
		}
		}
	 	}else throw  KevoreeException("KMFContainer is Null");


}
