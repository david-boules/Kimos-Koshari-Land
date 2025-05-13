#include "enemy.h"
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QBrush>
#include <QGraphicsScene>
#include <QDebug>

Enemy::Enemy(QPixmap pixmap, QPointF startingPos, QGraphicsItem* parent) : QObject(nullptr), QGraphicsPixmapItem(parent)
{
    QPixmap scaled = pixmap.scaled(60,60);
    setPixmap(scaled);
    setPos(startingPos);  // Starting position


    //health=3;

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

void Enemy::setSpeed(qreal s) {
    speed = s;
}
void Enemy::takedamage(int enemydamage){
    health -= enemydamage;
//     if (health <= 0) {
//         scene()->removeItem(this);
//         deleteLater();
// }
}
int Enemy::get_enemy_health()const{
    return health;
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
