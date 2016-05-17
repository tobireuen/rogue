#include "dungeon.h"

Dungeon::Dungeon(QObject *parent) : QObject(parent)
{
}

void Dungeon::reset()
{
    foreach (const QModelIndex &index, m_objects.keys())
        removeObjectAtIndex(index);

}

AbstractMapItem *Dungeon::getObjectAtIndex(const QModelIndex &index)
{
    return m_objects.value(index, 0);
}

bool Dungeon::containsObjectAtIndex(const QModelIndex &index)
{
    if(getObjectAtIndex(index) == 0)
        return false;
    else
        return true;
}

void Dungeon::setObjectAtIndex(const QModelIndex &index, AbstractMapItem *itemType)
{
    if(!index.isValid())
        return;

    m_objects.insert(index, itemType);
    emit objectAdded(index);
}

void Dungeon::removeObjectAtIndex(const QModelIndex &index)
{
    delete m_objects.take(index);
    emit objectRemoved(index);
}
