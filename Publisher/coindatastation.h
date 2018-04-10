#ifndef COINDATASTATION_H
#define COINDATASTATION_H

#include <QObject>
#include <QHash>
#include <QHashIterator>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtDebug>
#include "Publisher/datapublisher.h"
#include "Model/crywsapi.h"
#include "Model/coincollection.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSignalMapper>
using DataObserverPtr = shared_ptr<DataObserver>;
using CoinCollectionPtr = shared_ptr<CoinCollection>;
class CoinDataStation : public QObject, public DataPublisher
{
    Q_OBJECT
private:
    QHash<QString, CoinPtr> trackedCoins;
    QHash<QString, DataObserverPtr> observers;
    QNetworkAccessManager* networkManager;
    QHash<QString, QNetworkReply*> repliesHashTable;
    QSignalMapper* repliesMapper;
    int replyCount;
    CryWSAPI API;
public:
    explicit CoinDataStation(QObject *parent = nullptr);

signals:
    void parseLastValueOfAllCoinsCompleted(const QHash<QString, CoinPtr>& trackedCoins);
    void parseMaxValueIn7DaysOfAllCoinsCompleted(const QHash<QString, CoinPtr>& trackedCoins);
    void creatingANewCollectionCompleted(const QString& collectionName);
public slots:
    void getLastValueOfAllCoins();
    void parseLastValueOfALLCoins(QNetworkReply* replyFromServer);
    void getMaxValueIn7DaysOfAllCoins();
    void parseMaxValueIn7DaysOfAllCoins(QNetworkReply* replyFromServer);
    void replyFromServerArrived(const QString &replyDiscription);
    void createANewCollectionWith(const QString& collectionName, const QStringList& contents);
    // DataPublisher interface
public:
    virtual void registerObserver(const DataObserverPtr &observer) override;
    virtual void removeObserver(const DataObserverPtr &observer) override;
    virtual void notifyAllObservers() override;
    const QHash<QString, CoinPtr>& getTrackedCoins() const;
    const QHash<QString, DataObserverPtr>& getObservers() const;
    QHash<QString, DataObserverPtr>& getRefObservers();
};

#endif // COINDATASTATION_H
