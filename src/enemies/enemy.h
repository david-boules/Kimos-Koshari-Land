#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>
#include "kimo.h"

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Enemy(QPixmap path, QPointF startingPos, QGraphicsItem* parent = nullptr);
    void setTargetKimo(Kimo* kimo) { kimoo = kimo; }
    void SetHealth(int health);
    void setSpeed(qreal s);
    int get_enemy_health() const;
    void takedamage(int enemydamage);
    void update_health_bar();
    virtual bool can_be_inhaled() const {
        return true;
    }

public slots:
    void pause();
    void resume();

signals:
    void enemyDefeated(Enemy* enemy);

private slots:
    virtual void move()=0;
protected:
    qreal speed;
    Kimo* kimoo;
    qreal damage;
    int health;
    int max_health;

private:
    QTimer* moveTimer;

    QGraphicsRectItem* healthBar;
    QGraphicsRectItem* healthBarBackground;
    QGraphicsTextItem* enemy_health;

};

#endif // ENEMY_H
