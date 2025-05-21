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


// void cat::setRange(qreal minX, qreal maxX) {
//     rangeMin = minX;
//     rangeMax = maxX;
// }

// void cat::move() {

//     if (kimoo && collidesWithItem(kimoo)) {
//         kimoo->takeDamage(damage);

//     }



//     if (!kimoo) return; // If no Kimo linked, skip

//     // Distance between enemy and Kimo
//     qreal distancex = qAbs(x() - kimoo->x());
//     qreal distancey=qAbs(y()-kimoo->y());




//     setPos(x() - speed, y());

//     if (speed > 0) {
//         setPixmap(cat_left_img);
//     } else {
//         setPixmap(cat_right_img);
//     }

//     if (x() <= 600 || x() >= 1100 - pixmap().width()) {
//         speed = -speed;
//     }
// }


// void cat::move() {
//     if (!kimoo) return;

//     qreal dx = kimoo->x() - x(); // Horizontal distance to Kimo
//     qreal dy = kimoo->y() - y(); // Vertical distance to Kimo

//     // 1. Detect Kimo on the left and within a specific range
//     if (dx < 0 && qAbs(dx) < 200 && qAbs(dy) < 100) {
//         // Face left and stop patrol
//         setPixmap(cat_left_img);

//         // Jump directly towards Kimo's current position
//         setPos(kimoo->x(), kimoo->y());

//         // Apply damage
//         if (collidesWithItem(kimoo)) {
//             kimoo->takeDamage(damage);
//             hasJumped = true; //prevent repeated jumps
//         }

//         return; // Skip regular patrol
//     }


//     if (qAbs(dx) > 300) {
//         hasJumped = false;
//     }


//     // 2. Regular patrol movement
//     setPos(x() + speed, y());

//     // 3. Flip direction at bounds
//     if (x() <= 600 || x() >= 1100 - pixmap().width()) {
//         speed = -speed;
//     }

//     // 4. Update facing image
//     if (speed > 0) {
//         setPixmap(cat_right_img);
//     } else {
//         setPixmap(cat_left_img);
//     }
// }



// void cat::move() { almost work
//     if (!kimoo) return;

//     qreal dx = kimoo->x() - x();
//     qreal dy = kimoo->y() - y();

//     // 1. Start the jump when Kimo is on the left and in range
//     if (!isJumping && dx < 0 && qAbs(dx) < 200 && qAbs(dy) < 50) {
//         isJumping = true;
//         angle = 0.0;
//         jumpStartPos = pos();
//         setPixmap(cat_left_img);
//         return;
//     }

//     // 2. Perform sine-wave jump toward Kimo
//     if (isJumping) {
//         angle += 0.1;

//         // Move horizontally toward Kimo
//         qreal moveX = x() - speed; // toward left
//         // Move vertically in an arc
//         qreal moveY = jumpStartPos.y() + qSin(angle) * -25; // -25 for upward arc

//         setPos(moveX, moveY);

//         // Stop the jump after a full arc
//         if (angle >= 3.14) { // π = half sine wave (up + down)
//             isJumping = false;
//             angle = 0;

//             // Final landing position toward Kimo
//             setPos(kimoo->x(), kimoo->y());

//             // Deal damage if colliding
//             if (collidesWithItem(kimoo)) {
//                 kimoo->takeDamage(damage);
//             }
//         }

//         return; // Skip normal patrol
//     }

//     // 3. Patrol if not jumping
//     setPos(x() + speed, y());

//     if (x() <= 600 || x() >= 1100 - pixmap().width()) {
//         speed = -speed;
//     }

//     setPixmap(speed > 0 ? cat_right_img : cat_left_img);
// }

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
        if (kimoo->x() < 600) return;
        isJumping = true;
        angle = 0.0;
        jumpStartPos = pos();
       // jumpTargetPos = kimoo->pos();
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

    if (x() <= 600 || x() >= 1100 - pixmap().width()) {
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

        // if (collidesWithItem(kimoo)) {
        //     kimoo->takeDamage(damage);
        //     setPos(originalPos);  // Return cat to its initial spawn point
        // }

        break;

}



}


