#include "dungeongenerator.h"
#include "gold.h"
#include "monster.h"
#include "obstacle.h"
#include "randomizer.h"

#include <QDebug>
#include <QList>


DungeonGenerator::DungeonGenerator(QAbstractItemModel *model, QObject *parent) : QObject(parent)
{
    m_model = model;
    m_dungeon = new Dungeon;
}

Dungeon *DungeonGenerator::generateCaves()
{
    //    initialiseMap(0.5);
    //    tweakDungeon(4, 5, 5);
    createBorders();

    placeTreasure(5);
    placeMonster(1);
    return m_dungeon;
}

Dungeon *DungeonGenerator::generateRooms()
{
    fillMap();
    int centerWidth = m_model->rowCount() / 2;
    int centerHeight = m_model->columnCount() / 2;
    createRoom(m_model->index(centerWidth, centerHeight), 3, 3);
    return m_dungeon;
}

void DungeonGenerator::initialiseMap(double obstacleChance)
{
    Randomizer rd;
    for (int row = 0; row < m_model->rowCount(); row++)
        for (int column = 0; column < m_model->columnCount(); column++)
            if( rd.randDouble(0,1) < obstacleChance)
                m_dungeon->createObjectAtIndex(m_model->index(row, column), new Obstacle(m_dungeon));
}

void DungeonGenerator::smoothOutDungeon(int birthlimit, int deathlimit)
{
    Dungeon* newDungeon = new Dungeon;
    for (int row = 0; row < m_model->rowCount(); row++)
        for (int column = 0; column < m_model->columnCount(); column++){
            QModelIndex index = m_model->index(row, column);
            if(m_dungeon->containsObjectAtIndex(index)){
                if(countAliveNeighbours(index) >= deathlimit)
                    newDungeon->createObjectAtIndex(index, new Obstacle);
            }
            else {
                if(countAliveNeighbours(index) >= birthlimit)
                    newDungeon->createObjectAtIndex(index, new Obstacle);
            }
        }
    delete m_dungeon;
    m_dungeon = newDungeon;
}

void DungeonGenerator::createBorders()
{
    for (int row = 0; row < m_model->rowCount(); row++)
        for (int column = 0; column < m_model->columnCount(); column++)
            if(row == 0 || row == m_model->rowCount() - 1 || column == 0 || column == m_model->columnCount()- 1)
                m_dungeon->createObjectAtIndex(m_model->index(row, column), new Obstacle(m_dungeon));
}

void DungeonGenerator::tweakDungeon(int birthlimit, int deathlimit, int steps)
{
    for (int i = 0; i < steps; i++)
        smoothOutDungeon(birthlimit, deathlimit);
}

void DungeonGenerator::placeTreasure(int hiddenTreasureLimit)
{
    for (int row = 0; row < m_model->rowCount(); row++)
        for (int column = 0; column < m_model->columnCount(); column++)
            if(!m_dungeon->containsObjectAtIndex(m_model->index(row, column))){
                if(countAliveNeighbours(m_model->index(row, column)) >= hiddenTreasureLimit)
                    m_dungeon->createObjectAtIndex(m_model->index(row, column), new Gold);
            }
}

void DungeonGenerator::placeMonster(int monsterLimit)
{
    Randomizer rd;
    int row;
    int column;
    int monsterCount = 0;

    while(monsterCount < monsterLimit){
        row = rd.randInt(0, m_model->rowCount());
        column = rd.randInt(0, m_model->columnCount());
        if(!m_dungeon->containsObjectAtIndex(m_model->index(row, column))){
            m_dungeon->createObjectAtIndex(m_model->index(row, column), new Monster);
            monsterCount++;
        }
    }
}

void DungeonGenerator::floodfill()
{
    QModelIndex firstFreeIndex;

    for (int row = 0; row < m_model->rowCount() && !firstFreeIndex.isValid(); row++) {
        for (int column = 0; column < m_model->columnCount() && !firstFreeIndex.isValid(); column++) {
            QModelIndex current = m_model->index(row, column);
            if (!m_dungeon->containsObjectAtIndex(current))
                firstFreeIndex = current;
        }
    }

    QHash <QModelIndex, bool> floodIndex;
    colorIndex(floodIndex, firstFreeIndex);
    qDebug() << floodIndex.size();
}

void DungeonGenerator::colorIndex(QHash<QModelIndex, bool> &hash, const QModelIndex &index)
{
    if(!index.isValid() || index.row() >= m_model->rowCount() || index.column() >= m_model->columnCount())
        return;

    if(hash.value(index, false))
        return;

    if(m_dungeon->containsObjectAtIndex(index))
        return;

    hash.insert(index, true);

    colorIndex(hash, m_model->index(index.row() + 1, index.column()));
    colorIndex(hash, m_model->index(index.row() - 1, index.column()));
    colorIndex(hash, m_model->index(index.row(), index.column() + 1));
    colorIndex(hash, m_model->index(index.row(), index.column() - 1));
}

int DungeonGenerator::countAliveNeighbours(const QModelIndex &index)
{
    int count = 0;
    for (int row = index.row() - 1; row <= index.row() + 1; row++)
        for (int column = index.column() - 1; column <= index.column() + 1; column++){
            QModelIndex neighbour = m_model->index(row, column);
            if(!index.isValid() || index == neighbour)
                continue;
            if(m_dungeon->containsObjectAtIndex(neighbour))
                count++;
        }
    return count;
}

void DungeonGenerator::fillMap()
{
    for (int row = 0; row < m_model->rowCount(); row++)
        for (int column = 0; column < m_model->columnCount(); column++)
            m_dungeon->createObjectAtIndex(m_model->index(row, column), new Obstacle(m_dungeon));
}

void DungeonGenerator::createRoom(const QModelIndex &start, int width, int height)
{
    for(int row = start.row(); row < start.row() + width; row++)
        for(int column = start.column(); column < start.column() + height; column++)
            m_dungeon->removeObjectAtIndex(m_model->index(row, column));
}

