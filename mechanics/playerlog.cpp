#include "playerlog.h"

PlayerLog* PlayerLog::s_instance = 0;


PlayerLog::PlayerLog(QObject *parent) : QObject(parent)
{

}

PlayerLog *PlayerLog::instance()
{
    if (s_instance == 0) {
        s_instance = new PlayerLog;
    }
    return s_instance;

}

void PlayerLog::addNewInfo(const QString &info)
{
    emit newInfo(info);
}

PlayerLog& PlayerLog::operator<<(PlayerLog& log, const QString &info)
{
    emit newInfo(info);
    return log;
}
