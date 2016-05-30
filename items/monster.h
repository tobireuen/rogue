#ifndef MONSTER_H
#define MONSTER_H

#include "abstractnpc.h"

class Monster : public AbstractNPC
{
    Q_OBJECT

public:
    /**
     * @brief constructs a Monster with given parent
     */
    Monster(QObject *parent = 0);

public:
    /**
     * @brief checks if Monster is hostile
     * @return true if hostile, else return false. Always returns true, since monsters are always hostile
     */
    bool isHostile() const;

    /**
     * @brief checks if Monster is movable or stationary
     * @return true if movable, else returns false.
     */
    bool isMovable() const;

    /**
     * @brief defines appearance of monster on map
     * @return char representing monster
     */
    QChar appearance() const;
};

#endif // MONSTER_H
