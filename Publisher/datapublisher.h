#ifndef DATAPUBLISHER_H
#define DATAPUBLISHER_H
#include <memory>
#include "Observer/dataobserver.h"
using std::make_shared;
using std::shared_ptr;
using std::weak_ptr;
using DataObserverPtr = shared_ptr<DataObserver>;
class DataPublisher {
    virtual void registerObserver(const DataObserverPtr& observer) = 0;
    virtual void removeObserver(const DataObserverPtr& observer) = 0;
    virtual void notifyAllObservers() = 0;
};
#endif  // DATAPUBLISHER_H
