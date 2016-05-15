#include "dungeongenerator.h"
#include "gold.h"
#include "obstacle.h"
#include "randomizer.h"

#include <QDebug>

DungeonGenerator::DungeonGenerator(QAbstractItemModel *model, QObject *parent) : QObject(parent)
{
    m_model = model;
}

QHash<QModelIndex, AbstractMapItem *> DungeonGenerator::generateDungeon()
{
    QHash<QModelIndex, AbstractMapItem *> dungeon;

    createRandom(dungeon);

    foreach (QModelIndex index, dungeon.keys()) {
        qDebug() << QString("test index %1, %2: %3").arg(index.row()).arg(index.column()).arg(dungeon.contains(index));
    }

    smoothOutDungeon(dungeon);
    smoothOutDungeon(dungeon);

    return dungeon;
}

void DungeonGenerator::createRandom(QHash<QModelIndex, AbstractMapItem *> &hash)
{   //First Iteration
    QList<QModelIndex> allIdx = getAllIndexes();


    Randomizer rd;

    foreach (const QModelIndex& index, allIdx) {

        int random = rd.randInt(0,1);
        if(random == 1)
            hash.insert(index, new Obstacle());
    }
}

void DungeonGenerator::smoothOutDungeon(QHash<QModelIndex, AbstractMapItem *> &hash)
{
    QHash<QModelIndex, AbstractMapItem*> smoothDungeon;
    foreach (const QModelIndex& index, getAllIndexes()) {
        if (obstaclesInPattern(index, hash) >= 5)
            smoothDungeon.insert(index, new Obstacle());
    }
    hash = smoothDungeon;
}

void DungeonGenerator::createObjects(QHash<QModelIndex, AbstractMapItem *> &hash, int goldCount)
{
    QList<QModelIndex> allIdx;
    for (int row = 0; row < m_model->rowCount(); row++) {
        for (int column = 0; column < m_model->columnCount(); column++) {
            allIdx.append(m_model->index(row, column));
        }
    }

    Randomizer rd;

    int gold = 0;
    while(gold < goldCount ) {
        int random = rd.randInt(0, allIdx.size() - 1);
        QModelIndex randomIndex = allIdx.at(random);
        if(!hash.contains(randomIndex)){
            hash.insert(randomIndex, new Gold());
            gold++;
        }
    }
}

int DungeonGenerator::obstaclesInPattern(const QModelIndex &centerIndex, QHash<QModelIndex, AbstractMapItem *> &hash)
{
    int obstacleCounter = 0;
    for (int row = centerIndex.row() - 1; row < centerIndex.row() + 1; row++) {
        for (int column = centerIndex.column() - 1; column < centerIndex.column() + 1; column++) {

            QModelIndex index = m_model->index(row, column);

            //qDebug() << QString("test index %1, %2: %3").arg(index.row()).arg(index.column()).arg(hash.contains(index));

            if(hash.contains(index))
                obstacleCounter++;
        }
    }
    return obstacleCounter;
}

QList<QModelIndex> DungeonGenerator::getAllIndexes() const
{
    QList<QModelIndex> allIdx;
    for (int row = 0; row < m_model->rowCount(); row++) {
        for (int column = 0; column < m_model->columnCount(); column++) {
            allIdx.append(m_model->index(row, column));
        }
    }
    return allIdx;
}
