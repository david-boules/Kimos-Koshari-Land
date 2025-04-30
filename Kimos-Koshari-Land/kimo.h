#ifndef KIMO_H
#define KIMO_H
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>
#include <QList>
#include <QVector>

class Kimo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    // Constructor
    Kimo(QGraphicsItem *parent = nullptr);
    void updateSprite();
    
    // Gameplay Mechanics member functions
    void setHealthText(QGraphicsTextItem* text); // Updates Health on-screen
    void takeDamage(int amount);                           // Reduces Kimo's health
    bool isDead() const;                         // Checks whether Kimo's health is 0
    void respawn();                              // Relocates Kimo to starting position
    void inhale();                               // Kimo's 'inhale' function
    void spit();                                 // Kimo's 'spit' function

    // Movement and physics functions
    void keyPressEvent(QKeyEvent * event);       // Handles keyboard input for movement
    void keyReleaseEvent(QKeyEvent * event);     // Handles stopping movement when keys are released
    void jump();                                 // Initiates jump when grounded
    void checkCollision();                       // Checks and handles collisions with platforms
    void setGravity(bool enabled);               // Enables/disables gravity effect
    void setJumpVelocity(double velocity);       // Sets the initial jump velocity
    void setAirControl(bool enabled);            // Enables/disables air control

private slots:
    // Slots only called from inside 'Kimo' objects
    void updatePhysics();                        // Updates physics calculations every frame
    void finishSpit();
    
private:

    // Kimo Sprites
    QPixmap normalKimo;
    QPixmap inhalingKimo;
    QPixmap fullKimo;
    QPixmap spittingKimo;
    enum KimoState {Normal, Inhaling, Full, Spitting};
    KimoState currentState = Normal;

    // Gameplay Mechanics member variables
    int health = 3;                          // Kimo starts with 3 health strokes
    QGraphicsTextItem* healthText = nullptr; // Pointer to display health on screen

    // Timers and State variables
    QTimer * physicsTimer;                  // Timer for physics updates
    bool isJumping = false;                 // Tracks if character is currently jumping
    bool isGrounded = true;                 // Tracks if character is on a platform
    bool isInhaling = false;
    bool isFull = false;
    
    // Physics variables
    double verticalVelocity = 0;            // Current vertical speed
    double horizontalVelocity = 0;          // Current horizontal speed
    const double gravity = 0.5;             // Gravity force applied each frame
    double jumpForce = -12.0;               // Initial jump velocity (negative for upward movement)
    const double maxFallSpeed = 15.0;       // Maximum falling speed
    const double airControlFactor = 0.8;    // Movement control while in air (80% of ground control)
    const double groundControlFactor = 1.0; // Full movement control while on ground
    bool airControlEnabled = true;          // Flag to enable/disable air control
};

#endif // KIMO_H
