#ifndef LEVEL5_H
#define LEVEL5_H

#include "baselevel.h"

class Level5 : public BaseLevel
{
public:
    explicit Level5(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, LevelOrchestrator* orchestrator, QObject *parent = nullptr);
    void setEnemies() override;
    void setEnvironment() override;
};

#endif // LEVEL5_H
