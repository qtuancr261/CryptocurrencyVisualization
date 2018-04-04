#ifndef COINCOLLECTION_H
#define COINCOLLECTION_H

#include <QObject>
#include "Observer/dataobserver.h"
#include "Model/coin.h"
#include <QHash>
#include "Publisher/coindatastation.h"
class CoinCollection : public QObject, public DataObserver
{
    Q_OBJECT
private:
    QHash<QString, CoinPtr> trackedCoins;
public:
    explicit CoinCollection(QObject *parent = nullptr);
    const QHash<QString, CoinPtr>& getTrackedCoins() const;
    void addNewTrackedCoin(const QString& coinSymbol, const CoinPtr& coin);
    void removeTrackedCoin(const QString& coinSymbol);

signals:

public slots:
};

#endif // COINCOLLECTION_H
