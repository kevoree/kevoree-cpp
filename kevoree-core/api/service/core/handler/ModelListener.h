#ifndef __ModelListener_H
#define __ModelListener_H

#include <ContainerRoot.h>

class ModelListener {
public:
    /**
     *  Method called before Kevoree Core accept an input model. Synchronized this methods is not suppose to block
     * @param currentModel
     * @param proposedModel
     * @return
     */
	bool preUpdate(ContainerRoot *currentModel, ContainerRoot *proposedModel);

  /**
     * Method called to prepare the core to be update. Synchronized this methods can bloc Kevoree core
     * @param currentModel
     * @param proposedModel
     * @return
     */
    bool initUpdate(ContainerRoot *currentModel, ContainerRoot *proposedModel);

    /* Method called after the local update of the runtime. Synchronized this method can bloc Kevoree core and must return true if update is accepted or not if there is any failure  */
    public boolean afterLocalUpdate(ContainerRoot currentModel, ContainerRoot proposedModel);

    /**
     *  Method called asynchronisly after a model update
     */
     void modelUpdated();

     void preRollback(ContainerRoot *currentModel, ContainerRoot *proposedModel);
     void postRollback(ContainerRoot *currentModel, ContainerRoot *proposedModel);
}; // END CLASS 


#endif
