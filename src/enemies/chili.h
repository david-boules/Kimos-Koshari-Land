#ifndef CHILI_H
#define CHILI_H
#include "enemy.h"
#include "fireball.h"

enum class chili_move { level1, level2,level2_1, level3, level4 };

class chili: public Enemy{
    Q_OBJECT
public:
    chili(QString left,QString right, QPointF startingPos, QGraphicsItem* parent = nullptr);
    void move() override;
    void shootFire();
  // void setMoveStyle(MoveStyle s) { moveStyle = s; }
    void setMoveStyle(chili_move style);
    chili_move getMoveStyle() const;

private:
    qreal speed;
    qreal damage;
    QTimer* shootTimer;
    int enemy_health=2;
    bool facingKimo = false;
    QPixmap enemy_left;
    QPixmap enemy_right;
   // MoveStyle moveStyle = MoveStyle::level1;

    //level 2
    chili_move moveStyle= chili_move::level1;

    QTimer* fire_cooldown_timer = nullptr;// to pause fire
    bool canFire = true;

    float verticalSpeed = 2.0;  // vertical movement speed
    float minY = 300;           // minimum Y position chili can move to
    float maxY = 490;

    bool canShoot = true;// pause shoots in vertical move
    // void shootFire();
};




#endif // CHILI_H
