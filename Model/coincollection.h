#ifndef COINCOLLECTION_H
#define COINCOLLECTION_H

#include <QHash>
#include <QObject>
#include "Model/coin.h"
#include "Observer/dataobserver.h"
class CoinCollection : public DataObserver {
private:
    QHash<QString, CoinPtr> trackedCoins;
    QString name;

public:
    explicit CoinCollection(QString name);
    const QHash<QString, CoinPtr>& getTrackedCoins() const override;
    QHash<QString, CoinPtr>& getRefTrackedCoins() override;
    void addNewTrackedCoin(const QString& coinSymbol, const CoinPtr& coin) override;
    void removeTrackedCoin(const QString& coinSymbol) override;

    const QString& getName() const override;
    void setName(const QString& value) override;

    // DataObserver interface
};

#endif  // COINCOLLECTION_H
