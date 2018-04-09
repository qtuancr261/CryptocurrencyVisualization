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
using DataObserverPtr = shared_ptr<DataObserver>;
using CoinCollectionPtr = shared_ptr<CoinCollection>;
class CoinDataStation : public QObject, public DataPublisher
{
    Q_OBJECT
private:
    QHash<QString, CoinPtr> trackedCoins;
    QHash<QString, DataObserverPtr> observers;
    QNetworkAccessManager* networkManager;
    CryWSAPI API;
public:
    explicit CoinDataStation(QObject *parent = nullptr);

signals:
    void parseLastValueOfAllCoinsCompleted(const QHash<QString, CoinPtr>& availableCoins);
    void creatingANewCollectionCompleted(const QString& collectionName);
public slots:
    void getLastValueOfAllCoins();
    void gotLastValueOfALLCoins(QNetworkReply* replyFromServer);
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
