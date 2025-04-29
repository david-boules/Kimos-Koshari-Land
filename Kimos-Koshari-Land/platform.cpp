#include "platform.h"
#include <QGraphicsScene>
#include <QPen>
#include <QBrush>
#include <QPixmap>

// Platform base constructor: sets size and position
Platform::Platform(int width, int height, int x, int y) {
    setRect(0, 0, width, height);
    QPen pen(Qt::lightGray);
    QBrush brush(Qt::lightGray);
    setPen(pen);
    setBrush(brush);
    setPos(x, y);
}

// StaticPlatform constructor: calls base Platform constructor
// Static platforms do not move, so update() does nothing
StaticPlatform::StaticPlatform(int width, int height, int x, int y)
    : Platform(width, height, x, y) {}
void StaticPlatform::update() {
    // No movement or special behavior for static platforms
}

// MovingPlatform constructor: calls base Platform constructor and initializes movement variables
MovingPlatform::MovingPlatform(int width, int height, int x, int y, int range, int speed)
    : Platform(width, height, x, y), startX(x), moveRange(range), moveSpeed(speed), direction(1) {}

// MovingPlatform update: moves the platform back and forth horizontally
void MovingPlatform::update() {
    setPos(x() + direction * moveSpeed, y());
    if (x() >= startX + moveRange || x() <= startX) {
        direction *= -1;
    }
}

// SpikyPlatform constructor overlays a spike PNG on the platform
SpikyPlatform::SpikyPlatform(int width, int height, int x, int y)
    : Platform(width, height, x, y), spikeOverlay(nullptr)
{
    // Load the spike PNG from the Qt resource system (make sure the path matches your .qrc file)
    QPixmap spikePixmap(":/images/spikes.png"); // <-- update this path if your .qrc uses a different prefix
    if (!spikePixmap.isNull()) {
        spikePixmap = spikePixmap.scaled(width, spikePixmap.height(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        spikeOverlay = new QGraphicsPixmapItem(spikePixmap, this);
        spikeOverlay->setPos(0, -spikePixmap.height() + 5);
    }
}
void SpikyPlatform::update() {
    // Spiky platforms do not move by default
    // You can add animation or effects here if desired
}
