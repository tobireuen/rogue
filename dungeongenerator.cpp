#include "dungeongenerator.h"
#include "gold.h"
#include "obstacle.h"
#include "randomizer.h"

#include <QDebug>


DungeonGenerator::DungeonGenerator(QAbstractItemModel *model, QObject *parent) : QObject(parent)
{
    m_model = model;
    m_dungeon = new Dungeon;
}

Dungeon *DungeonGenerator::generate()
{
    initialiseMap(0.5);
    tweakDungeon(4, 3, 5);
    createBorders();
    placeTreasure(5);
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
                if(countAliveNeighbours(index) > deathlimit)
                    newDungeon->createObjectAtIndex(index, new Obstacle);
            }
            else {
                if(countAliveNeighbours(index) > birthlimit)
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

