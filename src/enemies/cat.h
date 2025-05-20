#ifndef CAT_H
#define CAT_H

#include "enemy.h"
#include <QTimer>

enum class cat_move { level3,level4 };

class cat : public Enemy {
    Q_OBJECT
public:
    cat(QString leftPath, QString rightPath, QPointF startPos, QGraphicsItem* parent = nullptr);
    void setRange(qreal minX, qreal maxX);
    void move() override;

    void setMoveStyle(cat_move style);
    cat_move getMoveStyle() const;


private:
    QTimer* moveTimer;
    QPixmap cat_left_img;
    QPixmap cat_right_img;
    qreal speed;
    qreal damage;
    qreal rangeMin = 100;
    qreal rangeMax = 800;
    QPointF originalPos;



    bool hasJumped = false;
    bool isJumping = false;
    qreal angle = 0.0;
    QPointF jumpStartPos;
    QPointF jumpTargetPos;

    bool isReturning = false;
    QPointF returnStartPos;
    QPointF returnTargetPos;


    cat_move moveStyle= cat_move::level3;


};

#endif // CAT_H
