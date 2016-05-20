#ifndef PLAYERLOG_H
#define PLAYERLOG_H

#include <QObject>

class PlayerLog : public QObject
{
    Q_OBJECT
    typedef QObject SUPER;

signals:
    void newInfo(const QString &newInfo);

public:
    static PlayerLog& instance();

    void addNewInfo(const QString &info);
    PlayerLog& operator <<(const QString &info);

protected:
    explicit PlayerLog(QObject *parent = 0);

private:
    static PlayerLog* s_instance;


};

#endif // PLAYERLOG_H
