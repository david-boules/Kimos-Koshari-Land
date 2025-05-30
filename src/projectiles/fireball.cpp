#include "fireball.h"
#include "chili.h"
#include "kimo.h"
#include "projectile.h"
#include <QPixmap>
#include <QGraphicsScene>

Fireball::Fireball(qreal direction,QGraphicsItem* shooter, QGraphicsItem* parent) : Projectile(parent),shooter(shooter)
{   damage=1;
    speed=direction*3;  // Speed: 3, direction: -1 or 1
    QPixmap fireball = QPixmap(":/images/projectiles/fireball.png").scaled(20,20);
    setPixmap(fireball);
}

void Fireball::hit(QGraphicsItem* target) {
    if (target == shooter)
        return; // Don't damage shooter

    // If shooter is Kimo, damage enemies
    if (dynamic_cast<Kimo*>(shooter)) {
        if (Enemy* e = dynamic_cast<Enemy*>(target)) {
            e->takedamage(damage);
            if (e->get_enemy_health() <= 0) {
                scene()->removeItem(e);
                delete e;
            }
            scene()->removeItem(this);
            deleteLater();
            return;
        }
    }

    // If shooter is Chili, damage Kimo
    if (dynamic_cast<chili*>(shooter)) {
        if (Kimo* k = dynamic_cast<Kimo*>(target)) {
            k->takeDamage(damage);
            scene()->removeItem(this);
            deleteLater();
            return;
        }
    }
}

