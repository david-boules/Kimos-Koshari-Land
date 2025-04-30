#include "kimo.h"
#include "enemy.h"
#include <QKeyEvent>
#include <QString>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <platform.h>

Kimo::Kimo(QGraphicsItem * parent) : QGraphicsPixmapItem(parent) {
    // Load and scale the character sprites (for different states)
    normalKimo = QPixmap(":/images/Kimo.png").scaled(64,64);
    inhalingKimo = QPixmap(":/images/Kimo_inhale").scaled(64,64);
    fullKimo = QPixmap(":/images/Kimo_full.png").scaled(64,64);
    spittingKimo = QPixmap(":/images/Kimo_spit.png").scaled(64,64);

    // Set up physics timer for smooth movement
    physicsTimer = new QTimer(this);
    connect(physicsTimer, SIGNAL(timeout()), this, SLOT(updatePhysics()));
    physicsTimer->start(16); // ~60 FPS for smooth physics
}

void Kimo::updateSprite() {
    if(currentState == Normal)
        setPixmap(normalKimo);
    else if(currentState == Inhaling)
        setPixmap(inhalingKimo);
    else if(currentState == Full)
        setPixmap(fullKimo);
    else if(currentState == Spitting)
        setPixmap(spittingKimo);
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
        if(currentState == Normal) {
            horizontalVelocity = -5.0; // Move left
        }
        else if(currentState == Full) {
            horizontalVelocity = -2.0; // Moves slower when full
        }
    }
    else if (event->key() == Qt::Key_Right) {
        if(currentState == Normal) {
            horizontalVelocity = 5.0; // Move right
        }
        else if(currentState == Full) {
            horizontalVelocity = 2.0; // Moves slower when full
        }
    }
    // Handle jumping (only when grounded)
    else if (event->key() == Qt::Key_Up && isGrounded) {
        jump();
    }
    // Handle crouching (placeholder for future implementation)
    else if (event->key() == Qt::Key_Down) {
        //crouch
    }
    else if (event->key() == Qt::Key_Space) {
        if(currentState == Normal){
            currentState = Inhaling;
            inhale();
            updateSprite();
        }
        else if (currentState == Full) {
            spit();
        }

    }
}

void Kimo::keyReleaseEvent(QKeyEvent * event) {
    // Stop horizontal movement when keys are released
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_Right) {
        horizontalVelocity = 0;
    }
    if (event->key() == Qt::Key_Space) {
        if(currentState == Inhaling){
            currentState = Normal;
            updateSprite();
        }
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

void Kimo::takeDamage(int amount) {
    health -= amount;
    if(isDead()) {
        respawn();
    }
    healthText->setPlainText("Health: " + QString::number(health)); // Updating health on screen
}

bool Kimo::isDead() const {
    return health <= 0;
}

void Kimo::respawn() {
    //Instead of deleting the object which could cause some issues with other functions, we relocate Kimo and reset the key physics
    this->setPos(100, 400);
    verticalVelocity = 0;
    horizontalVelocity = 0;
    health=3;
}

void Kimo::inhale() {
    for(int i = 0; i< scene()->items().size(); i++) {
        if(Enemy* enemy = dynamic_cast <Enemy*>(scene()->items()[i])) {
            if(x() < enemy->x() && abs(x() - enemy->x()) < 70 && abs(y() - enemy->y()) < 30) {
                scene()->removeItem(enemy);
                enemy->deleteLater(); // A Qt-safe way to delelte an object after events and singals are finished
                currentState = Full;
                updateSprite();
                break;
            }
        }
    }
}

void Kimo::spit() {
    currentState = Spitting;
    updateSprite();
    QTimer::singleShot(400, this, SLOT(finishSpit()));
    // Projectile is created then spat

}

void Kimo::finishSpit() {
    currentState = Normal;
    updateSprite();
}
