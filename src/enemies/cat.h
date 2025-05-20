#ifndef CAT_H
#define CAT_H

#include "enemy.h"
#include <QTimer>

class cat : public Enemy {
    Q_OBJECT
public:
    cat(QString leftPath, QString rightPath, QPointF startPos, QGraphicsItem* parent = nullptr);
    void setRange(qreal minX, qreal maxX);
    void move() override;

private:
    QTimer* moveTimer;
    QPixmap cat_left_img;
    QPixmap cat_right_img;
    qreal speed;
    qreal damage;
    qreal rangeMin = 100;
    qreal rangeMax = 800;


    bool hasJumped = false;
    bool isJumping = false;
    qreal angle = 0.0;
    QPointF jumpStartPos;
    QPointF jumpTargetPos;


};

#endif // CAT_H
