#ifndef LEVEL1_H
#define LEVEL1_H

#include "baselevel.h"

class Level1 : public BaseLevel
{
public:
    explicit Level1(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent = nullptr);
    void setEnemies() override;
    void setEnvironment() override;

private:
    bool enemySpawned = false;

};

#endif // LEVEL1_H
