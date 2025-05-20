#include "coin.h"
#include <QGraphicsScene>

Coin::Coin(QPointF pos, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent)
{
    // Load and scale the coin image
    setPixmap(QPixmap(":/images/misc/coin.png").scaled(30, 30));
    setPos(pos);

    // Set up animation timer
    animationTimer = new QTimer(this);
    connect(animationTimer, &QTimer::timeout, this, &Coin::updateAnimation);
    startAnimation();
}

void Coin::startAnimation()
{
    animationTimer->start(100); // Update every 100ms
}

void Coin::updateAnimation()
{
    // Simple rotation animation
    setRotation(rotation() + 10);
    if (rotation() >= 360)
    {
        setRotation(0);
    }
}