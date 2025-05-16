#ifndef ONION_H
#define ONION_H
#include "enemy.h"
#include <QtMath>


class onion : public Enemy {
    Q_OBJECT
public:
    onion(QString path, QPointF startingPos, QGraphicsItem* parent = nullptr);
    void move() override;

    void setBounds(qreal min, qreal max){
        minX=min;
        maxX=max;
    }

private:
    qreal angle = 0.0;
    qreal speed;
    qreal damage;
    int enemy_health=1;
    qreal minX = 0;
    qreal maxX = 800;
    //qreal healthOfEnemy;


};
#endif // ONION_H
