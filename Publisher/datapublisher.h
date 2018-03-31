#ifndef DATAPUBLISHER_H
#define DATAPUBLISHER_H
#include "Observer/dataobserver.h"
class DataPublisher
{
    virtual void registerObserver(const DataObserver& observer) = 0;
    virtual void removeObserver(const DataObserver& observer) = 0;
    virtual void notifyAllObservers() = 0;
};
#endif // DATAPUBLISHER_H
