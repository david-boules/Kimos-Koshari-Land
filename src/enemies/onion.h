#ifndef ONION_H
#define ONION_H
#include "enemy.h"
#include <QtMath>

enum class onion_move { level1, level2, level3, level4 };

class onion : public Enemy {
    Q_OBJECT
public:
    onion(QString path, QPointF startingPos, QGraphicsItem* parent = nullptr);
    void move() override;

    void setBounds(qreal min, qreal max){
        minX=min;
        maxX=max;
    }

public:
    void setMoveStyle(onion_move style);
    onion_move getMoveStyle() const;


private:
    qreal angle = 0.0;
    qreal speed;
    qreal damage;
    int enemy_health=1;
    qreal minX = 0;
    qreal maxX = 800;
    //qreal healthOfEnemy;
    onion_move moveStyle = onion_move::level1;



};
#endif // ONION_H
