#include "player.h"

Player* Player::s_instance = 0;

Player::Player(QObject *parent) : AbstractCombatItem(parent)
{
   setHealth(DEFAULT_PLAYER_HEALTH);
   setAttackRating(DEFAULT_PLAYER_ATTACKRATING);
}

Player *Player::instance()
{
    if (s_instance == 0) {
        s_instance = new Player;
    }
    return s_instance;
}

void Player::reset()
{
    setGoldCount(DEFAULT_GOLD_COUNT);
}

int Player::row() const
{
    return m_row;
}

int Player::column() const
{
    return m_column;
}

void Player::setRow(int row)
{
    if(m_row != row){
        int oldRow = m_row;
        m_row = row;
        emit rowChanged(row);
        emit moved(oldRow, row, m_column, m_column);
    }
}

void Player::setColumn(int column)
{
    if(m_column != column){
        int oldColumn = m_column;
        m_column = column;
        emit columnChanged(column);
        emit moved(m_row, m_row, oldColumn, m_column);
    }
}


int Player::goldCount() const
{
    return m_goldCount;
}


void Player::setGoldCount(int goldCount)
{
    m_goldCount = goldCount;
    emit goldChanged(m_goldCount);
}

void Player::addGold(int gold)
{
    setGoldCount(goldCount() + gold);
}

QChar Player::appearance() const
{
    return '@';
}

bool Player::isPassable() const
{
    return false;
}

bool Player::isCollectible() const
{
    return false;
}
