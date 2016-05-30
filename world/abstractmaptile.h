#ifndef ABSTRACTMAPTILE_H
#define ABSTRACTMAPTILE_H

#include <abstractmapitem.h>

/**
 * @brief The AbstractMapTile class is a derivative of AbstractMapItem and a baseclass for all passable floortiles
 */
class AbstractMapTile : public AbstractMapItem
{
    Q_OBJECT
    typedef AbstractMapItem SUPER;
public:
    /**
     * @brief constructs an AbstractMapTile with given parent
     */
    AbstractMapTile(QObject * parent = 0);

    /**
     * @brief is called when entered by player
     * @return true if entered, else return false
     */
    virtual bool onEntered() const = 0;

    /**
     * @brief checks if floortile is passable
     * @return true if passable, else returns false. Returns true, since AbstractMapTiles are always passable
     */
    bool isPassable() const;

    /**
     * @brief checks if derivative of AbstractMapTile is collectible
     * @return true if collectible, else returns false. Returns false, since AbstractMapTiles are never collectible
     */
    bool isCollectible() const;
};

#endif // ABSTRACTMAPTILE_H
