#ifndef PLAYERINFOWIDGET_H
#define PLAYERINFOWIDGET_H

#include <QWidget>

namespace Ui {
class PlayerInfoWidget;
}

class PlayerInfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerInfoWidget(QWidget *parent = 0);
    ~PlayerInfoWidget();

private:
    Ui::PlayerInfoWidget *m_ui;

private slots:
    void setGold(int gold);
};

#endif // PLAYERINFOWIDGET_H
