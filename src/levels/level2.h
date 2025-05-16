#ifndef LEVEL2_H
#define LEVEL2_H

#include "baselevel.h"

class Level2 : public BaseLevel
{
public:
    explicit Level2(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent = nullptr);
    void setEnemies() override;
    void setEnvironment() override;
};

#endif // LEVEL2_H
