#include "kimo.h"
#include "enemy.h"
#include "macaronimissile.h"
#include "fireball.h"
#include "fire_chili.h"
#include "coin.h"
#include <QKeyEvent>
#include <QString>
#include <QGraphicsScene>
#include "QElapsedTimer"
#include <QTimer>
#include <QList>
#include <platform.h>
#include <QGraphicsView>
#include <QRectF>
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsColorizeEffect>
#include <QMediaPlayer>
#include <QAudioOutput>

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
    crouchingRightKimo = QPixmap(":/images/kimo/Kimo_crouchRight.png").scaled(64,48);
    crouchingLeftKimo = QPixmap(":/images/kimo/Kimo_crouchLeft.png").scaled(64,48);

    // Initialize the damage and fireball timer
    damageTimer.start();
    fireballCooldown.start();

    // Set up physics timer for smooth movement
    physicsTimer = new QTimer();
    connect(physicsTimer, SIGNAL(timeout()), this, SLOT(updatePhysics()));
    physicsTimer->start(16); // ~60 FPS for smooth physics

    abilityTimer = new QTimer(this);
    abilityTimer->setInterval(1000);
    connect(abilityTimer, &QTimer::timeout, this, &Kimo::updateAbilityCountdown);
}

// Added implementation for setView
void Kimo::setView(QGraphicsView* v) {
    view = v;
}

// Getter for Kimo's health:
int Kimo::getHealth() {
    return health;
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
    else if(currentState == Crouching) {
        if (lastDirection == Left)
            setPixmap(crouchingLeftKimo);
        else
            setPixmap(crouchingRightKimo);
    }
}

void Kimo::setGoal(QGraphicsPixmapItem* g) {
    goal = g;
}

void Kimo::pause() {
    if (physicsTimer) physicsTimer->stop();
    if (abilityTimer && abilityTimer->isActive()) abilityTimer->stop();
}

void Kimo::resume() {
    if (physicsTimer && !physicsTimer->isActive()) physicsTimer->start(16);
    if (!currentAbility.isEmpty()) abilityTimer->start(1000);
}



void Kimo::keyPressEvent(QKeyEvent * event) {
    // Handle horizontal movement
    if (event->key() == Qt::Key_Left) {
        lastDirection = Left;
        if(currentState == NormalRight || currentState == NormalLeft) {
            currentState = NormalLeft;
            updateSprite();
            horizontalVelocity = -5.0; // Move left
        }
        else if(currentState == Full || currentState == Crouching) {
            horizontalVelocity = -2.0; // Moves slower when full/crouching
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
        else if(currentState == Full || currentState == Crouching) {
            horizontalVelocity = 2.0; // Moves slower when full/crouching
            updateSprite();
        }
    }
    else if (event->key() == Qt::Key_F) {
        if (hasFireball) {
            shootFireball();
        }
    }
    // Handle jumping (only when grounded)
    else if (event->key() == Qt::Key_Up) {
        if (isGrounded) jump();
        else if (hasDoubleJump && canDoubleJump) doubleJump();
    }
    // Handle crouching (only when grounded)
    else if (event->key() == Qt::Key_Down && isGrounded && !isCrouching && horizontalVelocity==0) {
        currentState = Crouching;
        setPixmap(lastDirection==Left ? crouchingLeftKimo : crouchingRightKimo);
        setY(y() + 16);
        isCrouching = true;
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

    if (event->key() == Qt::Key_Down && isCrouching && isGrounded) {   // Prevents unexpected action when trying to crouch in midair/on hitting the ground
        currentState = (lastDirection == Left) ? NormalLeft : NormalRight;
        setY(y() - 16);
        updateSprite();
        isCrouching = false;
    }
}

void Kimo::jump() {
    if (isGrounded) {
        verticalVelocity = jumpForce;
        isJumping = true;
        isGrounded = false;
        canDoubleJump = hasDoubleJump;
    }
}

void Kimo::updatePhysics() {
    if (!scene()) return;

    if (goal && this->collidesWithItem(goal, Qt::IntersectsItemShape)) {
        if (physicsTimer && physicsTimer->isActive()) {
            emit levelComplete();  // orchestrator begins transition
            return;
        }
    }

    // Fix edge bug: Check for platform under both left and right edges of the character
    isGrounded = false;
    int footY = y() + pixmap().height() + 1;

    // Check left foot
    bool leftFootOnPlatform = false;
    QList<QGraphicsItem*> itemsBelowLeft = scene()->items(QPointF(x() + 2, footY));
    for (QGraphicsItem* item : itemsBelowLeft) {
        // Check if item is either a Platform or a hitbox of a Platform
        if (Platform* platform = dynamic_cast<Platform*>(item)) {
            leftFootOnPlatform = true;
            // Check if it's a spiky platform
            if (SpikyPlatform* spikyPlatform = dynamic_cast<SpikyPlatform*>(platform)) {
                spikyPlatform->handleCollision(this);
            }
            // Check if it's a vertically moving platform
            else if (VerticallyMovingPlatform* movingPlatform = dynamic_cast<VerticallyMovingPlatform*>(platform)) {
                movingPlatform->moveKimoWithPlatform(this);
            }
            break;
        } else if (QGraphicsRectItem* rect = dynamic_cast<QGraphicsRectItem*>(item)) {
            // If it's a rect, check if its parent is a Platform
            if (Platform* platform = dynamic_cast<Platform*>(rect->parentItem())) {
                leftFootOnPlatform = true;
                // Check if it's a spiky platform
                if (SpikyPlatform* spikyPlatform = dynamic_cast<SpikyPlatform*>(platform)) {
                    spikyPlatform->handleCollision(this);
                }
                // Check if it's a vertically moving platform
                else if (VerticallyMovingPlatform* movingPlatform = dynamic_cast<VerticallyMovingPlatform*>(platform)) {
                    movingPlatform->moveKimoWithPlatform(this);
                }
                break;
            }
        }
    }

    // Check right foot
    bool rightFootOnPlatform = false;
    QList<QGraphicsItem*> itemsBelowRight = scene()->items(QPointF(x() + pixmap().width() - 2, footY));
    for (QGraphicsItem* item : itemsBelowRight) {
        // Check if item is either a Platform or a hitbox of a Platform
        if (Platform* platform = dynamic_cast<Platform*>(item)) {
            rightFootOnPlatform = true;
            // Check if it's a spiky platform
            if (SpikyPlatform* spikyPlatform = dynamic_cast<SpikyPlatform*>(platform)) {
                spikyPlatform->handleCollision(this);
            }
            // Check if it's a vertically moving platform
            else if (VerticallyMovingPlatform* movingPlatform = dynamic_cast<VerticallyMovingPlatform*>(platform)) {
                movingPlatform->moveKimoWithPlatform(this);
            }
            break;
        } else if (QGraphicsRectItem* rect = dynamic_cast<QGraphicsRectItem*>(item)) {
            // If it's a rect, check if its parent is a Platform
            if (Platform* platform = dynamic_cast<Platform*>(rect->parentItem())) {
                rightFootOnPlatform = true;
                // Check if it's a spiky platform
                if (SpikyPlatform* spikyPlatform = dynamic_cast<SpikyPlatform*>(platform)) {
                    spikyPlatform->handleCollision(this);
                }
                // Check if it's a vertically moving platform
                else if (VerticallyMovingPlatform* movingPlatform = dynamic_cast<VerticallyMovingPlatform*>(platform)) {
                    movingPlatform->moveKimoWithPlatform(this);
                }
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

    // After checking both feet, clear Kimo from all VerticallyMovingPlatform if not standing on one
    if (!leftFootOnPlatform && !rightFootOnPlatform) {
        QList<QGraphicsItem*> allItems = scene()->items();
        for (QGraphicsItem* item : allItems) {
            if (VerticallyMovingPlatform* movingPlatform = dynamic_cast<VerticallyMovingPlatform*>(item)) {
                movingPlatform->clearKimo();
            }
        }
    }
}

void Kimo::checkCollision() {
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (int i = 0; i < colliding_items.size(); ++i) {

        // Coin collection
        if (Coin *coin = dynamic_cast<Coin *>(colliding_items[i])) {
            addCoins(1);
            scene()->removeItem(coin);
            delete coin;
            continue;
        }

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
                        takeDamage(3); // Damage amount can be adjusted
                        break; // Prevent double damage in one frame
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

void Kimo::setKnockback(double verticalForce, double horizontalForce) {
    // Apply knockback forces
    verticalVelocity = verticalForce;
    horizontalVelocity = horizontalForce;
    
    // Disable air control temporarily during knockback
    airControlEnabled = false;
    
    // Stop horizontal movement after 200ms to prevent sliding
    QTimer::singleShot(200, this, [this]() {
        horizontalVelocity = 0;
    });
    // Re-enable air control after knockback duration
    QTimer::singleShot(500, this, [this]() {
        airControlEnabled = true;
    });
}

void Kimo::takeDamage(int amount) {
    // Check if shield is active
    if (isShieldActive) {
        deactivateShield();
        return;
    }

    // Only take damage if enough time has passed since last damage
    if (damageTimer.elapsed() > 1000) { // 1000ms (1s) invulnerability
        damageTimer.restart(); // Set invulnerability immediately
        QMediaPlayer* damagePlayer = new QMediaPlayer(this);
        QAudioOutput* damageOutput = new QAudioOutput(this);

        damagePlayer->setAudioOutput(damageOutput);
        damagePlayer->setSource(QUrl("qrc:/audio/damage.mp3"));
        damagePlayer->play();

        health -= amount;
        if (healthText) {
            healthText->setPlainText(QString("Health: %1").arg(health));

            auto* redText = new QGraphicsColorizeEffect();
            redText->setColor(Qt::red);
            redText->setStrength(2.0);
            healthText->setGraphicsEffect(redText);

            // Removing the effect with a separate timer
            QTimer::singleShot(1000, this, [this]() {
                if (healthText)
                    healthText->setGraphicsEffect(nullptr);
            });
        }

        if (isDead()) {

            respawn();
            return;
        }

        // Brief 'damage effect'
        auto* redFlash = new QGraphicsColorizeEffect();
        redFlash->setColor(Qt::red);
        redFlash->setStrength(0.5);
        setGraphicsEffect(redFlash);

        setOpacity(0.8);  // Make Kimo semi-transparent
        QTimer::singleShot(700, this, [this]() {
            setOpacity(1.0); // Back to normal opacity after 700ms (same as 'invulnerability' timer)
            setGraphicsEffect(nullptr);
        });
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
            if(enemy_health<2&& enemy->can_be_inhaled())

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

void Kimo::setCoinText(QGraphicsTextItem *text)
{
    coinText = text;
    if (coinText)
    {
        coinText->setPlainText(QString("Coins: %1").arg(coins));
    }
}

void Kimo::addCoins(int amount)
{
    coins += amount;
    if (coinText)
    {
        coinText->setPlainText(QString("Coins: %1").arg(coins));
    }
    emit coinsChanged(coins);
}

int Kimo::getCoins() const {return coins;}

int Kimo::getScore() const {return score;}

void Kimo::updateScore(int points)
{
    score += points;
}

void Kimo::shootFireball()
{
    if (!hasFireball)
        return;

    if (fireballCooldown.elapsed() < 1000)
        return;

    fireballCooldown.restart();

    // Update Sprite
    currentState = Spitting;
    updateSprite();
    QTimer::singleShot(400, this, SLOT(finishSpit())); // Resetting sprite after fireball spit animation

    // Create and shoot fireball
    Fireball *fireball = new Fireball(lastDirection == Right ? 1 : -1, this);

    qreal fireballX = lastDirection == Right ? x() + pixmap().width() : x() - fireball->pixmap().width();
    int direction = lastDirection == Right ? 1 : -1;
    fireball->setPos(fireballX + (direction > 0 ? 10 : -10), y() - pixmap().height() + 80);
    scene()->addItem(fireball);
}

void Kimo::grantShield()
{
    hasShield = true;
    currentAbility = "Shield";
    abilityDuration = 5; // DURATION: Set shield ability duration in seconds
    abilityTimer->start();
    emit abilityCountdownChanged(currentAbility, abilityDuration);

    // Activate shield immediately
    activateShield();
}

void Kimo::activateShield()
{
    if (!hasShield || isShieldActive)
        return;

    isShieldActive = true;

    // Add visual shield effect
    QGraphicsEllipseItem *shield = new QGraphicsEllipseItem(-10, -10, pixmap().width() + 20, pixmap().height() + 20, this);
    shield->setPen(QPen(Qt::cyan, 2));
    shield->setBrush(QBrush(QColor(0, 255, 255, 50))); // Semi-transparent cyan
    shield->setZValue(-1);                             // Place behind Kimo
}

void Kimo::deactivateShield()
{
    isShieldActive = false;
    hasShield = false;

    // Stop the ability timer and reset ability state
    abilityTimer->stop();
    currentAbility = "";
    emit abilityCountdownChanged("", 0);

    // Remove shield effect
    for (QGraphicsItem *item : childItems())
    {
        if (QGraphicsEllipseItem *shield = dynamic_cast<QGraphicsEllipseItem *>(item))
        {
            delete shield;
            break;
        }
    }
}

void Kimo::doubleJump()
{
    if (!hasDoubleJump || !canDoubleJump)
        return;

    // Perform double jump
    verticalVelocity = jumpForce;
    canDoubleJump = false; // Disable double jump after use
}

void Kimo::grantFireball()
{
    hasFireball = true;
    currentAbility = "Fireball";
    abilityDuration = 5; // DURATION: Set fireball ability duration in seconds
    abilityTimer->start();
    emit abilityCountdownChanged(currentAbility, abilityDuration);
}

void Kimo::grantDoubleJump()
{
    hasDoubleJump = true;
    canDoubleJump = true;
    currentAbility = "Double Jump";
    abilityDuration = 10; // DURATION: Set double jump ability duration in seconds
    abilityTimer->start();
    emit abilityCountdownChanged(currentAbility, abilityDuration);
}

void Kimo::updateAbilityCountdown()
{
    if (abilityDuration > 0)
    {
        abilityDuration--;
        emit abilityCountdownChanged(currentAbility, abilityDuration);
    }
    else
    {
        abilityTimer->stop();
        if (currentAbility == "Fireball")
            hasFireball = false;
        else if (currentAbility == "Double Jump")
        {
            hasDoubleJump = false;
            canDoubleJump = false;
        }
        else if (currentAbility == "Shield")
        {
            hasShield = false;
            deactivateShield(); // Deactivate shield when ability expires
        }
        currentAbility = "";
        emit abilityCountdownChanged("", 0);
    }
}
