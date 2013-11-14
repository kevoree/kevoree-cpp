#ifndef __ModelHandlerLockCallBack_H
#define __ModelHandlerLockCallBack_H

class ModelHandlerLockCallBack {
public:
     void lockTimeout();
     void lockRejected();
     void lockAcquired(UUID bypassUUID);
};


#endif
