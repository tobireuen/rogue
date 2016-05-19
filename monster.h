#ifndef MONSTER_H
#define MONSTER_H

#include "abstractnpc.h"

class Monster : public AbstractNPC
{
    Q_OBJECT

signals:
    void healthChanged(int health);
    void monsterDied();

public:
    Monster(QObject *parent = 0);

public:
    bool isHostile() const;
    bool isMovable() const;

    QChar appearance() const;

protected:
    void setHealth(int health);

private:
    int m_health = 10;
};

#endif // MONSTER_H
