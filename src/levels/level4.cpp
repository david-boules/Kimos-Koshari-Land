#include "level4.h"

Level4::Level4(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent)
    : BaseLevel(view, kimo, healthText, levelText, parent) {}

void Level4::setEnemies() {
    // Add the enemies in Level 4
}

void Level4::setEnvironment() {
    // Add the platforms, spikes, background, etc. for Level 4

    view->setBackgroundBrush(QPixmap(":/images/levels/L4background.png"));

}
