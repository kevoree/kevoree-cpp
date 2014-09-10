/*
 * ModelCloner.cpp


 *
 *  Created on: 5 sept. 2014
 *      Author: Aymeric
 */

#include <string>
#include <map>


#include <microframework/api/utils/ModelCloner.h>
#include <microframework/api/utils/KevoreeException.h>



ModelCloner::ModelCloner(KMFFactory* factory) {
	mainFactory = factory ;
}

ModelCloner::~ModelCloner() {
	// TODO Auto-generated destructor stub
}

std::map<string, KMFContainer*>* ModelCloner::createContext()
{
	std::map<string, KMFContainer*>* map = new std::map<string, KMFContainer*>();
	return map ;
}



KMFContainer* ModelCloner::cloneModelElm(KMFContainer* src) {



	if(src != NULL)
	{
		string metaClassname = src->metaClassName() ;
		if(!metaClassname.empty()){
			KMFContainer* clonedSrc = mainFactory->create("org.kevoree." + src->metaClassName()) ;
			if(clonedSrc != NULL)
			{
				ModelAttributeVisitor* mav = new AttributeCloner(clonedSrc) ;
				src->visitAttributes(mav);

				return clonedSrc ;
			}else throw  KevoreeException("Unable to clone element" + src->metaClassName());
		}
		else throw  KevoreeException("KMF Container metaClass Name is empty in cloneModelElm");

	}else throw  KevoreeException("KMF Container in cloneModelElm is Null");


}


void ModelCloner::resolveModelElem(KMFContainer* src, KMFContainer* target,std::map<string, KMFContainer*>* context,bool mutableOnlyIn){
	ReferenceResolver* rf = new ReferenceResolver(target,mutableOnlyIn,context);
	src->visit(rf,false,true,true);
}





/* ------------ Internal Class Attribute Cloner ------------ */

ModelCloner::AttributeCloner::AttributeCloner(KMFContainer* clonedSrcIn){

	clonedSrc = clonedSrcIn;
}

void ModelCloner::AttributeCloner::visit(any val,string name,KMFContainer *parent){
	if(!val.empty ())
	{
		string data="";
		if (!val.empty () && val.type () == typeid (string) )
		{
			data =AnyCast < string>(val);
		}else  if(!val.empty () && val.type () == typeid (int))
		{
			data =AnyCast < int>(val);
		}else  if(!val.empty () && val.type () == typeid (short))
		{
			data =AnyCast <short>(val);
		} else  if(!val.empty () && val.type () == typeid (bool))
		{
			if(AnyCast<bool>(val) == true)
			{
				data ="true";
			} else
			{
				data  ="false";
			}
		}
		else{
			LOGGER_WRITE(Logger::ERROR,"The SerializerAttributeVisitor::visit the type is not supported of "+name+" his parent his "+parent->path());
		}
		clonedSrc->reflexiveMutator(SET,name, data, false, false);
	}
}
/*
 *
 *
 *
 *

 		cout << "visiting " << name  <<" : "<< data << endl ;

 */

/* ------------ Internal Class ReferenceResolver ------------ */

ModelCloner::ReferenceResolver::ReferenceResolver(KMFContainer* targetIn, bool mutableOnlyIn,std::map<string, KMFContainer*>* contextIn)
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
			KMFContainer *  elemResolved = NULL ;
			if(context->find(elem->path()) != context->end()){
				elemResolved = (*context)[elem->path()];
			}
			if(elemResolved == NULL){
				cout << elem->metaClassName() << endl ;
				throw KevoreeException("Cloner error, not self-contain model, the element " + elem->path() + " is contained in the root element") ;
			}

			target->reflexiveMutator(ADD,refNameInParent,elemResolved,false,false);

		}
	}else throw  KevoreeException("KMFContainer is Null");
}

/* ------------ Internal Class CloneGraphVisitor ------------ */

ModelCloner::CloneGraphVisitor::CloneGraphVisitor(std::map<string, KMFContainer*>* contextIn, bool mutableOnlyIn, ModelCloner* obj){
	context = contextIn;
	mutableOnly = mutableOnlyIn ;
	modelclone = obj ;
}

void ModelCloner::CloneGraphVisitor::visit(KMFContainer* elem,string name, KMFContainer *parent){
	if(elem != NULL){
		if(mutableOnly && elem->isRecursiveReadOnly() ){
			noChildrenVisit();
		}else{
			KMFContainer* clonedObject = modelclone->cloneModelElm(elem);
			(*context)[elem->path()] =clonedObject ;

		}
	}else throw  KevoreeException("KMFContainer is Null");

}

/* ------------ Internal Class ResolveGraphVisitor ------------ */

ModelCloner::ResolveGraphVisitor::ResolveGraphVisitor(std::map<string, KMFContainer*>* contextIn, bool mutableOnlyIn, bool readOnlyIn,ModelCloner* obj){
	context = contextIn;
	mutableOnly = mutableOnlyIn ;
	readOnly = readOnlyIn ;
	modelclone = obj ;
}

void ModelCloner::ResolveGraphVisitor::visit(KMFContainer *elem,string name,KMFContainer *parent){

	if(elem != NULL){
		if(mutableOnly && elem->isRecursiveReadOnly() ){

		}else{
			KMFContainer * clonedObj =  NULL ;
			if(context->find(elem->path()) != context->end()){
				clonedObj = (*context)[elem->path()];
				modelclone->resolveModelElem(elem,clonedObj, context,mutableOnly);

					}else throw  KevoreeException("Unable to resolve Model Element " + elem->metaClassName());

				if(readOnly){
					clonedObj->setInternalReadOnly();
						}



		}
	}else throw  KevoreeException("KMFContainer is Null");


}
