#include "kimo.h"
#include "enemy.h"
#include "macaronimissile.h"
#include <QKeyEvent>
#include <QString>
#include <QGraphicsScene>
#include "QElapsedTimer"
#include <QTimer>
#include <QList>
#include <platform.h>
#include <QGraphicsView> // Added for view reference
#include <QRectF> // Added for sceneRect

Kimo::Kimo(QGraphicsItem * parent) : QGraphicsPixmapItem(parent) {
    // Load and scale the character sprites (for different states)
    normalRightKimo = QPixmap(":/images/kimo/Kimo_right.png").scaled(64,64);
    normalLeftKimo = QPixmap(":/images/kimo/Kimo_left.png").scaled(64,64);
    inhalingRightKimo = QPixmap(":/images/kimo/Kimo_inhaleRight.png").scaled(64,64);
    inhalingLeftKimo = QPixmap(":/images/kimo/Kimo_inhaleLeft.png").scaled(64,64);
    fullRightKimo = QPixmap(":/images/kimo/Kimo_fullRight.png").scaled(64,64);
    fullLeftKimo = QPixmap(":/images/kimo/Kimo_fullLeft.png").scaled(64,64);
    spittingRightKimo = QPixmap(":/images/kimo/Kimo_spitRight.png").scaled(64,64);
    spittingLeftKimo = QPixmap(":/images/kimo/Kimo_spitLeft.png").scaled(64,64);

    // Initialize the damage timer
    damageTimer.start();

    // Set up physics timer for smooth movement
    physicsTimer = new QTimer(this);
    connect(physicsTimer, SIGNAL(timeout()), this, SLOT(updatePhysics()));
    physicsTimer->start(16); // ~60 FPS for smooth physics
}

// Added implementation for setView
void Kimo::setView(QGraphicsView* v) {
    view = v;
}

// Updating Kimo's sprite based on his current state
void Kimo::updateSprite() {
    if(currentState == NormalRight)
        setPixmap(normalRightKimo);
    else if(currentState == NormalLeft)
        setPixmap(normalLeftKimo);
    else if(currentState == Inhaling) {
        if(lastDirection == Left)
            setPixmap(inhalingLeftKimo);
        else
            setPixmap(inhalingRightKimo);
    }
    else if(currentState == Full) {
        if(lastDirection == Left){
            setPixmap(fullLeftKimo);
        } else {
            setPixmap(fullRightKimo);
        }
    }
    else if(currentState == Spitting) {
        if(lastDirection == Left){
            setPixmap(spittingLeftKimo);
        } else {
            setPixmap(spittingRightKimo);
        }
    }
}

void Kimo::setGoal(QGraphicsRectItem* g) {
    goal = g;
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
        lastDirection = Left;
        if(currentState == NormalRight || currentState == NormalLeft) {
            currentState = NormalLeft;
            updateSprite();
            horizontalVelocity = -5.0; // Move left
        }
        else if(currentState == Full) {
            horizontalVelocity = -2.0; // Moves slower when full
            updateSprite();
        }
    }
    else if (event->key() == Qt::Key_Right) {
        lastDirection = Right;
        if(currentState == NormalRight || currentState == NormalLeft) {
            currentState = NormalRight;
            updateSprite();
            horizontalVelocity = 5.0; // Move right
        }
        else if(currentState == Full) {
            horizontalVelocity = 2.0; // Moves slower when full
            updateSprite();
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
        if(currentState != Full){
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
            if (lastDirection == Left)
                currentState = NormalLeft;
            else if (lastDirection == Right)
                currentState = NormalRight;
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
        // Check if item is either a Platform or a hitbox of a Platform
        if (dynamic_cast<Platform*>(item)) {
            leftFootOnPlatform = true;
            break;
        } else if (QGraphicsRectItem* rect = dynamic_cast<QGraphicsRectItem*>(item)) {
            // If it's a rect, check if its parent is a Platform
            if (rect->parentItem() && dynamic_cast<Platform*>(rect->parentItem())) {
                leftFootOnPlatform = true;
                break;
            }
        }
    }

    // Check right foot
    bool rightFootOnPlatform = false;
    QList<QGraphicsItem*> itemsBelowRight = scene()->items(QPointF(x() + pixmap().width() - 2, footY));
    for (QGraphicsItem* item : itemsBelowRight) {
        // Check if item is either a Platform or a hitbox of a Platform
        if (dynamic_cast<Platform*>(item)) {
            rightFootOnPlatform = true;
            break;
        } else if (QGraphicsRectItem* rect = dynamic_cast<QGraphicsRectItem*>(item)) {
            // If it's a rect, check if its parent is a Platform
            if (rect->parentItem() && dynamic_cast<Platform*>(rect->parentItem())) {
                rightFootOnPlatform = true;
                break;
            }
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
        // Check for platform hitboxes or platform objects
        QGraphicsRectItem* hitbox = nullptr;
        
        // First, check if item is a Platform directly
        if (Platform* platform = dynamic_cast<Platform*>(colliding_items[i])) {
            hitbox = platform->getHitbox();
        } 
        // Alternatively, check if it's a hitbox belonging to a platform
        else if (QGraphicsRectItem* rect = dynamic_cast<QGraphicsRectItem*>(colliding_items[i])) {
            // See if this rect belongs to a Platform
            QGraphicsItem* parent = rect->parentItem();
            if (dynamic_cast<Platform*>(parent)) {
                hitbox = rect;
            }
        }
        
        if (hitbox) {
            QRectF kimoRect = this->sceneBoundingRect();
            QRectF platformRect = hitbox->sceneBoundingRect();

            if (goal && collidingItems().contains(goal)) {
                QGraphicsTextItem* cleared = new QGraphicsTextItem("Level Complete!");
                cleared->setFont(QFont("Arial", 24));
                cleared->setDefaultTextColor(Qt::red);
                cleared->setPos(x(), y()-40);
                scene()->addItem(cleared);
            }

            // Calculate intersection
            QRectF intersection = kimoRect.intersected(platformRect);

            // Check if collision is primarily vertical (landing or hitting head)
            if (intersection.width() > intersection.height()) {
                // Collision from above (landing on platform)
                if (verticalVelocity > 0 &&
                    kimoRect.bottom() > platformRect.top() &&
                    kimoRect.top() < platformRect.top() &&
                    kimoRect.right() > platformRect.left() &&
                    kimoRect.left() < platformRect.right())
                {
                    setY(platformRect.top() - pixmap().height()+4); // Slight offset added so Kimo appears to stand on platforms
                    verticalVelocity = 0;
                    isGrounded = true;
                    isJumping = false;

                    // Check for specific platform types by looking at parent
                    if (hitbox->parentItem() && dynamic_cast<SpikyPlatform*>(hitbox->parentItem())) {
                        // Standing on a spiky platform: take damage
                        takeDamage(1); // Damage amount can be adjusted
                    }
                }
                // Collision from below (hitting head)
                else if (verticalVelocity < 0 &&
                         kimoRect.top() < platformRect.bottom() &&
                         kimoRect.bottom() > platformRect.bottom()) {
                    setY(platformRect.bottom());
                    verticalVelocity = 0;
                }
            }
            // Check if collision is primarily horizontal
            else if (intersection.height() > intersection.width()) {
                // Collision from the right side (hitting platform's left edge)
                if (horizontalVelocity > 0 &&
                    kimoRect.right() > platformRect.left() &&
                    kimoRect.left() < platformRect.left()) {
                    setX(platformRect.left() - pixmap().width());
                    horizontalVelocity = 0;
                }
                // Collision from the left side (hitting platform's right edge)
                else if (horizontalVelocity < 0 &&
                         kimoRect.left() < platformRect.right() &&
                         kimoRect.right() > platformRect.right()) {
                    setX(platformRect.right());
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
if (damageTimer.elapsed() < 800) return; // Only take damage once per second
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
    currentState = NormalRight; // Reset state
    updateSprite();
}

void Kimo::inhale() {
    for(int i = 0; i< scene()->items().size(); i++) {
        if(Enemy* enemy = dynamic_cast <Enemy*>(scene()->items()[i])) {
            int enemy_health= enemy->get_enemy_health();
            if(enemy_health<2)

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
    bool facingRight = (lastDirection == Right);
    qreal missileTemp = facingRight ? x() + pixmap().width() : x() - missile->pixmap().width();
    missile->setPos(missileTemp, y() + 5);
    // Set missile direction
    missile->setDirection(facingRight ? 1 : -1);
    scene()->addItem(missile);
}

void Kimo::finishSpit() {
    if (horizontalVelocity < 0)
        currentState = NormalLeft;
    else
        currentState = NormalRight;
    updateSprite();
}
