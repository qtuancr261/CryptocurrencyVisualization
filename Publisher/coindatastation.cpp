#include "coindatastation.h"

CoinDataStation::CoinDataStation(QObject *parent)
    : QObject(parent),
      networkManager{new QNetworkAccessManager(this)}
{
    QObject::connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(gotLastValueOfALLCoins(QNetworkReply*)));
}

void CoinDataStation::getLastValueOfAllCoins()
{
    networkManager->get(QNetworkRequest(QUrl(API.getGetDataWithoutAllValues())));
}

void CoinDataStation::gotLastValueOfALLCoins(QNetworkReply *replyFromServer)
{
    qDebug() << replyFromServer->readAll();
}


void CoinDataStation::registerObserver(const DataObserverPtr &observer)
{

}

void CoinDataStation::removeObserver(const DataObserverPtr &observer)
{
}

void CoinDataStation::notifyAllObservers()
{
}
