#include "monster.h"

Monster::Monster(QObject *parent)
    : AbstractNPC(parent)
{
    QList<Direction> directions;
    directions << Up
               << Right
               << Down
               << Left;
    m_moveset.setDirectionList(directions);
}

QChar Monster::appearance() const
{
    return 'X';
}


bool Monster::isHostile() const
{
    return true;
}

bool Monster::isMovable() const
{
    return true;
}

