#ifndef PLAYER_H
#define PLAYER_H

#include "abstractcombatitem.h"

#include <QObject>

#define DEFAULT_GOLD_COUNT 0
#define DEFAULT_PLAYER_HEALTH 10
#define DEFAULT_PLAYER_ATTACKRATING 1
class Player : public AbstractCombatItem
{
    Q_OBJECT

signals:
    void moved(int oldRow, int newRow, int oldColumn, int newColumn);
    void rowChanged(int row);
    void columnChanged(int column);
    void goldChanged(int gold);

public:
    static Player* instance();

    void reset();

    int row() const;
    int column() const;

    void setRow(int row);
    void setColumn(int column);

    int goldCount() const;
    void addGold(int gold);

protected:
    explicit Player(QObject *parent = 0);
    void setGoldCount(int goldCount);

private:
    static Player* s_instance;

    int m_row = 0;
    int m_column = 0;
    int m_goldCount = DEFAULT_GOLD_COUNT;

    // AbstractMapItem interface
public:
    QChar appearance() const;
    bool isPassable() const;
    bool isCollectible() const;
};

#endif // PLAYER_H
