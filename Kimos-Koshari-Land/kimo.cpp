#include "kimo.h"
#include <QKeyEvent>
#include <QString>
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

/* Movement & Physics functions
keyPressEvent
keyReleaseEvent
jump
crouch (not yet implemented)
updatePhysics
checkCollision
setGravity
setJumpVelocity
setAirControl
 */
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
    // Fix edge bug: Check for platform under both left and right edges of the character
    bool wasGrounded = isGrounded;
    isGrounded = false;
    int footY = y() + pixmap().height() + 1;

    // Check left foot
    bool leftFootOnPlatform = false;
    QList<QGraphicsItem*> itemsBelowLeft = scene()->items(QPointF(x() + 2, footY));
    for (QGraphicsItem* item : itemsBelowLeft) {
        if (dynamic_cast<Platform*>(item)) {
            leftFootOnPlatform = true;
            break;
        }
    }

    // Check right foot
    bool rightFootOnPlatform = false;
    QList<QGraphicsItem*> itemsBelowRight = scene()->items(QPointF(x() + pixmap().width() - 2, footY));
    for (QGraphicsItem* item : itemsBelowRight) {
        if (dynamic_cast<Platform*>(item)) {
            rightFootOnPlatform = true;
            break;
        }
    }

    isGrounded = leftFootOnPlatform || rightFootOnPlatform;

    // Apply gravity when not grounded
    if (!isGrounded) {
        verticalVelocity += gravity;
        if (verticalVelocity > maxFallSpeed) {
            verticalVelocity = maxFallSpeed;
        }
    }

    if (y() > 650) {
        respawn(); // Kimo respawns if he falls of the screen
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
        // Check for any platform type using dynamic_cast
        if (Platform* platform = dynamic_cast<Platform*>(colliding_items[i])) {
            // Check if collision is from above (landing on platform)
            if (verticalVelocity > 0 && y() < platform->y()) {
                setPos(x(), platform->y() - pixmap().height());
                verticalVelocity = 0;
                isGrounded = true;
                isJumping = false;

                // Check for specific platform types
                if (dynamic_cast<StaticPlatform*>(platform)) {
                    // Standing on a static platform: do nothing special
                } else if (dynamic_cast<MovingPlatform*>(platform)) {
                    // Standing on a moving platform: do nothing special (could add logic to move with platform)
                } else if (dynamic_cast<SpikyPlatform*>(platform)) {
                    // Standing on a spiky platform: TODO - take damage (to be implemented by your colleague)
                }
            }
            // Check if collision is from below (hitting head)
            else if (verticalVelocity < 0) {
                setPos(x(), platform->y() + platform->boundingRect().height());
                verticalVelocity = 0;
            }
            // Check if collision is from the sides
            else {
                if (horizontalVelocity > 0) { // Moving right
                    setPos(platform->x() - pixmap().width(), y());
                }
                else if (horizontalVelocity < 0) { // Moving left
                    setPos(platform->x() + platform->boundingRect().width(), y());
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

/* Gameplay Mechanics functions
 * setHealthText
 * takeDamage
 * isDead
 * respawn
 * inhale (to-do)
 * spit (to-do)
 */

void Kimo::setHealthText(QGraphicsTextItem* text) {
    healthText = text;
}

void Kimo::takeDamage() {
    health -= 1;
    if(isDead()) {
        respawn();
    }
    healthText->setPlainText("Health: " + QString::number(health)); // Updating health on screen
}

bool Kimo::isDead() const {
    return health == 0;
}

void Kimo::respawn() {
    //Instead of deleting the object which could cause some issues with other functions, we relocate Kimo and reset the key physics
    this->setPos(100, 400);
    verticalVelocity = 0;
    horizontalVelocity = 0;
    health=3;
}

void Kimo::inhale() {
    // To-do
}

void Kimo::spit() {
    // To-do
}
