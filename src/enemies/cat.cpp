#include "cat.h"

cat::cat(QString leftPath, QString rightPath, QPointF startPos, QGraphicsItem* parent)
    : Enemy(QPixmap(leftPath), startPos, parent) // start facing left
{
  //  setPos(startPos);


    speed=2;
    health=3;
    damage=3;
    max_health=3;
    update_health_bar();
    cat_left_img = QPixmap(leftPath).scaled(60, 60);
    cat_right_img = QPixmap(rightPath).scaled(60, 60);
     originalPos = startPos;  //save the original poistion to make cat return back
}



void cat::setMoveStyle(cat_move style) {
    moveStyle = style;
}

cat_move cat::getMoveStyle() const {
    return moveStyle;
}




void cat::move() {
    if (!kimoo) return;

    qreal dx = kimoo->x() - x();
    qreal dy = kimoo->y() - y();

    if (!isJumping) {
        if (jumpCooldownStarted && jumpCooldown.elapsed() < 200) {

            return;
        }
    }



    // 1. Trigger jump only once, when Kimo is on the left and within range
    if (!isJumping && qAbs(dx) < 200 && qAbs(dy) < 50)
     {
        if (kimoo->x() < 320+pixmap().width() || kimoo->x() > 950 - pixmap().width()) return;
        isJumping = true;
        angle = 0.0;
        jumpStartPos = pos();
        jumpTargetPos = QPointF(kimoo->pos().x(), jumpStartPos.y()); // use fixed y value
        if (kimoo->x() > x())
            setPixmap(cat_right_img);
        else
            setPixmap(cat_left_img);
        return;
    }

    //  Perform sine-curve jump toward Kimo
    if (isJumping) {
        angle += 0.1;

        // Linear horizontal interpolation
        qreal progress = angle / 3.14; // π is one full half sine wave
        if (progress > 1.0) progress = 1.0;

        qreal newX = jumpStartPos.x() + (jumpTargetPos.x() - jumpStartPos.x()) * progress;
        qreal newY = jumpStartPos.y() + qSin(angle) * -25; // -25 = jump height

        setPos(newX, newY);

        // End of jump
        if (angle >= 3.14) {
            isJumping = false;
            angle = 0.0;
            setY(jumpStartPos.y());

            // make y
            jumpTargetPos = QPointF(kimoo->pos().x(), jumpStartPos.y());

            // Deal damage only if it lands and collides
            if (collidesWithItem(kimoo)) {
                kimoo->takeDamage(damage);

                isReturning = true;
                angle = 0.0;
                returnStartPos = pos();
                returnTargetPos = originalPos;
            }
            jumpCooldown.restart();          // Restart timer
            jumpCooldownStarted = true;
        }

        return;
    }



    if (isReturning && moveStyle == cat_move::level4) {
        angle += 0.1;
        qreal progress = angle / 3.14;
        if (progress > 1.0) progress = 1.0;

        qreal newX = returnStartPos.x() + (returnTargetPos.x() - returnStartPos.x()) * progress;
        qreal newY = returnStartPos.y() + qSin(angle) * -25;
        setPos(newX, newY);

        if (angle >= 3.14) {
            isReturning = false;
            angle = 0.0;
            setPos(originalPos);  // Snap exactly back
        }
        return;
    }


    switch (moveStyle)
    {
    case cat_move::level3:

    //  Regular speed
    setPos(x() + speed, y());

    if (x() <= 320 || x() >= 950 - pixmap().width()) {
        speed = -speed;
    }

    setPixmap(speed > 0 ? cat_right_img : cat_left_img);
    break;



    case cat_move::level4:

        if (!kimoo) return;

        if (kimoo->x() < x()) {
            setPixmap(cat_left_img);
        } else {
            setPixmap(cat_right_img);
        }
        break;

}



}


