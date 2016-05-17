#include "MapModel.h"
#include "randomizer.h"
#include "player.h"
#include "obstacle.h"
#include "gold.h"
#include "dungeongenerator.h"

#include <QSize>
#include <QDebug>
#include <QtGlobal>
#include <QFont>


MapModel::MapModel(int rowCount, int columnCount, QObject *parent)
    : SUPER(parent)
{
    connect(Player::instance(), &Player::moved, this, &MapModel::onPlayerMoved);
    init(rowCount, columnCount);
}

QVariant MapModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation)
    Q_UNUSED(role)
    return section;
}

int MapModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_rowCount;
}

int MapModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
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
        else if(m_dungeon->containsObjectAtIndex(index))
            return m_dungeon->getObjectAtIndex(index)->appearance();
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
    Q_UNUSED(index)
    return Qt::ItemIsEnabled;
}

bool MapModel::movePlayer(MapModel::Direction direction)
{
    if (direction == Up || direction == Down){
        int addend = (direction == Up ? -1 : 1);
        QModelIndex newIndex = index(Player::instance()->row() + addend, Player::instance()->column());

        //Object on newIndex?
        if(m_dungeon->containsObjectAtIndex(newIndex)) {
            if (!m_dungeon->getObjectAtIndex(newIndex)->isPassable())
                return false;
        }

        if (direction == Up && Player::instance()->row() + addend < 0)
            return false;
        if (direction == Down && Player::instance()->row() + addend >= rowCount())
            return false;

        Player::instance()->setRow(Player::instance()->row() + addend);
        collectObject(newIndex);

        return true;
    }

    if (direction == Left || direction == Right){
        int addend = (direction == Left ? -1 : 1);
        QModelIndex newIndex = index(Player::instance()->row(), Player::instance()->column() + addend);

        if(m_dungeon->containsObjectAtIndex(newIndex)) {
            if (!m_dungeon->getObjectAtIndex(newIndex)->isPassable())
                return false;
        }
        if (direction == Left && Player::instance()->column() + addend < 0)
            return false;
        if (direction == Right && Player::instance()->column() + addend >= columnCount())
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

    m_dungeon->reset();

    endResetModel();
}

void MapModel::init(int rowCount, int columnCount)
{
    emit layoutAboutToBeChanged();

    m_rowCount = rowCount;
    m_columnCount = columnCount;

    DungeonGenerator generator(this);
    m_dungeon = generator.generate();
    connect(m_dungeon, &Dungeon::objectAdded, this, &MapModel::onObjectChanged);
    connect(m_dungeon, &Dungeon::objectRemoved, this, &MapModel::onObjectChanged);
    m_dungeon->setParent(this);

    setPlayer();

    emit layoutChanged();
}

void MapModel::collectObject(const QModelIndex &index)
{
    if(!m_dungeon->containsObjectAtIndex(index))
        return;

    AbstractMapItem* object = m_dungeon->getObjectAtIndex(index);

    if(!object->isCollectible())
        return;

    AbstractCollectibleItem* collectible = qobject_cast<AbstractCollectibleItem*>(object);

    if(!collectible)
        return;

    if(collectible->onEntered())
        m_dungeon->removeObjectAtIndex(index);
}

void MapModel::setPlayer()
{
    Randomizer rd;
    int randomColumn = rd.randInt(1, m_columnCount - 1);
    int randomRow = rd.randInt(1, m_rowCount - 1);

    if(!m_dungeon->containsObjectAtIndex(index(randomRow, randomColumn))){
        Player::instance()->setRow(randomRow);
        Player::instance()->setColumn(randomColumn);
    }
    else {
        setPlayer();
    }
}

QModelIndex MapModel::currentPlayerIndex() const
{
    return index(Player::instance()->row(), Player::instance()->column());
}

void MapModel::onPlayerMoved(int oldRow, int row, int oldColumn, int column)
{
    emit dataChanged(index(oldRow, oldColumn), index(row, column), QVector<int>() << Qt::DisplayRole);
}

void MapModel::onObjectChanged(const QModelIndex &index)
{
    emit dataChanged(index, index, QVector<int>() << Qt::DisplayRole);
}


