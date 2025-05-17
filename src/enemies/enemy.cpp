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

    healthBarBackground = new QGraphicsRectItem(0, 0, 60, 6, this);
    healthBarBackground->setBrush(Qt::black);
    healthBarBackground->setPos(0, -10);

    healthBar= new QGraphicsRectItem(0,0,60,6,healthBarBackground);
    healthBar->setBrush(Qt::green);

    enemy_health = new QGraphicsTextItem(QString::number(health), healthBarBackground);
    enemy_health->setPos(25, -8);
    enemy_health->setDefaultTextColor(Qt::white);


    // Set up movement timer for smooth update
    moveTimer = new QTimer(this);
    connect(moveTimer, SIGNAL(timeout()), this, SLOT(move()));
    moveTimer->start(16); // ~60 FPS
}

void Enemy::setSpeed(qreal s) {
    speed = s;
}

void Enemy::update_health_bar() {
    if (max_health <= 0) return;  // Prevent division by zero

    qreal percentage = static_cast<qreal>(health) / static_cast<qreal>(max_health);
    percentage = qMax(0.0, percentage); // Avoid negative bar

    healthBar->setRect(0, 0, 60 * percentage, 6);

    if (enemy_health) {
        enemy_health->setPlainText(QString::number(health));
    }
}



void Enemy::takedamage(int enemydamage){
    health -= enemydamage;
     update_health_bar();
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
