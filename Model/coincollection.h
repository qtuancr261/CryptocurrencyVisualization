#ifndef COINCOLLECTION_H
#define COINCOLLECTION_H

#include <QObject>
#include "Observer/dataobserver.h"
#include "Model/coin.h"
#include <QHash>
class CoinCollection : public DataObserver
{
private:
    QHash<QString, CoinPtr> trackedCoins;
    QString name;
public:
    explicit CoinCollection(QString name);
    const QHash<QString, CoinPtr>& getTrackedCoins() const override;
    void addNewTrackedCoin(const QString& coinSymbol, const CoinPtr& coin) override;
    void removeTrackedCoin(const QString& coinSymbol) override;

    const QString& getName() const override;
    void setName(const QString &value) override;
};

#endif // COINCOLLECTION_H
