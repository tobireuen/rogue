#include "dungeongenerator.h"

DungeonGenerator::DungeonGenerator(QAbstractItemModel *model, QObject *parent) : QObject(parent)
{
    m_model = model;
}

QHash<QModelIndex, AbstractMapItem *> DungeonGenerator::generateDungeon()
{
    QHash<QModelIndex, AbstractMapItem *> dungeon;

    createRandom(dungeon);


}

void DungeonGenerator::createRandom(QHash<QModelIndex, AbstractMapItem *> &hash)
{
    //QList<QModelIndex> allIdx;
    //for (int row = 0; row < rowCount(); row++) {
    //    for (int column = 0; column < columnCount(); column++) {
    //        allIdx.append(index(row, column));
    //    }
    //}
    //
    //Randomizer rd;
    //
    //foreach (const QModelIndex& index, allIdx) {
    //
    //    int random = rd.randInt(0, allIdx.size() - 1);
    //    QModelIndex randomIndex = allIdx.at(random);
    //
    //    if(!m_objects.contains(randomIndex)){
    //        m_objects.insert(randomIndex, new Obstacle());
    //        obstacles++;
    //    }
    //}
}
