#include "MapModel.h"
#include "randomizer.h"
#include "player.h"
#include "obstacle.h"
#include "gold.h"

#include <QSize>
#include <QDebug>
#include <QtGlobal>
#include <QFont>

MapModel::MapModel(QObject *parent)
    : SUPER(parent)
{
    connect(Player::instance(), &Player::moved, this, &MapModel::onPlayerMoved);
}

MapModel::MapModel(int rowCount, int columnCount, int obstacleCount, QObject *parent)
    : MapModel(parent)
{
    init(rowCount, columnCount, obstacleCount);
}

QVariant MapModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return section;
}

int MapModel::rowCount(const QModelIndex &parent) const
{
    return m_rowCount;
}

int MapModel::columnCount(const QModelIndex &parent) const
{
    return m_columnCount;
}

QVariant MapModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        if (index.row() == Player::instance()->row() && index.column() == Player::instance()->column())
            return "@";
        else if(m_objects.contains(index))
            return m_objects.value(index)->appearance();
        break;
    case Qt::SizeHintRole:
        return QSize(5, 5);
        break;
    case Qt::TextAlignmentRole:
        return Qt::AlignCenter;
        break;
    case Qt::ToolTipRole:
        return QString("%1, %2").arg(index.row()).arg(index.column());
        break;
    case Qt::FontRole: {
        QFont font;
        font.setPointSize(6);
        return font;
    }
    default:
        break;
    }

    return QVariant();
}

Qt::ItemFlags MapModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEnabled;
}

bool MapModel::movePlayer(MapModel::Direction direction)
{
    if (direction == Up || direction == Down){
        int addend = (direction == Up ? -1 : 1);
        QModelIndex newIndex = index(Player::instance()->row() + addend, Player::instance()->column());

        //Object on newIndex?
        if(m_objects.contains(newIndex)) {
            if (!m_objects.value(newIndex)->isPassable())
                return false;
        }

        if (Player::instance()->row() + addend < 0)
            return false;

        Player::instance()->setRow(Player::instance()->row() + addend);
        collectObject(newIndex);

        return true;
    }

    if (direction == Left || direction == Right){
        int addend = (direction == Left ? -1 : 1);
        QModelIndex newIndex = index(Player::instance()->row(), Player::instance()->column() + addend);

        if(m_objects.contains(newIndex))
            if (!m_objects.value(newIndex)->isPassable())
                return false;

        if (Player::instance()->column() + addend < 0)
            return false;

        Player::instance()->setColumn(Player::instance()->column() + addend);
        collectObject(newIndex);

        return true;
    }

    return false;
}

void MapModel::reset()
{
    beginResetModel();

    m_rowCount = 0;
    m_columnCount = 0;

    foreach (const QModelIndex &index, m_objects.keys())
        removeObject(index);

    endResetModel();
}

void MapModel::init(int rowCount, int columnCount, int obstacleCount)
{
    emit layoutAboutToBeChanged();

    Player::instance()->setRow(rowCount / 2);
    Player::instance()->setColumn(columnCount / 2);
    m_rowCount = rowCount;
    m_columnCount = columnCount;
    createObjects(obstacleCount, 5);

    emit layoutChanged();
}

void MapModel::createObjects(int obstacleCount, int goldCount)
{
    QList<QModelIndex> allIdx;
    for (int row = 0; row < rowCount(); row++) {
        for (int column = 0; column < columnCount(); column++) {
            allIdx.append(index(row, column));
        }
    }

    Randomizer rd;

    int obstacles = 0;
    while(obstacles < obstacleCount ) {
        int random = rd.randInt(0, allIdx.size() - 1);
        QModelIndex randomIndex = allIdx.at(random);
        if(!m_objects.contains(randomIndex) && randomIndex != currentPlayerIndex()){
            m_objects.insert(randomIndex, new Obstacle());
            obstacles++;
        }
    }
    int gold = 0;
    while(gold < goldCount ) {
        int random = rd.randInt(0, allIdx.size() - 1);
        QModelIndex randomIndex = allIdx.at(random);
        if(!m_objects.contains(randomIndex) && randomIndex != currentPlayerIndex()){
            m_objects.insert(randomIndex, new Gold());
            gold++;
        }
    }
}

void MapModel::removeObject(const QModelIndex &index)
{
    delete m_objects.take(index);
    emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);
}

void MapModel::collectObject(const QModelIndex &index)
{
    if(!m_objects.contains(index))
        return;

    AbstractMapItem* object = m_objects.value(index);

    if(!object->isCollectible())
        return;

    AbstractCollectibleItem* collectible = qobject_cast<AbstractCollectibleItem*>(object);

    if(!collectible)
        return;

    if(collectible->onEntered())
        removeObject(index);
}

QModelIndex MapModel::currentPlayerIndex() const
{
    return index(Player::instance()->row(), Player::instance()->column());
}

void MapModel::onPlayerMoved(int oldRow, int row, int oldColumn, int column)
{
    emit dataChanged(index(oldRow, oldColumn), index(row, column), QVector<int>() << Qt::DisplayRole);
}


