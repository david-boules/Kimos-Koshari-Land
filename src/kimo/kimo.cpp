#include "kimo.h"
#include "enemy.h"
#include "macaronimissile.h"
#include <QKeyEvent>
#include <QString>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <platform.h>
#include <QGraphicsView> // Added for view reference
#include <QRectF> // Added for sceneRect

Kimo::Kimo(QGraphicsItem * parent) : QGraphicsPixmapItem(parent) {
    // Load and scale the character sprites (for different states)
    normalKimo = QPixmap(":/images/kimo/Kimo.png").scaled(64,64);
    inhalingKimo = QPixmap(":/images/kimo/Kimo_inhale").scaled(64,64);
    fullKimo = QPixmap(":/images/kimo/Kimo_full.png").scaled(64,64);
    spittingKimo = QPixmap(":/images/kimo/Kimo_spit.png").scaled(64,64);

    // Set up physics timer for smooth movement
    physicsTimer = new QTimer(this);
    connect(physicsTimer, SIGNAL(timeout()), this, SLOT(updatePhysics()));
    physicsTimer->start(16); // ~60 FPS for smooth physics
}

// Added implementation for setView
void Kimo::setView(QGraphicsView* v) {
    view = v;
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

    // Calculate potential next position
    double controlFactor = isGrounded ? groundControlFactor : airControlFactor;
    double nextX = x() + horizontalVelocity * controlFactor;
    double nextY = y() + verticalVelocity;

    // Get scene boundaries
    QRectF sceneBounds = scene()->sceneRect();

    // --- Scene Border Implementation START ---
    // Check horizontal boundaries
    if (nextX < sceneBounds.left()) {
        nextX = sceneBounds.left();
        horizontalVelocity = 0; // Stop horizontal movement at the edge
    } else if (nextX + pixmap().width() > sceneBounds.right()) {
        nextX = sceneBounds.right() - pixmap().width();
        horizontalVelocity = 0; // Stop horizontal movement at the edge
    }

    // Check top boundary
    if (nextY < sceneBounds.top()) {
        nextY = sceneBounds.top();
        verticalVelocity = 0; // Stop vertical movement at the edge
    }
    // --- Scene Border Implementation END ---

    // Check if Kimo fell off the bottom (existing logic)
    if (nextY > sceneBounds.bottom() + 50) { // Added a small buffer below scene bottom before respawn
        respawn();
        return; // Skip position update and collision check after respawn
    }

    // Apply final position
    setPos(nextX, nextY);

    // Check for collisions with platforms (after position update)
    checkCollision();

    // Update view to follow Kimo (Scrolling Camera)
    if (view) {
        // Center view, but constrain it within scene boundaries
        qreal viewCenterX = qBound(view->width() / 2.0, x() + pixmap().width() / 2.0, sceneBounds.right() - view->width() / 2.0);
        qreal viewCenterY = qBound(view->height() / 2.0, y() + pixmap().height() / 2.0, sceneBounds.bottom() - view->height() / 2.0);
        view->centerOn(viewCenterX, viewCenterY);
    }
}

void Kimo::checkCollision() {
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {
        // Check for any platform type using dynamic_cast
        if (Platform* platform = dynamic_cast<Platform*>(colliding_items[i])) {
            QRectF kimoRect = this->sceneBoundingRect();
            QRectF platformRect = platform->sceneBoundingRect();

            // Calculate intersection
            QRectF intersection = kimoRect.intersected(platformRect);

            // Check if collision is primarily vertical (landing or hitting head)
            if (intersection.width() > intersection.height()) {
                // Collision from above (landing on platform)
                if (verticalVelocity > 0 && kimoRect.bottom() > platformRect.top() && kimoRect.top() < platformRect.top()) {
                    setPos(x(), platformRect.top() - pixmap().height());
                    verticalVelocity = 0;
                    isGrounded = true;
                    isJumping = false;

                    // Check for specific platform types
                    if (dynamic_cast<SpikyPlatform*>(platform)) {
                        // Standing on a spiky platform: take damage
                        takeDamage(1); // Damage amount can be adjusted
                    }
                }
                // Collision from below (hitting head)
                else if (verticalVelocity < 0 && kimoRect.top() < platformRect.bottom() && kimoRect.bottom() > platformRect.bottom()) {
                    setPos(x(), platformRect.bottom());
                    verticalVelocity = 0;
                }
            }
            // Check if collision is primarily horizontal
            else if (intersection.height() > intersection.width()) {
                 // Collision from the right side (hitting platform's left edge)
                if (horizontalVelocity > 0 && kimoRect.right() > platformRect.left() && kimoRect.left() < platformRect.left()) {
                    setPos(platformRect.left() - pixmap().width(), y());
                    horizontalVelocity = 0;
                }
                // Collision from the left side (hitting platform's right edge)
                else if (horizontalVelocity < 0 && kimoRect.left() < platformRect.right() && kimoRect.right() > platformRect.right()) {
                    setPos(platformRect.right(), y());
                    horizontalVelocity = 0;
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
if (damageTimer.elapsed() < 1000) return; // Only take damage once per second
    damageTimer.restart();

    health -= amount;
    if (healthText) { // Check if healthText is valid
         healthText->setPlainText("Health: " + QString::number(health)); // Updating health on screen
    }
    if(isDead()) {
        respawn();
    }
}

bool Kimo::isDead() const {
    return health <= 0;
}

void Kimo::respawn() {
    //Instead of deleting the object which could cause some issues with other functions, we relocate Kimo and reset the key physics
    this->setPos(100, 400); // Reset to initial position
    verticalVelocity = 0;
    horizontalVelocity = 0;
    health=3; // Reset health
    if (healthText) { // Update health display on respawn
         healthText->setPlainText("Health: " + QString::number(health));
    }
    currentState = Normal; // Reset state
    updateSprite();
}

void Kimo::inhale() {
    for(int i = 0; i< scene()->items().size(); i++) {
        if(Enemy* enemy = dynamic_cast <Enemy*>(scene()->items()[i])) {
            // Check distance and relative position for inhale
            if(abs(x() - enemy->x()) < 100 && abs(y() - enemy->y()) < 50) { // Increased inhale range slightly
                // Check if enemy is generally in front based on horizontal velocity or default right
                bool facingRight = horizontalVelocity >= 0; // Simple check, could be refined
                if ((facingRight && enemy->x() > x()) || (!facingRight && enemy->x() < x())) {
                    scene()->removeItem(enemy);
                    enemy->deleteLater(); // A Qt-safe way to delelte an object after events and singals are finished
                    currentState = Full;
                    updateSprite();
                    break; // Inhale only one enemy at a time
                }
            }
        }
    }
}

void Kimo::spit() {
    currentState = Spitting;
    updateSprite();
    QTimer::singleShot(400, this, SLOT(finishSpit()));
    // Projectile is created then spat
    MacaroniMissile* missile = new MacaroniMissile();
    // Adjust spawn position based on Kimo's facing direction (simple check)
    bool facingRight = horizontalVelocity >= 0;
    qreal missileX = facingRight ? x() + pixmap().width() : x() - missile->pixmap().width();
    missile->setPos(missileX, y() + 20);
    // Set missile direction
    missile->setDirection(facingRight ? 1 : -1);
    scene()->addItem(missile);
}

void Kimo::finishSpit() {
    currentState = Normal;
    updateSprite();
}

