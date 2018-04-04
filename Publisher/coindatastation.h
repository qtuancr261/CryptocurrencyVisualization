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
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
using std::map;
using CoinPtr = shared_ptr<Coin>;
class CoinDataStation : public QObject, public DataPublisher
{
    Q_OBJECT
private:
    QHash<QString, CoinPtr> trackedCoins;
    QNetworkAccessManager* networkManager;
    CryWSAPI API;
public:
    explicit CoinDataStation(QObject *parent = nullptr);

signals:
    void parseLastValueOfAllCoinsCompleted(const QHash<QString, CoinPtr>& availableCoins);
public slots:
    void getLastValueOfAllCoins();
    void gotLastValueOfALLCoins(QNetworkReply* replyFromServer);
    // DataPublisher interface
public:
    virtual void registerObserver(const DataObserverPtr &observer) override;
    virtual void removeObserver(const DataObserverPtr &observer) override;
    virtual void notifyAllObservers() override;
    const QHash<QString, CoinPtr>& getTrackedCoins() const;
};

#endif // COINDATASTATION_H
