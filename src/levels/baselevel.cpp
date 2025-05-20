#include "baselevel.h"
#include "kosharitrophy.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QGraphicsProxyWidget>

BaseLevel::BaseLevel(QGraphicsView* view, Kimo* kimo, QGraphicsTextItem* healthText, QGraphicsTextItem* levelText, QObject *parent)
    : QGraphicsScene(parent), view(view), kimo(kimo), HUD_health(healthText), HUD_levelName(levelText)
{
    // Adding 'Clear Condition' object
    KoshariTrophy* goal = new KoshariTrophy();
    addItem(goal);
    goal->setPos(1800, 480);
    kimo->setGoal(goal);

    // Level Music
    lvlMusicPlayer = new QMediaPlayer(this);
    lvlMusicOutput = new QAudioOutput(this);
    lvlMusicPlayer->setAudioOutput(lvlMusicOutput);
    lvlMusicPlayer->setSource(QUrl("qrc:/audio/lvlmusic.mp3"));
    lvlMusicPlayer->play();

    // Create store
    store = new Store(view, kimo, this);
    connect(store, &Store::storeClosed, this, &BaseLevel::toggleStore);

    // Create store button
    storeButton = new QPushButton("Store");
    storeButton->setFixedSize(80, 30);
    storeButtonProxy = addWidget(storeButton);
    storeButtonProxy->setPos(700, 20);
    connect(storeButton, &QPushButton::clicked, this, &BaseLevel::toggleStore);

    // Create coin display
    HUD_coins = new QGraphicsTextItem();
    HUD_coins->setFont(QFont("Arial", 16));
    HUD_coins->setDefaultTextColor(Qt::yellow);
    HUD_coins->setPos(600, 20);
    addItem(HUD_coins);
    kimo->setCoinText(HUD_coins);

    // Create ability countdown display
    HUD_abilityCountdown = new QGraphicsTextItem();
    HUD_abilityCountdown->setFont(QFont("Arial", 16));
    HUD_abilityCountdown->setDefaultTextColor(Qt::cyan);
    HUD_abilityCountdown->setPos(400, 20);
    HUD_abilityCountdown->hide(); // Initially hidden
    addItem(HUD_abilityCountdown);

    // Connect ability countdown signal
    connect(kimo, &Kimo::abilityCountdownChanged, this, &BaseLevel::updateAbilityCountdown);
}

void BaseLevel::setupScene(QString levelName) {
    setSceneRect(0, 0, 2000, 600);

    setKimo();
    setHUD(levelName);
    setEnemies();
    setEnvironment();
    kimo->setView(view);

    QTimer* hudUpdateTimer = new QTimer(this);
    connect(hudUpdateTimer, &QTimer::timeout, this, [this]() {
        if (!view || !HUD_health || !HUD_levelName) {
            return;
        }

        QPointF viewTopLeft = view->mapToScene(0, 0);
        HUD_health->setPos(viewTopLeft.x() + 10, viewTopLeft.y() + 10);
        HUD_levelName->setPos(viewTopLeft.x() + 10, viewTopLeft.y() + 35);

        // Update coins display position
        if (HUD_coins) {
            HUD_coins->setPos(viewTopLeft.x() + 600, viewTopLeft.y() + 20);
        }

        // Update store button position
        if (storeButtonProxy) {
            storeButtonProxy->setPos(viewTopLeft.x() + 700, viewTopLeft.y() + 20);
        }

        // Update ability countdown position
        if (HUD_abilityCountdown) {
            HUD_abilityCountdown->setPos(viewTopLeft.x() + 400, viewTopLeft.y() + 20);
        }

    });

    hudUpdateTimer->start(16); // ~60 FPS
}


void BaseLevel::setKimo() {
    kimo->setFlag(QGraphicsItem::ItemIsFocusable);
    kimo->setFocus();
    kimo->setPos(25,450);
    kimo->setPixmap(QPixmap(":/images/kimo/Kimo_right.png").scaled(64,64));
    addItem(kimo);
    kimo->setParentItem(nullptr);
    kimo->setParent(nullptr); // Ensures that when 'currentLevel' (in 'LevelOrchestrator') is deleted, that Kimo is not deleted with it
    kimo->setView(view);

    if (HUD_health)
        kimo->setHealthText(HUD_health); // This connects the 'HUD_health' text with Kimo's 'healthText'
}

void BaseLevel::setHUD(QString levelName) {

    // Ensuring setHUD() doesn't reuse a scene-bound text item which leads to crashes
    if (HUD_health && HUD_health->scene()) {
        HUD_health->scene()->removeItem(HUD_health);
    }
    if (HUD_levelName && HUD_levelName->scene()) {
        HUD_levelName->scene()->removeItem(HUD_levelName);
    }

    // Health Text in HUD
    if (HUD_health) {
        if (HUD_health->scene()) HUD_health->scene()->removeItem(HUD_health);
        HUD_health->setPlainText("Health: " + QString::number(kimo->getHealth()));
        HUD_health->setDefaultTextColor(Qt::white);
        HUD_health->setFont(QFont("Arial", 16));
        addItem(HUD_health);
    }

    if (HUD_levelName) {
        if (HUD_levelName->scene()) HUD_levelName->scene()->removeItem(HUD_levelName);
        HUD_levelName->setPlainText("Level: " + levelName);
        HUD_levelName->setDefaultTextColor(Qt::white);
        HUD_levelName->setFont(QFont("Arial", 16));
        addItem(HUD_levelName);
    }
}

void BaseLevel::stopMusic() {
    if (lvlMusicPlayer) lvlMusicPlayer->stop();
}

void BaseLevel::toggleStore() {
    if (!store->isVisible()) {
        store->setPos(view->mapToScene(0,0));
        addItem(store);
        store->setZValue(100);
        store->setVisible(true);
        kimo->setEnabled(false);       // blocks input
        kimo->pauseGame();             // pause logic
    } else {
        store->setVisible(false);
        removeItem(store);
        kimo->setEnabled(true);        // re-enable input
        kimo->setFocus();              // restore focus
        kimo->resumeGame();            // resume logic
    }
}

void BaseLevel::updateAbilityCountdown(const QString &abilityName, int remainingTime)
{
    if (remainingTime > 0)
    {
        HUD_abilityCountdown->setPlainText(QString("%1: %2s").arg(abilityName).arg(remainingTime));
        HUD_abilityCountdown->show();
    }
    else
    {
        HUD_abilityCountdown->hide();
    }
}
