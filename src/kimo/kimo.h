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
    void takeDamage(int amount);                           // Reduces Kimo's health
    bool isDead() const;                         // Checks whether Kimo's health is 0
    void respawn();                              // Relocates Kimo to starting position
    void inhale();                               // Kimo's 'inhale' function
    void spit();                                 // Kimo's 'spit' function
    void setGoal(QGraphicsRectItem* g);          // 'Setter' to update Kimo's pointer to the goal

    // Movement and physics functions
    void keyPressEvent(QKeyEvent * event);       // Handles keyboard input for movement
    void keyReleaseEvent(QKeyEvent * event);     // Handles stopping movement when keys are released
    void jump();                                 // Initiates jump when grounded
    void checkCollision();                       // Checks and handles collisions with platforms
    void setGravity(bool enabled);               // Enables/disables gravity effect
    void setJumpVelocity(double velocity);       // Sets the initial jump velocity
    void setAirControl(bool enabled);            // Enables/disables air control

    // View setter
    void setView(QGraphicsView* v); // Added setter for the view
    QElapsedTimer damageTimer;

private slots:
    // Slots only called from inside 'Kimo' objects
    void updatePhysics();                        // Updates physics calculations every frame
    void finishSpit();
    
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
    enum KimoState {NormalRight, NormalLeft, Inhaling, Full, Spitting};
    KimoState currentState = NormalRight;

    // Kimo's Direction (for updating sprites after inhale/spit)
    enum Direction {Left, Right};
    Direction lastDirection = Right;

    // Gameplay Mechanics member variables
    int health = 3;                          // Kimo starts with 3 health strokes
    QGraphicsTextItem* healthText = nullptr; // Pointer to display health on screen
    QGraphicsRectItem* goal = nullptr;       // Pointer to the goal ('Clear Condition')

    // Timers and State variables
    QTimer * physicsTimer;                  // Timer for physics updates
    bool isJumping = false;                 // Tracks if Kimo is currently jumping
    bool isGrounded = true;                 // Tracks if Kimo is on a platform
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

