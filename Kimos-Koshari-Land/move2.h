#ifndef MOVE2_H
#define MOVE2_H
#include "enemy.h"

class move2: public Enemy{
    Q_OBJECT
public:
    move2(QString path, QPointF startingPos, QGraphicsItem* parent = nullptr);
    void move() override;

private:
    qreal speed;
    qreal damage;
};


#endif // MOVE2_H
