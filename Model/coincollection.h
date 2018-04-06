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
    QString name;
public:
    explicit CoinCollection(QString name, QObject *parent = nullptr);
    const QHash<QString, CoinPtr>& getTrackedCoins() const;
    void addNewTrackedCoin(const QString& coinSymbol, const CoinPtr& coin);
    void removeTrackedCoin(const QString& coinSymbol);

    const QString& getName() const;
    void setName(const QString &value);

signals:

public slots:
};

#endif // COINCOLLECTION_H
