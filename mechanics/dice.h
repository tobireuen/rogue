#ifndef DICE_H
#define DICE_H

#include "randomizer.h"


/**
 * @brief The Dice class is a derivative of the randomizer class and represents a dice roll
 */
class Dice : public Randomizer
{
    Q_OBJECT
    typedef Randomizer SUPER;

public:
    /**
     * @brief constructs a Dice with given parent
     * @param sides
     */
    Dice(int sides, QObject *parent = 0);

    /**
     * @brief rolls Dice
     * @return result of dice throw
     */
    int rollDice();

    /**
     * @brief roll more than one dice
     * @param diceCount is number of thrown dice
     * @return sum of dice rolls
     */
    int rollMultipleDice(int diceCount);

private:
    int m_sides;
};

#endif // DICE_H
