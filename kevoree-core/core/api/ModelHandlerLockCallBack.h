#ifndef __ModelHandlerLockCallBack_H
#define __ModelHandlerLockCallBack_H

class ModelHandlerLockCallBack {
public:
    virtual void lockTimeout()=0;
    virtual void lockRejected()=0;
    virtual void lockAcquired(UUID bypassUUID)=0;
};


#endif
