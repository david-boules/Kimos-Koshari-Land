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

    int get_enemy_health() const override{
        return enemy_health;
    }

private:
    qreal speed;
    qreal damage;
    QTimer* shootTimer;
    int enemy_health=2;
    // void shootFire();
};




#endif // MOVE2_H
