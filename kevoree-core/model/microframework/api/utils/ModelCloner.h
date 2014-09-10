#ifndef ModelCloner_H
#define ModelCloner_H

#include <microframework/api/KMFContainer.h>
#include <microframework/api/KMFFactory.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
#include <microframework/api/utils/KevoreeException.h>
#include <microframework/api/utils/ModelAttributeVisitor.h>

#include <map>
#include <iostream>
#include <list>
#include <string>
#include <sstream>



/**
 * Author: jedartois@gmail.com
 * Date: 24/10/13
 * Time: 18:36
 */

class ModelCloner {

public:
	KMFFactory* mainFactory;

	ModelCloner(KMFFactory* factory) ;
	virtual ~ModelCloner();
	std::map<string, KMFContainer*> * createContext() ;


	template<class A>
	A* clone(A* o, bool readOnly, bool mutableOnly){
		cout << "Start " << endl;
		std::map<string, KMFContainer*>*  context = createContext();
		KMFContainer* clonedObject = cloneModelElm(o);
		if(clonedObject != NULL)
		{
			(*context)[o->path()] = clonedObject ;
			CloneGraphVisitor* cgv =  new CloneGraphVisitor(context,mutableOnly,this);
			((KMFContainer*)o)->visit(cgv,true,true,false);
			ResolveGraphVisitor *rgv = new ResolveGraphVisitor(context,mutableOnly,readOnly,this);
			resolveModelElem(o, clonedObject, context, mutableOnly);
			((KMFContainer*)o)->visit(rgv,true,true,false);
			if(readOnly){
				clonedObject->setInternalReadOnly();
			}
			return (A*)clonedObject ;


		}else  throw  KevoreeException("clonedObject NULL");
	}

private:

	 KMFContainer* cloneModelElm(KMFContainer* src) ;
	 void resolveModelElem(KMFContainer* src, KMFContainer* target,std::map<string, KMFContainer*>* context, bool mutableOnly ) ;


	class AttributeCloner : public ModelAttributeVisitor{
	public:
		KMFContainer* clonedSrc ;
		AttributeCloner(KMFContainer* _clonedSrc);
		void  visit(any val,string name,KMFContainer *parent);
	};

	class ReferenceResolver : public ModelVisitor{
	public:
		KMFContainer* target ;
		bool mutableOnly ;
		std::map<string, KMFContainer*>* context ;

		ReferenceResolver(KMFContainer* targetIn, bool mutableOnlyIn,std::map<string, KMFContainer*>* contextIn) ;
		void visit(KMFContainer *elem,string name,KMFContainer *parent);

		};

	class CloneGraphVisitor : public ModelVisitor{
	public:
		std::map<string, KMFContainer*>* context ;
		bool mutableOnly ;
		ModelCloner* modelclone ;

		CloneGraphVisitor(std::map<string, KMFContainer*>*contextIn, bool mutableOnlyIn, ModelCloner* obj);
		void visit(KMFContainer *elem,string name,KMFContainer *parent);
		};

	class ResolveGraphVisitor : public ModelVisitor{
		public:
			std::map<string, KMFContainer*>* context ;
			bool mutableOnly ;
			bool readOnly ;
			ModelCloner* modelclone ;

			ResolveGraphVisitor(std::map<string, KMFContainer*> *contextIn, bool mutableOnlyIn, bool readOnlyIn, ModelCloner* obj);
			void visit(KMFContainer *elem,string name,KMFContainer *parent);
			};
};


#endif


