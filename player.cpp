#include "player.h"

Player* Player::s_instance = 0;

Player::Player(QObject *parent) : QObject(parent)
{

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

int Player::health() const
{
    return m_health;
}

int Player::goldCount() const
{
    return m_goldCount;
}

void Player::getDamage(int damage)
{
    setHealth(health() - damage);
}

void Player::setGoldCount(int goldCount)
{
    m_goldCount = goldCount;
    emit goldChanged(m_goldCount);
}

void Player::setHealth(int health)
{
    m_health = health;
    emit healthChanged(m_health);
}

void Player::addGold(int gold)
{
    setGoldCount(goldCount() + gold);
}


