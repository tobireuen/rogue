#ifndef GOLD_H
#define GOLD_H

#include "abstractcollectibleitem.h"

class Gold : public AbstractCollectibleItem
{
    Q_OBJECT
public:
    /**
     * @brief constructs a Gold item with given parent
     */
    Gold(QObject *parent = 0);

    /**
     * @brief when entered by player adds gold to player inventory
     * @return true if entered, else returns false
     */
    virtual bool onEntered() const final;

    /**
     * @brief defines appearance of gold on map
     * @return char representing gold
     */
    virtual QChar appearance() const;
};

#endif // GOLD_H
