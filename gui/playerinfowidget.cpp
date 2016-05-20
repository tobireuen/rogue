#include "playerinfowidget.h"
#include "ui_playerinfowidget.h"
#include "player.h"

PlayerInfoWidget::PlayerInfoWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::PlayerInfoWidget)
{
    m_ui->setupUi(this);
    setGold(Player::instance()->goldCount());
    setPlayerHealth(Player::instance()->health());
    connect(Player::instance(), &Player::goldChanged, this, &PlayerInfoWidget::setGold);
    connect(Player::instance(), &Player::healthChanged, this, &PlayerInfoWidget::setPlayerHealth);

}

PlayerInfoWidget::~PlayerInfoWidget()
{
    delete m_ui;
}

void PlayerInfoWidget::setGold(int gold)
{
    m_ui->labelGold->setText(QString::number(gold));
}

void PlayerInfoWidget::setPlayerHealth(int health)
{
    m_ui->labelPlayerHealth->setText(QString::number(health));
}
