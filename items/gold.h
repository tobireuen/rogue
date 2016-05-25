#ifndef GOLD_H
#define GOLD_H

#include "abstractcollectibleitem.h"

class Gold : public AbstractCollectibleItem
{
    Q_OBJECT
public:
    Gold(QObject *parent = 0);

    virtual bool onEntered() const final;

    virtual QChar appearance() const;
};

#endif // GOLD_H
