#ifndef MOVE1_H
#define MOVE1_H
#include "enemy.h"
#include <QtMath>


class move1 : public Enemy {
    Q_OBJECT
public:
    move1(QString path, QPointF startingPos, QGraphicsItem* parent = nullptr);
    void move() override;
    int get_enemy_health() const override{
        return enemy_health;
    }
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
#endif // MOVE1_H
