#ifndef KIMO_H
#define KIMO_H
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>
#include <QList>
#include <QVector>
#include <QGraphicsView> // Added for view reference
#include <QGraphicsTextItem> // Added for health text
#include <QKeyEvent> // Added for key events

class Kimo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    // Constructor
    Kimo(QGraphicsItem *parent = nullptr);
    void updateSprite();
    
    // Gameplay Mechanics member functions
    void setHealthText(QGraphicsTextItem* text); // Updates Health on-screen
    void takeDamage(int amount);                 // Reduces Kimo's health
    bool isDead() const;                         // Checks whether Kimo's health is 0
    void respawn();                              // Relocates Kimo to starting position
    void inhale();                               // Kimo's 'inhale' function
    void spit();                                 // Kimo's 'spit' function
    void setGoal(QGraphicsRectItem* g);          // 'Setter' to update Kimo's pointer to the goal
    void addCoins(int amount);                   // Adds coins to player's balance
    int getCoins() const;                        // Returns current coin balance
    void setCoinText(QGraphicsTextItem *text);   // Sets the coin display text
    void updateScore(int points);                // Updates score
    void shootFireball();                        // Shoots a fireball projectile
    void activateShield();                       // Activates temporary invincibility
    void doubleJump();                           // Performs a double jump if available
    void grantFireball();                        // Grants the fireball ability
    void grantDoubleJump();                      // Grants the double jump ability
    void grantShield();                          // Grants the shield ability

    // Movement and physics functions
    void keyPressEvent(QKeyEvent * event);       // Handles keyboard input for movement
    void keyReleaseEvent(QKeyEvent * event);     // Handles stopping movement when keys are released
    void jump();                                 // Initiates jump when grounded
    void checkCollision();                       // Checks and handles collisions with platforms
    void setGravity(bool enabled);               // Enables/disables gravity effect
    void setJumpVelocity(double velocity);       // Sets the initial jump velocity
    void setAirControl(bool enabled);            // Enables/disables air control
    void setKnockback(double verticalForce, double horizontalForce); // Sets knockback forces

    // View setter
    void setView(QGraphicsView* v); // Added setter for the view
    QElapsedTimer damageTimer;

    int getHealth(); // Getter for Kimo's health
    int getScore() const;

    // Resume/Pause
    void pauseGame();
    void resumeGame();

    ~Kimo() {if(physicsTimer) physicsTimer->deleteLater();}

signals:
    void levelComplete(); // Singal emitted when Kimo reaches the goal
    void coinsChanged(int newAmount); // Signal emitted when coins change
    void healthChanged(int health);
    void abilityCountdownChanged(const QString &abilityName, int remainingTime);

private slots:
    // Slots only called from inside 'Kimo' objects
    void updatePhysics();                        // Updates physics calculations every frame
    void finishSpit();
    void deactivateShield(); // Deactivates the shield after its duration
    void updateAbilityCountdown();
    
private:

    // Kimo's Sprites
    QPixmap normalRightKimo;
    QPixmap normalLeftKimo;
    QPixmap inhalingRightKimo;
    QPixmap inhalingLeftKimo;
    QPixmap fullRightKimo;
    QPixmap fullLeftKimo;
    QPixmap spittingRightKimo;
    QPixmap spittingLeftKimo;
    QPixmap crouchingRightKimo;
    QPixmap crouchingLeftKimo;
    enum KimoState {NormalRight, NormalLeft, Inhaling, Full, Spitting, Crouching};
    KimoState currentState = NormalRight;

    // Kimo's Direction (for updating sprites after inhale/spit)
    enum Direction {Left, Right};
    Direction lastDirection = Right;

    // Gameplay Mechanics member variables
    int health = 3;                          // Kimo starts with 3 health strokes
    QGraphicsTextItem* healthText = nullptr; // Pointer to display health on screen
    QGraphicsRectItem* goal = nullptr;       // Pointer to the goal ('Clear Condition')
    int coins = 20;                          // Player's coin balance
    int score = 0;                           // Player's current score
    QGraphicsTextItem *coinText = nullptr;   // Pointer to display coins on screen

    // Ability-related variables
    bool hasFireball = false;      // Whether Kimo has the fireball ability
    bool hasDoubleJump = false;    // Whether Kimo has the double jump ability
    bool hasShield = false;        // Whether Kimo has the shield ability
    bool isShieldActive = false;   // Whether the shield is currently active
    bool canDoubleJump = false;    // Whether Kimo can perform a double jump
    QTimer *shieldTimer = nullptr; // Timer for shield duration
    QTimer *abilityTimer;
    QString currentAbility;
    int abilityDuration;

    // Timers and State variables
    QTimer * physicsTimer;                  // Timer for physics updates
    bool isJumping = false;                 // Tracks if Kimo is currently jumping (preventing multiple jumps at once)
    bool isGrounded = true;                 // Tracks if Kimo is on a platform
    bool isCrouching = false;               // Tracks if Kimo is currently crouching (preventing multiple crouches)
    bool isInhaling = false;                // Tracks if Kimo is inhaling
    bool isFull = false;                    // Tracks if Kimo is 'full'
    
    // Physics variables
    double verticalVelocity = 0;            // Current vertical speed
    double horizontalVelocity = 0;          // Current horizontal speed
    const double gravity = 0.5;             // Gravity force applied each frame
    double jumpForce = -12.0;               // Initial jump velocity (negative for upward movement)
    const double maxFallSpeed = 15.0;       // Maximum falling speed
    const double airControlFactor = 0.8;    // Movement control while in air (80% of ground control)
    const double groundControlFactor = 1.0; // Full movement control while on ground
    bool airControlEnabled = true;          // Flag to enable/disable air control

    // View reference
    QGraphicsView* view = nullptr; // Added pointer to the view
};

#endif // KIMO_H

