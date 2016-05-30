#ifndef PLAYERINFOWIDGET_H
#define PLAYERINFOWIDGET_H

#include <QWidget>

namespace Ui {

/**
 * displays information about the player
 */
class PlayerInfoWidget;
}

class PlayerInfoWidget : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief constructs a PlayerInfoWidget with given parent
     */
    explicit PlayerInfoWidget(QWidget *parent = 0);

    /**
     * @brief destroys PlayerInfoWidget
     */
    ~PlayerInfoWidget();

private:
    Ui::PlayerInfoWidget *m_ui;

private slots:
    /**
     * @brief displays amount of gold in labelGold in PlayerInfoWidget
     * @param amount of gold to be displayed
     */
    void setGold(int gold);

    /**
     * @brief displays amount of health in labelHealth in PlayerInfoWidget
     * @param amount of health to be displayed
     */
    void setPlayerHealth(int health);
};

#endif // PLAYERINFOWIDGET_H
