#include "fallinglaundry.h"
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
    setPos(x(), y() + 3);
    if (scene() && y() > scene()->height()) {
        scene()->removeItem(this);
        deleteLater();              // For safe object deletion
        return;
    }
}
