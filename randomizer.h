#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <QObject>

class Randomizer : public QObject
{
    Q_OBJECT
public:
    explicit Randomizer(QObject *parent = 0);

    int randInt(int low, int high) const;
    double randDouble(double low, double high) const;

};

#endif // RANDOMIZER_H
