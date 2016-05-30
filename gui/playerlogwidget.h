#ifndef PLAYERLOGWIDGET_H
#define PLAYERLOGWIDGET_H

#include <QTextEdit>

/**
 * @brief The PlayerLogWidget class displays information about current in-game events happening
 */
class PlayerLogWidget : public QTextEdit
{
    Q_OBJECT
    typedef QTextEdit SUPER;

public:
    /**
     * @brief Constructs a PlayerLogWidget with the given parent
     */
    PlayerLogWidget(QWidget * parent = 0);

private slots:
    /**
     * @brief displays incoming information in PlayerLogWidget
     * @param String containing appendable information
     */
    void onNewInfo(const QString &newInfo);
};

#endif // PLAYERLOGWIDGET_H
