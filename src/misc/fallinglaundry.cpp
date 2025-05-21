#include "fallinglaundry.h"
#include "kimo.h"
#include "platform.h"
#include <QTimer>
#include <QGraphicsScene>

FallingLaundry::FallingLaundry(const QPixmap& pixmap, QPointF spawnPos, QObject* parent)
    : QObject(parent)
{
    setPixmap(pixmap.scaled(30,30));
    setPos(spawnPos);

    fallTimer = new QTimer();
    connect(fallTimer, &QTimer::timeout, this, &FallingLaundry::fall);
    fallTimer->start(16);
}

void FallingLaundry::fall() {
    setPos(x(), y() + 2);

    // Checking for collisions with Kimo or Platforms (to deal damage / be removed)
    for (QGraphicsItem* item : collidingItems()) {
        if (Kimo* kimo = dynamic_cast<Kimo*>(item)) {
            kimo->takeDamage(1);
            scene()->removeItem(this);
            deleteLater(); // For safe object deletion
            return;
        }
        else if (Platform* p = dynamic_cast<Platform*>(item)) {
            scene()->removeItem(this);
            deleteLater();
            return;
        }
    }

    if (scene() && y() > scene()->height()) {
        scene()->removeItem(this);
        deleteLater();              // For safe object deletion
        return;
    }
}

void FallingLaundry::pause() {
    if (fallTimer && fallTimer->isActive()) fallTimer->stop();
}

void FallingLaundry::resume() {
    if (fallTimer && !fallTimer->isActive()) fallTimer->start(16);
}
