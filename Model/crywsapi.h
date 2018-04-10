#ifndef CRYWSAPI_H
#define CRYWSAPI_H

#include <QUrl>
#include <QString>
class CryWSAPI
{
private:
    QString hostname;
    QString apiCoins;
    QString getMaxValueIn7DaysOfAllCoins;
    QString getLastValueOfAllCoins;
    QString getSpecificCoinDataWithoutAllValues;
    QString apiAccount;
public:
    CryWSAPI();
    QUrl getMaxValueIn7DaysOfAllCoinsURL() const;
    QUrl getLastValueOfAllCoinsUrl() const;
};

#endif // CRYWSAPI_H
