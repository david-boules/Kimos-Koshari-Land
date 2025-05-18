#include "level3.h"
#include "platform.h"

Level3::Level3(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent)
    : BaseLevel(view, kimo, healthText, levelText, parent) {}

void Level3::setEnemies() {
    // Add the enemies in Level 3
}

void Level3::setEnvironment() {
    QPixmap bgPixmap(":/images/levels/L3background.png");
    QGraphicsPixmapItem* background = new QGraphicsPixmapItem(bgPixmap.scaled(2000, 600));
    background->setZValue(-100);  // Push behind everything
    addItem(background);

    StaticPlatform *ground1 = new StaticPlatform(500, 50, 0, 550);
    StaticPlatform *ground2 = new StaticPlatform(500, 50, 600, 550);
    addItem(ground1);
    addItem(ground2);

    // Climbable steps
    addItem(new StaticPlatform(100, 20, 1200, 500));
    addItem(new StaticPlatform(100, 20, 1300, 450));
    addItem(new StaticPlatform(100, 20, 1400, 400));
    addItem(new StaticPlatform(100, 20, 1500, 350));

    // 'Crackable' blocks (as placeholders)
    // TODO: Replace with real BreakablePlatform class later
    QGraphicsRectItem* cracked1 = new QGraphicsRectItem(1600, 300, 100, 20);
    cracked1->setBrush(Qt::darkYellow);
    cracked1->setZValue(0);
    addItem(cracked1);

    // Spikes between jumps
    addItem(new SpikyPlatform(100, 20, 800, 580));
    addItem(new SpikyPlatform(100, 20, 1600, 580));

    // Add goal
    QGraphicsRectItem* goal = new QGraphicsRectItem(0,0,64,64);
    goal->setBrush(Qt::red);
    goal->setPos(1900, 450);
    addItem(goal);
    kimo->setGoal(goal);
}
