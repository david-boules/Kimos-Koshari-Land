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
    // Use direction when calculating horizontal movement
    setPos(x() + (speed * direction), y());

    // Check CollidingItems
    QList<QGraphicsItem*> items = collidingItems();
    for(int i = 0; i < items.size(); i++) {
        if (Kimo* kimo = dynamic_cast<Kimo*>(items[i])) {
            if (!kimo->isEnabled()) return; // Making all projectiles stop moving if the game is paused (store)
           // break;
        }
        // Avoid hitting self or other projectiles immediately after firing
        if (items[i] == this || dynamic_cast<Projectile*>(items[i])) {
            continue;
        }
        hit(items[i]);
        // If hit() resulted in deletion (e.g., hit an enemy), stop processing
        // We check if the scene still contains this item. If not, it was deleted.
        if (!scene() || !scene()->items().contains(this)) {
             return;
        }
    }

    // Remove projectile if it goes off scene boundaries
    if (scene()) { // Check if scene exists before accessing its properties
        QRectF sceneBounds = scene()->sceneRect();
        if (x() < sceneBounds.left() || x() + pixmap().width() > sceneBounds.right()) {
            scene()->removeItem(this);
            deleteLater();
        }
    }
}

