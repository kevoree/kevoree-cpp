#ifndef __KevoreeListeners_H
#define __KevoreeListeners_H

#include <kevoree-core/api/ModelListener.h>
#include <string>

class KevoreeListeners {
	
public:
	KevoreeListeners();
    void start(std::string nodeName);
    void stop();

};

#endif
