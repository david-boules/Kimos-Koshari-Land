#include "enemy.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>


#include <QDebug>
Enemy::Enemy(QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
    // Load and scale enemy sprite
    QPixmap enemyLarge(":/images/chili.png");
    QPixmap enemyScaled = enemyLarge.scaled(60, 60);  // Adjust size as needed
    setPixmap(enemyScaled);
    setPos(600, 300);  // Starting position
    speed=2.0;

    // Set up movement timer for smooth update
    moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(16); // ~60 FPS
}
void Enemy::move(){

    if (!kimoo) return; // If no Kimo linked, skip

    // Distance between enemy and Kimo
    qreal distancex = qAbs(x() - kimoo->x());
    qreal distancey=qAbs(y()-kimoo->y());

    // If Kimo is close (for example, within 50 pixels)
    if (distancex <200&&distancey<30) {
        // Move towards Kimo
        if (x() > kimoo->x()) {
            setPos(x() - qAbs(speed), y()); // Move left towards Kimo
        } else if (x() < kimoo->x()) {
            setPos(x() + speed, y()); // Move right towards Kimo
        }
    }
    else {
        // Normal bouncing movement (if Kimo is far)
        setPos(x() - speed, y());

        // Bounce back when hitting screen edges
        if (x() <= 0 || x() >= 800 - pixmap().width()) {
            speed = -speed; // Change direction
        }
    }
}

   //      setPos(x() - speed, y());

   //  // Bounce back at edges
   //  if (x() <= 0 || x() >= 800 - pixmap().width()) {
   //      speed = -speed;
   // // Change direction
   //  }
   //  if (kimoo && kimoo->y() < 400) {
   //      setPos(x(), y() - 2); // Enemy moves up slightly
   //  }
   //  qDebug() << "Enemy at:" << pos();
   //  }
