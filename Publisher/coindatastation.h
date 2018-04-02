#ifndef COINDATASTATION_H
#define COINDATASTATION_H

#include <QObject>

class CoinDataStation : public QObject
{
    Q_OBJECT
public:
    explicit CoinDataStation(QObject *parent = nullptr);

signals:

public slots:
};

#endif // COINDATASTATION_H