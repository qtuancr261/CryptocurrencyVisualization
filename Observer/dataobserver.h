#ifndef DATAOBSERVER_H
#define DATAOBSERVER_H
#include <QVector>
#include "Model/coin.h"
using CoinPtr = shared_ptr<Coin>;
class DataObserver {
    // virtual void update(QVector<Coin*> coins) = 0;
public:
    virtual const QString& getName() const = 0;
    virtual void setName(const QString& name) = 0;
    virtual const QHash<QString, CoinPtr>& getTrackedCoins() const = 0;
    virtual QHash<QString, CoinPtr>& getRefTrackedCoins() = 0;
    virtual void addNewTrackedCoin(const QString& coinSymbol, const CoinPtr& coin) = 0;
    virtual void removeTrackedCoin(const QString& coinSymbol) = 0;
};
#endif  // DATAOBSERVER_H
