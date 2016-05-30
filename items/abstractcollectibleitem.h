#ifndef ABSTRACTCOLLECTIBLEITEM_H
#define ABSTRACTCOLLECTIBLEITEM_H

#include "abstractmaptile.h"

/**
 * @brief The AbstractCollectibleItem class is derivative of the AbstractMapTile class and a baseclass for various collectible items
 */
class AbstractCollectibleItem : public AbstractMapTile
{
    Q_OBJECT
    typedef AbstractMapTile SUPER;

public:
    /**
     * @brief Constructs an AbstractCollectibleItem with the given parent
     */
    AbstractCollectibleItem(QObject * parent = 0);

    /**
     * @brief checks if derivative of AbstractMapItem is passable
     * @return true if passable, else returns false
     */
    virtual bool isPassable() const final;

    /**
     * @brief checks if derivative of AbstractMapItem is collectible
     * @return true if collectible, else returns false
     */
    virtual bool isCollectible() const final;

    /**
     * @brief is called when entered by player
     * @return true if entered, else return false
     */
    virtual bool onEntered() const = 0;
};

#endif // ABSTRACTCOLLECTIBLEITEM_H
