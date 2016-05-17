#include "randomizer.h"
#include <QTime>

Randomizer::Randomizer(QObject *parent) : QObject(parent)
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
}
int Randomizer::randInt(int low, int high) const
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

double Randomizer::randDouble(double low, double high) const
{
    return randInt(low*100,high*100) / 100.0;
}
