#ifndef MOVE2_H
#define MOVE2_H
#include "enemy.h"
#include "fireball.h"

class move2: public Enemy{
    Q_OBJECT
public:
    move2(QString path, QPointF startingPos, QGraphicsItem* parent = nullptr);
    void move() override;
     void shootFire();


private:
    qreal speed;
    qreal damage;
    QTimer* shootTimer;
   // void shootFire();
};


#endif // MOVE2_H
