#include "playerlogwidget.h"
#include "playerlog.h"

PlayerLogWidget::PlayerLogWidget(QWidget *parent) : SUPER(parent)
{
  connect(&PlayerLog::instance(), &PlayerLog::newInfo, this, &PlayerLogWidget::onNewInfo);
  setPlainText("Welcome!");
}

void PlayerLogWidget::onNewInfo(const QString &newInfo)
{
    QString currentText = toPlainText();
    currentText.append("\n" + newInfo);
    setPlainText(currentText);
}
