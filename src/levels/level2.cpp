#include "level2.h"

Level2::Level2(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent)
    : BaseLevel(view, kimo, healthText, levelText, parent) {}

void Level2::setEnemies() {
    // Add the enemies in Level 2
}

void Level2::setEnvironment() {
    // Add the platforms, spikes, background, etc. for Level 2
}
