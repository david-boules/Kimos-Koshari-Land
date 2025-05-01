#include "enemy.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QBrush>
#include <QGraphicsScene>


#include <QDebug>
Enemy::Enemy(QString path, QPointF startingPos, QGraphicsItem* parent) : QGraphicsPixmapItem(parent)
{
    // Load and scale enemy sprite
    QPixmap enemyLarge(path);
    QPixmap enemyScaled = enemyLarge.scaled(60, 60);    // Adjust size as needed
     setPixmap(enemyScaled);
    setPos(startingPos);  // Starting position
    speed=2.0;
    damage=1;
    health=2;
    healthBarBackground = new QGraphicsRectItem(0, 0, 60, 6, this);
    healthBarBackground->setBrush(Qt::black);
    healthBarBackground->setPos(0, -10);

    healthBar= new QGraphicsRectItem(0,0,60,6,healthBarBackground);
    healthBar->setBrush(Qt::green);


    // Set up movement timer for smooth update
    moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(16); // ~60 FPS
}

void Enemy::move(){
    if (kimoo && collidesWithItem(kimoo)) {
        kimoo->takeDamage(damage);
        health-=1;
         healthBar->setRect(0, 0, 60 * (health / 2.0), 6);
        if(health<=0){
        scene()->removeItem(this);
        delete this;
        return;
        }
    }

    if (!kimoo) return; // If no Kimo linked, skip

    // Distance between enemy and Kimo
    qreal distancex = qAbs(x() - kimoo->x());
    qreal distancey=qAbs(y()-kimoo->y());



    // If Kimo is close (for example, within 50 pixels)
    if (distancex <200&&distancey<10) {
        // Move towards Kimo
        if (x() > kimoo->x() && x() > 300) {
            setPos(x() - qAbs(speed), y()); // Move left towards Kimo
        } else if (x() < kimoo->x()&&x()+pixmap().width()<460) {
            setPos(x() + qAbs(speed), y()); // Move right towards Kimo
        }
    }
    else {
        // Normal bouncing movement (if Kimo is far)
        setPos(x() - speed, y());

        // Bounce back when hitting screen edges
        if (x() <= 300 || x() >= 460 - pixmap().width()) {
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
