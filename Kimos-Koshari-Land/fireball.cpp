#include "fireball.h"
#include <QPixmap>
#include <QGraphicsScene>

Fireball::Fireball(qreal direction, QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)
{  damage=2;
    speed=direction*3;  // Speed: 3, direction: -1 or 1
    QPixmap fireball(":/images/fireball.png");
    QPixmap fireballScaled = fireball.scaled(20, 20); // Adjust fireball size
    setPixmap(fireballScaled);
    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &Fireball::move);
    moveTimer->start(16); // ~60 FPS
}

void Fireball::setTargetKimo(Kimo* kimo){
    kimoo=kimo;
}

void Fireball::move() {
    setPos(x() + speed, y());

    if (kimoo && collidesWithItem(kimoo)) {
        kimoo->takeDamage(damage);           // Deal damage
        scene()->removeItem(this);           // Remove from scene
        delete this;                         // Delete object
        return;
    }
    // Remove fireball if it goes off screen
    if (x() < 0 || x() > 800) {
        scene()->removeItem(this);
        deleteLater();
    }

    // You can also add collision detection with Kimo here
}
