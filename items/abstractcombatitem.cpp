#include "abstractcombatitem.h"
#include <QDebug>
#include <playerlog.h>

AbstractCombatItem::AbstractCombatItem(QObject *parent) : SUPER(parent)
{
}

void AbstractCombatItem::setHealth(int health)
{
    m_health = health;
    emit healthChanged(m_health);
}

int AbstractCombatItem::health() const
{
    return m_health;
}

void AbstractCombatItem::getDamage(int damage)
{
    PlayerLog::instance()<<QString("got damage");
    setHealth(health() - damage);
}

void AbstractCombatItem::hit(AbstractCombatItem *target)
{
    //random abfrage für wahrscheinlichkeit
    target->getDamage(m_attackRating);
}

int AbstractCombatItem::attackRating()
{
    return m_attackRating;
}

void AbstractCombatItem::setAttackRating(int attackRating)
{
    m_attackRating = attackRating;
    emit attackRatingChanged(m_attackRating);
}
