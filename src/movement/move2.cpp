#include "move2.h"
#include <QGraphicsScene>

move2::move2(QString path, QPointF startingPos, QGraphicsItem* parent)
    : Enemy(path, startingPos, parent){
    speed=2.0;
    damage=2;
    shootTimer = new QTimer(this);
    connect(shootTimer, &QTimer::timeout, this, &move2::shootFire);
    shootTimer->start(600); // Shoot every 0.8 seconds

}
void move2::shootFire(){
    if (!kimoo || !scene()) return;
       if (qAbs(kimoo->y() - y()) <= 20  && qAbs(kimoo->x() - x()) <= 300){


    qreal direction = (kimoo->x() < x()) ? -1 : 1; // Left or right
    Fireball* fb = new Fireball(direction);
    fb->setPos(x(), y() + 20); // Starting position slightly below the enemy
    scene()->addItem(fb);
    }
}

void move2::move() {
    if (kimoo && collidesWithItem(kimoo)) {
        kimoo->takeDamage(damage);

    }

    if (!kimoo) return; // If no Kimo linked, skip

    // Distance between enemy and Kimo
    qreal distancex = qAbs(x() - kimoo->x());
    qreal distancey=qAbs(y()-kimoo->y());

    // If Kimo is close (for example, within 50 pixels)
    if (distancex <300&&distancey<30) {
        // Move towards Kimo
        if (x() > kimoo->x()) {
            setPos(x() - qAbs(speed), y()); // Move left towards Kimo
        } else if (x() < kimoo->x()) {
            setPos(x() + qAbs(speed), y()); // Move right towards Kimo
        }
    }
    else {
        // Normal bouncing movement (if Kimo is far)
        setPos(x() - speed, y());

        // Bounce back when hitting screen edges
        if (x() <= 0 || x() >= 800 - pixmap().width()) {
            speed = -speed; // Change direction
        }
    }


}
;


