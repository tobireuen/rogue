#include "playerinfowidget.h"
#include "ui_playerinfowidget.h"
#include "player.h"

PlayerInfoWidget::PlayerInfoWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::PlayerInfoWidget)
{
    m_ui->setupUi(this);
    setGold(Player::instance()->goldCount());
    connect(Player::instance(), &Player::goldChanged, this, &PlayerInfoWidget::setGold);
}

PlayerInfoWidget::~PlayerInfoWidget()
{
    delete m_ui;
}

void PlayerInfoWidget::setGold(int gold)
{
    m_ui->labelGold->setText(QString::number(gold));
}
