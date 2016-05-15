#ifndef DUNGEONGENERATOR_H
#define DUNGEONGENERATOR_H

#include "abstractmapitem.h"

#include <QAbstractItemModel>
#include <QObject>
#include <QList>
#include <QModelIndex>

class DungeonGenerator : public QObject
{
    Q_OBJECT
public:
    explicit DungeonGenerator(QAbstractItemModel *model, QObject *parent = 0);

    QHash<QModelIndex, AbstractMapItem*> generateDungeon();

private:
    void createRandom(QHash<QModelIndex, AbstractMapItem*>& hash);
    void smoothOutDungeon(QHash<QModelIndex, AbstractMapItem*>& hash);
    void createObjects(QHash<QModelIndex, AbstractMapItem *> &hash, int goldCount);

    int obstaclesInPattern(const QModelIndex &centerIndex, QHash<QModelIndex, AbstractMapItem *> &hash);

    QList<QModelIndex> getAllIndexes() const;

private:
    QAbstractItemModel *m_model;
};

#endif // DUNGEONGENERATOR_H
