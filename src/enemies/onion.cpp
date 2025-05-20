#include "onion.h"

// onion::onion(Qstring rightImage, QString leftImage, QPointF startingPos, QGraphicsItem* parent)
//     : Enemy(QPixmap(rightImage), startingPos, parent), angle(0),rightPixmap(QPixmap(rightImage)), leftPixmap(QPixmap(leftImage)){

onion::onion(QString imagePath, QPointF startingPos, QGraphicsItem* parent)
    : Enemy(QPixmap(imagePath), startingPos, parent),
      rightPixmap(QPixmap(imagePath)), leftPixmap(QPixmap(imagePath)), has_left_and_right(false)
{

    speed=2.0;
    damage=1;
    health=1;
    max_health=1;
    update_health_bar();
    original_y=pos().y();

    poisonCooldown.start();


    // shootTimer = new QTimer(this);
    // connect(shootTimer, &QTimer::timeout, this, &onion::shoot_poison);
    // shootTimer->start(200); // Shoot every 0.8 seconds 800


}

onion::onion(QString left_image, QString right_image, QPointF startingPos, QGraphicsItem* parent)
    : Enemy(QPixmap(left_image), startingPos, parent),
    //leftPixmap(QPixmap(left_image)), rightPixmap(QPixmap(right_image)),
    leftPixmap(QPixmap(left_image).scaled(60, 60)),
    rightPixmap(QPixmap(right_image).scaled(64, 64)),
    has_left_and_right(true)
{
    speed = 2.0;
    damage = 1;
    health = 1;
    max_health = 1;
    update_health_bar();
    original_y = pos().y();
    poisonCooldown.start();
}





void onion::setMoveStyle(onion_move style) {
    moveStyle = style;
}

onion_move onion::getMoveStyle() const {
    return moveStyle;
}


void onion::shoot_poison(){
    if (!kimoo || !scene()) return;
    if (poisonCooldown.elapsed() < 300) return;

    //  Reset cooldown timer
    poisonCooldown.restart();

    if (qAbs(kimoo->y() - y()) <= 40  && qAbs(kimoo->x() - x()) <= 250){


        qreal direction = (kimoo->x() < x()) ? -1 : 1; // Left or right
        Poison* p = new Poison(direction);
        p->setPos(x(), y() + 20); // Starting position slightly below the enemy
        scene()->addItem(p);


    }
}




void onion::move() {

    if (kimoo && collidesWithItem(kimoo)) {
        kimoo->takeDamage(damage);
        double knockbackForce = -8.0; // Upward force
        double horizontalKnockback = (kimoo->x() < x() + pixmap().width() / 2) ? -5.0 : 5.0; // Left or right knockback

        // Set Kimo's velocities for knockback
        kimoo->setKnockback(knockbackForce, horizontalKnockback);


        // qreal Direction = (kimoo->x() < x()) ? 1 : -1;
        // kimoo->setPos(kimoo->x() - Direction * 120, kimoo->y());

        // scene()->removeItem(this);
        // delete this;
        // return;
    }

    switch (moveStyle)
    {
    case onion_move::level1:


    angle += 0.1;
    setPos(x() -speed, y() + qSin(angle) * 3.5);
    if (x() <= minX || x() >= maxX - pixmap().width()) {
        speed = -speed; // bounce between minX and maxX
    }
    break;

    case onion_move::level2:
        angle += 0.1;
        setPos(x() -speed, y() + qSin(angle) * 3.5);
        if (x() <= 500 || x() >= 800 - pixmap().width()) {
            speed = -speed; // bounce between minX and maxX
        }

break;

    case onion_move::level2_1:
        angle += 0.1;
        setPos(x() -speed, y() + qSin(angle) * 2.0);
        if (x() <= 1220 || x() >= 1310) {
            speed = -speed; // bounce between minX and maxX
        }
        break;

    case onion_move::level3_1:  //first eagle
 is_jumping = false;
        angle += 0.1;
        setPos(x() -speed, y() + qSin(angle) * 3.5);

        if (has_left_and_right) {
            if (speed > 0) {
                setPixmap(leftPixmap);
            } else {
                setPixmap(rightPixmap);
            }
        }

        if (x() <= 0 || x() >= 400 - pixmap().width()) {
            speed = -speed; // bounce between minX and maxX
        }
        break;


    case onion_move::level3_2:  //second eagle
is_jumping = false;
        angle += 0.1;
        setPos(x() -speed, y() + qSin(angle) * 3.5);

        if(has_left_and_right){

        if (speed > 0) {
                setPixmap(leftPixmap);  // left-facing image
        } else {
            setPixmap(rightPixmap);   // right-facing image
        }
        }

        if (x() <= 600 || x() >= 1100 - pixmap().width()) {
            speed = -speed; // bounce between minX and maxX
        }
        break;





    case onion_move::level3:{


        if (!kimoo) break;

            is_jumping = true;

            // Update jump angle
            jump += 0.1;
            if (jump >= 3.14) jump = 0;

            // Vertical jump using sine wave
            qreal jumpY = original_y + qSin(jump) * -50;  // -20 = jump height
            setY(jumpY);

            shoot_poison();



            break;
    }


    case onion_move::level4:{  //first eagle
        is_jumping = false;
        angle += 0.1;
        setPos(x() -speed, y() + qSin(angle) * 3.5);

        if (has_left_and_right) {
            if (speed > 0) {
                setPixmap(leftPixmap);
            } else {
                setPixmap(rightPixmap);
            }
        }

        if (x() <= 380 || x() >= 660 - pixmap().width()) {
            speed = -speed; // bounce between minX and maxX
        }
        break;
    }





}

}

;


