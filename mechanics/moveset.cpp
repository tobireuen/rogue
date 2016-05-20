#include "moveset.h"

MoveSet::MoveSet(QObject *parent) : QObject(parent)
{
}

void MoveSet::setDirectionList(QList<Direction> directions)
{
    m_directionList = directions;
    m_iterator = m_directionList.begin();
}

Direction MoveSet::currentDirection() const
{
    return *m_iterator;
}

void MoveSet::nextDirection()
{
    if(m_iterator == m_directionList.end()-1)
        m_iterator = m_directionList.begin();
    else
        m_iterator++;
}
