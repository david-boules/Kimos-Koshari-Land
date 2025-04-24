#include "kimo.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <platform.h>

Kimo::Kimo(QGraphicsItem * parent) : QGraphicsPixmapItem(parent) {
    // Load and scale the character sprite
    QPixmap KimoLarge(":/images/Kimo.png");
    QPixmap Kimo = KimoLarge.scaled(64, 64);
    setPixmap(Kimo);

    // Set up physics timer for smooth movement
    physicsTimer = new QTimer(this);
    connect(physicsTimer, SIGNAL(timeout()), this, SLOT(updatePhysics()));
    physicsTimer->start(16); // ~60 FPS for smooth physics
}

void Kimo::keyPressEvent(QKeyEvent * event) {
    // Handle horizontal movement
    if (event->key() == Qt::Key_Left) {
        horizontalVelocity = -5.0; // Move left
    }
    else if (event->key() == Qt::Key_Right) {
        horizontalVelocity = 5.0; // Move right
    }
    // Handle jumping (only when grounded)
    else if (event->key() == Qt::Key_Up && isGrounded) {
        jump();
    }
    // Handle crouching (placeholder for future implementation)
    else if (event->key() == Qt::Key_Down) {
        //crouch
    }
}

void Kimo::keyReleaseEvent(QKeyEvent * event) {
    // Stop horizontal movement when keys are released
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        horizontalVelocity = 0;
    }
}

void Kimo::jump() {
    if (isGrounded) {
        verticalVelocity = jumpForce;
        isJumping = true;
        isGrounded = false;
    }
}

void Kimo::updatePhysics() {
    // Check if we're still on a platform
    bool wasGrounded = isGrounded;
    isGrounded = false;
    
    // Check for platform directly below us
    QList<QGraphicsItem*> itemsBelow = scene()->items(QPointF(x() + pixmap().width()/2, y() + pixmap().height() + 1));
    for (QGraphicsItem* item : itemsBelow) {
        if (typeid(*item) == typeid(Platform)) {
            isGrounded = true;
            break;
        }
    }

    // Apply gravity when not grounded
    if (!isGrounded) {
        verticalVelocity += gravity;
        if (verticalVelocity > maxFallSpeed) {
            verticalVelocity = maxFallSpeed;
        }
    }

    // Apply horizontal movement with air control
    double controlFactor = isGrounded ? groundControlFactor : airControlFactor;
    setPos(x() + horizontalVelocity * controlFactor, y() + verticalVelocity);

    // Check for collisions with platforms
    checkCollision();
}

void Kimo::checkCollision() {
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Platform)) {
            // Check if collision is from above (landing on platform)
            if (verticalVelocity > 0 && y() < colliding_items[i]->y()) {
                setPos(x(), colliding_items[i]->y() - pixmap().height());
                verticalVelocity = 0;
                isGrounded = true;
                isJumping = false;
            }
            // Check if collision is from below (hitting head)
            else if (verticalVelocity < 0) {
                setPos(x(), colliding_items[i]->y() + colliding_items[i]->boundingRect().height());
                verticalVelocity = 0;
            }
            // Check if collision is from the sides
            else {
                if (horizontalVelocity > 0) { // Moving right
                    setPos(colliding_items[i]->x() - pixmap().width(), y());
                }
                else if (horizontalVelocity < 0) { // Moving left
                    setPos(colliding_items[i]->x() + colliding_items[i]->boundingRect().width(), y());
                }
            }
        }
    }
}

void Kimo::setGravity(bool enabled) {
    if (!enabled) {
        verticalVelocity = 0;
    }
}

void Kimo::setJumpVelocity(double velocity) {
    jumpForce = -velocity; // Negative because upward movement is negative in Qt's coordinate system
}

void Kimo::setAirControl(bool enabled) {
    airControlEnabled = enabled;
}
