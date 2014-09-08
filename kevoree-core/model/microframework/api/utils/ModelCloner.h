#ifndef ModelCloner_H
#define ModelCloner_H

#include <microframework/api/KMFContainer.h>
#include <microframework/api/KMFFactory.h>
#include <kevoree-core/model/kevoree/ContainerRoot.h>
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
	std::map<KMFContainer*, KMFContainer*>*  createContext() ;

	template<class A> A*  clone(A* o, bool readOnly, bool mutableOnly);

private:

	 KMFContainer* cloneModelElm(KMFContainer* src) ;
	 void resolveModelElem(KMFContainer* src, KMFContainer* target,std::map<KMFContainer*, KMFContainer*>* context, bool mutableOnly ) ;


	class AttributeCloner : public ModelAttributeVisitor{
	public:
		KMFContainer* clonedSrc ;
		AttributeCloner(KMFContainer* _clonedSrc);
		void visit(KMFContainer *elem,string name,KMFContainer *parent);
	};

	class ReferenceResolver : public ModelVisitor{
	public:
		KMFContainer* target ;
		bool mutableOnly ;
		std::map<KMFContainer*, KMFContainer*>* context ;

		ReferenceResolver(KMFContainer* targetIn, bool mutableOnlyIn,std::map<KMFContainer*, KMFContainer*>* contextIn) ;
		void visit(KMFContainer *elem,string name,KMFContainer *parent);

		};

	class CloneGraphVisitor : public ModelVisitor{
	public:
		std::map<KMFContainer*, KMFContainer*>* context ;
		bool mutableOnly ;
		ModelCloner* modelclone ;

		CloneGraphVisitor(std::map<KMFContainer*, KMFContainer*>* contextIn, bool mutableOnlyIn, ModelCloner* obj);
		void visit(KMFContainer *elem,string name,KMFContainer *parent);
		};

	class ResolveGraphVisitor : public ModelVisitor{
		public:
			std::map<KMFContainer*, KMFContainer*>* context ;
			bool mutableOnly ;
			bool readOnly ;
			ModelCloner* modelclone ;

			ResolveGraphVisitor(std::map<KMFContainer*, KMFContainer*>* contextIn, bool mutableOnlyIn, bool readOnlyIn, ModelCloner* obj);
			void visit(KMFContainer *elem,string name,KMFContainer *parent);
			};
};


#endif


