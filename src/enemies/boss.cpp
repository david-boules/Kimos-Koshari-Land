#include "boss.h"
#include <QGraphicsScene>

Boss::Boss(QString pixmap, QPointF start, QGraphicsItem* parent)
    : Enemy(QPixmap(pixmap), start, parent) {

    speed=2;
    damage=4;
    health=4;
    max_health=4;
    update_health_bar();

    boss_img = QPixmap(pixmap).scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(boss_img);


    shoot_timer = new QTimer(this);
    connect(shoot_timer, &QTimer::timeout, this, &Boss::shoot_chili);
    shoot_timer->start(900);


   // boss_img=QPixmap(pixmap).scaled(200,200);
}

void Boss::shoot_chili(){
    if (!kimoo || !scene()) return;

    if (qAbs(kimoo->y() - y()) <= 200 && qAbs(kimoo->x() - x()) <= 300){


        qreal direction = (kimoo->x() < x()) ? -1 : 1; // Left or right
        fire_chili* fc = new fire_chili(direction);
        fc->setPos(x(), y() + 60); // Starting position slightly below the enemy

        scene()->addItem(fc);

    }
}



void Boss::move() {
    // Placeholder: no movement yet
    setPos(x() - speed, y());


    if (x() <= 1450|| x() >= 1560) {
        speed = -speed; // Change direction
    }
};
