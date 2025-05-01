#ifndef MOVE1_H
#define MOVE1_H
#include "enemy.h"
#include <QtMath>


class move1 : public Enemy {
    Q_OBJECT
public:
    move1(QString path, QPointF startingPos, QGraphicsItem* parent = nullptr);
    void move() override;

private:
    qreal angle = 0.0;
    qreal speed;
};


#endif // MOVE1_H
