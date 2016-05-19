#ifndef MOVESET_H
#define MOVESET_H

#include "constants.h"

#include <QObject>

class MoveSet : public QObject
{
    Q_OBJECT
public:
    explicit MoveSet(QObject *parent = 0);

    void setDirectionList(QList<Direction> directions);

    Direction currentDirection() const;
    void nextDirection();

private:
    QList<Direction> m_directionList;
    QList<Direction>::const_iterator m_iterator;
};

#endif // MOVESET_H
