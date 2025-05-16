#ifndef LEVEL4_H
#define LEVEL4_H

#include "baselevel.h"

class Level4 : public BaseLevel
{
public:
    explicit Level4(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent = nullptr);
    void setEnemies() override;
    void setEnvironment() override;
};

#endif // LEVEL4_H
