#ifndef ABSTRACTNPC_H
#define ABSTRACTNPC_H

#include "abstractcombatitem.h"
#include "constants.h"
#include "moveset.h"

class AbstractNPC : public AbstractCombatItem
{
    Q_OBJECT
    typedef AbstractCombatItem SUPER;

public:
    AbstractNPC(QObject *parent = 0);

public:
    bool isPassable() const final;
    bool isCollectible() const final;

    virtual bool isHostile() const = 0;
    virtual bool isMovable() const = 0;

    Direction nextDirection();

    void onMoved();

protected:
    MoveSet m_moveset;
};

#endif // ABSTRACTNPC_H