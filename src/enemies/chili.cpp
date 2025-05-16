#include "chili.h"
#include <QGraphicsScene>

chili::chili(QString left,QString right, QPointF startingPos, QGraphicsItem* parent)
    : Enemy(QPixmap(left), startingPos, parent){
    speed=2.0;
    damage=2;
    health=2;

    enemy_left=QPixmap(left).scaled(60,60);
    enemy_right=QPixmap(right).scaled(64,64);
    shootTimer = new QTimer(this);
    connect(shootTimer, &QTimer::timeout, this, &chili::shootFire);
    shootTimer->start(18000); // Shoot every 0.8 seconds

}
void chili::shootFire(){
    if (!kimoo || !scene()) return;
       if (qAbs(kimoo->y() - y()) <= 20  && qAbs(kimoo->x() - x()) <= 300){


    qreal direction = (kimoo->x() < x()) ? -1 : 1; // Left or right
    Fireball* fb = new Fireball(direction);
    fb->setPos(x(), y() + 20); // Starting position slightly below the enemy
    scene()->addItem(fb);
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

    // If Kimo is close
    // if (distancex <300&&distancey<120) {
    //     // Move towards Kimo
    //     if (x() > kimoo->x()) {

    //         setPos(x() - qAbs(speed), y());         // Move left towards Kimo

    //     } else if (x() < kimoo->x()) {
    //        setPos(x() + qAbs(speed), y()); // Move right towards Kimo

    //     }
    // }
     {
        // Normal bouncing movement (if Kimo is far)
        setPos(x() - speed, y());
        if(speed>0){
            setPixmap(enemy_left);
        }
        else{
            setPixmap(enemy_right);
        }

        // Bounce back when hitting screen edges
        if (x() <= 0 || x() >= 800 - pixmap().width()) {
            speed = -speed; // Change direction
        }
    }
    }

;


