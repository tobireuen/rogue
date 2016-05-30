#ifndef PLAYERLOG_H
#define PLAYERLOG_H

#include <QObject>

/**
 * @brief The PlayerLog class is a singleton and manages all information displayed in the PlayerLogWidget
 */
class PlayerLog : public QObject
{
    Q_OBJECT
    typedef QObject SUPER;

signals:
    /**
     * @brief emits a signal if new information is to be added
     * @param newInfo is the String to be displayed in the widget
     */
    void newInfo(const QString &newInfo);

public:
    /**
     * @brief since the PlayerLog class is considered to be a singleton instance() is needed
     * @return reference on PlayerLog
     */
    static PlayerLog& instance();

    /**
     * @brief calls newInfo
     * @param info is a string to be displayed
     */
    void addNewInfo(const QString &info);

    /**
     * @brief overloads the operator << to handle Strings directly
     * @param info
     * @return
     */
    PlayerLog& operator <<(const QString &info);

protected:
    /**
     * @brief constructs a PlayerLog with given parent
     */
    explicit PlayerLog(QObject *parent = 0);

private:
    /**
     * @brief s_instance is a pointer representing the Player as a singleton
     */
    static PlayerLog* s_instance;
};

#endif // PLAYERLOG_H
