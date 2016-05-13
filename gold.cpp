#include "gold.h"
#include "player.h"

Gold::Gold(QObject *parent) : AbstractCollectibleItem(parent)
{

}

bool Gold::onEntered()
{
    Player::instance()->addGold(1);
    return true;
}

QChar Gold::appearance() const
{
    return 'o';
}


