#ifndef DATAOBSERVER_H
#define DATAOBSERVER_H
#include "Model/coin.h"
#include <QVector>
class DataObserver
{
    virtual void update(QVector<Coin*> coins) = 0;
};
#endif // DATAOBSERVER_H
