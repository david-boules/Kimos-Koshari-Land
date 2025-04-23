#ifndef KIMO_H
#define KIMO_H
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>

class Kimo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Kimo(QGraphicsItem *parent = nullptr);
public:
    void keyPressEvent(QKeyEvent * event);
    void jump();
private slots:
    void jumpChange(); //must be a slot to connect to a timer
private:
    QTimer * jumpTimer;
    bool isJumping = false; //used as a condition to start jumping animation
    bool isGrounded = true; //doubles as checking if character jumping to prevent double jumps
    int jumpChanges = 0;
};

#endif // KIMO_H
