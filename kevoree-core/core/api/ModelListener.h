#ifndef __ModelListener_H
#define __ModelListener_H

#include <kevoree-core/model/kevoree/ContainerRoot.h>

class ModelListener {
public:
    /**
     *  Method called before Kevoree Core accept an input model. Synchronized this methods is not suppose to block
     * @param currentModel
     * @param proposedModel
     * @return
     */
	virtual bool preUpdate(ContainerRoot *currentModel, ContainerRoot *proposedModel)=0;

  /**
     * Method called to prepare the core to be update. Synchronized this methods can bloc Kevoree core
     * @param currentModel
     * @param proposedModel
     * @return
     */
	virtual bool initUpdate(ContainerRoot *currentModel, ContainerRoot *proposedModel)=0;

    /* Method called after the local update of the runtime. Synchronized this method can bloc Kevoree core and must return true if update is accepted or not if there is any failure  */
	virtual bool afterLocalUpdate(ContainerRoot currentModel, ContainerRoot proposedModel)=0;

    /**
     *  Method called asynchronisly after a model update
     */
     virtual void modelUpdated()=0;

     virtual void preRollback(ContainerRoot *currentModel, ContainerRoot *proposedModel)=0;
     virtual void postRollback(ContainerRoot *currentModel, ContainerRoot *proposedModel)=0;
}; // END CLASS 


#endif
