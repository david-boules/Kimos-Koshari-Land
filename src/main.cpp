#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QFont>
#include <QPointF>
#include "kimo/kimo.h"
#include "enemies/enemy.h"
#include "environment/platform.h"
#include "movement/move1.h"
#include "movement/move2.h"
#include "move1.h"
#include "move2.h"
#include "enemy.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create Scene
    QGraphicsScene scene;
    // Increased scene size to allow for scrolling
    scene.setSceneRect(0, 0, 1600, 600); // Example: doubled width

    // Create View
    QGraphicsView view;
    view.setFixedSize(800, 600);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setScene(&scene); // Set scene before creating items that need it
    view.setBackgroundBrush(Qt::blue);

    // Create Kimo Instance
    Kimo *kimo = new Kimo();
    kimo->setFlag(QGraphicsItem::ItemIsFocusable);
    kimo->setFocus();
    kimo->setPos(100, 400); // Starting position
    kimo->setPixmap(QPixmap (":/images/kimo/Kimo.png").scaled(64,64));
    scene.addItem(kimo);

    // Pass the view to Kimo for camera control
    kimo->setView(&view);

    // --- HUD Implementation START ---
    // Create Health Text (HUD Element)
    QGraphicsTextItem* healthText = new QGraphicsTextItem();
    healthText->setDefaultTextColor(Qt::white);
    healthText->setFont(QFont("Arial", 16));
    healthText->setPlainText("Health: 3"); // Initial text
    // Set Z-value to ensure HUD is drawn on top
    healthText->setZValue(1); 
    scene.addItem(healthText); // Add to scene, position updated in timer
    kimo->setHealthText(healthText); // Link Kimo to update the text content

    // Create Level Name Text (HUD Element)
    QGraphicsTextItem* levelNameText = new QGraphicsTextItem();
    levelNameText->setDefaultTextColor(Qt::white);
    levelNameText->setFont(QFont("Arial", 16));
    levelNameText->setPlainText("Level: Kimo's Kitchen"); // Example level name
    levelNameText->setZValue(1); // Ensure HUD is drawn on top
    scene.addItem(levelNameText); // Add to scene, position updated in timer
    // --- HUD Implementation END ---

    //Create enemy
    move2* Chili = new move2(":/images/enemies/chili.png",QPointF(500,336));
    scene.addItem(Chili);
    Chili->setTargetKimo(kimo);

    Enemy* macaroni = new Enemy(":/images/enemies/macaroni.png",QPointF(364,236));
    scene.addItem(macaroni);
    macaroni->setTargetKimo(kimo);

    move1* onion = new move1(":/images/enemies/onion.png",QPointF(500,400));
    scene.addItem(onion);
    onion->setTargetKimo(kimo);

    static bool enemySpawned = false;

    QTimer* enemySpawnTimer = new QTimer();
    QObject::connect(enemySpawnTimer, &QTimer::timeout, [&]() {
        if (kimo->x() > 550 && !enemySpawned) {
            move1* onion2 = new move1(":/images/enemies/onion.png", QPointF(800, 400));
            onion2->setBounds(600,1400);
            scene.addItem(onion2);
            onion2->setTargetKimo(kimo);
            enemySpawned = true;
        }
    });
    enemySpawnTimer->start(16); // Check ~60 times per second
    // Create Platforms
    // Ground platform (extended for larger scene)
    StaticPlatform *ground = new StaticPlatform(1600, 50, 0, 550);
    scene.addItem(ground);

    // floating static plaforms
    StaticPlatform *platform1 = new StaticPlatform(160, 20, 100, 400);
    scene.addItem(platform1);

    StaticPlatform *platform2 = new StaticPlatform(160, 20, 300, 300);
    scene.addItem(platform2);

    // Moving platform (moves horizontally with range 200 and speed 2)
    MovingPlatform *platform3 = new MovingPlatform(160, 20, 400, 200, 200, 2);
    scene.addItem(platform3);

    // spikey platform
    SpikyPlatform *platform4 = new SpikyPlatform(160, 20, 200, 100);
    scene.addItem(platform4);
    
    // Add more platforms for the larger scene
    StaticPlatform *platform5 = new StaticPlatform(160, 20, 700, 450);
    scene.addItem(platform5);
    StaticPlatform *platform6 = new StaticPlatform(160, 20, 900, 350);
    scene.addItem(platform6);
    StaticPlatform *platform7 = new StaticPlatform(160, 20, 1100, 250);
    scene.addItem(platform7);
    MovingPlatform *platform8 = new MovingPlatform(160, 20, 1300, 400, 150, 3);
    scene.addItem(platform8);

    view.show(); // Show the view

    // Timer for game updates (platforms, HUD)
    QTimer *gameUpdateTimer = new QTimer();
    QObject::connect(gameUpdateTimer, &QTimer::timeout, [&]() {
        // Update moving platforms
        platform3->update();
        platform8->update();

        // --- HUD Position Update START ---
        // Map the view's top-left corner (0,0) to scene coordinates
        QPointF viewTopLeft = view.mapToScene(0, 0);
        // Set HUD element positions relative to the view's top-left
        healthText->setPos(viewTopLeft.x() + 10, viewTopLeft.y() + 10);
        levelNameText->setPos(viewTopLeft.x() + 10, viewTopLeft.y() + 35); // Position below health
        // --- HUD Position Update END ---
    });
    gameUpdateTimer->start(16); // ~60 FPS

    return a.exec();
}

