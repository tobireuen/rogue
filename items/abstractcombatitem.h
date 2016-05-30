#ifndef ABSTRACTCOMBATITEM_H
#define ABSTRACTCOMBATITEM_H

#include "abstractmapitem.h"

/**
 * @brief The AbstractCombatItem class is a derivative of AbstractMapItem and a base class for the Player and all moving combat enabled AbstractMapItems
 */
class AbstractCombatItem : public AbstractMapItem
{
    Q_OBJECT
    typedef AbstractMapItem SUPER;

signals:
    /**
     * @brief emits a signal when player health changes
     * @param health is amount of changed health
     */
    void healthChanged(int health);

    /**
     * @brief emits a signal when player attack rating changes
     * @param attackRating is amount of changed attack rating
     */
    void attackRatingChanged(int attackRating);

    /**
     * @brief emits a signal if a hit connects
     */
    void hitConnected();

    /**
     * @brief emits signal when AbstractCombatItem health reaches zero
     */
    void died();

public:
    /**
     * @brief constructs an AbstractCombatItem with given parent
     */
    AbstractCombatItem(QObject * parent = 0);

    /**
     * @brief calls getDamage method on target Item and subtracts attackRating
     * @param target is AbstractCombatItem to be attacked
     */
    void hit(AbstractCombatItem * target);

    /**
     * @brief displays info of hit and changes health according to damage
     * @param damage is decrement of health subtracted from total health
     */
    void getDamage(int damage);

    /**
     * @return current health of called combat item
     */
    int health() const;

    /**
     * @return current attack rating of called combat item
     */
    int attackRating();

protected:
    /**
     * @brief sets health of combat item and calls healthChanged
     * @param health is amount to which health will be set
     */
    void setHealth(int health);

    /**
     * @brief sets attack rating of combat item and calls attackRatingChanged
     * @param attack rating is amount to which attack rating will be set
     */
    void setAttackRating(int attackRating);

private:
    int m_health = 0;
    int m_attackRating = 0;
};

#endif // ABSTRACTCOMBATITEM_H
