#include "baselevel.h"

BaseLevel::BaseLevel(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent)
    : QGraphicsScene(parent), view(view), kimo(kimo), HUD_health(healthText), HUD_levelName(levelText)
{}

void BaseLevel::setupScene(QString levelName) {
    setSceneRect(0, 0, 2000, 600);

    setKimo();
    setHUD(levelName);
    setEnemies();
    setEnvironment();

    kimo->setView(view);

    // Ensuring HUD element positions stay in the view's top-left as the view moves
    QTimer* hudUpdateTimer = new QTimer(this);
    connect(hudUpdateTimer, &QTimer::timeout, this, [this]() {
        if (!view || !HUD_health || !HUD_levelName) return;

        QPointF viewTopLeft = view->mapToScene(0, 0);
        HUD_health->setPos(viewTopLeft.x() + 10, viewTopLeft.y() + 10);
        HUD_levelName->setPos(viewTopLeft.x() + 10, viewTopLeft.y() + 35);
    });

    hudUpdateTimer->start(16); // ~60 FPS
}

void BaseLevel::setKimo() {
    kimo->setFlag(QGraphicsItem::ItemIsFocusable);
    kimo->setFocus();
    kimo->setPos(25,450);
    kimo->setPixmap(QPixmap(":/images/kimo/Kimo_right.png").scaled(64,64));
    addItem(kimo);
}

void BaseLevel::setHUD(QString levelName) {
    // Health Text in HUD
    HUD_health->setDefaultTextColor(Qt::white);
    HUD_health->setFont(QFont("Arial", 16));
    HUD_health->setPlainText(QString("Health: " + QString::number(kimo->getHealth() ) ));
    HUD_health->setZValue(1); // To ensure HUD is drawn on top
    addItem(HUD_health); // Add to scene, position updated in timer
    kimo->setHealthText(HUD_health); // Link Kimo to update the text content

    // Level Name Text in HUD
    HUD_levelName->setDefaultTextColor(Qt::white);
    HUD_levelName->setFont(QFont("Arial", 16));
    HUD_levelName->setPlainText("Level: " + levelName); // Level name
    HUD_levelName->setZValue(1); // Ensure HUD is drawn on top
    addItem(HUD_levelName); // Add to scene, position updated in timer
}
