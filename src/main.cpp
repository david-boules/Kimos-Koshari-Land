#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QFont>
#include <QPointF>
#include "kimo/kimo.h"
#include "enemies/enemy.h"
#include "environment/platform.h"
#include "movement/onion.h"
#include "movement/chili.h"
#include "onion.h"
#include "chili.h"
#include "macaroni.h"
#include "enemy.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Create Scene
    QGraphicsScene scene;
    // Increased scene size to allow for scrolling
    scene.setSceneRect(0, 0, 2000, 600); // Example: doubled width

    // Create View
    QGraphicsView view;
    view.setFixedSize(800, 600);
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setScene(&scene); // Set scene before creating items that need it
    view.setBackgroundBrush(QPixmap(":/images/background.png"));

    // Create Kimo Instance
    Kimo *kimo = new Kimo();
    kimo->setFlag(QGraphicsItem::ItemIsFocusable);
    kimo->setFocus();
    kimo->setPos(25, 450); // Starting position
    kimo->setPixmap(QPixmap (":/images/kimo/Kimo_right.png").scaled(64,64));
    scene.addItem(kimo);

    // Pass the view to Kimo for camera control
    kimo->setView(&view);

    // HUD Implementation
    // Create Health Text
    QGraphicsTextItem* healthText = new QGraphicsTextItem();
    healthText->setDefaultTextColor(Qt::white);
    healthText->setFont(QFont("Arial", 16));
    healthText->setPlainText("Health: 3"); // Initial text
    // Set Z-value to ensure HUD is drawn on top
    healthText->setZValue(1);
    scene.addItem(healthText); // Add to scene, position updated in timer
    kimo->setHealthText(healthText); // Link Kimo to update the text content

    // Create Level Name Text
    QGraphicsTextItem* levelNameText = new QGraphicsTextItem();
    levelNameText->setDefaultTextColor(Qt::white);
    levelNameText->setFont(QFont("Arial", 16));
    levelNameText->setPlainText("Level: Koshari Kitchen"); // Level name
    levelNameText->setZValue(1); // Ensure HUD is drawn on top
    scene.addItem(levelNameText); // Add to scene, position updated in timer

    //Create enemy
    chili* ChiliEnemy = new chili(":/images/enemies/chiliLeft.png",":/images/enemies/chiliRight.png",QPointF(500,336));
    scene.addItem(ChiliEnemy);
    ChiliEnemy->setTargetKimo(kimo);

    macaroni* macaroni1 = new macaroni(QPixmap(":/images/enemies/macaroni.png"),QPointF(364,236));
    scene.addItem(macaroni1);
    macaroni1->setTargetKimo(kimo);

    onion* OnionEnemy = new onion(":/images/enemies/onion.png",QPointF(500,400));
    scene.addItem(OnionEnemy);
    OnionEnemy->setTargetKimo(kimo);

    macaroni* macaroniBig = new macaroni(QPixmap(":/images/enemies/macaroni.png"), QPointF(1300,250));
    macaroniBig->setScale(5.0);
    macaroniBig->setTargetKimo(kimo);
    macaroniBig->setSpeed(0);
    macaroniBig->setTargetKimo(kimo);
    scene.addItem(macaroniBig);

    static bool enemySpawned = false;

    QTimer* enemySpawnTimer = new QTimer();
    QObject::connect(enemySpawnTimer, &QTimer::timeout, [&]() {
        if (kimo->x() > 550 && !enemySpawned) {
            onion* onion2 = new onion(":/images/enemies/onion.png", QPointF(800, 400));
            onion2->setBounds(600,1400);
            scene.addItem(onion2);
            onion2->setTargetKimo(kimo);
            enemySpawned = true;
        }
    });
    enemySpawnTimer->start(16); // Check ~60 times per second
    // Create Platforms
    // Ground platform (extended for larger scene)
    StaticPlatform *ground1 = new StaticPlatform(200, 50, 0, 550);
    scene.addItem(ground1);

    StaticPlatform *ground2 = new StaticPlatform(200, 50, 300, 550);
    scene.addItem(ground2);

    StaticPlatform *ground3 = new StaticPlatform(200, 50, 600, 550);
    scene.addItem(ground3);

    StaticPlatform *ground4 = new StaticPlatform(200, 50, 900, 550);
    scene.addItem(ground4);

    StaticPlatform *ground5 = new StaticPlatform(800, 50, 1200, 550);
    scene.addItem(ground5);


    SpikyPlatform *spiky1 = new SpikyPlatform(100, 20, 200, 580);
    scene.addItem(spiky1);

    SpikyPlatform *spiky2 = new SpikyPlatform(100, 20, 500, 580);
    scene.addItem(spiky2);

    SpikyPlatform *spiky3 = new SpikyPlatform(100, 20, 800, 580);
    scene.addItem(spiky3);

    SpikyPlatform *spiky4 = new SpikyPlatform(100, 20, 1100, 580);
    scene.addItem(spiky4);

    // Floating static plaforms
    StaticPlatform *platform1 = new StaticPlatform(160, 20, 100, 400);
    //platform1->setPixmap(QPixmap(":/images/tiles/brick.png").scaled(160, 20));
    scene.addItem(platform1);

    StaticPlatform *platform2 = new StaticPlatform(160, 20, 300, 300);
    scene.addItem(platform2);

    // Moving platform (moves horizontally with range 200 and speed 2)
    MovingPlatform *moving1 = new MovingPlatform(160, 20, 400, 200, 200, 2);
    scene.addItem(moving1);

    // Spiky platform

    
    // Add more platforms for the larger scene
    StaticPlatform *platform3 = new StaticPlatform(160, 20, 700, 450);
    scene.addItem(platform3);
    StaticPlatform *platform4 = new StaticPlatform(160, 20, 900, 300);
    scene.addItem(platform4);
    MovingPlatform *moving2 = new MovingPlatform(160, 20, 1100, 150, 250, 3);
    scene.addItem(moving2);

    // Adding temporary 'Clear Condition' object
    QGraphicsRectItem* goal = new QGraphicsRectItem(0,0,64,64);
    goal->setBrush(Qt::red);
    goal->setPos(1800, 450);
    scene.addItem(goal);
    kimo->setGoal(goal);

    view.show(); // Show the view

    // Timer for game updates (platforms, HUD)
    QTimer *gameUpdateTimer = new QTimer();
    QObject::connect(gameUpdateTimer, &QTimer::timeout, [&]() {
        // Update moving platforms
        moving1->update();
        moving2->update();

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
