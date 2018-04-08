#ifndef COIN_H
#define COIN_H
#include <QString>
#include <QIcon>
#include <QVector>
#include <QListWidgetItem>
#include <QtDebug>
#include <QDateTime>
#include <memory>
using std::shared_ptr;
using std::make_shared;
using QListWidgetItemPtr = shared_ptr<QListWidgetItem>;
using ulong = unsigned long;
class Coin
{
private:
    QString name;
    QString symbol;
    QListWidgetItemPtr displayItem;
    long available_supply;
    struct value
    {
        QDateTime timeStamp;
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
    long getAvailable_supply() const;
    void setAvailable_supply(long value);
    QListWidgetItemPtr& getRefDisplayItem();
    void setDisplayItem(const QListWidgetItemPtr &value);
    ~Coin();
    QListWidgetItemPtr getDisplayItem() const;
    value& getLastValue();
    void setLastValue(const value &value);
};

#endif // COIN_H
