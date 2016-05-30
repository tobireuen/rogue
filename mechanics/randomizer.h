#ifndef RANDOMIZER_H
#define RANDOMIZER_H

#include <QObject>
/**
 * @brief The Randomizer class provides methods to generate random numbers within a given interval.
 */
class Randomizer : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief constructs a Randomizer with given parent
     */
    explicit Randomizer(QObject *parent = 0);

    /**
     * @brief generates a random integer between the given borders
     * @param low is lower border
     * @param high is higher border
     * @return random integer between high and low
     */
    int randInt(int low, int high) const;

    /**
     * @brief generates a random double between the given borders
     * @param low is lower border
     * @param high is higher border
     * @return random double between high and low
     */
    double randDouble(double low, double high) const;

};

#endif // RANDOMIZER_H
