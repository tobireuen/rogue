#ifndef ABSTRACTMAPITEM_H
#define ABSTRACTMAPITEM_H

#include <QObject>
#include <QChar>

class AbstractMapItem : public QObject
{
    Q_OBJECT

public:
    explicit AbstractMapItem(QObject *parent = 0);

    virtual QChar appearance() const = 0;
    virtual bool isPassable() const = 0;
    virtual bool isCollectible() const = 0;

};

#endif // ABSTRACTMAPITEM_H
