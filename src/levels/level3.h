#ifndef LEVEL3_H
#define LEVEL3_H

#include "baselevel.h"

class Level3 : public BaseLevel
{
public:
    explicit Level3(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent = nullptr);
    void setEnemies() override;
    void setEnvironment() override;
};

#endif // LEVEL3_H
