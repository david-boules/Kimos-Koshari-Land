#include "chili.h"
#include "fireball.h"
#include <QGraphicsScene>

chili::chili(QString left,QString right, QPointF startingPos, QGraphicsItem* parent)
    : Enemy(QPixmap(left), startingPos, parent){
    speed=1.5;
    damage=3;
    health=2;
    max_health=2;
    update_health_bar();


    enemy_left=QPixmap(left).scaled(60,60);
    enemy_right=QPixmap(right).scaled(64,64);
    shootTimer = new QTimer(this);
    connect(shootTimer, &QTimer::timeout, this, &chili::shootFire);
    shootTimer->start(900); // Shoot every 0.8 seconds 800
    fire_cooldown_timer = new QTimer(this);
    fire_cooldown_timer->setInterval(1500); // 1.5 seconds cooldown
    fire_cooldown_timer->setSingleShot(true);
    connect(fire_cooldown_timer, &QTimer::timeout, [this]() {
        canFire = true;
    });

}

void chili::setMoveStyle(chili_move style) {
    moveStyle = style;
    // if (moveStyle == chili_move::level2_1) {
    //     health = 1;      // Increase health for level 2
    //     max_health = 1;
    //     update_health_bar();
    // }
    // else {
    //     health=2;
    //     max_health=2;
    //     update_health_bar();
    // }
}

chili_move chili::getMoveStyle() const {
    return moveStyle;
}



void chili::shootFire(){
    if (!kimoo || !scene()) return;
    if (!canShoot) return;
       if (qAbs(kimoo->y() - y()) <= 20  && qAbs(kimoo->x() - x()) <= 300){


    qreal direction = (kimoo->x() < x()) ? -1 : 1; // Left or right
    Fireball* fb = new Fireball(direction,this);
    fb->setPos(x(), y() + 20); // Starting position slightly below the enemy
    scene()->addItem(fb);

    canShoot = false;
    QTimer::singleShot(2000, [this]() { canShoot = true; });
    }
}


void chili::move() {
    if (kimoo && collidesWithItem(kimoo)) {
        kimoo->takeDamage(damage);

    }



    if (!kimoo) return; // If no Kimo linked, skip

    // Distance between enemy and Kimo
    qreal distancex = qAbs(x() - kimoo->x());
    qreal distancey=qAbs(y()-kimoo->y());



    switch (moveStyle)
    {
    case chili_move::level1:  {         // original “bounce” code
        if (!kimoo) return;

        qreal distancex = qAbs(x() - kimoo->x());
        qreal distancey = qAbs(y() - kimoo->y());

        if (distancex < 300 && distancey < 120) {

            if (kimoo->x() < x()) {
                setPos(x() - qAbs(speed), y());
                setPixmap(enemy_left);
            } else if (kimoo->x() > x()) {
                setPos(x() + qAbs(speed), y());
                setPixmap(enemy_right);
            }
        } else {

            setPos(x() + speed, y());


            if (x() <= 0 || x() >= 800 - pixmap().width()) {
                speed = -speed; // Reverse direction
            }


            if (speed > 0) {
                setPixmap(enemy_right);
            } else {
                setPixmap(enemy_left);
            }
        }

        break;
    }








case chili_move::level2:

        setPos(x(), y() + verticalSpeed);

        if (y() <= minY || y() >= maxY) {
            verticalSpeed = -verticalSpeed;  // reverse direction
        }

        // Check if Kimo is to the LEFT and roughly on the same vertical level
        if (kimoo->x() < x()&&distancex<=320 && qAbs(kimoo->y() - y()) <= 20 && canFire) {
            shootFire();
            canFire = false;
            fire_cooldown_timer->start();
        }
        break;

case chili_move::level2_1:

    setPos(x(), y() + verticalSpeed);

    if (y() <= 150 || y() >= 330) {
        verticalSpeed = -verticalSpeed;  // reverse direction
    }

    // Check if Kimo is to the LEFT and roughly on the same vertical level
    if (kimoo->x() < x()&&distancex<=320 && qAbs(kimoo->y() - y()) <= 20 && canFire) {
        shootFire();
        canFire = false;
        fire_cooldown_timer->start();
    }
    break;



case chili_move::level4:

    setPos(x(), y() + verticalSpeed);

    if (y() <= 100 || y() >= 300) {
        verticalSpeed = -verticalSpeed;  // reverse direction
    }

    // Check if Kimo is to the LEFT and roughly on the same vertical level
    if (kimoo->x() < x()&&distancex<=320 && qAbs(kimoo->y() - y()) <= 20 && canFire) {
        shootFire();
        canFire = false;
        fire_cooldown_timer->start();
    }
    break;


case chili_move::level5:


    if (!kimoo) return;

    if (kimoo->x() < x()) {
        setPixmap(enemy_left);
    } else {
        setPixmap(enemy_right);
    }
    break;

    }
}


