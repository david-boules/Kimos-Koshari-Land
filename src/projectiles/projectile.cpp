#include "projectile.h"
#include "kimo.h"
#include <QGraphicsScene>
#include <QTimer>

Projectile::Projectile(QGraphicsItem *parent) : QGraphicsPixmapItem(parent) {
    moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(16); // ~60 FPS
}

void Projectile::move() {
    // Pause check using Kimo's flag
    for (QGraphicsItem* item : scene()->items()) {
        if (Kimo* kimo = dynamic_cast<Kimo*>(item)) {
            if (!kimo->isEnabled()) return; // Pause movement
            break;
        }
    }

    // Perform movement
    setPos(x() + (speed * direction), y());

    // Check for collisions
    QList<QGraphicsItem*> items = collidingItems();
    for (QGraphicsItem* item : items) {
        if (item == this || dynamic_cast<Projectile*>(item)) continue;
        hit(item);
        if (!scene() || !scene()->items().contains(this)) return;
    }

    // Remove projectile if out of bounds
    if (scene()) {
        QRectF sceneBounds = scene()->sceneRect();
        if (x() < sceneBounds.left() || x() + pixmap().width() > sceneBounds.right()) {
            scene()->removeItem(this);
            deleteLater();
        }
    }
}
