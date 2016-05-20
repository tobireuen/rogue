#include "dice.h"

Dice::Dice(int sides, QObject *parent) : SUPER(parent)
{
    m_sides = sides;
}

int Dice::rollDice()
{
    return randInt(1, m_sides);
}

int Dice::rollMultipleDice(int diceCount)
{
    int numberCount;
    for(int i; i < diceCount; i++)
        numberCount += rollDice();
    return numberCount;
}
