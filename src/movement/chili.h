#ifndef CHILI_H
#define CHILI_H
#include "enemy.h"
#include "fireball.h"

class chili: public Enemy{
    Q_OBJECT
public:
    chili(QString left,QString right, QPointF startingPos, QGraphicsItem* parent = nullptr);
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
    bool facingKimo = false;
    QPixmap enemy_left;
    QPixmap enemy_right;

    // void shootFire();
};




#endif // CHILI_H
