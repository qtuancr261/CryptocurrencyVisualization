#ifndef COIN_H
#define COIN_H
#include <QString>
#include <QIcon>
#include <QVector>
using ulong = unsigned long;
class Coin
{
private:
    QString name;
    QString symbol;
    QIcon icon;
    long available_supply;
    struct value
    {
        ulong timeStamp;
        ulong price;
        ulong marketcap;
        double volume_24h;
        double changedPercent_1h;
        double changedPercent_24h;
    };
    value lastValue;
    QVector<value> allValues;
public:
    explicit Coin(QString name, QString symbol);
    QString getName() const;
    void setName(const QString &value);
    QString getSymbol() const;
    void setSymbol(const QString &value);
    QIcon getIcon() const;
    void setIcon(const QIcon &value);
    long getAvailable_supply() const;
    void setAvailable_supply(long value);
};

#endif // COIN_H
