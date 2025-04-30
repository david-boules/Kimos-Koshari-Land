#include "projectile.h"
#include <QGraphicsScene>
#include <QTimer>

Projectile::Projectile(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(16); // ~60 FPS
}

void Projectile::move() {
    setPos(x() + speed, y());

    // Check CollidingItems
    for(int i = 0; i < collidingItems().size(); i++) {
        hit(collidingItems()[i]);
        return;
    }

    // Remove projectile if it goes off screen
    if (x() < 0 || x() > scene()->width()) {
        scene()->removeItem(this);
        deleteLater();
    }
}
