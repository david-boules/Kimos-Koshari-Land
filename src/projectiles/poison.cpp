#include "poison.h"
#include "projectile.h"
#include "kimo.h"
#include <QPixmap>
#include <QGraphicsScene>

Poison::Poison(qreal direction, QGraphicsItem* parent)
    : Projectile(parent)
{
    damage = 1;
    speed = direction * 2.5;  // Slightly slower than fireball
    QPixmap poisonImg = QPixmap(":/images/projectiles/poison.png").scaled(25, 25);
    setPixmap(poisonImg);
}

void Poison::hit(QGraphicsItem* target) {
    if (Kimo* k = dynamic_cast<Kimo*>(target)) {
        k->takeDamage(damage);
        scene()->removeItem(this);
        deleteLater();
    }
}
