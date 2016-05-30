#ifndef ABSTRACTNPC_H
#define ABSTRACTNPC_H

#include "abstractcombatitem.h"
#include "constants.h"
#include "moveset.h"

/**
 * @brief The AbstractNPC class is a derivative of AbstractCombatItem and a base class for all npcs
 */
class AbstractNPC : public AbstractCombatItem
{
    Q_OBJECT
    typedef AbstractCombatItem SUPER;

public:
    /**
     * @brief constructs an AbstractNPC with the given parent
     */
    AbstractNPC(QObject *parent = 0);

public:
    /**
     * @brief checks if AbstractNPC is passable
     * @return true if passable, else returns false. Always false, since NPCs are never passable
     */
    bool isPassable() const final;

    /**
     * @brief checks if AbstractNPC is collectible
     * @return true if collectible, else returns false. Always false, since NPCs are never collectible
     */
    bool isCollectible() const final;

    /**
     * @brief checks if AbstractNPC is hostile
     * @return true if hostile, else returns false.
     */
    virtual bool isHostile() const = 0;

    /**
     * @brief checks if AbstractNPC is movable or stationary
     * @return true if movable, else returns false.
     */
    virtual bool isMovable() const = 0;

    /**
     * @brief returns current direction of NPC moveset
     * @return Direction enum
     */
    Direction nextDirection();

    /**
     * @brief calls nextDirection on movement
     */
    void onMoved();

protected:
    /**
     * @brief governs npc behaviour
     */
    MoveSet m_moveset;
};

#endif // ABSTRACTNPC_H
