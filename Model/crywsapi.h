#ifndef CRYWSAPI_H
#define CRYWSAPI_H

#include <QUrl>
#include <QString>
class CryWSAPI
{
private:
    QString hostname;
    QString apiCoins;
    QString getDataInSevenDays;
    QString getDataWithoutAllValues;
    QString getSpecificCoinDataWithoutAllValues;
    QString apiAccount;
public:
    CryWSAPI();
    QString getGetDataInSevenDays() const;
    QString getGetDataWithoutAllValues() const;
};

#endif // CRYWSAPI_H
