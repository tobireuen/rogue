#ifndef DICE_H
#define DICE_H

#include "randomizer.h"



class Dice : public Randomizer
{
    Q_OBJECT
    typedef Randomizer SUPER;

public:
    Dice(int sides, QObject *parent = 0);

    int rollDice();
    int rollMultipleDice(int diceCount);

private:
    int m_sides;
};

#endif // DICE_H
