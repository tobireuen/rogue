#ifndef ABSTRACTCOMBATITEM_H
#define ABSTRACTCOMBATITEM_H

#include "abstractmapitem.h"

class AbstractCombatItem : public AbstractMapItem
{
    Q_OBJECT
    typedef AbstractMapItem SUPER;

signals:
    void healthChanged(int health);
    void attackRatingChanged(int attackRating);
    void hitConnected();
    void died();

public:
    AbstractCombatItem(QObject * parent = 0);

    void hit(AbstractCombatItem * target);

    void getDamage(int damage);

    int health() const;
    int attackRating();

protected:
    void setHealth(int health);
    void setAttackRating(int attackRating);

private:
    int m_health = 0;
    int m_attackRating = 0;
};

#endif // ABSTRACTCOMBATITEM_H
