#include "coindatastation.h"

const QHash<QString, CoinPtr>& CoinDataStation::getTrackedCoins() const { return trackedCoins; }

const QHash<QString, DataObserverPtr>& CoinDataStation::getObservers() const { return observers; }

QHash<QString, DataObserverPtr>& CoinDataStation::getRefObservers() { return observers; }
CoinDataStation::CoinDataStation(QObject* parent)
    : QObject(parent), networkManager{new QNetworkAccessManager(this)}, repliesHashTable{}, repliesMapper{new QSignalMapper(this)}, replyCount{} {
    // QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this,
    // SLOT(gotLastValueOfALLCoins(QNetworkReply*)));
    QObject::connect(repliesMapper, SIGNAL(mapped(QString)), this, SLOT(replyFromServerArrived(QString)));
}

void CoinDataStation::getLastValueOfAllCoins() {
    QNetworkReply* reply{networkManager->get(QNetworkRequest(API.getLastValueOfAllCoinsUrl()))};
    QString replyKey{QString("%1|%2|%3").arg(QString::number(replyCount++)).arg("ALL").arg("lastvalue")};
    repliesHashTable.insert(replyKey, reply);
    repliesMapper->setMapping(reply, replyKey);
    QObject::connect(reply, SIGNAL(finished()), repliesMapper, SLOT(map()));
}

void CoinDataStation::parseLastValueOfALLCoins(QNetworkReply* replyFromServer) {
    // qDebug() << replyFromServer->readAll();
    if (replyFromServer->error()) {
        qDebug() << "Server Error: " << replyFromServer->errorString();
        emit parseLastValueOfAllCoinsCompleted(trackedCoins);
        return;
    }
    QString jsonString{replyFromServer->readAll()};
    QJsonDocument jsonDoc{QJsonDocument::fromJson(jsonString.toUtf8())};
    QJsonArray jsonArray(jsonDoc.array());
    for (int i{}; i < jsonArray.size(); i++) {
        // Parse Coin Object and its last Value
        QJsonObject currentObj{jsonArray.at(i).toObject()};
        QJsonObject lastValue{currentObj.value("last_values").toObject()};
        // Get the value we want from the key we provide
        QString symbol{currentObj.value("symbol").toString()};
        QString name{currentObj.value("name").toString()};
        long availableSupply{static_cast<long>(currentObj.value("available_supply").toString().toDouble())};

        // qDebug() << currentValue.value("price").toDouble() <<
        // currentValue.value("timeStamp").toDouble();
        CoinPtr currentCoin{make_shared<Coin>(name, symbol)};
        // qDebug() << "availale supply" << availableSupply;
        currentCoin->setAvailable_supply(availableSupply);
        currentCoin->getLastValue().timeStamp.setTime_t(lastValue.value("timeStamp").toInt());
        currentCoin->getLastValue().price = lastValue.value("price").toDouble();
        currentCoin->getLastValue().marketcap = lastValue.value("marketcap").toDouble();
        currentCoin->getLastValue().volume_24h = lastValue.value("volume24").toString().toDouble();
        // qDebug() << lastValue.value("volume24").toString();
        currentCoin->getLastValue().changedPercent_1h = lastValue.value("change_1h").toString();
        currentCoin->getLastValue().changedPercent_24h = lastValue.value("change_24h").toString();
        trackedCoins.insert(symbol, currentCoin);
        // qDebug() <<
        // jsonArray.at(0).toArray().at(i).toObject().value("symbol").toString();
        //
    }
    qDebug() << "emit parseLastValueOfAllCoinsCompleted";
    emit parseLastValueOfAllCoinsCompleted(trackedCoins);
}

void CoinDataStation::getMaxValueIn7DaysOfAllCoins() {
    QNetworkReply* reply{networkManager->get(QNetworkRequest(API.getMaxValueIn7DaysOfAllCoinsURL()))};
    QString replyKey{QString("%1|%2|%3").arg(QString::number(replyCount++), "ALL", "chart7days")};
    repliesHashTable.insert(replyKey, reply);
    repliesMapper->setMapping(reply, replyKey);
    QObject::connect(reply, SIGNAL(finished()), repliesMapper, SLOT(map()));
}

void CoinDataStation::parseMaxValueIn7DaysOfAllCoins(QNetworkReply* replyFromServer) {
    qDebug() << "7Days";
    if (replyFromServer->error()) {
        qDebug() << "Server Error: " << replyFromServer->errorString();
        emit parseMaxValueIn7DaysOfAllCoinsCompleted(trackedCoins);
        return;
    }
    QString jsonString{replyFromServer->readAll()};
    QJsonDocument jsonDoc{QJsonDocument::fromJson(jsonString.toUtf8())};
    QJsonArray jsonArray(jsonDoc.array());
    for (int i{}; i < jsonArray.size(); i++) {
        QJsonObject currentCoin{jsonArray.at(i).toObject()};
        QJsonObject max7DaysValues{currentCoin.value("max7days_values").toObject()};
        CoinPtr ptr = trackedCoins.value(currentCoin.value("symbol").toString());
        if (ptr) {
            for (const QString& key : max7DaysValues.keys()) {
                if (key == "prev0") continue;
                qDebug() << key;
                QJsonObject dayValuesObject{max7DaysValues.value(key).toObject()};
                Coin::value dayValues;
                dayValues.timeStamp.setTime_t(dayValuesObject.value("timeStamp").toInt());
                // qDebug() << dayValues.timeStamp.toString("dd/MM/yyyy");
                dayValues.price = dayValuesObject.value("price").toDouble();
                dayValues.marketcap = dayValuesObject.value("marketcap").toInt();
                dayValues.volume_24h = dayValuesObject.value("volume24").toString().toDouble();
                dayValues.changedPercent_24h = dayValuesObject.value("change_24h").toString();
                ptr->getRefAllValues().append(dayValues);
            }
            // Update last Value
        }
    }

    emit parseMaxValueIn7DaysOfAllCoinsCompleted(trackedCoins);
}

void CoinDataStation::replyFromServerArrived(const QString& replyDiscription) {
    qDebug() << "reply ok";
    QString collectionName{replyDiscription.section("|", 1, 1)};
    QString replyType{replyDiscription.section("|", 2, 2)};
    if (collectionName == "ALL" && replyType == "lastvalue")
        parseLastValueOfALLCoins(repliesHashTable.value(replyDiscription));
    else if (collectionName == "ALL" && replyType == "chart7days")
        parseMaxValueIn7DaysOfAllCoins(repliesHashTable.value(replyDiscription));
}

void CoinDataStation::createANewCollection(const QString& collectionName, const QStringList& contents) {
    CoinCollectionPtr newCollection{make_shared<CoinCollection>(CoinCollection(collectionName))};
    for (const QString& symbol : contents) {
        if (trackedCoins.contains(symbol)) newCollection->addNewTrackedCoin(symbol, trackedCoins.value(symbol));
    }
    registerObserver(newCollection);
    qDebug() << observers.contains(collectionName);
    emit creatingANewCollectionCompleted(collectionName);
}

void CoinDataStation::modifyCollectionContents(const QString& collectionName, const QStringList& contents) {
    if (observers.contains(collectionName)) {
        DataObserverPtr collection{observers.value(collectionName)};
        collection->getRefTrackedCoins().clear();
        // :3 We use a trick to modify content

        for (const QString& symbol : contents) {
            collection->addNewTrackedCoin(symbol, trackedCoins.value(symbol));
        }
    }
    emit modifyingCollectionContentsCompleted(collectionName);
}

void CoinDataStation::registerObserver(const DataObserverPtr& observer) {
    if (!observers.contains(observer->getName())) observers.insert(observer->getName(), observer);
}

void CoinDataStation::removeObserver(const DataObserverPtr& observer) { observers.remove(observer->getName()); }

void CoinDataStation::notifyAllObservers() {}
