#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#define DEFAULT_GOLD_COUNT 5

class Player : public QObject
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
};

#endif // PLAYER_H
