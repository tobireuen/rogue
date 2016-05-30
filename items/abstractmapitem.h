#ifndef ABSTRACTMAPITEM_H
#define ABSTRACTMAPITEM_H

#include <QObject>
#include <QChar>

/**
 * @brief The AbstractMapItem class is a base class for all items found on the map
 */
class AbstractMapItem : public QObject
{
    Q_OBJECT
    typedef QObject SUPER;

public:
    /**
     * @brief constructs an AbstractMapItem with given parent
     */
    explicit AbstractMapItem(QObject *parent = 0);

    /**
     * @brief defines appearance of map item on map
     * @return char representing map item
     */
    virtual QChar appearance() const = 0;

    /**
     * @brief checks if AbstractMapItem is passable
     * @return true if passable, else returns false
     */
    virtual bool isPassable() const = 0;

    /**
     * @brief checks if AbstractMapItem is collectible
     * @return true if collectible, else returns false
     */
    virtual bool isCollectible() const = 0;

};

#endif // ABSTRACTMAPITEM_H
