#ifndef PLAYERLOGWIDGET_H
#define PLAYERLOGWIDGET_H

#include <QTextEdit>

class PlayerLogWidget : public QTextEdit
{
    Q_OBJECT
    typedef QTextEdit SUPER;

public:
    PlayerLogWidget(QWidget * parent = 0);

private slots:
    void onNewInfo(const QString &newInfo);
};

#endif // PLAYERLOGWIDGET_H
