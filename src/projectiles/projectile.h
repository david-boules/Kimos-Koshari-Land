#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>

class Projectile : public QObject, public QGraphicsPixmapItem {
Q_OBJECT

public:
    Projectile(QGraphicsItem *parent = nullptr);
    QPixmap sprite;

    virtual void hit(QGraphicsItem* target) = 0; // Pure virtual function to damage/destroy object hit by the projectile (varies by class)

public slots:
    void pause() {if (moveTimer && moveTimer->isActive()) moveTimer->stop();}
    void resume() { if (moveTimer && !moveTimer->isActive()) moveTimer->start(16);}

protected:              // 'Protected' so inheriting classes can access these variables:
    int speed;          // Projectile's speed magnitude
    int direction = 1;  // Projectile's direction (1 for right, -1 for left)
    QTimer* moveTimer;  // Timer to move the projectile smoothly

private slots:
    void move();            // Function that moves the projectiles (private is fine, despite inheritance)
                            // Because 'Projectile' handles the slot and can connect signals

};

#endif // PROJECTILE_H

