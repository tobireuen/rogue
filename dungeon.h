#ifndef DUNGEON_H
#define DUNGEON_H

#include "abstractmapitem.h"

#include <QObject>
#include <QModelIndex>
#include <QHash>

class Dungeon : public QObject
{
    Q_OBJECT

signals:
    void objectRemoved(const QModelIndex &index);
    void objectAdded(const QModelIndex &index);

public:
    explicit Dungeon(QObject *parent = 0);

    void reset();

    AbstractMapItem* getObjectAtIndex(const QModelIndex &index);

    bool containsObjectAtIndex(const QModelIndex &index);

    void createObjectAtIndex(const QModelIndex &index, AbstractMapItem *itemType);
    void removeObjectAtIndex(const QModelIndex &index);

private:
    QHash<QModelIndex, AbstractMapItem*> m_objects;
};

#endif // DUNGEON_H
