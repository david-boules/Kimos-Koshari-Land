#include "boss.h"
#include "macaroni.h"
#include <QGraphicsScene>

Boss::Boss(QString pixmap, QPointF start, QGraphicsItem* parent)
    : Enemy(QPixmap(pixmap), start, parent) {

    speed=2;
    damage=3;
    health=5;
    max_health=5;
    update_health_bar();

    boss_img = QPixmap(":/images/enemies/abou-tarek.png").scaled(200, 200, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    setPixmap(boss_img);


    shoot_timer = new QTimer(this);
    connect(shoot_timer, &QTimer::timeout, this, &Boss::shoot_macaroni);
    shoot_timer->start(3000);

    move_timer = new QTimer(this);
    connect(move_timer, &QTimer::timeout, this, &Boss::move);
    move_timer->start(16);

}

void Boss::shoot_macaroni(){
    if (!kimoo || !scene()) return;

    if (qAbs(kimoo->y() - y()) <= 170 && qAbs(kimoo->x() - x()) <= 300) {
        QPixmap macPixmap(":/images/enemies/macaroni.png");
        QPointF spawnPos(x(), y() + 100);

        macaroni* mc = new macaroni(macPixmap, spawnPos);
        mc->setTargetKimo(kimoo);
        mc->setMoveStyle(macaroni_move::level5);
        scene()->addItem(mc);
    }
}

void Boss::move() {
    if (kimoo && collidesWithItem(kimoo)) {
        kimoo->takeDamage(3);
    }

    setPos(x() - speed, y());


    if (x() <= 1500|| x() >= 1700) {
        speed = -speed; // Change direction
    }
};
