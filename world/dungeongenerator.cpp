#include "dungeongenerator.h"
#include "floortile.h"
#include "gold.h"
#include "monster.h"
#include "obstacle.h"
#include "randomizer.h"
#include "constants.h"

#include <QDebug>
#include <QList>
#include <math.h>


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

Dungeon *DungeonGenerator:: generateRooms()
{
    fillMap();

    int centerWidth = ((double)m_model->rowCount() / (double) 2);
    int centerHeight = ((double)m_model->columnCount() / (double) 2);
    QModelIndex roomIndex = m_model->index(centerWidth, centerHeight);
    qDebug() << "central room starting index" << roomIndex;

    //set central room index
    QPair<QModelIndex, Direction> coordinates; //index relevant for dungeon creation
    coordinates.first = roomIndex;
    coordinates.second = NoDirection;

    //create central room

    qDebug()<<"building CENTRAL ROOM";
    coordinates.first = createRoom(coordinates, 3, 3);

    //Setting up generator
    Randomizer rd;
    int totalFailCounter = 0;
    int failStreakCounter = 0;
    while((checkObstacleDensity() > 0.6) && (totalFailCounter < 5000))
    {
        qDebug()<< "OBSTACLE DENSITY" << checkObstacleDensity();
        qDebug()<< "FAILCOUNTER" << totalFailCounter;

        coordinates = selectWall(coordinates.first, (Direction)rd.randInt(Up,Right));

        switch (rd.randInt(Room, Corridor)) {
        case Room:
        {
            QPair<QModelIndex, Direction> tempCoordinates = coordinates;
            if(!checkForCorridorSpace(tempCoordinates, 1))
            {
                int height = rd.randInt(2,4);
                int width = rd.randInt(2,4);
                if(!checkForRoomSpace(tempCoordinates, height, width))
                {
                    coordinates.first = createCorridor(coordinates, 1);
                    coordinates = selectWall(coordinates.first, coordinates.second);
                    coordinates.first = createRoom(coordinates, height, width);

                    failStreakCounter = 0;
                }
            }
            else //failsafe
            {
                totalFailCounter++;
                failStreakCounter++;
            }
            break;
        }
        case Corridor:
        {
            QPair<QModelIndex, Direction> tempCoordinates = coordinates;
            int length = rd.randInt(3, 5);
            if(!checkForCorridorSpace(tempCoordinates, length))
            {
                if(!checkForCorridorSpace(tempCoordinates, length))
                {
                    coordinates.first = createCorridor(coordinates, length);

                    failStreakCounter = 0;
                }
            }
            else //failsafe
            {
                totalFailCounter++;
                failStreakCounter++;
            }
            break;
        }
            break;
        default:
            break;
        }

        if(failStreakCounter > 10)
        {
            coordinates.first = roomIndex;
            coordinates.second = NoDirection;
            failStreakCounter = 0;
            qDebug()<<"Failstreak reset";
        }else
        {
            qDebug()<<"No Failstreak reset";
        }
    }
    placeTreasure(5);
    placeMonster(1);
    qDebug()<<"DONE CREATING";
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
            if(m_dungeon->isFloor(m_model->index(row, column))){
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



        if(m_dungeon->isFloor(m_model->index(row, column))){
            m_dungeon->createObjectAtIndex(m_model->index(row, column), new Monster);
            monsterCount++;
        }
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
            if(m_dungeon->isWall(neighbour))
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

QModelIndex DungeonGenerator::createRoom(QPair<QModelIndex, Direction> startingPoint, int height, int width)
{
    QModelIndex roomIndex = startingPoint.first;

    int referenceHeight = height/2;
    int referenceWidth = width/2;

    int roundedReferenceHeight = round((double)(height)/(double)(2));
    int roundedReferenceWidth  = round((double)(width)/(double)(2));

    switch (startingPoint.second) {
    case Up:
        for(int row = roomIndex.row(); row > roomIndex.row() - height; row--)
            for(int column = roomIndex.column()- referenceWidth; column < roomIndex.column() + roundedReferenceWidth; column++)
                m_dungeon->createObjectAtIndex(m_model->index(row, column), new FloorTile);
        break;
    case Down:
        for(int row = roomIndex.row(); row < roomIndex.row() + height; row++)
            for(int column = roomIndex.column()- referenceWidth; column < roomIndex.column() + roundedReferenceWidth; column++)
                m_dungeon->createObjectAtIndex(m_model->index(row, column), new FloorTile);
        break;
    case Left:
        for(int row = roomIndex.row() - referenceHeight; row < roomIndex.row() + roundedReferenceHeight; row++)
            for(int column = roomIndex.column(); column > roomIndex.column() - width; column--)
                m_dungeon->createObjectAtIndex(m_model->index(row, column), new FloorTile);
        break;
    case Right:
        for(int row = roomIndex.row() - referenceHeight; row < roomIndex.row() + roundedReferenceHeight; row++)
            for(int column = roomIndex.column(); column < roomIndex.column() + width; column++)
                m_dungeon->createObjectAtIndex(m_model->index(row, column), new FloorTile);
        break;
    default:
        for(int row = roomIndex.row() - referenceHeight; row < roomIndex.row() + roundedReferenceHeight; row++)
            for(int column = roomIndex.column() - referenceWidth; column < roomIndex.column() + roundedReferenceWidth; column++)
                m_dungeon->createObjectAtIndex(m_model->index(row, column), new FloorTile);
        break;
    }
    qDebug() << "roomsize:" << height << "by" << width;
    qDebug() << "roomIndex" <<roomIndex;
    return roomIndex;
}

QPair<QModelIndex, Direction> DungeonGenerator::selectWall(const QModelIndex &startIndex, Direction direction)
{
    QPair<QModelIndex, Direction> coordinates;
    //    bool isWall = false;

    QModelIndex floorIndex = startIndex;

    switch (direction) {
    case Up:
        coordinates.second = Up;
        while(!m_dungeon->isWall(floorIndex))
            floorIndex = m_model->index(floorIndex.row() - 1, floorIndex.column());
        if(indexAtBorder(floorIndex))
            floorIndex = m_model->index(floorIndex.row() + 1, floorIndex.column());
        //            isWall = m_dungeon->isWall(floorIndex);

        break;
    case Down:
        coordinates.second = Down;
        while(!m_dungeon->isWall(floorIndex))
            floorIndex = m_model->index(floorIndex.row() + 1, floorIndex.column());
        if(indexAtBorder(floorIndex))
            floorIndex = m_model->index(floorIndex.row() - 1, floorIndex.column());

        //            isWall = m_dungeon->isWall(floorIndex);
        break;
    case Left:
        coordinates.second = Left;
        while(!m_dungeon->isWall(floorIndex))
            floorIndex = m_model->index(floorIndex.row(), floorIndex.column() - 1);
        if(indexAtBorder(floorIndex))
            floorIndex = m_model->index(floorIndex.row(), floorIndex.column() + 1);

        //            isWall = m_dungeon->isWall(floorIndex);
        break;
    case Right:
        coordinates.second = Right;
        while(!m_dungeon->isWall(floorIndex))
            floorIndex = m_model->index(floorIndex.row(), floorIndex.column() + 1);
        if(indexAtBorder(floorIndex))
            floorIndex = m_model->index(floorIndex.row(), floorIndex.column() - 1);
        //            isWall = m_dungeon->isWall(floorIndex);
        break;
    default:
        break;
    }


    coordinates.first = floorIndex;
    qDebug()<< "selected wall: " << coordinates;
    return coordinates;
}

QModelIndex DungeonGenerator::createCorridor(QPair<QModelIndex, Direction> startingPoint, int length)
{
    QModelIndex corridorIndex = startingPoint.first;
    if(length > 0)
    {
        m_dungeon->createObjectAtIndex(corridorIndex, new FloorTile);
        switch (startingPoint.second) {
        case Up:
            for(int i = 0; i < length - 1; i++){
                corridorIndex = m_model->index(corridorIndex.row() - 1, corridorIndex.column());
                m_dungeon->createObjectAtIndex(corridorIndex, new FloorTile);
            }
            break;
        case Down:
            for(int i = 0; i < length - 1; i++){
                corridorIndex = m_model->index(corridorIndex.row() + 1, corridorIndex.column());
                m_dungeon->createObjectAtIndex(corridorIndex, new FloorTile);
            }
            break;
        case Left:
            qDebug() << "building corridor to the left";
            for(int i = 0; i < length - 1; i++){
                corridorIndex = m_model->index(corridorIndex.row(), corridorIndex.column() - 1);
                m_dungeon->createObjectAtIndex(corridorIndex, new FloorTile);
            }
            break;
        case Right:
            for(int i = 0; i < length - 1; i++){
                corridorIndex = m_model->index(corridorIndex.row(), corridorIndex.column() + 1);
                m_dungeon->createObjectAtIndex(corridorIndex, new FloorTile);
            }
            break;
        default:
            break;
        }
        qDebug()<< "startIndex & Direction of corridor" << startingPoint;
        qDebug()<< "length of corridor: " << length;
        qDebug()<< "endindex of corridor: " << corridorIndex;
    }


    return corridorIndex;
}

bool DungeonGenerator::checkForRoomSpace(QPair<QModelIndex, Direction> checkCoordinates, int height, int width)

{
    //untere Grenze
    int referenceHeight = height/2;
    int referenceWidth = width/2;

    //obere Grenze
    int roundedReferenceHeight = round((double)(height)/(double)(2));
    int roundedReferenceWidth  = round((double)(width)/(double)(2));

    QModelIndex roomIndex = checkCoordinates.first;

    switch (checkCoordinates.second) {
    case Up:
        for(int row = roomIndex.row(); row > roomIndex.row() - height - 1; row--)
            for(int column = (roomIndex.column() - referenceWidth) - 1; column < (roomIndex.column() + roundedReferenceWidth) + 1; column++)
            {
                qDebug()<< m_model->index(row, column);
                if(!m_dungeon->isWall(m_model->index(row, column)) || indexAtBorder(m_model->index(row, column)))
                {
                    qDebug() << "NOT enough space for roomcreation";
                    return true;
                }
            }
        break;
    case Down:
        for(int row = roomIndex.row(); row < (roomIndex.row() + height) + 1; row++)
            for(int column = (roomIndex.column()- referenceWidth) - 1; column < (roomIndex.column() + roundedReferenceWidth) + 1; column++)
            {
                qDebug() << m_model->index(row, column);
                if(!m_dungeon->isWall(m_model->index(row, column)) || indexAtBorder(m_model->index(row, column)))
                {
                    qDebug() << "NOT enough space for roomcreation";
                    return true;
                }
            }
        break;
    case Left:
        for(int column = roomIndex.column(); column > roomIndex.column() - width - 1; column--)
            for(int row = (roomIndex.row() - referenceHeight - 1); row < (roomIndex.row() + roundedReferenceHeight + 1); row++)
            {
                qDebug() << m_model->index(row, column);
                if(!m_dungeon->isWall(m_model->index(row, column)) || indexAtBorder(m_model->index(row, column)))
                {
                    qDebug() << "NOT enough space for roomcreation";
                    return true;
                }
            }
        break;
    case Right:
        for(int column = roomIndex.column(); column < roomIndex.column() + width + 1; column++)
            for(int row = (roomIndex.row() - referenceHeight) - 1; row < (roomIndex.row() + roundedReferenceHeight) + 1; row++)
            {
                qDebug() << m_model->index(row, column);
                if(!m_dungeon->isWall(m_model->index(row, column)) || indexAtBorder(m_model->index(row, column)))
                {
                    qDebug() << "NOT enough space for roomcreation";
                    return true;
                }
            }
        break;
    default:
        qDebug() << "DEFAULT STATE: enough space for roomcreation";
        return false;
    }
    qDebug() << "enough space for roomcreation";
    return false;
}

bool DungeonGenerator::checkForCorridorSpace(QPair<QModelIndex, Direction> checkCoordinates, int length)
{
    qDebug()<<"length of corridor:"<<length;
    QModelIndex roomIndex = checkCoordinates.first;
    switch (checkCoordinates.second) {
    case Up:
        for(int row = roomIndex.row(); row > roomIndex.row() - length; row--)
            for(int column = roomIndex.column() - 1; column <= roomIndex.column() + 1; column++)
            {
                qDebug() << m_model->index(row,column);
                {
                    if(!m_dungeon->isWall(m_model->index(row, column)) || indexAtBorder(m_model->index(row, column)))
                    {
                        qDebug() << "NOT enough space for corridorcreation";
                        return true;
                    }
                }
            }
        break;
    case Down:
        for(int row = roomIndex.row(); row < roomIndex.row() + length; row++)
            for(int column = roomIndex.column() - 1; column <= roomIndex.column() + 1; column++)
                if(!m_dungeon->isWall(m_model->index(row, column)) || indexAtBorder(m_model->index(row, column)))
                {
                    qDebug() << m_model->index(row,column);
                    {
                        qDebug() << "NOT enough space for corridorcreation";
                        return true;
                    }
                }
        break;
    case Left:
        for(int column = roomIndex.column(); column > roomIndex.column() - length; column--)
            for(int row = roomIndex.row() - 1; row <= roomIndex.row() + 1; row++)
            {
                qDebug() << m_model->index(row,column);
                if(!m_dungeon->isWall(m_model->index(row, column)) || indexAtBorder(m_model->index(row, column)))
                {
                    qDebug() << "NOT enough space for corridorcreation";
                    return true;
                }
            }
        break;
    case Right:
        for(int column = roomIndex.column(); column < roomIndex.column() + length; column++)
            for(int row = roomIndex.row() - 1; row <= roomIndex.row() + 1; row++)
            {
                qDebug() << m_model->index(row,column);

                if(!m_dungeon->isWall(m_model->index(row, column)) || indexAtBorder(m_model->index(row, column)))
                {
                    qDebug() << "NOT enough space for corridorcreation";
                    return true;
                }
            }
        break;
    default:
        qDebug() << "DEFAULT STATE: enough space for corridorcreation";
        return false;
    }
    qDebug() << "enough space for corridorcreation";
    return false;
}

bool DungeonGenerator::indexAtBorder(const QModelIndex &checkIndex)
{
    if (checkIndex.row() <= 0
            || checkIndex.row() >= m_model->rowCount() - 1
            || checkIndex.column() <= 0
            || checkIndex.column() >= m_model->columnCount() - 1)
        return true;
    else return false;
}

double DungeonGenerator::checkObstacleDensity()
{
    double obstacleCount = 0;
    for(int row = 0; row < m_model->rowCount(); row++)
        for(int column = 0; column < m_model->columnCount(); column++)
            if(m_dungeon->isWall(m_model->index(row, column)))
                obstacleCount++;
    return obstacleCount / (m_model->rowCount() * m_model->columnCount());
}
