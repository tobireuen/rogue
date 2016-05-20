#ifndef MONSTER_H
#define MONSTER_H

#include "abstractnpc.h"

class Monster : public AbstractNPC
{
    Q_OBJECT

public:
    Monster(QObject *parent = 0);

public:
    bool isHostile() const;
    bool isMovable() const;

    QChar appearance() const;
};

#endif // MONSTER_H
